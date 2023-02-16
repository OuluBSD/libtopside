#include "ParallelLib.h"

#if IS_UPP_CORE
// TopWindow
#include <CtrlLib/CtrlLib.h>
#endif

NAMESPACE_PARALLEL_BEGIN

template <class Dim>
ScopeT<Dim>::ScopeT()
{
	SetFrameBox(Dim::GetDefaultScopeDimensions());

	handle_counter = 0;
	maximize_all = false;
	active_pos = -1;
	active_id = -1;
	
	#if 0
	this->SetPendingLayout();
	this->SetPendingRedraw();
	#else
	//desktop.Invalidate(); // not needed
	#endif
	
}

#if 0
template <class Dim>
bool ScopeT<Dim>::Init()
{
	this->SetPendingLayout();
	this->SetPendingRedraw();
	this->SetPendingEffectRedraw();
	
	return true;
}

template <class Dim>
bool ScopeT<Dim>::IsGeomDrawBegin() const {
	return true;
}

template <class Dim>
bool ScopeT<Dim>::Poll(typename Dim::Event& e)
{
	return false;
}

template <class Dim>
void ScopeT<Dim>::Paint(DrawT& draw) {
	TODO // persistent
}

template <>
void ScopeT<Ctx2D>::Paint(DrawT& draw) {
	Color bg = Color(28, 127, 150);
	Sz handle_sz(this->GetFrameBox().GetSize());
	draw.DrawRect(handle_sz, bg);
}

template <class Dim>
void ScopeT<Dim>::Render()
{
	Box b = this->GetFrameBox();
	Sz sz = b.GetSize();
	
	if (pd.GetPageSize() != sz)
		pd.Create(sz);
	
	CmdPainter& pp = pd.GetPainter();
	
	pd.cmd_screen_begin.Check();
	
	pp.Attach(this->GetCommandBegin(), this->GetCommandEnd()); // <-- attach window to this
	
	pd.cmd_screen_begin.Check();

	do_render = CheckRender();
	
	pd.cmd_screen_begin.Check();
	
	//pp.Dump();
	
}

template <class Dim>
void ScopeT<Dim>::Shutdown()
{
	TODO
}

template <class Dim>
bool ScopeT<Dim>::ProcessCloseQueue()
{
	bool ret = close_handle_queue.GetCount();

	for(int i = 0; i < close_handle_queue.GetCount(); i++)
		CloseHandle(close_handle_queue[i]);

	close_handle_queue.Clear();

	return ret;
}

template <class Dim>
bool ScopeT<Dim>::Key(dword key, int count)
{
	if(key == (K_CTRL | K_F4)) {
		QueueCloseHandle(active_id);
		return true;
	}
	if(key == (K_CTRL | K_TAB)) {
		active_pos++;
		if(active_pos >= handles.GetCount())
			active_pos = 0;
		FocusHandlePos(active_pos);
		return true;
	}
	if(key == (K_CTRL | K_SHIFT | K_TAB)) {
		active_pos--;
		if(active_pos < 0)
			active_pos = handles.GetCount() - 1;
		FocusHandlePos(active_pos);
		return true;
	}
	return false;
}

/*template <class Dim>
void ScopeT<Dim>::LeftDown(Point p, dword keyflags) {
    //LOG(p);

}*/

template <class Dim>
void ScopeT<Dim>::Layout()
{
	for(GeomInteraction* c : this->sub) {
		Interaction* c2 = CastPtr<Interaction>(c);
		if(c2) {
			Box r = c2->GetFrameBox();
			if(r.IsEmpty()) {
				// Set default handle rect (could be smarter)
				r = Dim::GetDefaultHandleDimensions(30);
				c2->SetFrameBox(r);
			}
		}
	}

	// Resize active Handle if it is maximised and ScopeT<Dim> area size changes (TopContainer
	// area changes usually)
	if(maximize_all) {
		if(active_pos < 0 || active_pos >= handles.GetCount())
			return;
		Sz sz(this->GetFrameSize());
		Handle& h = handles[active_pos];
		h.SetFrameBox(BoxC(Pt(Null), sz));
	}
}

