#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"

namespace Chaos {

	ChsTexture2D * ChsTextureManager::getTexture2D( std::string name ){
		if( name.empty() )
			return NULL;
		if( this->cache.find( name ) != this->cache.end() )
        	return ( ChsTexture2D * )this->cache[name]; //cache hit
		ChsTexture2D * texture = ChsTextureFactory::sharedInstance()->createTexture2D( name );
		if( texture ){
			printf( "生成texture:%s\n", name.c_str() );
    		this->cache.insert( std::make_pair( name, texture ) );
		}
	    return texture;
	}
	
}
