#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN


PlayTokenizer::PlayTokenizer() : ErrorSource("PlayTokenizer") {
	
}

Token& PlayTokenizer::Add(int token_id) {
	struct Token& t = tokens.Add();
	t.loc = loc;
	t.end = loc;
	t.end.col++;
	t.type = token_id;
	return t;
}

bool PlayTokenizer::Process(String str, String path) {
	input = str.ToWString();
	
	loc.file = path;
	loc.line = 1;
	loc.col = 0;
	loc.cursor = 0;
	
	int& cursor = loc.cursor;
	WString s;
	
	while (cursor < input.GetCount()) {
		loc.cursor = cursor;
		loc.col++;
		
		int chr = input[cursor++];
		int chr1 = cursor < input.GetCount() ? input[cursor] : 0;
		
		if (state == ANY) {
			if (chr == '\n') {
				Add(TK_NEWLINE);
				loc.col = 0;
				loc.line++;
			}
			else if (chr == '\r' || chr == '\t' || chr == ' ') {
				continue;
			}
			else if (chr == '\"') {
				state = STRING;
				s.Clear();
			}
			else if (chr == ':') {
				Add(TK_COLON);
			}
			else if (chr == '/' && chr1 == '/') {
				cursor++;
				Add(TK_COMMENT);
			}
			else if (chr == '*' && chr1 == '*') {
				cursor++;
				Add(TK_BLOCK_COMMENT);
			}
			else if (chr == '#') {
				Add(TK_NUMBERSIGN);
			}
			else {
				state = WORD;
				s.Clear();
				s.Cat(chr);
			}
		}
		else if (state == WORD) {
			if (chr == '\n') {
				Add(TK_ID).str_value = s.ToString();
				Add(TK_NEWLINE);
				loc.col = 0;
				loc.line++;
				state = ANY;
			}
			else if (chr == '\r' || chr == '\t' || chr == ' ' || chr == '*') {
				Add(TK_ID).str_value = s.ToString();
				state = ANY;
				cursor--;
				continue;
			}
			else if (chr == ':') {
				Add(TK_ID).str_value = s.ToString();
				Add(TK_COLON);
				state = ANY;
			}
			else {
				s.Cat(chr);
			}
		}
		else if (state == STRING) {
			if (chr == '\"') {
				Token& t = Add(TK_STRING);
				t.str_value = s.ToString();
				state = ANY;
			}
			else {
				s.Cat(chr);
			}
		}
		else Panic("Invalid state");
		
	}
	
	Add(TK_EOF);
	
	return true;
}

void PlayTokenizer::Dump() const {
	LOG("Dumping tokenizer:");
	String prev_file;
	for(int i = 0; i < tokens.GetCount(); i++) {
		const Token& tk = tokens[i];
		if (tk.loc.file != prev_file) {
			prev_file = tk.loc.file;
			LOG("\tfile: " << prev_file);
		}
		
		LOG("\t[" << i << "] (" << tk.loc.line << ":" << tk.loc.col << ") = " <<
			tk.GetTypeString() << ": " << tk.GetTextValue());
	}
}












PlayParser::PlayParser(PlayScript& script) : ErrorSource("PlayParser"), script(script) {
	
}

bool PlayParser::Process(const Vector<Token>& tokens) {
	this->tokens = &tokens;
	cursor = 0;
	
	
	if (!ParseScript(script))
		return false;
	
	
	return true;
}

bool PlayParser::ParseScript(PlayScript& s) {
	
	if (!ParseMetaText(s.title)) return false;
	if (!ParseMetaText(s.description)) return false;
	if (!ParseMetaText(s.disclaimer)) return false;
	if (!ParseMetaText(s.author)) return false;
	if (!ParsePlayDialogue(s.actors)) return false;
	if (!ParseParts(s)) return false;
	
	return true;
}

bool PlayParser::IsPartToken(const Token& t) {
	if (t.IsType(TK_ID)) {
		String s = t.GetTextValue();
		return s == "Part" || s == "Osa";
	}
	return false;
}

bool PlayParser::IsSectionToken(const Token& t) {
	if (t.IsType(TK_ID)) {
		String s = t.GetTextValue();
		return s == "Section" || s == "Luku";
	}
	return false;
}

bool PlayParser::ParseParts(PlayScript& s) {
	PassEmpty();
	
	while (!IsEof()) {
		PassEmpty();
		
		{
			const Token& t = Current();
			if (!IsPartToken(t))
				break;
		}
		
		PlayPart& part = s.parts.Add();
		part.idx = s.parts.GetCount()-1;
		if (!ParsePart(part))
			return false;
		
		{
			const Token& t = Current();
			if (t.IsType(TK_NEWLINE)) {
				Next();
				if (!IsEof() && Current().IsType(TK_NEWLINE)) {
					Next();
					break;
				}
			}
		}
	}
	
	if (s.parts.IsEmpty()) {
		AddError(Current().loc, "Expected at least one part");
		return false;
	}
	
	return true;
}

