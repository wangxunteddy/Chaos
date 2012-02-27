#ifndef _CHSRENDERFACTORY_H
#define _CHSRENDERFACTORY_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	class ChsRenderSystem;
	//----------------------------------------------------------------------------------------------
	class ChsRenderFactory{
	public:
		static ChsRenderSystem * create( ChsRenderType type 
#if defined(CHS_PLATFORM_IOS)
										= CHS_RENDER_IOS
#elif defined(CHS_PLATFORM_ANDROID)
										= CHS_RENDER_ANDROID
#endif
										);
		static void shutdown( void );
	};
	//----------------------------------------------------------------------------------------------
}

#endif//
