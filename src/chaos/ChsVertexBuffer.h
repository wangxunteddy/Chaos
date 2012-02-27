#ifndef _CHS_VERTEXBUFFER_H
#define _CHS_VERTEXBUFFER_H
#pragma once

//--------------------------------------------------------------------------------------------------------------------------------------------
#include <string>
#include <vector>

#include "ChsMacro.h"
#include "ChsUtility.h"

namespace Chaos {
	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsShaderProgram;

	//--------------------------------------------------------------------------------------------------------------------------------------------
	struct ChsAttribUnit{
		int size;
		int count;
		int type;
		bool isNormalized;
		int index;
		int stride;
		int offset;
		std::string  name;
		ChsAttribUnit(int count, int type, bool isNormalized, std::string name ){
			this->count = count;
			this->type = type;
			this->isNormalized = isNormalized;
			this->size = count * getGLDataTypeSize( type );
			this->name = name;
		}
		void bind( ) {
			glVertexAttribPointer( index, count, type, isNormalized, stride, (void *)offset );
			glEnableVertexAttribArray( index );
		}
		void unbind( ) {
			glDisableVertexAttribArray( index );
		}
	};


	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsVertexBuffer {
	public:
		ChsVertexBuffer( void );
		~ChsVertexBuffer( void );
		void bindAttribLocations( const ChsShaderProgram * program );
		void addAttrib( int count, int type, bool isNormalized, std::string name );
		void setData( const void * vertices, int size );
		void preDraw( void );
		void postDraw( void );
		
	private:
		void bindVertexArray( void );
		void unbindVertexArray( void );
		void bindAttribArrays( void );
		void unbindAttribArrays( void );
		void update( void );
		
		std::vector<ChsAttribUnit *> attribs;
		unsigned int vboHandle;
		unsigned int vaoHandle;
		char * vertices;
		int size;
		bool isNeedUpdate;
	};
	
//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_VERTEXBUFFER_H
