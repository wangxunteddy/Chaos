#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H

#include <map>
#include "ChsUtility.h"
#include <boost/shared_ptr.hpp>

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType > class ChsManagerWithCache {
	public:
    	void purge( void );
	protected:
		typedef std::map< KeyType, boost::shared_ptr<ValueType> > CacheType;
	   	CacheType cache;
		boost::shared_ptr<ValueType> getFromCache( std::string name );
		ValueType * getFromCacheWithValue( std::string name );
	};

	//------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType >
	void ChsManagerWithCache< KeyType, ValueType >::purge( void ) {
		this->cache.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType >
	boost::shared_ptr<ValueType> ChsManagerWithCache< KeyType, ValueType >::getFromCache( std::string name ){
		boost::shared_ptr<ValueType> objPtr;
		typename CacheType::iterator iter = this->cache.find( name );
		if( iter != this->cache.end() )
			objPtr = iter->second;
		return objPtr;
	}
	
	//----------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType >
	ValueType * ChsManagerWithCache< KeyType, ValueType >::getFromCacheWithValue( std::string name ){
		return this->getFromCache( name ).get();
	}
	
	//----------------------------------------------------------------------------------------------
	
}


#endif//_CHS_MANAGERWITHCACHE_H
