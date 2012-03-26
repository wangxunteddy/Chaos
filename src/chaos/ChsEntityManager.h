#ifndef _CHS_ENTITYMANAGER_H
#define _CHS_ENTITYMANAGER_H

#include "ChsManagerWithCache.h"

namespace Chaos {
	class ChsEntity;
	//----------------------------------------------------------------------------------------------
	class ChsEntityManager : public ChsManagerWithCache< ChsEntity > {
	public:
		boost::shared_ptr<ChsEntity> getEntity( std::string entityName );
		
		boost::shared_ptr<ChsEntity> getEntityWithModel( std::string entityName,
										std::string modelName );
		
		boost::shared_ptr<ChsEntity> getEntityWithModelAndAnimation( std::string entityName, 
												    std::string modelName,
													std::string animationName );
	};
	
	//----------------------------------------------------------------------------------------------
	
}

#endif//_CHS_ENTITYMANAGER_H
