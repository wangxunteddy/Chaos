#include "ChsCoordinatePlane.h"
#include "platform/ChsOpenGL.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"

namespace Chaos {
	
	ChsCoordinatePlane::ChsCoordinatePlane( float size, int divide ) : ChsCoordinatePlane( "Coordinate Plane", size, divide ){
	}
	
	struct Vertex{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
		float a;
	};
	
	ChsCoordinatePlane::ChsCoordinatePlane( std::string name, float size, int divide ){
		int vertexCount = 2 * ( divide+1)*2;
		Vertex * vertices = new Vertex[vertexCount];
		float stepSize = size/divide;
		float w = size/2;
		for( int i=-divide/2,k=0;i<=divide/2;++i,k+=4){
			if(i==0){
				for(int j=0;j<4;j++){
					vertices[k+j].r = 0.0f;//r
					vertices[k+j].g = 1.0f;//g
					vertices[k+j].b = 0.0f;//b
					vertices[k+j].a = 1.0f;//a
				}
				w = size/2 + stepSize;
			}
			else{
				for(int j=0;j<4;j++){
					vertices[k+j].r = 1.0f;//r
					vertices[k+j].g = 1.0f;//g
					vertices[k+j].b = 1.0f;//b
					vertices[k+j].a = 0.9f;//a
				}
				w = size/2;
			}
			vertices[k].z = w;
			vertices[k+1].z = -w;
			vertices[k+2].x = w;
			vertices[k+3].x = -w;

			vertices[k].x = i*stepSize;
			vertices[k+1].x = i*stepSize;
			vertices[k+2].z = i*stepSize;
			vertices[k+3].z = i*stepSize;

			vertices[k].y = 0.0f;
			vertices[k+1].y = 0.0f;
			vertices[k+2].y = 0.0f;
			vertices[k+3].y = 0.0f;
		}
		this->vertexBuffer = new ChsVertexBuffer( );
		this->vertexBuffer->addAttrib( 3, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		this->vertexBuffer->setData( vertices, sizeof(Vertex)*vertexCount );
		delete [] vertices;
		
		int indexCount = vertexCount;
		GLushort * indices = new GLushort [indexCount];
		for( int i=0;i<indexCount;i++)
			indices[i] = (GLushort)i;
		
		this->indexBuffer = new ChsIndexBuffer( );
		this->indexBuffer->setData( indices, indexCount, GL_UNSIGNED_SHORT, GL_LINES);
		delete [] indices;
	}

}