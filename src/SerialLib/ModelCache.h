#ifndef _SerialLib_ModelCache_h_
#define _SerialLib_ModelCache_h_

NAMESPACE_TOPSIDE_BEGIN
using namespace Serial;

class ModelCache :
	public Parallel::System<ModelCache>
{
	
protected:
	//CalibrationData				calib;
	ArrayMap<String, ModelLoader> model_cache;
	double time = 0;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	using Base = System<ModelCache>;
	RTTI_DECL1(ModelCache, Base)
    SYS_CTOR(ModelCache)
	SYS_DEF_VISIT
	
	ModelRef GetAddModelFile(String path);
	
	//void CalibrationEvent(CtrlEvent& ev);
	
};

using ModelCacheRef = Ref<ModelCache>;

NAMESPACE_TOPSIDE_END

#endif
