#ifndef _CHSRENDERFACTORY_H
#define _CHSRENDERFACTORY_H
#pragma once
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	class ChsRenderSystem;
	//----------------------------------------------------------------------------------------------
	class ChsRenderFactory{
	public:
		static ChsRenderSystem * create( void );
		static void shutdown( void );
	};
	//----------------------------------------------------------------------------------------------
}

#endif//
