#include "AudioShaderEditor.h"


NAMESPACE_OULU_BEGIN


AudioShaderEditor::AudioShaderEditor() {
	//CtrlLayout(*this, "AudioShaderEditor");
	MaximizeBox().Sizeable();
	Title("AudioShaderEditor");
	
	tc.Set(-1, THISBACK(MachineUpdater));
	
	Add(tabs.SizePos());
	
	tabs.Add<Editor>("Editor");
	tabs.Add<EntityCtrl>("Entities");
	tabs.Add<InterfaceSystemCtrl>("Interfaces");
	tabs.Add<InterfaceConnectionCtrl>("Connections");
	
	data_tc.Set(-500, callback(this, &Ctrl::Update));
	
	
}

bool AudioShaderEditor::InitializeDefault(String audio_path) {
	if (1) {
		Machine& m = GetMachine();
		Ref<EntityStore> es = m.Get<EntityStore>();
		
		EntityRef reader = es->CreateEmpty();
		reader->SetPrefab("Manual debug sound input");
		reader->Add<Connector>(); // for automatic unlinking
		SoundGeneratorComponent* sg = reader->Add<SoundGeneratorComponent>();
		sg->SetPreset(0);
		
		EntityRef output = es->CreateEmpty();
		output->SetPrefab("Manual Sound output");
		output->Add<Connector>(); // for automatic unlinking
		PortaudioSinkComponent* audio_out = output->Add<PortaudioSinkComponent>();
		
		sg->AsAudioSource()->LinkManually(*audio_out->AsAudioSink());
	}
	else if (1) {
		if (audio_path.IsEmpty()) {
			LOG("Give a audio file path as an argument");
			return false;
		}
		Machine& m = GetMachine();
		Ref<EntityStore> es = m.Get<EntityStore>();
		
		EntityRef reader = es->CreateEmpty();
		reader->SetPrefab("Manual MP3 input");
		reader->Add<Connector>(); // for automatic unlinking
		MultiMediaComponent* mm = reader->Add<MultiMediaComponent>();
		if (!mm->LoadFileAny(audio_path)) {
			LOG("could not open input: " + audio_path);
			return false;
		}
		
		EntityRef output = es->CreateEmpty();
		output->SetPrefab("Manual Sound output");
		output->Add<Connector>(); // for automatic unlinking
		PortaudioSinkComponent* audio_out = output->Add<PortaudioSinkComponent>();
		
		mm->AsMediaSource()->LinkManually(*audio_out->AsMediaSink());
	}
	else {
		Machine& m = GetMachine();
		Ref<EntityStore> es = m.Get<EntityStore>();
		Ref<FluidsynthSystem> fs_sys = m.Get<FluidsynthSystem>();
			
		String file_path = GetDataFile("test.mid");
		
		auto file = es->Create<MidiFileController>();
		MidiFileComponent* midi = file->Find<MidiFileComponent>();
		ASSERT(midi);
		if (!midi->OpenFilePath(file_path)) {
			LOG("error: " << midi->GetLastError());
			GetMachine().SetNotRunning();
			return false;
		}
		
		
		for(int i = 0; i < 16; i++) {
			auto synth = es->Create<CompleteFluidsynth>();
			FluidsynthComponent* fs = synth->Find<FluidsynthComponent>();
			ASSERT(fs);
			fs->OpenTrackListener(i);
			midi->LinkManually(*fs);
		}
	}
	return true;
}

void AudioShaderEditor::OnError() {
	GetMachine().SetNotRunning();
}

void AudioShaderEditor::MachineUpdater() {
	GetMachine().Update(ResetSeconds(ts));
}

void AudioShaderEditor::Updated() {
	tabs.Updated();
}


NAMESPACE_OULU_END

