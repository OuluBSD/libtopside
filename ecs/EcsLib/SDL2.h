#ifndef _EcsLib_SDL2_h_
#define _EcsLib_SDL2_h_

#if 0

NAMESPACE_OULU_BEGIN


class SDL2_System : public System<SDL2_System> {
	bool is_open = false;
	
	uint32 prev_ticks;
	uint32 prev_global_ticks;
	
	bool is_lalt = false, is_lshift = false, is_lctrl = false;
	bool is_ralt = false, is_rshift = false, is_rctrl = false;
	uint32 key = 0;
	uint32 mouse_code;
	int mouse_zdelta, x, y, dx, dy;
	Point prev_mouse_pt, mouse_pt;
	
	
public:
	SDL2_System(Machine& m);
	
	void RunTest();
	
    bool Initialize() override;
    void Start() override;
    void Update(float dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void FatalError(String msg);
	
protected:
	friend class Font;
	friend class CoreWindow;
	
	
	//bool Poll(Event& e);
	void Render(float dt);
	
	void KeyboardPad(int key, bool down);
	
	Callback WhenUserShutdownSignal;
	Callback2<int, int> WhenKey;
	Callback1<Point> WhenMouseMove;
	Callback2<Point, int> WhenMouse, WhenMouseScroll;
	
protected:
	friend class ScreenSDL2;
	
	Index<void*> screens;
	
	
	void AddScreen(ScreenSDL2& screen);
	void RemoveScreen(ScreenSDL2& screen);
	
	
};


NAMESPACE_OULU_END

#endif
#endif
