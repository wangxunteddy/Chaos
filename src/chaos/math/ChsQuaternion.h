#ifndef _CHS_QUATERNION_H
#define _CHS_QUATERNION_H
#pragma once

#include <boost/operators.hpp>

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	class ChsVector3;

	//----------------------------------------------------------------------------------------------
	class ChsQuaternion : boost::multipliable<ChsQuaternion> {
	public:
		float w;
		float x;
		float y;
		float z;

		ChsQuaternion( void );
		ChsQuaternion( const float quat[4] );
		ChsQuaternion( float x, float y, float z, float w );

		ChsQuaternion operator *= ( const ChsQuaternion & quat );
		ChsQuaternion & operator = ( const ChsQuaternion & quat );

		void normailize( void );
		void identity( void );
						
		static const ChsQuaternion quaternionIndentity;
		static ChsQuaternion rotationVector( const ChsVector3 & from, const ChsVector3 & to );
		//点乘
		static float dot( const ChsQuaternion & quat1, const ChsQuaternion & quat2 );
		//插值
		static ChsQuaternion slerp( const ChsQuaternion & quat1, const ChsQuaternion & quat2, float t );
		//共轭
		static ChsQuaternion conjugate( const ChsQuaternion & quat );
		//四元素幂
		static ChsQuaternion pow( const ChsQuaternion & quat, float exponent );
	};

	//----------------------------------------------------------------------------------------------

}//namespace
#endif	//_CHS_QUATERNION_H
