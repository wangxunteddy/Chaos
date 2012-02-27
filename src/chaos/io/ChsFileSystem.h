#ifndef _CHS_FILESYSTEM_H
#define _CHS_FILESYSTEM_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsFileSystem : public ChsSingleton< ChsFileSystem >{
	public:
    	virtual const char * readFileAsRaw( const char *  path ) = 0;
	};

}//namespace

#endif //_CHS_FILESYSTEM_H
