#ifndef _CHS_TEXTUREMANAGER_H
#define _CHS_TEXTUREMANAGER_H

#include "ChsManagerWithCache.h"

namespace Chaos{
	class ChsTexture2D;	
	//----------------------------------------------------------------------------------------------
	class ChsTextureManager : public ChsManagerWithCache< ChsTexture2D > {
	public:
		boost::shared_ptr<ChsTexture2D> getTexture2D( std::string name );
	};
	
	//----------------------------------------------------------------------------------------------
	
}


#endif//_CHS_TEXTUREMANAGER_H
