#include <stdio.h>
#include <boost/scoped_ptr.hpp>

#include "ChsShader.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsShader::ChsShader( int type ) : _handle( 0 ){
		if( type ){
	    	this->type = type;
		    this->_handle = glCreateShader( type );
		}
	}

	//----------------------------------------------------------------------------------------------
	ChsShader::~ChsShader( void ){
		if( this->_handle ){
		   	glDeleteShader( this->_handle );
	    	this->_handle = 0;
		}
	}

	//----------------------------------------------------------------------------------------------
	bool ChsShader::load( const char * source ) {
    	if ( !source ) {
        	printf("Failed to load vertex shader" );
	        return false;
    	}
	    glShaderSource( this->handle(), 1, &source, NULL );
    	return this->compile();
	}

	//----------------------------------------------------------------------------------------------
	bool ChsShader::compile( void ) {
    	glCompileShader( this->handle() );
	    return this->getStatus();
	}

	//----------------------------------------------------------------------------------------------
	int ChsShader::getStatus( void ) {
	#if defined( DEBUG )
    	GLint logLength;
	    glGetShaderiv( this->handle(), GL_INFO_LOG_LENGTH, &logLength );
    	if ( logLength > 0 ) {
			boost::scoped_ptr<GLchar> log( new GLchar[logLength] );
			glGetShaderInfoLog( this->handle(), logLength, &logLength, log.get() );
    	    printf( "Shader compile log:\n%s", log.get() );
	    }
	#endif
    	GLint status;
	    glGetShaderiv( this->handle(), GL_COMPILE_STATUS, &status );
    	return status;
	}

//--------------------------------------------------------------------------------------------------
}//namespace
