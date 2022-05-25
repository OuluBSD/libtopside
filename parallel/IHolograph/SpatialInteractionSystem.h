#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// SpatialInteraction event listener
class ISpatialInteractionListener abstract
{
	
public:
    virtual void OnSourceDetected(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceLost(const SpatialSourceEventArgs& args) {};
    virtual void OnSourcePressed(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceUpdated(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceReleased(const SpatialSourceEventArgs& args) {};
    
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
        spatial_interaction_listeners.Add(std::move(listener));
    }

    void RemoveListener(Shared<ISpatialInteractionListener> listener)
    {
        spatial_interaction_listeners.Remove(std::move(listener));
    }

    ISpatialInteractionManager GetInteractionManager() const
    {
        fail_fast_if(spatial_interaction_manager == nullptr);
        return spatial_interaction_manager;
    }

protected:
    void Initialize() override;
    void Uninitialize() override;

private:
    ISpatialInteractionManager spatial_interaction_manager = 0;

    enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    NativeEventToken source_tokens[SourceEvent::Count];

    ListenerCollection<ISpatialInteractionListener> spatial_interaction_listeners;

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
