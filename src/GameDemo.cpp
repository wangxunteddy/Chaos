#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
//--------------------------------------------------------------------------------------------------
using namespace Chaos;

GameDemo game;

ChsEntity * cube;

//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedEntityManager();
	cube = resMgr->getEntity( "cube" );
	this->render()->root()->add( "cube", cube );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
