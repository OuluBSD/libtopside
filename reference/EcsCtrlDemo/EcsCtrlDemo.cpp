#include "EcsCtrlDemo.h"


NAMESPACE_TOPSIDE_BEGIN


EcsCtrlDemo::EcsCtrlDemo(Machine& mach) : mach(mach) {
	MaximizeBox().Sizeable();
	Title("EcsCtrlDemo");
	
	tc.Set(-1, THISBACK(MachineUpdater));
	
	Add(tabs.SizePos());
	
	tabs.Add<EntityCtrl>("Entities").SetMachine(mach);
	tabs.Add<InterfaceSystemCtrl>("Interfaces").SetMachine(mach);
	tabs.Add<InterfaceConnectionCtrl>("Connections").SetMachine(mach);
	
	data_tc.Set(-500, callback(this, &Ctrl::Update));
	
}

bool EcsCtrlDemo::InitializeDefault() {
	PoolRef p = GetPool();
	p->Add<ConnectAllInterfaces<AudioSource>>();
	
	EntityRef reader = p->CreateEmpty();
	reader->SetPrefab("Manual debug sound input");
	SoundGeneratorComponentRef sg = reader->Add<SoundGeneratorComponent>();
	sg->SetPreset(0);
	
	EntityRef output = p->CreateEmpty();
	output->SetPrefab("Manual Sound output");
	PortaudioSinkComponentRef audio_out = output->Add<PortaudioSinkComponent>();
	
	return true;
}

void EcsCtrlDemo::OnError() {
	mach.SetNotRunning();
}

void EcsCtrlDemo::MachineUpdater() {
	mach.Update(ResetSeconds(ts));
}

void EcsCtrlDemo::Updated() {
	tabs.Updated();
}


NAMESPACE_TOPSIDE_END

