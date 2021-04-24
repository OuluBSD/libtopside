#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN


BoxType BlockBox::GetType()
{
	return BOX_BLOCK;
}

int BlockBox::Height()
{
	return element->Height();
}

int BlockBox::Width()
{
	return element->Width();
}

void BlockBox::AddElement(Element* el)
{
	element = el;
	el->box = this;
}

void BlockBox::Finish(bool last_box)
{
	if(!element) return;

	CssOffsets offsets;
	if(element->GetElementPosition(&offsets) == ElementPositionRelative)
	{
		if(!offsets.left.IsPredefined())
			element->pos.x += offsets.left.CalcPercent(box_right - box_left);
		else if(!offsets.right.IsPredefined())
			element->pos.x -= offsets.right.CalcPercent(box_right - box_left);

		if(!offsets.top.IsPredefined())
		{
			int h = 0;
			if(offsets.top.Units() == CssUnitsPercentage)
			{
				if(element->GetParentElement())
				{
					element->GetParentElement()->GetPredefinedHeight(h);
				}
			}
			element->pos.y += offsets.top.CalcPercent(h);
		}
		else if(!offsets.bottom.IsPredefined())
		{
			int h = 0;
			if(offsets.bottom.Units() == CssUnitsPercentage)
			{
				if(element->GetParentElement())
				{
					element->GetParentElement()->GetPredefinedHeight(h);
				}
			}
			element->pos.y -= offsets.bottom.CalcPercent(h);
		}
	}
}

bool BlockBox::CanHold( Element* el, WhiteSpace ws )
{
	if(element || el->IsInLineBox())
	{
		return false;
	}
	return true;
}

bool BlockBox::IsEmpty()
{
	if(element)
	{
		return false;
	}
	return true;
}

int BlockBox::Baseline()
{
	if(element)
	{
		return element->GetBaseLine();
	}
	return 0;
}

void BlockBox::GetElements(ElementsVector& els)
{
	els.Add(element);
}

int BlockBox::TopMargin()
{
	if(element && element->CollapseTopMargin())
	{
		return element->margins.top;
	}
	return 0;
}

int BlockBox::BottomMargin()
{
	if(element && element->CollapseBottomMargin())
	{
		return element->margins.bottom;
	}
	return 0;
}

void BlockBox::SetYShift( int shift )
{
	box_top += shift;
	if(element)
	{
		element->pos.y += shift;
	}
}

void BlockBox::NewWidth( int left, int right, ElementsVector& els )
{

}










BoxType LineBox::GetType()
{
	return BOX_LINE;
}

int LineBox::Height()
{
	return height;
}

int LineBox::Width()
{
	return width;
}

void LineBox::AddElement(Element* el)
{
	el->skip	= false;
	el->box	= 0;
	bool add	= true;
	if( (items.IsEmpty() && el->IsWhiteSpace()) || el->IsBreak() ) {
		el->skip = true;
	}
	else if(el->IsWhiteSpace()) {
		Element* ws = GetLastSpace();
		if(ws) {
			add = false;
			el->skip = true;
		}
	}

	if(add)
	{
		el->box = this;
		items.Add(el);
		ASSERT(el->GetParent());

		if(!el->skip)
		{
			int el_shift_left	= el->GetInlineShiftLeft();
			int el_shift_right	= el->GetInlineShiftRight();

			el->pos.x	= box_left + width + el_shift_left + el->ContentMarginsLeft();
			el->pos.y	= box_top + el->ContentMarginsTop();
			width		+= el->Width() + el_shift_left + el_shift_right;
		}
	}
}

