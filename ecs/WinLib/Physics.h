#pragma once


namespace SpatialInputUtilities::Physics {

// Compute the linear velocity near a SpatialInteractionSourceLocation assuming the position is part of the
// spatial interaction source rigid body. When a user does a throwing motion, the user often snaps their
// wrist. The angular velocity from snapping will contribute to the linear velocity of the object being thrown
// proportional to how far the object is from the pivot location (SpatialInteractionSourceLocation).
static inline std::optional<winrt::Windows::Foundation::Numerics::float3> GetVelocityNearSourceLocation(
    winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceLocation const& sourceLocation,
    winrt::Windows::Foundation::Numerics::float3 const& positionNearSourceLocation)
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Numerics;

    const IReference<float3> graspVelocity = sourceLocation.Velocity();
    const IReference<float3> graspPosition = sourceLocation.Position();
    const IReference<float3> angular_velocity = sourceLocation.AngularVelocity();

    if (!graspVelocity || !graspPosition || !angular_velocity)
    {
        return {};
    }

    // Compute the tangential velocity at positionNearSourceLocation due to angular velocity.
    const float3 positionNearSourceLocationOffset = positionNearSourceLocation - graspPosition.Value();
    const float3 angularTangentialVelocity = cross(angular_velocity.Value(), positionNearSourceLocationOffset);

    // Combine the tangential velocity with the velocity to get the combined velocity.
    return graspVelocity.Value() + angularTangentialVelocity;
}

}
