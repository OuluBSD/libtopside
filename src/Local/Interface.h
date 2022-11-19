#ifndef _Local_Interface_h_
#define _Local_Interface_h_

NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;


#if 0

class IScreen {
	
public:
	IScreen() {}
	virtual ~IScreen() {}
	
	virtual bool Init(const String& arg)									= 0;
	virtual bool Open()														= 0;
	virtual void Close()													= 0;
	virtual void Destroy()													= 0;
	virtual void EventLoop()												= 0;
	
	virtual void GetSize(int* w, int* h) const								= 0;
	virtual void GetCursor(int* x, int* y) const							= 0;
	
	virtual void SetUpdateInterval(int value)								= 0;
	virtual void Paint()													= 0;
	virtual void MousePressHandler(int button, int state, int x, int y)		= 0;
	virtual void MouseMoveHandler(int x, int y)								= 0;
	virtual void KeyboardHandler(unsigned char key, int x, int y)			= 0;
	
	
	enum {
		SCR_SVGALIB,
		SCR_DIRECTFB,
		SCR_SDL1,
		SCR_SDL2,
		SCR_GLUT,
		SCR_GDK3,
		SCR_GTK3,
		SCR_QT5,
		SCR_WIN32,
	};
	
	
	
	
	/*enum {
		UNKNOWN,
		LEFT_DOWN,
		LEFT_DOUBLE,
		LEFT_TRIPLE,
		LEFT_DRAG,
		LEFT_HOLD,
		LEFT_REPEAT,
		LEFT_UP,
		RIGHT_DOWN,
		RIGHT_DOUBLE,
		RIGHT_TRIPLE,
		RIGHT_DRAG,
		RIGHT_HOLD,
		RIGHT_REPEAT,
		RIGHT_UP,
		MIDDLE_DOWN,
		MIDDLE_DOUBLE,
		MIDDLE_TRIPLE,
		MIDDLE_DRAG,
		MIDDLE_HOLD,
		MIDDLE_REPEAT,
		MIDDLE_UP,
	};
	
	enum {
		EVENT_INVALID,
		EVENT_SHUTDOWN,
	};*/

};

#endif


NAMESPACE_TOPSIDE_END

#endif
