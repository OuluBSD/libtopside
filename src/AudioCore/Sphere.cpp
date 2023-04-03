#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

vec3* Sphere::GetRelativePosition( vec3* position ) {
	working_vector_.Set(position->data[0] - position_.data[0],
						  position->data[1] - position_.data[1],
						  position->data[2] - position_.data[2]);
	return &working_vector_;
};

float Sphere::GetVelocity( vec3* velocity ) {
	velocity->Set( velocity_.data[0], velocity_.data[1], velocity_.data[2] );
	return velocity_.GetLength();
};

float Sphere::isInside( vec3* position ) {
	float distance;
	vec3* tempVector;
	tempVector = this->GetRelativePosition( position );
	distance = tempVector->GetLength();
	return distance - radius_;
};

void Sphere::AddVelocity(float x, float y, float z) {
	velocity_.data[0] = (velocity_.data[0] + x);
	velocity_.data[1] = (velocity_.data[1] + y);
	velocity_.data[2] = (velocity_.data[2] + z);
}

NAMESPACE_AUDIO_END
