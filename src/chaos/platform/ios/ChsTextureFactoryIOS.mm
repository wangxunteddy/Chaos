#import <Foundation/Foundation.h>
#include "ChsFileSystemIOS.h"
#include "ChsTextureFactoryIOS.h"
#include "ChsTexture2D.h"

namespace Chaos {
	
	ChsTextureFactoryIOS gTextureFactory;
	
	ChsTexture2D * ChsTextureFactoryIOS::createTexture2D( std::string path ){
		NSString * fullPathName = ChsFileSystemIOS::getFullPath( path.c_str() );
		UIImage* imageClass = [[UIImage alloc] initWithContentsOfFile: fullPathName];
		CGImageRef cgImage = imageClass.CGImage;
		if( !cgImage )
			return NULL;
		
		unsigned int width = CGImageGetWidth(cgImage);
		unsigned int height = CGImageGetHeight(cgImage);
		CGImageAlphaInfo alphaInfo =  CGImageGetAlphaInfo( cgImage );
		int format = GL_RGBA;
		if( alphaInfo == kCGImageAlphaNone)
			format = GL_RGB;
		
		unsigned int rowByteSize = width * 4;
		unsigned char * imgData = new unsigned char[height * rowByteSize];

		CGContextRef context = CGBitmapContextCreate( imgData, width, height, 8, rowByteSize,
													 CGImageGetColorSpace(cgImage), kCGImageAlphaNoneSkipLast);
		CGContextSetBlendMode( context, kCGBlendModeCopy);
		CGContextTranslateCTM( context, 0.0, height );
		CGContextScaleCTM( context, 1.0, -1.0);
		CGContextDrawImage( context, CGRectMake(0.0, 0.0, width, height ), cgImage );
		CGContextRelease( context );

		ChsTexture2D * texture = new ChsTexture2D();
		texture->build( width, height, format, imgData );
		return texture;
	}
}