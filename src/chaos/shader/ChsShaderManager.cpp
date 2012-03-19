#include "ChsShaderManager.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"

namespace Chaos{
	//----------------------------------------------------------------------------------------------
	template < typename ShaderType > ShaderType * ChsShaderManager::getShader( const std::string name ) {
    	if( name.empty() )
        	return NULL;
    
    	if( this->cache.find( name ) != this->cache.end() )
        	return ( ShaderType * )this->cache[name]; //cache hit
    
	    //not in cache, so load source from file
    	char * source ;
		ChsFileSystem::sharedInstance()->readFileAsRaw( name.c_str(), &source );
		if( !source )
			return NULL;

	    ShaderType * shader = new ShaderType();
    	if(  !shader->load( source ) ){
			safeDelete( &source );
			safeDelete( &shader );
    	    return NULL;
	    }
		
		safeDelete( &source );
		
		printf( "生成Shader:%s\n", name.c_str() );
    	this->cache.insert( std::make_pair( name, shader ) );
	    return shader;
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
		if( this->cache.find( name ) != this->cache.end() )
        	return ( ChsShaderProgram * )this->cache[name]; //cache hit
		ChsShaderProgram * program = new ChsShaderProgram();
		ChsVertexShader * vs = this->getVertexShader( vertexShaderName );
		assert( vs );
		ChsFragmentShader * fs = this->getFragmentShader( fragmentShaderName );
		assert( fs );
		program->attachShader( vs );
		program->attachShader( fs );
		printf( "生成ShaderProgram:%s\n", name.c_str() );
    	this->cache.insert( std::make_pair( name, program ) );
		return program;
	}

}//namespace
