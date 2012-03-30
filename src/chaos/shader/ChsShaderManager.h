#ifndef _CHS_SHADERMANAGER_H
#define _CHS_SHADERMANAGER_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "ChsManagerWithCache.h"

namespace Chaos {
	class ChsShader;
	class ChsVertexShader;
	class ChsFragmentShader;
	class ChsShaderProgram;
	//----------------------------------------------------------------------------------------------
	class ChsShaderManager : public ChsManagerWithCache< ChsShader >{
	public:
		boost::shared_ptr<ChsShaderProgram> getShaderProgram( const std::string & vertexShaderName, const std::string & fragmentShaderName );
	private:
		template < typename ShaderType >
		boost::shared_ptr<ShaderType> getShader( const std::string & name );
		boost::shared_ptr<ChsVertexShader> getVertexShader( const std::string & name );
		boost::shared_ptr<ChsFragmentShader> getFragmentShader( const std::string & name );
	};

	//----------------------------------------------------------------------------------------------
}//namespace
#endif//_CHS_SHADERMANAGER_H
