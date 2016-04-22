#include "CConfig.h"
#if TEST1 == ON
#include <exception>
#include <iostream>
#include <memory>

class CBase
{
public:
	CBase(int a, int b) :
		m_nA(a),
		m_nB(b)
	{}
protected:
private:
	int m_nA;
	int m_nB;
};

template <typename T, typename... Args>
std::shared_ptr<T> CreateSharedPtr(Args&&... args)
{
	CBase* ptr = new CBase(std::forward<Args>(args)...);
	return std::shared_ptr<T>(ptr);
}

int main()
{
	std::shared_ptr<CBase> p = CreateSharedPtr<CBase>(3, 4);
	std::cout << p.use_count() << std::endl;
	system("pause");
	return 0;
}
#endif // TEST1
