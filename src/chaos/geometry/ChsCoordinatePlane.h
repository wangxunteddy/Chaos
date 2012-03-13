#ifndef _CHS_COORDINATEPLANE_H
#define _CHS_COORDINATEPLANE_H

#include "ChsMesh.h"

namespace Chaos {
	class ChsCoordinatePlane : public ChsMesh {
	public:
		ChsCoordinatePlane( float size, int divide );
		void setMaterial( void );
	};
}


#endif//_CHS_COORDINATEPLANE_H
