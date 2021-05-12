#pragma once


NAMESPACE_OULU_BEGIN

class Engine;

NAMESPACE_OULU_END


// Updates, renders, and presents holographic content using Direct3D.
NAMESPACE_OULU_BEGIN


class DemoRoomMain {
	
public:
    DemoRoomMain();
    ~DemoRoomMain();

    // Sets the holographic space. This is our closest analogue to setting a new window
    // for the app.
    void SetHolographicSpace(HolographicSpace const& holospace);

    // Starts the holographic frame and updates the content.
    void Update();

    // Handle saving and loading of app state owned by AppMain.
    void SaveAppState();
    void LoadAppState();

private:
    std::unique_ptr<Neso::Engine>		machine;

    // Cached pointer to device resources.
    SharedDeviceResources				dev_res;

    // Render loop timer.
    StopTimer							timer;
};


NAMESPACE_OULU_END

