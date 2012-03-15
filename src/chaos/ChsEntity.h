#ifndef _CHS_ENTITY_H
#define _CHS_ENTITY_H

#include "ChsRenderNode.h"

namespace Chaos {

	class ChsRenderSystem;
	
	//----------------------------------------------------------------------------------------------
	class ChsEntity : public ChsRenderNode {
	private:
		void doRender( ChsRenderSystem * render );
	public:
		ChsEntity( std::string name );
		virtual ~ChsEntity( void );
		
		PROPERTY_READONLY( std::string , name );
	};
	
	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY( ChsEntity, std::string, name );
}

#endif//_CHS_ENTITY_H
