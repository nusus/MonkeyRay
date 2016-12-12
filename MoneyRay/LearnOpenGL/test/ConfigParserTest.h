#pragma once
#include "config/ConfigParser.h"
#include <iostream>

namespace LOGL
{
	namespace Test
	{
		class ConfigParserTest
		{
		public:
			void Run()
			{
				ConfigParser config;
				config.ReadConfig("config/config.xml");
				ConfigParser& person = config.GetGroup("person");
				auto number = person.GetValueByKey<std::string>("name");
				std::cout << "person: " << number << std::endl;

				auto age = person.GetValueByKey<int>("age");
				std::cout << "age: " << age << std::endl;
				std::cin.get();
			}
		protected:
		private:
		};

	}
}