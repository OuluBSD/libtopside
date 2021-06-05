#include "OOSDL2.h"

NAMESPACE_SDL2_BEGIN


bool Events::Open0() {
	return true;
}

void Events::Close0() {
	
}

uint32 Events::GetTickCount() {
	return SDL_GetTicks();
}

void Events::WaitEvent(int ms) {
	SDL_WaitEventTimeout(NULL, ms);
}

bool Events::IsWaitingEvent() {
	SDL_PumpEvents();
	SDL_Event events;
	return SDL_PeepEvents(&events, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0;
}

unsigned int Events::WakeCb(Uint32 interval, void* param) {
	((Events*)param)->WokeUp();
	return 0;
}

void Events::WakeUpEventThread() {
	if (waketimer_id < 0)
		waketimer_id = SDL_AddTimer(20, &Events::WakeCb, this);
}

void Events::PutKeyFlags(dword& key) {
	if (is_lalt || is_ralt)			key |= K_ALT;
	if (is_lshift || is_rshift)		key |= K_SHIFT;
	if (is_lctrl || is_rctrl)		key |= K_CTRL;
}

bool Events::Poll(UPP::CtrlEvent& e) {
	SDL_Event event;
	Size screen_sz;
	Point mouse_pt;
#ifdef flagGUI
	Screen* scr = ctx->FindContextConnector<Screen>();
#endif
	dword key;
	int mouse_code;
	
	// Process the events
	while (SDL_PollEvent(&event)) {
		e.Clear();
		
	switch (event.type) {
		
		case SDL_WINDOWEVENT:
			
			/*if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
				if (IsCaptured())
					;//Ctrl::captured->LeftUp(prev_mouse_pt, 0);
				else
					DeepMouseLeave();
			}
			else*/
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				e.type = EVENT_SHUTDOWN;
				return true;
			}
			else if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				screen_sz.cx = event.window.data1;
				screen_sz.cy = event.window.data2;
#ifdef flagGUI
				if (scr)
					scr->screen_sz = screen_sz;
#endif
				/*SetFrameRect0(RectC(0, 0, screen_sz.cx, screen_sz.cy));
				SetContentRect(RectC(0, 0, screen_sz.cx, screen_sz.cyh));
				SetPendingLayout();
				SetPendingEffectRedraw();
				SetPendingRedraw();*/
				e.type = EVENT_WINDOW_RESIZE;
				e.sz = screen_sz;
				return true;
			}
			break;
		
			
		case SDL_KEYDOWN:
		
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:	event.type = SDL_QUIT; break;
				case SDLK_LALT:		is_lalt = true; break;
				case SDLK_RALT:		is_ralt = true; break;
				case SDLK_LSHIFT:	is_lshift = true; break;
				case SDLK_RSHIFT:	is_rshift = true; break;
				case SDLK_LCTRL:	is_lctrl = true; break;
				case SDLK_RCTRL:	is_rctrl = true; break;
			}
			
			key = event.key.keysym.sym;
			if (key & SDLK_SCANCODE_MASK) {
				key &= ~SDLK_SCANCODE_MASK;
				
				// TODO handle codes separately
				if (0 /*key == */) {
					
				}
				else key = 0;
			}
			PutKeyFlags(key);
			
			e.type = EVENT_KEYDOWN;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
			
		case SDL_KEYUP:
		
			switch (event.key.keysym.sym) {
				case SDLK_LALT:		is_lalt = false; break;
				case SDLK_RALT:		is_ralt = false; break;
				case SDLK_LSHIFT:	is_lshift = false; break;
				case SDLK_RSHIFT:	is_rshift = false; break;
				case SDLK_LCTRL:	is_lctrl = false; break;
				case SDLK_RCTRL:	is_rctrl = false; break;
			}
			
			key = event.key.keysym.sym | K_KEYUP;
			if (key & SDLK_SCANCODE_MASK) {
				key &= ~SDLK_SCANCODE_MASK;
				
				// TODO handle codes separately
				if (0 /*key == */) {
					
				}
				else key = 0;
			}
			PutKeyFlags(key);
			
			e.type = EVENT_KEYUP;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
			
		case SDL_MOUSEMOTION:
			mouse_pt = Point(event.motion.x, event.motion.y);
			key = 0;
			PutKeyFlags(key);
			
			e.type = EVENT_MOUSEMOVE;
			e.value = key;
			e.pt = mouse_pt;
			
			prev_mouse_pt = mouse_pt;
			return true;
		
		case SDL_MOUSEWHEEL:
			key = 0;
			PutKeyFlags(key);
			
			e.type = EVENT_MOUSEWHEEL;
			e.value = key;
			e.pt = mouse_pt;
			
			return true;
			
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			
			mouse_code = 0;
			//mouse_zdelta = 0;
			if (event.button.state == SDL_PRESSED) {
				if (event.button.clicks == 1) {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = Ctrl::LEFT_DOWN;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = Ctrl::MIDDLE_DOWN;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = Ctrl::RIGHT_DOWN;
				}
				else if (event.button.clicks == 2) {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = Ctrl::LEFT_DOUBLE;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = Ctrl::MIDDLE_DOUBLE;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = Ctrl::RIGHT_DOUBLE;
				}
				else {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = Ctrl::LEFT_TRIPLE;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = Ctrl::MIDDLE_TRIPLE;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = Ctrl::RIGHT_TRIPLE;
				}
				/*else if (event.button.button == SDL_BUTTON_WHEELUP)
					mouse_zdelta = 120;
				else if (event.button.button == SDL_BUTTON_WHEELDOWN)
					mouse_zdelta = -120;*/
			}
			else if (event.button.state == SDL_RELEASED) {
				if (event.button.button == SDL_BUTTON_LEFT)
					mouse_code = Ctrl::LEFT_UP;
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					mouse_code = Ctrl::MIDDLE_UP;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					mouse_code = Ctrl::RIGHT_UP;
			}
			
			if (mouse_code) {
				mouse_pt = Point(event.button.x, event.button.y);
				key = 0;
				PutKeyFlags(key);
				
				e.type = EVENT_MOUSE_EVENT;
				e.value = key;
				e.pt = mouse_pt;
				e.n = mouse_code;
				
				prev_mouse_pt = mouse_pt;
				return true;
			}
			
		default:
			break;
		}
	}
	
	
	return false;
}


NAMESPACE_SDL2_END
