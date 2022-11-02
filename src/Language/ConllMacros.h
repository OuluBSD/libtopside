#ifndef _Language_ConllMacros_h_
#define _Language_ConllMacros_h_

NAMESPACE_LANGUAGE_BEGIN


inline bool IsS(const WString& n) {return IsConstChar(n, "S", 1);}
inline bool IsN(const WString& n) {return IsConstChar(n, "N", 1);}
inline bool IsA(const WString& n) {return IsConstChar(n, "A", 1);}
inline bool IsV(const WString& n) {return IsConstChar(n, "V", 1);}
inline bool IsNP(const WString& n) {return IsConstChar(n, "NP", 2);}
inline bool IsVP(const WString& n) {return IsConstChar(n, "VP", 2);}
inline bool IsAP(const WString& n) {return IsConstChar(n, "AP", 2);}
inline bool IsPP(const WString& n) {return IsConstChar(n, "PP", 2);}
inline bool IsDT(const WString& n) {return IsConstChar(n, "DT", 2);}
inline bool IsIN(const WString& n) {return IsConstChar(n, "IN", 2);}
inline bool IsCC(const WString& n) {return IsConstChar(n, "CC", 2);}
inline bool IsCD(const WString& n) {return IsConstChar(n, "CD", 2);}
inline bool IsFW(const WString& n) {return IsConstChar(n, "FW", 2);}
inline bool IsTO(const WString& n) {return IsConstChar(n, "TO", 2);}
inline bool IsMD(const WString& n) {return IsConstChar(n, "MD", 2);}
inline bool IsPUNC(const WString& n) {return IsConstChar(n, "PUNC", 4);}
inline bool IsAdv(const WString& n) {return IsConstChar(n, "Adv", 3);}
inline bool IsNum(const WString& n) {return IsConstChar(n, "Num", 3);}
inline bool IsPron(const WString& n) {return IsConstChar(n, "Pron", 4);}
inline bool IsUnknown(const WString& n) {return IsConstChar(n, "UNKNOWN", 7);}
inline bool IsRare(const WString& n) {
	return
		IsConstChar(n, "SYM", 3) ||
		IsConstChar(n, "Num", 3);
}

inline bool IsArg(Node& n, const char* cmp, int cmp_len) {return n.IsType(NODE_NL) && TS::IsArg(n.GetText(), cmp, cmp_len);}
inline bool IsA(Node& n) {return n.IsType(NODE_NL) && IsA(n.GetText());}
inline bool IsV(Node& n) {return n.IsType(NODE_NL) && IsV(n.GetText());}
inline bool IsS(Node& n) {return n.IsType(NODE_NL) && IsS(n.GetText());}
inline bool IsNP(Node& n) {return n.IsType(NODE_NL) && IsNP(n.GetText());}
inline bool IsVP(Node& n) {return n.IsType(NODE_NL) && IsVP(n.GetText());}
inline bool IsPP(Node& n) {return n.IsType(NODE_NL) && IsPP(n.GetText());}
inline bool IsUnknown(Node& n) {return n.IsType(NODE_NL) && IsUnknown(n.GetText());}
inline bool IsPUNC(Node& n) {return n.IsType(NODE_NL) && IsPUNC(n.GetText());}
inline bool IsAdv(Node& n) {return n.IsType(NODE_NL) && IsAdv(n.GetText());}
inline bool IsPron(Node& n) {return n.IsType(NODE_NL) && IsPron(n.GetText());}
inline bool IsRare(Node& n) {return n.IsType(NODE_NL) && IsRare(n.GetText());}
inline bool IsAnyN(Node& n) {return n.IsType(NODE_NL) && (IsNP(n.GetText()) || IsN(n.GetText()));}

inline bool IsVB(const WString& n) {
	const char* cmp = "VB";
	int cmp_len = 2;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return
		IsConstCharEnd(n, "VBD", 2, 3) ||
		IsConstCharEnd(n, "VBG", 2, 3) ||
		IsConstCharEnd(n, "VBN", 2, 3) ||
		IsConstCharEnd(n, "VBP", 2, 3) ||
		IsConstCharEnd(n, "VBZ", 2, 3);
}

inline bool IsNN(const WString& n) {
	const char* cmp = "NN";
	int cmp_len = 2;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return
		IsConstCharEnd(n, "NNS", 2, 3) ||
		IsConstCharEnd(n, "NNP", 2, 3) ||
		IsConstCharEnd(n, "NNPS", 2, 4);
}

inline bool IsJJ(const WString& n) {
	const char* cmp = "JJ";
	int cmp_len = 2;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return
		IsConstCharEnd(n, "JJR", 2, 3) ||
		IsConstCharEnd(n, "JJS", 2, 3);
}

inline bool IsPRP(const WString& n) {
	const char* cmp = "PRP";
	int cmp_len = 3;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return
		IsConstCharEnd(n, "PRP$", 3, 4);
}

inline bool IsRB(const WString& n) {
	const char* cmp = "RB";
	int cmp_len = 2;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return
		IsConstCharEnd(n, "RBR", 2, 3) ||
		IsConstCharEnd(n, "RBS", 2, 3);
}

inline bool IsWH(const WString& n) {
	const char* cmp = "W";
	int cmp_len = 1;
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	
	return
		IsConstCharEnd(n, "WDT", 1, 3) ||
		IsConstCharEnd(n, "WP$", 1, 3) ||
		IsConstCharEnd(n, "WRB", 1, 3) ||
		IsConstCharEnd(n, "WP", 1, 2);
}



inline bool IsAnyV(Node& n) {return n.IsType(NODE_NL) && (IsVP(n.GetText()) || IsVB(n.GetText()) || IsV(n.GetText()));}
inline bool IsAnyA(Node& n) {return n.IsType(NODE_NL) && (IsAP(n.GetText()) || IsA(n.GetText()));}


NAMESPACE_LANGUAGE_END

#endif
