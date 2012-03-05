#ifndef _CHS_PLANE_H
#define _CHS_PLANE_H

#include "ChsMesh.h"

namespace Chaos {
	
	struct ChsPlaneVertex{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
		float a;
	};
	class ChsPlane : public ChsMesh {
	public:
		ChsPlane( std::string name, float w, float h );
		ChsPlane( float w, float h );
	private:
		float w,h;
		ChsPlaneVertex vertices[4];
	};
}

#endif //_CHS_PLANE_H
