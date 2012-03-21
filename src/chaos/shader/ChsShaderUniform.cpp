#include "ChsShaderUniform.h"
#include "ChsShaderProgram.h"
#include <boost/foreach.hpp>
namespace Chaos {
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
	void setUniformWithPtr( const Uniform & uniform );
	void setUniformWithPtr( const Uniform & uniform ){
		switch ( uniform.type ){
			case CHS_SHADER_UNIFORM_MAT2:
				glUniformMatrix2fv( uniform.location, uniform.count, false, ( const GLfloat * )uniform.varAddr );
				break;
			case CHS_SHADER_UNIFORM_MAT3:
				glUniformMatrix3fv( uniform.location, uniform.count, false, ( const GLfloat * )uniform.varAddr );
				break;
			case CHS_SHADER_UNIFORM_MAT4:
				glUniformMatrix4fv( uniform.location, uniform.count, false, ( const GLfloat * )uniform.varAddr );
				break;
			default:
				//vec2 equ float * 2, vec4 equ float * 4, int3 equ int * 3 ....etc..
				GLsizei count = uniform.count * ( uniform.type / 2 + 1 );
				if( uniform.type % 2 )
					glUniform1iv( uniform.location, count, ( const GLint * )uniform.varAddr );
				else
					glUniform1fv( uniform.location, count,(const GLfloat * )uniform.varAddr );
				break;
		}
	}
	//----------------------------------------------------------------------------------------------
	void setUniformWithValues( const Uniform & uniform );
	void setUniformWithValues( const Uniform & uniform ){
		switch ( uniform.type ){
			case CHS_SHADER_UNIFORM_1_FLOAT:
				glUniform1f( uniform.location, boost::any_cast<GLfloat>(uniform.values[0]));
				break;
			case CHS_SHADER_UNIFORM_1_INT:
				glUniform1i( uniform.location, boost::any_cast<GLint>(uniform.values[0]) );
				break;
			case CHS_SHADER_UNIFORM_VEC2_FLOAT:
				glUniform2f( uniform.location,
							boost::any_cast<GLfloat>(uniform.values[0]),
							boost::any_cast<GLfloat>(uniform.values[1]) );
				break;
			case CHS_SHADER_UNIFORM_VEC2_INT:
				glUniform2i( uniform.location,
							boost::any_cast<GLint>(uniform.values[0]),
							boost::any_cast<GLint>(uniform.values[1]) );
				break;
			case CHS_SHADER_UNIFORM_VEC3_FLOAT:
				glUniform3f( uniform.location,
							boost::any_cast<GLfloat>(uniform.values[0]),
							boost::any_cast<GLfloat>(uniform.values[1]),
							boost::any_cast<GLfloat>(uniform.values[2]) );
				break;
			case CHS_SHADER_UNIFORM_VEC3_INT:
				glUniform3i( uniform.location,
							boost::any_cast<GLint>(uniform.values[0]),
							boost::any_cast<GLint>(uniform.values[1]),
							boost::any_cast<GLint>(uniform.values[2]) );
				break;
			case CHS_SHADER_UNIFORM_VEC4_FLOAT:
				glUniform4f( uniform.location,
							boost::any_cast<GLfloat>(uniform.values[0]),
							boost::any_cast<GLfloat>(uniform.values[1]),
							boost::any_cast<GLfloat>(uniform.values[2]),
							boost::any_cast<GLfloat>(uniform.values[3]) );
				break;
			case CHS_SHADER_UNIFORM_VEC4_INT:
				glUniform4i( uniform.location,
							boost::any_cast<GLint>(uniform.values[0]),
							boost::any_cast<GLint>(uniform.values[1]),
							boost::any_cast<GLint>(uniform.values[2]),
							boost::any_cast<GLint>(uniform.values[3]) );
				break;
		}
	}
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::apply ( ChsShaderProgram * program ){
		if( program == NULL )
			return;
		
		bool needUpdateLocation = false;
		if( this->program != program ){
			needUpdateLocation = true;
			this->program = program;
		}

		std::pair<std::string, Uniform> p;
		BOOST_FOREACH( p, this->uniformVariables ){
			std::string name = p.first;
			Uniform uniform = p.second;
			if( uniform.location == UNLOCATED || needUpdateLocation ) {
				//looking for uniform in program
				GLint location = program->getUniformLocation(name.c_str());
				if( location < 0 )
					continue;//no uniform named that in program, process next
				uniform.location = location;//save location
				this->uniformVariables[name] = uniform;
			}
			
			if( uniform.varAddr == NULL )
				setUniformWithValues( uniform );
			else
				setUniformWithPtr( uniform );
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::add( std::string name, const void * varAddr, ChsShaderUniformDataType type, unsigned int count ){
		if( this->isExist( name ) )
			return;
		//leave location with -1
		Uniform uniform = { type, count, UNLOCATED, varAddr };
		//just add to list,
		uniformVariables.insert( std::make_pair( name, uniform ) );
	}

	//----------------------------------------------------------------------------------------------
	bool ChsShaderUniform::isExist( std::string name ){
		return uniformVariables.find( name ) != uniformVariables.end();
	}
}
