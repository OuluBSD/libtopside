#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


bool GeomInteraction::do_debug_draw;


GeomInteraction::GeomInteraction() {
	
}

String GeomInteraction::GetDesc() const {
	return String();
}

bool GeomInteraction::IsGeomDrawBegin() {
	return false;
}

bool GeomInteraction::Key(dword key, int count) {
	return false;
}

bool GeomInteraction::IsCaptureRoot() const {
	return false;
}

GeomInteraction* GeomInteraction::GetCaptured() const {
	return 0;
}

GeomInteraction* GeomInteraction::GetWithMouse() const {
	return 0;
}

bool GeomInteraction::HotKey(dword key) {
	return false;
}

bool GeomInteraction::Is2D() const {
	return false;
}

bool GeomInteraction::Is3D() const {
	return false;
}

bool GeomInteraction::IsCtrl() const {
	return false;
}

GeomInteraction2D* GeomInteraction::Get2D() {
	return 0;
}

GeomInteraction3D* GeomInteraction::Get3D() {
	return 0;
}

Ctrl* GeomInteraction::GetCtrl() {
	return 0;
}

int GeomInteraction::GetSubCount() const {
	return sub.GetCount();
}

void GeomInteraction::ClearSub() {
	sub.Clear();
}

bool GeomInteraction::IsModified() const {
	TODO
	/*GuiLock __;
	return modify;*/
}

void GeomInteraction::SetModify() {
	TODO
	/*GuiLock __;
	modify = true;*/
}

void GeomInteraction::ClearModify() {
	TODO
	/*GuiLock __;
	modify = false;*/
}

void GeomInteraction::SetFocus() {
	TODO
}

void GeomInteraction::DeepUnfocus() {
	TODO
}

void GeomInteraction::Add(GeomInteraction& c) {
	for (GeomInteraction* s : sub)
		if (s == &c)
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

void GeomInteraction::AddSub(GeomInteraction* c) {
	if (!c) return;
	Add(*c);
}

GeomInteraction* GeomInteraction::GetLastSub() {
	return sub.Top();
}

GeomInteraction* GeomInteraction::GetOwner() const {
	return owner;
}

GeomInteraction* GeomInteraction::GetIndexSub(int i) {
	return sub[i];
}

void GeomInteraction::RemoveSub(GeomInteraction* c) {
	for(int i = 0; i < sub.GetCount(); i++) {
		if (sub[i] == c) {
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

bool GeomInteraction::DeepKey(dword key, int count) {
	if (HasFocus()) {
		return Key(key, count);
	}
	else {
		for(GeomInteraction* c : sub) {
			if (c->HasFocusDeep())
				return c->DeepKey(key, count);
		}
		return false;
	}
}

void GeomInteraction::PostCallback(Callback cb) {
	SetTimeCallback(1, cb, this);
}

void GeomInteraction::PostRefresh() {
	PostCallback(THISBACK(Refresh0));
}

void GeomInteraction::PostLayoutCallback() {
	PostCallback(THISBACK(Layout0));
}

void GeomInteraction::Layout0() {
	Layout();
}

void GeomInteraction::Refresh0() {
	Refresh();
}

void GeomInteraction::SetCapture() {
	//SDL_CaptureMouse(SDL_TRUE);
	SetCaptured(this);
}

void GeomInteraction::ReleaseCapture() {
	//SDL_CaptureMouse(SDL_FALSE);
	SetCaptured(NULL);
}

void GeomInteraction::SetCaptured(GeomInteraction* c) {
	TODO
}

void GeomInteraction::SetWithMouse(GeomInteraction* c) {
	TODO
}


NAMESPACE_TOPSIDE_END
