#include "ChsMath.h"
#include "ChsMatrix.h"
#include "ChsQuaternion.h"
#include <math.h>

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsMatrix & matrixRotationQuaternion( ChsMatrix & matrix, const ChsQuaternion & quaternion ){
		matrix._m11 = 1-2 * ( quaternion.y * quaternion.y + quaternion.z * quaternion.z );
		matrix._m12 = 2 * ( quaternion.x * quaternion.y + quaternion.w * quaternion.z );
		matrix._m13 = 2 * ( quaternion.x * quaternion.z - quaternion.w * quaternion.y );
		matrix._m14 = 0;
	
		matrix._m21 = 2 * ( quaternion.x * quaternion.y - quaternion.w * quaternion.z );
		matrix._m22 = 1- 2 * ( quaternion.x * quaternion.x + quaternion.z * quaternion.z );
		matrix._m23 = 2 * ( quaternion.z * quaternion.y + quaternion.w * quaternion.x );
		matrix._m24 = 0;

		matrix._m31 = 2 * ( quaternion.x * quaternion.z + quaternion.w * quaternion.y );
		matrix._m32 = 2 * ( quaternion.y * quaternion.z - quaternion.w * quaternion.x );
		matrix._m33 = 1- 2 * ( quaternion.x * quaternion.x + quaternion.y * quaternion.y );
		matrix._m34 = 0;

		matrix._m41 = 0;
		matrix._m42 = 0;
		matrix._m43 = 0;
		matrix._m44 = 1;

		return matrix;
	}

	//----------------------------------------------------------------------------------------------
	ChsQuaternion & quaternionRotationMatrix( ChsQuaternion & quaternion, const ChsMatrix & matrix ){
		float m11 = matrix._m11,	m12 = matrix._m12,	m13 = matrix._m13;
		float m21 = matrix._m21,	m22 = matrix._m22,	m23 = matrix._m23;
		float m31 = matrix._m31,	m32 = matrix._m32,	m33 = matrix._m33;

		float w = 0.0f, x = 0.0f, y = 0.0f, z = 0.0f;

		float fourWSquaredMinusl = m11 + m22 + m33;
		float fourXSquaredMinusl = m11 - m22 - m33;
		float fourYSquaredMinusl = m22 - m11 - m33;
		float fourZSquaredMinusl = m33 - m11 - m22;

		int biggestIndex = 0;

		float fourBiggestSquaredMinusl = fourWSquaredMinusl;

		if( fourXSquaredMinusl > fourBiggestSquaredMinusl ){
			fourBiggestSquaredMinusl = fourXSquaredMinusl;
			biggestIndex = 1;
		}
		
		if( fourYSquaredMinusl > fourBiggestSquaredMinusl ){
			fourBiggestSquaredMinusl = fourYSquaredMinusl;
			biggestIndex = 2;
		}

		if( fourZSquaredMinusl > fourBiggestSquaredMinusl ) {
			fourBiggestSquaredMinusl = fourZSquaredMinusl;
			biggestIndex = 3;
		}

		float biggestVal = sqrt( fourBiggestSquaredMinusl + 1.0f ) * 0.5f;
		float mult = 0.25f / biggestVal;
        
		switch( biggestIndex ){
		case 0:
			w = biggestVal;
			x = ( m23 - m32 ) * mult;
			y = ( m31 - m13 ) * mult;
			z = ( m12 - m21 ) * mult;
			break;
		case 1:
			x = biggestVal;
			w = ( m23 - m32 ) * mult;
			y = ( m12 + m21 ) * mult;
			z = ( m31 + m13 ) * mult;
			break;
		case 2:
			y = biggestVal;
			w = ( m31 - m13 ) * mult;
			x = ( m12 + m21 ) * mult;
			z = ( m23 + m32 ) * mult;
			break;
		case 3:
			z = biggestVal;
			w = ( m12 - m21 ) * mult;
			x = ( m31 + m13 ) * mult;
			y = ( m23 + m32 ) * mult;
			break;
		}
	
		quaternion.w = w;
		quaternion.x = x;
		quaternion.y = y;
		quaternion.z = z;
		return quaternion;
	}
	
	//----------------------------------------------------------------------------------------------
	
}//namespace
