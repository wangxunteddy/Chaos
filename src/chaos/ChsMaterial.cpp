#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"

namespace Chaos {
	
#define UNLOCATED -1
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ){
		this->_shaderProgram = NULL;
		this->_hasVertexColor = false;
		this->_hasTexture = false;
		this->_textureCount = 1;
		this->_alpha = 1.0f;
		this->uniformVariables.clear();
		this->registerUniform( "hasVertexColor", &this->_hasVertexColor, CHS_UNIFORM_1_INT, 1);
		this->registerUniform( "hasTexture", &this->_hasVertexColor, CHS_UNIFORM_1_INT, 1);
		this->registerUniform( "hasTexture", &this->_hasTexture, CHS_UNIFORM_1_INT, 1);
		this->registerUniform( "alpha", &this->_alpha, CHS_UNIFORM_1_FLOAT, 1);
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
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsMaterial::updateUniforms( void ){
		UniformVariables::iterator iter = this->uniformVariables.begin();
		UniformVariables::iterator end = this->uniformVariables.end();
		for( ; iter != end; iter++ ){
			std::string name = iter->first;
			Uniform uniform = iter->second;
			
			if( uniform.location == UNLOCATED ) {
				//not connect with program location
				//looking for uniform in program
				GLint location = this->_shaderProgram->getUniformLocation(name.c_str());
				if( location < 0 )
					continue;//no uniform named that in program, process next
				
				uniform.location = location;//save location
				uniformVariables[name] = uniform;
			}
			
			switch ( uniform.type ) {
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
					//vec2 equ float * 2, vec4 equ float * 4, int3 equ int * 3 ....etc..
					GLsizei count = uniform.count * (uniform.type/2+1);
					if( uniform.type % 2 )
						glUniform1iv(uniform.location,count,(const GLint*)uniform.varAddr);
					else
						glUniform1fv(uniform.location,count,(const GLfloat*)uniform.varAddr);
					break;
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------	
	void ChsMaterial::registerUniform( std::string name, void * varAddr, ChsUniformDataType type, size_t count ){
		if( uniformVariables.find( name ) != uniformVariables.end() )
			return;//already in list, do nothing
		//leave location with -1
		Uniform uniform = { type, count, UNLOCATED, varAddr };
		//just add to list,
		uniformVariables.insert( std::make_pair( name, uniform));
	}

}//namespace
