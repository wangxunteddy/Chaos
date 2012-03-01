#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include <string>
#include <map>

#include "ChsMacro.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
	//----------------------------------------------------------------------------------------------
	class ChsMatrix;
	class ChsRenderSystem;
	//----------------------------------------------------------------------------------------------
	class ChsRenderNode {
	protected:
		virtual void doRender( ChsRenderSystem * render ) = 0;
	public:
		ChsRenderNode( std::string name = "unnamed" );
		virtual ~ChsRenderNode( void );
		
		void add( std::string name, ChsRenderNode * node );
		inline void add( ChsRenderNode * node );
		ChsRenderNode * remove( std::string name );
		ChsRenderNode * get( std::string name );

		void render( ChsRenderSystem * render );
		
	private:
		std::map< std::string, ChsRenderNode * >  children;
		PROPERTY_READONLY( ChsMatrix *, worldMatrix);
		PROPERTY_READONLY_CONST( std::string, name );
	};
	
	SYNTHESIZE_READONLY( ChsRenderNode, ChsMatrix *, worldMatrix )
	SYNTHESIZE_READONLY_CONST( ChsRenderNode, std::string , name )	

	inline void ChsRenderNode::add( ChsRenderNode * node ){
		this->add( node->name(), node );
	}
	//--------------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_RENDERNODE_H
