#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// SpatialInteraction event listener
class ISpatialInteractionListener abstract
{
public:
    virtual void OnSourceDetected(
        const SpatialSourceEventArgs& args) {};

    virtual void OnSourceLost(
        const SpatialSourceEventArgs& args) {};

    virtual void OnSourcePressed(
        const SpatialSourceEventArgs& args) {};

    virtual void OnSourceUpdated(
        const SpatialSourceEventArgs& args) {};

    virtual void OnSourceReleased(
        const SpatialSourceEventArgs& args) {};
};

////////////////////////////////////////////////////////////////////////////////
// SpatialInteractionSystem
// Responsible for managing the events from SpatialInteractionManager with additional filtering
class SpatialInteractionSystem final : public System<SpatialInteractionSystem>
{
public:
    using System::System;

    void AddListener(Shared<ISpatialInteractionListener> listener)
    {
        m_spatialInteractionListeners.Add(std::move(listener));
    }

    void RemoveListener(Shared<ISpatialInteractionListener> listener)
    {
        m_spatialInteractionListeners.Remove(std::move(listener));
    }

    ISpatialInteractionManager GetInteractionManager() const
    {
        fail_fast_if(m_spatialInteractionManager == nullptr);
        return m_spatialInteractionManager;
    }

protected:
    void Initialize() override;
    void Uninitialize() override;

private:
    ISpatialInteractionManager m_spatialInteractionManager{ nullptr };

    enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    NativeEventToken m_sourceTokens[SourceEvent::Count];

    ListenerCollection<ISpatialInteractionListener> m_spatialInteractionListeners;

    void BindEventHandlers();
    void ReleaseEventHandlers();

    // Events Handlers
    void HandleSourceDetected(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs&  args);

    void HandleSourceLost(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourcePressed(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourceUpdated(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourceReleased(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

};


NAMESPACE_PARALLEL_END
