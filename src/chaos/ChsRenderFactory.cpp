#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsUtility.h"

#if defined( CHS_PLATFORM_IOS )
	#include "ChsRenderSystemIOS.h"
#elif defined(CHS_PLATFORM_ANDROID)
	#include "platform/android/ChsRenderSystemAndroid.h"
#endif

//--------------------------------------------------------------------------------------------------
namespace Chaos{
	
	//----------------------------------------------------------------------------------------------
	static ChsRenderSystem * currentRender = NULL;
	
	//----------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsRenderFactory::create( void ) {
		ChsRenderFactory::shutdown();
		ChsRenderSystem * render = 
#if defined (CHS_PLATFORM_IOS)
				new ChsRenderSystemIOS();
#elif defined(CHS_PLATFORM_ANDROID)
				new ChsRenderSystemAndroid();
#endif
		if( render ){
			render->init();
			currentRender = render;
		}
		return render;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderFactory::shutdown( void ){
		if( currentRender ){
			currentRender->shutdown();
			safeDelete( &currentRender, "delete current render" );
		}
	}
	
	//----------------------------------------------------------------------------------------------
}//namespace
