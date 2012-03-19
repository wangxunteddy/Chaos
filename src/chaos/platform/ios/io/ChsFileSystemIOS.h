#ifndef _CHS_FILESYSTEMIO_H
#define _CHS_FILESYSTEMIO_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsFileSystem.h"
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsFileSystemIOS : public ChsFileSystem {
	public:
    	int readFileAsRaw( const char * path, char ** data );
	};

	//----------------------------------------------------------------------------------------------
	
}//namespace

#endif //_CHS_FILESYSTEMIO_H
