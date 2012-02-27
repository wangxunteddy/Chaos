#import <QuartzCore/QuartzCore.h>
#import "EAGLView.h"

//----------------------------------------------------------------------------
@interface EAGLView (PrivateMethods)
@end

//----------------------------------------------------------------------------
@implementation EAGLView

//----------------------------------------------------------------------------
// You must implement this method
+ (Class)
layerClass
{
	return [CAEAGLLayer class];
}

//----------------------------------------------------------------------------
//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)
initWithCoder:(NSCoder*)coder
{
	self = [super initWithCoder:coder];
	if (self) {
    	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
       
		eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
    }
    
    return self;
}

@end