template <class Dim>
void ScopeT<Dim>::PostLayout()
{
	Handle* win = GetActiveHandle();
	if(win && win->IsMaximized())
		SetHandleMaximized(*win, true);
}

template <class Dim>
bool ScopeT<Dim>::IsCaptureRoot() const
{
	return true;
}

template <class Dim>
bool ScopeT<Dim>::MouseMoveInFrame(Pt pt, dword keyflags) {
	return Dim::Interaction::MouseMoveInFrame(pt, keyflags);
}

template <class Dim>
bool ScopeT<Dim>::DeepMouseMove(const Pt& pt, dword keyflags) {
	global_mouse = pt;
	
	return Dim::Interaction::DeepMouseMove(pt, keyflags);
}



template <class Dim>
void ScopeT<Dim>::SetCaptured(GeomInteraction* c) {
	captured = CastPtr<Interaction>(c);
	captured_ctrl = CastPtr<Container>(c);
	ASSERT_(captured || !c, "expected same Dim::Interaction class"); // might be okay, but don't know yet
}

template <class Dim>
void ScopeT<Dim>::SetWithMouse(GeomInteraction* c) {
	with_mouse = CastPtr<Interaction>(c);
	with_mouse_ctrl = CastPtr<Container>(c);
	ASSERT_(with_mouse || !c, "expected same Dim::Interaction class"); // might be okay, but don't know yet
}

#endif

template <class Dim>
bool ScopeT<Dim>::CheckRender()
{
	TODO
	#if 0
	bool do_render = false;

	if(this->IsPendingLayout()) {
		this->DeepLayout();
		this->SetPendingEffectRedraw();
	}

	int sc = this->GetSubCount();
	for(int i = 0; i < sc; i++) {
		typename Dim::Interaction* c = this->At(i);

		if(c->IsPendingLayout()) {
			c->DeepLayout();
			c->SetPendingEffectRedraw();
		}
	}

	do_render = this->Redraw(true) || do_render;

	return do_render;
	#endif
}

template <class Dim>
typename ScopeT<Dim>::Frame* ScopeT<Dim>::GetFrame(TopContainer& tw)
{
	TODO
	#if 0
	for(int i = 0; i < handles.GetCount(); i++) {
		TopContainer* ptr = handles[i].GetTopContainer();
		if(ptr == &tw) {
			return &handles[i];
		}
	}
	NEVER();
	return 0;
	#endif
}

template <class Dim>
void ScopeT<Dim>::FocusHandle(TopContainer* tw)
{
	TODO
	#if 0
	for(int i = 0; i < handles.GetCount(); i++) {
		TopContainer* ptr = handles[i].GetTopContainer();
		if(ptr == tw) {
			FocusHandle(i);
			return;
		}
	}
	#endif
}

template <class Dim>
void ScopeT<Dim>::MoveHandle(Pt pt, int handle_id)
{
	TODO
	#if 0
	if(maximize_all)
		return;
	Handle& h = handles.Get(handle_id);
	Sz sz(h.GetFrameSize());
	Pt tl = FirstCorner(h.GetFrameBox());
	tl += pt;
	h.SetFrameBox(BoxC(tl, sz));
	#endif
}

template <class Dim>
void ScopeT<Dim>::FocusHandle(int handle_id)
{
	int i = handles.Find(handle_id);
	if(i >= 0)
		FocusHandlePos(i);
}

template <class Dim>
void ScopeT<Dim>::FocusHandlePos(int handle_pos)
{
	TODO
	#if 0
	if(handle_pos < 0 || handle_pos >= handles.GetCount())
		return;
	Handle& h = handles[handle_pos];
	h.Show();
	Interaction* c = &h;
	if(GetLastSub() == c) {
		int prev_active_id = active_id;
		active_pos = handle_pos;
		active_id = handles.GetKey(handle_pos);
		if(handles.Find(prev_active_id) != -1)
			handles.Get(prev_active_id).Refresh();
		this->Refresh();
		return;
	}

	if(!h.IsMaximized()) {
		if(maximize_all)
			MaximizeHandle(handles.GetKey(handle_pos));
	}
	else {
		Sz sz(this->GetFrameSize());
		Handle& h = handles[handle_pos];
		h.SetFrameBox(BoxC(Pt(), sz));
	}
	h.GetTopContainer()->FocusEvent();
	this->RemoveSub(&h);
	this->AddSub(&h);
	int prev_active_id = active_id;
	active_pos = handle_pos;
	active_id = handles.GetKey(handle_pos);
	if(handles.Find(prev_active_id) != -1)
		handles.Get(prev_active_id).Refresh();
	h.Refresh();
	this->Refresh();
	WhenActiveHandleChanges();
	#endif
}

