#ifndef Reflection_h__
#define Reflection_h__
#include "CMRRef.h"
namespace MR
{
	class ObjectFactory
	{
	public:
		typedef CMRRef* (*CreateClass)(void);


	public:
		static ObjectFactory* Instance()
		{
			static ObjectFactory s_objectFactory;
			return &s_objectFactory;
		}

		CMRRef* GetClassByName(const string& name)
		{
			auto itr = m_classMap.find(name);
			if (itr != m_classMap.end())
			{
				CreateClass pMethod = itr->second;
				return pMethod();
			}
			return nullptr;
		}

		void RegisterClass(const string& name, CreateClass method)
		{
			m_classMap.insert(std::make_pair(name, method));
		}


	protected:
		ObjectFactory() {}
		ObjectFactory(const ObjectFactory& rhs) {}
		ObjectFactory& operator=(const ObjectFactory& rhs) {}


	protected:
		map<string, CreateClass> m_classMap;
	};


	class DynamicClass
	{
	public:
		DynamicClass(const string& name, ObjectFactory::CreateClass method)
		{
			ObjectFactory::Instance()->RegisterClass(name, method);
		}
	};

#define DELCARE_CLASS(className) \
string className##Name; \
static DynamicClass* ms_##className##dc;

#define IMPLEMENT_CLASS(className) \
DynamicClass* className::ms_className##dc = new DynamicClass(#className, className::CreateInstance);

	template<typename T>
	class TemplateReflectionClass  : public CMRRef
	{
	public:
		typedef T value_type;


	public:
		static CMRRef* CreateInstance()
		{
			return new value_type;
		}
	};

}
#endif // Reflection_h__
