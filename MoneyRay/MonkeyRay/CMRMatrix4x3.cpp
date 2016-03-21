#include "CMRMatrix4x3.h"
#include "CMRVector3.h"
#include "CMRRotationMatrix.h"
#include "CMRMathUtil.h"
#include "CMRQuaternion.h"

#include <assert.h>

void CMRMatrix4x3::Identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = 0.0f; ty = 0.0f; tz = 1.0f;
}

void CMRMatrix4x3::ZeroTranslation()
{
	tx = ty = tz = 0.0f;
}

void CMRMatrix4x3::SetTranslation(const CMRVector3 & v)
{
	tx = v.x;
	ty = v.y;
	tz = v.z;
}

void CMRMatrix4x3::SetupTranslation(const CMRVector3 & v)
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = v.x;ty = v.y;tz = v.z;
}

void CMRMatrix4x3::SetupLocalToParent(const CMRVector3 & v, const CMREulerAngles & e)
{
	CMRRotationMatrix orientMatrix;
	orientMatrix.Setup(e);
	SetupLocalToParent(v, orientMatrix);
}

void CMRMatrix4x3::SetupLocalToParent(const CMRVector3 & v, const CMRRotationMatrix & r)
{
	m11 = r.m11; m12 = r.m21; m13 = r.m31;
	m21 = r.m12; m22 = r.m22; m23 = r.m32;
	m31 = r.m13; m32 = r.m23; m33 = r.m33;

	tx = v.x; ty = v.y; tz = v.z;
}

void CMRMatrix4x3::SetupParentToLocal(const CMRVector3 & v, const CMREulerAngles & e)
{
	CMRRotationMatrix orientMatrix;
	orientMatrix.Setup(e);
	SetupParentToLocal(v, orientMatrix);
}

void CMRMatrix4x3::SetupParentToLocal(const CMRVector3 & v, const CMRRotationMatrix & r)
{
	m11 = r.m11; m12 = r.m12; m13 = r.m13;
	m21 = r.m21; m22 = r.m22; m23 = r.m23;
	m31 = r.m31; m32 = r.m32; m33 = r.m33;

	tx = v.x; ty = v.y; tz = v.z;
}

void CMRMatrix4x3::SetupRotate(int axis, float theta)
{
	float  s, c;
	SinCos(&s, &c, theta);

	switch (axis)
	{
	case 1:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m31 = 0.0f; m32 = -s; m22 = c;
		break;
	case 2:
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = 0.0f; m22 = c;
		break;
	case 3:
		m11 = c; m12 =s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m22 = 1.0f;
		break;
	default:
		assert(false);
		break;
	}
	tx = ty = tz = 0.0f; 
}

void CMRMatrix4x3::SetupRotate(const CMRVector3 & v, float theta)
{
	assert(fabs(v*v - 1.0f) < 0.01f);

	float s, c;
	SinCos(&s, &c, theta);

	//计算公式所需公共因子
	float factor = 1.0f - c;
	float fx = factor*v.x;
	float fy = factor*v.y;
	float fz = factor*v.z;

	m11 = fx*v.x + c;
	m12 = fx*v.y + v.z*s;
	m13 = fx*v.z - v.y*s;

	m21 = fy*v.x - v.z*s;
	m22 = fy*v.y + c;
	m23 = fy*v.z + v.x*s;

	m31 = fz*v.x + v.y*s;
	m32 = fz*v.y - v.x*s;
	m33 = fz*v.z + c;

	tx = ty = tz = 0.0f;
}

void CMRMatrix4x3::FromQuaternion(const CMRQuaternion & q)
{
	//计算一些公用因子
	float ww = 2.0f*q.w;
	float xx = 2.0f*q.x;
	float yy = 2.0f*q.y;
	float zz = 2.0f*q.z;

	m11 = 1.0f - yy*q.y - zz*q.z;
	m12 = xx*q.y + ww*q.z;
	m13 = xx*q.z - ww*q.x;

	m21 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m23 = yy*q.z + ww*q.x;

	m31 = xx*q.z + ww*q.y;
	m32 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;

	tx = ty = tz = 0.0f;
}

void CMRMatrix4x3::SetupScale(const CMRVector3 & v)
{
	m11 = v.x; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = v.y; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = v.z;

	tx = ty = tz = 0.0f;
}

void CMRMatrix4x3::SetupScaleAlongAxis(const CMRVector3 & v, float k)
{
	assert(fabs(v*v - 1.0f) < 0.01f);

	//计算一些公用的因子
	float f = k - 1;
	float fx = f*v.x;
	float fy = f*v.y;
	float fz = f*v.z;

	m11 = fx*v.x + 1.0f;
	m22 = fy*v.y + 1.0f;
	m33 = fz*v.z + 1.0f;

	m12 = m21 = fx*v.y;
	m13 = m31 = fx*v.z;
	m23 = m32 = fy*v.z;

	tx = ty = tz = 0;
}

void CMRMatrix4x3::SetupShear(int axis, float s, float t)
{
	switch (axis)
	{
	case 1:
		m11 = 1.0f; m12 = s; m13 =t ;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 2:
		m11 = 1.0f; m12 =0.0f ; m13 = 0.0f;
		m21 = s; m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 3:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = t; m33 = 1.0f;
		break;
	default:
		assert(false);
		break;
	}
}

void CMRMatrix4x3::SetupProject(const CMRVector3 & v)
{
	assert(fabs(v*v - 1.0f) < 0.01f);
	
	m11 = 1 - v.x*v.x;
	m22 = 1 - v.y*v.y;
	m33 = 1 - v.z*v.z;

	m12 = m21 = -v.x*v.y;
	m13 = m31 = -v.x*v.z;
	m23 = m32 = -v.y*v.z;

	tx = ty = tz = 0.0f;

}

void CMRMatrix4x3::SetupReflect(int axis, float k)
{
	switch (axis)
	{
	case 1://沿x=k平面反射
		m11 = -1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 2.0f*k;
		ty = 0.0f;
		tz = 0.0f;
		break;
	case 2://y=k反射
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = -1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 0.0f;
		ty = 2.0f*k;
		tz = 0.0f;
		break;
	case 3://z=k
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = -1.0f;
		tx = 0.0f;
		ty = 0.0f;
		tz = 2.0f*k;
		break;
	default:
		assert(false);
		break;
	}
}

void CMRMatrix4x3::SetupReflect(const CMRVector3 & v)
{
	assert(fabs(v*v - 1.0f) < 0.01f);

	float fx = -2.0f*v.x;
	float fy = -2.0f*v.y;
	float fz = -2.0f*v.z;
	
	m11 = 1.0f + fx*v.x;
	m22 = 1.0f + fy*v.y;
	m33 = 1.0f + fz*v.z;

	m12 = m21 = fx*v.y;
	m13 = m31 = fx*v.z;
	m23 = m32 = fy*v.z;

	tx = ty = tz = 0.0f;
}
