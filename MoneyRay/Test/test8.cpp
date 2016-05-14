#include "CConfig.h"
#if TEST8 == ON
#include <iostream>
class A;
class B;
class S
{
public:

	void Traverse(A& a);
	void Apply(A&);

	void Apply(B&);
protected:
private:
};

class A
{
public:
	virtual void Traverse(S& s);
protected:
private:
};

void A::Traverse(S& s)
{
	s.Apply(*this);
}

class B : public A
{
public:
	void Traverse(S& s)
	{
		s.Apply(*this);
	}
protected:
private:
};



void S::Traverse(A& a)
{
	a.Traverse(*this);
}

void S::Apply(B&)
{
	std::cout << "B" << std::endl;
}

void S::Apply(A&)
{
	std::cout << "A" << std::endl;
}

int main(void)
{
	A* a = new B();
	S s;
	s.Traverse(*a);
	system("pause");
	return 1;
}
#endif