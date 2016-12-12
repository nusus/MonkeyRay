#pragma once
#include <functional>
#include <iostream>
namespace LOGL
{
	namespace Test
	{
		class FunctorTest
		{
		public:
			void Call(int x, int y)
			{
				std::cout << "call" << std::endl;
			}
		protected:
		private:
		};

		class Test
		{
		public:
			typedef void(*CallPtr)(int, int);
		public:
			void Run()
			{
				std::function<void(int, int)> fn = [&](int x, int y) ->void {
					m_fun.Call(x, y);
				};
				CallTest(1, 2, fn.target<void(int, int)>());
			}

			void CallTest(int a, int b, CallPtr fn)
			{
				fn(a, b);
			}
		protected:
		private:
			FunctorTest m_fun;
		};

	}
}