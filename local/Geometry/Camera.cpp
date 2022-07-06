#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


Camera::Camera() {
	this->fov = 120.0f;
	this->aspect = 1.3f;
	this->near = 0.01f;
	this->far = 1000.0f;
	this->width = 1.0;
	this->height = 1.0f;

	this->world = mat4();
	this->view.SetPerspective(DEG2RAD(this->fov * 0.5), this->aspect, this->near, this->far);
	this->proj_mode = 0;
}

mat4 Camera::GetWorldMatrix() {
	return this->world;
}

bool Camera::IsOrthoNormal() {
	vec3 right = world[0].Splice();
	vec3 up = world[1].Splice();
	vec3 forward = world[2].Splice();
	
	// Axis is not normal
	if (!CMP(Dot(right, right), 1.0f)) {
		return false;
	}
	if (!CMP(Dot(up, up), 1.0f)) {
		return false;
	}
	if (!CMP(Dot(forward, forward), 1.0f)) {
		return false;
	}
	
	// Not perpendicular
	if (!CMP(Dot(forward, up), 0.0f)) {
		return false;
	}
	if (!CMP(Dot(forward, right), 0.0f)) {
		return false;
	}
	if (!CMP(Dot(right, up), 0.0f)) {
		return false;
	}

	return true;
}

void Camera::OrthoNormalize() {
	vec3 right = world[0].Splice();
	vec3 up = world[1].Splice();
	vec3 forward = world[2].Splice();

	vec3 f = forward.GetNormalized();
	vec3 r = Cross(up, f).GetNormalized();
	vec3 u = Cross(f, r);

	this->world = mat4 {
		r[0], r[1], r[2], 0.0f,
		u[0], u[1], u[2], 0.0f,
		f[0], f[1], f[2], 0.0f,
		world[3][0], world[3][1], world[3][2], 1.0f
	};
}

mat4 Camera::GetViewMatrix() {
	return world;
	/*
	if (!IsOrthoNormal()) {
		OrthoNormalize();
	}
	
	mat4 inverse = Transpose(world);
	inverse[3][0] = 0.0f;
	inverse[0][3] = 0.0f;
	inverse[3][1] = 0.0f;
	inverse[1][3] = 0.0f;
	inverse[3][2] = 0.0f;
	inverse[2][3] = 0.0f;
	
	vec3 right = world[0].Splice();
	vec3 up = world[1].Splice();
	vec3 forward = world[2].Splice();
	vec3 position = world[3].Splice();
	
	inverse[3][0] = -Dot(right, position);
	inverse[3][1] = -Dot(up, position);
	inverse[3][2] = -Dot(forward, position);
	
	return inverse;*/
}

float Camera::GetAspect() {
	return aspect;
}

mat4 Camera::GetProjectionMatrix() {
	return view;
}

void Camera::SetResolution(int width, int height) {
	this->width = (float)width;
	this->height = (float)height;
	
	UpdateMatrices();
}

void Camera::UpdateMatrices() {
	this->aspect = (float)width / (float)height;

	if (this->proj_mode == 0) {
		this->view = Perspective(DEG2RAD(this->fov * 0.5), this->aspect, this->near, this->far);
	}
	else if (this->proj_mode == 1) {

		float halfW = this->width * 0.5f;
		float halfH = this->height * 0.5f;

		this->view = Ortho(-halfW, halfW, halfH, -halfH, this->near, this->far);
	}
	// this->proj_mode == 2
		// User defined
}

bool Camera::IsOrthographic() {
	return this->proj_mode == 1;
}

bool Camera::IsPerspective() {
	return this->proj_mode == 0;
}

void Camera::SetPerspective(float fov_angle, float aspect, float zNear, float zFar) {
	this->fov = fov_angle;
	this->aspect = aspect;
	this->near = zNear;
	this->far = zFar;

	this->view = Perspective(DEG2RAD(fov_angle * 0.5), aspect, zNear, zFar);
	this->proj_mode = 0;
}

void Camera::SetOrthographic(float width, float height, float zNear, float zFar) {
	this->width = width;
	this->height = height;
	this->near = zNear;
	this->far = zFar;

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;

	this->view = Ortho(-halfW, halfW, halfH, -halfH, zNear, zFar);
	this->proj_mode = 1;
}

void Camera::SetProjection(const mat4& projection) {
	this->view = projection;
	this->proj_mode = 2;
}

void Camera::SetWorld(const mat4& view) {
	this->world = view;
}

void Camera::SetWorld(const vec3& position, const quat& orient) {
	world = Translate(position) * QuatMat(orient).GetInverse();
}

Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
	Camera result;
	result.SetPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
	return result;
}

Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane) {
	Camera result;
	result.SetOrthographic(width, height, nearPlane, farPlane);
	return result;
}




