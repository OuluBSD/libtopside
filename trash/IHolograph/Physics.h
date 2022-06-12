#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


struct SpatialInputUtilities {
	//using SpatialSourceLocation = typename Holo::SpatialSourceLocation;
	
	
	// Compute the linear velocity near a SpatialInteractionSourceLocation assuming the position is part of the
	// spatial interaction source rigid body. When a user does a throwing motion, the user often snaps their
	// wrist. The angular velocity from snapping will contribute to the linear velocity of the object being thrown
	// proportional to how far the object is from the pivot location (SpatialInteractionSourceLocation).
	static inline Optional<vec3> GetVelocityNearSourceLocation(
	    const SpatialSourceLocation& source_location,
	    const vec3& position_near_source_location)
	{
	    const vec3 grasp_velocity = source_location.GetVelocity();
	    const vec3 grasp_position = source_location.GetPosition();
	    const vec3 angular_velocity = source_location.GetAngularVelocity();
		
		TODO // value is optional
	    /*if (!grasp_velocity || !grasp_position || !angular_velocity)
	    {
	        return {};
	    }*/
	
	    // Compute the tangential velocity at position_near_source_location due to angular velocity.
	    const vec3 position_near_source_locationOffset = position_near_source_location - grasp_position;
	    const vec3 angularTangentialVelocity = cross(angular_velocity, position_near_source_locationOffset);
	
	    // Combine the tangential velocity with the velocity to get the combined velocity.
	    return grasp_velocity + angularTangentialVelocity;
	}

};


NAMESPACE_PARALLEL_END

#endif
