#include "OrgLib.h"



BEGIN_TEXTLIB_NAMESPACE


void MetaStatementString::Dump() {
	LOG(GetInstruction());
}

String MetaStatementString::GetInstruction() const {
	String s;
	s << meta_instruction << " " << name;
	for (const auto& p : params) {
		s << ", " << p.name << ": " << p.type;
	}
	if (ret.GetCount())
		s << " -> " << ret;
	if (comment.GetCount())
		s << " // " << comment;
	return s;
}

bool Parser::ParseTypeString(const String& s, Vector<String>& parts) {
	parts.Clear();
	String cur_part;
	int level = 0;
	for(int i = 0; i < s.GetCount(); i++) {
		int chr0 = s[i];
		int chr1 = i+1 < s.GetCount() ? s[i+1] : 0;
		if (chr0 == '<') {
			cur_part.Cat(chr0);
			level++;
		}
		else if (chr0 == '>') {
			cur_part.Cat(chr0);
			level--;
		}
		else if (level == 0 && chr0 == ':' && chr1 == ':') {
			parts << cur_part;
			cur_part.Clear();
			i++;
		}
		else
			cur_part.Cat(chr0);
	}
	if (cur_part.GetCount())
		parts << cur_part;
	return true;
}

bool Parser::ParseTypeString(CParser& p, Vector<String>& parts) {
	parts.Clear();
	String cur_part;
	int level = 0;
	while (!p.IsEof()) {
		if (p.IsId()) {
			cur_part << p.ReadId();
			while (p.IsChar('&') || p.IsChar('*'))
				cur_part.Cat(p.GetChar());
			p.Spaces();
			if (level == 0 && p.PeekChar() != ':' && p.PeekChar() != '<')
				break;
		}
		else if (p.Char('<')) {
			cur_part << "<";
			level++;
		}
		else if (p.Char('>')) {
			cur_part << ">";
			level--;
			if (level == 0 && p.PeekChar() != ':')
				break;
		}
		else if (level == 0 && p.Char2(':', ':')) {
			parts << cur_part;
			cur_part.Clear();
		}
		else
			cur_part.Cat(p.GetChar());
	}
	if (cur_part.GetCount())
		parts << cur_part;
	return true;
}

bool Parser::ParseMetaStatementString(const String& in, MetaStatementString& out) {
	CParser p(in);
	Vector<String> parts;
	
	try {
		out.meta_instruction = p.ReadId();
		
		// C++ style header
		if ((out.meta_instruction == "DECLARE_FUNCTION" ||
			out.meta_instruction == "DECLARE_METHOD" ||
			out.meta_instruction == "DECLARE_META_FUNCTION") &&
			in.Find("->") < 0) {
			String s = p.ReadString();
			CParser p(s);
			
			if (!ParseTypeString(p, parts))
				throw Exc("Invalid type");
			out.ret = Join(parts, "::");
			
			if (!ParseTypeString(p, parts))
				throw Exc("Invalid type");
			out.class_path.Clear();
			for(int i = 0; i < parts.GetCount()-1; i++)
				out.class_path << parts[i];
			out.name = parts.Top();
			
			out.params.Clear();
			if (p.Char('(')) {
				for(int i = 0; ; i++) {
					if (p.Char(')'))
						break;
					if (i)
						p.PassChar(',');
					
					auto& param = out.params.Add();
					if (!ParseTypeString(p, parts))
						throw Exc("Invalid type");
					param.type = Join(parts, "::");
					
					param.name = p.ReadId();
				}
			}
		}
		else {
			if (!ParseTypeString(p.ReadString(), parts))
				throw Exc("Invalid type");
			
			out.class_path.Clear();
			for(int i = 0; i < parts.GetCount()-1; i++)
				out.class_path << parts[i];
			out.name = parts.Top();
			
			out.params.Clear();
			while (p.Char(',')) {
				if (p.IsChar2('-','>'))
					break;
				auto& param = out.params.Add();
				param.name = p.ReadId();
				p.PassChar(':');
				
				if (!ParseTypeString(p, parts))
					throw Exc("Invalid type");
				param.type = Join(parts, "::");
			}
			
			out.ret.Clear();
			if (p.Char2('-','>')) {
				if (!ParseTypeString(p, parts))
					throw Exc("Invalid type");
				out.ret = Join(parts, "::");
			}
		}
		
		out.comment.Clear();
		if (p.Char2('/','/')) {
			out.comment = TrimBoth(p.GetPtr());
		}
	}
	catch (Exc e) {
		LOG("error parsing: " + e);
		return false;
	}
	return true;
}

bool Parser::ParseMetaInstructionType(const String& in, MetaInstructionType& out) {
	#define INS(x) if (in == #x) {out = x; return true;}
	META_INSTRUCTION_LIST
	#undef INS
	return false;
}

String Parser::GetMetaInstructionString(MetaInstructionType type) {
	#define INS(x) if (type == x) return #x;
	META_INSTRUCTION_LIST
	#undef INS
	return String("<unknown type " + IntStr((int)type) << ">");
}


END_TEXTLIB_NAMESPACE

