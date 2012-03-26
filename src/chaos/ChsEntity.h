#ifndef _CHS_ENTITY_H
#define _CHS_ENTITY_H

#include <boost/weak_ptr.hpp>

#include "ChsRenderNode.h"

namespace Chaos {

	class ChsRenderSystem;
	class ChsModel;	
	//----------------------------------------------------------------------------------------------
	class ChsEntity : public ChsRenderNode {
	private:
		void render( ChsRenderSystem * render );
	public:
		ChsEntity( std::string name );
		virtual ~ChsEntity( void );
		
		boost::weak_ptr<ChsModel> model;
		inline void setModel( const boost::shared_ptr<ChsModel> & model );
		
		PROPERTY_READONLY( std::string , name );
	};
	
	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY( ChsEntity, std::string, name );
	
	inline void ChsEntity::setModel( const boost::shared_ptr<ChsModel> & model ){
		this->model = model;
	}
}

#endif//_CHS_ENTITY_H
