#include "ChsShaderUniform.h"
#include "ChsShaderProgram.h"
#include "ChsUtility.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	ChsShaderUniform::ChsShaderUniform( void ) : fValuePtr( NULL ),linkedValuePtr( NULL ){
	}
	//----------------------------------------------------------------------------------------------
	ChsShaderUniform::~ChsShaderUniform( void ){
		safeDeleteArray( &this->fValuePtr );
	}
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::apply( ChsShaderProgram * program, bool needUpdateLocation ){
		if( this->location == UNLOCATED || needUpdateLocation ) {
			//looking for uniform in program
			GLint location = program->getUniformLocation( this->name.c_str() );
			if( location < 0 )
				return;//no uniform named that in program, process next
			this->location = location;//save location, because it is a reference
		}

		void * ptr = this->linkedValuePtr;
		if( !ptr )
			ptr = this->fValuePtr;
		switch ( this->type ){
			case CHS_SHADER_UNIFORM_MAT2:
				glUniformMatrix2fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
			case CHS_SHADER_UNIFORM_MAT3:
				glUniformMatrix3fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
			case CHS_SHADER_UNIFORM_MAT4:
				glUniformMatrix4fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
			default:
				//vec2 equ float * 2, vec4 equ float * 4, int3 equ int * 3 ....etc..
				GLsizei count = this->count * ( this->type / 2 + 1 );
				if( this->type % 2 )
					glUniform1iv( this->location, count, (const GLint*)ptr );
				else
					glUniform1fv( this->location, count, (const GLfloat*)ptr );
				break;
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::init( std::string name, ChsShaderUniformDataType type, int count, void * varAddr ){
		this->location = UNLOCATED;
		this->name = name;
		this->type = type;
		this->count = count;
		if( varAddr ){
			this->linkedValuePtr = varAddr;
		}
		else{
			switch ( this->type ){
				case CHS_SHADER_UNIFORM_MAT2:
					this->fValuePtr = new float[ this->count * 4 ];
					break;
				case CHS_SHADER_UNIFORM_MAT3:
					this->fValuePtr = new float[ this->count * 9 ];
					break;
				case CHS_SHADER_UNIFORM_MAT4:
					this->fValuePtr = new float[ this->count * 16 ];
					break;
				default:
					GLsizei size = this->count * ( this->type / 2 + 1 );
					if( this->type % 2 )
						this->iValuePtr = new int[size];
					else
						this->fValuePtr = new float[size];
					break;
			}
		}
	}
	//----------------------------------------------------------------------------------------------

}
