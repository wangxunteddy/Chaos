#import <QuartzCore/QuartzCore.h>
#include "ChsRenderSystemIOS.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer );
	CAEAGLLayer * glLayer = nil;
	EAGLContext * glContext = nil;

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer ){
		glLayer = layer;
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::initFrameAndRenderBuffers( void ){
		ChsRenderSystem::initFrameAndRenderBuffers();
		
		//connect with layer
		assert( glLayer );
		[glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:glLayer];
		//attachment
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->renderbuffer );
		
        glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &(this->renderbufferWidth) );
        glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &(this->renderbufferHeight) );
		
		if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
            printf( "Failed to make complete framebuffer object %x", glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::initContext( void ) {
		EAGLContext * context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2];
		
		if( !context )
			NSLog( @"Failed to create ES context" );
		else if( ![EAGLContext setCurrentContext : context ] )
			NSLog( @"Failed to set ES context current" );
		glContext = context;
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::releaseContext( void ) {
		if( [EAGLContext currentContext] == glContext )
			[EAGLContext setCurrentContext: nil];
		[glContext release];
		glContext = nil;
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::present( void ) {
		glBindRenderbuffer( GL_RENDERBUFFER, this->renderbuffer );
		[glContext presentRenderbuffer:GL_RENDERBUFFER];
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::attachContext( void ){
		if( [EAGLContext currentContext] != glContext )
			[EAGLContext setCurrentContext:glContext];
	}

}//namespace