template <class Dim>
void ScopeT<Dim>::CloseHandle(int handle_id)
{
	TODO
	#if 0
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return;
	Handle& h0 = handles[handle_pos];

	if(h0.HasMouseDeep())
		h0.DeepMouseLeave();
	if(h0.HasFocusDeep())
		h0.DeepUnfocus();
	this->RemoveSub(&h0);
	TopContainer* tw = h0.GetTopContainer();
	handles.Remove(handle_pos);
	this->Refresh();
	FocusPrevious();
	WhenHandleClose();
	#endif
}

template <class Dim>
void ScopeT<Dim>::MaximizeHandle(int handle_id)
{
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return;
	Frame& h = handles[handle_pos];
	SetHandleMaximized(h, 1);
}

template <class Dim>
void ScopeT<Dim>::RestoreHandle(int handle_id)
{
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return;
	Frame& h = handles[handle_pos];
	SetHandleMaximized(h, 0);
}

template <class Dim>
void ScopeT<Dim>::SetHandleMaximized(Frame& h, bool b)
{
	TODO
	#if 0
	Sz sz(this->GetFrameSize());
	if(b) {
		if(!h.IsMaximized()) {
			h.StoreRect();
			h.SetMaximized(true);
		}
		h.SetFrameBox(BoxC(Pt(), sz));
		maximize_all = true;
	}
	else {
		h.LoadRect();
		h.SetMaximized(false);
		maximize_all = false;
		LoadDimsAll();

		Sz h_size = h.GetFrameSize();
		if(h_size.cx > sz.cx || h_size.cy > sz.cy) {
			h.SetFrameBox(BoxC(Pt(10), sz - Sz(20)));
		}
	}
	this->SetPendingLayout();
	#endif
}

template <class Dim>
void ScopeT<Dim>::LoadDimsAll()
{
	TODO
	#if 0
	for(int i = 0; i < handles.GetCount(); i++) {
		Handle& h = handles[i];
		if(h.IsMaximized()) {
			h.LoadRect();
			h.SetMaximized(false);
		}
	}
	#endif
}

template <class Dim>
void ScopeT<Dim>::MinimizeHandle(int handle_id)
{
	TODO
	#if 0
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return;
	Handle& h = handles[handle_pos];
	h.Hide();
	FocusPrevious();
	#endif
}

template <class Dim>
void ScopeT<Dim>::FocusPrevious()
{
	TODO
	#if 0
	this->SetPendingLayout();
	int handle_pos = active_pos;
	// Focus previous
	int count = handles.GetCount();
	while(handle_pos >= count)
		handle_pos--;
	for(int i = 0; i < count; i++) {
		if(handle_pos <= -1)
			handle_pos = count - 1;
		Handle& h2 = handles[handle_pos];
		// if (!maximize_all && !h2.IsShown()) {
		if(!h2.IsShown()) {
			handle_pos--;
			continue;
		}
		FocusHandlePos(handle_pos);
		return;
	}
	active_id = -1;
	active_pos = -1;
	#endif
}

template <class Dim>
void ScopeT<Dim>::SetTitle(int handle_id, String title)
{
	TODO
	#if 0
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return;
	Handle& h = handles[handle_pos];
	h.Title(title);
	
	this->SetPendingEffectRedraw();
	this->PostRefresh();
	#endif
}

template <class Dim>
String ScopeT<Dim>::GetTitle(int handle_id)
{
	TODO
	#if 0
	int handle_pos = handles.Find(handle_id);
	if(handle_pos == -1)
		return "";
	Handle& h = handles[handle_pos];
	return h.GetTitle();
	#endif
}

