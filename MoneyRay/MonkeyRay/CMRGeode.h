#ifndef CMRGeode_h__
#define CMRGeode_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
namespace MR
{
	class CMRGeode : public CMRGroup
	{
	public:
		void SetMVPWMatrix(const vmath::mat4& matrix)
		{
			m_mvpwMatrix = matrix;
		}

		vmath::mat4 GetMVPWMatrix() const
		{
			return m_mvpwMatrix;
		}

	protected:
		vmath::mat4 m_mvpwMatrix;
	private:
	};	 
}
#endif // CMRGeode_h__
