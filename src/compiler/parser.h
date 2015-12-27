#ifndef FAST_CODEC_PARSER_HEADER
#define FAST_CODEC_PARSER_HEADER

#include <string>
#include <cstdint>
#include <map>
#include <boost/property_tree/xml_parser.hpp>
#include "config.h"

class Parser
{
	const std::string indent_ = "   ";
	std::uint8_t indent_counter_;
	std::map<std::string, std::string> tags_;
private:
	template<class F>
	void AddToTags(const F& f)
	{
		std::string field_name = f.second.get_child("<xmlattr>.name").data();
		std::string field_id = f.second.get_child("<xmlattr>.id").data();
		tags_[field_name] = field_id;
	}
	void ParseFields(std::ofstream& out, std::ofstream& out_enc_cpp, const boost::property_tree::ptree& fields, const std::string& prefix);
	void ParseSequence(std::ofstream& out, std::ofstream& out_enc_cpp, const std::string& name, const boost::property_tree::ptree& fields, const std::string& prefix);
public:
	Parser() : indent_counter_(0) {};

	void GenerateCppSources(const Config& cfg);
};

#endif
