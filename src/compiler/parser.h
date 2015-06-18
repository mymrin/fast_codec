#ifndef FAST_SIMPLE_CODEC_PARSER_HEADER
#define FAST_SIMPLE_CODEC_PARSER_HEADER

#include <string>
#include <cstdint>
#include <boost/property_tree/xml_parser.hpp>

class Parser
{
	const std::string indent_ = "   ";
	std::uint8_t indent_counter_;
private:
	void ParseFields(std::ofstream& out, const boost::property_tree::ptree& fields);
	void ParseSequence(std::ofstream& out, const std::string& name, const boost::property_tree::ptree& fields);
public:
	Parser() : indent_counter_(0) {};

	void Parse(const std::string& templates, const std::string& output);
};

#endif
