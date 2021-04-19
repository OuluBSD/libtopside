#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


String Lexer::DumpTokens() {
	String s;
	for(int i = 0; i < tokens.GetCount(); i++) {
		const Token& t = tokens[i];
		s << "\t[" << i << "] " << GetTypeString(t.type);
		if (t.int_value)
			s << " (" << t.int_value << ")";
		if (t.str_value.GetCount())
			s << ": \"" << t.str_value.ToString() << "\"";
		s << "\n";
	}
	return s;
}


NAMESPACE_LANGUAGE_END
