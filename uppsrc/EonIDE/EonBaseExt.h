#ifndef _EonIDE_EonBaseExt_h_
#define _EonIDE_EonBaseExt_h_

NAMESPACE_TOPSIDE_BEGIN



class EonBaseExt : public EditorExtension {
	
	
public:
	typedef EonBaseExt CLASSNAME;
	EonBaseExt();
	
	void Activate() override;
	void Deactivate() override;
	void Save() override;
	bool HotKey(dword key) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
