#import <Foundation/Foundation.h>
#include <string.h>
#include "ChsFileSystemIOS.h"

//--------------------------------------------------------------------------------------------------

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsFileSystemIOS gFileSystem;

	//----------------------------------------------------------------------------------------------
	NSString * ChsFileSystemIOS::getFullPath( const char * path ){
		NSString * fileName = [NSString stringWithUTF8String:path ];
	    NSString * type = [ fileName pathExtension];
    	fileName = [ [ fileName lastPathComponent ] stringByDeletingPathExtension ];
    	NSString * fullPathName = [[NSBundle mainBundle] pathForResource:fileName ofType:type];
		return fullPathName;
	}
	
	//----------------------------------------------------------------------------------------------
	int ChsFileSystemIOS::readFileAsUTF8( const char * path, char ** data ){
		NSString * fullPathName = getFullPath( path );
		NSString * source = [NSString stringWithContentsOfFile:fullPathName
													  encoding:NSUTF8StringEncoding
														 error:nil];
		int length = [source length];
		if(length>0){
			*data = new char [length];
		    strcpy( *data, static_cast<const char *>([source UTF8String]));
		}
    	return length;
	}
	
	//----------------------------------------------------------------------------------------------
	int ChsFileSystemIOS::readFileAsRaw( const char * path, char ** data ){
    	NSString * fullPathName = getFullPath( path );
		NSData * rawData = [NSData dataWithContentsOfFile: fullPathName ];
		int length = [rawData length];
		if(length > 0){
			*data = new char [length];
		    memcpy( *data, static_cast<const char *>( [rawData bytes] ), length );
		}
    	return length;
	}
	
}//namespace
