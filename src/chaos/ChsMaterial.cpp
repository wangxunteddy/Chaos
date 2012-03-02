#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"

namespace Chaos {
	

	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ){
		this->_shaderProgram = NULL;
		this->_hasVertexColor = false;
		this->_hasTexture = false;
		this->_textureCount = 1;
		this->_alpha = 1.0f;
		this->shaderUniforms.add( "hasVertexColor", &this->_hasVertexColor, CHS_SHADER_UNIFORM_1_INT, 1);
		this->shaderUniforms.add( "hasTexture", &this->_hasVertexColor, CHS_SHADER_UNIFORM_1_INT, 1);
		this->shaderUniforms.add( "hasTexture", &this->_hasTexture, CHS_SHADER_UNIFORM_1_INT, 1);
		this->shaderUniforms.add( "alpha", &this->_alpha, CHS_SHADER_UNIFORM_1_FLOAT, 1);
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ){
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::apply( void ) {
    	this->shaderUniforms.update();
		if( this->_shaderProgram ){
        	this->_shaderProgram->use();
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate( ) ) 
        	   printf("Failed to validate program: %d", this->shaderProgram->handle( ) );
	}
	#endif

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( ChsShaderProgram * program ){
		this->_shaderProgram = program;
		this->shaderUniforms.attachShader( program );
	}
	
}//namespace
