#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "math/ChsMatrix.h"

namespace Chaos {

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::ChsRenderNode( std::string name ) : ChsNode( name ) {
		this->visible( true );
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::~ChsRenderNode( void ){
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderNode::render( ChsRenderSystem * render ){
		if( !this->visible() )
			return;//if this node is invisible,then all chilren are invisible too
		this->doRender( render );
		ChsNodeList::iterator iter =  this->children.begin();
		ChsNodeList::iterator endIter =  this->children.end();
		while( iter != endIter ){
			ChsRenderNode * node = ( ChsRenderNode * )iter->second;
			node->render( render );
			iter++;
		}
	}

	//----------------------------------------------------------------------------------------------
}