void LineBox::Finish(bool last_box)
{
	if( IsEmpty() || (!IsEmpty() && last_box && IsBreakOnly()) )
	{
		height = 0;
		return;
	}

	for(int j = items.GetCount() - 1; j >= 0; j--) {
		Element& e = *items[j];
		if(e.IsWhiteSpace() || e.IsBreak())
		{
			if(!e.skip)
			{
				e.skip = true;
				width -= e.Width();
			}
		} else
		{
			break;
		}
	}

	int baseline	= font_metrics.BaseLine();
	int line_height = this->line_height;

	int add_x = 0;
	switch(text_align)
	{
	case TextAlignRight:
		if(width < (box_right - box_left))
			add_x = (box_right - box_left) - width;
		break;
		
	case TextAlignCenter:
		if(width < (box_right - box_left))
			add_x = ((box_right - box_left) - width) / 2;
		break;
		
	default:
		add_x = 0;
	}

	height = 0;
	
	// find line Box baseline and line-height
	for(size_t i = 0; i < items.GetCount(); i++)
	{
		if(items[i]->GetDisplay() == DisplayInlineText)
		{
			FontMetrics fm;
			items[i]->GetFont(&fm);
			baseline	= max(baseline,	fm.BaseLine());
			line_height	= max(line_height,	items[i]->LineHeight());
			height = max(height, fm.height);
		}
		items[i]->pos.x += add_x;
	}

	if(height)
	{
		baseline += (line_height - height) / 2;
	}

	height = line_height;

	int y1	= 0;
	int y2	= height;

	for(size_t i = 0; i < items.GetCount(); i++)
	{
		if(items[i]->GetDisplay() == DisplayInlineText)
		{
			FontMetrics fm;
			items[i]->GetFont(&fm);
			items[i]->pos.y = height - baseline - fm.ascent;
		} else
		{
			switch(items[i]->GetVerticalAlign())
			{
			case VASuper:
			case VASub:
			case VABaseline:
				items[i]->pos.y = height - baseline - items[i]->Height() + items[i]->GetBaseLine() + items[i]->ContentMarginsTop();
				break;
			case VATop:
				items[i]->pos.y = y1 + items[i]->ContentMarginsTop();
				break;
			case VATextTop:
				items[i]->pos.y = height - baseline - font_metrics.ascent + items[i]->ContentMarginsTop();
				break;
			case VAMiddle:
				items[i]->pos.y = height - baseline - font_metrics.x_height / 2 - items[i]->Height() / 2 + items[i]->ContentMarginsTop();
				break;
			case VABottom:
				items[i]->pos.y = y2 - items[i]->Height() + items[i]->ContentMarginsTop();
				break;
			case VATextBottom:
				items[i]->pos.y = height - baseline + font_metrics.descent - items[i]->Height() + items[i]->ContentMarginsTop();
				break;
			}
			y1 = min(y1, items[i]->Top());
			y2 = max(y2, items[i]->Bottom());
		}
	}

	CssOffsets offsets;

	for(size_t i = 0; i < items.GetCount(); i++)
	{
		items[i]->pos.y -= y1;
		items[i]->pos.y += box_top;
		if(items[i]->GetDisplay() != DisplayInlineText)
		{
			switch(items[i]->GetVerticalAlign())
			{
			case VATop:
				items[i]->pos.y = box_top + items[i]->ContentMarginsTop();
				break;
			case VABottom:
				items[i]->pos.y = box_top + (y2 - y1) - items[i]->Height() + items[i]->ContentMarginsTop();
				break;
			case VABaseline:
				//TODO: process vertical align "baseline"
				break;
			case VAMiddle:
				//TODO: process vertical align "middle"
				break;
			case VASub:
				//TODO: process vertical align "sub"
				break;
			case VASuper:
				//TODO: process vertical align "super"
				break;
			case VATextBottom:
				//TODO: process vertical align "text-bottom"
				break;
			case VATextTop:
				//TODO: process vertical align "text-top"
				break;
			}
		}

		// update Position for relative Positioned elements
		if(items[i]->GetElementPosition(&offsets) == ElementPositionRelative)
		{
			if(!offsets.left.IsPredefined())
			{
				items[i]->pos.x += offsets.left.CalcPercent(box_right - box_left);
			} else if(!offsets.right.IsPredefined())
			{
				items[i]->pos.x -= offsets.right.CalcPercent(box_right - box_left);
			}
			if(!offsets.top.IsPredefined())
			{
				// TODO: line_height is not correct here
				items[i]->pos.y += offsets.top.CalcPercent(this->line_height);
			} else if(!offsets.bottom.IsPredefined())
			{
				// TODO: line_height is not correct here
				items[i]->pos.y -= offsets.bottom.CalcPercent(this->line_height);
			}
		}
	}
	height = y2 - y1;
	this->baseline = (baseline - y1) - (height - line_height);
}

bool LineBox::CanHold( Element* el, WhiteSpace ws )
{
	if(!el->IsInLineBox()) return false;

	if(el->IsBreak())
	{
		return false;
	}

	if(ws == WhiteSpaceNowrap || ws == WhiteSpacePre)
	{
		return true;
	}

	if(box_left + width + el->Width() + el->GetInlineShiftLeft() + el->GetInlineShiftRight() > box_right)
	{
		return false;
	}

	return true;
}

Element* LineBox::GetLastSpace()
{
	Element* ret = 0;
	for(int j = items.GetCount() - 1; j >= 0; j--) {
		Element& e = *items[j];
		if(e.IsWhiteSpace() || e.IsBreak())
		{
			ret = &e;
		} else
		{
			break;
		}
	}
	return ret;
}

bool LineBox::IsEmpty()
{
	if(items.IsEmpty()) return true;
	for(int j = items.GetCount() - 1; j >= 0; j--) {
		Element& e = *items[j];
		if(!e.skip || e.IsBreak())
		{
			return false;
		}
	}
	return true;
}

int LineBox::Baseline()
{
	return baseline;
}

void LineBox::GetElements( ElementsVector& els )
{
	for(int i = 0; i < items.GetCount(); i++) {
		els.Insert(i, items[i]);
	}
}

int LineBox::TopMargin()
{
	return 0;
}

int LineBox::BottomMargin()
{
	return 0;
}

void LineBox::SetYShift( int shift )
{
	box_top += shift;
	for (int i = 0; i < items.GetCount(); i++) {
		Element& e = *items[i];
		e.pos.y += shift;
	}
}

bool LineBox::IsBreakOnly()
{
	if(items.IsEmpty()) return true;

	if(items[0]->IsBreak())
	{
		for (int i = 0; i < items.GetCount(); i++) {
			Element& e = *items[i];
			if(!e.skip)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void LineBox::NewWidth( int left, int right, ElementsVector& els )
{
	int add = left - box_left;
	if(add)
	{
		box_left	= left;
		box_right	= right;
		width = 0;
		int remove_begin = items.GetCount();
		for (int i = 1; i != items.GetCount(); i++) {
			Element* el = items[i];

			if(!el->skip)
			{
				if(box_left + width + el->Width() + el->GetInlineShiftRight() + el->GetInlineShiftLeft() > box_right)
				{
					remove_begin = i;
					break;
				} else
				{
					el->pos.x += add;
					width += el->Width() + el->GetInlineShiftRight() + el->GetInlineShiftLeft();
				}
			}
		}
		if(remove_begin != items.GetCount())
		{
			for(int i = remove_begin; i < items.GetCount(); i++) {
				els.Insert(i, items[i]);
			}
			items.Remove(remove_begin, items.GetCount() - remove_begin);
			for(int i = 0; i < els.GetCount(); i++) {
				els[i]->box = 0;
			}
		}
	}
}


NAMESPACE_LAYOUT_END
