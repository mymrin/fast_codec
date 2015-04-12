#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include "parser.h"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	try
	{
		std::string templates("templates.xml");
		std::string output("templates.h");
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("templates,t", po::value<std::string>(&templates), "input templates file")
			("output,o", po::value<std::string>(&output), "output file");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help") || argc == 1) {
			std::cout << desc << "\n";
			return 1;
		}

		std::cout << "Compile templates: " << templates << std::endl;
		Parser parser;
		parser.Parse(templates, output);

		std::cout << "Output file: " << output << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "std::exception: " << e.what();
	}
	return 0;
}