bool PlayParser::ParsePart(PlayPart& p) {
	PassEmpty();
	
	if (!IsPartToken(Current())) {
		AddError(Current().loc, "Expected part-token");
		return false;
	}
	Next();
	if (!CheckEof()) return false;
	int i = ScanInt(Current().GetTextValue());
	if (i-1 != p.idx) {
		AddError(Current().loc, "Unexpected part id: " + IntStr(i) + " != " + IntStr(p.idx+1));
		return false;
	}
	Next();
	if (!CheckEof()) return false;
	if (!CheckColon()) return false;
	Next();
	if (!CheckEof()) return false;
	if (!ParseSentenceEol(p.title, false)) return false;
	
	
	while (!IsEof()) {
		PassEmpty();
		
		{
			const Token& t = Current();
			if (!IsSectionToken(t))
				break;
		}
		
		PlaySection& sect = p.sections.Add();
		sect.idx = p.sections.GetCount()-1;
		if (!ParseSection(sect))
			return false;
		
		{
			const Token& t = Current();
			if (t.IsType(TK_NEWLINE)) {
				Next();
				if (!IsEof() && Current().IsType(TK_NEWLINE)) {
					Next();
					break;
				}
			}
		}
	}
	
	if (p.sections.IsEmpty()) {
		AddError(Current().loc, "Expected at least one part");
		return false;
	}
	
	
	return true;
}

bool PlayParser::ParseSection(PlaySection& s) {
	PassEmpty();
	
	if (!IsSectionToken(Current())) {
		AddError(Current().loc, "Expected section-token");
		return false;
	}
	Next();
	if (!CheckEof()) return false;
	int i = ScanInt(Current().GetTextValue());
	if (i-1 != s.idx) {
		AddError(Current().loc, "Unexpected section id: " + IntStr(i) + " != " + IntStr(s.idx+1));
		return false;
	}
	Next();
	if (!CheckEof()) return false;
	if (!CheckColon()) return false;
	Next();
	if (!CheckEof()) return false;
	if (!ParseSentenceEol(s.title, false)) return false;
	if (!ParsePlayDialogue(s.dialog)) return false;
	
	return true;
}

bool PlayParser::CheckEof() {
	if (IsEof()) {
		AddError(Current().loc, "Unexpected end-of-file");
		return false;
	}
	return true;
}

bool PlayParser::CheckColon() {
	const Token& t = Current();
	if (!t.IsType(TK_COLON)) {
		AddError(t.loc, "Expected ':'");
		return false;
	}
	return true;
}

bool PlayParser::ParseMetaText(MetaText& txt) {
	PassEmpty();
	
	while (!IsEof()) {
		PlaySentence& sent = txt.sents.Add();
		
		if (!ParseSentence(sent, false))
			return false;
		
		const Token& t = Current();
		if (t.IsType(TK_NEWLINE)) {
			Next();
			if (!IsEof() && Current().IsType(TK_NEWLINE)) {
				Next();
				break;
			}
		}
	}
	
	if (txt.sents.IsEmpty()) {
		AddError(Current().loc, "Expected meta-text");
		return false;
	}
	
	return true;
}

bool PlayParser::CheckEol() {
	const Token& t = Current();
	if (!t.IsType(TK_NEWLINE)) {
		AddError(t.loc, "Expected newline");
		return false;
	}
	Next();
	return true;
}

bool PlayParser::ParseSentenceEol(PlaySentence& sent, bool opt_voice_id) {
	
	if (!ParseSentence(sent, opt_voice_id))
		return false;
	
	return CheckEol();
}

#if 0
bool PlayParser::ParseTiming(PlayLine& l) {
	if (Current().IsType(TK_ID)) {
		String a = Current().GetTextValue();
		if (a.Left(1) == "[") {
			Next();
			if (Current().IsType(TK_COLON)) {
				Next();
				if (Current().IsType(TK_ID)) {
					String b = Current().GetTextValue();
					if (b.Right(1) == "]") {
						Next();
						a = a.Mid(1);
						b = b.Left(b.GetCount()-1);
						int min = ScanInt(a);
						int sec = ScanInt(b);
						if (min >= 0 && min < 10000 && sec >= 0 && sec < 60) {
							l.is_meta = true;
							l.time = min * 60 + sec;
							return CheckEol();
						}
					}
				}
			}
		}
	}
	
	AddError(Current().loc, "Invalid time declaration");
	return false;
}
#endif

