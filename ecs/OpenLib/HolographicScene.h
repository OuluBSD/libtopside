#ifndef _OpenLib_HolographicScene_h_
#define _OpenLib_HolographicScene_h_

NAMESPACE_TOPSIDE_BEGIN

class HolographicScene :
	public System<HolographicScene>
{
	
public:
	SYS_CTOR(HolographicScene);
	void Visit(RuntimeVisitor& vis) override {}
    
    
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
    const SpatialCoordinateSystem&		WorldCoordinateSystem() const;
    PerceptionTimestamp					CurrentTimestamp() const;
    
};


NAMESPACE_TOPSIDE_END

#endif
