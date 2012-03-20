#include "ChsResourceManager.h"

namespace Chaos{

	//----------------------------------------------------------------------------------------------
	void ChsResourceManager::purge( void ){
		ChsEntityManager::purge();
		ChsShaderManager::purge();
		ChsTextureManager::purge();
	}

}