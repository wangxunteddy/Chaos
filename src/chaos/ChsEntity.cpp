#include "ChsEntity.h"
#include "ChsModel.h"

namespace Chaos {

	ChsEntity::ChsEntity( std::string name ) : _name( name ) {
	}
	
	ChsEntity::~ChsEntity( void ){
	}
	
	void ChsEntity::render( ChsRenderSystem * render ){
		if( this->model.expired() )
			return;
		boost::shared_ptr<ChsModel> model = this->model.lock();
		model->renderNodes( render );
	}
	
}
