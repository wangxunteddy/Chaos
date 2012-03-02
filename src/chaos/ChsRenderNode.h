#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include <string>
#include <map>

#include "ChsNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
	//----------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	//----------------------------------------------------------------------------------------------
	class ChsRenderNode : public ChsNode{
	protected:
		virtual void doRender( ChsRenderSystem * render ) = 0;
	public:
		ChsRenderNode( std::string name = "unnamed" );
		virtual ~ChsRenderNode( void );

		void render( ChsRenderSystem * render );
		
	private:
		
		PROPERTY( bool , visible );
	};
	
	//----------------------------------------------------------------------------------------------	
	SYNTHESIZE( ChsRenderNode, bool, visible );
	
	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_RENDERNODE_H
