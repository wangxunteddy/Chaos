#ifndef _CHSDEFINE_H
#define _CHSDEFINE_H
#pragma once

namespace Chaos {

	//----------------------------------------------------------------------------------------------
#if defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined (TARGET_OS_IPHONE)
		#define CHS_PLATFORM_IOS
	#endif
#endif

	//----------------------------------------------------------------------------------------------
#if defined(ANDROID)
	#define CHS_PLATFORM_ANDROID
#endif

	//----------------------------------------------------------------------------------------------
	enum ChsRenderType{
		CHS_RENDER_IOS,
		CHS_RENDER_ANDROID,
		//		CHS_RENDER_D3D
	};
	//----------------------------------------------------------------------------------------------

}//namespace
#endif//_CHSDEFINE_H
