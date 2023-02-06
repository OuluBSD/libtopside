#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


DrawCommandImageRenderer::DrawCommandImageRenderer() {
	
}

void DrawCommandImageRenderer::ProcessWindowCommands(DrawCommand* begin, DrawCommand* end) {
	
	// Get ctrl size from draw command queue
	Size sz(0,0);
	{
		DrawCommand* iter = begin;
		while (iter) {
			if (iter->type == DRAW_META_SIZE) {
				sz.cx = iter->i[0];
				sz.cy = iter->i[1];
				break;
			}
			iter = iter->next;
		}
	}
	ASSERT(!sz.IsEmpty());
	if (sz.IsEmpty()) sz = Size(320,240);
	this->sz = sz;
	
	if (id.IsEmpty() || id->GetPageSize() != sz) {
		#ifdef UPP_VERSION
		id = new ImageDraw(sz.cx, sz.cy);
		#else
		id->Create(sz, 3);
		#endif
	}
	
	id->DrawRect(sz, GrayColor());
	
	pi.SkipWindowCommands();
	pi.Paint(begin, end, *id);
	
	
}

Image DrawCommandImageRenderer::GetImage() {
	return *id;
}

bool DrawCommandImageRenderer::TrimBegin(DrawCommand*& begin) {
	while (begin && begin->type == 0)
		begin = begin->next;
	if (!begin)
		return false;
	
	ASSERT(begin->type == DRAW_BIND_WINDOW);
	return true;
}

void DrawCommandImageRenderer::FindBegin(DrawCommand*& cmd) {
	while (cmd && cmd->type != DRAW_BIND_WINDOW)
		cmd = cmd->next;
}

DrawCommand* DrawCommandImageRenderer::FindEnd(DrawCommand* begin) {
	DrawCommand* end = begin;
	while (end) {
		if (end->type == DRAW_UNBIND_WINDOW) {
			end = end->next;
			break;
		}
		end = end->next;
	}
	return end;
}

DrawCommand* DrawCommandImageRenderer::MoveEnd(DrawCommand* end) {
	DrawCommand* next = end->next;
	while (next && next->type != DRAW_BIND_WINDOW)
		next = next->next;
	
	return next;
}


NAMESPACE_PARALLEL_END
