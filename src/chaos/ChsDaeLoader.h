#ifndef _CHS_DAELOADER_H
#define _CHS_DAELOADER_H

namespace Chaos {

	class ChsModel;
	
	class ChsDaeLoader {
	public:
		ChsModel* load( const char * filename );
	private:
	};
	
}


#endif//_CHS_DAELOADER_H
