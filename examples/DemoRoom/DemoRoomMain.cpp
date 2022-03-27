#include "DemoRoom.h"


NAMESPACE_TOPSIDE_BEGIN


// Loads and initializes application assets when the application is loaded.
DemoRoomMain::DemoRoomMain() {
	
}

void DemoRoomMain::SetHolographicSpace(const HolographicSpace& holospace)
{
	using namespace Ecs;
	
    if (engine && engine->HasStarted()) {
        engine->Stop();
        engine.Clear();
    }

    if (!holospace) {
        return;
    }
	
    
	#ifdef flagUWP
    LoadDefaultResources(
		dev_res,
		holospace,
		"ms-appx:///Media/Environment/DiffuseHDR.dds",
		"ms-appx:///Media/Environment/SpecularHDR.dds",
		"ms-appx:///Media/Environment/EnvHDR.dds",
		"ms-appx:///PBR/brdf_lut.png");
	#endif
	
	
    // System::Update is called in the order they were added to the Engine
    // Which is why we put the factories at the start, and the rendering at the end.
    engine.Create();

    engine->Add<EntityStore>();
    engine->Add<ComponentStore>();
    engine->Add<HolographicScene>();//->SetResources(holospace);
    engine->Add<EasingSystem>();
    engine->Add<PhysicsSystem>();
    engine->Add<PbrModelCache>();//->SetResources(pbr_res);

    engine->Add<SpatialInteractionSystem>();
    engine->Add<MotionControllerSystem>();
    engine->Add<WorldLogicSystem>();

    engine->Add<ToolboxSystem>();
    engine->Add<ShootingInteractionSystem>();
    engine->Add<PaintingInteractionSystem>();
    engine->Add<ThrowingInteractionSystem>();

    engine->Add<PaintStrokeSystem>();//->SetResources(pbr_res);
    engine->Add<HolographicRenderer>();//->SetResources(dev_res, pbr_res, skyboxTexture.Get());

    engine->Start();

    // Seed model cache
    auto pbr_model_cache = engine->Get<PbrModelCache>();

	TODO
	#if 0
    // Register a low poly sphere model.
    {
        Pbr::Primitive sphere_prim(
            *pbr_res,
            Pbr::PrimitiveBuilder().AddSphere(1.0f, 3),
            Pbr::Material::CreateFlat(*pbr_res, Colors::White, 0.15f));

        // Add the primitive into a new model.
        auto sphereModel = std::make_shared<Pbr::Model>();
        sphereModel->AddPrimitive(std::move(sphere_prim));
        pbr_model_cache->RegisterModel(KnownModelNames::UnitSphere, std::move(sphereModel));
    }

    // Register a cube model.
    {
        // Load the primitive into D3D buffers with associated material
        Pbr::Primitive cube_prim(
            *pbr_res, 
            Pbr::PrimitiveBuilder().AddCube(1.0f), 
            Pbr::Material::CreateFlat(*pbr_res, Colors::White, 0.15f));

        // Add the primitive into a new model.
        auto cubeModel = std::make_shared<Pbr::Model>();
        cubeModel->AddPrimitive(std::move(cube_prim));
        pbr_model_cache->RegisterModel(KnownModelNames::UnitCube, std::move(cubeModel));
    }

    // Register glb models.
    auto loadGLBModels = [this](
        String path,
        String name,
        std::optional<DirectX::XMFLOAT4X4> transform = std::nullopt,
        std::optional<DirectX::XMFLOAT4> color = std::nullopt) -> std::future<void>
    {
        auto pbr_model_cache = engine->Get<PbrModelCache>();
        auto pbr_res = engine->Get<HolographicRenderer>()->GetPbrResources();

        std::vector<byte> fileData = co_await DX::ReadDataAsync(std::wstring(path));

        const DirectX::XMMATRIX modelTransform = transform.has_value()
            ? DirectX::XMLoadFloat4x4(&transform.value())
            : DirectX::XMMatrixIdentity();

        Shared<Pbr::Model> pbr_model = Gltf::FromGltfBinary(
            *pbr_res,
            fileData.data(),
            (uint32_t)fileData.size(),
            modelTransform);

        if (color) {
            for (uint32_t i = 0; i < pbr_model->GetPrimitiveCount(); ++i) {
                pbr_model->GetPrimitive(i).GetMaterial()->Parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
                    data.BaseColorFactor = color.value();
                });
            }
        }

        debug_log("Loaded Model: %s", name.data());

        pbr_model_cache->RegisterModel(name, std::move(pbr_model));
    };

    DirectX::XMFLOAT4X4 baseballScale;
    DirectX::XMStoreFloat4x4(&baseballScale, DirectX::XMMatrixScaling(0.15f, 0.15f, 0.15f));
    loadGLBModels(L"ms-appx:///Media/Models/Baseball.glb", KnownModelNames::Baseball, baseballScale, DirectX::XMFLOAT4{ 2.0f, 2.0f, 2.0f, 1.0f });

    DirectX::XMFLOAT4X4 gunScale;
    DirectX::XMStoreFloat4x4(&gunScale, DirectX::XMMatrixScaling(0.35f, 0.35f, 0.35f));
    loadGLBModels(L"ms-appx:///Media/Models/Gun.glb", KnownModelNames::Gun, gunScale);

    loadGLBModels(L"ms-appx:///Media/Models/PaintBrush.glb", KnownModelNames::PaintBrush);
	#endif
	
	
    // We don't store the returned Floor Entity locally, so it lives foreeevvverrr
    engine->Get<EntityStore>()->GetRoot()->GetAddPool("models")->Create<FloorPrefab>();

    // Reset timer on startup so the first update's delta time is sensible (albeit still small)
    timer.ResetElapsedTime();
}

