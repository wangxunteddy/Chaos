#ifndef _GAMEDEMO_H
#define _GAMEDEMO_H

#include "chaos/ChsGameBase.h"

class GameDemo : public Chaos::ChsGameBase {
public:
	void onInit( void );
	void onUpdate( void );
	void onShutdown( void );
};

#endif//_GAMEDEMO_H
