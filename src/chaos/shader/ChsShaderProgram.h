#ifndef _CHS_SHADERPROGRAM_H
#define _CHS_SHADERPROGRAM_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsShader.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsShaderProgram : public ChsShader{
	public:
		ChsShaderProgram( void );
		~ChsShaderProgram( void );
		bool link( void );
		void use( void );
		bool validate( void );
		void attachShader( ChsShader * shader );
		int getUniformLocation( const char * name );
	private:
		int getStatus( void );

		PROPERTY_CONST( GLuint, handle )
		bool load( const char * source ){ return false; }
		
	};
	
	SYNTHESIZE_CONST( ChsShaderProgram, GLuint, handle )

	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_SHADERPROGRAM_H
