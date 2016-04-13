#ifndef CMRStateSet_h__
#define CMRStateSet_h__
#include "CMRPrerequisites.h"
#include "CMRShader.h"
#include "vmath.h"
#include "CMRRef.h"
#include "SmartPtr.h"

namespace MR
{
	class CMRStateSet : public CMRRef
	{
	public:
		CMRStateSet() {}

		void SetMatrix(const vmath::mat4& matrix)
		{
			m_matrix = matrix;
		}

		void SetShader(CMRShader* pShader)
		{
			m_spShader = pShader;
		}

		vmath::mat4 GetMatrix() const
		{
			return m_matrix;
		}

		CMRShader* GetShader() const
		{
			return m_spShader.Get();
		}
	protected:
		vmath::mat4 m_matrix;
		SmartPtr<CMRShader> m_spShader;		
	};
}

#endif // CMRStateSet_h__
