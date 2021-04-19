#ifndef _EasyClang_Node_h_
#define _EasyClang_Node_h_




class ClangItem {
	
	
public:
	ClangItem() {}
	
	
	virtual Node<ClangItem>* GetNode() {return 0;}
	
};



typedef Node<ClangItem> ClangNode;


ClangNode CacheFile(const String& path);
void Dump(ClangNode& node);



#endif
