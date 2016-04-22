#ifndef CMRFile_h__
#define CMRFile_h__
#include "CMRPrerequisites.h"
namespace MR
{
	class CMRFile
	{
	public:
		static string GetDirAux(const string& name);

		static string GetFileNameAux(const string& name);

		static string ReadFile(const string& name);
	protected:
		CMRFile() {}
		CMRFile(const CMRFile&) {}
		CMRFile& operator=(const CMRFile&) { return *this; }
	private:
	};
}
#endif // CMRFile_h__
