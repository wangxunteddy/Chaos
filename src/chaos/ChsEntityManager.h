#ifndef _CHS_ENTITYMANAGER_H
#define _CHS_ENTITYMANAGER_H

#include "ChsManagerWithCache.h"
#include "ChsEntity.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsEntityManager : public ChsManagerWithCache< std::string, ChsEntity > {
	private:
		ChsEntity * getEntityFromCache( std::string entityName );
	public:
		ChsEntity * getEntity( std::string entityName );
		
		ChsEntity * getEntityWithModel( std::string entityName,
										std::string modelName );
		
		ChsEntity * getEntityWithModelAndAnimation( std::string entityName, 
												    std::string modelName,
													std::string animationName );

		void releaseEntity( std::string entityName );
	};
	
	//----------------------------------------------------------------------------------------------
	
}

#endif//_CHS_ENTITYMANAGER_H