bool PlayParser::ParseSentence(PlaySentence& p, bool opt_voice_id) {
	
	if (opt_voice_id && Current().IsType(TK_ID)) {
		WString txt = Current().GetTextValue().ToWString();
		if (txt.GetCount() && txt[0] == '(') {
			Next();
			if (txt.GetCount() == 1) {
				while (!IsEof()) {
					txt += Current().GetTextValue().ToWString();
					Next();
					if (txt[txt.GetCount()-1] == ')')
						break;
				}
			}
			if (txt[0] == '(' && txt[txt.GetCount()-1] == ')') {
				p.voice_id = txt.Mid(1, txt.GetCount()-2);
			}
			else {
				AddError(Current().loc, "invalid voice id");
				return false;
			}
		}
	}
	
	while (!IsEof()) {
		const Token& t = Current();
		if (t.IsType(TK_ID) || t.IsType(TK_STRING)) {
			p.tokens.Add(t);
			Next();
		}
		else
			break;
	}
	
	if (p.tokens.IsEmpty()) {
		const Token& t = Current();
		DUMP(t);
		AddError(Current().loc, "Expected text");
		return false;
	}
	
	return true;
}

void PlayParser::PassEmpty() {
	while (!IsEof()) {
		const Token& t = Current();
		if (t.IsType(TK_NEWLINE))
			Next();
		else
			break;
	}
}

bool PlayParser::ParsePlayDialogue(PlayDialogue& p) {
	PassEmpty();
	
	while (!IsEof()) {
		if (IsSectionToken(Current()) || IsPartToken(Current()))
			break;
		
		PlayLine& l = p.lines.Add();
		
		if (!ParsePlayLine(l))
			return false;
		
		if (p.lines.GetCount() >= 2) {
			PlayLine& prev = p.lines[p.lines.GetCount()-2];
			if ((prev.is_narration && l.is_narration) ||
				(prev.is_comment && l.is_comment) ||
				(prev.is_meta && l.is_meta)) {
				prev.sents.Append(l.sents);
				p.lines.Remove(p.lines.GetCount()-1);
			}
		}
		
		PassEmpty();
	}
	
	if (p.lines.IsEmpty()) {
		AddError(Current().loc, "Expected lines");
		return false;
	}
	
	return true;
}

bool PlayParser::ParsePlayLine(PlayLine& l) {
	if (Current().IsType(TK_BLOCK_COMMENT)) {
		Next();
		l.is_narration = true;
		
		PlaySentence& sent = l.sents.Add();
		if (!ParseSentence(sent, false))
			return false;
		
		if (!Current().IsType(TK_BLOCK_COMMENT)) {
			AddError(Current().loc, "Expected end of narration '**'");
			return false;
		}
		Next();
	}
	else if (Current().IsType(TK_NUMBERSIGN)) {
		Next();
		l.is_meta = true;
		
		#if 0
		if (Current().IsType(TK_ID) && Current().GetTextValue().Left(1) == "[") {
			ParseTiming(l);
		}
		else
		#endif
		{
			PlaySentence& sent = l.sents.Add();
			if (!ParseSentenceEol(sent, false))
				return false;
		}
	}
	else {
		if (Current().IsType(TK_COMMENT)) {
			Next();
			l.is_comment = true;
		}
		else {
			{
				const Token& t = Current();
				if (!t.IsType(TK_ID)) {
					AddError(t.loc, "Expected identifier");
					return false;
				}
				l.id.name = t.GetTextValue().ToWString();
				Next();
			}
			
			{
				const Token& t = Current();
				if (!CheckColon())
					return false;
				Next();
			}
		}
		
		while (!IsEof()) {
			{
				const Token& t = Current();
				const Token* n = GetNext();
				if (t.IsType(TK_ID) && n && n->IsType(TK_COLON))
					break;
				if (t.IsType(TK_NEWLINE))
					break;
				if (t.IsType(TK_COMMENT) || t.IsType(TK_BLOCK_COMMENT))
					break;
			}
			
			PlaySentence& sent = l.sents.Add();
			if (!ParseSentenceEol(sent, true))
				return false;
		}
		
		if (l.sents.IsEmpty()) {
			AddError(Current().loc, "Expected sentences");
			return false;
		}
	}
	return true;
}




String PlayPart::ToString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << "Part " << idx+1 << " (" << title.ToString(-1) << "):\n";
	for (const PlaySection& sect : sections)
		s << sect.ToString(indent+1);
	return s;
}

String PlaySection::ToString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << "Section " << idx+1 << " (" << title.ToString(-1) << "):\n";
	s << dialog.ToString("Dialog", indent+1);
	return s;
}

