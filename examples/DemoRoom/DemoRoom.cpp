#include "DemoRoom.h"


NAMESPACE_TOPSIDE_BEGIN






void DemoRoomInit() {
	using namespace Ecs;
	
	Ecs::Engine& e = GetActiveEngine();
	
	#ifdef flagUWP
	DeviceResources				dev_res;
    Pbr::Resources				pbr_res;
	
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
	
    e.Add<EntityStore>();
    e.Add<ComponentStore>();
    e.Add<HolographicScene>();//->SetResources(holospace);
    e.Add<EasingSystem>();
    e.Add<PhysicsSystem>();
    e.Add<PbrModelCache>();//->SetResources(pbr_res);
	
    e.Add<SpatialInteractionSystem>();
    e.Add<MotionControllerSystem>();
    e.Add<WorldLogicSystem>();
	
    e.Add<ToolboxSystem>();
    e.Add<ShootingInteractionSystem>();
    e.Add<PaintingInteractionSystem>();
    e.Add<ThrowingInteractionSystem>();
	
    e.Add<PaintStrokeSystem>();//->SetResources(pbr_res);
    e.Add<HolographicRenderer>();//->SetResources(dev_res, pbr_res, skyboxTexture.Get());
	
}

void DemoRoomStartup() {
	using namespace Ecs;
	
	Ecs::Engine& e = GetActiveEngine();
	
    // Seed model cache
    auto pbr_model_cache = e.Get<PbrModelCache>();
    
    
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
        auto pbr_model_cache = e.Get<PbrModelCache>();
        auto pbr_res = e.Get<HolographicRenderer>()->GetPbrResources();

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
	
	
	
    // We don't store the returned Floor Entity locally, so it lives foreeevvverrr
    e.Get<EntityStore>()->GetRoot()->GetAddPool("models")->Create<FloorPrefab>();
}







NAMESPACE_TOPSIDE_END






DEFAULT_ECS_SHELL_EON("DemoRoom", "tests/07c_ecs_ogl.eon")
ECS_INITIALIZE_STARTUP__(DemoRoom, DemoRoomInit, DemoRoomStartup)





#if 0


NAMESPACE_TOPSIDE_BEGIN

//		DUPLICATE FROM AtomShell PACKAGE


/*using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, args)
MAKE_STATIC(String, eon_file)*/


bool Initializer() {
	SetCoutLog();
	
	TODO
	/*CommandLineArguments cmd;
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
	
	args <<= cmd.GetVariables();*/
	
	return true;
}


/*size_t break_addr = 0;
bool verify = false;
MAKE_STATIC(Serial::MachineVerifier, verifier);*/


void SerialInitializer() {
	using namespace Serial;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	TODO
	/*if (1)
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
		
	}*/
}


void Runner(String app_name) {
	//DUMP(eon_file);
	//DUMPC(args);
	TODO
	/*if (!break_addr)
		Serial::DebugMain(eon_file, args, verify ? &verifier : 0);
	else
		Serial::DebugMain(eon_file, args, verify ? &verifier : 0, 1, break_addr);*/
}

void Startup() {
	LOG("<-- Startup -->");
}

NAMESPACE_TOPSIDE_END



APP_INITIALIZE_(TS::SerialInitializer)
APP_STARTUP_(TS::Startup)


#ifdef flagGUI
//RENDER_APP_MAIN {TS::Serial::SimpleSerialMain("DemoRoom");}
RENDER_APP_MAIN {TS::Runner("DemoRoom");}
#else
CONSOLE_APP_MAIN {TS::Runner("DemoRoom");}
#endif


#endif
