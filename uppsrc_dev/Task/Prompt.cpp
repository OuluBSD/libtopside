#include "Task.h"


BEGIN_TEXTLIB_NAMESPACE


String TaskTitledList::GetTreeString(int indent) const {
	String s;
	String in;
	in.Cat('\t', indent);
	
	s << in << "title_format_str: " << title_format_str << "\n";
	if (title_value.GetCount()) s << in << "title_value: " << title_value << "\n";
	if (title_args.GetCount()) {
		s << in << "title_args: ";
		String a;
		for (const Value& v : title_args) {
			if (!a.IsEmpty()) a << ", ";
			a << v.ToString();
		}
		s << a << "\n";
	}
	if (separator.GetCount()) s << in << "separator: " << separator << "\n";
	if (line_str.GetCount()) s << in << "line_str: " << line_str << "\n";
	if (line_in_alpha) s << in << "line_in_alpha: true\n";
	if (no_colon) s << in << "no_colon: true\n";
	if (no_listchar) s << in << "no_listchar: true\n";
	if (title_in_quotes) s << in << "title_in_quotes: true\n";
	if (value_in_quotes) s << in << "value_in_quotes: true\n";
	if (count_sub) s << in << "count_sub: true\n";
	if (count_lines) s << in << "count_lines: true\n";
	if (inline_list) s << in << "inline_list: true\n";
	if (no_separator) s << in << "no_separator: true\n";
	if (combination_string) s << in << "combination_string: true\n";
	if (empty_line) s << in << "empty_line: true\n";
	if (capitalize) s << in << "capitalize: true\n";
	if (line_begin) s << in << "line_begin: " << line_begin << "\n";
	if (scores.GetCount()) {
		s << in << "scores: ";
		for(int i = 0; i < scores.GetCount(); i++) {
			if (i) s << ", ";
			s << scores[i];
		}
		s << "\n";
	}
	
	for(int i = 0; i < items.GetCount(); i++) {
		String key = items.GetKey(i);
		String value = items[i];
		if (key.GetCount() && items.GetCount())
			s << in << "\t[" << i << "] " << key << ": " << items[i] << "\n";
		else if (key.GetCount())
			s << in << "\t[" << i << "] " << key << "\n";
		else if (value.GetCount())
			s << in << "\t[" << i << "] " << value << "\n";
		else
			s << in << "\t[" << i << "] <empty>\n";
	}
	
	int sub_i = 0;
	for (const auto& list : sub) {
		s << in << "sub[" << sub_i++ << "] {\n";
		s << list.GetTreeString(indent+1);
		s << in << "}\n";
	}
	
	return s;
}

String AiPrompt::GetTreeString() const {
	String s;
	
	for (const TaskTitledList& list : titled_lists) {
		s << "{\n";
		s << list.GetTreeString(1);
		s << "}\n";
	}
	
	if (pre_answer) {
		s << "{\n";
		s << pre_answer->GetTreeString(1);
		s << "}\n";
	}
	
	s << "response_length: " << response_length << "\n";
	
	return s;
}

void TaskTitledList::LineBegin(int i, String& s) const {
	if (inline_list && i > 0) {
		if (no_separator)
			s << " ";
		else if (separator.IsEmpty())
			s << ", ";
		else
			s << separator;
	}
	
	if (numbered_lines) {
		s << line_begin + i << ".";
		if (!no_numbered_lines_space)
			s << " ";
	}
	else if (count_lines) {
		bool skip_space = false;
		if (!no_listchar && !inline_list) {
			s << "-";
		}
		else
			skip_space = true;
		
		if (line_in_alpha) {
			int limit = 'z' - 'a' + 1;
			int chr = i % limit;
			int mul = i / limit;
			s.Cat('a' + chr);
			if (mul > 0) s << mul;
		}
		else {
			if (!skip_space)
				s.Cat(' ');
			s << "Line " << line_begin + i;
		}
		if (!no_separator) {
			if (separator.GetCount())
				s << separator;
			else
				s << ", ";
		}
	}
	else {
		if (!no_listchar && !inline_list)
			s << "- ";
	}
}