String PlayIdentifier::ToString() const {
	if (name.IsEmpty())
		return "<PlayIdentifier>";
	return name.ToString();
}

PlaySentence& PlaySentence::Set(String txt) {
	tokens.Clear();
	Token& t = tokens.Add();
	t.type = TK_ID;
	t.str_value = txt;
	return *this;
}


String PlaySentence::ToString(int indent) const {
	String s;
	if (indent >= 0)
		s.Cat('\t', indent);
	int i = 0;
	//if (voice_id.GetCount())
	//	s << "[voice " << voice_id.ToString() << "] ";
	for (const Token& t : tokens) {
		if (i++ > 0)
			s.Cat(' ');
		s << t.GetTextValue();
	}
	if (indent >= 0)
		s.Cat('\n');
	return s;
}

Value PlaySentence::GetData() const {
	String s = ToString();
	
	return s;
}

String PlayLine::ToString(int indent) const {
	String s;
	s.Cat('\t', indent);
	if (is_comment) {
		s << "Comment:\n";
		for (const PlaySentence& sent : sents)
			s << sent.ToString(indent+1);
	}
	else if (is_narration) {
		s << "Narration:\n";
		for (const PlaySentence& sent : sents)
			s << sent.ToString(indent+1);
	}
	else {
		s << id.ToString() << ":\n";
		for (const PlaySentence& sent : sents)
			s << sent.ToString(indent+1);
	}
	return s;
}

String MetaText::ToString(String title, int indent) const {
	String s;
	if (title.IsEmpty())
		title = "<MetaText>";
	s.Cat('\t', indent);
	s << title << ":\n";
	for (const PlaySentence& sent : sents)
		s << sent.ToString(indent+1);
	return s;
}

String PlayDialogue::ToString(String title, int indent) const {
	String s;
	if (title.IsEmpty())
		title = "<PlayDialogue>";
	s.Cat('\t', indent);
	s << title << ":\n";
	for (const PlayLine& line : lines)
		s << line.ToString(indent+1);
	return s;
}

String PlayScript::ToString(int indent) const {
	String s;
	s << title.ToString("Title");
	s << description.ToString("Description");
	s << disclaimer.ToString("Disclaimer");
	s << author.ToString("Author");
	s << actors.ToString("Actors");
	
	s.Cat('\t', indent);
	s << "Parts:\n";
	for (const PlayPart& p : parts) {
		s << p.ToString(indent+1);
	}
	
	return s;
}


#define LW 96

String GetPartString() {
	return "Osa";
}

String GetSectionString() {
	return "Luku";
}


String PlayScript::ToScript() const {
	String s;
	
	s << title.ToScript() << "\n\n";
	s << description.ToScript() << "\n\n";
	s << disclaimer.ToScript() << "\n\n";
	s << author.ToScript() << "\n\n";
	
	s << actors.ToScript() << "\n\n";
	
	for (const PlayPart& p : parts)
		s << p.ToScript() << "\n\n";
	
	s << GetSubtitleExtensionScript();
	s << GetNotesExtensionScript();
	
	return s;
}

String PlayScript::GetSubtitleExtensionScript() const {
	String s;
	Index<unsigned> used_hashes;
	
	s << "<Extension: Subtitle-time>\n";
	for (const Subtitle& st : subtitles) {
		WString str = st.str;
		unsigned h = str.GetHashValue();
		while (used_hashes.Find(h) >= 0) {
			str.Cat('_');
			h = str.GetHashValue();
		}
		used_hashes.Add(h);
		
		if (st.time >= 0)
			s << HexStr(h).Mid(2) << "," << st.time << "\n";
	}
	s << "\n";
	
	return s;
}

String PlayScript::GetNotesExtensionScript() const {
	String s;
	s << "<Extension: Notes-time>\n";
	for(int i = 0; i < input_ext_notes.GetCount(); i++) {
		int part = input_ext_notes.GetKey(i);
		const auto& p = input_ext_notes[i];
		for(int j = 0; j < p.GetCount(); j++) {
			int sect = p.GetKey(j);
			const NoteData& n = p[j];
			s << part << "," << sect << "," << n.time;
			if (n.fps > 0.0)
				s << "," << n.fps;
			s << "\n";
		}
	}
	s << "\n";
	return s;
}

String MetaText::ToScript() const {
	String s;
	
	for (const PlaySentence& ps : sents)
		s << CenteredString(ps.ToString(), LW) << "\n";
	
	return s;
}

Value MetaText::GetData() const {
	String s;
	
	for (const PlaySentence& ps : sents) {
		if (!s.IsEmpty()) s.Cat('\n');
		s << ps.ToString();
	}
	
	return s;
}

