#include "ChsTexture2D.h"
#include "ChsFileSystem.h"
#include "ChsUtility.h"
#include "shader/ChsShaderProgram.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsTexture2D::ChsTexture2D( void ) : _type( GL_UNSIGNED_BYTE ),
										_handle( 0 ){
	}
	
	//----------------------------------------------------------------------------------------------
	ChsTexture2D::~ChsTexture2D( void ){
		if( this->handle() )
			glDeleteTextures( 1, &(this->_handle) );
		safeDeleteArray( &(this->_data));
	}
	
	//----------------------------------------------------------------------------------------------
	GLuint currentTextureHandle = -1;
	//----------------------------------------------------------------------------------------------
	void ChsTexture2D::bind( void ){
		if( currentTextureHandle == this->handle() )
			return;
		glBindTexture( GL_TEXTURE_2D, this->handle() );
		glActiveTexture( this->activeUnit() );
		currentTextureHandle = this->handle();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsTexture2D::build( GLuint width, GLuint height, GLenum format, GLubyte* data ){
		this->_width = width;
		this->_height = height;
		this->_format = format;
		this->_data = data;

		glGenTextures( 1, &(this->_handle) );
		glBindTexture( GL_TEXTURE_2D, this->handle() );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Allocate and load image data into texture
		glTexImage2D( GL_TEXTURE_2D, 0, this->format(), this->width(), this->height(), 0,
					 this->format(), this->type(), this->data() );
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	//----------------------------------------------------------------------------------------------
	
}
