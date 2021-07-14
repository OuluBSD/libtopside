#include "Core.h"


NAMESPACE_UPP_BEGIN

Object ParseMap(CParser& tk);



Object ParseArray(CParser& p) {
	String str;
	int64 i64;
	double dbl;
	ObjectArray arr;
	
	p.PassChar('[');
	
	while (!p.IsChar(']')) {
		
		if (p.IsChar('{')) {
			arr.Add(ParseMap(p));
		}
		else if (p.IsChar('[')) {
			arr.Add(ParseArray(p));
		}
		else if (p.IsChar('\"')) {
			String value = p.ReadString();
			arr.Add(value);
		}
		else if (p.GetId(str)) {
			if (str == "true")
				arr.Add(true);
			else if (str == "false")
				arr.Add(false);
			else
				arr.Add(str);
		}
		else if (p.GetInt(i64)) {
			arr.Add(i64);
		}
		else if (p.GetFloating(dbl)) {
			arr.Add(dbl);
		}
		else {
			THROW(Exc("Unexpected token at " + IntStr(p.GetLine()) + ":" + IntStr(p.GetColumn())));
		}
		
		p.Char(',');
	}
	
	p.PassChar(']');
	
	return arr;
}

Object ParseMap(CParser& p) {
	ObjectMap vm;
	
	p.PassChar('{');
	
	while (!p.IsChar('}')) {
		String key;
		if (p.IsId())
			key = p.ReadId();
		else if (p.IsString())
			key = p.ReadString();
		else {
			THROW(Exc("Unexpected token at " + IntStr(p.GetLine()) + ":" + IntStr(p.GetColumn())));
		}
		
		if (p.IsChar(',') || p.IsChar('}')) {
			p.Char(',');
			vm.Add(key);
			continue;
		}
		
		p.PassChar(':');
		
		if (p.IsChar('{')) {
			vm.Add(key, ParseMap(p));
		}
		else if (p.IsChar('[')) {
			vm.Add(key, ParseArray(p));
		}
		else if (p.IsId()) {
			String value = p.ReadId();
			if (value == "true")
				vm.Add(key, true);
			else if (value == "false")
				vm.Add(key, false);
			else
				vm.Add(key, value);
		}
		else if (p.IsInt()) {
			int64 value = p.ReadInt();
			vm.Add(key, value);
		}
		else if (p.IsNumber()) {
			double value = p.ReadNumber();
			vm.Add(key, value);
		}
		else if (p.IsString()) {
			String value = p.ReadString();
			vm.Add(key, value);
		}
		else {
			THROW(Exc("Unexpected token at " + IntStr(p.GetLine()) + ":" + IntStr(p.GetColumn())));
		}
		
		p.Char(',');
	}
	
	p.PassChar('}');
	
	return vm;
}

Object ParseJSON(String json) {
	CParser p(json);
	return ParseMap(p);
}

#ifdef flagSTDEXC
Object ParseJSONSafe(String json) {
	Object v;
	
	try {
		v = ParseJSON(json);
	}
	catch (Exc e) {
		LOG("JSON parsing error: " << e);
	}
	
	return v;
}
#endif

NAMESPACE_UPP_END
