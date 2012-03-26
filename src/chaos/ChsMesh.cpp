#include "platform/ChsOpenGL.h"
#include "ChsMesh.h"
#include "ChsMaterial.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "ChsResourceManager.h"
#include "ChsUtility.h"
#include "ChsRenderSystem.h"
#include "ChsTexture2D.h"
#include "shader/ChsShaderProgram.h"

namespace Chaos {
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMesh::ChsMesh( std::string name ) : ChsRenderNode( name ),
											vertexBuffer(new ChsVertexBuffer()),
											indexBuffer(new ChsIndexBuffer())
	{
		this->material = NULL;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMesh::~ChsMesh( void ) {
		safeDelete( &this->material );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::doRender( ChsRenderSystem * render ) {
		ChsRenderUnit unit;
		unit.material = this->material;
		unit.vertexBuffer = this->vertexBuffer.get();
		unit.indexBuffer = this->indexBuffer.get();
		render->sendToRender(unit);
	}
#if 0
	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::load( const float * vertices, int verCount, const void * indices ) {
		this->vertexBuffer = new ChsVertexBuffer( );
		this->vertexBuffer->addAttrib( 2, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "color" );
		this->vertexBuffer->setData( vertices, verCount );
		
		this->indexBuffer = new ChsIndexBuffer( );
		this->indexBuffer->setData( indices, 4, GL_UNSIGNED_SHORT, GL_TRIANGLE_STRIP);
	}
#endif
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::setMaterial( void ) {
		this->material = new ChsMaterial();
		boost::shared_ptr<ChsShaderProgram> shaderProgram( ChsResourceManager::sharedInstance()->getShaderProgram("Shader.vsh", "Shader.fsh") );
		
		// Bind attribute locations.
		// This needs to be done prior to linking.
		this->vertexBuffer->bindAttribLocations( shaderProgram.get() );
		
		// Link program.
		if ( !shaderProgram->link() ) {
			printf("Failed to link program: %d", shaderProgram->handle() );
			delete this->material;
			this->material = NULL;
		}
		this->material->setShader( shaderProgram );
	}

//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
