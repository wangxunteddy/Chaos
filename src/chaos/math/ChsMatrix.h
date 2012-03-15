#ifndef	_CHS_MATRIX_H
#define	_CHS_MATRIX_H
#pragma once

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	class ChsVector3;

	//----------------------------------------------------------------------------------------------
	class ChsMatrix {
	public:
		union{
			float m4x4[4][4];
			float m[16];
			struct{
				float _m11,_m12,_m13,_m14;
				float _m21,_m22,_m23,_m24;
				float _m31,_m32,_m33,_m34;
				float _m41,_m42,_m43,_m44;
			};
		};

		ChsMatrix( void );
		ChsMatrix( const float [16] );
		ChsMatrix( const ChsMatrix & m );
		ChsMatrix( float _11, float _12, float _13, float _14,
					float _21, float _22, float _23, float _24,
					float _31, float _32, float _33, float _34,
					float _41, float _42, float _43, float _44 );

		// binary operators
		//ChsMatrix			operator * ( ChsMatrix & a,ChsMatrix &b);
		//ChsMatrix&		operator *= ( ChsMatrix& );
		ChsMatrix & operator = ( const ChsMatrix & matrix );
		inline float * getArrary( void );

		void lookAt( const ChsVector3 & eye, const ChsVector3 & at, const ChsVector3 & up );
		void ortho( float w, float h, float zn, float zf );
		void perspective( float fovy, float aspect, float zn, float zf );
			
		void identity( void );
		void inverse( void );
		ChsVector3 * transformCoord( ChsVector3 * destinaion, const ChsVector3 * origin );
		void translation( float x, float y, float z );
			
			

		void rotateX( float theta );
		void rotateY( float theta );
		void rotateZ( float theta );

		void rotateXTo( float theta );
		void rotateYTo( float theta );
		void rotateZTo( float theta );
			
		ChsMatrix operator * ( ChsMatrix & m );
	};

	//----------------------------------------------------------------------------------------------
	ChsMatrix * multiply( ChsMatrix * out, const ChsMatrix & matrix1, const ChsMatrix & matrix2 );
	ChsMatrix & operator *= ( ChsMatrix & a, ChsMatrix & b );

	//----------------------------------------------------------------------------------------------
	inline float * ChsMatrix::getArrary( void ){
		return this->m;
	};

	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_MATRIX_H