String PlayPart::ToScript() const {
	String s;
	
	s << CenteredString(GetPartString() + " " + IntStr(idx+1) + ": " + title.ToString(), LW) << "\n\n";
	
	for (const PlaySection& ps : sections) {
		s << ps.ToScript() << "\n\n";
	}
	
	return s;
}

String PlaySection::ToScript() const {
	String s;
	
	s << CenteredString(GetSectionString() + " " + IntStr(idx+1) + ": " + title.ToString(), LW) << "\n\n";
	
	s << dialog.ToScript();
	
	return s;
}

String PlayDialogue::ToScript() const {
	String s;
	
	for (const PlayLine& l : lines) {
		s << l.ToScript();
	}
	s << "\n";
	
	return s;
}

String PlayLine::GetId() const {
	if (is_comment) {
		return "Comment";
	}
	else if (is_narration) {
		return "Narrator";
	}
	else if (is_meta) {
		return "Meta";
	}
	else {
		return id.name.ToString();
	}
}

String PlayLine::ToScript() const {
	String s;
	
	if (is_comment) {
		s << "\n";
		for (const PlaySentence& ps : sents)
			s << "// " << ps.ToScript() << "\n";
		s << "\n";
	}
	else if (is_narration) {
		s << "\n";
		for (const PlaySentence& ps : sents)
			s << "    ** " + ps.ToScript() + " **" << "\n";
			//s << CenteredString("** " + ps.ToScript() + " **", LW) << "\n";
		s << "\n";
	}
	else if (is_meta) {
		for (const PlaySentence& ps : sents)
			s << "#" + ps.ToScript() << "\n";
	}
	else {
		s << id.ToScript() << ": ";
		int c = s.ToWString().GetCount();
		static const int indent = 13;
		if (c < indent)
			s.Cat(' ', indent - c);
		for(int i = 0; i < sents.GetCount(); i++) {
			const PlaySentence& ps = sents[i];
			if (i) s.Cat(' ', indent);
			s << ps.ToScript() << "\n";
		}
	}
	
	return s;
}

String PlaySentence::ToScript() const {
	String s;
	int i = 0;
	//if (voice_id.GetCount())
	//	s << "(" << voice_id.ToString() << ") ";
	for (const Token& t : tokens) {
		if (i++ > 0)
			s.Cat(' ');
		s << t.GetTextValue();
	}
	return TrimBoth(s);
}

String PlayIdentifier::ToScript() const {
	return name.ToString();
}





void PlayScript::LoadExtension(String s) {
	Vector<String> lines = Split(s, "\n");
	if (lines.IsEmpty()) return;
	String header = TrimBoth(lines[0]);
	if (header.Right(1) == ">") header = header.Left(header.GetCount()-1);
	header = ToLower(header);
	
	if (header == "subtitle-time") {
		input_ext_time.Clear();
		
		for(int i = 1; i < lines.GetCount(); i++) {
			const String& line = lines[i];
			int j = line.Find(",");
			if (j == -1) continue;
			String hash = line.Left(j);
			String timestr = line.Mid(j+1);
			unsigned h = HexInt64("0x" + hash);
			int time = StrInt(timestr);
			if (time >= 0)
				input_ext_time.Add(h, time);
		}
		
	}
	else if (header == "notes-time") {
		input_ext_notes.Clear();
		for(int i = 1; i < lines.GetCount(); i++) {
			const String& line = lines[i];
			Vector<String> parts = Split(line, ",");
			if (parts.GetCount() < 3) {
				ASSERT(0);
				LOG("error: line does not have 3 parts: " << line);
				continue;
			}
			int part = ScanInt(parts[0]);
			int sect = ScanInt(parts[1]);
			int time = ScanInt(parts[2]);
			double fps = 0;
			if (parts.GetCount() >= 4)
				fps = ScanDouble(parts[3]);
			input_ext_notes.GetAdd(part).GetAdd(sect).Set(time, fps);
		}
		//DUMPC(input_ext_notes);
		
	}
	else {
		PromptOK("Unsupported extension: " + header);
	}
}

