#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsShaderUniformSet.h"

namespace Chaos{
	//----------------------------------------------------------------------------------------------
	ChsShaderUniformSet::ChsShaderUniformSet( void ){
		this->reset();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsShaderUniformSet::~ChsShaderUniformSet( void ){
		this->reset();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::reset( void ){
		this->uniforms.clear();
		this->program = NULL;
	}	
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::apply ( ChsShaderProgram * program ){
		if( program == NULL )
			return;
		
		bool needUpdateLocation = false;
		if( this->program != program ){
			needUpdateLocation = true;
			this->program = program;
		}
		
		std::pair<std::string, boost::shared_ptr<ChsShaderUniform> > p;
		BOOST_FOREACH( p, this->uniforms )
			p.second->apply( program, needUpdateLocation );
	}
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::add( std::string name, ChsShaderUniformDataType type, unsigned int count, void * varAddr ){
		if( this->isExist( name ) )
			return;
		boost::shared_ptr<ChsShaderUniform> uniform( new ChsShaderUniform() );
		uniform->init( name, type, count, varAddr );
		insert( this->uniforms )( name, uniform );
	}
}
