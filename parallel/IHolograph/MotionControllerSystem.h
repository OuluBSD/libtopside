#pragma once


NAMESPACE_PARALLEL_BEGIN


struct MotionControllerComponent : Component<MotionControllerComponent>
{
    bool IsSource(const SpatialSource& rhs) const;

    bool						attach_ctrl_model = false;
    SpatialSourceHandedness		req_hand { SpatialSourceHandedness::Unspecified };
    SpatialSource				source = 0;
    SpatialSourceLocation		location = 0;
    
};


// MotionControllerSystem
// This system manages events and behaviors specific to Motion Controllers 
//
// You can use the MotionControllerComponent::req_hand to automatically update an Entity's Transform based on handedness 
// i.e. Attach this entity to the Left or Right controller, and the MotionControllerSystem will automatically update the Transform
//
// You can also use the MotionControllerComponent::attach_ctrl_model to automatically attach the correct 3D model to the object
// so that the virtual controller will be rendered in the same position as the physical controller
class MotionControllerSystem :
    public System<MotionControllerSystem>,
    public IPredictionUpdateListener,
    public ISpatialInteractionListener
{
public:
    using System::System;

protected:
    // System
    void Start() override;
    void Stop() override;

    // IPredictionUpdateListener
    void OnPredictionUpdated(
        Neso::IPredictionUpdateListener::PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HoloFramePred& prediction) override;

    // ISpatialInteractionListener
    void OnSourceDetected(const SpatialSourceEventArgs& args) override;
    void OnSourceUpdated(const SpatialSourceEventArgs& args) override;
    void OnSourceLost(const SpatialSourceEventArgs& args) override;
    
private:
    void RefreshComponentsForSource(const SpatialSource& source);
    
};


NAMESPACE_PARALLEL_END

