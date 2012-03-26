#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "ChsDefine.h"
#include "ChsMacro.h"
#include "shader/ChsShaderUniform.h"

namespace Chaos {
	class ChsShaderProgram;
	class ChsTexture2D;
	//----------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    	ChsMaterial( void );
	    virtual ~ChsMaterial( void );
    	ChsShaderProgram * apply( ChsShaderProgram * program );
	    void setShader( boost::shared_ptr<ChsShaderProgram> program );
		void addTexture( boost::shared_ptr<ChsTexture2D> texture );
	private:
		
		std::vector<boost::shared_ptr<ChsTexture2D>> textures;
		
		ChsShaderUniform shaderUniforms;
		PROPERTY_READONLY( boost::weak_ptr<ChsShaderProgram>, shaderProgram );
		
		PROPERTY( boolean, hasVertexColor );
		PROPERTY( float, alpha );

		//texture
		PROPERTY( boolean, hasTexture );
		PROPERTY( int, textureCount );

		//light

	};

	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY( ChsMaterial, boost::weak_ptr<ChsShaderProgram>, shaderProgram );
	
	//color
	SYNTHESIZE( ChsMaterial, boolean, hasVertexColor );
	SYNTHESIZE( ChsMaterial, float, alpha );

	//texture
	SYNTHESIZE( ChsMaterial, boolean, hasTexture );
	SYNTHESIZE( ChsMaterial, int, textureCount );
	
	//lighting
	
}//namespace
#endif //_CHSMATERIAL_H
