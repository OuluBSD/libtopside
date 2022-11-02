#include "EcsVirtualGui.h"

NAMESPACE_ECS_BEGIN




bool VirtualGuiSystem::Initialize() {
	return gui.Open();
}

void VirtualGuiSystem::Start() {
	
}

void VirtualGuiSystem::Update(double dt) {
	
}

void VirtualGuiSystem::Stop() {
	
}

void VirtualGuiSystem::Uninitialize() {
	gui.Close();
}





NAMESPACE_ECS_END
