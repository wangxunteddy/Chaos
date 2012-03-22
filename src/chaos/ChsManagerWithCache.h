#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H

#include <map>
#include "ChsUtility.h"
#include <boost/foreach.hpp>

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
		std::pair<KeyType, ValueType *> p;
		BOOST_FOREACH( p, this->cache ){
			ValueType * obj = p.second;
			safeDelete( &obj, "删除对象" );
		}
		this->cache.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	
}


#endif//_CHS_MANAGERWITHCACHE_H
