#pragma once
#ifndef ConfigParser_h__
#define ConfigParser_h__
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <memory>

namespace LOGL
{
	namespace bpt = boost::property_tree;

	class ConfigParser
	{
	public:
		typedef bpt::ptree NodeType;
	public:
		ConfigParser();

		ConfigParser(const NodeType& tree);

		ConfigParser(const ConfigParser& rhs) = delete;

		ConfigParser& operator=(const ConfigParser& rhs) = delete;

		~ConfigParser();


	protected:



	public:
		void ReadConfig(const std::string& fileName);

		template<typename T>
		T GetValueByKey(const std::string& key)
		{
			return m_Tree.get<T>(key);
		}

		ConfigParser GetGroup(const std::string& key);

	protected:
		void InitIni(const std::string& fileName);

		void InitXml(const std::string& fileName);

		void InitJson(const std::string& fileName);


	protected:
		bool EndWith(const std::string& source, const std::string& tail);


	protected:
		NodeType m_Tree;
	};

}


#endif // ConfigParser_h__#pragma once
