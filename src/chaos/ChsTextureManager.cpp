#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"
#include "ChsTexture2D.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsTexture2D> ChsTextureManager::getTexture2D( std::string name ){
		boost::shared_ptr<ChsTexture2D> texture = this->getFromCache( name );
		if( !texture ){
			texture.reset( ChsTextureFactory::sharedInstance()->createTexture2D( name.c_str() ) );
			if( texture ){
				printf( "生成texture:%s\n", name.c_str() );
				insert( this->cache )( name, texture );
			}
		}
	    return texture;
	}
	
	//----------------------------------------------------------------------------------------------
	
}
