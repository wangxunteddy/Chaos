#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H

#include <string>
#include <vector>

#include "ChsDefine.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsShaderProgram;
	#define UNLOCATED -1
	//----------------------------------------------------------------------------------------------
	class ChsShaderUniform {
	public:
		ChsShaderUniform( void );
		~ChsShaderUniform( void );
		void init( std::string name, ChsShaderUniformDataType type, int count, void * varAddr = NULL );
		void apply( ChsShaderProgram * program, bool needUpdateLocation );
	//	void set( const void * value );
	//	template<typename T> T * get( void );
		template<typename T> void set( T value );
		template<typename T> T get( void );
	private:
		std::string name;
		int type;
		unsigned int count;
		int location;
		void * linkedValuePtr;
		union{
			float * fValuePtr;
			int * iValuePtr;
		};
	};
	
	//----------------------------------------------------------------------------------------------
	template<typename T>
	void ChsShaderUniform::set( T value ){
		if( this->fValuePtr ){
			if( this->type == CHS_SHADER_UNIFORM_1_INT )
				*( this->iValuePtr ) = value;
			else if( this->type == CHS_SHADER_UNIFORM_1_FLOAT )
				*( this->fValuePtr ) = value;
		}
	}
	//----------------------------------------------------------------------------------------------
	template<typename T>
	T ChsShaderUniform::get( void ){
		if( this->type == CHS_SHADER_UNIFORM_1_INT )
			return *( this->iValuePtr );
		else if( this->type == CHS_SHADER_UNIFORM_1_FLOAT )
			return *( this->fValuePtr );
		else
			return 0;
	}
#if 0
	//----------------------------------------------------------------------------------------------
	void ChsShaderUniform::set( const void  * value ){
		if( this->isExternal )
			return;
		int size = this->count * sizeof(float);
		switch ( this->type ){
			case CHS_SHADER_UNIFORM_MAT2:
				memcpy( this->valuePtr, value, size * 4 );
				break;
			case CHS_SHADER_UNIFORM_MAT3:
				memcpy( this->valuePtr, value, size * 9 );
				break;
			case CHS_SHADER_UNIFORM_MAT4:
				memcpy( this->valuePtr, value, size * 16 );
				break;
			default:
				size = this->count * ( this->type / 2 + 1 );
				memcpy( this->valuePtr, value, size);
				break;
		}
	}

	//----------------------------------------------------------------------------------------------
	template<typename T>
	T * ChsShaderUniform::get( void ){
		return static_cast<T>( this->valuePtr );
	}
	
	
	
	
#endif
}
//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
