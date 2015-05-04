#include "parser.h"
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

template<typename C>
bool ParseConstant(const C& c, const std::string& field_name, std::ofstream& out, std::string& const_value)
{
	const auto& childs = c.get_child("");
	for (const auto& f : childs)
	{
		if (f.first == "constant")
		{
			out << "const" << " " << field_name;
			if (field_name == "char")
				const_value = std::string("[] = ") + "\"" + f.second.get_child("<xmlattr>.value").data() + "\"";
			else
				const_value += std::string(" = ") + f.second.get_child("<xmlattr>.value").data();
			return true;
		}
	}
	return false;
}

template<typename F>
bool ParseField(const F& f, std::ofstream& out, std::string& const_value)
{
	if (f.first == "string")
	{
		if (!ParseConstant(f.second, "char", out, const_value))
			out << "std::string";
		return true;
	}
	else if (f.first == "uInt32")
	{
		if (!ParseConstant(f.second, "std::uint32_t", out, const_value))
			out << "std::uint32_t";
		return true;
	}
	else if (f.first == "uInt64")
	{
		if (!ParseConstant(f.second, "std::uint64_t", out, const_value))
			out << "std::uint64_t";
		return true;
	}
	return false;
}

void Parser::Parse(const std::string& templates, const std::string& output)
{
	std::ofstream out(output);

	pt::ptree tree;
	pt::read_xml(templates, tree, pt::xml_parser::no_comments);

	out << "#include <cstdint>" << std::endl;
	out << "#include <string>" << std::endl;
	out << std::endl;

	const auto& childs = tree.get_child("templates");
	for (const auto& t : childs)
	{
		if (t.first == "template")
		{
			out << "struct " << t.second.get_child("<xmlattr>.name").data() << std::endl;
			out << "{" << std::endl;
			out << "   const int id = " << t.second.get_child("<xmlattr>.id").data() << ";" << std::endl;
			out << "   const int dictionary = " << t.second.get_child("<xmlattr>.dictionary").data() << ";" << std::endl;
			out << std::endl;

			const auto& fields = t.second.get_child("");
			for (const auto& f : fields)
			{
				if (f.first != "<xmlattr>")
				{
					out << "   ";
					std::string const_value;
					if (f.first == "sequence")
					{
						out << "std::vector<" << f.second.get_child("<xmlattr>.name").data() << "> ";
						out << f.second.get_child("<xmlattr>.name").data() + "_Seq;" << std::endl;
					}
					else
					{
						if (!ParseField(f, out, const_value))
							out << f.first.data();
						out << " " << f.second.get_child("<xmlattr>.name").data() << const_value << ";" << std::endl;
					}
				}
			}

			out << "};" << std::endl;
			out << std::endl;
		}
	}
}
