#ifndef _AudioCore_SPHERE_H
#define _AudioCore_SPHERE_H


NAMESPACE_AUDIO_BEGIN


class Sphere : public Audio {
public:

	Sphere( float radius = 1.0f ) {
		radius_ = radius;
		mass_ = 1.0f;
	};

	void SetPosition( float x, float y, float z ) {
		position_.Set(x, y, z);
	};

	void SetVelocity( float x, float y, float z ) {
		velocity_.Set(x, y, z);
	};

	void SetRadius( float radius ) {
		radius_ = radius;
	};

	void SetMass( float mass ) {
		mass_ = mass;
	};

	vec3* GetPosition() {
		return &position_;
	};

	vec3* GetRelativePosition( vec3* position );
	float GetVelocity( vec3* velocity );
	float isInside( vec3* position );
	
	float GetRadius() {
		return radius_;
	};

	float GetMass() {
		return mass_;
	};

	void AddVelocity( float x, float y, float z );
	void Tick( float dt );

private:
	vec3 position_;
	vec3 velocity_;
	vec3 working_vector_;
	float radius_;
	float mass_;
};

inline void Sphere::Tick( float dt ) {
	position_.data[0] = (float)(position_[0] + (dt * velocity_[0]));
	position_.data[1] = (float)(position_[1] + (dt * velocity_[1]));
	position_.data[2] = (float)(position_[2] + (dt * velocity_[2]));
};

NAMESPACE_AUDIO_END

#endif
