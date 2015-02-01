#include <string>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	std::string templates("templates.xml");
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("templates-file,t", po::value<std::string>(&templates), "input templates file");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || argc == 1) {
		std::cout << desc << "\n";
		return 1;
	}

	std::cout << "Compile templates: " << templates << std::endl;

	return 0;
}
