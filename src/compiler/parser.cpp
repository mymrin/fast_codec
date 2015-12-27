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
			// A static data member with an in-class initializer must have non-volatile const integral type
			if (field_type == "std::string" || field_type == "fast_codec::Decimal")
				out << "// ";

			out << "static const" << " " << field_type;
			if (field_type == "std::string")
				const_value = std::string(" = ") + "\"" + f.second.get_child("<xmlattr>.value").data() + "\"";
			else
				const_value += std::string(" = ") + f.second.get_child("<xmlattr>.value").data();
			return true;
		}
	}
	return false;
}

void GenerateOutput(std::ofstream& out, std::ofstream& out_enc_cpp, const std::string& type, const std::string& func,
	const std::string& indent, const std::string& prefix, const std::string& field_name)
{
	out << type;
	out_enc_cpp << indent << func << "(0, encoder, " << prefix << field_name << ");" << std::endl;
}

template<typename F>
bool ParseField(const F& f, std::ofstream& out, std::ofstream& out_enc_cpp, std::string& const_value, const std::string& indent, const std::string& prefix)
{
	bool is_constant = false;
	std::string field_name = f.second.get_child("<xmlattr>.name").data();
	
	std::string charset;
	try
	{
		charset = f.second.get_child("<xmlattr>.charset").data();
	}
	catch (const pt::ptree_bad_path&) {}
	
	std::string presence;
	try
	{
		presence = f.second.get_child("<xmlattr>.presence").data();
	}
	catch (const pt::ptree_bad_path&) {}

	if (f.first == "string" && charset == "unicode")
	{
		if (presence == "optional")
			GenerateOutput(out, out_enc_cpp, "fast_codec::string_nt", "fast_codec::encode_string_utf8_optional", indent, prefix, field_name);
		else
			GenerateOutput(out, out_enc_cpp, "std::string", "fast_codec::encode_string_utf8", indent, prefix, field_name);
	}
	else if (f.first == "string")
	{
		is_constant = ParseConstant(f.second, "std::string", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::string_nt", "fast_codec::encode_string_ascii_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "std::string", "fast_codec::encode_string_ascii", indent, prefix, field_name);
		}
	}
	else if (f.first == "uInt32")
	{
		is_constant = ParseConstant(f.second, "std::uint32_t", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::uint32_nt", "fast_codec::encode_u32_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "std::uint32_t", "fast_codec::encode_u32", indent, prefix, field_name);
		}
	}
	else if (f.first == "int32")
	{
		is_constant = ParseConstant(f.second, "std::int32_t", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::int32_nt", "fast_codec::encode_i32_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "std::int32_t", "fast_codec::encode_i32", indent, prefix, field_name);
		}
	}
	else if (f.first == "uInt64")
	{
		is_constant = ParseConstant(f.second, "std::uint64_t", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::uint64_nt", "fast_codec::encode_u64_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "std::uint64_t", "fast_codec::encode_u64", indent, prefix, field_name);
		}
	}
	else if (f.first == "int64")
	{
		is_constant = ParseConstant(f.second, "std::int64_t", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::int64_nt", "fast_codec::encode_i64_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "std::int64_t", "fast_codec::encode_i64", indent, prefix, field_name);
		}
	}
	else if (f.first == "decimal")
	{
		is_constant = ParseConstant(f.second, "fast_codec::Decimal", out, const_value);
		if (!is_constant)
		{
			if (presence == "optional")
				GenerateOutput(out, out_enc_cpp, "fast_codec::DecimalNullable", "fast_codec::encode_decimal_optional", indent, prefix, field_name);
			else
				GenerateOutput(out, out_enc_cpp, "fast_codec::Decimal", "fast_codec::encode_decimal", indent, prefix, field_name);
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
			{
				AddToTags(f);
			}
			else
			{
				AddToTags(f);
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
	out_enc_cpp << indent << indent_ << "fast_codec::encode_u64(0, encoder, " << prefix << name << "Seq.size());" << std::endl;
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
	std::ofstream out_tags_(cfg.tags_h_);
	std::ofstream out(cfg.templates_h_);
	std::ofstream out_enc_h(cfg.templates_encoders_h_);
	std::ofstream out_enc_cpp(cfg.templates_encoders_cpp_);

	pt::ptree tree;
	pt::read_xml(cfg.templates_, tree, pt::xml_parser::no_comments);

	out << "#include <cstdint>" << std::endl;
	out << "#include <string>" << std::endl;
	out << "#include \"codec/fast_codec.h\"" << std::endl;
	out << std::endl;

	out_enc_h << "#include \"" << cfg.templates_h_ << "\"" << std::endl;
	out_enc_h << std::endl;

	out_enc_cpp << "#include \"" << cfg.tags_h_ << "\"" << std::endl;
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
			out << indent_ << "static const std::uint32_t id = " << t.second.get_child("<xmlattr>.id").data() << ";" << std::endl;
			out << std::endl;

			out_enc_h << "void Encode(fast_codec::Encoder& encoder, const " << name << "& msg);" << std::endl;
			out_enc_cpp << "void Encode(fast_codec::Encoder& encoder, const " << name << "& msg)" << std::endl << "{" << std::endl;
			
			if (cfg.is_msgseqnum_preamble_)
			{
				out_enc_cpp << indent_ << "// Preamble encoding" << std::endl;
				out_enc_cpp << indent_ << "fast_codec::write(encoder, msg.MsgSeqNum);" << std::endl << std::endl;
			}

			out_enc_cpp << indent_ << "// Constant PMAP encoding" << std::endl;
			out_enc_cpp << indent_ << "// 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id" << std::endl;
			out_enc_cpp << indent_ << "fast_codec::write_byte(encoder, 0xC0);" << std::endl << std::endl;

			out_enc_cpp << indent_ << "// Template id encoding" << std::endl;
			out_enc_cpp << indent_ << "fast_codec::encode_u32(0, encoder, msg.id);" << std::endl << std::endl;

			const auto& fields = t.second.get_child("");
			ParseFields(out, out_enc_cpp, fields, "msg.");

			out_enc_cpp << "}" << std::endl << std::endl;
			out << "};" << std::endl;
			out << std::endl;
		}
	}

	out_tags_ << "// tags.h" << std::endl;
	out_tags_ << std::endl;
	out_tags_ << "#ifndef FAST_TAGS" << std::endl;
	out_tags_ << "#define FAST_TAGS" << std::endl;
	out_tags_ << std::endl;
	out_tags_ << "enum Tags" << std::endl;
	out_tags_ << "{" << std::endl;
	out_tags_ << indent_ << "NullTag" << " = " << "0," << std::endl;
	for (auto i = tags_.begin(); i != tags_.end(); ++i)
	{
		out_tags_ << indent_ << i->first << " = " << i->second;
		if (i != tags_.end())
			out_tags_ << "," << std::endl;
		else
			out_tags_ << std::endl;
	}
	out_tags_ << "};" << std::endl;
	out_tags_ << std::endl;
	out_tags_ << "#endif" << std::endl;
}
