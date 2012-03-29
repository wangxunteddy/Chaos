#ifndef _CHS_INDEXBUFFER_H
#define _CHS_INDEXBUFFER_H
#pragma once

#include <vector>
#include "ChsMacro.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsIndexBuffer {
	public:
		ChsIndexBuffer( void );
		~ChsIndexBuffer( void );
		void setData( const void * triangles, int count, int type = GL_UNSIGNED_SHORT );
		inline void setData( std::vector<unsigned short> & triangles );
		void draw( void );
	private:
		unsigned int handle;
		int count;
		int type;
		int size;
		char * triangles;
		bool isNeedUpdate;
		
		PROPERTY_WRITEONLY( int, mode );
	};

	SYNTHESIZE_WRITEONLY( ChsIndexBuffer, int, mode );
	
	inline void ChsIndexBuffer::setData( std::vector<unsigned short> & triangles ){
		this->setData( triangles.data(), triangles.size() );
	}
	
//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespaces
#endif//_CHS_INDEXBUFFER_H
