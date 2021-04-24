#ifndef _LayoutCtrl_Table_h_
#define _LayoutCtrl_Table_h_

NAMESPACE_LAYOUT_BEGIN


struct TableRow : public Moveable<TableRow>
{
	typedef Vector<TableRow>	vector;

	int			height;
	int			border_top;
	int			border_bottom;
	Element*	el_row;
	int			top;
	int			bottom;

	TableRow()
	{
		top				= 0;
		bottom			= 0;
		border_bottom	= 0;
		border_top		= 0;
		height			= 0;
		el_row			= 0;
	}

	TableRow(int h, Element* row)
	{
		height			= h;
		el_row			= row;
		border_bottom	= 0;
		border_top		= 0;
		top				= 0;
		bottom			= 0;
	}

	TableRow(const TableRow& val)
	{
		top				= val.top;
		bottom			= val.bottom;
		border_bottom	= val.border_bottom;
		border_top		= val.border_top;
		height			= val.height;
		el_row			= val.el_row;
	}
};

struct TableColumn : public Moveable<TableColumn>
{
	typedef Vector<TableColumn>	vector;
	
	int			min_width;
	int			max_width;
	int			width;
	CssLength	css_width;
	int			border_left;
	int			border_right;
	int			left;
	int			right;

	TableColumn()
	{
		left			= 0;
		right			= 0;
		border_left		= 0;
		border_right	= 0;
		min_width		= 0;
		max_width		= 0;
		width			= 0;
		css_width.PreDefine(0);
	}

	TableColumn(int min_w, int max_w)
	{
		left			= 0;
		right			= 0;
		border_left		= 0;
		border_right	= 0;
		max_width		= max_w;
		min_width		= min_w;
		width			= 0;
		css_width.PreDefine(0);
	}

	TableColumn(const TableColumn& val)
	{
		left			= val.left;
		right			= val.right;
		border_left		= val.border_left;
		border_right	= val.border_right;
		max_width		= val.max_width;
		min_width		= val.min_width;
		width			= val.width;
		css_width		= val.css_width;
	}
};

class TableColumnAccessor
{
public:
	virtual int& Get(TableColumn& col) = 0;
};

class TableColumnAccessorMaxWidth : public TableColumnAccessor
{
public:
	virtual int& Get(TableColumn& col);
};

class TableColumnAccessorMinWidth : public TableColumnAccessor
{
public:
	virtual int& Get(TableColumn& col);
};

class TableColumnAccessorWidth : public TableColumnAccessor
{
public:
	virtual int& Get(TableColumn& col);
};

struct TableCell : public Moveable<TableCell>
{
	Element*		el;
	int				colspan;
	int				rowspan;
	int				min_width;
	int				min_height;
	int				max_width;
	int				max_height;
	int				width;
	int				height;
	Margins			Borders;

	TableCell()
	{
		min_width		= 0;
		min_height		= 0;
		max_width		= 0;
		max_height		= 0;
		width			= 0;
		height			= 0;
		colspan			= 1;
		rowspan			= 1;
		el				= 0;
	}

	TableCell(const TableCell& val)
	{
		el				= val.el;
		colspan			= val.colspan;
		rowspan			= val.rowspan;
		width			= val.width;
		height			= val.height;
		min_width		= val.min_width;
		min_height		= val.min_height;
		max_width		= val.max_width;
		max_height		= val.max_height;
		Borders			= val.Borders;
	}
};

class TableGrid
{
public:
	typedef Vector< Vector<TableCell> >	Rows;
	
private:
	int						rows_count;
	int						cols_count;
	Rows					cells;
	TableColumn::vector		columns;
	TableRow::vector		rows;
public:

	TableGrid()
	{
		rows_count	= 0;
		cols_count	= 0;
	}

	void			Clear();
	void			BeginRow(Element* row);
	void			AddCell(Element* el);
	bool			IsRowSpanned(int r, int c);
	void			Finish();
	TableCell*		Cell(int t_col, int t_row);
	TableColumn&	Column(int c)	{ return columns[c];	}
	TableRow&		Row(int r)		{ return rows[r];		}

	int				GetRowsCount()	{ return rows_count;	}
	int				GetColsCount()	{ return cols_count;	}

	void			DistributeMaxWidth(int width, int start, int end);
	void			DistributeMinWidth(int width, int start, int end);
	void			DistributeWidth(int width, int start, int end);
	void			DistributeWidth(int width, int start, int end, TableColumnAccessor* acc);
	int				CalcTableWidth(int block_width, bool is_auto, int& min_table_width, int& max_table_width);
	void			CalcHorizPos(Margins& table_borders, BorderCollapse bc, int bdr_space_x);
	void			CalcVertPos(Margins& table_borders, BorderCollapse bc, int bdr_space_y);
};


NAMESPACE_LAYOUT_END

#endif
