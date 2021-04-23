#include "OrchestraConductor.h"

NAMESPACE_OULU_BEGIN

String file_path;
bool use_fluidsynth;


void OrchestraConductor::OnError() {
	GetMachine().SetNotRunning();
}

void OrchestraConductor::Initialize() {
	Machine& m = GetEntity().GetMachine();
	Ref<EntityStore> es = m.Get<EntityStore>();
	auto fusion = es->Create<CompleteFusion>();
	bool use_midi_file = file_path.GetCount();
	
	if (use_fluidsynth) {
		Ref<FluidsynthSystem> fs_sys = m.Get<FluidsynthSystem>();
		
		if (use_midi_file) {
			auto file		= es->Create<MidiFileController>();
			MidiFileComponent* midi = file->Find<MidiFileComponent>();
			ASSERT(midi);
			if (!midi->OpenFilePath(file_path)) {
				LOG("error: " << midi->GetLastError());
				GetMachine().SetNotRunning();
				return;
			}
			
			
			for(int i = 0; i < 16; i++) {
				auto synth		= es->Create<CompleteFluidsynth>();
				FluidsynthComponent* fs = synth->Find<FluidsynthComponent>();
				ASSERT(fs);
				fs->OpenTrackListener(i);
				midi->LinkManually(*fs);
			}
			
		}
		else {
			auto vocalist	= es->Create<CompleteMusicVocalist>();
			auto guitarist	= es->Create<CompleteMusicGuitarist>();
			auto bassist	= es->Create<CompleteMusicBassist>();
		}
	}
	else {
		auto audio		= es->Create<CompleteMixer>();
		auto output		= es->Create<CompleteMixerOutput>();
		
		auto conductor	= es->Create<CompleteMusicConductor>();
		auto composer	= es->Create<CompleteMusicComposer>();
		
		//auto vocalist		= es->Create<CompleteMusicVocalist>();
		//auto guitarist	= es->Create<CompleteMusicGuitarist>();
		//auto bassist		= es->Create<CompleteMusicBassist>();
		auto drummer	= es->Create<CompleteMusicDrummer>();
		
		auto v_channel	= es->Create<CompleteMixerChannel>();
		auto g_channel	= es->Create<CompleteMixerChannel>();
		auto b_channel	= es->Create<CompleteMixerChannel>();
		auto d_channel	= es->Create<CompleteMixerChannel>();
		
		
		String style_string = "pop,funk,punk,rock,rap,sad,energizing";
		
		conductor->Find<MusicConductorComponent>()->EvaluateRequest(style_string);
		composer->Find<MusicComposerComponent>()->EvaluateRequest(style_string);
		/*vocalist->Find<MusicComposerComponent>()->EvaluateRequest(style_string);
		guitarist->Find<MusicComposerComponent>()->EvaluateRequest(style_string);
		bassist->Find<MusicComposerComponent>()->EvaluateRequest(style_string);*/
		drummer->Find<MusicComposerComponent>()->EvaluateRequest(style_string);
	}
}

void OrchestraConductor::Uninitialize() {
	
}

void OrchestraConductorStartup() {
	SetCoutLog();
	
	
	String html = LoadFile(GetDataFile("UI.html"));
	HtmlParser p;
	if(!p.Parse(html))
		Exit(1);
	
	
	CommandLineArguments cmd;
	cmd.AddArg('t', "Use timidity as sound output", false);
	cmd.AddArg('f', "The path for the music file", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		GetMachine().SetNotRunning();
		return;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'f')
			file_path = in.value;
		if (in.key == 't')
			use_fluidsynth = true;
	}
	
	if (file_path.GetCount() && !use_fluidsynth) {
		cmd.PrintHelp();
		LOG("Playing midi file internally is currently unsupported.");
		GetMachine().SetNotRunning();
		return;
	}
	
	Machine& m = GetMachine();
	m.Add<FluidsynthSystem>();
	
}


NAMESPACE_OULU_END

CONSOLE_ECS_APP_(Oulu::OrchestraConductor)
APP_STARTUP_(Oulu::OrchestraConductorStartup);
APP_DEFAULT_GFX_(GFX_OPENGL);

