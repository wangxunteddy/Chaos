#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <map>
#include <string>
#include "ChsMacro.h"
#include "shader/ChsShaderUniform.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    	ChsMaterial( void );
	    ~ChsMaterial( void );
    	void apply( void );
	    void setShader( ChsShaderProgram * program );
	private:
		ChsShaderUniform shaderUniforms;
		PROPERTY_READONLY(ChsShaderProgram *, shaderProgram);
		
		PROPERTY( bool, hasVertexColor);
		PROPERTY( float, alpha);

		//texture
		PROPERTY( bool, hasTexture);
		PROPERTY( int, textureCount);

		//light
		
	};

	SYNTHESIZE_READONLY( ChsMaterial, ChsShaderProgram *, shaderProgram );
	
	//color
	SYNTHESIZE( ChsMaterial, bool, hasVertexColor );
	SYNTHESIZE( ChsMaterial, float, alpha );

	//texture
	SYNTHESIZE( ChsMaterial, bool, hasTexture );
	SYNTHESIZE( ChsMaterial, int, textureCount );
	
	//lighting
	
}//namespace
#endif //_CHSMATERIAL_H