void PlayScript::MakeSubtitles() {
	subtitles.Clear();
	used_hashes.Clear();
	
	beginning.id.name = "Meta";
	beginning.is_meta = true;
	beginning.sents.Clear();
	AddSubtitle(beginning, beginning.sents.Add().Set("<Beginning>"));
	
	intro_line.id.name = String("Narrator").ToWString();
	intro_line.is_narration = true;
	for (PlaySentence& sent : title.sents)       AddSubtitle(intro_line, sent);
	for (PlaySentence& sent : description.sents) AddSubtitle(intro_line, sent);
	for (PlaySentence& sent : disclaimer.sents)  AddSubtitle(intro_line, sent);
	for (PlaySentence& sent : author.sents)      AddSubtitle(intro_line, sent);
	
	for (PlayPart& part : parts) {
		for (PlaySection& sect : part.sections) {
			for (PlayLine& line : sect.dialog.lines) {
				if (line.is_comment || line.is_meta)
					continue;
				
				for (PlaySentence& sent : line.sents) {
					AddSubtitle(line, sent);
				}
			}
		}
	}
	
	ending.id.name = "Meta";
	ending.is_meta = true;
	ending.sents.Clear();
	AddSubtitle(ending, ending.sents.Add().Set("<Ending>"));
	//DUMPC(subtitles);
}

void PlayScript::AddSubtitle(PlayLine& line, PlaySentence& sent) {
	String s = sent.ToScript();
	if (s == "-")
		return;
	
	int part_i = 0;
	int a = 0;
	int f = 0;
	
	Color clr = Black();
	String id = line.GetId();
	int i = tmp_actors.Find(id);
	ASSERT(i >= 0);
	if (i >= 0) {
		Actor& a = tmp_actors[i];
		clr = a.normal_paper;
	}
	
	while (1) {
		int f0 = s.Find(". ", f+1);
		int f1 = s.Find(", ", f+1);
		f = f0 == -1 ? f1 : f0;
		if (f < 0) break;
		
		int b = f+1;
		
		String part = s.Mid(a, b-a);
		
		if (part.Find(" ") == -1 && part.Right(1) == ",")
			continue;
		
		Subtitle& st = subtitles.Add();
		st.str = part.ToWString();
		
		// Find unique subtitle hash
		WString str = st.str;
		unsigned h = str.GetHashValue();
		while (used_hashes.Find(h) >= 0) {
			str.Cat('_');
			h = str.GetHashValue();
		}
		used_hashes.Add(h);
		
		int i = input_ext_time.Find(h);
		if (i >= 0)
			st.time = input_ext_time[i];
		
		if (subtitles.GetCount() == 1) st.time = 0;
		st.line = &line;
		st.sent = &sent;
		st.part_i = part_i++;
		st.clr = clr;
		
		a = b+1;
	}
	
	int b = s.GetCount();
	String part = s.Mid(a, b-a);
	Subtitle& st = subtitles.Add();
	st.str = part.ToWString();
	
	// Find unique subtitle hash
	WString str = st.str;
	unsigned h = str.GetHashValue();
	while (used_hashes.Find(h) >= 0) {
		str.Cat('_');
		h = str.GetHashValue();
	}
	used_hashes.Add(h);
	
	i = input_ext_time.Find(h);
	if (i >= 0)
		st.time = input_ext_time[i];
	
	if (subtitles.GetCount() == 1) st.time = 0;
	st.line = &line;
	st.sent = &sent;
	st.part_i = part_i++;
	st.clr = clr;
	
}

void PlayScript::MakeActors() {
	tmp_actors.Clear();
	
	int i = 0;
	for (PlayLine& pl : actors.lines) {
		String id = pl.id.name.ToString();
		
		Actor& act = tmp_actors.Add(id);
		act.name = id;
		act.idx = i++;
		act.normal_paper = RandomColor(256-64, 64);
		act.line = &pl;
		
		{
			String desc = pl.sents[0].GetData();
			int a = desc.Find("Color(");
			if (a >= 0) {
				a += 6;
				int b = desc.Find(")", a);
				if (b >= 0) {
					String clr_str = desc.Mid(a, b-a);
					Vector<String> comps = Split(clr_str, ",");
					if (comps.GetCount() == 3) {
						int r = ScanInt(TrimBoth(comps[0]));
						int g = ScanInt(TrimBoth(comps[1]));
						int b = ScanInt(TrimBoth(comps[2]));
						act.normal_paper = Color(r,g,b);
					}
				}
			}
		}
	}
	
	Actor& narrator = tmp_actors.Add("Narrator");
	narrator.name = "Narrator";
	narrator.normal_paper = GrayColor(256-64);
	narrator.idx = i++;
	
	Actor& comment = tmp_actors.Add("Comment");
	comment.name = "Comment";
	comment.normal_paper = Color(256-64, 255, 256-64);
	comment.idx = i++;
	
	Actor& meta = tmp_actors.Add("Meta");
	meta.name = "Meta";
	meta.normal_paper = Color(255, 256-64, 256-64);
	meta.idx = i++;
	
}

