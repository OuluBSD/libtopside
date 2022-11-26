#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


bool GeomInteraction::do_debug_draw;

String GeomInteraction::GetDesc() const {
	return String();
}

bool GeomInteraction::IsGeomDrawBegin() {
	return false;
}

bool GeomInteraction::Key(dword key, int count) {
	return false;
}

bool GeomInteraction::HotKey(dword key) {
	return false;
}

void GeomInteraction::DeepMouseLeave() {
	if (GetCaptured()) {
		
	}
	else {
		has_mouse_deep = false;
		if (has_mouse) {
			MouseLeave();
			SetWithMouse(NULL);
			has_mouse = false;
			MouseLeaveFrame();
		}
		for (GeomInteraction* c : sub) {
			if (c->has_mouse_deep) {
				c->DeepMouseLeave();
			}
		}
	}
}

void GeomInteraction::MouseLeave() {
	if (do_debug_draw)
		Refresh();
}

void GeomInteraction::Show(bool b) {
	hidden = !b;
}

bool GeomInteraction::IsShown() const {
	return !hidden;
}






GeomInteraction2D::GeomInteraction2D() {
	ignore_mouse = false;
	hidden = false;
	
	cmd_begin.next = &cmd_frame;
	cmd_frame.prev = &cmd_begin;
	cmd_frame.next = &cmd_pre;
	cmd_pre.prev = &cmd_frame;
	cmd_pre.next = &cmd_post;
	cmd_post.prev = &cmd_pre;
	cmd_post.next = &cmd_end;
	cmd_end.prev = &cmd_post;
}

void GeomInteraction2D::Add(GeomInteraction2D& c) {
	for (GeomInteraction* s : sub)
		if (GeomInteraction2D* s0 = CastPtr<GeomInteraction2D>(s))
			if (s0 == &c)
				return;
	cmd_post.prev = &c.cmd_end;
	c.cmd_end.next = &cmd_post;
	if (sub.GetCount()) {
		GeomInteraction& top = *sub.Top();
		c.cmd_begin.prev = &top.cmd_end;
		top.cmd_end.next = &c.cmd_begin;
	}
	else {
		c.cmd_begin.prev = &cmd_pre;
		cmd_pre.next = &c.cmd_begin;
	}
	sub.Add(&c);
	c.owner = this;
	c.Activate();
}

GeomInteraction2D* GeomInteraction2D::GetIndexSub(int i) {
	return CastPtr<GeomInteraction2D>(sub[i]);
}

int GeomInteraction2D::GetSubCount() const {
	return sub.GetCount();
}


void GeomInteraction2D::AddSub(GeomInteraction2D* c) {
	if (!c) return;
	Add(*c);
}

GeomInteraction2D* GeomInteraction2D::GetLastSub() {
	return CastPtr<GeomInteraction2D>(sub.Top());
}

void GeomInteraction2D::RemoveSub(GeomInteraction2D* c) {
	for(int i = 0; i < sub.GetCount(); i++) {
		if (sub[i] == c) {
			/*DrawCommand* prev;
			if (i > 0)
				prev = &sub[i-1]->cmd_end;
			else
				prev = &cmd_pre;
			
			DrawCommand* next;
			if (i < sub.GetCount()-1)
				next = &sub[i+1]->cmd_begin;
			else
				next = &cmd_post;*/
			
			c->cmd_end.next->prev = c->cmd_begin.prev;
			c->cmd_begin.prev->next = c->cmd_end.next;
			c->cmd_end.next = NULL;
			c->cmd_begin.prev = NULL;
			
			c->Deactivate();
			c->owner = NULL;
			sub.Remove(i--);
		}
	}
}

GeomInteraction2D* GeomInteraction2D::GetOwner() const {
	return CastPtr<GeomInteraction2D>(owner);
}

Image GeomInteraction2D::FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

Image GeomInteraction2D::MouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

void GeomInteraction2D::MouseEnter(Point frame_p, dword keyflags) {
	if (do_debug_draw)
		Refresh();
}

Image GeomInteraction2D::CursorImage(Point p, dword keyflags) {
	return DefaultImages::Arrow;
}

int GeomInteraction2D::GetCount() const {
	return sub.GetCount();
}

GeomInteraction2D* GeomInteraction2D::operator[](int i) {
	return CastPtr<GeomInteraction2D>(sub[i]);
}


NAMESPACE_TOPSIDE_END
