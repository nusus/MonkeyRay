#ifndef CGlobalInclude_h__
#define CGlobalInclude_h__

#include <string>
#include <iostream>
#include <assert.h>

#include <glew.h>
#include <glfw3.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "vmath.h"

namespace MR
{
	using namespace std;
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
			s_strResourceRoot("F:/VSWorkspace/VS2015Workspace/MonkeyRay/MoneyRay/Resource"),
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
#endif // CGlobalInclude_h__
