#ifndef _CHS_RENDERSYSTEMIOS_H
#define _CHS_RENDERSYSTEMIOS_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "chaos/ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsRenderSystemIOS : public ChsRenderSystem {
	private:
		void present( void );
		
		void initContext( void );
		void releaseContext( void );
		void attachContext( void );
		
		void initRenderBuffer( void );
	};

	//----------------------------------------------------------------------------------------------
	
}//namespace

#endif//_CHSRENDERSYSTEMIOS_H
