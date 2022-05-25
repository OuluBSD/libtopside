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
        const SpatialCoordinateSystem& coordinateSystem,
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
    mutable std::shared_mutex			m_mutex;
    SpatialStageFrameOfReference		m_stageFrameOfReference{ nullptr };
    SpatialStationaryFrameOfReference	m_stationaryFrameOfReference{ nullptr };
    NativeEventToken					m_spatialStageCurrentChanged;

    HoloSpace							m_holospace;
    HoloFrame							m_currentFrame;

    ListenerCollection<IPredictionUpdateListener> m_predictionUpdatelisteners;
    
};


NAMESPACE_PARALLEL_END
