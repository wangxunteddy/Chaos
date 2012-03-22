#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"
#include <boost/assign.hpp>
using namespace boost::assign;
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsTexture2D * ChsTextureManager::getTexture2D( std::string name ){
		if( name.empty() )
			return NULL;
		if( this->cache.find( name ) != this->cache.end() )
        	return ( ChsTexture2D * )this->cache[name]; //cache hit
		ChsTexture2D * texture = ChsTextureFactory::sharedInstance()->createTexture2D( name.c_str() );
		if( texture ){
			printf( "生成texture:%s\n", name.c_str() );
			insert( this->cache )( name, texture );
		}
	    return texture;
	}
	
	//----------------------------------------------------------------------------------------------
	
}
