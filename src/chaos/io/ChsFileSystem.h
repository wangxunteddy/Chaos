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
    	virtual int readFileAsUTF8( const char *  path , char ** data ) = 0;
		virtual int readFileAsRaw( const char *  path , char ** data ) = 0;
		
	};

}//namespace

#endif //_CHS_FILESYSTEM_H
