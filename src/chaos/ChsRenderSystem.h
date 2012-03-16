#ifndef _CHS_RENDERSYSTEM_H
#define _CHS_RENDERSYSTEM_H
#pragma once

#include "ChsDefine.h"
#include "ChsMacro.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {

	class ChsRenderNode;
	class ChsMaterial;
	class ChsIndexBuffer;
	class ChsVertexBuffer;
	class ChsCameraBase;
	
	struct ChsRenderUnit{
		ChsMaterial * material;
		ChsVertexBuffer * vertexBuffer;
		ChsIndexBuffer * indexBuffer;
	};
	
	//----------------------------------------------------------------------------------------------
	class ChsRenderSystem {
	protected:
		virtual void present( void ) = 0;
		
		virtual void initContext( void ) = 0;
		virtual void releaseContext( void ) = 0;
		virtual void attachContext( void ) = 0;
		virtual void initRenderBuffer( void ) = 0;
	
		
		// The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
	    GLuint framebuffer;
		GLuint renderbuffer;
		GLuint depthRenderbuffer;
		
		// The pixel dimensions of the CAEAGLLayer.
    	GLint renderbufferWidth;
	    GLint renderbufferHeight;
		
	private:
		//viewport
		ChsRect viewport;

		void preRender( void );
		void render( void );
	    void postRender( void );

		void initAllBuffers( void );
		void deleteAllBuffers( void );
		void initFrameBuffer( void );
		void initDepthBuffer( void );
		void initGL( void );
	public:
		ChsRenderSystem( void );
		virtual ~ChsRenderSystem( void );
		
		void init( void );
		void shutdown( void );
		void update( void );
	
		void sendToRender( ChsRenderUnit unit );
		
		void setClearColor( float r, float g, float b, float a );
		void setClearColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		void setClearColor( unsigned int rgba );
		
		void setViewPort( int x, int y, int w, int h );
		inline ChsRect getViewPort( void );
		
		PROPERTY_READONLY( ChsRenderNode *, root );
		PROPERTY( ChsCameraBase *, currentCamera );
		PROPERTY( bool, showDebugCoordinate );
	};
	
	//----------------------------------------------------------------------------------------------
	inline ChsRect ChsRenderSystem::getViewPort( void ){
		return this->viewport;
	}

	//----------------------------------------------------------------------------------------------
	SYNTHESIZE_READONLY( ChsRenderSystem, ChsRenderNode *, root );
	SYNTHESIZE( ChsRenderSystem, ChsCameraBase *, currentCamera );
	SYNTHESIZE_GETTER( ChsRenderSystem, bool, showDebugCoordinate );
	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_RENDERSYSTEM_H