String TaskTitledList::AsString() const {
	String s;
	
	bool parenthesis = inline_list && no_separator;
	
	if (!title_format_str.IsEmpty() || !title_value.IsEmpty()) {
		if (title_in_quotes)
			s << "\"";
		if (!title_format_str.IsEmpty()) {
			String title = Format(title_format_str, title_args);
			if (capitalize)
				title = ::TextLib::Capitalize(title);
			s << title;
		}
		if (title_in_quotes)
			s << "\"";
		
		if (!title_value.IsEmpty()) {
			s << ": ";
			if (value_in_quotes)
				s << "\"";
			if (capitalize)
				s << ::TextLib::Capitalize(title_value);
			else
				s << title_value;
			if (value_in_quotes)
				s << "\"";
		}
		if (!no_colon)
			s << ":";
		
		s << "\n";
	}
	
	int line = -1;
	if (!values.IsEmpty()) {
		for(int i = 0; i < values.GetCount(); i++) {
			++line;
			LineBegin(line, s);
			
			String value = values[i];
			if (capitalize) {
				value = ::TextLib::Capitalize(value);
			}
			if (value.GetCount()) {
				if (parenthesis)
					s.Cat('(');
				if (value_in_quotes)
					s.Cat('\"');
				s << value;
				if (value_in_quotes)
					s.Cat('\"');
				if (parenthesis)
					s.Cat(')');
			}
			
			if (result_list && i == values.GetCount() - 1)
				; // pass
			else if (!inline_list)
				s << "\n";
		}
	}
	
	if (!items.IsEmpty()) {
		for(int i = 0; i < items.GetCount(); i++) {
			++line;
			LineBegin(line, s);
			
			String key = items.GetKey(i);
			String value = items[i];
			if (capitalize) {
				key = ::TextLib::Capitalize(key);
				value = ::TextLib::Capitalize(value);
			}
			if (parenthesis)
				s.Cat('(');
			if (key.GetCount())
				s << key << ":";
			if (key.GetCount() && value.GetCount())
				s.Cat(' ');
			if (value.GetCount()) {
				if (value_in_quotes)
					s.Cat('\"');
				s << value;
				if (value_in_quotes)
					s.Cat('\"');
			}
			if (parenthesis)
				s.Cat(')');
			
			if (result_list && i == items.GetCount() - 1)
				; // pass
			else if (!inline_list)
				s << "\n";
		}
	}
	
	for(int i = 0; i < sub.GetCount(); i++) {
		const TaskTitledList& list = sub[i];
		++line;
		if (list.inline_list || count_sub) {
			LineBegin(line, s);
		}
		s << list.AsString();
		if (result_list && i == sub.GetCount() - 1)
			; // pass
		else
			s << "\n";
	}
	
	if (combination_string) {
		if (s.Right(1) != "\n")
			s << "\n";
		
		String comb_str;
		for(int i = 0; i < scores.GetCount(); i++) {
			int score = scores[i];
			if (i) comb_str.Cat(' ');
			int chr = i % ('z' - 'a');
			int mod = i / ('z' - 'a');
			comb_str.Cat('a' + chr);
			if (mod > 0)
				comb_str << mod << "_";
			if      (score > 0) comb_str.Cat('+');
			else if (score < 0) comb_str.Cat('-');
			comb_str << score;
		}
		s << "Combination string:";
		if (comb_str.GetCount())
			s << " " << comb_str << "\n";
	}
	
	if (empty_line) {
		LineBegin(0, s);
		if (s.Right(1) == " ")
			s = s.Left(s.GetCount()-1);
		s << empty_line_string;
	}
	
	return s;
}

String AiPrompt::AsString() const {
	String s;
	
	//LOG(GetTreeString());
	
	for (const TaskTitledList& list : titled_lists) {
		s << list.AsString();
		s << "\n\n";
	}
	
	if (pre_answer) {
		s << pre_answer->AsString();
	}
	
	//LOG(s);
	
	return s;
}



END_TEXTLIB_NAMESPACE

