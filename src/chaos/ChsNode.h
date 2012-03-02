#ifndef _CHS_NODE_H
#define _CHS_NODE_H

#include <map>
#include <string>
#include "ChsMacro.h"

namespace Chaos {
	
	
	class ChsNode {
	public:
		ChsNode( std::string name );
		~ChsNode( void );
		void add( std::string name, ChsNode * node );
		inline void add( ChsNode * node );
		ChsNode * remove( std::string name );
		ChsNode * get( std::string name );
	protected:
		std::map< std::string, ChsNode * >  children;
	
		PROPERTY_READONLY_CONST( std::string, name );
	};

	inline void ChsNode::add( ChsNode * node ){
		this->add( node->name(), node );
	}
	
	typedef std::map< std::string, ChsNode * > ChsNodeList;
	
	SYNTHESIZE_READONLY_CONST( ChsNode, std::string , name )	

}


#endif//_CHS_NODE_H
