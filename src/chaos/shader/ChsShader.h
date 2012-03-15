#ifndef _CHS_SHADER_H
#define _CHS_SHADER_H
#pragma once

#include "ChsMacro.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsShader{
	public :
		ChsShader( int type );
		virtual ~ChsShader( void );
		bool load( const char * source );
		
	protected:
		int type;

	private:
		bool compile( void );
		int getStatus( void );

		PROPERTY_CONST( GLuint, handle )

	};

	SYNTHESIZE_CONST( ChsShader, GLuint, handle )

	
	//----------------------------------------------------------------------------------------------
	class ChsFragmentShader : public ChsShader{
	public:
		ChsFragmentShader( void ) : ChsShader( GL_FRAGMENT_SHADER ){}
	};

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsVertexShader : public ChsShader{
	public:
		ChsVertexShader( void ) : ChsShader( GL_VERTEX_SHADER ){}
	};
	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHSSHADER_H
