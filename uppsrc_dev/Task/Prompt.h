#ifndef _Task_Prompt_h_
#define _Task_Prompt_h_


BEGIN_TEXTLIB_NAMESPACE



struct TaskTitledList {
	String title_format_str;
	String title_value;
	Vector<Value> title_args;
	String separator;
	String line_str;
	String empty_line_string;
	bool line_in_alpha = false;
	bool no_colon = false;
	bool no_listchar = false;
	bool title_in_quotes = false;
	bool value_in_quotes = false;
	bool count_sub = false;
	bool count_lines = false;
	bool numbered_lines = false;
	bool no_numbered_lines_space = false;
	bool inline_list = false;
	bool no_separator = false;
	bool combination_string = false;
	bool empty_line = false;
	bool capitalize = false;
	bool result_list = false;
	int line_begin = 1;
	
	Vector<int> scores;
	
	VectorMap<String,String> items;
	Vector<String> values;
	Array<TaskTitledList> sub;
	
	// Temp
	Vector<String> args;
	
	TaskTitledList& Title(String title_fmt, String value=String()) {title_format_str = title_fmt; title_value = value; return *this;}
	TaskTitledList& FormatArg(String s) {title_args << s; return *this;}
	TaskTitledList& Add(String s) {values.Add(s); return *this;}
	TaskTitledList& Add(String key, String value) {items.Add(key, value); return *this;}
	TaskTitledList& Add(String key, int value) {items.Add(key, IntStr(value)); return *this;}
	TaskTitledList& NoColon(bool b=true) {no_colon = b; return *this;}
	TaskTitledList& NoListChar(bool b=true) {no_listchar = b; return *this;}
	TaskTitledList& TitleInQuotes(bool b=true) {title_in_quotes = b; return *this;}
	TaskTitledList& ValueInQuotes(bool b=true) {value_in_quotes = b; return *this;}
	TaskTitledList& CountSub(bool b=true) {count_sub = b; return *this;}
	TaskTitledList& CountLines(bool b=true) {count_lines = b; return *this;}
	TaskTitledList& CountLinesAlpha(bool b=true) {line_in_alpha = true; count_lines = b; return *this;}
	TaskTitledList& CountLines(String line_str, bool b=true) {this->line_str = line_str; count_lines = b; return *this;}
	TaskTitledList& InlineList(bool b=true) {inline_list = b; return *this;}
	TaskTitledList& NoSeparator(bool b=true) {no_separator = b; return *this;}
	TaskTitledList& CombinationString(bool b=true) {combination_string = b; return *this;}
	TaskTitledList& EmptyLine(bool b=true) {empty_line = b; return *this;}
	TaskTitledList& Capitalize(bool b=true) {capitalize = b; return *this;}
	TaskTitledList& AddSub() {return sub.Add();}
	TaskTitledList& Arg(String s) {args.Add(s); return *this;}
	TaskTitledList& Separator(String s) {separator = s; return *this;}
	TaskTitledList& LineBegin(int line_begin) {this->line_begin = line_begin; return *this;}
	TaskTitledList& NumberedLines(bool b=true) {numbered_lines = b; return *this;}
	TaskTitledList& NoNumberedLinesSpace(bool b=true) {no_numbered_lines_space = b; return *this;}
	TaskTitledList& EmptyLineString(String s) {empty_line_string = s; return *this;}
	
	String AsString() const;
	String GetTreeString(int indent) const;
	
	TaskTitledList& operator[](int i) {return sub[i];}
	const TaskTitledList& operator[](int i) const {return sub[i];}
	
private:
	void LineBegin(int i, String& s) const;
	
};

struct AiPrompt {
	Array<TaskTitledList> titled_lists;
	One<TaskTitledList> pre_answer;
	int response_length = 0;
	
	void Clear() {
		titled_lists.Clear();
		pre_answer.Clear();
		response_length = 0;
	}
	TaskTitledList& PreAnswer() {
		if (pre_answer.IsEmpty()) {
			pre_answer.Create();
			pre_answer->result_list = true;
		}
		return *pre_answer;
	}
	TaskTitledList& AddSub() {return titled_lists.Add();}
	
	bool IsEmpty() const {return titled_lists.IsEmpty() && pre_answer.IsEmpty();}
	String AsString() const;
	String GetTreeString() const;
	
	int GetCount() const {return titled_lists.GetCount() + (pre_answer.IsEmpty() ? 0 : 1);}
	TaskTitledList& operator[](int i) {
		if (i == titled_lists.GetCount())
			return *pre_answer;
		return titled_lists[i];
	}
	const TaskTitledList& operator[](int i) const {
		if (i == titled_lists.GetCount())
			return *pre_answer;
		return titled_lists[i];}
	
};



END_TEXTLIB_NAMESPACE


#endif
