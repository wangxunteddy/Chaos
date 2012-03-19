#include <string>
#include "ChsIndexBuffer.h"
#include "ChsUtility.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	ChsIndexBuffer::ChsIndexBuffer( void ) : handle( 0 ), triangles( NULL ){
		this->isNeedUpdate = false;
    	glGenBuffers( 1, &this->handle );
	}

	//----------------------------------------------------------------------------------------------
	ChsIndexBuffer::~ChsIndexBuffer( void ){
    	if( this->handle )
        	glDeleteBuffers( 1, &this->handle );
		safeDeleteArray( &this->triangles );
	}

	//----------------------------------------------------------------------------------------------
	void ChsIndexBuffer::setData( const void * triangles, int count, int type ){
	    this->type = type;
    	this->count = count;
	    this->size = getGLDataTypeSize( type ) * count ;
		safeDeleteArray( &this->triangles );
		this->triangles = new char[this->size];
		memcpy( this->triangles, triangles, size );
    	this->isNeedUpdate = true;
	}

	//----------------------------------------------------------------------------------------------
	void ChsIndexBuffer::draw( void ){
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->handle );
		if( this->isNeedUpdate ){
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->size, this->triangles, GL_STATIC_DRAW ); 
			this->isNeedUpdate = false;
		}
	    glDrawElements( this->_mode, this->count, this->type, 0 );
	}

	//----------------------------------------------------------------------------------------------
	
}//namespace
