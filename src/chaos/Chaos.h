#ifndef _CHS_CHAOS_H
#define _CHS_CHAOS_H
#pragma once

#include "ChsEngine.h"
#include "ChsRenderSystem.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	
#ifdef __OBJC__
	//set layer before engine start
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer );
#endif
	
	extern CHsOrientation orientation;
	
	//----------------------------------------------------------------------------------------------

}//namespace

#endif//_CHS_CHAOS_H
