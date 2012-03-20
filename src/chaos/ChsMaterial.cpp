#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"

namespace Chaos {
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ) {
		this->_shaderProgram = NULL;
		
		this->_hasVertexColor = false;
		this->shaderUniforms.add( "hasVertexColor", &(this->_hasVertexColor), CHS_SHADER_UNIFORM_1_INT, 1);
		
		this->_hasTexture = false;
		this->shaderUniforms.add( "hasTexture", &(this->_hasTexture), CHS_SHADER_UNIFORM_1_INT, 1);
		
		this->_alpha = 1.0f;
		this->shaderUniforms.add( "alpha", &(this->_alpha), CHS_SHADER_UNIFORM_1_FLOAT, 1);

		this->_textureCount = 1;
		
		this->textures.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ) {
		this->_shaderProgram = NULL;
		this->textures.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::addTexture( ChsTexture2D * texture ){
		this->textures.push_back( texture );
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsShaderProgram * ChsMaterial::apply( ChsShaderProgram * sysProgram ) {
		if( this->_shaderProgram == NULL && sysProgram == NULL )
			return NULL;
		ChsShaderProgram * currentProgram = this->_shaderProgram != NULL ? this->_shaderProgram : sysProgram;
		if( currentProgram != sysProgram )
			currentProgram->use();
    	this->shaderUniforms.apply( currentProgram );
		for( int i = 0; i < this->textures.size(); i++ )
			this->textures[i]->bind();
		return currentProgram;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( void ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate() ) 
        	   printf("Failed to validate program: %d", this->shaderProgram->handle() );
	}
	#endif

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( ChsShaderProgram * program ){
		this->_shaderProgram = program;
	}
	
}//namespace
