#include "ChsNode.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsNode::ChsNode( std::string name ) : _name( name ){
		this->children.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsNode::~ChsNode( void ){
		this->children.clear();
	}

	//----------------------------------------------------------------------------------------------
	void ChsNode::add( std::string name, ChsNode * node ){
		ChsNodeList::iterator iter = this->children.find( name );
		if( iter == this->children.end() ){
			this->children.insert( make_pair( name, node ) );
		}
	}
	
	//----------------------------------------------------------------------------------------------
	ChsNode * ChsNode::remove( std::string name ){
		ChsNode * node = this->get( name );
		if( node != NULL )
			this->children.erase( name );
		return node;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsNode * ChsNode::get( std::string name ){
		ChsNodeList::iterator iter = this->children.find( name );
		return  ( iter == this->children.end( ) ) ? NULL : iter->second;
	}

}
