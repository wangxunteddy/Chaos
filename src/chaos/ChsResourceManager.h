#ifndef _CHS_RESOURCEMANAGER_H
#define _CHS_RESOURCEMANAGER_H

//--------------------------------------------------------------------------------------------------
#include "ChsSingleton.h"
#include "ChsEntityManager.h"
#include "shader/ChsShaderManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsResourceManager :	public ChsSingleton< ChsResourceManager >,
								public ChsShaderManager,
								public ChsEntityManager {
	public:
		void purge( void );
		static ChsEntityManager * sharedEntityManager( void );
		static ChsShaderManager * sharedShaderManager( void );
	};
	//----------------------------------------------------------------------------------------------

}

#endif//_CHS_RESOURCEMANAGER_H
