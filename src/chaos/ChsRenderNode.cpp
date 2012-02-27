#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "ChsMatrix.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------

	typedef std::map< std::string, ChsRenderNode * > ChsRenderNodeList;
	
	//----------------------------------------------------------------------------------------------
	ChsRenderNode::ChsRenderNode( void ) : _worldMatrix( NULL ) {
		this->children.clear();
		this->_worldMatrix = new ChsMatrix();
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode::~ChsRenderNode( void ){
		safeDelete( &this->_worldMatrix );
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderNode::add( std::string name, ChsRenderNode * node ){
		ChsRenderNodeList::iterator iter = this->children.find( name );
		if( iter == this->children.end() ){
			this->children.insert( make_pair( name, node ) );
		}
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode * ChsRenderNode::remove( std::string name ){
		ChsRenderNode * node = this->get( name );
		if( node != NULL )
			this->children.erase( name );
		return node;
	}

	//----------------------------------------------------------------------------------------------
	ChsRenderNode * ChsRenderNode::get( std::string name ){
		ChsRenderNodeList::iterator iter = this->children.find( name );
		return  ( iter == this->children.end( ) ) ? NULL : iter->second;
	}

	//----------------------------------------------------------------------------------------------
	void ChsRenderNode::render( ChsRenderSystem * render ){
		this->doRender( render );
		ChsRenderNodeList::iterator iter =  this->children.begin();
		ChsRenderNodeList::iterator endIter =  this->children.end();
		while( iter != endIter ){
			iter->second->render( render );
			iter++;
		}
	}

	//----------------------------------------------------------------------------------------------
}
