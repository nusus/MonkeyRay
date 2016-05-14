#ifndef CMRImportedMesh_h__
#define CMRImportedMesh_h__
#include "CMRDrawable.h"
#include "CMRImpotedModelImp.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRImportedMesh : public CMRDrawable
	{
	public:
		explicit CMRImportedMesh(string name);

		CMRImportedMesh(const CMRImportedMesh& rhs);

		CMRImportedMesh& operator=(const CMRImportedMesh& rhs);

	public:
		void LoadMesh();

		virtual void DrawImplemention(CMRProgram* program) override;

	protected:
		bool m_bLoaded;
		SmartPtr<CMRImpotedModelImp> m_spImportedMesh;
	private:
	};
}
#endif // CMRImportedMesh_h__
