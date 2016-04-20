#ifndef CMRLog_h__
#define CMRLog_h__

namespace MR
{
	class CMRLog
	{
	public:
		static CMRLog* Instance()
		{
			static CMRLog s_log;
			return &s_log;
		}
	protected:
		CMRLog() {}
		CMRLog(const CMRLog& log) {}
		CMRLog& operator=(const CMRLog&) { return *this; }
	private:
	};
}
#endif // CMRLog_h__
