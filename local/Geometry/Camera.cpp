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
	this->proj.SetPerspective(DEG2RAD(this->fov * 0.5), this->aspect, this->near, this->far);
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

mat4 Camera::GetViewportMatrix() {
	float ratio = (float)height / (float)width;
	return GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
}

mat4 Camera::GetViewMatrix() {
	return proj * world;
}

void Camera::SetProgram(int i) {
	prog_id = i;
}

int Camera::GetProgram() const {
	return prog_id;
}

float Camera::GetAspect() {
	return aspect;
}

mat4 Camera::GetProjectionMatrix() {
	return proj;
}

void Camera::SetResolution(int width, int height) {
	this->width = (float)width;
	this->height = (float)height;
	
	UpdateMatrices();
}

void Camera::SetResolution(Size sz) {
	width = sz.cx;
	height = sz.cy;
	
	UpdateMatrices();
}

void Camera::UpdateMatrices() {
	this->aspect = (float)width / (float)height;

	if (this->proj_mode == 0) {
		this->proj = Perspective(DEG2RAD(this->fov * 0.5), this->aspect, this->near, this->far);
	}
	else if (this->proj_mode == 1) {

		float halfW = this->width * 0.5f;
		float halfH = this->height * 0.5f;

		this->proj = Ortho(-halfW, halfW, halfH, -halfH, this->near, this->far);
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
	
	float ratio = 1.0f / aspect;
	this->proj =
		GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1) *
		Perspective(DEG2RAD(fov_angle * 0.5), 1, zNear, zFar);
	this->proj_mode = 0;
}

void Camera::SetOrthographic(float width, float height, float zNear, float zFar) {
	this->width = width;
	this->height = height;
	this->near = zNear;
	this->far = zFar;

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;

	this->proj = Ortho(-halfW, halfW, halfH, -halfH, zNear, zFar);
	this->proj_mode = 1;
}

void Camera::SetProjection(const mat4& projection) {
	this->proj = projection;
	this->proj_mode = 2;
}

void Camera::SetWorld(const mat4& world) {
	this->world = world;
}

void Camera::SetWorld(const vec3& position, const quat& orient) {
	world = Translate(position) * QuatMat(orient).GetInverse();
}

