#include "ShaderViewer.h"

NAMESPACE_OULU_BEGIN

String multistage_arg;


void ShaderViewer::OnError() {
	GetMachine().SetNotRunning();
}

void ShaderViewer::Initialize() {
	TODO
	/*fusion = GetEntity().GetMachine().Get<EntityStore>()->Create<CompleteFusion>();
	fusion->Find<Connector>()->ConnectAll();
	
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
	}*/
}

void ShaderViewer::Uninitialize() {
	fusion->Destroy();
	fusion.Clear();
}

void ShaderViewerStartup() {
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


NAMESPACE_OULU_END

RENDER_APP_(Oulu::ShaderViewer)
APP_STARTUP_(Oulu::ShaderViewerStartup);
APP_DEFAULT_GFX_(GFX_OPENGL);