DemoRoomMain::~DemoRoomMain()
{
    if (engine)
    {
        engine->Stop();
        engine.Clear();
    }
}

// Updates the application state once per frame.
void DemoRoomMain::Update()
{
    timer.Tick(THISBACK(ProcessUpdate));
}

void DemoRoomMain::ProcessUpdate() {
	engine->Update(static_cast<float>(timer.GetElapsedSeconds()));
}

void DemoRoomMain::SaveAppState()
{
    dev_res.Trim();

    if (engine) {
        engine->Suspend();
    }
}

void DemoRoomMain::LoadAppState()
{
    if (engine) {
        engine->Resume();
    }
}















//		DUPLICATE FROM AtomShell PACKAGE


using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, args)
MAKE_STATIC(String, eon_file)


bool Initializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('e', "The path for the eon file", true, "path");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'e') eon_file = in.value;
	}
	if (eon_file.IsEmpty()) {
		cmd.PrintHelp();
		LOG("");
		LOG("\te.g. -e play_audio_file.eon -MACHINE_TIME_LIMIT=3 -FILE=/home/user/some.mp3");
		return false;
	}
	
	args <<= cmd.GetVariables();
	
	return true;
}


size_t break_addr = 0;
bool verify = false;
MAKE_STATIC(Serial::MachineVerifier, verifier);


void SerialInitializer() {
	using namespace Serial;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	
	if (1)
		verify = true;
	
	if (0)
		break_addr = 0x806A81E68;
	
	
	if (!Initializer())
		return;
	
	if (verify) {
		verifier.AddSystem<RegistrySystem>();
		verifier.AddSystem<LoopStore>();
		verifier.AddSystem<AtomStore>();
		verifier.AddSystem<AtomSystem>();
		verifier.AddSystem<ScriptLoader>();
		TODO
		
		auto& ent		= verifier.GetRoot().AddLoop("tester").AddLoop("generator").AddEntity();
		auto& customer	= ent.AddAtomWith<CenterCustomer>	(VD(CENTER,ORDER));
		auto& src		= ent.AddAtomWith<TestRealtimeSrc>	(VD(CENTER,AUDIO));
		auto& sink		= ent.AddAtomWith<TestRealtimeSink>	(VD(CENTER,RECEIPT));
		customer << src << sink << customer;
		src.SetSourceFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		sink.SetSinkFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		
	}
}


void Runner(String app_name) {
	DUMP(eon_file);
	DUMPC(args);
	if (!break_addr)
		Serial::DebugMain(eon_file, args, verify ? &verifier : 0);
	else
		Serial::DebugMain(eon_file, args, verify ? &verifier : 0, 1, break_addr);
}

void Startup() {
	LOG("<-- Startup -->");
}

NAMESPACE_TOPSIDE_END



APP_INITIALIZE_(TS::SerialInitializer)
APP_STARTUP_(TS::Startup)


#ifdef flagGUI
//RENDER_APP_MAIN {TS::Serial::SimpleSerialMain("AtomShell");}
RENDER_APP_MAIN {TS::Runner("AtomShell");}
#else
CONSOLE_APP_MAIN {TS::Runner("AtomShell");}
#endif
