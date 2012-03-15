#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H

#include <map>
#include "ChsUtility.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType > class ChsManagerWithCache {
	public:
    	void purge( void );
	protected:
		typedef std::map< KeyType, ValueType * > CacheType;
	   	CacheType cache;
	};

	//------------------------------------------------------------------------------------------
	template < typename KeyType, typename ValueType >
	void ChsManagerWithCache< KeyType, ValueType >::purge( void ) {
		
		typename CacheType::iterator iter = this->cache.begin();
		typename CacheType::iterator end = this->cache.end();
		while ( iter != end ) {
			ValueType * obj = iter->second;
			//delete obj;
			safeDelete( &obj, "删除对象" );
		}
		this->cache.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	
}


#endif//_CHS_MANAGERWITHCACHE_H
