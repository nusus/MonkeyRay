#ifndef CMRCamera_h__
#define CMRCamera_h__

#include "vmath.h"
#include "CMRMesh.h"
#include <iostream>


namespace MR
{
	class CMRCamera
	{
	public:
		CMRCamera():
			m_bInit(false)
		{
		}

		~CMRCamera()
		{
		}

		virtual void Init()
		{
			
		}

		

		virtual void Update(unsigned int uiDeltaFrameNum)
		{
			//m_matModelViewMatrix *= vmath::rotate(0.0f, (float)uiDeltaFrameNum, 0.0f);
		}

		virtual void LookAt(const vmath::vecN<float, 3>& eye, const vmath::vecN<float, 3>& center, const vmath::vecN<float, 3>& up)
		{
			m_matModelViewMatrix = vmath::lookat(eye, center, up);
		}

		vmath::mat4 GetModelViewMatrix() const
		{
			return m_matModelViewMatrix;
		}

		void SetProjectionMatrix(const double fvoy, const double width, const double height, const double near, const double far)
		{
			m_matProjectionMatrix = vmath::perspective((float)fvoy, (float)(width / height), (float)near, (float)far);
		}

		vmath::mat4 GetProjectionMatrix() const
		{
			return m_matProjectionMatrix;
		}
	protected:
		bool m_bInit;
		vmath::mat4 m_matModelViewMatrix;
		vmath::mat4 m_matProjectionMatrix;
		
	};
}
#endif // CMRCamera_h__
