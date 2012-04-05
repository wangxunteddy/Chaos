#ifndef _CHS_SHADERUNIFORMSET_H
#define _CHS_SHADERUNIFORMSET_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "ChsShaderUniform.h"

namespace Chaos {

	class ChsShaderUniformSet{
	public:
		ChsShaderUniformSet( void );
		~ChsShaderUniformSet( void );
		void reset( void );
		void apply( ChsShaderProgram * program );
		void add( std::string name, ChsShaderUniformDataType type, unsigned int count, void * varAddr = NULL ); 
		template<typename T> void set( std::string name, T values );
		template<typename T> T get( std::string name );
	private:
		inline bool isExist( std::string name );
		ChsShaderProgram * program;
		std::map< std::string, boost::shared_ptr<ChsShaderUniform> > uniforms;
	};
	//----------------------------------------------------------------------------------------------
	inline bool ChsShaderUniformSet::isExist( std::string name ){
		return uniforms.find( name ) != uniforms.end();
	}

	//----------------------------------------------------------------------------------------------
	template<typename T>
	void ChsShaderUniformSet::set( std::string name, T values ){
		auto iter = this->uniforms.find( name );
		if( iter == this->uniforms.end() )
			return;
		iter->second->set( values );
	}
	
	//----------------------------------------------------------------------------------------------
	template<typename T> T ChsShaderUniformSet::get( std::string name ){
		auto iter = this->uniforms.find( name );
		if( iter == this->uniforms.end() )
			return 0;
		return iter->second->get<T>();
	}
}


#endif//_CHS_SHADERUNIFORMSET_H
