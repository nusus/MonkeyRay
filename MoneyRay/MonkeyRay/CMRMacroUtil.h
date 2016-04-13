#ifndef CMRMacroUtil_h__
#define CMRMacroUtil_h__


#define META_OBJECT(library,name) \
        virtual MR::CMRObject* Clone() const override{ return new name (); } \
        virtual MR::CMRObject* Copy(const CMRCopyPolicy& policy) const override{ return new name (*this, policy); } \
        virtual bool IsSameKindAs(const MR::CMRObject* obj) const override{ return dynamic_cast<const name *>(obj) != nullptr; } \
        virtual const char* LibraryName() const override{ return #library; }\
        virtual const char* ClassName() const override{ return #name; }


#define DEFAULT_OBJECT_CONSTRUCTORS(name) \
		public: \
			name (); \
			name (const name & obj, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY); \
		protected: \
			virtual ~##name (); \
		public:



#define OBJECT_MEMBER_GET_SET(name) \
void Set##name ( CMR##name * ptr ); \
template<typename T> void Set##name ( const SmartPtr<T>& spPtr ){ Set##name (spPtr.Get()); } \
CMR##name * Get##name (); \
const CMR##name * Get##name () const




#define OBJECT_MEMBER_ADD_GET_REMOVE(name) \
void Add##name ( CMR##name * ptr); \
template<typename T> void Add##name (const SmartPtr<T>& spPtr) { Add##name (spPtr.Get());} \
void Remove##name ( CMR##name * ptr); \
template<typename T> void Remove##name(const SmartPtr<T>& spPtr) { Remove##name(spPtr.Get()); } \
CMR##name* Get##name (); \
const CMR##name* Get##name () const


#define META_NODE(name) \
virtual CMRObject* Clone() const override{return new name () ;} \
virtual CMRObject* Copy(const CMRCopyPolicy& policy) const override {return  new name (*this, policy);} \
virtual bool IsSameKindAs(const CMRObject* obj) const override {return dynamic_cast<const name *> (obj) != nullptr;} \
virtual const char* ClassName() const override {return #name ;} \
virtual void Accept(CMRNodeVisitor& nv) \
{ \
	if (nv.ValidNodeMask(*this)) \
	{ \
		nv.PushOntoNodePath(*this); \
		nv.Apply(*this); \
		nv.PopFromNodePath(); \
	} \
}


#endif // CMRMacroUtil_h__
