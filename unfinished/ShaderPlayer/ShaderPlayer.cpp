#include "ShaderPlayer.h"

NAMESPACE_TOPSIDE_BEGIN

String multistage_arg;


void ShaderPlayer::OnError() {
	GetMachine().SetNotRunning();
}

void ShaderPlayer::Initialize() {
	PoolRef root = GetEntity()->GetMachine().Get<EntityStore>()->GetRoot();
	root->AddConnectEverythingWithAccel();
	
	root->Create<CenterStreamScope>();
	
	PoolRef pool = root->GetAddPool("accel");
	accel = pool->Create<AccelStreamScope>();
	ASSERT(accel);
	
	ctx = accel->Find<AccelStageContextConnector>();
	if (ctx) {
		ctx->WhenError << THISBACK(OnError);
		if (multistage_arg.GetCount()) {
			ctx->PostLoadFileAny(multistage_arg); // async cmd
		}
		else {
			LOG("error: currently the shadertoy directory is required as program argument");
			GetMachine().SetNotRunning();
			return;
		}
	}
}

void ShaderPlayer::Uninitialize() {
	ASSERT(!accel)
	//accel->Destroy();
	//accel.Clear();
}

void ShaderPlayerInitializer() {
	SetCoutLog();
	
	//StructuralTests();
	
	CommandLineArguments cmd;
	cmd.AddArg('d', "The directory for the toy shader", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'd') multistage_arg = in.value;
	}
	if (multistage_arg.IsEmpty()) {
		cmd.PrintHelp();
		return;
	}
	
	//EntityRef snd_in = GetMachine().Get<EntityStore>()->Create<StandaloneLineIn>();
	//snd_in->Find<Connector>()->ConnectAll();
	
}


NAMESPACE_TOPSIDE_END

RENDER_APP_(TS::ShaderPlayer)
APP_INITIALIZE_(TS::ShaderPlayerInitializer);
APP_DEFAULT_GFX_(GFX_OPENGL);

