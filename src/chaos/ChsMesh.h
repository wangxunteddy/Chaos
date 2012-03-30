#ifndef _CHSMESH_H
#define _CHSMESH_H
#pragma once

//--------------------------------------------------------------------------------------------------------------------------------------------
#include "ChsRenderNode.h"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace Chaos {
	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsMaterial;
	class ChsVertexBuffer;
	class ChsIndexBuffer;

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsMesh : public ChsRenderNode{
		friend class ChsDaeLoader;
		friend class ChsModelLoader;
	public:
		ChsMesh( std::string name = "unnamed" );
		virtual ~ChsMesh( void );
		void setMaterial( ChsMaterial * material );
		inline ChsMaterial * getMaterial( void );
		void render( ChsRenderSystem * render );
	protected:
		boost::shared_ptr<ChsMaterial> material;
		boost::scoped_ptr<ChsVertexBuffer> vertexBuffer;
		boost::scoped_ptr<ChsIndexBuffer> indexBuffer;
	};

	//--------------------------------------------------------------------------------------------------------------------------------------------
	inline ChsMaterial * ChsMesh::getMaterial( ){
		return this->material.get();
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
#endif //_CHSMESH_H
