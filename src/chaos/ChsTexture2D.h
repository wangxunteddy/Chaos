#ifndef _CHS_TEXTURE2D_H
#define _CHS_TEXTURE2D_H

#include <string>
#include "ChsMacro.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsTexture2D {
		friend class ChsTextureFactory;
	public:
		ChsTexture2D( void );
		~ChsTexture2D( void );
		void build( GLuint width, GLuint height, GLenum format, GLubyte * data );
		void bind( void );

		inline const GLuint * activeUnitPtr( void ) const ;
	private:

		PROPERTY_READONLY_CONST( GLuint, handle );
		PROPERTY_READONLY_CONST( GLuint, width );
		PROPERTY_READONLY_CONST( GLuint, height );
		PROPERTY_READONLY_CONST( GLenum, format );
		PROPERTY_READONLY_CONST( GLenum, type );
		PROPERTY_READONLY_CONST( std::string, name );
		PROPERTY_READONLY_CONST( boolean, hasAlpha );
		PROPERTY_READONLY_CONST( GLubyte *, data );
		PROPERTY( GLuint, activeUnit );
		PROPERTY( std::string, sampleName );
	};
	
	//----------------------------------------------------------------------------------------------
	inline const GLuint * ChsTexture2D::activeUnitPtr( void ) const {
		return &(this->_activeUnit);
	}
	
	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLuint, handle );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLuint, width );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLuint, height );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLenum, format );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLenum, type );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, std::string, name );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, boolean, hasAlpha );
	SYNTHESIZE_READONLY_CONST( ChsTexture2D, GLubyte*, data );
	SYNTHESIZE( ChsTexture2D, GLuint, activeUnit );
	SYNTHESIZE( ChsTexture2D, std::string, sampleName );
}


#endif//_CHS_TEXTURE2D_H
