#include "ChsEntityManager.h"
#include <boost/assign.hpp>
using namespace boost::assign;
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntity( std::string entityName ){
		if( entityName.empty() )
			return NULL;
		boost::shared_ptr<ChsEntity> entityPtr = this->getFromCache( entityName );
		if( !entityPtr ){
			entityPtr = boost::shared_ptr<ChsEntity>( new ChsEntity( entityName ) );
			printf( "生成Entity:%s\n", entityName.c_str() );
			insert( this->cache )( entityName, entityPtr );
		}
		return entityPtr.get();
	}
#if 0
	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntityWithModel( std::string entityName,
													 std::string modelName ){
		if( entityName.empty() )
			return NULL;
		ChsEntity * entity = this->getEntity( entityName );
		//TODO: set model
		return entity;
	}


	//----------------------------------------------------------------------------------------------
	ChsEntity * ChsEntityManager::getEntityWithModelAndAnimation( std::string entityName,
																 std::string modelName,
																 std::string animationName ){
		if( entityName.empty() )
			return NULL;
		ChsEntity * entity = this->getEntityWithModel( entityName, modelName );
		//TODO: set animation
		return entity;
	}
#endif
	//----------------------------------------------------------------------------------------------
	void ChsEntityManager::releaseEntity( std::string name ){
		if( name.empty() )
			return;
		boost::shared_ptr<ChsEntity> entityPtr = this->getFromCache( name );
		if( entityPtr )
			this->cache.erase( name );
	}
	
	//----------------------------------------------------------------------------------------------
	
}//namespace
