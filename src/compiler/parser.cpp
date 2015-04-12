#include "parser.h"
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

void Parser::Parse(const std::string& templates, const std::string& output)
{
	pt::ptree tree;
	pt::read_xml(templates, tree);
}
