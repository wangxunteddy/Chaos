#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "math/ChsMatrix.h"
#include <boost/foreach.hpp>

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::ChsRenderNode( std::string name ) : ChsNode( name ) {
		this->visible( true );
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::~ChsRenderNode( void ){
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderNode::renderNodes( ChsRenderSystem * render ){
		if( !this->visible() )
			return;//if this node is invisible,then all chilren are invisible too
		this->render( render );
		std::pair<std::string, ChsNode *> p;
		BOOST_FOREACH( p, this->children )
			( ( ChsRenderNode * )p.second )->renderNodes( render );
	}

	//----------------------------------------------------------------------------------------------
}
