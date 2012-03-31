#ifndef _CHS_RENDERSTATES_H
#define _CHS_RENDERSTATES_H

#include "ChsMacro.h"
#include "ChsSingleton.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	enum ChsRenderState{
		CHS_RS_DISABLE,
		CHS_RS_ENABLE,
		
		CHS_RS_TEXTURE_2D = 0,
		CHS_RS_CULL_FACE,
		CHS_RS_BLEND,
		CHS_RS_DITHER,
		CHS_RS_STENCIL_TEST,
		CHS_RS_DEPTH_TEST,
		CHS_RS_SCISSOR_TEST,
		CHS_RS_POLYGON_OFFSET_FILL,
		CHS_RS_SAMPLE_ALPHA_TO_COVERAGE,
		CHS_RS_SAMPLE_COVERAGE,
		CHS_RS_ENABLECAP = CHS_RS_SAMPLE_COVERAGE,
		
		CHS_RS_MAX,
	};

	//----------------------------------------------------------------------------------------------
	class ChsRenderStates : public ChsSingleton<ChsRenderStates> {
	public:
		void queryCurrentStates( void );
		void set( ChsRenderState state, unsigned int value );
	private:
		unsigned int states[CHS_RS_MAX];
	};
	
	//----------------------------------------------------------------------------------------------
#define ChsRSTexture2D( state ) ChsRenderStates::sharedInstance()->set( CHS_RS_TEXTURE_2D, ( state ) )
#define ChsRSDepthTest( state ) ChsRenderStates::sharedInstance()->set( CHS_RS_DEPTH_TEST, ( state ) )
#define ChsRSBlend( state ) ChsRenderStates::sharedInstance()->set( CHS_RS_BLEND, ( state ) )
#define ChsRSCullFace( state ) ChsRenderStates::sharedInstance()->set( CHS_RS_CULL_FACE, ( state ) )
}


#endif//_CHS_RENDERSTATES_H
