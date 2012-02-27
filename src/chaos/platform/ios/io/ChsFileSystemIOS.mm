#import <Foundation/Foundation.h>
#include "ChsFileSystemIOS.h"

//--------------------------------------------------------------------------------------------------

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsFileSystemIOS gFileSystem;

	//----------------------------------------------------------------------------------------------
	const char * ChsFileSystemIOS::readFileAsRaw( const char * path ){
    	NSString * fileName = [NSString stringWithUTF8String:path ];
	    NSString * type = [ fileName pathExtension];
    	fileName = [ [ fileName lastPathComponent ] stringByDeletingPathExtension ];
	    // Create and compile vertex shader.
    	NSString * vertShaderPathname = [[NSBundle mainBundle] pathForResource:fileName ofType:type];
		NSString * source = [NSString stringWithContentsOfFile:vertShaderPathname
													  encoding:NSUTF8StringEncoding
														 error:nil];
	    const char * data = (const char *)[source UTF8String];
    	return data;
	}

	//----------------------------------------------------------------------------------------------

}//namespace
