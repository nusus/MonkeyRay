#ifndef CMRUserDataContainer_h__
#define CMRUserDataContainer_h__

#include "CMRObject.h"

namespace MR
{
	class CMRUserDataContainer :public CMRObject
	{
		DEFAULT_OBJECT_CONSTRUCTORS(CMRUserDataContainer)
	public:
		virtual bool IsSameKindAs(const CMRObject* obj) const override { return dynamic_cast<const CMRUserDataContainer*>(obj) != nullptr; }
		virtual const char* LibraryName() const override
		{
			return "MonkeyRay";
		}
		virtual const char* ClassName() const override
		{
			return "CMRUserDataContainer";
		}

		virtual CMRRef* GetUserData() override = 0;
		virtual const CMRRef* GetUserData() const override = 0;
		virtual void SetUserData(CMRRef* obj) override = 0;
		using CMRObject::SetUserData;

		virtual unsigned int AddUserObject(CMRObject* obj) = 0;
		template <typename T>
		unsigned int AddUserObject(const SmartPtr<T> obj)
		{
			AddUserObject(obj.Get());
		}
		virtual void SetUserObject(unsigned int index, CMRObject* obj) = 0;
		virtual void RemoveUserObject(unsigned int index) = 0;
		virtual CMRObject* GetUserObject(unsigned int index) = 0;
		virtual const CMRObject* GetUserObject(unsigned int index) const = 0;
		virtual unsigned int GetNumUserObjects() const = 0;

		virtual unsigned GetUserObjectIndex(const CMRObject* obj, unsigned int nStartPosition = 0) const = 0;
		virtual unsigned GetUserObjectIndex(const string& strName, unsigned int nStartPosition = 0) const = 0;
		virtual CMRObject* GetUserObject(const string& strName, unsigned int nStartPosition = 0);
		virtual const CMRObject* GetUserObject(const string& strName, unsigned int nStartPosition = 0) const;

		typedef vector<string> DescriptionList;

		virtual void SetDescriptions(const DescriptionList& dl) = 0;
		virtual DescriptionList& GetDescriptions() = 0;
		virtual const DescriptionList& GetDescriptions() const = 0;
		virtual unsigned int GetNumDescriptions() const = 0;
		virtual void AddDescription(const string& strName) = 0;
	};

	class CMRDefaultUserDataContainer : public CMRUserDataContainer
	{
		DEFAULT_OBJECT_CONSTRUCTORS(CMRDefaultUserDataContainer)	
	public:
		META_OBJECT(MonkeyRay, CMRDefaultUserDataContainer)
		virtual void SetUserData(CMRRef* obj) override;
		using CMRObject::SetUserData;
		using CMRUserDataContainer::AddUserObject;
		virtual CMRRef* GetUserData() override;
		virtual const CMRRef* GetUserData() const override;

		virtual unsigned int AddUserObject(CMRObject* obj) override;
		virtual void SetUserObject(unsigned int index, CMRObject* obj) override;
		virtual void RemoveUserObject(unsigned int index) override;
		virtual CMRObject* GetUserObject(unsigned int index) override;
		virtual const CMRObject* GetUserObject(unsigned int index) const override;
		virtual unsigned int GetNumUserObjects() const override;

		virtual unsigned int GetUserObjectIndex(const CMRObject* obj, unsigned int nStartPosition = 0) const override;
		virtual unsigned int GetUserObjectIndex(const string& strName, unsigned int nStartPosition = 0) const override;

		virtual void SetDescriptions(const DescriptionList& dl) override;
		virtual DescriptionList& GetDescriptions() override;
		virtual const DescriptionList& GetDescriptions() const override;
		virtual void AddDescription(const string& strName) override;
		virtual unsigned int GetNumDescriptions() const override;
	protected:
		typedef vector<SmartPtr<CMRObject> > ObjectList;

		SmartPtr<CMRRef> m_userData;
		DescriptionList m_descriptionList;
		ObjectList m_objectList;
	};
}
#endif // CMRUserDataContainer_h__
