#include "ChsVertexBuffer.h"
#include "shader/ChsShaderProgram.h"
#include "ChsUtility.h"
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsVertexBuffer::ChsVertexBuffer( void ) :	vboHandle( 0 ) ,
												vaoHandle( 0 ),
												vertices( NULL ),
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
		attribs.clear();
		safeDeleteArray( &this->vertices );
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribLocations( const ChsShaderProgram * program ) {
		BOOST_FOREACH( const ChsAttribUnitPtr & attrib, this->attribs )
			glBindAttribLocation( program->handle(), attrib->index, attrib->name.c_str() );
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::setData( const void * vertices, int size ) {
    	this->size = size;
		safeDeleteArray( &this->vertices );
		this->vertices = new char[size];
		memcpy( this->vertices, vertices, size );
		this->isNeedUpdate = true;
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::addAttrib( int count, int type, bool isNormalized, std::string name ) {
		ChsAttribUnitPtr attrib( new ChsAttribUnit( count, type, isNormalized, name ) );
    	int lastOne = this->attribs.size();
	    attrib->index = lastOne;
	    int stride = 0;
    	if( lastOne ) {
        	const ChsAttribUnitPtr & lastAttrib = this->attribs[lastOne-1];
	        attrib->offset = lastAttrib->offset + lastAttrib->size;
    	    stride = lastAttrib->stride;
	    }
    	else{
	        attrib->offset = 0;
    	}
	    this->attribs += attrib;
    	stride += attrib->size;
		BOOST_FOREACH( const ChsAttribUnitPtr & attrib, this->attribs )
			attrib->stride = stride;
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribArrays( void ){
    	glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
		BOOST_FOREACH( const ChsAttribUnitPtr & attrib, this->attribs )
			attrib->bind();
	}

	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbindAttribArrays( void ){
	    BOOST_FOREACH( const ChsAttribUnitPtr & attrib, this->attribs )
			attrib->unbind();
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
		this->bindAttribArrays();
		glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
    	glBufferData( GL_ARRAY_BUFFER, this->size, this->vertices,  GL_STATIC_DRAW );
		this->isNeedUpdate = false;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::preDraw( void ){
		this->bindVertexArray();
		if( this->isNeedUpdate )
			this->update();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsVertexBuffer::postDraw( void ){
		this->unbindVertexArray();
	}

}//namespace
