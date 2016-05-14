#ifndef CMRSingleton_h__
#define CMRSingleton_h__
#include "CMRPrerequisites.h"
namespace MR
{
	template<typename T>
	class TMRSingleton
	{
	public:
		static T* Instance() 
		{
			static T s_instance;
			return &s_instance;
		}

		virtual ~TMRSingleton() {}


	protected:
		TMRSingleton() {}
		TMRSingleton(const TMRSingleton& rhs) {}
		TMRSingleton& operator=(const TMRSingleton& rhs) { return *this; }
	};


	template<typename T>
	class TMRSingletonCache
	{
	public:
		typedef T value_type;
		typedef vector<value_type*> Cache;


	public:
		TMRSingletonCache() : m_cache() {}
		virtual ~TMRSingletonCache() {}


	public:
		inline void Add(value_type* ptr)
		{
			m_cache.push_back(ptr);
		}

		inline void Remove(value_type* ptr)
		{
			m_cache.erase(std::remove(m_cache.begin(), m_cache.end(), ptr), m_cache.end());
		}

		//template<typename U>
		//inline value_type* Get(U* ptr)
		//{
		//	static_assert(false, "Get Method must be specialized");
		//	return nullptr;
		//}


	public:
		Cache m_cache;


	protected:
		TMRSingletonCache(const TMRSingletonCache& rhs) {}
		TMRSingletonCache& operator=(const TMRSingletonCache& rhs) { return *this; }
	};
}
#endif // CMRSingleton_h__
