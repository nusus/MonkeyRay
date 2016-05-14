#include "CMRImportedMesh.h"
#include "CMRUniform.h"
#include "SmartPtr.h"

using namespace MR;

MR::CMRImportedMesh& MR::CMRImportedMesh::operator=(const CMRImportedMesh& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	m_spImportedMesh = rhs.m_spImportedMesh;
	m_bLoaded = rhs.m_bLoaded;
	return *this;
}

MR::CMRImportedMesh::CMRImportedMesh(const CMRImportedMesh& rhs) :m_spImportedMesh(rhs.m_spImportedMesh),
m_bLoaded(rhs.m_bLoaded)
{

}

MR::CMRImportedMesh::CMRImportedMesh(string name) :m_spImportedMesh(new CMRImpotedModelImp(name)),
m_bLoaded(false)
{

}

void MR::CMRImportedMesh::LoadMesh()
{
	m_bLoaded = m_spImportedMesh->LoadMesh();
}

void MR::CMRImportedMesh::DrawImplemention(CMRProgram* program)
{
	if (!m_bLoaded)
	{
		LoadMesh();
	}
	Update();
	_ApplyUniform(program);
	m_spImportedMesh->Render();
}
