#ifndef _CHS_MATH_H
#define _CHS_MATH_H
#pragma once

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	static const float CHAOS_PI = 3.141592654f;

	//----------------------------------------------------------------------------------------------
	inline float degree2Radian( float degree ){
		return CHAOS_PI * degree / 180.0f;
	}

	//----------------------------------------------------------------------------------------------
	class ChsMatrix;
	class ChsQuaternion;

	//----------------------------------------------------------------------------------------------
	ChsMatrix & matrixRotationQuaternion( ChsMatrix & matrix, const ChsQuaternion & quaternion  );
	ChsQuaternion & quaternionRotationMatrix( ChsQuaternion & quaternion, const ChsMatrix & matrix );

	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_MATH_H
