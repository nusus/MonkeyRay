#ifndef CMRImageLoader_h__
#define CMRImageLoader_h__

#include <string>
namespace MR
{
	std::string GetDirAux(const std::string& name)
	{
		std::string::size_type slashIndex = name.find_last_of("/");

		if (slashIndex == std::string::npos) {
			return std::string(".");
		}
		else if (slashIndex == 0) {
			return std::string("/");
		}
		else {
			return name.substr(0, slashIndex);
		}
	}

	std::string GetFileNameAux(const std::string& name)
	{
		std::string::size_type slashIndex = name.find_last_of("/");
		return name.substr(slashIndex + 1);
	}

	struct ImageEntity
	{
		GLint width;
		GLint height;
		GLint components;
		GLenum format;
		void* data;
	};

	class CMRImageLoader
	{
	public:
		explicit CMRImageLoader(const std::string& name) :
			m_strSuffixName(name)
		{

		}
		virtual ImageEntity LoadImage(const std::string& name) = 0;
	protected:
		std::string m_strSuffixName;
	};
}
#endif // CMRImageLoader_h__
