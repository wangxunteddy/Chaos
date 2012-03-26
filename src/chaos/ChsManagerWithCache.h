#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H

#include <string>
#include <map>
#include "ChsUtility.h"
#include <boost/shared_ptr.hpp>

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	template <typename ValueType> class ChsManagerWithCache {
	public:
    	void purge( void );
	protected:
		typedef std::map< std::string, boost::shared_ptr<ValueType> > CacheType;
	   	CacheType cache;
		boost::shared_ptr<ValueType> getFromCache( std::string key );
		ValueType * getFromCacheWithValue( std::string key );
		void remove( std::string key );
	};

	//------------------------------------------------------------------------------------------
	template < typename ValueType >
	void ChsManagerWithCache< ValueType >::purge( void ) {
		this->cache.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	template < typename ValueType >
	boost::shared_ptr<ValueType> ChsManagerWithCache< ValueType >::getFromCache( std::string key ){
		boost::shared_ptr<ValueType> objPtr;
		typename CacheType::iterator iter = this->cache.find( key );
		if( iter != this->cache.end() )
			objPtr = iter->second;
		return objPtr;
	}
	
	//----------------------------------------------------------------------------------------------
	template < typename ValueType >
	ValueType * ChsManagerWithCache< ValueType >::getFromCacheWithValue( std::string key ){
		return this->getFromCache( key ).get();
	}
	
	//----------------------------------------------------------------------------------------------
	template < typename ValueType >
	void ChsManagerWithCache< ValueType >::remove( std::string key ){
		this->cache.erase( key );
	}
}


#endif//_CHS_MANAGERWITHCACHE_H
