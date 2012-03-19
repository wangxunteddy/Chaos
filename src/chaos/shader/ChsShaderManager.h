#ifndef _CHS_SHADERMANAGER_H
#define _CHS_SHADERMANAGER_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsManagerWithCache.h"
#include "ChsShaderProgram.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsShaderManager : public ChsManagerWithCache< std::string, ChsShader >{
	public:
		ChsVertexShader * getVertexShader( const std::string name );
		ChsFragmentShader * getFragmentShader( const std::string name );
		ChsShaderProgram * getShaderProgram( const std::string vertexShaderName, const std::string fragmentShaderName );
	private:
		template < typename ShaderType > ShaderType * getShader( const std::string name );
	};

	//----------------------------------------------------------------------------------------------
}//namespace
#endif//_CHS_SHADERMANAGER_H
