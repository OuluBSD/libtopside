#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


Camera::Camera() {
	
}

mat4 Camera::GetWorldMatrix() {
	return this->world;
}

mat4 Camera::GetViewportMatrix() {
	float ratio = (float)height / (float)width;
	return GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
}

mat4 Camera::GetViewMatrix() {
	return proj * world;
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
	
	this->proj = Perspective(DEG2RAD(fov_angle * 0.5), aspect, zNear, zFar);
	this->proj_mode = 0;
}

void Camera::SetOrthographic(float width, float height, float zNear, float zFar) {
	this->width = width;
	this->height = height;
	this->near = zNear;
	this->far = zFar;

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;

	this->proj =
		Ortho(-halfW, halfW, halfH, -halfH, zNear, zFar)
		* Scale(vec3(+1,-1,+1));
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
	world = (Translate(position) * QuatMat(orient)).GetInverse();
}

void Camera::SetWorld(const vec3& position, const quat& orient, float scale) {
	world = (Translate(position) * QuatMat(orient) * Scale(vec3(scale))).GetInverse();
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



void FromNumbers(const vec4& numbers, Plane& p) {
	vec3 abc = numbers.Splice();
	float mag = abc.GetLength();
	abc.Normalize();
	
	p.normal = abc;
	p.distance = numbers[3] / mag;
}

void NormalizePlane(Plane& p) {
	float magnitude = sqrtf(p.normal.data[0] * p.normal.data[0] + p.normal.data[1] * p.normal.data[1] + p.normal.data[2] * p.normal.data[2]);
	p.normal.data[0] /= magnitude;
	p.normal.data[1] /= magnitude;
	p.normal.data[2] /= magnitude;
	p.distance /= magnitude;
}

Frustum Camera::GetFrustum() {
	Frustum result;
	
	mat4 vp;
	mat4 proj = GetProjectionMatrix();
	mat4 world = GetWorldMatrix();
	vp = proj * world;
	
	float clip[16];

	clip[0] = world.data[0].data[0] * proj.data[0].data[0] + world.data[0].data[1] * proj.data[1].data[0] + world.data[0].data[2] * proj.data[2].data[0] + world.data[0].data[3] * proj.data[3].data[0];
	clip[1] = world.data[0].data[0] * proj.data[0].data[1] + world.data[0].data[1] * proj.data[1].data[1] + world.data[0].data[2] * proj.data[2].data[1] + world.data[0].data[3] * proj.data[3].data[1];
	clip[2] = world.data[0].data[0] * proj.data[0].data[2] + world.data[0].data[1] * proj.data[1].data[2] + world.data[0].data[2] * proj.data[2].data[2] + world.data[0].data[3] * proj.data[3].data[2];
	clip[3] = world.data[0].data[0] * proj.data[0].data[3] + world.data[0].data[1] * proj.data[1].data[3] + world.data[0].data[2] * proj.data[2].data[3] + world.data[0].data[3] * proj.data[3].data[3];

	clip[4] = world.data[1].data[0] * proj.data[0].data[0] + world.data[1].data[1] * proj.data[1].data[0] + world.data[1].data[2] * proj.data[2].data[0] + world.data[1].data[3] * proj.data[3].data[0];
	clip[5] = world.data[1].data[0] * proj.data[0].data[1] + world.data[1].data[1] * proj.data[1].data[1] + world.data[1].data[2] * proj.data[2].data[1] + world.data[1].data[3] * proj.data[3].data[1];
	clip[6] = world.data[1].data[0] * proj.data[0].data[2] + world.data[1].data[1] * proj.data[1].data[2] + world.data[1].data[2] * proj.data[2].data[2] + world.data[1].data[3] * proj.data[3].data[2];
	clip[7] = world.data[1].data[0] * proj.data[0].data[3] + world.data[1].data[1] * proj.data[1].data[3] + world.data[1].data[2] * proj.data[2].data[3] + world.data[1].data[3] * proj.data[3].data[3];

	clip[8] = world.data[2].data[0] * proj.data[0].data[0] + world.data[2].data[1] * proj.data[1].data[0] + world.data[2].data[2] * proj.data[2].data[0] + world.data[2].data[3] * proj.data[3].data[0];
	clip[9] = world.data[2].data[0] * proj.data[0].data[1] + world.data[2].data[1] * proj.data[1].data[1] + world.data[2].data[2] * proj.data[2].data[1] + world.data[2].data[3] * proj.data[3].data[1];
	clip[10] = world.data[2].data[0] * proj.data[0].data[2] + world.data[2].data[1] * proj.data[1].data[2] + world.data[2].data[2] * proj.data[2].data[2] + world.data[2].data[3] * proj.data[3].data[2];
	clip[11] = world.data[2].data[0] * proj.data[0].data[3] + world.data[2].data[1] * proj.data[1].data[3] + world.data[2].data[2] * proj.data[2].data[3] + world.data[2].data[3] * proj.data[3].data[3];

	clip[12] = world.data[3].data[0] * proj.data[0].data[0] + world.data[3].data[1] * proj.data[1].data[0] + world.data[3].data[2] * proj.data[2].data[0] + world.data[3].data[3] * proj.data[3].data[0];
	clip[13] = world.data[3].data[0] * proj.data[0].data[1] + world.data[3].data[1] * proj.data[1].data[1] + world.data[3].data[2] * proj.data[2].data[1] + world.data[3].data[3] * proj.data[3].data[1];
	clip[14] = world.data[3].data[0] * proj.data[0].data[2] + world.data[3].data[1] * proj.data[1].data[2] + world.data[3].data[2] * proj.data[2].data[2] + world.data[3].data[3] * proj.data[3].data[2];
	clip[15] = world.data[3].data[0] * proj.data[0].data[3] + world.data[3].data[1] * proj.data[1].data[3] + world.data[3].data[2] * proj.data[2].data[3] + world.data[3].data[3] * proj.data[3].data[3];

	// This will extract the LEFT side of the frustum.
	result.planes[1].normal.data[0] = clip[3] - clip[0];
	result.planes[1].normal.data[1] = clip[7] - clip[4];
	result.planes[1].normal.data[2] = clip[11] - clip[8];
	result.planes[1].distance = clip[15] - clip[12];

	NormalizePlane(result.planes[1]);

	// This will extract the RIGHT side of the frustum.
	result.planes[0].normal.data[0] = clip[3] + clip[0];
	result.planes[0].normal.data[1] = clip[7] + clip[4];
	result.planes[0].normal.data[2] = clip[11] + clip[8];
	result.planes[0].distance = clip[15] + clip[12];

	NormalizePlane(result.planes[0]);

	// This will extract the BOTTOM side of the frustum.
	result.planes[2].normal.data[0] = clip[3] + clip[1];
	result.planes[2].normal.data[1] = clip[7] + clip[5];
	result.planes[2].normal.data[2] = clip[11] + clip[9];
	result.planes[2].distance = clip[15] + clip[13];

	NormalizePlane(result.planes[2]);

	// This will extract the TOP side of the frustum.
	result.planes[3].normal.data[0] = clip[3] - clip[1];
	result.planes[3].normal.data[1] = clip[7] - clip[5];
	result.planes[3].normal.data[2] = clip[11] - clip[9];
	result.planes[3].distance = clip[15] - clip[13];

	NormalizePlane(result.planes[3]);

	// This will extract the BACK side of the frustum.
	result.planes[4].normal.data[0] = clip[3] + clip[2];
	result.planes[4].normal.data[1] = clip[7] + clip[6];
	result.planes[4].normal.data[2] = clip[11] + clip[10];
	result.planes[4].distance = clip[15] + clip[14];

	NormalizePlane(result.planes[4]);

	// This will extract the FRONT side of the frustum.
	result.planes[5].normal.data[0] = clip[3] - clip[2];
	result.planes[5].normal.data[1] = clip[7] - clip[6];
	result.planes[5].normal.data[2] = clip[11] - clip[10];
	result.planes[5].distance = clip[15] - clip[14];

	NormalizePlane(result.planes[5]);
	
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
	//float deg = angle / M_PI * 180;
	//vec3 v0(sin(angle), 0, -cos(angle));
	
	float roll_angle = -atan2f(ct_rel[0], ct_rel[1]);
	//float roll_deg = roll_angle / M_PI * 180;
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
	
	for(int i = 0; i < 4; i++) {
		ASSERT(angle_to_pixel_poly.data[i] != 0);
	}
	
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
