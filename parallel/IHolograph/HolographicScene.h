#pragma once


NAMESPACE_PARALLEL_BEGIN


// PredictionUpdated event listener
class IPredictionUpdateListener abstract
{
public:
    enum PredictionUpdateReason
    {
        HolographicSpaceCreateNextFrame,
        HolographicFrameUpdatePrediction,
    };

    virtual void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HoloFramePred& prediction) = 0;
    
};


// HolographicScene
// Maintains a list of our current state of Windows::Perception objects, ensuring the rest of the systems
// use the same coordinate system, timestamp, etc. 
class HolographicScene : public System<HolographicScene>
{
public:
    using System::System;

    HolographicScene(Engine& core, HoloSpace holospace);

    HoloFrame CurrentFrame() const;
    HoloSpace HolographicSpace() const;

    SpatialCoordinateSystem WorldCoordinateSystem() const;
    PerceptionTimestamp CurrentTimestamp() const;

    void UpdateCurrentPrediction();

    void AddPredictionUpdateListener(Shared<IPredictionUpdateListener> listener);
    void RemovePredictionUpdateListener(Shared<IPredictionUpdateListener> listener);

protected:
    void Initialize() override;
    void Update(double) override;
    void Uninitialize() override;

    void OnCurrentStageChanged();

    void OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason);

private:
    mutable std::shared_mutex			lock;
    SpatialStageFrameOfReference		stage_frame_of_reference = 0;
    SpatialStationaryFrameOfReference	stationary_frame_of_reference = 0;
    NativeEventToken					spatial_stage_current_changed;

    HoloSpace							holospace;
    HoloFrame							current_frame;

    ListenerCollection<IPredictionUpdateListener>	prediction_update_listeners;
    
};


NAMESPACE_PARALLEL_END
