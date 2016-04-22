#ifndef CMRMesh_h__
#define CMRMesh_h__

#include "CGlobalInclude.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdio.h>
#include <vector>
#include "CMRTexture.h"
#include <fstream>

#define INVALIDE_OGL_VALUE 0xffffffff
#define INVALIDE_MATERIAL 0xFFFFFFFF

namespace MR
{
	struct Vector2i
	{
		int x;
		int y;
	};

	struct Vector2f
	{
		float x;
		float y;

		Vector2f()
		{
		}

		Vector2f(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
	};


	struct Vector3f
	{
		float x;
		float y;
		float z;

		Vector3f() {}

		Vector3f(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		Vector3f(const float* pFloat)
		{
			x = pFloat[0];
			y = pFloat[0];
			z = pFloat[0];
		}

		Vector3f(float f)
		{
			x = y = z = f;
		}

		Vector3f& operator+=(const Vector3f& r)
		{
			x += r.x;
			y += r.y;
			z += r.z;

			return *this;
		}

		Vector3f& operator-=(const Vector3f& r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;

			return *this;
		}

		Vector3f& operator*=(float f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		operator const float*() const
		{
			return &(x);
		}


		Vector3f Cross(const Vector3f& v) const;

		Vector3f& Normalize();

		void Rotate(float Angle, const Vector3f& Axis);

		void Print() const
		{
			printf("(%.02f, %.02f, %.02f)", x, y, z);
		}
	};


	struct Vector4f
	{
		float x;
		float y;
		float z;
		float w;

		Vector4f()
		{
		}

		Vector4f(float _x, float _y, float _z, float _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		void Print(bool endl = true) const
		{
			printf("(%.02f, %.02f, %.02f, %.02f)", x, y, z, w);

			if (endl) {
				printf("\n");
			}
		}

		Vector3f to3f() const
		{
			Vector3f v(x, y, z);
			return v;
		}
	};



	inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
	{
		Vector3f Ret(l.x + r.x,
			l.y + r.y,
			l.z + r.z);

		return Ret;
	}

	inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
	{
		Vector3f Ret(l.x - r.x,
			l.y - r.y,
			l.z - r.z);

		return Ret;
	}

	inline Vector3f operator*(const Vector3f& l, float f)
	{
		Vector3f Ret(l.x * f,
			l.y * f,
			l.z * f);

		return Ret;
	}


	inline Vector4f operator/(const Vector4f& l, float f)
	{
		Vector4f Ret(l.x / f,
			l.y / f,
			l.z / f,
			l.w / f);

		return Ret;
	}
	struct Vertex
	{
		Vector3f m_pos;
		Vector2f m_tex;
		Vector3f m_normal;

		Vertex() {}

		Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
		{
			m_pos = pos;
			m_tex = tex;
			m_normal = normal;
		}
	};


	class CMRMesh
	{
	public:
		struct MeshEntry {
			MeshEntry()
			{
				VB = INVALIDE_OGL_VALUE;
				IB = INVALIDE_OGL_VALUE;
				NumIndices = 0;
				MaterialIndex = INVALIDE_MATERIAL;
			}

			~MeshEntry()
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

			void Init(const std::vector<Vertex>& Vertices,
				const std::vector<unsigned int>& Indices)
			{
				NumIndices = Indices.size();

				glGenBuffers(1, &VB);
				glBindBuffer(GL_ARRAY_BUFFER, VB);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

				glGenBuffers(1, &IB);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
			}

			GLuint VB;
			GLuint IB;
			unsigned int NumIndices;
			unsigned int MaterialIndex;
		};
	public:
		CMRMesh(const std::string& stdName):
			m_strMeshName(MR::CMRConfig::Instance()->s_strModelDir + stdName)
		{

		}
		~CMRMesh()
		{
			this->Clear();
		}


		bool LoadMesh()
		{
			Clear();

			bool ret = false;
			Assimp::Importer importer;
			const aiScene* pScene = importer.ReadFile(m_strMeshName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

			if (pScene)
			{
				ret = _InitFromScene(pScene, GetFileNameAux(m_strMeshName));
			}
			else
			{
				printf("Error parsing '%s' : '%s'\n", m_strMeshName.c_str(), importer.GetErrorString());
			}

			return ret;
		}

		void Render()
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

				if (MaterialIndex < m_textures.size() && m_textures[MaterialIndex]) {
					m_textures[MaterialIndex]->Bind(GL_TEXTURE0);
				}

				glDrawElements(GL_TRIANGLES, m_meshEntries[i].NumIndices, GL_UNSIGNED_INT, 0);
			}

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			glBindVertexArray(0);
		}
	protected:

		bool _InitFromScene(const aiScene* pScene, const std::string& strFileName)
		{
			m_meshEntries.resize(pScene->mNumMeshes);
			m_textures.resize(pScene->mNumMaterials);

			for (unsigned int i = 0; i < m_meshEntries.size(); ++i)
			{
				const aiMesh* paiMesh = pScene->mMeshes[i];
				_InitMesh(i, paiMesh);
			}
			std::cout << "Load " << pScene->mNumMeshes << " Meshed in " << strFileName << std::endl;
			return _InitMaterials(pScene, strFileName);
		}

		//for debug
		void PrintVertex(std::ofstream& outfile,  const Vertex& vertex, unsigned int index) const
		{
			outfile << "\n print "<<index<<" vertex debug position in the loading mesh \n\n";
			char buffer[2048];
			int j =sprintf(buffer, "vertex position : %f, %f, %f\n", vertex.m_pos.x, vertex.m_pos.y, vertex.m_pos.z);
			j += sprintf(buffer+j ,"vertex texture_coordinate : %f, %f\n", vertex.m_tex.x, vertex.m_tex.y);
			sprintf(buffer + j ,"vertex normal : %f, %f, %f\n", vertex.m_normal.x, vertex.m_normal.y, vertex.m_normal.z);
			outfile << buffer;
		}

		void _InitMesh(unsigned int uiIndex, const aiMesh* paiMesh)
		{
			m_meshEntries[uiIndex].MaterialIndex = paiMesh->mMaterialIndex;

			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

			//std::ofstream outFile("mesh_info.txt", std::ios_base::out | std::ios_base::app);
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
		bool _InitMaterials(const aiScene* pScene, const std::string& Filename)
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
							delete m_textures[i];
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
		void Clear()
		{
			for (auto pTexture : m_textures)
			{
				if (pTexture)
				{
					delete pTexture;
					pTexture = nullptr;
				}
			}
		}
		std::string m_strMeshName;
		std::vector<MeshEntry> m_meshEntries;
		std::vector<CMRTexture*> m_textures;
	};
}
#endif // CMRMesh_h__
