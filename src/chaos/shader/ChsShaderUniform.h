#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H

#include <string>
#include <vector>
#include <map>
#include <boost/any.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

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
		std::vector<boost::any> values;
	};
	
	#define UNLOCATED -1

	typedef std::map< std::string, Uniform > UniformVariables;
	
	//----------------------------------------------------------------------------------------------
	class ChsShaderUniform {
	public:
		ChsShaderUniform( void );
		~ChsShaderUniform( void );
		void reset( void );
		void apply( ChsShaderProgram * program );
		void add( std::string name, const void * varAddr, ChsShaderUniformDataType type, unsigned int count ); 
		template<typename T> void add( std::string name, ChsShaderUniformDataType type, T * values );
	 private:
		bool isExist( std::string name );
		
		ChsShaderProgram * program;
		UniformVariables uniformVariables;
	};
	
	//----------------------------------------------------------------------------------------------
	template<typename T>
	void ChsShaderUniform::add( std::string name, ChsShaderUniformDataType type, T * values ){
		if( this->isExist( name ) )
			return;//already in list, do nothing
		unsigned int count = type / 2 + 1;
		//leave location with -1
		Uniform uniform = { type, count, UNLOCATED, NULL };
		for( int i = 0; i < count; i++ )
			uniform.values += values[i];
		//just add to list,
		insert( this->uniformVariables )( name, uniform );
	}

}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
