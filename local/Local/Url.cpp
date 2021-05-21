#include "Local.h"

#ifdef flagSTDEXC

NAMESPACE_TOPSIDE_BEGIN


UrlParser::UrlParser() {
	
}

bool UrlParser::Parse(String url) {
	this->url = url;
	is_protocol_defined = false;
	
	// Tokenize
	tokens.Clear();
	for(int i = 0; i < url.GetCount(); i++) {
		int chr = url[i];
		if (chr == '/') {
			int chr1 = i+1 < url.GetCount() ? url[i+1] : 0;
			if (chr1 == '/') {
				tokens.Add().Set(DOUBLESLASH, "//");
				i++;
			}
			else
				tokens.Add().Set(SLASH, "/");
		}
		else if (chr == ':')
			tokens.Add().Set(COLON, ":");
		else {
			if (tokens.IsEmpty() || tokens.Top().type != TEXT)
				tokens.Add().type = TEXT;
			tokens.Top().text.Cat(chr);
		}
	}
	//DUMPC(tokens);
	if (tokens.IsEmpty()) return false;
	
	cursor = 0;
	bool succ = false;
	try {
		ReadProtocol();
		
		if (protocol == "file") {
			succ = true;
			without_protocol = "";
			while (!IsEnd()) {
				without_protocol += Get().text;
				cursor++;
			}
			server_addr = without_protocol;
		}
		else {
			base_addr = ReadText();
			
			if (Type(COLON))
				port = ReadInt();
			
			server_addr = "";
			while (!IsEnd()) {
				server_addr += Get().text;
				cursor++;
			}
			without_protocol = base_addr + ":" + IntStr(port) + server_addr;
			
			succ = true;
		}
	}
	catch (Exc e) {
		
	}
	
	return succ;
}

bool UrlParser::Type(int type) {
	if (IsEnd()) return false;
	if (Get().type == type) {
		cursor++;
		return true;
	}
	return false;
}

String UrlParser::ReadText() {
	if (IsEnd()) throw Exc("Unexpected end");
	const UrlToken& t = Get();
	if (t.type != TEXT) throw Exc("Unexpected type");
	cursor++;
	return t.text;
}

int UrlParser::ReadInt() {
	if (IsEnd()) throw Exc("Unexpected end");
	const UrlToken& t = Get();
	if (t.type != TEXT) throw Exc("Unexpected type");
	cursor++;
	return ScanInt(t.text);
}

void UrlParser::ReadProtocol() {
	protocol = "http";
	port = 80;
	
	const UrlToken& t = Get();
	if (t.type == TEXT) {
		UrlToken* t1 = cursor+1 < tokens.GetCount() ? &tokens[cursor+1] : NULL;
		UrlToken* t2 = cursor+2 < tokens.GetCount() ? &tokens[cursor+2] : NULL;
		if (t1 && t2 && t1->type == COLON && t2->type == DOUBLESLASH) {
			protocol = t.text;
			cursor += 3;
			is_protocol_defined = true;
		}
	}
	if (protocol == "http")			port = 80;
	else if (protocol == "https")	port = 443;
	else if (protocol == "ftp")		port = 21;
	else if (protocol == "dns")		port = 53;
	else if (protocol == "dns")		port = 53;
	else if (protocol == "dict")	port = 2628;
	else if (protocol == "imap")	port = 143;
	else if (protocol == "smtp")	port = 25;
	else if (protocol == "irc")		port = 6667;
	else if (protocol == "javascript")	port = 80;
	else if (protocol == "mms")		port = 1755;
	else if (protocol == "nfs")		port = 111;
	else if (protocol == "pop3")	port = 110;
	else if (protocol == "rtsp")	port = 554;
	else if (protocol == "rtsp")	port = 554;
	else if (protocol == "telnet")	port = 23;
	else if (protocol == "whois")	port = 43;
	else if (protocol == "xmpp")	port = 5222;
	else port = 0;
}

String UrlParser::GetFormattedAddr() const {
	if (protocol == "file")
		return "file://" + server_addr;
	else
		return protocol + "://" + base_addr + ":" + IntStr(port) + server_addr;
}

String UrlParser::GetFormattedBaseAddr() const {
	if (protocol == "file")
		return "file://";
	else
		return protocol + "://" + base_addr + ":" + IntStr(port);
}

String UrlParser::GetFormattedDirectory() const {
	String addr = GetFormattedAddr();
	int i = addr.ReverseFind("/");
	if (i >= 0)
		return addr.Left(i+1);
	return addr;
}




String JoinUrl(String base, String rel_path) {
	while (base.Right(1) == "/") base = base.Left(base.GetCount() - 1);
	while (rel_path.Left(1) == "/") rel_path = rel_path.Mid(1);
	return base + "/" + rel_path;
}


NAMESPACE_TOPSIDE_END

#endif
