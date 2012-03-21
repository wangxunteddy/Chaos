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
		unsigned int count;
		int location;
		const void * varAddr;
	};
	
	typedef std::map< std::string, Uniform > UniformVariables;
	
	//----------------------------------------------------------------------------------------------
	class ChsShaderUniform {
	public:
		ChsShaderUniform( void );
		~ChsShaderUniform( void );
		void reset( void );
		void apply( ChsShaderProgram * program );
		void add( std::string name, const void * varAddr, ChsShaderUniformDataType type, unsigned int count ); 
	 private:
		ChsShaderProgram * program;
		UniformVariables uniformVariables;
	};
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
