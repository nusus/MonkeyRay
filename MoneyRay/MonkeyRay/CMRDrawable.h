#ifndef CMRDrawable_h__
#define CMRDrawable_h__
#include "CMRNode.h"
#include "CMRShader.h"
namespace MR
{
	class CMRDrawable : public CMRNode
	{
	public:
		CMRDrawable();
		CMRDrawable(const CMRDrawable& rhs);
		CMRDrawable& operator=(const CMRDrawable& rhs);
	public:
		void Draw();

		virtual void DrawImplemention();

		void SetMVPWMatrix(const vmath::mat4& matrix);

		vmath::mat4 GetMVPWMatrix() const;

		CMRShader::ShaderSet GetShaderSet() const;

		void AddShader(CMRShader* pShader);


	protected:
		virtual ~CMRDrawable();


	protected:
		vmath::mat4 m_mvpwMatrix;
		CMRShader::ShaderSet m_shaderSet;
	};
}
#endif // CMRDrawable_h__
