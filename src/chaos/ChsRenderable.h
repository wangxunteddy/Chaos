#ifndef _CHS_RENDERABLE_H
#define _CHS_RENDERABLE_H

namespace Chaos {
	class ChsRenderSystem;
	
	class ChsRenderable {
	protected:
		virtual void render( ChsRenderSystem * render ){};
	};
}


#endif
