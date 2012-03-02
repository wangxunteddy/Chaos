#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H

#include <string>
#include <map>

#include "ChsDefine.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsShaderProgram;
	
	struct Uniform {
		int type;
		int count;
		int location;
		void * varAddr;
	};
	
	typedef std::map< std::string, Uniform > UniformVariables;
	
	//----------------------------------------------------------------------------------------------
	class ChsShaderUniform {
	public:
		ChsShaderUniform( void );
		~ChsShaderUniform( void );
		void update ( void );
		void add( std::string name, void * varAddr, ChsShaderUniformDataType type, size_t count ); 
		void attachShader( ChsShaderProgram * shaderProgram );
	 private:
		ChsShaderProgram * shaderProgram;
		UniformVariables uniformVariables;
		bool needUpdateLocation;
	};
	//----------------------------------------------------------------------------------------------
	
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
