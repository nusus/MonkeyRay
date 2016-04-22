#include "CMRImpotedModel.h"

using namespace MR;

MR::CMRImpotedModel::CMRImpotedModel(const string& stdName) :
	m_strMeshName(CMRConfig::Instance()->s_strModelDir + stdName)
{

}

MR::CMRImpotedModel::~CMRImpotedModel()
{

}

bool MR::CMRImpotedModel::LoadMesh()
{
	bool ret = false;
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(m_strMeshName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene)
	{
		ret = _InitFromScene(pScene, CMRFile::GetFileNameAux(m_strMeshName));
	}
	else
	{
		printf("Error parsing '%s' : '%s'\n", m_strMeshName.c_str(), importer.GetErrorString());
	}

	return ret;
}

void MR::CMRImpotedModel::Render()
{
	GLuint va;
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_meshEntries.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, m_meshEntries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshEntries[i].IB);

		const unsigned int MaterialIndex = m_meshEntries[i].MaterialIndex;

		if (MaterialIndex < m_textures.size() && m_textures[MaterialIndex].Valid()) {
			m_textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElements(GL_TRIANGLES, m_meshEntries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}

bool MR::CMRImpotedModel::_InitFromScene(const aiScene* pScene, const string& strFileName)
{
	m_meshEntries.resize(pScene->mNumMeshes);
	m_textures.resize(pScene->mNumMaterials);

	for (unsigned int i = 0; i < m_meshEntries.size(); ++i)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		_InitMesh(i, paiMesh);
	}
	CMR_STD_OUT << "Load " << pScene->mNumMeshes << " Meshed in " << strFileName << CMR_STD_ENDL;
	return _InitMaterials(pScene, strFileName);
}

void MR::CMRImpotedModel::PrintVertex(std::ofstream& outfile, const Vertex& vertex, unsigned int index) const
{
	outfile << "\n print " << index << " vertex debug position in the loading mesh \n\n";
	char buffer[2048];
	int j = sprintf(buffer, "vertex position : %f, %f, %f\n", vertex.m_pos.x, vertex.m_pos.y, vertex.m_pos.z);
	j += sprintf(buffer + j, "vertex texture_coordinate : %f, %f\n", vertex.m_tex.x, vertex.m_tex.y);
	sprintf(buffer + j, "vertex normal : %f, %f, %f\n", vertex.m_normal.x, vertex.m_normal.y, vertex.m_normal.z);
	outfile << buffer;
}

void MR::CMRImpotedModel::_InitMesh(unsigned int uiIndex, const aiMesh* paiMesh)
{
	m_meshEntries[uiIndex].MaterialIndex = paiMesh->mMaterialIndex;

	vector<Vertex> vertices;
	vector<unsigned int> indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	//ofstream outFile("mesh_info.txt", ios_base::out | ios_base::app);
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(Vector3f(pPos->x, pPos->y, pPos->z),
			Vector2f(pTexCoord->x, pTexCoord->y),
			Vector3f(pNormal->x, pNormal->y, pNormal->z));

		//PrintVertex(outFile, v, i);

		vertices.push_back(v);
	}

	//outFile.close();

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	m_meshEntries[uiIndex].Init(vertices, indices);
}

bool MR::CMRImpotedModel::_InitMaterials(const aiScene* pScene, const string& Filename)
{
	bool Ret = true;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		m_textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				m_textures[i] = new CMRTexture(Path.data);

				if (!m_textures[i]->LoadTexture()) {
					printf("Error loading texture '%s'\n", Path.data);
					m_textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", Path.data);
				}
			}
		}

		//Load a white texture in case the model does not include its own texture
		if (!m_textures[i]) {
			m_textures[i] = new CMRTexture("bricks.tga");

			Ret = m_textures[i]->LoadTexture();
		}
	}
	return Ret;
}

void MR::CMRImpotedModel::DrawImplemention()
{
	Render();
}

MR::CMRImpotedModel::MeshEntry::MeshEntry()
{
	VB = INVALIDE_OGL_VALUE;
	IB = INVALIDE_OGL_VALUE;
	NumIndices = 0;
	MaterialIndex = INVALIDE_MATERIAL;
}

MR::CMRImpotedModel::MeshEntry::~MeshEntry()
{
	if (VB != INVALIDE_OGL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}
	if (IB != INVALIDE_OGL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}

void MR::CMRImpotedModel::MeshEntry::Init(const vector<Vertex>& Vertices, const vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}
