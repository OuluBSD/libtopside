#pragma once


NAMESPACE_TOPSIDE_BEGIN




class DemoRoomMain {
	
public:
	typedef DemoRoomMain CLASSNAME;
    DemoRoomMain();
    
    // Sets the holographic space. This is our closest analogue to setting a new window
    // for the app.
    void SetHolographicSpace(const HolographicSpace& holospace);
    
private:

    // Cached pointer to device resources.
    DeviceResources				dev_res;
    Pbr::Resources				pbr_res;

    // Render loop timer.
    StepTimer					timer;
    
    
};


NAMESPACE_TOPSIDE_END

