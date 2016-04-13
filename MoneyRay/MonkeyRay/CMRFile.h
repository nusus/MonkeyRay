#ifndef CMRFile_h__
#define CMRFile_h__
#include "CMRPrerequisites.h"
namespace MR
{
	class CMRFile
	{
	public:
		static string GetDirAux(const string& name)
		{
			string::size_type slashIndex = name.find_last_of("/");

			if (slashIndex == string::npos) {
				return string(".");
			}
			else if (slashIndex == 0) {
				return string("/");
			}
			else {
				return name.substr(0, slashIndex);
			}
		}

		static string GetFileNameAux(const string& name)
		{
			string::size_type slashIndex = name.find_last_of("/");
			return name.substr(slashIndex + 1);
		}


		static string ReadFile(const string& name)
		{
			std::ifstream in(name.c_str(), std::ios_base::in | std::ios_base::binary);
			if (!in.is_open())
			{
				CMR_STD_OUT << "can not open file " << name << CMR_STD_ENDL;
				return string();
			}
			std::istreambuf_iterator<char> beg(in), end;
			string ret(beg, end);
			in.close();
			return ret;
		}
	protected:
	private:
	};
}
#endif // CMRFile_h__
