#ifndef _CHS_RENDERSTATES_H
#define _CHS_RENDERSTATES_H

#include "ChsMacro.h"
#include "ChsDefine.h"
#include "ChsSingleton.h"

namespace Chaos {
	
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
