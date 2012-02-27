#include "ChsVector4.h"
#include <math.h>
#include <assert.h>

namespace Chaos {
//---------------------------------------------------------------------------------------------------------------------
ChsVector4::ChsVector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){
}
//---------------------------------------------------------------------------------------------------------------------
ChsVector4::ChsVector4(){
	ChsVector4(0.0f, 0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------------------------------------------
ChsVector4::ChsVector4(const float vec[4]){
	ChsVector4(vec[0], vec[1], vec[2], vec[3]);
}
//------------------------------------------------------------------------------------------------------------
ChsVector4::ChsVector4(const ChsVector4& vec){
	ChsVector4(vec.x, vec.y, vec.z, vec.w);
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator += (const ChsVector4& vec){
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator -= (const ChsVector4& vec){
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator *= (const ChsVector4& vec){
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator *= (float scale){
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	this->w *= scale;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator /= (float scale){
	this->x /= scale;
	this->y /= scale;
	this->z /= scale;
	this->w /= scale;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
ChsVector4 ChsVector4::operator * (float scale)const{
	return ChsVector4(this->x * scale, this->y * scale, this->z * scale, this->w * scale);
}
//------------------------------------------------------------------------------------------------------------
ChsVector4 ChsVector4::operator / (float scale)const{
	assert(scale != 0);
	return ChsVector4(this->x / scale, this->y / scale, this->z / scale, this->w / scale);
}
//------------------------------------------------------------------------------------------------------------
ChsVector4&	ChsVector4::operator = (const ChsVector4 & vec){
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
	return *this;
}
//------------------------------------------------------------------------------------------------------------
float ChsVector4::length()const{
	return sqrtf(lengthSQ());
}
//------------------------------------------------------------------------------------------------------------
float ChsVector4::lengthSQ()const{
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

//------------------------------------------------------------------------------------------------------------
}//namespace
