#ifndef _AudioCore_SPHERE_H
#define _AudioCore_SPHERE_H


NAMESPACE_AUDIO_BEGIN


class Sphere : public Audio {
public:

	Sphere( double radius = 1.0 ) {
		radius_ = radius;
		mass_ = 1.0;
	};

	void SetPosition( double x, double y, double z ) {
		position_.Set(x, y, z);
	};

	void SetVelocity( double x, double y, double z ) {
		velocity_.Set(x, y, z);
	};

	void SetRadius( double radius ) {
		radius_ = radius;
	};

	void SetMass( double mass ) {
		mass_ = mass;
	};

	vec3* GetPosition() {
		return &position_;
	};

	vec3* GetRelativePosition( vec3* position );
	double GetVelocity( vec3* velocity );
	double isInside( vec3* position );
	
	double GetRadius() {
		return radius_;
	};

	double GetMass() {
		return mass_;
	};

	void AddVelocity( double x, double y, double z );
	void Tick( double dt );

private:
	vec3 position_;
	vec3 velocity_;
	vec3 working_vector_;
	double radius_;
	double mass_;
};

inline void Sphere::Tick( double dt ) {
	position_.data[0] = (position_[0] + (dt * velocity_[0]));
	position_.data[1] = (position_[1] + (dt * velocity_[1]));
	position_.data[2] = (position_[2] + (dt * velocity_[2]));
};

NAMESPACE_AUDIO_END

#endif
