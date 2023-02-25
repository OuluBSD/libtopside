#ifndef _CtrlLibAlt_ArrayCtrl_h_
#define _CtrlLibAlt_ArrayCtrl_h_

NAMESPACE_UPP


class ArrayCtrl : public Ctrl {
	HeaderCtrl                 header;
	
	
public:
	RTTI_DECL1(ArrayCtrl, Ctrl)
	ArrayCtrl();
	
	void	Add(Value v);
	void	AddIndex();
	void	AddColumn(String key);
	void	ColumnWidths(String rel_size_str);
	void	Set(int row, int col, Value o);
	void	SetCount(int c);
	void	SetCursor(int row);
	void	GoEnd();
	
	ArrayCtrl& Header(bool b = true)                   { header.Invisible(!b); return *this; }
	ArrayCtrl& NoHeader()                              { return Header(false); }
	ArrayCtrl& SetLineCy(int cy);
	
	bool	IsCursor() const;
	int		GetCursor() const;
	Value	Get(int row, int col) const;
	
	void	Clear();
	
	
	Callback	WhenCursor;
	
};


END_UPP_NAMESPACE

#endif
