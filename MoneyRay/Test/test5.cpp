#include "CConfig.h"
#if TEST5 == ON

#include "CGlobalInclude.h"
#include "CMRMesh.h"
#include "CMRApplication.h"
#include <array>
//
//template<typename T, const unsigned int N>
//struct CMRUniformDataType
//{
//	typedef T value_type;
//	const unsigned int GetSize() const
//	{
//		return N;
//	}
//	const T* GetDataPointer() const
//	{
//		return &m_val[0];
//	}
//
//	T[N] m_val;
//};

template<typename T, const size_t N, void M(int, unsigned int, const T* ) >
class CMRUniform
{
public:
	typedef T value_type[N];
public:
	CMRUniform(const std::string& strName, value_type val) :
		m_strUniformName(strName)
	{
		memcpy(m_val, val, sizeof(T) * N);
	}

	virtual void Apply()
	{
		//GLint uni_loc = glGetUniformLocation(pProgram->GetProgramObject(), m_strUniformName.c_str());
		M(1, N, m_val);
	}
protected:
	std::string m_strUniformName;
	T m_val[N];
};

void Func(int a, unsigned int b, const float* c)
{

}

typedef CMRUniform<float, 1, Func> Uniform1fv;

typedef int value_type[5];



int main(void)
{
	/*MR::CMRMesh* pMesh = new MR::CMRMesh("box.3DS");
	MR::CMRApplication app;
	app.AddMesh(pMesh);*/
	//return app.Run();
	value_type a;
	size_t sz = sizeof(a);
	return 1;
}
#endif