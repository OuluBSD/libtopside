#include "GuboLib.h"

NAMESPACE_GUBO_BEGIN


template <class Dim>
HandleSystemT<Dim>::HandleSystemT(Parallel::Machine& m) :
	RefScopeEnabler<MetaSystemBase, MetaMachineBase>::SP(m) {
	
}

template <class Dim>
bool HandleSystemT<Dim>::Initialize() {
	return true;
}

template <>
bool HandleSystemT<Ctx2D>::Initialize() {
	//RealizeScope();
	return true;
}

template <class Dim>
void HandleSystemT<Dim>::Start() {
	
}

template <class Dim>
void HandleSystemT<Dim>::Update(double dt) {
	bool closed = false;
	
	for(int i = 0; i < scopes.GetCount(); i++) {
		Scope& s = scopes[i];
		
		Event e;
		while (s.Poll(e)) {
			
			if (e.type == EVENT_SHUTDOWN) {
				if (close_machine_when_empty)
					this->GetMachine().SetNotRunning();
			}
			
		}
		closed = s.ProcessCloseQueue() || closed;
		
		s.Render();
	}
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
	ASSERT_(scopes.IsEmpty(), "only 1 screen support is implemented for now: see static Surface::SetWindows");
	lock.Enter();
	Scope& s = scopes.Add();
	s.SetParent(RefParent1<HandleSystemT<Dim>>(this));
	lock.Leave();
	s.Init();
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
	
	for (const Event& e : ev) {
		if (e.type == EVENT_SHUTDOWN)
			this->GetMachine().SetNotRunning();
		else
			scope.Dispatch(e);
	}
}

template <class Dim>
void HandleSystemT<Dim>::Close() {
	for(Scope& s : scopes) {
		s.CloseAll();
		s.ProcessCloseQueue();
	}
	owned_wins.Clear();
	
	for(int i = scopes.GetCount()-1; i >= 0; i--)
		scopes[i].Shutdown();
	scopes.Clear();
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
Image HandleSystemT<Dim>::OverrideCursor(const Image& img) {
	TODO
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(HandleSystemT)


NAMESPACE_GUBO_END
