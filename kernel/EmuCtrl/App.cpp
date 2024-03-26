#include "EmuCtrl.h"


EmuApp::EmuApp() : scr(*this) {
	Title("LittleKernel emulator");
	Add(scr.SizePos());
	
	SetRect(scr.GetPreferredSize());
	
	WhenClose << THISBACK(OnClose);
}

EmuApp::~EmuApp() {
	Stop();
}

void EmuApp::OnClose() {
	Thread::ShutdownThreads();
}

void EmuApp::Init() {
	ASSERT(global);
	Monitor& mon = global->monitor;
	
	mon.SetTarget(scr.vscr);
}

void EmuApp::Data() {
	Monitor& mon = global->monitor;
	
	
	
}

void EmuApp::Start() {
	running = 1;
	stopped = 0;
	
	Thread::Start(THISBACK(EmuProcess));
	Sleep(100); // give some time for booting
	
	TopWindow::Run();
	
	running = 0;
	while (!stopped) Sleep(1);
}

void EmuApp::EmuProcess() {
	multiboot mboot;
	
	mboot.OnMonitorCreate << THISBACK(Init);
	
	int ret = multiboot_main(&mboot);
	
	stopped = 1;
	running = 0;
}

void EmuApp::RefreshOutput() {
	Refresh();
}




EmuScreen::EmuScreen(EmuApp& a) : app(a) {
	int grid_w = 14;
	grid = Size(grid_w, grid_w*4/3);
	
	int cols = 80;
	int expected_w = cols * grid_w;
	int expected_h = expected_w * 3 / 4;
	int rows = expected_h / grid.cy;
	
	bg = Black();
	fg = White();
	
	// https://int10h.org/oldschool-pc-fonts/download/
	String preferred_fnt = "AcPlus IBM BIOS-2y";
	
	fnt = Monospace(grid.cy);
	for(int i = 0; i < Font::GetFaceCount(); i++) {
		String face_name = Font::GetFaceName(i);
		if (face_name == preferred_fnt) {
			fnt.SetFace(i, face_name);
			break;
		}
	}
	
	tc.Set(-1000/60, THISBACK(PostRefresh));
}

void EmuScreen::ClearScreen() {
	vscr.Clear();
}

void EmuScreen::NewLine() {
	vscr.NewLine();
}

void EmuScreen::Put(dword d, int count) {
	vscr.Put(d, count);
}
	
void EmuScreen::Paint(Draw& d) {
	Size sz(GetSize());
	d.DrawRect(sz, bg);
	
	if (vscr.mem  && vscr.sz > 0) {
		ASSERT(vscr.stride == 1);
		byte* it = vscr.mem;
		int gy = 0;
		for (int y = 0; y < vscr.height; y++) {
			int gx = 0;
			for (int x = 0; x < vscr.width; x++) {
				byte w = *it++;
				if (w > 0) {
					char txt[2];
					txt[0] = w;
					txt[1] = 0;
					d.DrawText(gx, gy, txt, fnt, fg);
				}
				gx += grid.cx;
			}
			gy += grid.cy;
		}
	}
}

Size EmuScreen::GetPreferredSize() const {
	return Size(
		vscr.width * grid.cx,
		vscr.height * grid.cy);
}

int __emu_kb_char_queue[KB_QUEUE_LENGTH];

bool EmuScreen::Key(dword key, int count) {
	if (key & K_KEYUP || key & K_DELTA) {
		
	}
	else {
		String desc = GetKeyDesc(key);
		int chr = desc.GetCount() == 1 ? desc[0] : 0;
		if (chr && chr >= 0x20 && chr < 0x80) {
			//Put(chr);
			for(int i = 0; i < KB_QUEUE_LENGTH; i++) {
				int& e = __emu_kb_char_queue[i];
				if (e == 0) {
					e = chr;
					break;
				}
			}
			Registers r;
			memset(&r, 0, sizeof(r));
			r.int_no = IRQ1;
			r.eax = chr;
			isr_handler(r);
			return true;
		}
	}
	
	return false;
}
