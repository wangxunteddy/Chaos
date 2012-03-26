#ifndef _CHSMODEL_H
#define _CHSMODEL_H
#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include "ChsRenderNode.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsMesh;

	//----------------------------------------------------------------------------------------------
	class ChsModel : public ChsRenderNode {
	public:
		ChsModel( std::string name = "unnamed" );
		virtual ~ChsModel( void );
		void addMesh( boost::shared_ptr<ChsMesh> mesh );
	private:
		std::vector< boost::shared_ptr<ChsMesh> > meshs;
		void render( ChsRenderSystem * render );
	};

	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHSMODEL_H
