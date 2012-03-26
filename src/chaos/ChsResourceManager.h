#ifndef _CHS_RESOURCEMANAGER_H
#define _CHS_RESOURCEMANAGER_H

//--------------------------------------------------------------------------------------------------
#include "ChsSingleton.h"
#include "ChsEntityManager.h"
#include "ChsTextureManager.h"
#include "ChsModelManager.h"
#include "shader/ChsShaderManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsResourceManager :	public ChsSingleton< ChsResourceManager >,
								public ChsShaderManager,
								public ChsEntityManager,
								public ChsTextureManager,
								public ChsModelManager
	{
	public:
		void purge( void );
	};
	//----------------------------------------------------------------------------------------------

}

#endif//_CHS_RESOURCEMANAGER_H
