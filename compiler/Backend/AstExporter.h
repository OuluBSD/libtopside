#ifndef _Backend_AstExporter_h_
#define _Backend_AstExporter_h_

NAMESPACE_TOPSIDE_BEGIN


class AstExporter :
	public ErrorSource
{
	String output;
	
	
public:
	typedef AstExporter CLASSNAME;
	AstExporter();
	
	bool Process(const AstNode& n);
	
	String GetResult() const {return output;}
	
	
	void Visit(const AstNode& n);
	
};


NAMESPACE_TOPSIDE_END

#endif
