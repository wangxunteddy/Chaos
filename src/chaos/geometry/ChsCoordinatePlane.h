#ifndef _CHS_COORDINATEPLANE_H
#define _CHS_COORDINATEPLANE_H

#include "ChsMesh.h"

namespace Chaos {
	class ChsCoordinatePlane : public ChsMesh {
	public:
		ChsCoordinatePlane( float size, int divide );
		ChsCoordinatePlane( std::string name, float size, int divide );
	};
}


#endif//_CHS_COORDINATEPLANE_H
