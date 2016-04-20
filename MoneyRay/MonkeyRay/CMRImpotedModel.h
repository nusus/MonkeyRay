#ifndef CMRImpotedModel_h__
#define CMRImpotedModel_h__
#include "CMRDrawable.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CMRTexture.h"


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

}
namespace MR
{
	class CMRImpotedModel : public CMRDrawable
	{
	public:
		struct MeshEntry {
			MeshEntry();

			~MeshEntry();

			void Init(const vector<Vertex>& Vertices,
				const vector<unsigned int>& Indices);

			GLuint VB;
			GLuint IB;
			unsigned int NumIndices;
			unsigned int MaterialIndex;
		};
	public:
		CMRImpotedModel(const string& stdName);
		~CMRImpotedModel();


		bool LoadMesh();

		void Render();
	protected:

		bool _InitFromScene(const aiScene* pScene, const string& strFileName);

		//for debug
		void PrintVertex(std::ofstream& outfile, const Vertex& vertex, unsigned int index) const;

		void _InitMesh(unsigned int uiIndex, const aiMesh* paiMesh);
		bool _InitMaterials(const aiScene* pScene, const string& Filename);

		virtual void DrawImplemention() override;

		string m_strMeshName;
		vector<MeshEntry> m_meshEntries;
		vector<SmartPtr<CMRTexture> > m_textures;
	};
}
#endif // CMRImpotedModel_h__
