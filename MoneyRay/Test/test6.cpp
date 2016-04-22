#include "CConfig.h"
#if TEST6 == ON
#include "vmath.h"
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class CMRTemplateSingletonCache
{
public:
	typedef T value_type;
public:
	CMRTemplateSingletonCache() {}
	inline void Add(value_type* ptr)
	{
		m_cache.push_back(ptr);
	}

	inline void Remove(value_type* ptr)
	{
		m_cache.erase(std::remove(m_cache.begin(), m_cache.end(), ptr), m_cache.end());
	}

	template<typename U>
	inline value_type* Get(U* ptr)
	{
		static_assert(false, "Get Method must be specialized");
		return nullptr;
	}
public:
	typedef vector<value_type*> Cache;
	Cache m_cache;
};

struct A
{
	
};

class  ASingletonCache : public CMRTemplateSingletonCache<A>
{
public:
	inline value_type* Get(A* ptr)
	{
		return nullptr;
	}

protected:
private:
};

int main(void)
{
	ASingletonCache a;
	A* ptr = new A;
	a.Get(ptr);
	return 1;
}
#endif