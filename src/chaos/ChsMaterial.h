#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <vector>
//#include <string>
#include "ChsDefine.h"
#include "ChsMacro.h"
#include "shader/ChsShaderUniform.h"

namespace Chaos {
	class ChsTexture2D;
	//----------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    	ChsMaterial( void );
	    virtual ~ChsMaterial( void );
    	ChsShaderProgram * apply( ChsShaderProgram * program );
	    void setShader( ChsShaderProgram * program );
		void addTexture( ChsTexture2D * texture );
	private:
		
		std::vector<ChsTexture2D*> textures;
		
		ChsShaderUniform shaderUniforms;
		PROPERTY_READONLY( ChsShaderProgram *, shaderProgram );
		
		PROPERTY( boolean, hasVertexColor );
		PROPERTY( float, alpha );

		//texture
		PROPERTY( boolean, hasTexture );
		PROPERTY( int, textureCount );

		//light

	};

	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY( ChsMaterial, ChsShaderProgram *, shaderProgram );
	
	//color
	SYNTHESIZE( ChsMaterial, boolean, hasVertexColor );
	SYNTHESIZE( ChsMaterial, float, alpha );

	//texture
	SYNTHESIZE( ChsMaterial, boolean, hasTexture );
	SYNTHESIZE( ChsMaterial, int, textureCount );
	
	//lighting
	
}//namespace
#endif //_CHSMATERIAL_H
