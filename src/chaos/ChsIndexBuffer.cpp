#include <OpenGLES/ES2/gl.h>
#include "ChsIndexBuffer.h"
#include "string.h"
#include "ChsUtility.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	ChsIndexBuffer::ChsIndexBuffer( ) : handle( 0 ) {
		this->isNeedUpdate = false;
    	glGenBuffers( 1, &this->handle );
	}

	//----------------------------------------------------------------------------------------------
	ChsIndexBuffer::~ChsIndexBuffer( ) {
    	if( this->handle )
        	glDeleteBuffers( 1, &this->handle );
	}

	//----------------------------------------------------------------------------------------------
	void ChsIndexBuffer::setData( const void * triangles, int count, int type, int mode ) {
    	this->mode = mode;
	    this->type = type;
    	this->count = count;
	    this->size = getGLDataTypeSize( type ) * count ;
		safeDeleteArray(&this->triangles);
		this->triangles = new char[this->size];
		memcpy( this->triangles, triangles, size );
    	this->isNeedUpdate = true;
	}

	//----------------------------------------------------------------------------------------------
	void ChsIndexBuffer::draw( ) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handle );
		if(this->isNeedUpdate){
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->size, this->triangles, GL_STATIC_DRAW); 
			this->isNeedUpdate = false;
		}
	    glDrawElements( this->mode, this->count, this->type, 0 );
	}

	//----------------------------------------------------------------------------------------------
	
}//namespace
