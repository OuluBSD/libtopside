#pragma once


NAMESPACE_TOPSIDE_BEGIN




class DemoRoomMain {
	
public:
	typedef DemoRoomMain CLASSNAME;
    DemoRoomMain();
    ~DemoRoomMain();

    // Sets the holographic space. This is our closest analogue to setting a new window
    // for the app.
    void SetHolographicSpace(const HolographicSpace& holospace);

    // Starts the holographic frame and updates the content.
    void Update();
    void ProcessUpdate();

    // Handle saving and loading of app state owned by AppMain.
    void SaveAppState();
    void LoadAppState();

private:
    One<Ecs::Engine>			engine;

    // Cached pointer to device resources.
    DeviceResources				dev_res;
    Pbr::Resources				pbr_res;

    // Render loop timer.
    StepTimer					timer;
    
    
};


NAMESPACE_TOPSIDE_END

