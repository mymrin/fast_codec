#ifndef FAST_SIMPLE_CODEC_PARSER_HEADER
#define FAST_SIMPLE_CODEC_PARSER_HEADER

#include <string>
#include <list>

class Parser
{
public:
	Parser() {};
	void Parse(const std::string& templates, const std::string& output);
private:
	std::list<std::string> output_;
};

#endif
