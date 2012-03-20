#ifndef _CHS_FILESYSTEMIO_H
#define _CHS_FILESYSTEMIO_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsFileSystem.h"
namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsFileSystemIOS : public ChsFileSystem {
	public:
    	int readFileAsUTF8( const char * path, char ** data );
		int readFileAsRaw( const char *  path , char ** data );
		static NSString * getFullPath( const char * path );
	};

	//----------------------------------------------------------------------------------------------
	
}//namespace

#endif //_CHS_FILESYSTEMIO_H
