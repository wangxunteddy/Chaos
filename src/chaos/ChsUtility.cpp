#include "ChsUtility.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	size_t getGLDataTypeSize( int type ){
		switch (type) {
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
				return sizeof( char );
			case GL_INT:
			case GL_UNSIGNED_INT:
				return sizeof( int );
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
				return sizeof( short );
			case GL_FLOAT:
				return sizeof( float );
			default:
				return -1;//unsupported type
			}
	}
	
	//----------------------------------------------------------------------------------------------
}//namespace
