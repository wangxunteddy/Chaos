#include "ChsEntityManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntityFromCache( std::string entityName ){
		ChsEntity * entity = NULL;
		if(this->cache.find( entityName ) != this->cache.end() ){
			entity = this->cache[entityName];
		}
		return entity;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntity( std::string entityName ){
		if(entityName.empty())
			return NULL;
		ChsEntity * entity = this->getEntityFromCache( entityName );
		if( entity == NULL ){
			entity = new ChsEntity( entityName );
			printf("生成Entity:%s\n",entityName.c_str());
			this->cache.insert( std::make_pair( entityName, entity ) );
		}
		return entity;
	}

	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntityWithModel( std::string entityName,
													 std::string modelName ){
		if(entityName.empty())
			return NULL;
		ChsEntity * entity = this->getEntity( entityName );
		//TODO: set model
		return entity;
	}


	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntityWithModelAndAnimation( std::string entityName,
																 std::string modelName,
																 std::string animationName ){
		if(entityName.empty())
			return NULL;
		ChsEntity * entity = this->getEntityWithModel( entityName, modelName );
		//TODO: set animation
		return entity;
	}

	//----------------------------------------------------------------------------------------------
	void ChsEntityManager::releaseEntity( std::string entityName ){
		if(entityName.empty())
			return;
		if(this->cache.find(entityName) != this->cache.end() ) {
			ChsEntity * entity = this->cache[entityName];
			this->cache.erase(entityName);
			safeDelete( &entity );
		}
	}
	
}//namespace
