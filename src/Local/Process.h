#ifndef _Local_Process_h_
#define _Local_Process_h_

#define IMMEDIATE_TYPES_EQUAL(T) bool operator==(const T& t) const {return MemoryCompare(this, &t, sizeof(T)) == 0;}


NAMESPACE_TOPSIDE_BEGIN

struct FileLocation : Moveable<FileLocation> {
	String file;
	int cursor = -1;
	int line = -1;
	int col = -1;
	
	bool operator==(const FileLocation& t) const {
		return	file == t.file &&
				cursor == t.cursor &&
				line == t.line &&
				col == t.col;
	}
	void Clear() {file.Clear(); cursor = -1; line = -1; col = -1;}
	void SetFileLocation(const FileLocation& loc) {*this = loc;}
	void operator=(const FileLocation& loc) {
		file = loc.file;
		cursor = loc.cursor;
		line = loc.line;
		col = loc.col;
	}
	void Serialize(Stream& s) {s % file % cursor % line % col;}
	bool operator<(const FileLocation& l) const {
		if (file != l.file) return file < l.file;
		if (line != l.line) return line < l.line;
		return col < l.col;
	}
	bool operator>(const FileLocation& l) const {
		if (file != l.file) return file > l.file;
		if (line != l.line) return line > l.line;
		return col > l.col;
	}
	String ToString() const {return file + ":" + IntStr(line) + ":" + IntStr(col);}
	
};


enum { PROCMSG_UNKNOWN, PROCMSG_SKIP, PROCMSG_INFO, PROCMSG_WARNING, PROCMSG_ERROR };

struct ProcMsg : Moveable<ProcMsg>, public FileLocation {
	int severity = 0;
	String src;
	String msg;

	ProcMsg() {}
	ProcMsg(const ProcMsg& e) { *this = e; }
	ProcMsg(String source, FileLocation loc, int severity, String msg) {
		this->src = source;
		SetFileLocation(loc);
		this->severity = severity;
		this->msg = msg;
	}
	
	bool operator==(const ProcMsg& t) const {
		return	severity == t.severity &&
				src == t.src &&
				msg == t.msg &&
				FileLocation::operator==(t);
	}
	
	void operator=(const ProcMsg& e) {
		FileLocation::operator=(e);
		severity = e.severity;
		src = e.src;
		msg = e.msg;
	}
	
	void Serialize(Stream& s) {FileLocation::Serialize(s); s % severity % src % msg;}
	
	ProcMsg& Set(FileLocation loc, int severity, String src, String msg) {
		SetFileLocation(loc);
		this->severity = severity;
		this->src = src;
		this->msg = msg;
		return *this;
	}
	
	String ToString() const {
		String s;
		if (src.GetCount())
			s << ToUpper(src) << ": ";
		s	<< GetFileName(file)
			<< ":" << line
			<< ":" << col
			<< ": " << GetSeverityString()
			<< ": " << msg;
		return s;
	}
	
	String GetSeverityString() const {
		switch (severity) {
			case PROCMSG_UNKNOWN:	return "unknown";
			case PROCMSG_SKIP:		return "skip";
			case PROCMSG_INFO:		return "info";
			case PROCMSG_WARNING:	return "warning";
			case PROCMSG_ERROR:		return "error";
			default:				return "<invalid severity>";
		}
	}
};



class ErrorSource {
	String src;
	bool fail = false;

protected:
	
	void AddError(const FileLocation& loc, String msg) {fail = true; AddMessage(ProcMsg(src, loc, PROCMSG_ERROR, msg));}
	void AddWarning(const FileLocation& loc, String msg) {AddMessage(ProcMsg(src, loc, PROCMSG_WARNING, msg));}
	void AddInfo(const FileLocation& loc, String msg) {AddMessage(ProcMsg(src, loc, PROCMSG_INFO, msg));}
	void AddMessage(const ProcMsg& msg) {InternalAddMessage(msg); WhenMessage(msg);}
	virtual void InternalAddMessage(const ProcMsg& msg) {}
	
	
public:
	ErrorSource(String src_name) : src(src_name) {}

	void ResetFail() {fail = false;}
	bool IsFail() const {return fail;}
	String GetSource() const {return src;}
	
	void SetSource(String s) { src = s; }

	Callback1<ProcMsg> WhenMessage;
};


class ErrorSourceBuffered : public ErrorSource {
	Vector<ProcMsg> messages;
	
protected:
	void InternalAddMessage(const ProcMsg& msg) override {messages.Add(msg);}
	
	
public:
	ErrorSourceBuffered(String src_name) : ErrorSource(src_name) {}
	
	
	void DumpMessages();
	void ClearMessages() {messages.Clear();}
	
};

NAMESPACE_TOPSIDE_END

#endif
