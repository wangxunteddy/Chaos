#import <Foundation/Foundation.h>
#include <string.h>
#include "ChsFileSystemIOS.h"

//--------------------------------------------------------------------------------------------------

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsFileSystemIOS gFileSystem;

	//----------------------------------------------------------------------------------------------
	int ChsFileSystemIOS::readFileAsRaw( const char * path, char ** data ){
    	NSString * fileName = [NSString stringWithUTF8String:path ];
	    NSString * type = [ fileName pathExtension];
    	fileName = [ [ fileName lastPathComponent ] stringByDeletingPathExtension ];
	    // Create and compile vertex shader.
    	NSString * vertShaderPathname = [[NSBundle mainBundle] pathForResource:fileName ofType:type];
		NSString * source = [NSString stringWithContentsOfFile:vertShaderPathname
													  encoding:NSUTF8StringEncoding
														 error:nil];
		int length = [source length];
		if(length<=0)
			return NULL;
		*data = new char [length];
	    strcpy( (char *)*data, (const char *)[source UTF8String]);
    	return length;
	}
}//namespace
