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
	enum ChsShaderUniformDataType {
		CHS_SHADER_UNIFORM_1_FLOAT,
		CHS_SHADER_UNIFORM_1_INT,
		CHS_SHADER_UNIFORM_VEC2_FLOAT,
		CHS_SHADER_UNIFORM_VEC2_INT,
		CHS_SHADER_UNIFORM_VEC3_FLOAT,
		CHS_SHADER_UNIFORM_VEC3_INT,
		CHS_SHADER_UNIFORM_VEC4_FLOAT,
		CHS_SHADER_UNIFORM_VEC4_INT,
		CHS_SHADER_UNIFORM_MAT2,
		CHS_SHADER_UNIFORM_MAT3,
		CHS_SHADER_UNIFORM_MAT4,
	};
	
	//----------------------------------------------------------------------------------------------
	enum CHsOrientation{
		CHS_LANDSCAPE,
		CHS_PORTRAIT,
	};
	
	//----------------------------------------------------------------------------------------------
	struct ChsRect{
		float x;
		float y;
		float w;
		float h;
	};
}//namespace
#endif//_CHSDEFINE_H
