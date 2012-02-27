#include "ChsEngine.h"
#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsGameBase.h"
#include "ChsResourceManager.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsEngine::ChsEngine( void ) : _renderSystem(NULL),_game(NULL) {
	}
	
	//----------------------------------------------------------------------------------------------
	ChsEngine::~ChsEngine( void ){
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsEngine::start( void ){
		//init rendersystem
		this->_renderSystem = ChsRenderFactory::create();
		//init game
		assert(this->game());
		this->game()->onInit();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsEngine::run( void ){
		this->game()->onUpdate();
		this->renderSystem()->update();
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsEngine::shutdown( void ){
		this->game()->onShutdown();
		this->game(NULL);
		ChsRenderFactory::shutdown();
		ChsResourceManager::sharedInstance()->purge();
	}
	//----------------------------------------------------------------------------------------------
}