template <class Dim>
void ScopeT<Dim>::CloseAll()
{
	TODO
	#if 0
	for(int i = 0; i < handles.GetCount(); i++) {
		QueueCloseHandle(handles.GetKey(i));
	}
	this->SetPendingLayout();
	#endif
}

template <class Dim>
void ScopeT<Dim>::CloseOthers(int handle_id)
{
	for(int i = 0; i < handles.GetCount(); i++) {
		if(handles.GetKey(i) == handle_id)
			;
		else
			QueueCloseHandle(handles.GetKey(i));
	}
}

template <class Dim>
typename ScopeT<Dim>::Frame* ScopeT<Dim>::GetActiveHandle()
{
	TODO
	#if 0
	if(active_pos >= 0 && active_pos < handles.GetCount())
		return &handles[active_pos];
	return 0;
	#endif
}

#if 0
template <class Dim>
typename Dim::Interaction* ScopeT<Dim>::GetLastSub()
{
	if (this->sub.IsEmpty())
		return 0;
	Interaction* last = CastPtr<Interaction>(this->sub.Top());
	return last;
}
#endif

template <class Dim>
typename Dim::TopContainer* ScopeT<Dim>::GetVisibleTopContainer()
{
	TODO
	#if 0
	Interaction* last = GetLastSub();
	for(int i = 0; i < handles.GetCount(); i++) {
		Handle& h = handles[i];
		Interaction* ptr = &h;
		if(ptr == last) {
			return h.GetTopContainer();
		}
	}
	return 0;
	#endif
}

template <class Dim>
void ScopeT<Dim>::OrderTileHandles()
{
	TODO
	#if 0
	int count = handles.GetCount();
	if(maximize_all && count == 1)
		return;

	Sz sz(this->GetFrameSize());

	double target_ratio = 16.0 / 9.0; // 4.0 / 3.0;

	int rows, cols, mod, diff;
	int smallest_diff = INT_MAX;
	int smallest_diff_cols = -1;
	double smallest_diff_ratio_diff = DBL_MAX, ratio, ratio_diff;
	for(int i = 1; i < 100; i++) {
		rows = count / i;
		if(rows == 0)
			break;
		cols = i;
		mod = count % (rows * cols);
		diff = abs(rows - cols);
		// if (mod == 0)
		ratio = ((double)sz.cx / cols) / ((double)sz.cy / rows);
		// else
		// ratio = (((double)sz.cx/cols) / ((double)sz.cy/rows) * (rows * (cols-1)) +
		// ((double)sz.cx/cols) / ((double)sz.cy/(rows + mod)) * ((rows + mod) * 1)) / count;
		ratio_diff = fabs(ratio - target_ratio);

		// LOG(Format("rows=%d cols=%d mod=%d diff=%d ratio_diff=%f", rows, cols, mod, diff,
		// ratio_diff));

		// if (i <= smallest_diff) {
		if(ratio_diff < smallest_diff_ratio_diff && mod <= 2) {
			smallest_diff = diff;
			smallest_diff_cols = i;
			smallest_diff_ratio_diff = ratio_diff;
		}
	}
	rows = count / smallest_diff_cols;
	if(rows == 0)
		return;
	cols = smallest_diff_cols;
	mod = count % (rows * cols);
	diff = abs(rows - cols);
	ratio_diff = smallest_diff_ratio_diff;

	// LOG(Format("rows=%d cols=%d mod=%d diff=%d ratio_diff=%f", rows, cols, mod, diff,
	// ratio_diff));

	double x_step, y_step, ymod_step;
	x_step = (double)sz.cx / cols;
	y_step = (double)sz.cy / rows;
	ymod_step = (double)sz.cy / (rows + mod);

	maximize_all = false;

	int pos = 0;
	for(int i = 0; i < cols; i++) {
		int x = i * x_step;
		int rows_i;
		double yi_step;
		if(i < cols - 1) {
			rows_i = rows;
			yi_step = y_step;
		}
		else {
			rows_i = rows + mod;
			yi_step = ymod_step;
		}
		for(int j = 0; j < rows_i; j++) {
			int y = j * yi_step;
			Handle& h = handles[pos];
			h.SetFrameBox(BoxC<Box>(x, y, x_step, yi_step));
			h.SetMaximized(false);
			pos++;
		}
	}
	this->SetPendingLayout();
	#endif
}

