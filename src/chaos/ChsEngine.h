#ifndef _CHS_ENGINE_H
#define _CHS_ENGINE_H

#include <boost/noncopyable.hpp>
#include "ChsMacro.h"
#include "ChsSingleton.h"

namespace Chaos {

	class ChsRenderSystem;
	class ChsGameBase;
	
	class ChsEngine : public ChsSingleton<ChsEngine>, boost::noncopyable {
	public:
		ChsEngine();
		~ChsEngine();
		
		void start( void );
		void run( void );
		void shutdown( void );
		
		PROPERTY_READONLY( ChsRenderSystem *, renderSystem );
		PROPERTY( ChsGameBase *, game );
	};

	SYNTHESIZE_READONLY( ChsEngine, ChsRenderSystem *, renderSystem )
	SYNTHESIZE( ChsEngine, ChsGameBase *, game )

}

#endif//_CHS_ENGINE_H
