#ifndef _CHS_TEXTUREFACTORYIOS_H
#define _CHS_TEXTUREFACTORYIOS_H

#include "ChsTextureFactory.h"

namespace Chaos {
	
	class ChsTextureFactoryIOS : public ChsTextureFactory {
	public:
		ChsTexture2D * createTexture2D( std::string filename );
	};
	
}


#endif//_CHS_TEXTUREFACTORYIOS_H
