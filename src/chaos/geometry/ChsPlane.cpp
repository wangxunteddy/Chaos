#include "platform/ChsOpenGL.h"
#include "ChsPlane.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"

namespace Chaos {

	ChsPlane::ChsPlane( std::string name, float w, float h ) : ChsMesh( name ) {
		const GLfloat vertices[] = {
			-w/2, -h/2, 0.0f,
			1.0f, 1.0f,   0, 1.0f,
			
			w/2, -h/2, 0.0f,
			0,   1.0f, 1.0f, 1.0f,
			
			-w/2,  h/2, 0.0f,
			0,     0,   0,   0,
			
			w/2,  h/2, 0.0f,
			1.0f,   0, 1.0f, 1.0f,
		};
		memcpy( this->vertices, vertices, sizeof( vertices ) );
		
		this->vertexBuffer->addAttrib( 3, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		this->vertexBuffer->setData( vertices, sizeof( vertices ) );
		
		const GLubyte indices[]={
			0,1,2,3
		};
		this->indexBuffer->setData( indices, 4, GL_UNSIGNED_BYTE );
		this->indexBuffer->mode( GL_TRIANGLE_STRIP );
	}
	
	ChsPlane::ChsPlane( float w, float h ) : ChsPlane( "unnamed", w, h ) {
	}

}
