#include <stdio.h>
#include "ChsShaderProgram.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsShaderProgram:: ChsShaderProgram( void ) : ChsShader(0) {
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

	static GLuint lastUsedProgramHandle = -1;
	//----------------------------------------------------------------------------------------------
	void ChsShaderProgram::use( void ){
		GLuint currentHandle = this->handle();
		if( lastUsedProgramHandle != currentHandle ){
			lastUsedProgramHandle = currentHandle;
	    	glUseProgram( currentHandle );
		}
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
	    glGetProgramiv( this->handle(), GL_INFO_LOG_LENGTH, &logLength);
    	if (logLength > 0) {
        	GLchar *log = new GLchar[ logLength ];
	        glGetProgramInfoLog( this->handle(), logLength, &logLength, log );
    	    printf("Program link log:\n%s", log);
        	delete [ ] log;
	    }
	#endif
    	GLint status;
	    glGetProgramiv( this->handle(), GL_LINK_STATUS, &status );
    	return status;
	}

	//----------------------------------------------------------------------------------------------
	void ChsShaderProgram::attachShader( ChsShader * shader ) {
    	glAttachShader( this->handle(), shader->handle() );
	}

	//----------------------------------------------------------------------------------------------
	int ChsShaderProgram::getUniformLocation( const char * name ){
		return glGetUniformLocation( this->handle(), name );
	}
	//----------------------------------------------------------------------------------------------
}//namespace
