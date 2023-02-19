#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


bool GeomInteraction::do_debug_draw = false;


GeomInteraction::GeomInteraction() {
	ignore_mouse = false;
	hidden = false;
	pending_fx_redraw = true;
	pending_redraw = true;
	pending_layout = true;
	want_focus = false;
	has_focus = false;
	has_focus_deep = false;
	has_mouse = false;
	has_mouse_deep = false;
	modify = true;
	
}

String GeomInteraction::GetDesc() const {
	return String();
}

bool GeomInteraction::HasCapture() const {
	return GetCaptured() == this;
}

bool GeomInteraction::IsGeomDrawBegin() const {
	return false;
}

bool GeomInteraction::Key(dword key, int count) {
	return false;
}

bool GeomInteraction::IsCaptureRoot() const {
	return false;
}

GeomInteraction* GeomInteraction::GetCaptured() const {
	const GeomInteraction* db = GetGeomDrawBegin();
	if (db)
		return db->GetCaptured();
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

/*Ctrl* GeomInteraction::GetCtrl() {
	return 0;
}*/

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
	TODO
	#if 0
	::UPP::SetTimeCallback(1, cb, this);
	#endif
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
	GeomInteraction* draw_begin = GetGeomDrawBegin();
	if (draw_begin != this)
		draw_begin->SetCaptured(c);
}

void GeomInteraction::SetWithMouse(GeomInteraction* c) {
	GeomInteraction* draw_begin = GetGeomDrawBegin();
	if (draw_begin != this)
		draw_begin->SetWithMouse(c);
}

void GeomInteraction::DeepLayout() {
	TODO
}

void GeomInteraction::DeepFrameLayout() {
	// pass
}

String GeomInteraction::GetDrawCommandString() const {
	const DrawCommand* it = &cmd_begin;
	int i = 0;
	String s;
	while (it) {
		s << i++ << ": " << it->ToString() << "\n";
		it = it->next;
	}
	return s;
}

void GeomInteraction::DumpDrawCommands() const {
	LOG(GetDrawCommandString());
}

bool GeomInteraction::Dispatch(const CtrlEvent& e) {
	TODO
	/*
	Difficult circular dependency problem:
		- TS/UPP: GeomInteraction -> Gubo
		- TS/UPP: CtrlCore -> Gubo
		- UPP: CtrlCore -> GeomInteraction
		- TS: GeomInteraction -> CtrlCore
		? GeomCore ? SharedCore ?
	*/
	switch (e.type) {
		case EVENT_KEYDOWN:
			DeepKey(e.value, e.n);
			return true;
			
		/*
		case EVENT_KEYUP:
			DeepKey(e.value | K_KEYUP, e.n);
			return true;
		*/
		
		default:
			return false;
	}
}

GeomInteraction* GeomInteraction::GetGeomDrawBegin() {
	GeomInteraction* gi = this;
	while (gi) {
		if (gi->IsGeomDrawBegin())
			return gi;
		gi = gi->GetOwner();
	}
	return 0;
}

const GeomInteraction* GeomInteraction::GetGeomDrawBegin() const {
	const GeomInteraction* gi = this;
	while (gi) {
		if (gi->IsGeomDrawBegin())
			return gi;
		gi = gi->GetOwner();
	}
	return 0;
}

void GeomInteraction::Refresh() {
	SetPendingRedrawDeep();
	
}

void GeomInteraction::SetPendingRedrawDeep() {
	SetPendingEffectRedraw();
	SetPendingRedraw();
	int c = sub.GetCount();
	for(int i = 0; i < c; i++) {
		sub[i]->SetPendingRedrawDeep();
	}
}

GeomInteraction* GeomInteraction::FindProxy() {
	GeomInteraction* gi = this;
	while (gi) {
		GeomInteraction* linked = GetProxy();
		if (linked)
			return linked;
		gi = gi->GetOwner();
	}
	return 0;
}


NAMESPACE_TOPSIDE_END