template <class Dim>
void ScopeT<Dim>::OrderTileHandlesVert()
{
	TODO
	#if 0
	int count = handles.GetCount();
	if(maximize_all && count == 1)
		return;

	Sz sz(this->GetFrameSize());

	double y_step = (double)sz.cy / handles.GetCount();

	maximize_all = false;

	for(int i = 0; i < handles.GetCount(); i++) {
		Handle& h = handles[i];
		h.SetFrameBox(BoxC<Box>(0, i * y_step, sz.cx, y_step));
		h.SetMaximized(false);
	}
	#endif
}

/*template <class Dim>
bool ScopeT<Dim>::DeepKey(dword key, int count) {
    Handle* active = GetActiveHandle();
    if (active)
        return active->DeepKey(key, count);
    return false;
}*/

/*template <class Dim>
void ScopeT<Dim>::SetCaptured(Container* c) {
	captured = c;
	captured_ctrl = c;
}

template <class Dim>
void ScopeT<Dim>::SetWithMouse(Container* c) {
	with_mouse = c;
	with_mouse_ctrl = c;
}*/

#if IS_UPP_CORE

#if 0
template <>
void ScopeT<Ctx2D>::SetCaptured(GeomInteraction* c) {
	captured = CastPtr<Interaction>(c);
	#if IS_UPP_CORE
	CtrlGeomBase* cgb = CastPtr<CtrlGeomBase>(c);
	captured_ctrl = cgb ? cgb->GetCtrl() : 0;
	#else
	captured_ctrl = CastPtr<Container>(c);
	#endif
	ASSERT_(captured || !c, "expected same Dim::Interaction class"); // might be okay, but don't know yet
}

template <>
void ScopeT<Ctx2D>::SetWithMouse(GeomInteraction* c) {
	with_mouse = CastPtr<Interaction>(c);
	#if IS_UPP_CORE
	CtrlGeomBase* cgb = CastPtr<CtrlGeomBase>(c);
	with_mouse_ctrl = cgb ? cgb->GetCtrl() : 0;
	#else
	with_mouse_ctrl = CastPtr<Container>(c);
	#endif
	ASSERT_(with_mouse || !c, "expected same Dim::Interaction class"); // might be okay, but don't know yet
}

template <>
void ScopeT<Ctx2D>::SetCaptured(Container* c) {
	#if IS_UPP_CORE
	TODO // get GeomInteraction2D from Ctrl
	#else
	captured = c;
	#endif
	captured_ctrl = c;
}

template <>
void ScopeT<Ctx2D>::SetWithMouse(Container* c) {
	#if IS_UPP_CORE
	TODO // get GeomInteraction2D from Ctrl
	#else
	with_mouse = c;
	#endif
	with_mouse_ctrl = c;
}
#endif
	
#endif

template <class Dim>
void ScopeT<Dim>::AddInterface(TopContainer& tw)
{
	Box b = ::TS::GetFrameBox<Container,Box>(desktop);
	ASSERT(b.Width() > 0);
	int id = handle_counter++;
	int pos = handles.GetCount();

	Frame& h = handles.Add(id);
	h.RefScopeParent<RefParent1<ScopeT<Dim>>>::SetParent(this);
	h.SetId(id);
	
	//GeomInteraction::Add(h); // Add to Interaction (e.g. GeomInteraction2D)

	// Default initial position
	int i = handles.GetCount();
	int offset = i * 30;
	h.SetFrameBox(Dim::GetDefaultHandleDimensions(offset));

	if(maximize_all)
		this->MaximizeHandle(id);

	int prev_active_id = active_id;
	active_pos = pos;
	active_id = id;
	int prev_active_pos = handles.Find(prev_active_id);
	if(prev_active_pos >= 0)
		handles[prev_active_pos].Refresh();

	WhenActiveHandleChanges();

	String title = h.GetTitle();
	h.SetTitle(title.GetCount() ? title : "Unnamed");
	
	desktop.Refresh();
	
	h.Layout();
	h.Refresh();
	
	tw.SetTopFrame(h);
}

HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(ScopeT)

NAMESPACE_PARALLEL_END
