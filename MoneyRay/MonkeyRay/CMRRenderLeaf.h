#ifndef CMRRenderLeaf_h__
#define CMRRenderLeaf_h__

#include "CMRRef.h"
#include "vmath.h"
#include "SmartPtr.h"
#include "CMRDrawable.h"
namespace MR
{
	class CMRRenderLeaf : public CMRRef
	{
	public:
		CMRRenderLeaf(const vmath::mat4& matrix, CMRDrawable* pDrawable);

		void SetMVPWMatrix(const vmath::mat4& matrix);

		vmath::mat4 GetMVPWMatrix() const;

		void SetDrawable(CMRDrawable* pDrawable);

		CMRDrawable* GetDrawable() const;

		void Draw();
	protected:
		vmath::mat4 m_mvpwMatrix;
		SmartPtr<CMRDrawable> m_spDrawable;
	};
}
#endif // CMRRenderLeaf_h__
