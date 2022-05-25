#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace SpatialInputUtilities::Physics {

// Compute the linear velocity near a SpatialInteractionSourceLocation assuming the position is part of the
// spatial interaction source rigid body. When a user does a throwing motion, the user often snaps their
// wrist. The angular velocity from snapping will contribute to the linear velocity of the object being thrown
// proportional to how far the object is from the pivot location (SpatialInteractionSourceLocation).
static inline Optional<vec3> GetVelocityNearSourceLocation(
    const SpatialSourceLocation& source_location,
    const vec3& position_near_source_location)
{
    const IReference<vec3> grasp_velocity = source_location.Velocity();
    const IReference<vec3> grasp_position = source_location.Position();
    const IReference<vec3> angular_velocity = source_location.AngularVelocity();

    if (!grasp_velocity || !grasp_position || !angular_velocity)
    {
        return {};
    }

    // Compute the tangential velocity at position_near_source_location due to angular velocity.
    const vec3 position_near_source_locationOffset = position_near_source_location - grasp_position.Value();
    const vec3 angularTangentialVelocity = cross(angular_velocity.Value(), position_near_source_locationOffset);

    // Combine the tangential velocity with the velocity to get the combined velocity.
    return grasp_velocity.Value() + angularTangentialVelocity;
}

}


NAMESPACE_PARALLEL_END
