#include "parser.h"

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
	else if (f.first == "int32")
	{
		if (!ParseConstant(f.second, "std::int32_t", out, const_value))
			out << "std::int32_t";
		return true;
	}
	else if (f.first == "uInt64")
	{
		if (!ParseConstant(f.second, "std::uint64_t", out, const_value))
			out << "std::uint64_t";
		return true;
	}
	else if (f.first == "int64")
	{
		if (!ParseConstant(f.second, "std::int64_t", out, const_value))
			out << "std::int64_t";
		return true;
	}
	return false;
}

void Parser::ParseFields(std::ofstream& out, const pt::ptree& fields)
{
	std::string indent(indent_);
	for (std::uint8_t i = 0; i != indent_counter_; ++i)
		indent += indent_;

	for (const auto& f : fields)
	{
		if (f.first != "<xmlattr>")
		{
			std::string const_value;
			if (f.first == "sequence")
			{
				std::string sequence_name = f.second.get_child("<xmlattr>.name").data();
				ParseSequence(out, sequence_name, f.second.get_child(""));
			}
			else if (f.first == "length")
			{}
			else
			{
				out << indent;
				if (!ParseField(f, out, const_value))
					out << f.first.data();
				out << " " << f.second.get_child("<xmlattr>.name").data() << const_value << ";" << std::endl;
			}
		}
	}
}

void Parser::ParseSequence(std::ofstream& out, const std::string& name, const pt::ptree& fields)
{
	std::string indent(indent_);
	for (std::uint8_t i = 0; i != indent_counter_; ++i)
		indent += indent_;

	out << std::endl;
	out << indent << "struct " << name << std::endl;
	out << indent << "{" << std::endl;

	const auto& childs = fields.get_child("");
	++indent_counter_;
	ParseFields(out, childs);
	--indent_counter_;

	out << indent << "};" << std::endl;
	out << indent << "std::vector<" << name << "> " << name + "Seq;" << std::endl;
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
			ParseFields(out, fields);

			out << "};" << std::endl;
			out << std::endl;
		}
	}
}
