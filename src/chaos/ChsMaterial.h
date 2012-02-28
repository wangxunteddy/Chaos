#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <map>
#include <string>
#include "ChsMacro.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsShaderProgram;

	struct Uniform{
		int type;
		int count;
		int location;
		void * varAddr;
	};
	
	typedef std::map<std::string, Uniform> UniformVariables;
	
	enum ChsUniformDataType {
		CHS_UNIFORM_1_FLOAT,
		CHS_UNIFORM_1_INT,
		CHS_UNIFORM_VEC2_FLOAT,
		CHS_UNIFORM_VEC2_INT,
		CHS_UNIFORM_VEC3_FLOAT,
		CHS_UNIFORM_VEC3_INT,
		CHS_UNIFORM_VEC4_FLOAT,
		CHS_UNIFORM_VEC4_INT,
		CHS_UNIFORM_MAT2,
		CHS_UNIFORM_MAT3,
		CHS_UNIFORM_MAT4,
	};

	//----------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    	ChsMaterial( void );
	    ~ChsMaterial( void );
    	void apply( void );
	    void setShader( ChsShaderProgram * program );
		void updateUniforms( void );
		void connectUniform( std::string name, void * varAddr, ChsUniformDataType type, size_t count );
	private:
		UniformVariables uniformVariables;
		
		PROPERTY_READONLY(ChsShaderProgram *, shaderProgram);
		PROPERTY( bool, hasVertexColor);
		PROPERTY( bool, hasTexture);
		PROPERTY( int, textureCount);
		
	};

	SYNTHESIZE_READONLY( ChsMaterial, ChsShaderProgram *, shaderProgram );
	SYNTHESIZE( ChsMaterial, bool, hasVertexColor );
	SYNTHESIZE( ChsMaterial, bool, hasTexture );
	SYNTHESIZE( ChsMaterial, int, textureCount );
	
}//namespace
#endif //_CHSMATERIAL_H
