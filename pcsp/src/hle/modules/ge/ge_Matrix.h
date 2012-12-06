#pragma once

#include "stdafx.h"

class ge_Matrix43
{
public:
	ge_Matrix43(float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
                float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
                float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f,
                float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f)
	{
		mData[ 0] = m11;
		mData[ 1] = m12;
		mData[ 2] = m13;

		mData[ 3] = m21;
		mData[ 4] = m22;
		mData[ 5] = m23;
		
		mData[ 6] = m31;
		mData[ 7] = m32;
		mData[ 8] = m33;
		
		mData[ 9] = m41;
		mData[10] = m42;
		mData[11] = m43;
	}

	void DeepCopyFrom(ge_Matrix43 &inMatrix)
	{
		memcpy(mData, inMatrix.mData, sizeof(float)*12);
	}

public:
	float mData[12];
};

class ge_Matrix44
{
public:
	ge_Matrix44(float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
				float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
				float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
				float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f)
	{
		mData[ 0] = m11;
		mData[ 1] = m12;
		mData[ 2] = m13;
		mData[ 3] = m14;

		mData[ 4] = m21;
		mData[ 5] = m22;
		mData[ 6] = m23;
		mData[ 7] = m24;

		mData[ 8] = m31;
		mData[ 9] = m32;
		mData[10] = m33;
		mData[11] = m34;

		mData[12] = m41;
		mData[13] = m42;
		mData[14] = m43;
		mData[15] = m44;
	}

	ge_Matrix44(ge_Matrix43 *inMatrix)
	{
		mData[ 0] = inMatrix->mData[ 0];
		mData[ 1] = inMatrix->mData[ 1];
		mData[ 2] = inMatrix->mData[ 2];
		mData[ 3] = 0.0f; 

		mData[ 4] = inMatrix->mData[ 3];
		mData[ 5] = inMatrix->mData[ 4];
		mData[ 6] = inMatrix->mData[ 5];
		mData[ 7] = 0.0f; 

		mData[ 8] = inMatrix->mData[ 6];
		mData[ 9] = inMatrix->mData[ 7];
		mData[10] = inMatrix->mData[ 8];
		mData[11] = 0.0f;  

		mData[12] = inMatrix->mData[ 9]; 
		mData[13] = inMatrix->mData[10];
		mData[14] = inMatrix->mData[11];
		mData[15] = 1.0f;
	}

	void DeepCopyFrom(ge_Matrix44 &inMatrix)
	{
		memcpy(mData, inMatrix.mData, sizeof(float)*16);
	}

	inline void SetScale(float inX, float inY, float inZ)
    {
		mData[ 0] = inX;
		mData[ 5] = inY;
		mData[10] = inZ;
    }

public:
	float mData[16];
};