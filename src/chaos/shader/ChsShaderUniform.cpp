#include "ChsShaderUniform.h"
#include "ChsShaderProgram.h"

namespace Chaos {
	
	#define UNLOCATED -1
	
	//----------------------------------------------------------------------------------------------
	ChsShaderUniform::ChsShaderUniform( void ){
		this->reset();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsShaderUniform::~ChsShaderUniform( void ){
		this->reset();
	}

	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::reset( void ){
		this->uniformVariables.clear();
		this->program = NULL;
	}
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::apply ( ChsShaderProgram * program ){
		if( program == NULL )
			return;
		
		bool needUpdateLocation = false;
		if(this->program != program ){
			needUpdateLocation = true;
			this->program = program;
		}

		UniformVariables::iterator iter = this->uniformVariables.begin();
		UniformVariables::iterator end = this->uniformVariables.end();
		for( ; iter != end; iter++ ){
			std::string name = iter->first;
			Uniform uniform = iter->second;
			
			if( uniform.location == UNLOCATED || needUpdateLocation ) {
				//looking for uniform in program
				GLint location = program->getUniformLocation(name.c_str());
				if( location < 0 )
					continue;//no uniform named that in program, process next
				uniform.location = location;//save location
				uniformVariables[name] = uniform;
			}
			
			switch ( uniform.type ) {
				case CHS_SHADER_UNIFORM_MAT2:
					glUniformMatrix2fv(uniform.location, uniform.count, false, (const GLfloat*)uniform.varAddr);
					break;
				case CHS_SHADER_UNIFORM_MAT3:
					glUniformMatrix3fv(uniform.location, uniform.count, false, (const GLfloat*)uniform.varAddr);
					break;
				case CHS_SHADER_UNIFORM_MAT4:
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
	void ChsShaderUniform::add( std::string name, void * varAddr, ChsShaderUniformDataType type, size_t count ){
		if( uniformVariables.find( name ) != uniformVariables.end() )
			return;//already in list, do nothing
		//leave location with -1
		Uniform uniform = { type, count, UNLOCATED, varAddr };
		//just add to list,
		uniformVariables.insert( std::make_pair( name, uniform));
	}
}
