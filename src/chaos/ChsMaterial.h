#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <string>

namespace Chaos {

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsShaderProgram;

	//--------------------------------------------------------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    	ChsMaterial( );
	    ~ChsMaterial( );
    	void apply( );
	    void setShader( const std::string vertxShaderName, const std::string fragmentShaderName );
		inline ChsShaderProgram * getShaderProgram( void );
	private:
    	ChsShaderProgram * shaderProgram;
	};

	//--------------------------------------------------------------------------------------------------------------------------------------------
	inline ChsShaderProgram * ChsMaterial::getShaderProgram( void ) {
		return this->shaderProgram;
	}
	
}//namespace
#endif //_CHSMATERIAL_H
