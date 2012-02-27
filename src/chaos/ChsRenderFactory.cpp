#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsUtility.h"

#ifdef CHS_PLATFORM_IOS
	#include "ChsRenderSystemIOS.h"
#endif
//--------------------------------------------------------------------------------------------------
namespace Chaos{
	
	//----------------------------------------------------------------------------------------------
	static ChsRenderSystem * currentRender = NULL;
	
	//----------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsRenderFactory::create(ChsRenderType type){
		ChsRenderFactory::shutdown();
		ChsRenderSystem * render = NULL;
		switch ((int)type) {
#ifdef CHS_PLATFORM_IOS
			case CHS_RENDER_IOS:
				render = new ChsRenderSystemIOS();
				break;
#endif
			default:
				break;
		}
		if(render){
			render->init();
			currentRender = render;
		}
		return render;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderFactory::shutdown( void ){
		if(currentRender){
			currentRender->shutdown();
			safeDelete(&currentRender, "delete current render");
		}
	}
	
	//----------------------------------------------------------------------------------------------
}//namespace
