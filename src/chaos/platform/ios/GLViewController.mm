#import <QuartzCore/QuartzCore.h>
#import "GLViewController.h"
#import "EAGLView.h"
#include "chaos/Chaos.h"
//----------------------------------------------------------------------------
@interface GLViewController (){
	Chaos::ChsEngine * engine;
}

@property ( strong, nonatomic ) CADisplayLink * displayLink;
@property ( nonatomic ) BOOL isPresenting;
@property ( nonatomic ) NSInteger frameInterval;

-(void) setDisplayLinkToPresent;
-(void) resetDisplayLink;

@end

//----------------------------------------------------------------------------
@implementation GLViewController

@synthesize displayLink = _displayLink;
@synthesize isPresenting = _isPresenting;
@synthesize frameInterval = _frameInterval;

//----------------------------------------------------------------------------
-(void) update {
	engine->run();
}

//----------------------------------------------------------------------------
-(void) setDisplayLinkToPresent {
	if ( !self.isPresenting ) {
		CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(update)];
		[aDisplayLink setFrameInterval: self.frameInterval];
		[aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
		self.isPresenting = TRUE;
	}
}

//----------------------------------------------------------------------------
-(void) resetDisplayLink {
	if( self.isPresenting ){
		[self.displayLink invalidate];
    	self.displayLink = nil;
    	self.isPresenting = FALSE;
	}
}

//----------------------------------------------------------------------------
-(void) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

//----------------------------------------------------------------------------
#pragma mark - View lifecycle

- (void) 
viewDidLoad {
	[super viewDidLoad];
	//frameInterval must greater then 0, 1 = 60fps, 2 = 30fps etc...
	self.frameInterval = 1;
	Chaos::ChsRenderSystemIOSSetTargetGLLayer((CAEAGLLayer *)self.view.layer);
	engine = Chaos::ChsEngine::sharedInstance();
	engine->start();
}

//----------------------------------------------------------------------------
-(void) viewDidUnload {
	[super viewDidUnload];
	engine->shutdown();
}

//----------------------------------------------------------------------------
-(void) viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	[self setDisplayLinkToPresent];
}

//----------------------------------------------------------------------------
-(void) viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}

//----------------------------------------------------------------------------
-(void) viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
	[self resetDisplayLink];
}

//----------------------------------------------------------------------------
-(void) viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
}

//----------------------------------------------------------------------------
-(BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

@end
