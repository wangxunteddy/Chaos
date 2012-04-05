#include <map>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsRenderSystem.h"
#include "ChsRenderStates.h"
#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "shader/ChsShaderUniformSet.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "camera/ChsCameraBase.h"
#include "math/ChsMath.h"
#include "geometry/ChsCoordinatePlane.h"

namespace Chaos {

	typedef std::vector<ChsRenderUnit> ChsRenderUnitList;
	typedef std::map<ChsMaterial *, boost::shared_ptr<ChsRenderUnitList>> ChsRenderChain;
	ChsRenderChain renderChain;
	ChsShaderUniformSet globalUniformSet;
	ChsMatrix wvp;
	ChsMatrix wvit;
	ChsMatrix mtxWorld;
	ChsCoordinatePlane * debugCoordinatePlane;
	
	//----------------------------------------------------------------------------------------------
	ChsRenderSystem::ChsRenderSystem( void ) :	_root( new ChsRenderNode() ),
												framebuffer( 0 ),
												renderbuffer( 0 ),
												renderbufferWidth( 0 ),
												renderbufferHeight( 0 ),
												_currentCamera( NULL )
	{
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderSystem::~ChsRenderSystem( void ){
		safeDelete( &debugCoordinatePlane );
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::init( void ){
		this->initContext();
		this->initAllBuffers();
		this->initGL();
		globalUniformSet.reset();
		globalUniformSet.add( "wvp", CHS_SHADER_UNIFORM_MAT4, 1, &wvp);
		globalUniformSet.add( "wvit", CHS_SHADER_UNIFORM_MAT4, 1, &wvit );
		
		//add debug coordinate plane
		debugCoordinatePlane = new ChsCoordinatePlane( 50, 50 );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initGL( void ){
		this->setClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		this->setViewPort( 0, 0, this->renderbufferWidth, this->renderbufferHeight );

		glHint( GL_GENERATE_MIPMAP_HINT, GL_FASTEST );
		
		ChsRenderStates::sharedInstance()->queryCurrentStates();
		//以下内容在渲染过程中可能会被更改，如何更改，
		//depth
		//ChsRSDepthTest( CHS_RS_ENABLE);
		glDepthFunc( GL_LESS );
		glClearDepthf( 1.0f );
		
		//cull
		ChsRSCullFace( CHS_RS_ENABLE );
		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );
		
		//blend
		ChsRSBlend( CHS_RS_ENABLE );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::shutdown( void ){
		this->deleteAllBuffers();
		this->releaseContext();
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::preRender( void ){
		if( this->currentCamera() ){
			this->currentCamera()->update();
			wvp = mtxWorld * this->currentCamera()->getViewProjectionMatrix();
			wvit = mtxWorld * this->currentCamera()->getViewMatrix();
			wvit.inverse();
			wvit.transpose();
		}
		this->root()->renderNodes( this );
		glBindFramebuffer( GL_FRAMEBUFFER, this->framebuffer );
    	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	//----------------------------------------------------------------------------------------------
	static ChsShaderProgram * currentShaderProgram;

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::render( void ){
		std::pair<ChsMaterial *, boost::shared_ptr<ChsRenderUnitList>> p;
		BOOST_FOREACH( p, renderChain ){
			ChsMaterial * material = p.first;
			currentShaderProgram = material->apply( currentShaderProgram );
			globalUniformSet.apply( currentShaderProgram );
			BOOST_FOREACH( const ChsRenderUnit & unit, *p.second ){
				unit.vertexBuffer->preDraw();
				unit.indexBuffer->draw();
				unit.vertexBuffer->postDraw();
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::postRender( void ) {
		renderChain.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::update( void ) {
		this->attachContext();
		this->preRender();
		this->render();
		this->present();
		this->postRender();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::sendToRender( ChsRenderUnit unit ){
		ChsMaterial * material = unit.material;
		auto iter = renderChain.find( material );
		if( iter != renderChain.end() ){
			boost::shared_ptr<ChsRenderUnitList> & list = iter->second;
			list->push_back( unit );
		}
		else{
			boost::shared_ptr<ChsRenderUnitList> list( new ChsRenderUnitList() );
			list->push_back( unit );
			insert( renderChain )( material, list );
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initAllBuffers( void ){
		this->deleteAllBuffers();
		this->initRenderBuffer();
		this->initFrameBuffer();
		this->initDepthBuffer();
		if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
            printf( "Failed to make complete framebuffer object %x\n", glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initFrameBuffer( void ){
		glGenFramebuffers( 1, &(this->framebuffer) );
		glBindFramebuffer( GL_FRAMEBUFFER, this->framebuffer );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->renderbuffer );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initDepthBuffer( void ){
		glGenRenderbuffers(1, &(this->depthRenderbuffer) );
		glBindRenderbuffer(GL_RENDERBUFFER, this->depthRenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, this->renderbufferWidth, this->renderbufferHeight );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthRenderbuffer );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::deleteAllBuffers( void ){
		if( this->framebuffer ){
            glDeleteFramebuffers( 1, &(this->framebuffer) );
            this->framebuffer = 0;
        }
		if( this->renderbuffer ){
            glDeleteRenderbuffers( 1, &(this->renderbuffer) );
            this->renderbuffer = 0;
        }
		if( this->depthRenderbuffer ){
            glDeleteRenderbuffers( 1, &(this->depthRenderbuffer) );
            this->depthRenderbuffer = 0;
        }
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( float r, float g, float b, float a ){
		glClearColor( r, g, b, a );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a ){
		this->setClearColor( r/255.f, g/255.f, b/255.f, a/255.f );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( unsigned int rgba ){
		this->setClearColor( static_cast<unsigned char>( ( rgba & 0xff0000 ) >> 16 ),
							static_cast<unsigned char>( ( rgba & 0xff00 ) >> 8 ),
							static_cast<unsigned char>( ( rgba & 0xff ) ),
							static_cast<unsigned char>( ( rgba & 0xff000000 ) >> 24 ) );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setViewPort( int x, int y, int w, int h ){
		this->viewport.x = x;
		this->viewport.y = y;
		this->viewport.w = w;
		this->viewport.h = h;
		glViewport( this->viewport.x, this->viewport.y, this->viewport.w, this->viewport.h );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::showDebugCoordinate( bool isShow ){
		if( this->showDebugCoordinate() != isShow ){
			if( isShow )
				this->root()->add( debugCoordinatePlane->name(), debugCoordinatePlane );
			else
				this->root()->remove( debugCoordinatePlane->name() );
			this->_showDebugCoordinate = isShow;
		}
	}
	
}//namespace
