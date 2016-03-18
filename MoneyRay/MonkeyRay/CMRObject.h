#ifndef CMRObject_h__
#define CMRObject_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRCopyPolicy.h"

namespace MR
{
	//forward declare
	class CMRState;
	class CMRNode;
	class CMRNodeVisitor;
	class CMRStateAttribute;
	class CMRUniform;
	class CMRUserDataContainer;


#define META_OBJECT(library,name) \
        virtual MR::CMRObject* Clone() const override{ return new name (); } \
        virtual MR::CMRObject* Copy(const CMRCopyPolicy& policy) const override{ return new name (*this, policy); } \
        virtual bool IsSameKindAs(const MR::CMRObject* obj) const override{ return dynamic_cast<const name *>(obj) != nullptr; } \
        virtual const char* LibraryName() const override{ return #library; }\
        virtual const char* ClassName() const override{ return #name; }

#define DEFAULT_OBJECT_CONSTRUCTORS(name) \
		public: \
			name (); \
			name (const name & obj, const CMRCopyPolicy& policy); \
		protected: \
			virtual ~##name (); \
		public:


	class CMRObject : public CMRRef
	{
	public:
		enum class CMRDataVariance
		{
			DYNAMIC,
			STATIC,
			UNCERTAIN
		};
	
	public:
		inline CMRObject() : 
			CMRRef(), 
			m_dataVariance(CMRDataVariance::UNCERTAIN),
			m_pUserDataContainer(0)
		{}

		CMRObject(const CMRObject& obj, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		virtual CMRObject* Clone() const = 0;
		virtual CMRObject* Copy(const CMRCopyPolicy& policy) const = 0;

		virtual bool IsSameKindAs(const CMRObject*) const { return true; }

		virtual const char* LibraryName() const = 0;
		virtual const char* ClassName() const = 0;

		string GetCompoundClassName() const { return string(LibraryName()) + string("::") + string(ClassName()); }

		virtual CMRNode* AsNode() { return 0; }
		virtual const CMRNode* AsNode() const { return 0; }

		virtual CMRNodeVisitor* AsNodeVisitor() { return 0; }
		virtual const CMRNodeVisitor* AsNodeVisitor() const { return 0; }

		virtual CMRStateAttribute* AsStateAttribute() { return 0; }
		virtual const CMRStateAttribute* AsStateAttribute() const { return 0; }

		virtual CMRUniform* AsUniform() { return 0; }
		virtual const CMRUniform* AsUniform() const { return 0; }

		virtual void SetName(const string& name) { m_strName = name; }
		inline void SetName(const char* pszName)
		{
			if (pszName == nullptr)
			{
				SetName(string());
			}
			else
			{
				SetName(string(pszName));
			}
		}	
		inline const string& GetName() const
		{
			return m_strName;
		}

		inline void SetDataVariance(CMRDataVariance dataVariance)
		{
			m_dataVariance = dataVariance;
		}
		inline CMRDataVariance GetDataVariance() const
		{
			return m_dataVariance;
		}
		virtual void ComputeDataVariance() {}

		void SetUserDataContainer(CMRUserDataContainer* udc);

		template<typename T>
		inline void SetUserDataContainer(const SmartPtr<T>& udc)
		{
			SetUserDataContainer(udc.Get());
		}

		CMRUserDataContainer* GetUserDataContainer()
		{ 
			return m_pUserDataContainer; 
		}

		
		CMRUserDataContainer* GetUserDataContainer() const 
		{
			return m_pUserDataContainer;
		}

		CMRUserDataContainer* GetOrCreatUserDataContainer();

		virtual void SetUserData(CMRRef* obj);

		template <typename T>
		void SetUserData(const SmartPtr<T>& ptr)
		{
			SetUserData(ptr.Get());
		}

		virtual CMRRef* GetUserData();

		virtual const CMRRef* GetUserData() const;

		virtual void ResizeGLObjectBuffers(unsigned int) {}

		virtual void ReleaseGLobjects(CMRState* states = 0) const {}


		//TODO: user value
		
	protected:
		virtual ~CMRObject() {};

		string m_strName;
		CMRDataVariance m_dataVariance;
		CMRUserDataContainer* m_pUserDataContainer;
	private:
		CMRObject& operator = (const CMRObject&) { return *this; }
	};

}

namespace MR
{
	template <typename T>
	T* Copy(const T* ptr, const MR::CMRCopyPolicy& policy = MR::CMRCopyPolicy::SHALLOW_COPY)
	{
		if (ptr)
		{
			SmartPtr<CMRObject> tmp = ptr->Copy(policy);

			T* ret = dynamic_cast<T*>(tmp.Get());
			if (ret)
			{
				tmp.Release();
				return tmp.Get();
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	T* Copy(const T* ptr, const string& strName, const MR::CMRCopyPolicy& policy = MR::CMRCopyPolicy::SHALLOW_COPY)
	{
		T* ret = MR::Copy(ptr, policy);
		if (ret)
		{
			ret->SetName(strName);
			return ret;
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	T* Clone(const T* ptr)
	{
		if (ptr)
		{
			SmartPtr<CMRObject> tmp = ptr->Clone(policy);

			T* ret = dynamic_cast<T*>(tmp.Get());
			if (ret)
			{
				tmp.Release();
				return tmp.Get();
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
}
#endif // CMRObject_h__
