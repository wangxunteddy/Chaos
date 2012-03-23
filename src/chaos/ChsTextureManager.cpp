#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"
#include <boost/assign.hpp>
using namespace boost::assign;
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsTexture2D * ChsTextureManager::getTexture2D( std::string name ){
		if( name.empty() )
			return NULL;
		boost::shared_ptr<ChsTexture2D> texturePtr = this->getFromCache( name );
		if( !texturePtr ){
			texturePtr = boost::shared_ptr<ChsTexture2D>( ChsTextureFactory::sharedInstance()->createTexture2D( name.c_str() ) );
			if( texturePtr ){
				printf( "生成texture:%s\n", name.c_str() );
				insert( this->cache )( name, texturePtr );
			}
		}
	    return texturePtr.get();
	}
	
	//----------------------------------------------------------------------------------------------
	
}
