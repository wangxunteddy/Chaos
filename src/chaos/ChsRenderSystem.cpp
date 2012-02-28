#include <map>
#include <vector>

#include "ChsRenderSystem.h"
#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"


namespace Chaos {

	typedef std::vector<ChsRenderUnit> ChsRenderUnitList;
	
	typedef std::map<ChsMaterial *, ChsRenderUnitList *> ChsRenderChain;
	ChsRenderChain renderChain;
	
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
												renderbufferHeight( 0 )
	{
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderSystem::~ChsRenderSystem( void ){
		safeDelete( &this->_root );
	}
	
	// Uniform index.
//	enum {
//		UNIFORM_TRANSLATE,
//		NUM_UNIFORMS
//	};
//	GLint uniforms[NUM_UNIFORMS];
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::init( void ){
		this->initContext();
		this->initFrameAndRenderBuffers();
		this->setClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		//uniforms[UNIFORM_TRANSLATE] = mesh->getMaterial( )->getShaderProgram()->getUniformLocation( "translate" );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::shutdown( void ){
		safeDelete( &this->_root, "delete render root node");
		this->deleteFrameAndRenderBuffers();
		this->releaseContext();
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::preRender( void ) {
		this->_root->render( this );
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
		glViewport(0, 0, this->renderbufferWidth, this->renderbufferHeight);
    	glClear(GL_COLOR_BUFFER_BIT);
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::render( void ){
		ChsRenderChain::iterator iter = renderChain.begin();
		ChsRenderChain::iterator end = renderChain.end();
		for(;iter!=end;iter++){
			ChsMaterial * material = iter->first;
			material->apply();
			ChsRenderUnitList *list = iter->second;
			for(int i=0;i<list->size();i++){
				ChsRenderUnit unit = list->at(i);
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
	void ChsRenderSystem::sendToRender(ChsRenderUnit unit){
		ChsMaterial * material = unit.material;
		ChsRenderChain::iterator iter = renderChain.find(material);
		if( iter!= renderChain.end() ){
			ChsRenderUnitList * list = iter->second;
			list->push_back(unit);
		}
		else{
			ChsRenderUnitList * list = new ChsRenderUnitList();
			list->push_back(unit);
			renderChain.insert(std::make_pair(material, list));
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::initFrameAndRenderBuffers( void ){
		glGenFramebuffers(1, &(this->framebuffer));
		glGenRenderbuffers(1, &(this->renderbuffer));
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, this->renderbuffer);
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::deleteFrameAndRenderBuffers( void ){
		if(this->framebuffer){
            glDeleteFramebuffers(1, &(this->framebuffer));
            this->framebuffer = 0;
        }
		if(this->renderbuffer) {
            glDeleteRenderbuffers(1, &(this->renderbuffer));
            this->renderbuffer = 0;
        }
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor(float r,float g,float b,float a){
		glClearColor(r, g, b, a);
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a){
		this->setClearColor( r/255.f, g/255.f, b/255.f, a/255.f );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor(unsigned int rgba){
		this->setClearColor((unsigned char)(rgba & 0xff0000)>>16,
							(unsigned char)(rgba & 0xff00)>>8,
							(unsigned char)(rgba & 0xff),
							(unsigned char)(rgba & 0xff000000)>>24);
	}

	//----------------------------------------------------------------------------------------------

}//namespace
