#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H

#include <string>
#include <map>

#include "ChsDefine.h"
#include "ChsMacro.h"

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
		void apply ( ChsShaderProgram * program );
		void add( std::string name, void * varAddr, ChsShaderUniformDataType type, size_t count ); 
	 private:
		ChsShaderProgram * program;
		UniformVariables uniformVariables;
		
		void init( void );
	};
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
