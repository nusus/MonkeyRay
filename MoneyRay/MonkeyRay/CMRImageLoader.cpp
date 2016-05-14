#include "CMRImageLoader.h"
#include "CMRTGAImageLoader.h"

using namespace MR;

CMRImageLoader* MR::CMRImageLoader::GetImageLoader(const string& strName)
{
	if (strName.empty() || strName.size() == 0)
	{
		return nullptr;
	}
	size_t found = strName.find_first_of('.');
	if (found == string::npos)
	{
		return nullptr;
	}
	string substrName = strName.substr(found + 1, strName.size() - found);
	if (_stricmp(substrName.c_str(), "tga") == 0)
	{
		SmartPtr<CMRImageLoader> pRet = new CMRTGAImageLoader();
		return pRet.Release();
	}

	return nullptr;
}
