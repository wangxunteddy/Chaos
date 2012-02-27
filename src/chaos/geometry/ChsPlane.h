#ifndef _CHS_PLANE_H
#define _CHS_PLANE_H

#include "ChsMesh.h"

namespace Chaos {
	
	struct ChsPlaneVertex{
		float x;
		float y;
		float r;
		float g;
		float b;
		float a;
	};
	class ChsPlane : public ChsMesh {
	public:
		ChsPlane( float w, float h );
	private:
		float w,h;
		ChsPlaneVertex vertices[4];
	};
}

#endif //_CHS_PLANE_H
