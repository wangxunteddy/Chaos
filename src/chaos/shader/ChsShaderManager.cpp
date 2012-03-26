#include <boost/assign.hpp>
using namespace boost::assign;
#include <boost/scoped_array.hpp>

#include "ChsShaderManager.h"
#include "ChsShader.h"
#include "ChsShaderProgram.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"

namespace Chaos{
	//----------------------------------------------------------------------------------------------
	template < typename ShaderType >
	boost::shared_ptr<ShaderType> ChsShaderManager::getShader( const std::string & name ) {
		boost::shared_ptr<ShaderType> shader( (ShaderType*)this->getFromCacheWithValue( name ) );
		if( !shader ){
			//not in cache, so load source from file
			char * source ;
			ChsFileSystem::sharedInstance()->readFileAsUTF8( name.c_str(), &source );
			if( source ){
				boost::scoped_array<char> sourcePtr( source );
				shader = boost::shared_ptr<ShaderType>( new ShaderType() );
				if( shader->load( source ) ){
					printf( "生成Shader:%s\n", name.c_str() );
					insert( this->cache )( name, shader );
				}
			}
		}
	    return shader;
	}

	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsVertexShader> ChsShaderManager::getVertexShader( const std::string & name ){
    	return this->getShader< ChsVertexShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsFragmentShader> ChsShaderManager::getFragmentShader( const std::string & name ){
    	return this->getShader< ChsFragmentShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsShaderProgram> ChsShaderManager::getShaderProgram( const std::string & vsName,
															 const std::string & fsName ){
		std::string name  = vsName + "+" + fsName;
		boost::shared_ptr<ChsShaderProgram> program( (ChsShaderProgram*)this->getFromCacheWithValue( name ) );
		if( !program ){
			program.reset( new ChsShaderProgram() );
			boost::shared_ptr<ChsVertexShader> vs = this->getVertexShader( vsName );
			assert( vs );
			boost::shared_ptr<ChsFragmentShader> fs = this->getFragmentShader( fsName );
			assert( fs );
			program->attachShader( vs );
			program->attachShader( fs );
			printf( "生成ShaderProgram:%s\n", name.c_str() );
			insert( this->cache )( name, program );
		}
		return program;
	}

}//namespace
