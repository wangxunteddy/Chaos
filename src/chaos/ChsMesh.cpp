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
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMesh::~ChsMesh( void ) {
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::render( ChsRenderSystem * render ) {
		ChsRenderUnit unit;
		unit.material = this->material.get();
		unit.vertexBuffer = this->vertexBuffer.get();
		unit.indexBuffer = this->indexBuffer.get();
		render->sendToRender(unit);
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMesh::setMaterial( ChsMaterial * material ) {
		this->material.reset( material );
		if( this->material ){
			// Bind attribute locations.
			// This needs to be done prior to linking.
			this->vertexBuffer->bindAttribLocations( this->material->shaderProgram().lock().get() );
			this->material->linkShader();
		}
	}

//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
