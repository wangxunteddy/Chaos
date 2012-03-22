#ifndef _CHS_SINGLETON_H
#define _CHS_SINGLETON_H
#pragma once
//------------------------------------------------------------------------------------------
#include <assert.h>

namespace Chaos{
	//------------------------------------------------------------------------------------------
	template < typename T > class ChsSingleton {
	public:
    	ChsSingleton( void );
	    ~ChsSingleton( void );
    	static T* sharedInstance( void );
	protected:
    	static T* _shareInstance;
	};

	//------------------------------------------------------------------------------------------
	template < typename T >T* ChsSingleton< T >::_shareInstance = 0;

	//------------------------------------------------------------------------------------------
	template < typename T >ChsSingleton< T >::ChsSingleton( void ) {
    	assert( !_shareInstance );
	    _shareInstance = static_cast< T * >( this );
	}

	//------------------------------------------------------------------------------------------
	template < typename T >ChsSingleton< T >::~ChsSingleton( void ) {
 	   assert( _shareInstance );
 	   _shareInstance = 0;
	}

	//------------------------------------------------------------------------------------------
	template < typename T >T* ChsSingleton< T >::sharedInstance( void ) {
 	   assert( _shareInstance );
  	  return _shareInstance;
	}

	//------------------------------------------------------------------------------------------
}//namespace
#endif//_CHS_SINGLETON_H
