#ifndef _SDL2GUI3DAlt_SDL2GUI3DAlt_h_
#define _SDL2GUI3DAlt_SDL2GUI3DAlt_h_

#include <OOSDL2/OOSDL2.h>


NAMESPACE_UPP


class SDL2GUI3DAlt;


class SDL2GUI3DAlt : VirtualGui3DAlt
{
	
	
protected:
	friend class SDL2GUI3DAltSystem;
	//SDL2GUI3DAlt_MachineData* data = 0;
	
	Oulu::OOSDL2::AudioOutput* aout = 0;
	Oulu::OOSDL2::Screen* scr = 0;
	Oulu::OOSDL2::Events* ev = 0;
	
	SystemAudio					empty_aud;
	SystemDraw					empty_draw;
	String						desired_title;
	void*						sys;
	
	
public:
	bool            Poll(Upp::CtrlEvent& e) override {return ev ? ev->Poll(e) : false;}
	Size            GetSize() override {return scr ? scr->GetSize() : Size(0,0);}
	void            SetTitle(String title) override {desired_title = title; if (scr) scr->SetTitle(title);}
	SystemDraw&     BeginDraw() override {return scr ? scr->BeginDraw() : empty_draw;}
	void            CommitDraw() override {if (scr) scr->CommitDraw();}
	uint32          GetTickCount() override {return ev ? ev->GetTickCount() : 0;}
	void            WaitEvent(int ms) override {if (ev) ev->WaitEvent(ms);}
	bool            IsWaitingEvent() override {return ev ? ev->IsWaitingEvent() : false;}
	void            WakeUpGuiThread() override {if (ev) ev->WakeUpEventThread();}
	
	/*dword           GetMouseButtons() override;
	dword           GetModKeys() override;
	bool            IsMouseIn() override;
	void            SetMouseCursor(const Image& image) override;
	void            Quit() override {Close();}*/

	
	
	
	bool			Open();
	void			Close();
	//bool			IsOpen() const {return is_open;}
	//SDL2GUI3DAlt_MachineData* GetData() {return data;}
	void			RecvAudio(Uint8* stream, int len);
	
	
	//bool			InitMachine();
	//bool			DeinitMachine();
	//void			Render(bool do_render);
	//void			RenderFrame();
	//void			RenderCamera();
	//void			RenderWindows();
	
	SDL2GUI3DAlt(void* sys);
	~SDL2GUI3DAlt();
	
	static SDL2GUI3DAlt* Current();
	
};


bool Open_SDL2GUI3DAlt_ECS(bool gui);
void Close_SDL2GUI3DAlt_ECS();

END_UPP_NAMESPACE

#if defined(flagWIN32)
	#define GUI_APP_MAIN_(gui) \
	void GuiMainFn_(); \
	\
	int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, int show) {\
		::SetWin32Instances(hinst, hprev, show); \
		char chr[512]; GetModuleFileNameA(NULL, chr, 512); \
		::UPP::AppInit__(0, (const char **)cmdline); \
		if (Open_SDL2GUI3DAlt_ECS(gui)) { \
			GuiMainFn_(); \
			Close_SDL2GUI3DAlt_ECS(); \
		} \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#else
	#define GUI_APP_MAIN_(gui) \
	void GuiMainFn_(); \
	\
	extern "C" int main(int argc, char *argv[]) {\
		::UPP::AppInit__(argc, (const char **)argv); \
		if (Open_SDL2GUI3DAlt_ECS(gui)) { \
			GuiMainFn_(); \
			Close_SDL2GUI3DAlt_ECS(); \
		} \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#endif

#define GUI_APP_MAIN			GUI_APP_MAIN_(true)
#define RENDER_APP_MAIN			GUI_APP_MAIN_(false)


#endif
