#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsEntityManager.h"
#include "ChsEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsEntity> ChsEntityManager::getEntity( std::string entityName ){
		boost::shared_ptr<ChsEntity> entityPtr = this->getFromCache( entityName );
		if( !entityPtr ){
			entityPtr = boost::shared_ptr<ChsEntity>( new ChsEntity( entityName ) );
			printf( "生成Entity:%s\n", entityName.c_str() );
			insert( this->cache )( entityName, entityPtr );
		}
		return entityPtr;
	}
#if 0
	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsEntity> ChsEntityManager::getEntityWithModel( std::string entityName,
													 std::string modelName ){
		if( entityName.empty() )
			return NULL;
		ChsEntity * entity = this->getEntity( entityName );
		//TODO: set model
		return entity;
	}


	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsEntity> ChsEntityManager::getEntityWithModelAndAnimation( std::string entityName,
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
	
}//namespace
