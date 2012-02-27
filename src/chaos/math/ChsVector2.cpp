#include "ChsVector2.h"
#include <assert.h>

namespace Chaos {
//------------------------------------------------------------------------------------------
ChsVector2::ChsVector2(float _x, float _y) : x(_x), y(_y){
}
//------------------------------------------------------------------------------------------
ChsVector2::ChsVector2(){
	ChsVector2( 0.0f, 0.0f );
}
//------------------------------------------------------------------------------------------
ChsVector2::ChsVector2(const ChsVector2& vec2){
	ChsVector2(vec2.x, vec2.y);
}
//------------------------------------------------------------------------------------------
ChsVector2& ChsVector2::operator += (const ChsVector2& vec2){
	this->x += vec2.x;
	this->y += vec2.y;
	return *this;
}
//------------------------------------------------------------------------------------------
ChsVector2& ChsVector2::operator -= (const ChsVector2& vec2){		this->x -= vec2.x;
	this->y -= vec2.y;
	return *this;
}
//------------------------------------------------------------------------------------------
ChsVector2&	ChsVector2::operator *= (float scale){
	this->x *= scale;
	this->y *= scale;
	return *this;
}
//------------------------------------------------------------------------------------------
ChsVector2& ChsVector2::operator /= (float scale){
	this->x /= scale;
	this->y /= scale;
	return *this;
}
//------------------------------------------------------------------------------------------
ChsVector2 ChsVector2::operator + (const ChsVector2& vec2)const{
	return ChsVector2(this->x + vec2.x, this->y + vec2.y);
}
//------------------------------------------------------------------------------------------
ChsVector2 ChsVector2::operator - (const ChsVector2& vec2)const{
	return ChsVector2(this->x - vec2.x, this->y - vec2.y);
}
//------------------------------------------------------------------------------------------
ChsVector2 ChsVector2::operator * (float scale)const{
	return ChsVector2(this->x * scale, this->y * scale);
}
//------------------------------------------------------------------------------------------
ChsVector2	ChsVector2::operator / (float scale)const{
	assert(scale != 0);
	return ChsVector2(this->x / scale, this->y / scale);
}
//------------------------------------------------------------------------------------------
ChsVector2& ChsVector2::operator = (const ChsVector2& vec2){
	this->x = vec2.x;
	this->y = vec2.y;
	return *this;
}
//------------------------------------------------------------------------------------------
/*
 void ChsVector2::Normalize()
 {
 if( x!=0 || y!=0 )
 {
 float len = 1 / Length();
 x *= len;
 y *= len;
 }
 }
 
 ChsVector2	ChsVector2::Cross(const ChsVector2 &vec1,const ChsVector2 &vec2)
 {
 ChsVector2 result;
 result.x = vec1.y * vec2.z - vec2.y * vec1.z;
 result.y = vec1.z * vec2.x - vec2.z * vec1.x;
 result.z = vec1.x * vec2.y - vec2.x * vec1.y;
 return result;
 }
 
 float	ChsVector2::Dot(const ChsVector2 &vec1,const ChsVector2 &vec2)
 {
 return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
 }
 
 float ChsVector2::Length()
 {
 return sqrtf(LengthSQ());
 }
 
 float ChsVector2::LengthSQ()
 {
 return x * x + y * y + z * z;
 }
 */

	
//------------------------------------------------------------------------------------------
}//namespace
