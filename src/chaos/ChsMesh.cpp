#include <OpenGLES/ES2/gl.h>
#include "ChsMesh.h"
#include "ChsMaterial.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "ChsShaderProgram.h"
#include "ChsResourceManager.h"
#include "ChsUtility.h"
#include "ChsRenderSystem.h"

namespace Chaos {
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMesh::ChsMesh( ) : vertexBuffer( NULL ), 
						  indexBuffer( NULL )
	{
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMesh::~ChsMesh( ) {
		safeDelete( &this->vertexBuffer );
		safeDelete( &this->indexBuffer );
		safeDelete( &this->material );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::doRender( ChsRenderSystem * render ) {
		ChsRenderUnit unit;
		unit.material = this->material;
		unit.vertexBuffer = this->vertexBuffer;
		unit.indexBuffer = this->indexBuffer;
		render->sendToRender(unit);
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::load( const float * vertices, int verCount, const void * indices ) {
#if 0
		this->vertexBuffer = new ChsVertexBuffer( );
		this->vertexBuffer->addAttrib( 2, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "color" );
		this->vertexBuffer->setData( vertices, verCount );
		
		this->indexBuffer = new ChsIndexBuffer( );
		this->indexBuffer->setData( indices, 4, GL_UNSIGNED_BYTE, GL_TRIANGLE_STRIP);
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::setMaterial( ) {
		this->material = new ChsMaterial( );
		this->initShader( );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::initShader( ) {
		this->material->setShader("Shader.vsh", "Shader.fsh");
		ChsShaderProgram * program =  this->material->getShaderProgram();
		
		// Bind attribute locations.
		// This needs to be done prior to linking.
		this->vertexBuffer->bindAttribLocations( program );
		
		// Link program.
		if ( !program->link( ) ) {
			printf("Failed to link program: %d", program->handle() );
			delete this->material;
			this->material = NULL;
		}
	}

//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
