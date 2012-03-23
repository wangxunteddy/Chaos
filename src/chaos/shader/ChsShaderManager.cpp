#include "ChsShaderManager.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"
#include <boost/assign.hpp>
using namespace boost::assign;
#include <boost/scoped_array.hpp>

namespace Chaos{
	//----------------------------------------------------------------------------------------------
	template < typename ShaderType > ShaderType * ChsShaderManager::getShader( const std::string name ) {
    	if( name.empty() )
        	return NULL;
		boost::shared_ptr<ShaderType> shaderPtr( (ShaderType*)this->getFromCacheWithValue( name ) );
		if( !shaderPtr ){
			//not in cache, so load source from file
			char * source ;
			ChsFileSystem::sharedInstance()->readFileAsUTF8( name.c_str(), &source );
			if( !source )
				return NULL;
			boost::scoped_array<char> sourcePtr( source );			
			shaderPtr = boost::shared_ptr<ShaderType>( new ShaderType() );
			if(  !shaderPtr->load( source ) ){
				return NULL;
			}
			printf( "生成Shader:%s\n", name.c_str() );
			insert( this->cache )( name, shaderPtr );
		}
	    return shaderPtr.get();
	}

	//----------------------------------------------------------------------------------------------
	ChsVertexShader * ChsShaderManager::getVertexShader( const std::string name ){
    	return this->getShader< ChsVertexShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	ChsFragmentShader * ChsShaderManager::getFragmentShader( const std::string name ){
    	return this->getShader< ChsFragmentShader >( name );
	}

	//----------------------------------------------------------------------------------------------
	ChsShaderProgram * ChsShaderManager::getShaderProgram( const std::string vertexShaderName, const std::string fragmentShaderName ){
		std::string name  = vertexShaderName + "+" + fragmentShaderName;
		if( name.empty() )
        	return NULL;
		boost::shared_ptr<ChsShaderProgram> programPtr( (ChsShaderProgram*)this->getFromCacheWithValue( name ) );
		if( !programPtr ){
			programPtr = boost::shared_ptr<ChsShaderProgram>( new ChsShaderProgram() );
			ChsVertexShader * vs = this->getVertexShader( vertexShaderName );
			assert( vs );
			ChsFragmentShader * fs = this->getFragmentShader( fragmentShaderName );
			assert( fs );
			programPtr->attachShader( vs );
			programPtr->attachShader( fs );
			printf( "生成ShaderProgram:%s\n", name.c_str() );
			insert( this->cache )( name, programPtr );
		}
		return programPtr.get();
	}

}//namespace
