#include "ChsResourceManager.h"

namespace Chaos{

	//----------------------------------------------------------------------------------------------
	void ChsResourceManager::purge( void ){
		ChsEntityManager::purge();
		ChsShaderManager::purge();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsEntityManager * ChsResourceManager::sharedEntityManager( void ) {
		return ( ChsEntityManager * )ChsResourceManager::sharedInstance();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsShaderManager * ChsResourceManager::sharedShaderManager( void ) {
		return ( ChsShaderManager * )ChsResourceManager::sharedInstance();
	}

	//----------------------------------------------------------------------------------------------
	
}