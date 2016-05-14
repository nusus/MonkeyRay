#ifndef CMRDrawable_h__
#define CMRDrawable_h__
#include "CMRNode.h"
#include "CMRShader.h"
#include "CMRNodeVisitor.h"
#include "CMRProgram.h"
#include "CMRUniform.h"
#include "CMRTimer.h"
namespace MR
{
	class CMRDrawable : public CMRNode
	{
	public:
		typedef vector<SmartPtr<CMRUniformRef> > UniformList;


	public:
		CMRDrawable();
		CMRDrawable(const CMRDrawable& rhs);
		CMRDrawable& operator=(const CMRDrawable& rhs);
	public:
		void Draw(CMRProgram* program);

		virtual void DrawImplemention(CMRProgram* program);

		void SetMVPWMatrix(const vmath::mat4& matrix);

		vmath::mat4 GetMVPWMatrix() const;

		CMRShader::ShaderSet GetShaderSet() const;

		void AddShader(CMRShader* pShader);
		template<typename T>
		void AddShader(const SmartPtr<T>& spShader) { AddShader(spShader.Get()); }

		virtual void Accept(CMRNodeVisitor& nv) override { nv.Apply(*this); }
		virtual void Ascend(CMRNodeVisitor& nv) override;
		virtual void Traverse(CMRNodeVisitor& nv) override;

		void AddUniform(CMRUniformRef* pUniform);
		template<typename T>
		void AddUniform(const SmartPtr<T>& spUniform) { AddUniform(spUniform.Get()); }

		virtual void Update();

	protected:
		virtual ~CMRDrawable();


	protected:
		void _ApplyUniform(CMRProgram* program);


	protected:
		vmath::mat4 m_mvpwMatrix;
		CMRShader::ShaderSet m_shaderSet;
		UniformList m_uniformList;
	};
}
#endif // CMRDrawable_h__
