#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include "config.h"
#include "parser.h"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	try
	{
		Config cfg;
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("templates,t", po::value<std::string>(&cfg.templates_), "input templates file")
			("templates_h,h", po::value<std::string>(&cfg.templates_h_), "output file with message structs")
			("templates_encoders_h,e", po::value<std::string>(&cfg.templates_encoders_h_), "output file with encoder function definitions")
			("templates_encoders_cpp,c", po::value<std::string>(&cfg.templates_encoders_cpp_), "output file with encoder function implementations");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help") || argc == 1) {
			std::cout << desc << "\n";
			return 1;
		}

		std::cout << "Compile templates: " << cfg.templates_ << std::endl;
		Parser parser;
		parser.GenerateCppSources(cfg);

		std::cout << "Output files: " << std::endl 
			<< cfg.templates_h_ << std::endl
			<< cfg.templates_encoders_h_ << std::endl
			<< cfg.templates_encoders_cpp_ << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "std::exception: " << e.what();
	}
	return 0;
}
