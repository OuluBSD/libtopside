#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

vec3* Sphere::GetRelativePosition( vec3* position ) {
	working_vector_.Set(position->data[0] - position_.data[0],
						  position->data[1] - position_.data[1],
						  position->data[2] - position_.data[2]);
	return &working_vector_;
};

double Sphere::GetVelocity( vec3* velocity ) {
	velocity->Set( velocity_.data[0], velocity_.data[1], velocity_.data[2] );
	return velocity_.GetLength();
};

double Sphere::isInside( vec3* position ) {
	double distance;
	vec3* tempVector;
	tempVector = this->GetRelativePosition( position );
	distance = tempVector->GetLength();
	return distance - radius_;
};

void Sphere::AddVelocity(double x, double y, double z) {
	velocity_.data[0] = (velocity_.data[0] + x);
	velocity_.data[1] = (velocity_.data[1] + y);
	velocity_.data[2] = (velocity_.data[2] + z);
}

NAMESPACE_AUDIO_END
