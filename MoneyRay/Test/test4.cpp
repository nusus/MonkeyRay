#include "CConfig.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#if TEST4 == ON


class CMRObject;


class CMRCopyPolicy
{
public:
	template <typename T>
	T* operator () (const T* ptr) const
	{
		/*return const_cast<T*>(ptr);*/
		std::cout << "CMRCopyPolicy template operator" << std::endl;
		return const_cast<T*>(ptr);
	}
protected:
private:
};

class CMRShallowCopy : public CMRCopyPolicy {};
class CMRObjectDepthCopy : public CMRCopyPolicy
{
public:
	CMRObject* operator()(const CMRObject* obj) const
	{
		std::cout << "CMRObjectDepthCopy operator" << std::endl;
		return const_cast<CMRObject*>(obj);
	}
};

int main(void)
{
	CMRObjectDepthCopy odc;
	CMRObject* optr = nullptr;
	odc(optr);
	getchar();
}

#endif