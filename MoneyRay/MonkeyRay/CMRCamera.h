#ifndef CMRCamera_h__
#define CMRCamera_h__

namespace MR
{
	class CMRCamera
	{
	public:
		CMRRender* GetRender()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		CMRCallback* GetUpdateCallback()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Accept(CMRNodeVisitor& nv)
		{
			//TODO: CMRCamera is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		CMRGraphicsContext* GetGraphicsContext() const
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetView(MR:CMRViewBase* param1)
		{
			//TODO: CMRCamera is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}





	protected:
	private:


		

	};
}
#endif // CMRCamera_h__
