#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"

namespace Chaos {

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ){
		this->shaderProgram = NULL;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial(){
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::apply( ) {
    	if( this->shaderProgram )
        	this->shaderProgram->use( );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate( ) ) 
        	   printf("Failed to validate program: %d", this->shaderProgram->getHandle( ) );
	}
	#endif

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( const std::string vertxShaderName, const std::string fragmentShaderName ){
		this->shaderProgram = ChsResourceManager::sharedInstance()->getShaderProgram(vertxShaderName, fragmentShaderName);
	}
	
//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
