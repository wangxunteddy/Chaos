#include <stdio.h>
#include <boost/scoped_ptr.hpp>

#include "ChsShaderProgram.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsShaderProgram:: ChsShaderProgram( void ) : ChsShader( 0 ) {
    	this->handle( glCreateProgram() );
	}

	//----------------------------------------------------------------------------------------------
	ChsShaderProgram:: ~ChsShaderProgram( void ){
	    glDeleteProgram( this->handle() );
    	this->handle( 0 );
	}

	//----------------------------------------------------------------------------------------------
	bool ChsShaderProgram::link( void ){
    	glLinkProgram( this->handle() );
	    return this->getStatus();
	}

	//----------------------------------------------------------------------------------------------
	void ChsShaderProgram::use( void ){
    	glUseProgram( this->handle() );
	}

	//----------------------------------------------------------------------------------------------
	bool ChsShaderProgram::validate( void ){
    	glValidateProgram( this->handle() );
	    return this->getStatus();
	}

	//----------------------------------------------------------------------------------------------
	int ChsShaderProgram::getStatus( void ) {
	#if defined(DEBUG)
    	GLint logLength;
	    glGetProgramiv( this->handle(), GL_INFO_LOG_LENGTH, &logLength );
    	if ( logLength > 0 ){
			boost::scoped_ptr<GLchar> log( new GLchar[logLength] );
	        glGetProgramInfoLog( this->handle(), logLength, &logLength, log.get() );
    	    printf( "Program link log:\n%s", log.get() );
	    }
	#endif
    	GLint status;
	    glGetProgramiv( this->handle(), GL_LINK_STATUS, &status );
    	return status;
	}

	//----------------------------------------------------------------------------------------------
	void ChsShaderProgram::attachShader( const boost::shared_ptr<ChsShader> & shader ) {
    	glAttachShader( this->handle(), shader->handle() );
	}

	//----------------------------------------------------------------------------------------------
	int ChsShaderProgram::getUniformLocation( const char * name ){
		return glGetUniformLocation( this->handle(), name );
	}
	//----------------------------------------------------------------------------------------------
}//namespace
