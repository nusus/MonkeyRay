#ifndef CMRTemplateMatrix_h__
#define CMRTemplateMatrix_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
namespace MR
{
	template<typename T, const size_t N, const size_t M>
	class CMRTemplateMatrix
	{
	public:
	protected:
	private:
	};

	typedef CMRTemplateMatrix<double, 4, 4> CMRMatrix4d;
	class CMRRefMatrix : public CMRRef, public CMRMatrix4d
	{
	public:
	protected:
	private:
	};
}
#endif // CMRTemplateMatrix_h__
