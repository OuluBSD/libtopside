#include "EcsVirtualGui.h"

NAMESPACE_ECS_BEGIN





VirtualGui*				__current_VirtualGui;



VirtualGui::VirtualGui(VirtualGuiSystem* sys) : sys(sys) {
	__current_VirtualGui = this;
	title = "Unnamed";
	
}

VirtualGui::~VirtualGui() {
	
}

void VirtualGui::Clear() {
	
}

void VirtualGui::RecvAudio(byte* stream, int len) {
	TODO
	
}

VirtualGui* VirtualGui::Current() {
	return __current_VirtualGui;
}

bool VirtualGui::Open() {
	ASSERT(!VirtualGui3DPtr);
	VirtualGui3DPtr = this;
	
	Engine& eng = sys->GetEngine();
	Serial::EntitySystem& esys = eng.GetEntitySystem();
	Machine& mach = esys.GetMachine();
	
	rend = eng.Get<Ecs::RenderingSystem>();
	if (!rend) {
		LOG("VirtualGui::Open: error: could not find RenderingSystem");
		return false;
	}
	
	title = "VirtualGui";
	screen_sz = Size(TS::default_width, TS::default_height);
	
	
	return true;
}

void VirtualGui::Close() {
	
}


bool VirtualGui::Poll(UPP::CtrlEvent& e) {
	TODO
}
Size VirtualGui::GetSize() {
	return screen_sz;
}

void VirtualGui::SetTitle(String title) {
	this->title = title;
}

SystemDraw& VirtualGui::BeginDraw() {
	TODO
}

void VirtualGui::CommitDraw() {
	TODO
}

uint32 VirtualGui::GetTickCount() {
	TODO
}

void VirtualGui::WaitEvent(int ms) {
	TODO
}

bool VirtualGui::IsWaitingEvent() {
	TODO
}

void VirtualGui::WakeUpGuiThread() {
	TODO
}




NAMESPACE_ECS_END
