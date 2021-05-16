#ifndef _CtrlLibAlt_TreeCtrl_h_
#define _CtrlLibAlt_TreeCtrl_h_

NAMESPACE_UPP


class TreeCtrl : public Ctrl {
	
	
public:
	
	
	void	OpenDeep(int cursor);
	
	bool	IsCursor() const;
	Value	Get(int cursor);
	int		GetCursor() const;
	
	int		Add(int parent_cursor, Image i, Value key, Value text);
	int		Add(int parent_cursor, Image i, Value v);
	void	SetRoot(Image i, Value v);
	void	SetRoot(Image i, Value key, Value text);
	void	SetCursor(int i);
	
	void	Clear();
	
	
	
	Callback	WhenCursor;
	
};


END_UPP_NAMESPACE

#endif
