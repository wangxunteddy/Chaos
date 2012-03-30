#include <boost/scoped_array.hpp>
#include <boost/assign.hpp>
using namespace boost;
using namespace boost::assign;

#include "ChsShaderManager.h"
#include "ChsShader.h"
#include "ChsShaderProgram.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"

namespace Chaos{
	//----------------------------------------------------------------------------------------------
	template < typename ShaderType >
	shared_ptr<ShaderType> ChsShaderManager::getShader( const std::string & name ) {
		shared_ptr<ShaderType> shader = static_pointer_cast<ShaderType>( this->getFromCache( name ) );
		if( !shader ){
			//not in cache, so load source from file
			char * source ;
			ChsFileSystem::sharedInstance()->readFileAsUTF8( name.c_str(), &source );
			if( source ){
				scoped_array<char> sourcePtr( source );
				shader = shared_ptr<ShaderType>( new ShaderType() );
				if( shader->load( source ) ){
					printf( "生成Shader:%s\n", name.c_str() );
					insert( this->cache )( name, shader );
				}
			}
		}
	    return shader;
	}

	//----------------------------------------------------------------------------------------------
	shared_ptr<ChsVertexShader> ChsShaderManager::getVertexShader( const std::string & name ){
    	return this->getShader< ChsVertexShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	shared_ptr<ChsFragmentShader> ChsShaderManager::getFragmentShader( const std::string & name ){
    	return this->getShader< ChsFragmentShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	shared_ptr<ChsShaderProgram> ChsShaderManager::getShaderProgram( const std::string & vsName,
															 const std::string & fsName ){
		std::string name  = vsName + "+" + fsName;
		shared_ptr<ChsShaderProgram> program = boost::static_pointer_cast<ChsShaderProgram>( this->getFromCache( name ) );
		if( !program ){
			program.reset( new ChsShaderProgram() );
			shared_ptr<ChsVertexShader> vs = this->getShader<ChsVertexShader>( vsName );
			assert( vs );
			shared_ptr<ChsFragmentShader> fs = this->getShader<ChsFragmentShader>( fsName );
			assert( fs );
			program->attachShader( vs );
			program->attachShader( fs );
			printf( "生成ShaderProgram:%s\n", name.c_str() );
			insert( this->cache )( name, program );
		}
		return program;
	}

}//namespace
