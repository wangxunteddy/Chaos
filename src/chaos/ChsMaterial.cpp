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
		this->uniformVariables.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ){
		this->uniformVariables.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::apply( void ) {
    	this->updateUniforms();
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
        	   printf("Failed to validate program: %d", this->shaderProgram->getHandle( ) );
	}
	#endif

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( ChsShaderProgram * program ){
		this->_shaderProgram = program;
		this->connectUniform( "hasVertexColor", &this->_hasVertexColor, CHS_UNIFORM_1_INT, 1);
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsMaterial::updateUniforms( void ){
		UniformVariables::iterator iter = this->uniformVariables.begin();
		UniformVariables::iterator end = this->uniformVariables.end();
		for( ; iter != end; iter++ ){
			Uniform uniform = iter->second;
			switch (uniform.type) {
				case CHS_UNIFORM_MAT2:
					glUniformMatrix2fv(uniform.location, uniform.count, false, (const GLfloat*)uniform.varAddr);
					break;
				case CHS_UNIFORM_MAT3:
					glUniformMatrix3fv(uniform.location, uniform.count, false, (const GLfloat*)uniform.varAddr);
					break;
				case CHS_UNIFORM_MAT4:
					glUniformMatrix4fv(uniform.location, uniform.count, false, (const GLfloat*)uniform.varAddr);
					break;
				default:
					GLsizei count = uniform.count * (uniform.type/2+1);
					if(uniform.type%2)
						glUniform1iv(uniform.location,count,(const GLint*)uniform.varAddr);
					else
						glUniform1fv(uniform.location,count,(const GLfloat*)uniform.varAddr);
					break;
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsMaterial::connectUniform( std::string name, void * varAddr, ChsUniformDataType type, size_t count ){
		GLint location = this->_shaderProgram->getUniformLocation(name.c_str());
		if(location<0)
			return;// there has no uniform with that name in program
		Uniform uniform = { type, count, location, varAddr };
		uniformVariables.insert( std::make_pair( name, uniform));
				
	}

//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
