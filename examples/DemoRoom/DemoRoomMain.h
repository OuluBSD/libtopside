#pragma once


NAMESPACE_OULU_BEGIN

class Engine;



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
    One<Machine>				machine;

    // Cached pointer to device resources.
    DeviceResources				dev_res;
    Pbr::Resources				pbr_res;

    // Render loop timer.
    StepTimer					timer;
    
    
};


NAMESPACE_OULU_END