bool PlayScript::CheckReferences() {
	Index<String> failed;
	bool succ = true;
	
	for (const PlayPart& part : parts) {
		for (const PlaySection& sect : part.sections) {
			for (const PlayLine& line : sect.dialog.lines) {
				String id = line.id.name.ToString();
				
				if (id.IsEmpty()) continue;
				
				int i = tmp_actors.Find(id);
				if (i < 0 && failed.Find(id) < 0) {
					LOG("PlayScript::CheckReferences: error: actor '" << id << "' is not added to the actor list");
					succ = false;
					failed.Add(id);
				}
				
			}
		}
	}
	
	return succ;
}

const PlayScript::Actor& PlayScript::GetActor(const PlayLine& line) const {
	String key;
	if (line.is_comment)
		key = "Comment";
	else if (line.is_narration)
		key = "Narrator";
	else if (line.is_meta)
		key = "Meta";
	else
		key = line.id.name.ToString();
	
	int i = tmp_actors.Find(key);
	if (i == -1) Panic("Internal error: invalid actor key");
	return tmp_actors[i];
}

int PlayScript::FindSubtitle(int time) const {
	int i = 0;
	for (const Subtitle& st : subtitles) {
		if (st.time >= time)
			return i;
		i++;
	}
	return -1;
}

const PlayScript::Subtitle& PlayScript::Get(int i) const {
	return subtitles[i];
}

int PlayScript::GetLastSubtitleTiming() const {
	for (int i = subtitles.GetCount()-1; i >= 0; i--) {
		const Subtitle& st = subtitles[i];
		if (st.time >= 0)
			return st.time;
	}
	return -1;
}

int PlayScript::GetTotalTime() const {
	const PlaySection& sect = parts.Top().sections.Top();
	for(int i = sect.dialog.lines.GetCount()-1; i >= 0; i--) {
		const PlayLine& line = sect.dialog.lines[i];
		for(int j = line.sents.GetCount()-1; j >= 0; j--) {
			const PlaySentence& sent = line.sents[j];
			if (sent.tmp_time >= 0) {
				int end = sent.tmp_time + sent.tmp_duration;
				return end;
			}
		}
	}
	ASSERT(0);
	return 0;
}

void PlayScript::MakeTempPlaySentenceTimes() {
	Vector<PlaySentence*> sents;
	sents.Reserve(10000);
	
	Vector<MetaText*> intro_metatext;
	intro_metatext << &title << &description << &disclaimer << &author;
	
	for (MetaText* t : intro_metatext) {
		MetaText& mt = *t;
		for (PlaySentence& sent : mt.sents) {
			sent.tmp_time = -1;
			sent.tmp_duration = 0;
			sents.Add(&sent);
		}
	}
	
	for (PlayPart& part : parts) {
		for (PlaySection& sect : part.sections) {
			for (PlayLine& line : sect.dialog.lines) {
				for (PlaySentence& sent : line.sents) {
					sent.tmp_time = -1;
					sent.tmp_duration = 0;
					sents.Add(&sent);
				}
			}
		}
	}
	
	PlaySentence* prev = 0;
	
	for (Subtitle& st : subtitles) {
		if (st.sent == prev)
			continue;
		prev = st.sent;
		
		st.sent->tmp_time = st.time;
	}
	
	if (0) {
		int i = 0;
		for (PlaySentence* sent : sents) {
			LOG(i++ << ": " << sent->tmp_time << "\t" << sent->GetData());
		}
	}
	
	prev = 0;
	int prev_time = 0;
	for(int i = 0; i < sents.GetCount(); i++) {
		PlaySentence& a = *sents[i];
		
		/*if (i == 40) {
			LOG("");
		}*/
		
		if (a.tmp_time < 0) {
			bool found = false;
			for(int j = i+1; j < sents.GetCount(); j++) {
				PlaySentence& b = *sents[j];
				
				if (b.tmp_time > prev_time) {
					a.tmp_time = (prev_time + b.tmp_time) / 2;
					prev_time = a.tmp_time;
					found = true;
					break;
				}
			}
			
			if (!found) {
				a.tmp_time = ++prev_time;
			}
		}
		else if (a.tmp_time < prev_time) {
			a.tmp_time = ++prev_time;
		}
		else {
			prev_time = a.tmp_time;
		}
		
		ASSERT(!prev || a.tmp_time > prev->tmp_time);
		prev = &a;
	}
	
	prev = 0;
	for (PlaySentence* sent : sents) {
		if (prev) {
			prev->tmp_duration = sent->tmp_time - prev->tmp_time;
			ASSERT(prev->tmp_duration > 0);
		}
		prev = sent;
	}
	prev->tmp_duration = 1000;
	
}

