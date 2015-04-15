#include "parser.h"
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

void Parser::Parse(const std::string& templates, const std::string& output)
{
	std::ofstream out(output);

	pt::ptree tree;
	pt::read_xml(templates, tree, pt::xml_parser::no_comments);

	const auto& childs = tree.get_child("templates");
	for (const auto& t : childs)
	{
		if (t.first == "template")
		{
			out << "struct " << t.second.get_child("<xmlattr>.name").data() << std::endl;
			out << "{" << std::endl;

			const auto& fields = t.second.get_child("");
			for (const auto& f : fields)
			{
				if (f.first != "<xmlattr>")
				{
					out << "   ";
					if (f.first == "string")
						out << "std::";
					out << f.first.data() << " " << f.second.get_child("<xmlattr>.name").data() << ";" << std::endl;
				}
			}

			out << "}" << std::endl;
			out << std::endl;
		}
	}
}
