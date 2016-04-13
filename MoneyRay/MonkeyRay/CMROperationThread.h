#ifndef CMROperationThread_h__
#define CMROperationThread_h__

namespace MR
{
	class CMROperation : virtual public CMRRef
	{
	public:
		CMROperation(const string& strName, bool bKeep)
			:m_strName(strName),
			m_bKeep(bKeep)
		{

		}

		void SetName(const string& name) { m_strName = name; }
		string GetName() const { return m_strName; }

		void SetKeep(const bool bKeep) { m_bKeep = bKeep; }
		bool GetKeep() const { return m_bKeep; }

		virtual void ReleaseOperation() {}

		virtual void operator()(CMRObject* obj) = 0;
	protected:
		CMROperation() :m_bKeep(false) {}
		CMROperation(const CMROperation& op)
			:m_strName(op.m_strName),
			m_bKeep(op.m_bKeep) {}
		virtual ~CMROperation() {}
	protected:
		string m_strName;
		bool m_bKeep;
	private:
	};

	class CMROperationQueue
	{
	public:
		void RunOperations(MR::CMRObject* callingObject = (MR::CMRObject*) 0)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Add(const CMROperation* op)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Remove(const CMROperation* op)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}



	};

	class CMROperationThread
	{
	public:
	protected:
	private:
	};
}
#endif // CMROperationThread_h__
