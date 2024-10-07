#ifndef _ToolBase_TxtStructTranslate_h_
#define _ToolBase_TxtStructTranslate_h_


BEGIN_TEXTLIB_NAMESPACE



class TranslatorToolCtrl : public ToolAppCtrl {
	Splitter hsplit;
	CodeEditor orig, trans;
	
protected:
	enum {
		FN_TRANSLATE_NL,
		FN_UNPACK_STRUCTURE,
	};
	String key, trans_key;
	int fn = FN_TRANSLATE_NL;
	bool artist = 0;
	bool release = 0;
	bool song = 0;
	
public:
	typedef TranslatorToolCtrl CLASSNAME;
	TranslatorToolCtrl();
	
	void Data() override;
	String GetStatusText() override;
	void ToolMenu(Bar& bar) override;
	void Translate();
	void OnOriginalChange();
	void OnTranslatedChange();
	void OnTranslatedRecv();
	//String GetOriginalText() const;
	String GetTranslatedText() const;
	void InitEditor(CodeEditor& edit);
	
};



END_TEXTLIB_NAMESPACE


#endif
