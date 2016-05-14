#ifndef CMRConfig_h__
#define CMRConfig_h__

#include <string>
namespace MR
{
#if MR_REAL_PRECISION == MR_SINGLE_PRECISION
	typedef float real;
#else
	typedef double real;
#endif

#if MR_REAL_STRING_TYPE == MR_USE_STRING
	typedef std::string string;
#else
	typedef std::wstring string;
#endif

}


namespace MR
{
	class CMRConfig
	{
	public:
		static const CMRConfig* Instance()
		{
			static CMRConfig s_kConfig;
			return &s_kConfig;
		}
		~CMRConfig() {}

		const string s_strResourceRoot;
		const string s_strLogDir;
		const string s_strModelDir;
		const string s_strTextureDir;
		const string s_strShaderDir;
	protected:
		CMRConfig() :
			s_strResourceRoot("D:/VSWorkspace/VS2015Workspace/MonkeyRay/MoneyRay/Resource"),
			s_strLogDir(s_strResourceRoot + "/logs/"),
			s_strModelDir(s_strResourceRoot + "/models/"),
			s_strTextureDir(s_strResourceRoot + "/textures/"),
			s_strShaderDir(s_strResourceRoot + "/shaders/")
		{

		}
		CMRConfig(const CMRConfig& config) = delete;
		CMRConfig& operator=(const CMRConfig& config) = delete;
	};
}

#endif // CMRConfig_h__
