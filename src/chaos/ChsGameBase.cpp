#include "ChsGameBase.h"
#include "ChsRenderNode.h"
#include "ChsEngine.h"
#include "ChsRenderSystem.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsGameBase::ChsGameBase( void ){
		this->_engine = ChsEngine::sharedInstance();
		this->_engine->game( this );
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsGameBase::render( void ) {
		if( this->_render )
			return this->_render;
		else
			return this->_render = this->_engine->renderSystem();
	}
	//----------------------------------------------------------------------------------------------

}
