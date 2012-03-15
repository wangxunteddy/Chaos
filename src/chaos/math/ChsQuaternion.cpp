#include "ChsQuaternion.h"
#include "ChsVector3.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	ChsQuaternion::ChsQuaternion( void ){
		this->identity();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion::ChsQuaternion( const float q[4] ) : x( q[1] ), y( q[2] ), z( q[3] ), w( q[0] ){
	}
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion::ChsQuaternion( float x, float y, float z, float w ){
		float theta = w / 2;
		float sine = sin( theta );
		this->x = x * sine ;
		this->y = y * sine ;
		this->z = z * sine ;
		this->w = cos( theta );
	}
	
	//----------------------------------------------------------------------------------------------
	const ChsQuaternion	ChsQuaternion::quaternionIndentity( 0.0f, 0.0f, 0.0f, 0.0f );
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion& ChsQuaternion::operator = ( const ChsQuaternion & quat ){
		this->w = quat.w;
		this->x = quat.x;
		this->y = quat.y;
		this->z = quat.z;
		return *this;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion ChsQuaternion::operator *= ( const ChsQuaternion & quat ){
		ChsQuaternion qT;
		qT.w = this->w * quat.w - this->x * quat.x - this->y * quat.y - this->z * quat.z;
		qT.x = this->w * quat.x + this->x * quat.w + this->z * quat.y - this->y * quat.z;
		qT.y = this->w * quat.y + this->y * quat.w + this->x * quat.z - this->z * quat.x;
		qT.z = this->w * quat.z + this->z * quat.w + this->y * quat.x - this->x * quat.y;
		return qT;
	}
	
	//----------------------------------------------------------------------------------------------
	void ChsQuaternion::normailize( void ){
		float mag = (float)sqrt( this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z );
		if( mag > 0.0f ){
			float oneOverMag = 1.0f / mag;
			this->x *= oneOverMag;
			this->y *= oneOverMag;
			this->z *= oneOverMag;
			this->w *= oneOverMag;
		}
		else{
			//ERRMSG("被除数小于0！");
			this->identity();
		}
	}

	//----------------------------------------------------------------------------------------------
	void ChsQuaternion::identity( void ){
		this->w = 1.0f;
		this->x = this->y = this->z = 0.0f;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion ChsQuaternion::rotationVector( const ChsVector3 & from, const ChsVector3 & to ){
		ChsVector3 part = ChsVector3::cross( from, to );
		ChsQuaternion result;
		result.w = from * to;
		result.x = part.x;
		result.y = part.y;
		result.z = part.z;
		return result;
	}
	
	//----------------------------------------------------------------------------------------------
	float ChsQuaternion::dot( const ChsQuaternion & q1, const ChsQuaternion & q2 ){
		return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsQuaternion ChsQuaternion::slerp( const ChsQuaternion & q1, const ChsQuaternion & q2, float t ){
		//检查出界的参数，如果发现，则返回边界点
		if( t <= 0.0f )
			return q1;
		if( t >= 1.0f )
			return q2;
		//用点乘计算四元素夹角的cos
		float cosOmega = ChsQuaternion::dot( q1, q2 );
		//如果点乘为负，使用-q1
		//四元素q和-q代表相同的旋转，但可能产生不同的slerp运算，要选择一个正确的以便用锐角进行旋转
		float q1w = q1.w;
		float q1x = q1.x;
		float q1y = q1.y;
		float q1z = q1.z;
		if( cosOmega < 0.0f ){
			q1w = -q1w;
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			cosOmega = -cosOmega;
		}
		//因为使用的是两个单位四元素，点乘结果应该<=1.0f
		//assert ( cosOmega < 1.1f );
		//计算插值片，要注意检查非常接近的情况
		float k0,k1;
		if( cosOmega > 0.9999f ){
			//非常接近，即线性插值，防止除零
			k0 = 1.0f - t;
			k1 = t;
		}
		else{
			float sinOmega = sqrt( 1.0f - cosOmega * cosOmega );
			float omega = atan2( sinOmega, cosOmega );
			float oneOverSinOmega = 1.0f / sinOmega;
			k0 = sin( ( 1.0f - t ) * omega ) * oneOverSinOmega;
			k1 = sin( t * omega ) * oneOverSinOmega;
		}
		//插值
		ChsQuaternion result;
		result.x = k0 * q1.x + k1 * q1x;
		result.y = k0 * q1.y + k1 * q1y;
		result.z = k0 * q1.z + k1 * q1z;
		result.w = k0 * q1.w + k1 * q1w;
		return result;
	}
	
	//----------------------------------------------------------------------------------------------
	//共轭
	ChsQuaternion ChsQuaternion::conjugate( const ChsQuaternion & q ){
		ChsQuaternion result;
		//旋转量相同
		result.w = q.w;
		//旋转轴相反
		result.x = -q.x;
		result.y = -q.y;
		result.z = -q.z;
		return result;
	}
	
	//----------------------------------------------------------------------------------------------
	//求四元数幂
	ChsQuaternion ChsQuaternion::pow( const ChsQuaternion & q, float exponent ){
		if( fabs( q.w ) > 0.9999f )
			return q;
		
		//提取半角alpha（alpha = theta/2）
		float alpha = acos( q.w );
		float newAlpha = alpha * exponent;
		ChsQuaternion result;
		result.w = cos( newAlpha );
		float mult = sin( newAlpha ) / sin( alpha );
		result.x = q.x * mult; 
		result.y = q.y * mult;
		result.z = q.z * mult;
		return result;
	}

	//----------------------------------------------------------------------------------------------
}//namespace
