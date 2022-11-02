#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN



void TableGrid::AddCell(Element* el) {
	TableCell cell;
	
	cell.el = el;
	cell.colspan	= ScanInt(el->GetAttr("colspan", "1"));
	cell.rowspan	= ScanInt(el->GetAttr("rowspan", "1"));
	cell.Borders	= el->GetBorders();

	while (IsRowSpanned( (int) cells.GetCount() - 1, (int) LAST(cells).GetCount() ) ) {
		LAST(cells).Add(TableCell());
	}

	LAST(cells).Add(cell);
	for(int i = 1; i < cell.colspan; i++) {
		TableCell empty_cell;
		LAST(cells).Add(empty_cell);
	}
}


void TableGrid::BeginRow(Element* row) {
	Vector<TableCell> r;
	cells.Add(pick(r));
	
	rows.Add(TableRow(0, row));
}


bool TableGrid::IsRowSpanned( int r, int c )
{
	for(int row = r - 1; row >= 0; row--)
	{
		if (c < (int) cells[row].GetCount())
		{
			if (cells[row][c].rowspan > 1)
			{
				if (cells[row][c].rowspan >= r - row + 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void TableGrid::Finish()
{
	rows_count	= cells.GetCount();
	cols_count	= 0;
	
	for(int i = 0; i < cells.GetCount(); i++) {
		cols_count = max(cols_count, cells[i].GetCount());
	}
	
	for(int i = 0; i < cells.GetCount(); i++) {
		for(int j = cells[i].GetCount(); j < cols_count; j++) {
			TableCell empty_cell;
			cells[i].Add(empty_cell);
		}
	}

	columns.Clear();
	for (int i = 0; i < cols_count; i++) {
		columns.Add(TableColumn(0, 0));
	}

	for (int col = 0; col < cols_count; col++) {
		for (int row = 0; row < rows_count; row++) {
			if (Cell(col, row)->el) {
				// find minimum left Border width
				if(columns[col].border_left) {
					columns[col].border_left = min(columns[col].border_left, Cell(col, row)->Borders.left);
				}
				else {
					columns[col].border_left = Cell(col, row)->Borders.left;
				}
				
				// find minimum right Border width
				if(columns[col].border_right) {
					columns[col].border_right = min(columns[col].border_right, Cell(col, row)->Borders.right);
				}
				else {
					columns[col].border_right = Cell(col, row)->Borders.right;
				}
				
				// find minimum top Border width
				if(rows[row].border_top) {
					rows[row].border_top = min(rows[row].border_top, Cell(col, row)->Borders.top);
				}
				else {
					rows[row].border_top = Cell(col, row)->Borders.top;
				}
				
				// find minimum bottom Border width
				if (rows[row].border_bottom) {
					rows[row].border_bottom = min(rows[row].border_bottom, Cell(col, row)->Borders.bottom);
				}
				else {
					rows[row].border_bottom = Cell(col, row)->Borders.bottom;
				}
			}

			if(Cell(col, row)->el && Cell(col, row)->colspan <= 1) {
				if(!Cell(col, row)->el->GetCssWidth().IsPredefined()) {
					columns[col].css_width = Cell(col, row)->el->GetCssWidth();
					break;
				}
			}
		}
	}

	for(int col = 0; col < cols_count; col++) {
		for(int row = 0; row < rows_count; row++) {
			if (Cell(col, row)->el) {
				Cell(col, row)->el->SetCssWidth(columns[col].css_width);
			}
		}
	}
}

TableCell* TableGrid::Cell( int t_col, int t_row )
{
	if(t_col >= 0 && t_col < cols_count && t_row >= 0 && t_row < rows_count)
	{
		return &cells[t_row][t_col];
	}
	return 0;
}

void TableGrid::DistributeMaxWidth( int width, int start, int end )
{
	TableColumnAccessorMaxWidth selector;
	DistributeWidth(width, start, end, &selector);
}

void TableGrid::DistributeMinWidth( int width, int start, int end )
{
	TableColumnAccessorMinWidth selector;
	DistributeWidth(width, start, end, &selector);
}

void TableGrid::DistributeWidth( int width, int start, int end, TableColumnAccessor* acc )
{
	if(!(start >= 0 && start < cols_count && end >= 0 && end < cols_count))
	{
		return;
	}

	int cols_width = 0;
	for(int col = start; col <= end; col++)
	{
		cols_width += columns[col].max_width;
	}

	int add = width / (end - start + 1);
	int added_width = 0;
	for(int col = start; col <= end; col++) {
		if (cols_width) {
			add = RoundFlt( (float) width * ((float) columns[col].max_width / (float) cols_width) );
		}
		added_width += add;
		acc->Get(columns[col]) += add;
	}
	if(added_width < width) {
		acc->Get(columns[start]) += width - added_width;
	}
}

void TableGrid::DistributeWidth( int width, int start, int end )
{
	if(!(start >= 0 && start < cols_count && end >= 0 && end < cols_count))
		return;

	Vector<TableColumn*> distribute_columns;

	for(int step = 0; step < 3; step++)
	{
		distribute_columns.Clear();

		switch(step)
		{
		case 0:
			{
				// distribute between the columns with width == auto
				for(int col = start; col <= end; col++)
				{
					if(columns[col].css_width.IsPredefined())
					{
						distribute_columns.Add(&columns[col]);
					}
				}
			}
			break;
		case 1:
			{
				// distribute between the columns with percents
				for(int col = start; col <= end; col++)
				{
					if(!columns[col].css_width.IsPredefined() && columns[col].css_width.Units() == CssUnitsPercentage)
					{
						distribute_columns.Add(&columns[col]);
					}
				}
			}
			break;
		case 2:
			{
				//well distribute between all columns
				for(int col = start; col <= end; col++)
				{
					distribute_columns.Add(&columns[col]);
				}
			}
			break;
		}

		int added_width = 0;

		if(!distribute_columns.IsEmpty() || step == 2)
		{
			int cols_width = 0;
			for(Vector<TableColumn*>::Iterator col = distribute_columns.Begin(); col != distribute_columns.End(); col++)
				cols_width += (*col)->max_width - (*col)->min_width;
			
			if(cols_width)
			{
				int add = width / (int) distribute_columns.GetCount();
				for(Vector<TableColumn*>::Iterator col = distribute_columns.Begin(); col != distribute_columns.End(); col++)
				{
					add = RoundFlt( (float) width * ((float) ((*col)->max_width - (*col)->min_width) / (float) cols_width) );
					if((*col)->width + add >= (*col)->min_width)
					{
						(*col)->width	+= add;
						added_width		+= add;
					} else
					{
						added_width	+= ((*col)->width - (*col)->min_width) * (add / abs(add));
						(*col)->width = (*col)->min_width;
					}
				}
				if(added_width < width && step)
				{
					distribute_columns[0]->width += width - added_width;
					added_width = width;
				}
			} else
			{
				LAST(distribute_columns)->width += width;
				added_width = width;
			}
		}

		if (added_width == width) {
			break;
		}
		else {
			width -= added_width;
		}
	}
}

int TableGrid::CalcTableWidth(int block_width, bool is_auto, int& min_table_width, int& max_table_width)
{
	//int table_width = 0;

	min_table_width = 0; // MIN
	max_table_width = 0; // MAX

	int cur_width = 0;
	int max_w = 0;
	int min_w = 0;

	for(int col = 0; col < cols_count; col++) {
		min_table_width += columns[col].min_width;
		max_table_width += columns[col].max_width;

		if(!columns[col].css_width.IsPredefined())
		{
			columns[col].width = columns[col].css_width.CalcPercent(block_width);
			columns[col].width = max(columns[col].width, columns[col].min_width);
		}
		else {
			columns[col].width = columns[col].min_width;
			max_w += columns[col].max_width;
			min_w += columns[col].min_width;
		}

		cur_width += columns[col].width;
	}

	if (cur_width == block_width)
		return cur_width;

	if (cur_width < block_width)
	{
		if(cur_width - min_w + max_w <= block_width)
		{
			cur_width = 0;
			for(int col = 0; col < cols_count; col++)
			{
				if(columns[col].css_width.IsPredefined())
				{
					columns[col].width = columns[col].max_width;
				}
				cur_width += columns[col].width;
			}
			if(cur_width == block_width || is_auto)
			{
				return cur_width;
			}
		}
		DistributeWidth(block_width - cur_width, 0, cols_count - 1);
		cur_width = 0;
		for(int col = 0; col < cols_count; col++)
		{
			cur_width += columns[col].width;
		}
	}
	else {
		int fixed_width = 0;
		float percent = 0;
		for(int col = 0; col < cols_count; col++)
		{
			if(!columns[col].css_width.IsPredefined() && columns[col].css_width.Units() == CssUnitsPercentage)
				percent += columns[col].css_width.GetValue();
			else
				fixed_width += columns[col].width;
		}
		float scale = (float) (100.0 / percent);
		cur_width = 0;
		for(int col = 0; col < cols_count; col++)
		{
			if(!columns[col].css_width.IsPredefined() && columns[col].css_width.Units() == CssUnitsPercentage)
			{
				CssLength w;
				w.SetValue(columns[col].css_width.GetValue() * scale, CssUnitsPercentage);
				columns[col].width = w.CalcPercent(block_width - fixed_width);
				if (columns[col].width < columns[col].min_width)
					columns[col].width = columns[col].min_width;
			}
			cur_width += columns[col].width;
		}
	}
	return cur_width;
}

void TableGrid::Clear()
{
	rows_count	= 0;
	cols_count	= 0;
	cells.Clear();
	columns.Clear();
	rows.Clear();
}

void TableGrid::CalcHorizPos( Margins& table_borders, BorderCollapse bc, int bdr_space_x)
{
	if(bc == BorderCollapseSeparate)
	{
		int left = bdr_space_x;
		for(int i = 0; i < cols_count; i++)
		{
			columns[i].left	= left;
			columns[i].right	= columns[i].left + columns[i].width;
			left = columns[i].right + bdr_space_x;
		}
	}
	else {
		int left = 0;
		if (cols_count) {
			left -= min(table_borders.left, columns[0].border_left);
		}
		for(int i = 0; i < cols_count; i++) {
			if(i > 0)
				left -= min(columns[i - 1].border_right, columns[i].border_left);

			columns[i].left	= left;
			columns[i].right	= columns[i].left + columns[i].width;
			left = columns[i].right;
		}
	}
}

void TableGrid::CalcVertPos( Margins& table_borders, BorderCollapse bc, int bdr_space_y )
{
	if (bc == BorderCollapseSeparate) {
		int top = bdr_space_y;
		for(int i = 0; i < rows_count; i++)
		{
			rows[i].top		= top;
			rows[i].bottom	= rows[i].top + rows[i].height;
			top = rows[i].bottom + bdr_space_y;
		}
	}
	else {
		int top = 0;
		if(rows_count)
			top -= min(table_borders.top, rows[0].border_top);
		
		for (int i = 0; i < rows_count; i++) {
			if(i > 0)
				top -= min(rows[i - 1].border_bottom, rows[i].border_top);

			rows[i].top		= top;
			rows[i].bottom	= rows[i].top + rows[i].height;
			top = rows[i].bottom;
		}
	}
}


int& TableColumnAccessorMaxWidth::Get(TableColumn& col) {
	return col.max_width;
}

int& TableColumnAccessorMinWidth::Get(TableColumn& col) {
	return col.min_width;
}

int& TableColumnAccessorWidth::Get(TableColumn& col) {
	return col.width;
}


NAMESPACE_LAYOUT_END
