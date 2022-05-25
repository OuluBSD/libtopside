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
    float GraspPress{ 0 };
    float MenuPress{ 0 };
    float SelectPress{ 0 };
    float ThumbstickPress{ 0 };
    float ThumbstickX{ 0.5f };
    float ThumbstickY{ 0.5f };
    float TouchpadPress{ 0 };
    float TouchpadPressX{ 0.5f };
    float TouchpadPressY{ 0.5f };
    float TouchpadTouchX{ 0.5f };
    float TouchpadTouchY{ 0.5f };
    bool TouchIndicatorVisible{ false };
};

// Create a key for a given spatial interaction source.
ControllerModelKey GetControllerModelKey(SpatialSource const& source);

// Try to load the renderable model for a given a spatial interaction source.
std::future<Shared<const Pbr::Model>> TryLoadRenderModelAsync(
    Shared<Pbr::Resources> pbr_res,
    SpatialSource source);

// Get the articulation values given a spatial interaction source state.
ArticulateValues GetArticulateValues(
    SpatialSourceState const& sourceState);

// Articulate a controller model given the articulation values.
void ArticulateControllerModel(
    ArticulateValues const& articulateValues,
    Pbr::Model& controllerModel);

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
    std::mutex m_lock;
    std::map<ControllerModelKey, Shared<const Pbr::Model>> m_controllerMeshes;
};

}


NAMESPACE_PARALLEL_END
