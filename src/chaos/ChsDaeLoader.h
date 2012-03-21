#ifndef _CHS_DAELOADER_H
#define _CHS_DAELOADER_H

namespace Chaos {

	class ChsMesh;
	
	class ChsDaeLoader {
	public:
		ChsMesh* load( const char * filename );
	private:
	};
	
}


#endif//_CHS_DAELOADER_H
