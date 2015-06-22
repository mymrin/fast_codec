#ifndef FAST_CODEC_CONFIG_HEADER
#define FAST_CODEC_CONFIG_HEADER

#include <string>

struct Config
{
	std::string templates_ = "templates.xml";
	std::string templates_h_ = "templates.h";
	std::string templates_encoders_h_ ="templates_encoders.h";
	std::string templates_encoders_cpp_ = "templates_encoders.cpp";
};

#endif