void Camera::SetWorld(const vec3& position, const quat& orient, const vec3& scale) {
	world = Scale(scale).GetInverse() * QuatMat(orient).GetInverse() * Translate(position);
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




Frustum Camera::GetFrustum() {
	Frustum result;

	mat4 vp;
	mat4 proj = GetProjectionMatrix();
	mat4 world = GetWorldMatrix();
	vp = proj * world;
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

void VirtualStereoCamera::Render(const Octree& o, DescriptorImage& l_img, DescriptorImage& r_img) {
	l_img.ClearDescriptors();
	r_img.ClearDescriptors();
	
	Frustum f = GetFrustum();
	
	auto iter = const_cast<Octree&>(o).GetIterator(f);
	
	mat4 world = GetViewMatrix();
	
	LensPoly::SetSize(Size(width, height));
	
	
	while (iter) {
		const OctreeNode& n = *iter;
		//LOG(n.GetAABB().ToString());
		
		for (const auto& one_obj : n.objs) {
			const OctreeObject& obj = *one_obj;
			vec3 obj_pos = obj.GetPosition();
			vec3 local_obj_pos = (obj_pos.Embed() * world).Splice();
			
			if (local_obj_pos[2] * SCALAR_FWD_Z <= 0)
				continue;
			
			// Random additional descriptor values
			float angle = Randomf() * 2*M_PI;
			union {
				byte desc[32];
				uint32 u32[8];
				uint32 u64[4];
				const OctreeObject* ptr[4];
			};
			for(int i = 0; i < 4; i++)
				ptr[i] = &obj;
			
			axes2 l, r;
			LookAtStereoAngles(eye_dist, local_obj_pos, l, r);
			vec2 l_px = Project(0, l);
			vec2 r_px = Project(1, r);
			
			l_img.AddDescriptor(l_px[0], l_px[1], angle, desc);
			r_img.AddDescriptor(r_px[0], r_px[1], angle, desc);
			
			//LOG(l_px.ToString() << ", " << l.ToString()); LOG(r_px.ToString() << ", " << r.ToString());
		}
		
		iter++;
	}
	//LOG("");
}











void LensPoly::SetAnglePixel(float a, float b, float c, float d) {
	angle_to_pixel_poly[0] = a;
	angle_to_pixel_poly[1] = b;
	angle_to_pixel_poly[2] = c;
	angle_to_pixel_poly[3] = d;
}

vec2 LensPoly::Project(int lens_i, axes2 axes) {
	ASSERT(img_sz.cx && img_sz.cy);
	
	// Angle from center of "the lens"
	#if 0
	vec3 fwd = VEC_FWD;
	vec3 right = VEC_RIGHT;
	float angle = VectorAngle(fwd, local);
	float deg = angle / M_PI * 180;
	ASSERT(deg < 90);
	
	// Angle from local right vector
	vec3 roll_ortho = Cross(local, fwd);
	vec3 roll = Cross(fwd, roll_ortho);
	float roll_angle = VectorAngle(right, roll);
	if (roll.data[1] < 0)
		roll_angle = -roll_angle;
	float roll_deg = roll_angle / M_PI * 180;
	#endif
	
	if (lens_i == 0)
		axes[0] -= outward_angle;
	else
		axes[0] += outward_angle;
	
	axes2 roll_axes = GetDirAxesRoll(GetAxesDir(axes));
	float angle = roll_axes.data[0];
	float roll_angle = roll_axes.data[1];
	
	float pix_dist =
		angle_to_pixel_poly.data[0] * angle +
		angle_to_pixel_poly.data[1] * angle * angle +
		angle_to_pixel_poly.data[2] * angle * angle * angle +
		angle_to_pixel_poly.data[3] * angle * angle * angle * angle;
	
	vec2 px;
	px.data[0] = pix_dist * -sin(roll_angle);
	px.data[1] = pix_dist * cos(roll_angle);
	px.data[0] += img_sz.cx / 2;
	px.data[1] += img_sz.cy / 2;
	if (0) {
		px.data[0] = floor(px.data[0] + 0.5);
		px.data[1] = floor(px.data[1] + 0.5);
	}
	
	#if 0
	axes2 a = Unproject(px);
	if (!IsClose(a, axes, 1)) {
		DUMP(Unproject(px));
	}
	ASSERT(IsClose(a, axes, 1));
	#else
	ASSERT(IsClose(Unproject(lens_i, px), axes, 0.01));
	#endif
	
	return px;
}

axes2 LensPoly::Unproject(int lens_i, const vec2& pixel) {
	ASSERT(img_sz.cx && img_sz.cy);
	
	vec2 ct_rel = pixel - vec2(img_sz.cx / 2, img_sz.cy / 2);
	float len = ct_rel.GetLength();
	int leni0 = (int)(len * PIX_MUL);
	int leni1 = leni0 + 1 < pixel_to_angle.GetCount() ? leni0 + 1 : leni0;
	float f1 = fmodf(len, 1.0f);
	float f0 = 1.0f - f1;
	
	ASSERT(leni0 >= 0 && leni0 < pixel_to_angle.GetCount());
	if (leni0 >= pixel_to_angle.GetCount()) return axes2(0,0);
	
	float angle = pixel_to_angle[leni0] * f0 + pixel_to_angle[leni1] * f1;
	float deg = angle / M_PI * 180;
	//vec3 v0(sin(angle), 0, -cos(angle));
	
	float roll_angle = -atan2f(ct_rel[0], ct_rel[1]);
	float roll_deg = roll_angle / M_PI * 180;
	//mat4 rot = ZRotation(roll_angle);
	
	//vec3 dir = (rot * v0.Embed()).Splice();
	//dir.Normalize();
	vec3 dir = AxesDirRoll(angle, roll_angle);
	axes2 axes = GetDirAxes(dir).Splice();
	
	if (lens_i == 0)
		axes[0] += outward_angle;
	else
		axes[0] -= outward_angle;
	
	return axes;
}

void LensPoly::SetSize(Size sz) {
	if (img_sz != sz) {
		img_sz = sz;
		MakePixelToAngle();
	}
}

void LensPoly::MakePixelToAngle() {
	
	pixel_to_angle.SetCount(0);
	int max_len = (int)sqrt(img_sz.cx * img_sz.cx + img_sz.cy * img_sz.cy) + 1;
	max_len *= PIX_MUL;
	
	pixel_to_angle.SetCount(max_len, 0);
	
	float step = 0.0001 / (double)PIX_MUL;
	for (float angle = 0; angle <= M_PI; angle += step) {
		float pix_dist =
			angle_to_pixel_poly.data[0] * angle +
			angle_to_pixel_poly.data[1] * angle * angle +
			angle_to_pixel_poly.data[2] * angle * angle * angle +
			angle_to_pixel_poly.data[3] * angle * angle * angle * angle;
		
		int i = (int)(pix_dist * PIX_MUL);
		ASSERT(i >= 0);
		if (i < 0)
			continue;
		if (i >= max_len)
			break;
		
		float& pa = pixel_to_angle[i];
		if (pa == 0)
			pa = angle;
	}
	
	//DUMPC(pixel_to_angle);
	
}





NAMESPACE_TOPSIDE_END
