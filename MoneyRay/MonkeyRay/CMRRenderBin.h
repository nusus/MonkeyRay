#ifndef CMRRenderBin_h__
#define CMRRenderBin_h__
#include "CMRRef.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRRenderLeaf;
	class CMRShader;
	class CMRProgram;
	class CMRRenderBin : public CMRRef
	{
	public:
		typedef vector<CMRRenderLeaf*> RenderLeafList;
		typedef vector<SmartPtr<CMRRenderBin>> RenderBinList;
	public:
		CMRRenderBin();
	public:
		void AddRenderBin(CMRRenderBin* pBin);

		unsigned int GetNumRenderBinChildren() const;

		CMRRenderBin* GetRenderBinChild(unsigned int index) const;

		void AddRenderLeaf(CMRRenderLeaf* pLeaf);

		unsigned int GetNumRenderLeaf() const;

		CMRRenderLeaf* GetRenderLeaf(unsigned int index) const;

		virtual void Draw() const;

		void AddShader(CMRShader* pShader);
	protected:

		RenderLeafList m_renderLeafList;
		RenderBinList m_renderBinChildren;
		SmartPtr<CMRProgram> m_spProgram;
	};
}
#endif // CMRRenderBin_h__