void PlayScript::LoadImages() {
	author_img.Clear();
	subscribe.Clear();
	logo.Clear();
	
	String dir = GetFileDirectory(filepath);
	if (!DirectoryExists(dir))
		return;
	
	String logo_path = AppendFileName(dir, "logo.png");
	String author_path = AppendFileName(dir, "author.png");
	String subscribe_path = AppendFileName(dir, "subscribe.png");
	
	if (FileExists(logo_path))
		logo		= StreamRaster::LoadFileAny(logo_path);
	if (FileExists(author_path))
		author_img	= StreamRaster::LoadFileAny(author_path);
	if (FileExists(subscribe_path))
		subscribe	= StreamRaster::LoadFileAny(subscribe_path);
	
}

bool PlayScript::CheckMusical() {
	String dir = GetFileDirectory(filepath);
	
	int musical_idx = 0;
	for (PlayPart& part : parts) {
		for (PlaySection& sect : part.sections) {
			sect.musical_idx = -1;
			for (PlayLine& line : sect.dialog.lines) {
				
				if (line.is_meta && line.sents.GetCount() && line.sents[0].tokens.GetCount()) {
					const PlaySentence& sent = line.sents[0];
					const Token& meta_token = sent.tokens[0];
					
					if (meta_token.IsType(TK_ID)) {
						String str = meta_token.GetTextValue();
						if (str == "Musiikki" || str == "Music") {
							sect.musical_idx = musical_idx++;
							sect.musical_dir.Clear();
							
							String s = Format("%02d", sect.musical_idx + 1);
							FindFile ff;
							if (ff.Search(AppendFileName(dir, s + " *"))) {
								do {
									if (ff.IsDirectory()) {
										sect.musical_dir = ff.GetPath();
										break;
									}
								}
								while (ff.Next());
							}
							
							if (sect.musical_dir.IsEmpty()) {
								LOG("Could not find musical directory with beginning '" + s + "'");
								return false;
							}
							
							if (ff.Search(AppendFileName(sect.musical_dir, "notes *.png"))) {
								int min = INT_MAX, max = 0;
								int count = 0;
								int idx_digits = 0;
								do {
									String filename = ff.GetName();
									String numstr = filename.Mid(6, filename.GetCount() - 6 - 4);
									int num = ScanInt(numstr);
									if (num < min) min = num;
									if (num > max) max = num;
									count++;
									idx_digits = std::max(idx_digits, numstr.GetCount());
								}
								while (ff.Next());
								
								if (count == 0) {
									LOG("No images in musical directory " + sect.musical_dir);
									return false;
								}
								
								LOG("Image range in '" + sect.musical_dir + "': min " << min << ", max " << max << ", count " << count);
								sect.notes_min = min;
								sect.notes_max = max;
								sect.notes_idx_digits = idx_digits;
								
								
								auto& part_data = input_ext_notes.GetAdd(part.idx+1);
								int i = part_data.Find(sect.idx+1);
								if (i >= 0) {
									NoteData& n = part_data[i];
									if (n.time >= 0) {
										sect.musical_time = n.time;
										if (n.fps >= 0)
											sect.musical_fps = n.fps;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	return true;
}

const PlaySection* PlayScript::FindSection(int time, bool musical) const {
	const PlaySection* ret = 0;
	
	for (const PlayPart& part : parts) {
		for (const PlaySection& sect : part.sections) {
			if (musical && sect.musical_time >= 0) {
				if (sect.musical_time > time)
					return ret;
				if (sect.musical_time <= time)
					ret = &sect;
			}
			else {
				for (const PlayLine& line : sect.dialog.lines) {
					if (!line.is_meta && !line.is_comment && line.sents.GetCount()) {
						const PlaySentence& sent = line.sents[0];
						
						if (sent.tmp_time > time)
							return ret;
						if (sent.tmp_time <= time)
							ret = &sect;
						
						break;
					}
				}
			}
		}
	}
	return ret;
}

int PlayDialogue::GetFirstTime() const {
	for (const PlayLine& line : lines) {
		if (!line.is_meta && !line.is_comment && line.sents.GetCount()) {
			const PlaySentence& sent = line.sents[0];
			return sent.tmp_time;
		}
	}
	return -1;
}

int PlayDialogue::GetFirstActorTime() const {
	for (const PlayLine& line : lines) {
		if (!line.is_meta && !line.is_comment && !line.is_narration && line.sents.GetCount()) {
			const PlaySentence& sent = line.sents[0];
			return sent.tmp_time;
		}
	}
	return -1;
}



String PlayScript::Subtitle::ToString() const {
	return IntStr(time) + "\t" + str.ToString();
}


NAMESPACE_TOPSIDE_END
