#if 0
#include "EcsWin.h"


NAMESPACE_ECS_BEGIN


using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::placeholders;

bool SpatialInteractionSystem::Initialize()
{
    m_spatialInteractionManager = SpatialInteractionManager::GetForCurrentView();
    BindEventHandlers();
    return true;
}

void SpatialInteractionSystem::Uninitialize()
{
    ReleaseEventHandlers();
    m_spatialInteractionManager = nullptr;
}

void SpatialInteractionSystem::BindEventHandlers()
{
    fail_fast_if(m_spatialInteractionManager == nullptr);

    m_sourceTokens[Detected] = m_spatialInteractionManager.SourceDetected(
        std::bind(&SpatialInteractionSystem::HandleSourceDetected, this, _1, _2));

    m_sourceTokens[Pressed] = m_spatialInteractionManager.SourcePressed(
        std::bind(&SpatialInteractionSystem::HandleSourcePressed, this, _1, _2));

    m_sourceTokens[Updated] = m_spatialInteractionManager.SourceUpdated(
        std::bind(&SpatialInteractionSystem::HandleSourceUpdated, this, _1, _2));

    m_sourceTokens[Released] = m_spatialInteractionManager.SourceReleased(
        std::bind(&SpatialInteractionSystem::HandleSourceReleased, this, _1, _2));

    m_sourceTokens[Lost] = m_spatialInteractionManager.SourceLost(
        std::bind(&SpatialInteractionSystem::HandleSourceLost, this, _1, _2));
}

void SpatialInteractionSystem::ReleaseEventHandlers()
{
    fail_fast_if(m_spatialInteractionManager == nullptr);

    m_spatialInteractionManager.SourceLost(m_sourceTokens[Lost]);
    m_spatialInteractionManager.SourceReleased(m_sourceTokens[Released]);
    m_spatialInteractionManager.SourceUpdated(m_sourceTokens[Updated]);
    m_spatialInteractionManager.SourcePressed(m_sourceTokens[Pressed]);
    m_spatialInteractionManager.SourceDetected(m_sourceTokens[Detected]);
}

void SpatialInteractionSystem::HandleSourceDetected(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : m_spatialInteractionListeners.PurgeAndGetListeners())
    {
        listener->OnSourceDetected(args);
    }
}

void SpatialInteractionSystem::HandleSourceLost(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : m_spatialInteractionListeners.PurgeAndGetListeners())
    {
        listener->OnSourceLost(args);
    }
}

void SpatialInteractionSystem::HandleSourcePressed(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : m_spatialInteractionListeners.PurgeAndGetListeners())
    {
        listener->OnSourcePressed(args);
    }
}

void SpatialInteractionSystem::HandleSourceUpdated(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : m_spatialInteractionListeners.PurgeAndGetListeners())
    {
        listener->OnSourceUpdated(args);
    }
}

void SpatialInteractionSystem::HandleSourceReleased(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : m_spatialInteractionListeners.PurgeAndGetListeners())
    {
        listener->OnSourceReleased(args);
    }
}


NAMESPACE_ECS_END
#endif
