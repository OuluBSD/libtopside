#ifndef _System_MotionController_h_
#define _System_MotionController_h_

#if 0

NAMESPACE_OULU_BEGIN

struct MotionControllerComponent : Component<MotionControllerComponent>
{
    bool IsSource(const ControllerSourceDevice& rhs) const;

    bool attachControllerModel = false;
    ControllerSourceHandedness requestedHandedness;
    ControllerSource source;
    ControllerSourceLocation location;
};

////////////////////////////////////////////////////////////////////////////////
// MotionControllerSystem
// This system manages events and behaviors specific to Motion Controllers 
//
// You can use the MotionControllerComponent::requestedHandedness to automatically update an Entity's Transform based on handedness 
// i.e. Attach this entity to the Left or Right controller, and the MotionControllerSystem will automatically update the Transform
//
// You can also use the MotionControllerComponent::attachControllerModel to automatically attach the correct 3D model to the object
// so that the virtual controller will be rendered in the same position as the physical controller
class MotionControllerSystem :
    public System<MotionControllerSystem>,
    public IPredictionUpdateListener,
    public ControllerListenerInterface
{
public:
    using System::System;

protected:
    // System
    void Start() override;
    void Stop() override;

    // IPredictionUpdateListener
    void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const HolographicFramePrediction& prediction) const override;

    // ControllerListenerInterface
    void OnSourceDetected(const ControllerEventArgs& args) override;
    void OnSourceUpdated(const ControllerEventArgs& args) override;
    void OnSourceLost(const ControllerEventArgs& args) override;

private:
    void RefreshComponentsForSource(const ControllerSourceDevice& source) const;
};

NAMESPACE_OULU_END

#endif
#endif
