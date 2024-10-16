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
	mat4 proj;
	int proj_mode;
	
	
public:
	Camera();
	inline virtual ~Camera() { }
	
	int id = -1;

	mat4 GetWorldMatrix();
	mat4 GetViewMatrix();
	mat4 GetViewportMatrix();
	mat4 GetProjectionMatrix();

	float GetAspect();
	bool IsOrthographic();
	bool IsPerspective();

	void UpdateMatrices();
	
	void SetResolution(int width, int height);
	void SetResolution(Size sz);
	
	void SetPerspective(float fov_angle, float aspect, float zNear, float zFar);
	void SetOrthographic(float width, float height, float zNear, float zFar);
	
	void SetProjection(const mat4& projection);
	void SetWorld(const mat4& world);
	void SetWorld(const vec3& position, const quat& orient);
	void SetWorld(const vec3& position, const quat& orient, float scale);
	
	Frustum GetFrustum();
	
};

Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane);

#if 0

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

#endif


struct LensPoly {
	vec4 angle_to_pixel_poly;
	Vector<float> pixel_to_angle;
	Size img_sz = Size(0,0);
	float outward_angle = 0;
	
	static const int PIX_MUL = 100;
	
	void MakePixelToAngle();
	void SetSize(Size sz);
	vec2 Project(int lens_i, axes2 local);
	axes2 Unproject(int lens_i, const vec2& pixel);
	void SetAnglePixel(float a, float b, float c, float d);
	void SetEyeOutwardAngle(float f) {outward_angle = f;}
	
	
};

class VirtualStereoCamera : public Camera, public LensPoly {
	float eye_dist = 0.068f;
	
public:
	typedef VirtualStereoCamera CLASSNAME;
	VirtualStereoCamera();
	
	
	void SetEyeDistance(float f) {eye_dist = f;}
	
	void Render(const Octree& o, DescriptorImage& l_img, DescriptorImage& r_img);
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
