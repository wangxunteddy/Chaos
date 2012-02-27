#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "ChsVertexBuffer.h"
#include "ChsShaderProgram.h"
#include "ChsUtility.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsVertexBuffer::ChsVertexBuffer( void ) :	vboHandle( 0 ) ,
												vaoHandle( 0 ),
												isNeedUpdate( false )
	{
    	glGenBuffers( 1, &this->vboHandle );
	    glGenVertexArraysOES( 1, &this->vaoHandle);
	}

	//----------------------------------------------------------------------------------------------
	ChsVertexBuffer::~ChsVertexBuffer( void ){
    	if( this->vboHandle )
        	glDeleteBuffers( 1, &this->vboHandle );
	    if( this->vaoHandle )
    	    glDeleteVertexArraysOES( 1, &this->vaoHandle);

		for( int i=0; i< this->attribs.size(); i++){
    	    ChsAttribUnit * attrib = this->attribs[i];
	       	safeDelete(&attrib);
    	}
		attribs.clear( );
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribLocations( const ChsShaderProgram * program ) {
    	for( int i=0; i< this->attribs.size(); i++){
        	ChsAttribUnit * attrib = this->attribs[i];
	        glBindAttribLocation( program->handle(), attrib->index, attrib->name.c_str( ) );
    	}
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::setData( const void * vertices, int size ) {
    	this->size = size;
		safeDeleteArray( &this->vertices );
		this->vertices = new char[size];
		memcpy(this->vertices, vertices, size);
		this->isNeedUpdate = true;
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::addAttrib( int count, int type, bool isNormalized, std::string name ) {
		ChsAttribUnit * attrib = new ChsAttribUnit(count,type,isNormalized,name);
    	int lastOne = this->attribs.size();
	    attrib->index = lastOne;
	    int stride = 0;
    	if( lastOne ) {
        	ChsAttribUnit * lastAttrib = this->attribs[lastOne-1];
	        attrib->offset = lastAttrib->offset + lastAttrib->size;
    	    stride = lastAttrib->stride;
	    }
    	else{
	        attrib->offset = 0;
    	}
	    this->attribs.push_back(attrib);
    	stride += attrib->size;
	    lastOne = this->attribs.size();
    	for( int i=0; i< lastOne; i++)
	        this->attribs[i]->stride = stride;
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribArrays( void ){
    	glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
	    for( int i=0; i< this->attribs.size(); i++){
    	    ChsAttribUnit * attrib = this->attribs[i];
	       	attrib->bind( );
    	}
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbindAttribArrays( void ){
	    for( int i=0; i< this->attribs.size(); i++){
    	    ChsAttribUnit * attrib = this->attribs[i];
        	attrib->unbind( );
	    }
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindVertexArray( void ){
    	glBindVertexArrayOES( this->vaoHandle );
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbindVertexArray( void ){
    	glBindVertexArrayOES( 0 );
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::update( void ){
		this->bindAttribArrays( );
		glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
    	glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices,  GL_STATIC_DRAW);
		this->isNeedUpdate = false;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::preDraw( void ){
		this->bindVertexArray();
		if(this->isNeedUpdate)
			this->update();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::postDraw( void ){
		this->unbindVertexArray();
	}

}//namespace
