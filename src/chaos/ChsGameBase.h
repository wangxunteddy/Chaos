#ifndef _CHS_GAMEBASE_H
#define _CHS_GAMEBASE_H

#include "ChsMacro.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	class ChsEngine;
	//----------------------------------------------------------------------------------------------
	class ChsGameBase {
	public:
		ChsGameBase( void );
		virtual void onInit( void ) = 0;
		virtual void onUpdate( void ) = 0;
		virtual void onShutdown( void ) = 0;

		PROPERTY_READONLY( ChsRenderSystem *, render );
		PROPERTY_READONLY( ChsEngine *, engine );
	};

	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_GETTER( ChsGameBase, ChsEngine *, engine);
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_GAMEBASE_H
