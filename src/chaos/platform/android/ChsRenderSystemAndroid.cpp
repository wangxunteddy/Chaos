#include "ChsRenderSystemAndroid.h"

namespace Chaos{
	
	void ChsRenderSystemAndroid::initContext( void ) {
		glBindVertexArrayOES    = ( PFNGLBINDVERTEXARRAYOESPROC    ) eglGetProcAddress("glBindVertexArrayOES"  );
		glGenVertexArraysOES    = ( PFNGLGENVERTEXARRAYSOESPROC    ) eglGetProcAddress("glGenVertexArraysOES"  );
		glDeleteVertexArraysOES = ( PFNGLDELETEVERTEXARRAYSOESPROC ) eglGetProcAddress("glDeleteVertexArraysOES");
	}
}
