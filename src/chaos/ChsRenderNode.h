#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "ChsNode.h"
#include "ChsRenderable.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
	//----------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	//----------------------------------------------------------------------------------------------
	class ChsRenderNode : public ChsNode, ChsRenderable{
	public:
		ChsRenderNode( std::string name = "unnamed" );
		virtual ~ChsRenderNode( void );

		void renderNodes( ChsRenderSystem * render );
		
	private:
		
		PROPERTY( bool , visible );
	};
	
	//----------------------------------------------------------------------------------------------	
	SYNTHESIZE( ChsRenderNode, bool, visible );
	
	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_RENDERNODE_H
