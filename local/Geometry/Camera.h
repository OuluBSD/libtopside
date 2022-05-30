#ifndef _Geometry_Camera_h_
#define _Geometry_Camera_h_

NAMESPACE_TOPSIDE_BEGIN



class Camera {
protected:
	float fov;
	float aspect;
	float near;
	float far;
	float width;
	float height;

	mat4 world;
	mat4 view;
	int proj_mode;
public:
	Camera();
	inline virtual ~Camera() { }

	mat4 GetWorldMatrix();
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();

	float GetAspect();
	bool IsOrthographic();
	bool IsPerspective();

	bool IsOrthoNormal();
	void OrthoNormalize();

	void Resize(int width, int height);
	
	void Perspective(float fov_angle, float aspect, float zNear, float zFar);
	void Orthographic(float width, float height, float zNear, float zFar);
	
	void SetProjection(const mat4& projection);
	void SetWorld(const mat4& view);

	Frustum GetFrustum();
	
	
};

Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane);

class OrbitCamera : public Camera {
protected:
	vec3 target;
	vec2 pan_speed;

	float zoom_distance;
	vec2 zoom_distance_limit;
	float zoom_speed;

	vec2 rot_speed;
	vec2 y_rot_limit;
	vec2 cur_rot;
public:
	OrbitCamera();
	inline virtual ~OrbitCamera() { }

	void Rotate(const vec2& drot, float dt);
	void Zoom(float dzoom, float dt);
	void Pan(const vec2& dpan, float dt);

	void Update(float dt);
	float ClampAngle(float angle, float min, float max);

	void SetTarget(const vec3& new_tgt);
	void SetZoom(float zoom);
	void SetRotation(const vec2& rotation);
	void PrintDebug();
};


NAMESPACE_TOPSIDE_END

#endif
