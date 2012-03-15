#include <map>
#include <vector>

#include "ChsRenderSystem.h"
#include "ChsRenderNode.h"
#include "ChsUtility.h"
//#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "shader/ChsShaderUniform.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "camera/ChsCameraBase.h"
#include "math/ChsMath.h"
#include "geometry/ChsCoordinatePlane.h"

namespace Chaos {

	typedef std::vector<ChsRenderUnit> ChsRenderUnitList;
	
	typedef std::map<ChsMaterial *, ChsRenderUnitList *> ChsRenderChain;
	ChsRenderChain renderChain;
	ChsShaderUniform globalUniforms;
	ChsMatrix wvp;
	ChsMatrix mtxWorld;
	ChsCoordinatePlane * debugCoordinatePlane;
	//----------------------------------------------------------------------------------------------
	class ChsRenderRoot : public ChsRenderNode {
	private:
		void doRender( ChsRenderSystem * render ){}
	};
	
	//----------------------------------------------------------------------------------------------
	ChsRenderSystem::ChsRenderSystem( void ) :	_root( new ChsRenderRoot() ),
												framebuffer( 0 ),
												renderbuffer( 0 ),
												renderbufferWidth( 0 ),
												renderbufferHeight( 0 ),
												_currentCamera( NULL )
	{
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderSystem::~ChsRenderSystem( void ){
		safeDelete( &this->_root );
		safeDelete( &debugCoordinatePlane );
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::init( void ){
		this->initContext();
		this->initFrameAndRenderBuffers();
		this->initGL();
		globalUniforms.reset();
		globalUniforms.add( "wvp", &wvp, CHS_SHADER_UNIFORM_MAT4, 1 );
		
		//add debug coordinate plane
		debugCoordinatePlane = new ChsCoordinatePlane( 50, 50 );
		debugCoordinatePlane->setMaterial();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initGL( void ){
		this->setClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		this->setViewPort( 0, 0, this->renderbufferWidth, this->renderbufferHeight );

		//以下内容在渲染过程中可能会被更改，如何更改，
		//depth
		glEnable( GL_DEPTH_TEST );
		glClearDepthf( 1.0f );
		glDepthFunc( GL_LEQUAL );
		
		//cull
		//glEnable( GL_CULL_FACE );
		glCullFace( GL_FRONT );
		glFrontFace( GL_CW );
		
		//blend
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		
	}
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::shutdown( void ){
		safeDelete( &this->_root, "delete render root node");
		this->deleteFrameAndRenderBuffers();
		this->releaseContext();
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::preRender( void ){
		if( this->currentCamera() ){
			this->currentCamera()->update();
			wvp = mtxWorld * this->currentCamera()->getViewProjectionMatrix();
		}
		this->root()->render( this );
		glBindFramebuffer( GL_FRAMEBUFFER, this->framebuffer );
    	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	//----------------------------------------------------------------------------------------------
	static ChsShaderProgram * currentShaderProgram = NULL;

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::render( void ){
		ChsRenderChain::iterator iter = renderChain.begin();
		ChsRenderChain::iterator end = renderChain.end();
		for( ; iter!=end; iter++ ){
			ChsMaterial * material = iter->first;
			currentShaderProgram = material->apply( currentShaderProgram );
			globalUniforms.apply( currentShaderProgram );
			ChsRenderUnitList *list = iter->second;
			for( int i=0; i<list->size(); i++ ){
				ChsRenderUnit unit = list->at( i );
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
		ChsRenderChain::iterator iter = renderChain.find( material );
		if( iter != renderChain.end() ){
			ChsRenderUnitList * list = iter->second;
			list->push_back( unit );
		}
		else{
			ChsRenderUnitList * list = new ChsRenderUnitList();
			list->push_back( unit );
			renderChain.insert( std::make_pair( material, list ) );
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initFrameAndRenderBuffers( void ){
		this->deleteFrameAndRenderBuffers();
		glGenFramebuffers( 1, &(this->framebuffer) );
		glGenRenderbuffers( 1, &(this->renderbuffer) );
		glBindFramebuffer( GL_FRAMEBUFFER, this->framebuffer );
		glBindRenderbuffer( GL_RENDERBUFFER, this->renderbuffer );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::deleteFrameAndRenderBuffers( void ){
		if( this->framebuffer ){
            glDeleteFramebuffers( 1, &(this->framebuffer) );
            this->framebuffer = 0;
        }
		if( this->renderbuffer ){
            glDeleteRenderbuffers( 1, &(this->renderbuffer) );
            this->renderbuffer = 0;
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
		this->setClearColor( (unsigned char)(rgba & 0xff0000)>>16,
							(unsigned char)(rgba & 0xff00)>>8,
							(unsigned char)(rgba & 0xff),
							(unsigned char)(rgba & 0xff000000)>>24);
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
