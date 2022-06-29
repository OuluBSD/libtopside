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
	
	ASSERT(!e.TryGet<RenderingSystem>());
    e.GetAdd<EntityStore>();
    e.GetAdd<ComponentStore>();
    e.GetAdd<HolographicScene>();//->SetResources(holospace);
    e.GetAdd<EasingSystem>();
    e.GetAdd<PhysicsSystem>();
    e.GetAdd<PbrModelCache>();//->SetResources(pbr_res);
	
    e.GetAdd<SpatialInteractionSystem>();
    e.GetAdd<MotionControllerSystem>();
    e.GetAdd<WorldLogicSystem>();
	
    e.GetAdd<ToolboxSystem>();
    e.GetAdd<ShootingInteractionSystem>();
    e.GetAdd<PaintingInteractionSystem>();
    e.GetAdd<ThrowingInteractionSystem>();
	
    e.GetAdd<PaintStrokeSystem>();//->SetResources(pbr_res);
    e.GetAdd<HolographicRenderingSystem>();//->SetResources(dev_res, pbr_res, skyboxTexture.Get());
	
}

void DemoRoomStartup() {
	using namespace Ecs;
	
	Ecs::Engine& e = GetActiveEngine();
	HolographicRenderingSystemRef rs = e.Get<HolographicRenderingSystem>();
	Pbr::Resources& pbr_res = rs->GetScope().pbr_res;
	
    // Seed model cache
    auto pbr_model_cache = e.Get<PbrModelCache>();
    
    // Register a low poly sphere model.
    {
        Pbr::Model& sphere_model = pbr_model_cache->AddModel(KnownModelNames::UnitSphere);
        Pbr::Primitive& sphere_prim = sphere_model.AddPrimitive();
        Pbr::Material& mat = pbr_res.AddMaterial();
        sphere_prim.SetMaterial(mat);
        mat.SetFlat(Colors::White, 0.15f);
        Pbr::PrimitiveBuilder().CreateSphere(sphere_prim, 1.0f, 3);
    }

    // Register a cube model.
    {
        Pbr::Model& cube_model = pbr_model_cache->AddModel(KnownModelNames::UnitCube);
        Pbr::Primitive& cube_prim = cube_model.AddPrimitive();
        Pbr::Material& mat = pbr_res.AddMaterial();
        cube_prim.SetMaterial(mat);
        mat.SetFlat(Colors::White, 0.15f);
        Pbr::PrimitiveBuilder().CreateCube(cube_prim, 1.0f);
    }

    // Register glb models.
    auto load_glb_models = [&](
        String path,
        String name,
        Optional<mat4> transform = NullOpt(),
        Optional<vec4> color = NullOpt())
    {
        path = ShareDirFile(path);
        
        auto pbr_model_cache = e.Get<PbrModelCache>();
        //auto pbr_res = e.Get<HolographicRenderer>()->GetPbrResources();

        String file_data = LoadFile(path);
        if (file_data.IsEmpty()) {
            LOG("DemoRoomStartup: error: model file does not exist: " << path);
            Exit(1);
        }

        const mat4 model_transform = transform.has_value()
            ? transform.value()
            : Identity<mat4>();

        Pbr::Model& pbr_model = pbr_model_cache->AddModel(name);
        Gltf::FromGltfBinary(
            pbr_model,
            pbr_res,
            file_data.Begin(),
            file_data.GetCount(),
            model_transform);

        if (color) {
            for (uint32 i = 0; i < pbr_model.GetPrimitiveCount(); ++i) {
                pbr_model.GetPrimitive(i).GetMaterial().parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
                    data.base_clr_factor = color.value();
                });
            }
        }

        LOG("Loaded Model: " << name);
    };

    mat4 baseball_scale;
    baseball_scale = scale(vec3(0.15f, 0.15f, 0.15f));
    load_glb_models("models/ms/Baseball.glb", KnownModelNames::Baseball, baseball_scale, vec4{ 2.0f, 2.0f, 2.0f, 1.0f });

    mat4 gun_scale;
    gun_scale = scale(vec3(0.35f, 0.35f, 0.35f));
    load_glb_models("models/ms/Gun.glb", KnownModelNames::Gun, gun_scale);

    load_glb_models("models/ms/PaintBrush.glb", KnownModelNames::PaintBrush);
	
	
	
    // We don't store the returned Floor Entity locally, so it lives foreeevvverrr
    e.Get<EntityStore>()->GetRoot()->GetAddPool("models")->Create<FloorPrefab>();
    
}







NAMESPACE_TOPSIDE_END






DEFAULT_ECS_SHELL_EON("DemoRoom", "demo_room.eon")
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
