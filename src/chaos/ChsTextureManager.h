#ifndef _CHS_TEXTUREMANAGER_H
#define _CHS_TEXTUREMANAGER_H

#include "ChsManagerWithCache.h"
#include "ChsTexture2D.h"

namespace Chaos{
	
	//----------------------------------------------------------------------------------------------
	class ChsTextureManager : public ChsManagerWithCache<std::string,ChsTexture2D>{
	public:
		ChsTexture2D * getTexture2D( std::string name );
	};
	
	//----------------------------------------------------------------------------------------------
	
}


#endif//_CHS_TEXTUREMANAGER_H
