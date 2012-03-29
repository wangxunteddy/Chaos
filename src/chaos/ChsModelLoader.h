#ifndef _CHS_MODELLOADER_H
#define _CHS_MODELLOADER_H

namespace Chaos {
	class ChsModel;
	class ChsModelLoader {
	private:
		ChsModel* loadAsXML( const char * filename );
		ChsModel* loadAsBinary( const char * filename );
	public:
		ChsModel* load( const char * filename );
	};
}


#endif
