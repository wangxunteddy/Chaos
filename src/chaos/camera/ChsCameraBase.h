#ifndef _CHS_CAMERABASE_H
#define _CHS_CAMERABASE_H
#pragma once

#include "math/ChsVector3.h"
#include "math/ChsMatrix.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//----------------------------------------------------------------------------------------------
	class ChsCameraBase {
	public:
		ChsCameraBase( void );
		virtual ~ChsCameraBase( void );

		virtual	void update( void );
		
		virtual	void lookAt( const ChsVector3 & position , const ChsVector3 & target );
		virtual	void lookAt( float posX, float posY, float posZ, float targetX, float targetY, float targetZ );
		virtual	void perspective( float fovy , float aspect , float near , float far );
		virtual void frustum( float left, float right, float bottom, float top, float znear, float zfar );
		virtual void ortho( float left , float right , float bottom, float top, float near , float far );

		void moveTo( float x, float y, float z );
		void moveTo( const ChsVector3 & position );
		
		void targetTo( float x, float y, float z );
		void targetTo( const ChsVector3 & target );

		inline ChsMatrix & getViewProjectionMatrix( void );
		inline ChsMatrix & getViewMatrix( void );
		inline ChsMatrix & getProjectionMatrix( void );
	protected:
		bool isNeedUpdateViewMatrix;
		
		ChsMatrix mtxView;
		ChsMatrix mtxProjection;
		ChsMatrix mtxViewProj;
		
		ChsVector3 position;
		ChsVector3 target;
		ChsVector3 up;
		
		float prjFovy;
		float prjAspect;
		float prjNear;
		float prjFar;
		float prjLeft;
		float prjRight;
		float prjBottom;
		float prjTop;
	};

	//----------------------------------------------------------------------------------------------
	inline ChsMatrix & ChsCameraBase::getViewProjectionMatrix( void ){
		return this->mtxViewProj;
	}
	inline ChsMatrix & ChsCameraBase::getViewMatrix( void ){
		return this->mtxView;
	}
	inline ChsMatrix & ChsCameraBase::getProjectionMatrix( void ){
		return this->mtxProjection;
	}
}
#endif	//_CHS_CAMERABASE_H
