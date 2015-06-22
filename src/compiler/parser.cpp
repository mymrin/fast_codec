#include "parser.h"

namespace pt = boost::property_tree;

template<typename C>
bool ParseConstant(const C& c, const std::string& field_type, std::ofstream& out, std::string& const_value)
{
	const auto& childs = c.get_child("");
	for (const auto& f : childs)
	{
		if (f.first == "constant")
		{
			out << "const" << " " << field_type;
			if (field_type == "char")
				const_value = std::string("[] = ") + "\"" + f.second.get_child("<xmlattr>.value").data() + "\"";
			else
				const_value += std::string(" = ") + f.second.get_child("<xmlattr>.value").data();
			return true;
		}
	}
	return false;
}

template<typename F>
bool ParseField(const F& f, std::ofstream& out, std::ofstream& out_enc_cpp, std::string& const_value, const std::string& indent, const std::string& prefix)
{
	bool is_constant = false;
	std::string field_name = f.second.get_child("<xmlattr>.name").data();
	if (f.first == "string")
	{
		is_constant = ParseConstant(f.second, "char", out, const_value);
		if (!is_constant)
		{
			out << "std::string";
			out_enc_cpp << indent << "encode_ascii(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else if (f.first == "uInt32")
	{
		is_constant = ParseConstant(f.second, "std::uint32_t", out, const_value);
		if (!is_constant)
		{
			out << "std::uint32_t";
			out_enc_cpp << indent << "encode_u32(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else if (f.first == "int32")
	{
		is_constant = ParseConstant(f.second, "std::int32_t", out, const_value);
		if (!is_constant)
		{
			out << "std::int32_t";
			out_enc_cpp << indent << "encode_i32(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else if (f.first == "uInt64")
	{
		is_constant = ParseConstant(f.second, "std::uint64_t", out, const_value);
		if (!is_constant)
		{
			out << "std::uint64_t";
			out_enc_cpp << indent << "encode_u64(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else if (f.first == "int64")
	{
		is_constant = ParseConstant(f.second, "std::int64_t", out, const_value);
		if (!is_constant)
		{
			out << "std::int64_t";
			out_enc_cpp << indent << "encode_i64(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else if (f.first == "decimal")
	{
		is_constant = ParseConstant(f.second, "fast_codec::Decimal", out, const_value);
		if (!is_constant)
		{
			out << "fast_codec::Decimal";
			out_enc_cpp << indent << "encode_decimal(encoder, " << prefix << field_name << ");" << std::endl;
		}
	}
	else
	{
		std::string text = "ParseField: Unsupported type" + f.first + " of field " + field_name;
		throw std::logic_error("ParseField: Unsupported type");
	}
	return is_constant;
}

void Parser::ParseFields(std::ofstream& out, std::ofstream& out_enc_cpp, const pt::ptree& fields, const std::string& prefix)
{
	std::string indent(indent_);
	std::string indent_for_length(indent_);
	for (std::uint8_t i = 0; i != indent_counter_; ++i)
	{
		indent += indent_;
		if (i != indent_counter_ - 1)
			indent_for_length += indent_;
	}

	for (const auto& f : fields)
	{
		if (f.first != "<xmlattr>")
		{
			std::string const_value;
			std::string name = f.second.get_child("<xmlattr>.name").data();
			if (f.first == "sequence")
			{
				ParseSequence(out, out_enc_cpp, name, f.second.get_child(""), prefix);
			}
			else if (f.first == "length")
			{}
			else
			{
				out << indent;
				ParseField(f, out, out_enc_cpp, const_value, indent, prefix);
				out << " " << name << const_value << ";" << std::endl;
			}
		}
	}
}

void Parser::ParseSequence(std::ofstream& out, std::ofstream& out_enc_cpp, const std::string& name, const pt::ptree& fields, const std::string& prefix)
{
	std::string indent(indent_);
	for (std::uint8_t i = 0; i != indent_counter_; ++i)
		indent += indent_;

	out << std::endl;
	out << indent << "struct " << name << std::endl;
	out << indent << "{" << std::endl;

	std::string cycle_param_name = "i" + std::to_string(indent_counter_);
	out_enc_cpp << indent << "if (!" << prefix << name << "Seq.empty())" << std::endl;
	out_enc_cpp << indent << indent_ << "encode_i64(encoder, " << prefix << name << "Seq.size());" << std::endl;
	out_enc_cpp << indent << "for(const auto& " << cycle_param_name << " : " << prefix << name + "Seq" << ")" << std::endl;
	out_enc_cpp << indent << "{" << std::endl;

	const auto& childs = fields.get_child("");
	++indent_counter_;
	ParseFields(out, out_enc_cpp, childs, cycle_param_name + ".");
	--indent_counter_;

	out_enc_cpp << indent << "}" << std::endl;

	out << indent << "};" << std::endl;
	out << indent << "std::vector<" << name << "> " << name + "Seq;" << std::endl;
}

void Parser::GenerateCppSources(const Config& cfg)
{
	std::ofstream out(cfg.templates_h_);
	std::ofstream out_enc_h(cfg.templates_encoders_h_);
	std::ofstream out_enc_cpp(cfg.templates_encoders_cpp_);

	pt::ptree tree;
	pt::read_xml(cfg.templates_, tree, pt::xml_parser::no_comments);

	out << "#include <cstdint>" << std::endl;
	out << "#include <string>" << std::endl;
	out << "#include \"fast_codec.h\"" << std::endl;
	out << std::endl;

	out_enc_h << "#include \"" << cfg.templates_h_ << "\"" << std::endl;
	out_enc_h << std::endl;

	out_enc_cpp << "#include \"" << cfg.templates_encoders_h_ << "\"" << std::endl;
	out_enc_cpp << std::endl;

	const auto& childs = tree.get_child("templates");
	for (const auto& t : childs)
	{
		if (t.first == "template")
		{
			std::string name(t.second.get_child("<xmlattr>.name").data());
			out << "struct " << name << std::endl;
			out << "{" << std::endl;
			out << "   const int id = " << t.second.get_child("<xmlattr>.id").data() << ";" << std::endl;
			out << "   const int dictionary = " << t.second.get_child("<xmlattr>.dictionary").data() << ";" << std::endl;
			out << std::endl;

			out_enc_h << "void Encode(fast_codec::Encoder& encoder, const " << name << "& msg);" << std::endl;
			out_enc_cpp << "void Encode(fast_codec::Encoder& encoder, const " << name << "& msg)" << std::endl << "{" << std::endl;

			const auto& fields = t.second.get_child("");
			ParseFields(out, out_enc_cpp, fields, "msg.");

			out_enc_cpp << "}" << std::endl << std::endl;
			out << "};" << std::endl;
			out << std::endl;
		}
	}
}
