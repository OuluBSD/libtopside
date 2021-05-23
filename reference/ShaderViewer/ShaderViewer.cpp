#include "ShaderViewer.h"

NAMESPACE_TOPSIDE_BEGIN

String multistage_arg;


void ShaderViewer::OnError() {
	GetMachine().SetNotRunning();
}

void ShaderViewer::Initialize() {
	PoolRef pool = GetEntity()->GetMachine().Get<EntityStore>()->GetRoot()->GetAddPool("fusion");
	//fusion = pool->Create<CompleteFusion>();
	fusion = pool->Create<VideoOnlyFusion>();
	ASSERT(fusion);
	pool->Add<ConnectAllInterfaces<AudioSource>>();
	pool->Add<ConnectAllInterfaces<DisplaySource>>();
	pool->Add<ConnectAllInterfaces<AcceleratorSource>>();
	pool->Add<ConnectAllInterfaces<StaticSource>>();
	
	ctx = fusion->Find<FusionContextComponent>();
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

void ShaderViewer::Uninitialize() {
	ASSERT(!fusion)
	//fusion->Destroy();
	//fusion.Clear();
}

void ShaderViewerInitializer() {
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

RENDER_APP_(Topside::ShaderViewer)
APP_INITIALIZE_(Topside::ShaderViewerInitializer);
APP_DEFAULT_GFX_(GFX_OPENGL);

