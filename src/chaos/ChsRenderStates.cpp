#include "ChsRenderStates.h"

#include "platform/ChsOpenGL.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	GLenum glStates[]={
		GL_TEXTURE_2D,
		GL_CULL_FACE,
		GL_BLEND,
		GL_DITHER,
		GL_STENCIL_TEST,
		GL_DEPTH_TEST,
		GL_SCISSOR_TEST,
		GL_POLYGON_OFFSET_FILL,
		GL_SAMPLE_ALPHA_TO_COVERAGE,
		GL_SAMPLE_COVERAGE,
	};
	
	//----------------------------------------------------------------------------------------------
	void getEnableOrDisable( ChsRenderState index, unsigned int & value );
	void getEnableOrDisable( ChsRenderState index, unsigned int & value ){
		
	}
	//----------------------------------------------------------------------------------------------
	void setEnableOrDisable( ChsRenderState index, unsigned int value );
	void setEnableOrDisable( ChsRenderState index, unsigned int value ){
		if( value )
			glEnable( glStates[index] );
		else
			glDisable( glStates[index] );
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderStates::set( ChsRenderState index, unsigned int value ){
		if( this->states[ index ] != value ){
			this->states[ index ] = value;
			if( CHS_RS_ENABLECAP >= index )
				setEnableOrDisable( index, value );
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsRenderStates::queryCurrentStates( void ){
		for( ChsRenderState i = CHS_RS_TEXTURE_2D; i < CHS_RS_MAX; i++ ) {
			if( i <= CHS_RS_ENABLECAP){
				if( glIsEnabled( glStates[i] ))
					this->states[i] = CHS_RS_ENABLE;
				else
					this->states[i] = CHS_RS_DISABLE;
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------
	
}
