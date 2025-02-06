#ifndef _OrgLib_FileWriter_h_
#define _OrgLib_FileWriter_h_


BEGIN_TEXTLIB_NAMESPACE


class CppFileWriter {
	
	
public:
	typedef CppFileWriter CLASSNAME;
	CppFileWriter();
	
	void WriteHeader(Node& n, const String& h_path, const Vector<String>& inc_strs);
	void WriteImplementation(Node& n, const String& h_path, const String& incl_file);
	
	String GetFunctionHeaderString(Node& n);
	String GetFunctionImplString(Node& n, Node* cls_path);
	String GetClassHeaderString(Node& n);
	String GetClassImplString(Node& n);
	
};


END_TEXTLIB_NAMESPACE


#endif
