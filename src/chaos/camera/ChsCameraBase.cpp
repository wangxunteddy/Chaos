#include "ChsCameraBase.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsCameraBase::ChsCameraBase( void ) : up( 0.0f, 1.0f, 0.0f ) {
		this->mtxView.identity();
		this->mtxProjection.identity();
		this->isNeedUpdateViewMatrix = false;
	}

	//----------------------------------------------------------------------------------------------
	ChsCameraBase::~ChsCameraBase( void ){
	}

	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::update( void ){
		if( this->isNeedUpdateViewMatrix ){
			this->isNeedUpdateViewMatrix = false;
			this->mtxView.lookAt( this->position , this->target , this->up );
		}
		this->mtxViewProj = this->mtxView * this->mtxProjection;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::lookAt(const ChsVector3& position , const ChsVector3& target){
		this->moveTo( position );
		this->targetTo( target );
	}

	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::lookAt( float posX, float posY, float posZ, float targetX, float targetY, float targetZ ){
		this->moveTo( posX, posY, posZ );
		this->targetTo( targetX, targetY, targetZ );
	}

	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::perspective(float fovy, float aspect, float near, float far ){
		this->prjFovy = fovy;
		this->prjAspect = aspect;
		this->prjNear = near;
		this->prjFar = far;
		this->mtxProjection.perspective( fovy, aspect, near, far );
	}

	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::moveTo( float x, float y, float z ){
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
		this->isNeedUpdateViewMatrix = true;
	}
	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::moveTo( const ChsVector3 & position ){
		this->position = position;
		this->isNeedUpdateViewMatrix = true;
	}
	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::targetTo( float x, float y, float z ){
		this->target.x = x;
		this->target.y = y;
		this->target.z = z;
		this->isNeedUpdateViewMatrix = true;
	}
	//----------------------------------------------------------------------------------------------
	void ChsCameraBase::targetTo( const ChsVector3 & target ){
		this->target = target;
		this->isNeedUpdateViewMatrix = true;
	}
}
