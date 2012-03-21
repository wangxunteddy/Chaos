#ifndef _CHS_TEXTUREFACTORY_H
#define _CHS_TEXTUREFACTORY_H

#include "ChsSingleton.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsTexture2D;
	
	//----------------------------------------------------------------------------------------------
	class ChsTextureFactory : public ChsSingleton<ChsTextureFactory>{
	public:
		virtual ChsTexture2D * createTexture2D( const char * filename ) = 0;
	};
	
	//----------------------------------------------------------------------------------------------
	
}

#endif//_CHS_TEXTUREFACTORY_H
