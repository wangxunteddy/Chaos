#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "math/ChsMatrix.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------


	//----------------------------------------------------------------------------------------------
	ChsRenderNode::ChsRenderNode( std::string name ) : ChsNode( name ) {
//		this->_worldMatrix = new ChsMatrix();
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::~ChsRenderNode( void ){
//		safeDelete( &this->_worldMatrix ); 
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderNode::render( ChsRenderSystem * render ){
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
