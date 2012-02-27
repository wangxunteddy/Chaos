#ifndef _CHS_CUBE_H
#define _CHS_CUBE_H

#include "ChsMesh.h"

namespace Chaos {
	
	class ChsCube : public ChsMesh {
	public:
		ChsCube( float w, float h, float d);
	private:
		float w,h,d;
	};
}

#endif//_CHS_CUBE_H
