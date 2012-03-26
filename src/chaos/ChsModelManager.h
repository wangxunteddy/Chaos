#ifndef _CHS_MODELMANAGER_H
#define _CHS_MODELMANAGER_H

#include "ChsManagerWithCache.h"

namespace Chaos {
	class ChsModel;
	class ChsModelManager : public ChsManagerWithCache<ChsModel> {
	public:
		boost::shared_ptr<ChsModel> getModel( std::string name );
	};
	
}

#endif
