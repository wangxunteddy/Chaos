#ifndef _CHS_DAELOADER_H
#define _CHS_DAELOADER_H

#include <string>

namespace Chaos {

	class ChsMesh;
	
	class ChsDaeLoader {
	public:
		ChsMesh* load( std::string filename );
	private:
	};
	
}


#endif//_CHS_DAELOADER_H
