#include "MP3Player.h"

NAMESPACE_OULU_BEGIN

String file_path;


void MP3Player::OnError() {
	GetMachine().SetNotRunning();
}

void MP3Player::Initialize() {
	fusion = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteFusion>();
	fusion->Find<Connector>()->ConnectAll();
	
	audio = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteMixer>();
	audio->Find<Connector>()->ConnectAll();
	
	track0 = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteMixerTrackBegin>();
	track0->Find<Connector>()->ConnectAll();
	
	channel0 = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteMixerChannel>();
	channel0->Find<Connector>()->ConnectAll();
	
	output = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteMixerOutput>();
	output->Find<Connector>()->ConnectAll();
	
	ctx = e->Find<MixerContextComponent>();
	if (ctx) {
		ctx->WhenError << THISBACK(OnError);
		if (file_path.GetCount()) {
			ctx->PostLoadFileAny(file_path); // async cmd
		}
		else {
			LOG("error: sound file path is required");
			GetMachine().SetNotRunning();
			return;
		}
	}
}

void MP3Player::Uninitialize() {
	e->Destroy();
	e.Clear();
}

void MP3PlayerStartup() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('f', "The path for the music file", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'f') file_path = in.value;
	}
	if (file_path.IsEmpty()) {
		cmd.PrintHelp();
		return;
	}
	
}


NAMESPACE_OULU_END

CONSOLE_ECS_APP_(Oulu::MP3Player)
APP_STARTUP_(Oulu::MP3PlayerStartup);
APP_DEFAULT_GFX_(GFX_OPENGL);

