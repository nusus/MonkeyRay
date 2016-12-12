#include "config/ConfigParser.h"

LOGL::ConfigParser::ConfigParser(const LOGL::ConfigParser::NodeType& tree) :m_Tree(tree)
{

}

LOGL::ConfigParser::ConfigParser() : m_Tree()
{

}

LOGL::ConfigParser::~ConfigParser()
{

}

void LOGL::ConfigParser::ReadConfig(const std::string& fileName)
{
	if (EndWith(fileName, ".ini"))
	{
		InitIni(fileName);
	}

	if (EndWith(fileName, ".xml"))
	{
		InitXml(fileName);
	}

	if (EndWith(fileName, ".json"))
	{
		InitJson(fileName);
	}
}

LOGL::ConfigParser LOGL::ConfigParser::GetGroup(const std::string& key)
{
	return m_Tree.get_child(key);
}

void LOGL::ConfigParser::InitIni(const std::string& fileName)
{
	bpt::read_ini(fileName, m_Tree);
}

void LOGL::ConfigParser::InitXml(const std::string& fileName)
{
	bpt::read_xml(fileName, m_Tree);
}

void LOGL::ConfigParser::InitJson(const std::string& fileName)
{
	bpt::read_json(fileName, m_Tree);
}

bool LOGL::ConfigParser::EndWith(const std::string& source, const std::string& tail)
{
	if (source.size() < tail.size())
	{
		return false;
	}
	return (0 == source.compare(source.size() - tail.size(), tail.size(), tail));
}
