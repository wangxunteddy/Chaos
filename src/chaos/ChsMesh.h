#ifndef _CHSMESH_H
#define _CHSMESH_H
#pragma once

//--------------------------------------------------------------------------------------------------------------------------------------------
#include "ChsRenderNode.h"

namespace Chaos {
	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsMaterial;
	class ChsVertexBuffer;
	class ChsIndexBuffer;

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsMesh : public ChsRenderNode{
		friend class ChsDaeLoader;
	public:
		ChsMesh( std::string name = "unnamed" );
		virtual ~ChsMesh( void );
		void load( const float * vertices, int verCount, const void * indeices );
		void setMaterial( void );
		inline ChsMaterial * getMaterial( void );
		
	protected:
		ChsMaterial * material;
		ChsVertexBuffer * vertexBuffer;
		ChsIndexBuffer * indexBuffer;
		void doRender( ChsRenderSystem * render );
		
	};

	//--------------------------------------------------------------------------------------------------------------------------------------------
	inline ChsMaterial * ChsMesh::getMaterial( ){
		return this->material;
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespace
#endif //_CHSMESH_H