Frustum Camera::GetFrustum(float distance) {
	Frustum result;

	mat4 vp;
	mat4 proj = GetProjectionMatrix();
	mat4 view = GetViewMatrix();
	vp = proj * view;
	float vp41 = vp[3][0];
	float vp42 = vp[3][1];
	float vp43 = vp[3][2];
	float vp44 = vp[3][3];
	
	/*DUMP((proj * vec4(0,0,-1,1)).Splice());
	DUMP((view * vec4(0,0,-1,1)).Splice());
	DUMP((vp * vec4(0,0,-1,1)).Splice());*/
	
	
	vec3 col1 = vp.GetColumn(0).Splice();
	vec3 col2 = vp.GetColumn(1).Splice();
	vec3 col3 = vp.GetColumn(2).Splice();
	vec3 col4 = vp.GetColumn(3).Splice();
					
	// Find plane magnitudes
	result.left.normal	= col4 + col1;
	result.right.normal = col4 - col1;
	result.bottom.normal= col4 + col2;
	result.top.normal	= col4 - col2;
	result._near.normal	= /*col4 +*/ col3;
	result._far.normal	= col4 - col3;

	// Find plane distances
	result.left.distance	= vp44 + vp41;
	result.right.distance	= vp44 - vp41;
	result.bottom.distance	= vp44 + vp42;
	result.top.distance		= vp44 - vp42;
	result._near.distance	= /*vp44 +*/ vp43;
	result._far.distance	= vp44 - vp43;

	// Normalize all 6 planes
	for (int i = 0; i < 6; ++i) {
		float mag = 1.0f / result[i].normal.GetMagnitude();
		result[i].normal.Normalize();
		result[i].distance *= mag;
	}

	return result;
}






#if 0

OrbitCamera::OrbitCamera() {
	target = vec3(0, 0, 0);
	zoom_distance = 10.0f;
	zoom_speed = 200.0f;
	rot_speed = vec2(250.0f, 120.0f);
	y_rot_limit = vec2(-20.0f, 80.0f);
	zoom_distance_limit = vec2(3.0f, 15.0f);
	cur_rot = vec2(0, 0);
	pan_speed = vec2(180.0f, 180.0f);
}

void OrbitCamera::Rotate(const vec2& drot, float dt) {
	this->cur_rot[0] += drot[0] * this->rot_speed[0] * this->zoom_distance* dt;
	this->cur_rot[1] += drot[1] * this->rot_speed[1] * this->zoom_distance * dt;

	this->cur_rot[0] = ClampAngle(this->cur_rot[0], -360, 360);
	this->cur_rot[1] = ClampAngle(this->cur_rot[1], this->y_rot_limit[0], this->y_rot_limit[1]);
}

void OrbitCamera::Zoom(float dzoom, float dt) {
	this->zoom_distance = this->zoom_distance + dzoom  * this->zoom_speed * dt;
	if (this->zoom_distance < this->zoom_distance_limit[0]) {
		this->zoom_distance = this->zoom_distance_limit[0];
	}
	if (this->zoom_distance > this->zoom_distance_limit[1]) {
		this->zoom_distance = this->zoom_distance_limit[1];
	}
}

void OrbitCamera::Pan(const vec2& dpan, float dt) {
	vec3 right = world[0].Splice();

	target = target - (right * (dpan[0] * pan_speed[0] * dt));
	target = target + (vec3(0, 1, 0) * (dpan[1] * this->pan_speed[1] * dt));

	float midZoom = this->zoom_distance_limit[0] + (this->zoom_distance_limit[1] - this->zoom_distance_limit[0]) * 0.5f;
	this->zoom_distance = midZoom - this->zoom_distance;
	vec3 rotation = vec3(this->cur_rot[1], this->cur_rot[0], 0);
	mat3 orient = Rotation3x3(rotation[0], rotation[1], rotation[2]);
	vec3 dir = MultiplyVector( vec3(0.0, 0.0, -this->zoom_distance), orient);
	target = target - dir;
	this->zoom_distance = midZoom;
}

void OrbitCamera::Update(float dt) {
	vec3 rotation = vec3(this->cur_rot[1], this->cur_rot[0], 0);
	mat3 orient = Rotation3x3(rotation[0], rotation[1], rotation[2]);
	vec3 dir = MultiplyVector( vec3(0.0, 0.0, -this->zoom_distance), orient);
	vec3 position = dir + target;
	this->world = (LookAt(position, target, vec3(0, 1, 0))).GetInverse();
}

float OrbitCamera::ClampAngle(float angle, float min, float max) {
	while (angle < -360) {
		angle += 360;
	}
	while (angle > 360) {
		angle -= 360;
	}
	if (angle < min) {
		angle = min;
	}
	if (angle > max) {
		angle = max;
	}
	return angle;
}

void OrbitCamera::PrintDebug() {
	LOG("Target: (" << target[0] << ", " << target[1] << ", " << target[2] << ")");
	LOG("Zoom distance: " << zoom_distance);
	LOG("Rotation: (" << cur_rot[0] << ", " << cur_rot[1] << ")");
}

void OrbitCamera::SetTarget(const vec3& new_tgt) {
	target = new_tgt;
}

void OrbitCamera::SetZoom(float zoom) {
	this->zoom_distance = zoom;
}

void OrbitCamera::SetRotation(const vec2& rotation) {
	this->cur_rot = rotation;
}

#endif










VirtualStereoCamera::VirtualStereoCamera() {
	
}

void VirtualStereoCamera::SetPixelAngle(float a, float b, float c, float d) {
	lens_poly[0] = a;
	lens_poly[1] = b;
	lens_poly[2] = c;
	lens_poly[3] = d;
}

void VirtualStereoCamera::Render(const Octree& o, VectorImage& img) {
	Frustum f = GetFrustum(0.0);
	
	auto iter = o.GetFrustumIterator(f);
	
	mat4 inv_world = world.GetInverse();
	
	while (iter) {
		const OctreeNode& n = *iter;
		
		for (const auto& one_obj : n.objs) {
			const OctreeObject& obj = *one_obj;
			vec3 obj_pos = obj.GetPosition();
			
			// to camera local space
			vec3 local = (obj_pos.Embed() * world).Splice();
			
			TODO
			
			LOG(obj_pos.ToString() << ", " << local.ToString());
			
		}
		
		iter++;
	}
	
	LOG("");
}



NAMESPACE_TOPSIDE_END
