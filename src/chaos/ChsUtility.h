#ifndef _CHS_UTILITY_H
#define _CHS_UTILITY_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include <string>
#include <boost/checked_delete.hpp>

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	size_t getGLDataTypeSize( int type );

	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeRelease( Type **pptr ) {
		if ( * pptr ) {
			( * pptr )->Release();
			* pptr = NULL;
		}
	}

	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeRelease( Type **pptr, std::string msg ) {
		if ( * pptr ) {
			( * pptr )->Release();
			* pptr = NULL;
			//if(!msg.empty())
			//LOGMSG(msg.c_str());
		}
	}

	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeDelete( Type ** pptr ) {
		if( * pptr ) {
			boost::checked_delete( * pptr );
			* pptr = NULL;
		}
	}

	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeDelete( Type ** pptr, std::string msg ) {
		if( * pptr ) {
			//LOGMSG(msg.c_str());
			boost::checked_delete( * pptr );
			*pptr = NULL;
		}
	}
	
	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeDeleteArray( Type ** pArrayPtr ) {
		if( * pArrayPtr ) {
			boost::checked_array_delete( * pArrayPtr );
			*pArrayPtr = NULL;
		}
	}

	//----------------------------------------------------------------------------------------------
	template< typename Type > void safeDeleteArray( Type ** pArrayPtr, std::string msg ) {
		if( * pArrayPtr ) {
			//LOGMSG(msg.c_str());
			boost::checked_array_delete( * pArrayPtr );
			*pArrayPtr = NULL;
		}
	}

	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_UTILITY_H
