#ifndef _CtrlLibAlt_ArrayCtrl_h_
#define _CtrlLibAlt_ArrayCtrl_h_

NAMESPACE_UPP


class ArrayCtrl : public Ctrl {
	
	
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
	void	SetLineCy(int cy);
	void	NoHeader();
	void	GoEnd();
	
	bool	IsCursor() const;
	int		GetCursor() const;
	Value	Get(int row, int col) const;
	
	void	Clear();
	
	
	Callback	WhenCursor;
	
};


END_UPP_NAMESPACE

#endif
