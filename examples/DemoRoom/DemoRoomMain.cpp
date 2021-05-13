#include "DemoRoom.h"


NAMESPACE_OULU_BEGIN


// Loads and initializes application assets when the application is loaded.
DemoRoomMain::DemoRoomMain() {
	
}

void DemoRoomMain::SetHolographicSpace(const HolographicSpace& holospace)
{
    if (machine && machine->HasStarted()) {
        machine->Stop();
        machine.Clear();
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
    machine.Create();

    machine->Add<EntityStore>();
    machine->Add<ComponentStore>();
    machine->Add<HolographicScene>();//->SetResources(holospace);
    machine->Add<EasingSystem>();
    machine->Add<PhysicsSystem>();
    machine->Add<PbrModelCache>();//->SetResources(pbr_res);

    machine->Add<SpatialInteractionSystem>();
    machine->Add<MotionControllerSystem>();
    machine->Add<WorldLogicSystem>();

    machine->Add<ToolboxSystem>();
    machine->Add<ShootingInteractionSystem>();
    machine->Add<PaintingInteractionSystem>();
    machine->Add<ThrowingInteractionSystem>();

    machine->Add<PaintStrokeSystem>();//->SetResources(pbr_res);
    machine->Add<HolographicRenderer>();//->SetResources(dev_res, pbr_res, skyboxTexture.Get());

    machine->Start();

    // Seed model cache
    auto pbr_model_cache = machine->Get<PbrModelCache>();

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
        auto pbr_model_cache = machine->Get<PbrModelCache>();
        auto pbr_res = machine->Get<HolographicRenderer>()->GetPbrResources();

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
    machine->Get<EntityStore>()->GetRoot()->GetAddPool("models")->Create<FloorPrefab>();

    // Reset timer on startup so the first update's delta time is sensible (albeit still small)
    timer.ResetElapsedTime();
}

DemoRoomMain::~DemoRoomMain()
{
    if (machine)
    {
        machine->Stop();
        machine.Clear();
    }
}

// Updates the application state once per frame.
void DemoRoomMain::Update()
{
    timer.Tick(THISBACK(ProcessUpdate));
}

void DemoRoomMain::ProcessUpdate() {
	machine->Update(static_cast<float>(timer.GetElapsedSeconds()));
}

void DemoRoomMain::SaveAppState()
{
    dev_res.Trim();

    if (machine) {
        machine->Suspend();
    }
}

void DemoRoomMain::LoadAppState()
{
    if (machine) {
        machine->Resume();
    }
}


NAMESPACE_OULU_END
