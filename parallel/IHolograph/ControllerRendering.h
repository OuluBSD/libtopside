#pragma once


NAMESPACE_PBR_BEGIN
struct Model;
struct Resources;
NAMESPACE_PBR_END


NAMESPACE_PARALLEL_BEGIN


// Helper functionality related to controller rendering.
namespace ControllerRendering {

// A controller model can be cached using a key based on the Vendor ID, Product ID, Version, and Handedness.
using ControllerModelKey = std::tuple<uint16, uint16, uint16, SpatialSourceHandedness>;

// Values for articulating a controller, with defaults in the neutral state.
// All floating point values range from 0 to 1.
// For values which represent the X axis, 0 is left, 0.5 is the middle, and 1 is right.
// For values which represent the Y axis, 0 is top, 0.5 is the middle, and 1 is bottom.
struct ArticulateValues
{
    float grasp_press = 0;
    float menu_press = 0;
    float select_press = 0;
    float thumbstick_press = 0;
    float thumbstick_x = 0.5f;
    float thumbstick_y = 0.5f;
    float touchpad_press = 0;
    float touchpad_press_x = 0.5f;
    float touchpad_press_y = 0.5f;
    float touchpad_touch_x = 0.5f;
    float touchpad_touch_y = 0.5f;
    bool touch_indicator_visible = false;
    
};

// Create a key for a given spatial interaction source.
ControllerModelKey GetControllerModelKey(const SpatialSource& source);

// Try to load the renderable model for a given a spatial interaction source.
std::future<Shared<const Pbr::Model>> TryLoadRenderModelAsync(
    Shared<Pbr::Resources> pbr_res,
    SpatialSource source);

// Get the articulation values given a spatial interaction source state.
ArticulateValues GetArticulateValues(
    const SpatialSourceState const& src_state);

// Articulate a controller model given the articulation values.
void ArticulateControllerModel(
    const ArticulateValues& arti_vals,
    Pbr::Model& ctrl_model);

// Controller model cache keeps a single unique copy of the controller models.
struct ControllerModelCache
{
    // Gets the controller model from the cache if available, otherwise attempts to load it and persist in the cache.
    std::future<Shared<const Pbr::Model>> TryGetControllerModelAsync(
        Shared<Pbr::Resources> pbr_res,
        SpatialSource source);

    // Clears out the cache of models.
    void ReleaseDeviceDependentResources();

private:
    Mutex lock;
    ArrayMap<ControllerModelKey, Shared<const Pbr::Model>> ctrl_meshes;
    
    
};

}


NAMESPACE_PARALLEL_END
