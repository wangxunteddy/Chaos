#include "ChsGameBase.h"
#include "ChsRenderNode.h"
#include "ChsEngine.h"
#include "ChsRenderSystem.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsGameBase::ChsGameBase( void ) : _renderer( NULL ){
		this->_engine = ChsEngine::sharedInstance();
		this->_engine->game( this );
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsGameBase::renderer( void ) {
		return this->_renderer ? this->_renderer : this->_renderer = this->engine()->renderSystem();
	}
	//----------------------------------------------------------------------------------------------

}
