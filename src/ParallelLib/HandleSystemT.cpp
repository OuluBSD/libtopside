#include "ParallelLib.h"

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
HandleSystemT<Dim>::HandleSystemT(Machine& m) :
	RefScopeEnabler<MetaSystemBase, MetaMachineBase>::SP(m) {
	
}

template <class Dim>
bool HandleSystemT<Dim>::Initialize() {
	return true;
}

template <class Dim>
void HandleSystemT<Dim>::Start() {
	
}

template <class Dim>
void HandleSystemT<Dim>::Update(double dt) {
	bool closed = false;
	
	#if 0
	for(int i = 0; i < scopes.GetCount(); i++) {
		Scope& s = scopes[i];
		
		#if 0
		Event e;
		while (s.Poll(e)) {
			
			if (e.type == EVENT_SHUTDOWN) {
				if (close_machine_when_empty)
					this->GetMachine().SetNotRunning();
			}
			
		}
		closed = s.ProcessCloseQueue() || closed;
		
		s.Render();
		#endif
		
		// TODO multi AtomVirtualGui support and update VirtualGuiPtr here
		//      also, put Ctrl::desktop etc to own class and instance
		ASSERT(scopes.GetCount() == 1);
		Ctrl::PaintAll();
	}
	#endif
}

template <class Dim>
void HandleSystemT<Dim>::Stop() {
	
}

template <class Dim>
void HandleSystemT<Dim>::Uninitialize() {
	for (Scope& s : scopes) {
		s.CloseAll();
	}
	scopes.Clear();
}

template <class Dim>
typename HandleSystemT<Dim>::Scope& HandleSystemT<Dim>::AddScope() {
	ASSERT_(scopes.IsEmpty(), "only 1 screen support is implemented for now: see static Ctrl::SetWindows");
	lock.Enter();
	Scope& s = scopes.Add();
	s.SetParent(RefParent1<HandleSystemT<Dim>>(this));
	lock.Leave();
	
	//s.Init();
	
	return s;
}

template <class Dim>
void HandleSystemT<Dim>::RealizeScope() {
	if (scopes.IsEmpty()) {
		Scope& s = AddScope();
		active_pos = 0;
	}
}

template <class Dim>
ScopeT<Dim>& HandleSystemT<Dim>::GetActiveScope() {
	RealizeScope();
	
	if (active_pos < 0 || active_pos >= scopes.GetCount())
		active_pos = 0;
	return scopes[active_pos];
}

template <class Dim>
ScopeT<Dim>& HandleSystemT<Dim>::GetScope(int idx) {
	if (idx < 0 || idx >= scopes.GetCount())
		Panic("HandleSystemT::GetScope: Invalid scope id");
	return scopes[idx];
}

template <class Dim>
void HandleSystemT<Dim>::DoEvents(const EventCollection& ev) {
	Scope& scope = GetActiveScope();
	Desktop& d = scope.GetDesktop();
	
	for (const Event& e : ev) {
		switch (e.type) {
		case EVENT_SHUTDOWN:
			this->GetMachine().SetNotRunning();
			break;
		
		case EVENT_KEYDOWN:
			Ctrl::DoKeyFB(e.value, e.n);
			break;
			
		case EVENT_KEYUP:
			Ctrl::DoKeyFB(e.value | K_KEYUP, e.n);
			break;
		
		case EVENT_MOUSEMOVE:
			Ctrl::DoMouseFB(Ctrl::MOUSEMOVE, e.pt);
			break;
		
		case EVENT_MOUSEWHEEL:
			Ctrl::DoMouseFB(Ctrl::MOUSEWHEEL, e.pt, e.value * 120);
			break;
		
		case EVENT_MOUSE_EVENT:
			Ctrl::DoMouseFB(e.n, e.pt, e.value);
			break;
		
		default:
			TODO
		}
	}
}

template <class Dim>
void HandleSystemT<Dim>::Close() {
	TODO
	#if 0
	for(Scope& s : scopes) {
		s.CloseAll();
		s.ProcessCloseQueue();
	}
	owned_wins.Clear();
	
	for(int i = scopes.GetCount()-1; i >= 0; i--)
		scopes[i].Shutdown();
	scopes.Clear();
	#endif
}

template <class Dim>
void HandleSystemT<Dim>::CloseContainer(TopContainer* tc) {
	lock.Enter();
	for(int i = 0; i < owned_wins.GetCount(); i++) {
		if (&owned_wins[i] == tc) {
			owned_wins.Remove(i--);
		}
	}
	lock.Leave();
}

template <class Dim>
void HandleSystemT<Dim>::Set_SetMouseCursor(void (*fn)(void*,const Image&), void* arg) {
	set_mouse_cursor = fn;
	set_mouse_cursor_arg = arg;
}

template <class Dim>
void HandleSystemT<Dim>::Set_GetMouseCursor(Image (*fn)(void*), void* arg) {
	get_mouse_cursor = fn;
	get_mouse_cursor_arg = arg;
}

template <class Dim>
Image HandleSystemT<Dim>::OverrideCursor(const Image& m) {
	Image cursor;
	if (get_mouse_cursor) {
		cursor = get_mouse_cursor(get_mouse_cursor_arg);
	}
	if (set_mouse_cursor) {
		set_mouse_cursor(set_mouse_cursor_arg, m);
	}
	return cursor;
}

template <class Dim>
Image HandleSystemT<Dim>::DefaultCursor() {
	Image cursor;
	if (get_mouse_cursor) {
		cursor = get_mouse_cursor(get_mouse_cursor_arg);
	}
	if (set_mouse_cursor) {
		set_mouse_cursor(set_mouse_cursor_arg, Image());
	}
	return cursor;
}


#if IS_UPP_CORE

template <>
bool HandleSystemT<CtxUpp2D>::Initialize() {
	RealizeScope();
	return true;
}

#endif

PLIB_TYPE_EXCPLICIT_INITIALIZE_CLASS(HandleSystemT)


NAMESPACE_PARALLEL_END
