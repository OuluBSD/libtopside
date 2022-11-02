#ifndef _Local_Url_h_
#define _Local_Url_h_


NAMESPACE_TOPSIDE_BEGIN


class UrlParser {
	enum {TEXT, SLASH, DOUBLESLASH, COLON};
	
	struct UrlToken : Moveable<UrlToken> {
		int type = 0;
		String text;
		
		void Set(int type, String text) {this->type = type; this->text = text;}
		String ToString() const {
			switch (type) {
				case TEXT: return "Text: " + text;
				case SLASH: return "Slash: /";
				case DOUBLESLASH: return "Double-slash: //";
				case COLON: return "Colon: :";
			}
			return "";
		}
	};
	Vector<UrlToken> tokens;
	int cursor = 0;
	
	String url, without_protocol;
	String base_addr;
	String protocol = "http";
	String server_addr;
	int port = 80;
	bool is_protocol_defined = false;
	
	void ReadProtocol();
	String ReadText();
	int ReadInt();
	bool IsEnd() const {return cursor >= tokens.GetCount();}
	const UrlToken& Get() const {return tokens[cursor];}
	bool Type(int type);
public:
	UrlParser();
	
	bool Parse(String url);
	
	String GetUrl() const {return url;}
	String GetBaseAddress() const {return base_addr;}
	String GetProtocol() const {return protocol;}
	String GetWithoutProtocol() const {return without_protocol;}
	int GetPort() const {return port;}
	String GetFormattedAddr() const;
	String GetFormattedBaseAddr() const;
	String GetFormattedDirectory() const;
	bool IsProtocolDefined() const {return is_protocol_defined;}
};


String JoinUrl(String base, String rel_path);


NAMESPACE_TOPSIDE_END

#endif
