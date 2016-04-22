#include "CConfig.h"
#if TEST6 == ON
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

class A
{
public:
	A() :m_strName("def"), m_nA(0){}
	A(string name, int n) :m_strName(name), m_nA(n) {}
	A(const A& rhs) : m_strName(rhs.m_strName), m_nA(rhs.m_nA){}
	A& operator=(const A& rhs) 
	{
		return *this;
	}
public:
	string m_strName;
	int m_nA;
private:
};

int main(void)
{
	A a("a", 3);
	A b(a);
	A c;
	c = a;
	cout << a.m_strName << endl;
	cout << b.m_strName << endl;
	cout << c.m_strName << endl;
	getchar();
	return 1;
}
#endif