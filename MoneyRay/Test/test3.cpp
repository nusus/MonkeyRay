#include "CConfig.h"
#include <iostream>
#if TEST3 == ON

class A
{
public:
	A();
	~A();

private:

};

A::A()
{
}

A::~A()
{
}

class B
{
public:
	B();
	~B();

private:

};

B::B()
{
}

B::~B()
{
}

template <typename T>
bool IsSameType(const T& , const T& )
{
	return true;
}

template <typename T1, typename T2>
bool IsSameType(const T1&, const T2&)
{
	return false;
}

int main(void)
{
	A a1, a2;
	B b;
	std::cout << IsSameType(a1, a2) << std::endl;
	std::cout << IsSameType(a1, b) << std::endl;
	system("pause");
}

#endif