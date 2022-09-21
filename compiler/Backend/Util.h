#ifndef _Backend_Util_h_
#define _Backend_Util_h_

NAMESPACE_TOPSIDE_BEGIN


#if 0

class AccessControl {
	CodeAccess				access = ACC_PUBLIC;
	
public:
	void		SetAccess(CodeAccess a) {access = a;}
	void		SetPublic() {access = ACC_PUBLIC;}
	void		SetPrivate() {access = ACC_PRIVATE;}
	void		SetProtected() {access = ACC_PROTECTED;}
	
	CodeAccess	GetAccess() const {return access;}
	bool		IsPublic() const {return access == ACC_PUBLIC;}
	bool		IsPrivate() const {return access == ACC_PRIVATE;}
	bool		IsProtected() const {return access == ACC_PROTECTED;}
	
};

#define CHK_ACCESS \
	auto access = o.GetAccess(); \
	if (access != acc) { \
		s.Cat('\t', args.indent); \
		s.Cat('\n'); \
		s.Cat('\t', args.indent); \
		s << GetAccessString(access) << ":\n"; \
		acc = access; \
	}



struct MetaConditional {
	Index<String>			req_meta_defs;
	
	
	void	RequireMetaDefinition(String s) {req_meta_defs.Add(s);}
	String	PreCodeString(const CodeArgs& args) const;
	String	PostCodeString(const CodeArgs& args) const;
	
};

#endif


struct PathIdentifier {
	enum {
		DIRECT,
		PTR,
		LREF
	};
	
	static const int MAX_PARTS = 32;
	static const int MAX_TAIL_COUNT = 8;
	
	const Token* parts[MAX_PARTS];
	bool is_meta[MAX_PARTS];
	byte head[MAX_TAIL_COUNT];
	byte tail[MAX_TAIL_COUNT];
	int part_count = 0;
	int head_count = 0;
	int tail_count = 0;
	bool is_const = false;
	
	const Token* begin = 0;
	const Token* end = 0;
	
	void Clear();
	String ToString() const;
	bool HasMeta() const;
	bool IsEmpty() const;
	
};

NAMESPACE_TOPSIDE_END

#endif
