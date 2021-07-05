#ifndef _MusicCtrl_NotationCtrl_h_
#define _MusicCtrl_NotationCtrl_h_



NAMESPACE_TOPSIDE_BEGIN


class NotationCtrl : public Ctrl {
	lomse::EPixelFormat			m_format;
	lomse::LomseDoorway			lomse;      // the Lomse library doorway
	One<lomse::Presenter>		presenter;	// relates the View, the Document and the Interactor
	
	
public:
	typedef NotationCtrl CLASSNAME;
	NotationCtrl();
	
	void OpenDocumentLenmus(String content);
	void PostUpdate();
	
	void Paint(Draw& d) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
