#include <Pointcloud/Pointcloud.h>
using namespace TS;


int CalcLens();


CONSOLE_APP_MAIN {
	//MemoryBreakpoint(17450);
	
	SetCoutLog();
	
	CalcLens();
	return;
	
	dword tests = 0xFFFFFFFF;
	
	tests = 1 << 6;
	
	
	if (tests & (1 << 0)) {
		float eye_dist = 0.068;
		axes2s eyes = LookAtStereoAngles(eye_dist, VEC_FWD);
		axes2s out;
		bool b = CalculateStereoTarget(
			eyes,
			eye_dist,
			out);
		//DUMP(out);
		ASSERT(b && IsClose(out, VEC_FWD));
	}
	
	if (tests & (1 << 1)) {
		float eye_dist = 0.068;
		axes2s eyes = LookAtStereoAngles(eye_dist, VEC_FWD);
		axes2 l, r;
		AxesStereoMono(eyes, l, r);
		// or just: eyes = LookAtStereoAngles(eye_dist, VEC_FWD, l, r);
		
		LensPoly lp;
		lp.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		lp.SetSize(Size(2048, 2048));
		
		axes2 l1 = lp.Unproject(lp.Project(l));
		axes2 r1 = lp.Unproject(lp.Project(r));
		ASSERT(IsClose(l, l1));
		ASSERT(IsClose(r, r1));
	}
	
	if (tests & (1 << 2)) {
		float eye_dist = 0.068;
		
		vec3 pt = VEC_FWD;
		vec3 up = VEC_UP;
		vec3 eye;
		axes2 l, r;
		axes2s eyes = LookAtStereoAngles(eye_dist, pt, l, r); // eye must be at origo
		mat4 lookat = LookAt(eye, pt, up);
		
		LensPoly lp;
		lp.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		lp.SetSize(Size(2048, 2048));
		
		axes2 l1 = lp.Unproject(lp.Project(l));
		axes2 r1 = lp.Unproject(lp.Project(r));
		ASSERT(IsClose(l, l1));
		ASSERT(IsClose(r, r1));
		
		vec3 out;
		bool b = CalculateStereoTarget(
			eyes,
			eye_dist,
			out);
		
		
		out = (out.Embed() * lookat.GetInverse()).Splice();
		
		//DUMP(out);
		ASSERT(b && IsClose(out, pt));
	}
	
	if (tests & (1 << 3)) {
		Octree o;
		o.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		int points = 16;
		float radius = 1;
		bool random_points = 1;
		{
			float step = (M_PI*2) / points;
			float yaw = 0, pitch = 0;//M_PI/16;
			for(int i = 0; i < points; i++) {
				vec3 pos = AxesDir(yaw, (Randomf() * 2 - 1) * pitch) * radius;
				OctreeNode* n = o.GetAddNode(pos, -3);
				Pointcloud::Point& p = n->Add<Pointcloud::Point>();
				p.SetPosition(pos);
				//LOG(i << ": " << pos.ToString() + ": " + HexStr(n));
				yaw += step;
			}
		}
		Camera cam;
		cam.SetResolution(Size(1440, 1440));
		cam.SetPerspective(90,1,0.1,10);
		
		float yaw = 0;
		float step = (M_PI*2) / points;
		int min_count = INT_MAX, max_count = 0;
		for(int i = 0; i < points * 3; i++) {
			cam.SetWorld(vec3(0,0,0), AxesQuat(yaw,0,0));
			Frustum f = cam.GetFrustum();
			auto iter = const_cast<Octree&>(o).GetIterator(f);
			int count = 0;
			while (iter) {
				for (auto& one_obj : iter->objs) {
					count++;
				}
				iter++;
			}
			min_count = min(min_count, count);
			max_count = max(max_count, count);
			//LOG(i << ": " << count);
			yaw += step / 3;
		}
		ASSERT(min_count == max_count-1);
	}
	
	if (tests & (1 << 4)) {
		{
			vec3 x, y, z;
			GetPrincipalAxes(VEC_FWD, VEC_RIGHT, x, y, z);
			ASSERT(IsClose(x, VEC_RIGHT));
			ASSERT(IsClose(y, VEC_UP));
			ASSERT(IsClose(z, VEC_FWD));
		}
		{
			vec3 x, y, z;
			GetPrincipalAxes(VEC_RIGHT, -VEC_FWD, x, y, z);
			ASSERT(IsClose(x, -VEC_FWD));
			ASSERT(IsClose(y, VEC_UP));
			ASSERT(IsClose(z, VEC_RIGHT));
		}
		{
			vec3 x, y, z;
			GetPrincipalAxes(VEC_UP, VEC_RIGHT, x, y, z);
			ASSERT(IsClose(x, VEC_RIGHT));
			ASSERT(IsClose(y, -VEC_FWD));
			ASSERT(IsClose(z, VEC_UP));
		}
		{
			vec3 x, y, z;
			GetPrincipalAxes(-VEC_FWD, VEC_LEFT, x, y, z);
			ASSERT(IsClose(x, VEC_LEFT));
			ASSERT(IsClose(y, VEC_UP));
			ASSERT(IsClose(z, -VEC_FWD));
		}
		
		vec3 t = VEC_FWD;
		vec3 a0 = VEC_UP;
		vec3 a1 = VecMul(ZRotation(M_PI*2/3), a0);
		vec3 a2 = VecMul(ZRotation(M_PI*2/3), a1);
		{
			mat4 out;
			CalculateTriangleChange(a0,a1,a2,a0,a1,a2,out);
			ASSERT(IsClose(out, Identity<mat4>()));
		}
		{
			// rotate right
			mat4 m = YRotation(-M_PI/2);
			vec3 b0 = VecMul(m, a0);
			vec3 b1 = VecMul(m, a1);
			vec3 b2 = VecMul(m, a2);
			
			mat4 out;
			CalculateTriangleChange(a0,a1,a2,b0,b1,b2,out);
			vec3 c0 = VecMul(out, a0);
			vec3 c1 = VecMul(out, a1);
			vec3 c2 = VecMul(out, a2);
			ASSERT(IsClose(b0, c0));
			ASSERT(IsClose(b1, c1));
			ASSERT(IsClose(b2, c2));
		}
		{
			vec3 b0 = a0 + t;
			vec3 b1 = a1 + t;
			vec3 b2 = a2 + t;
			mat4 out;
			CalculateTriangleChange(a0,a1,a2,b0,b1,b2,out);
			vec3 c0 = VecMul(out, a0);
			vec3 c1 = VecMul(out, a1);
			vec3 c2 = VecMul(out, a2);
			ASSERT(IsClose(b0, c0));
			ASSERT(IsClose(b1, c1));
			ASSERT(IsClose(b2, c2));
		}
		{
			mat4 m = YRotation(-M_PI/2);
			vec3 b0 = VecMul(m, a0);
			vec3 b1 = VecMul(m, a1);
			vec3 b2 = VecMul(m, a2);
			mat4 out;
			CalculateTriangleChange(a0,a1,a2,b0,b1,b2,out);
			vec3 c0 = VecMul(out, a0);
			vec3 c1 = VecMul(out, a1);
			vec3 c2 = VecMul(out, a2);
			ASSERT(IsClose(b0, c0));
			ASSERT(IsClose(b1, c1));
			ASSERT(IsClose(b2, c2));
		}
		{
			vec3 aa0 = a0 + t;
			vec3 aa1 = a1 + t;
			vec3 aa2 = a2 + t;
			mat4 m = YRotation(-M_PI/2);
			vec3 bf = VecMul(m, VEC_FWD + t) + t;
			vec3 bo = VecMul(m, vec3(0,0,0) + t) + t;
			vec3 b0 = VecMul(m, aa0) + t;
			vec3 b1 = VecMul(m, aa1) + t;
			vec3 b2 = VecMul(m, aa2) + t;
			mat4 out;
			CalculateTriangleChange(aa0,aa1,aa2,b0,b1,b2,out);
			vec3 c0 = VecMul(out, aa0);
			vec3 c1 = VecMul(out, aa1);
			vec3 c2 = VecMul(out, aa2);
			ASSERT(IsClose(b0, c0));
			ASSERT(IsClose(b1, c1));
			ASSERT(IsClose(b2, c2));
		}
		{
			mat4 m = YRotation(-M_PI/2);
			vec3 aa0 = a0 + t*1.1;
			vec3 aa1 = a1 + t*1.2;
			vec3 aa2 = a2 + t*1.1;
			vec3 b0 = VecMul(m, aa0) + t * 0.9;
			vec3 b1 = VecMul(m, aa1) + t * 0.9;
			vec3 b2 = VecMul(m, aa2) + t * 0.9;
			mat4 out;
			CalculateTriangleChange(aa0,aa1,aa2,b0,b1,b2,out);
			vec3 c0 = VecMul(out, aa0);
			vec3 c1 = VecMul(out, aa1);
			vec3 c2 = VecMul(out, aa2);
			/*
			DUMP(b0);
			DUMP(c0);
			DUMP(b1);
			DUMP(c1);
			DUMP(b2);
			DUMP(c2);
			*/
			ASSERT(IsClose(b0, c0));
			ASSERT(IsClose(b1, c1));
			ASSERT(IsClose(b2, c2));
		}
	}
	
	if (tests & (1 << 5)) {
		Octree o0, o1;
		o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		o1.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		float radius = 1;
		bool random_points = 1;
		int points = 256;
		#if 1
		{
			float step = (M_PI*2) / points;
			float yaw = 0, pitch = M_PI/16;
			for(int i = 0; i < points; i++) {
				vec3 pos;
				switch (3) {
					case 0: pos = AxesDir(yaw, 0) * radius; break;
					case 1: pos = AxesDir(yaw, pitch) * radius; break;
					case 2: pos = AxesDir(yaw, pitch * (i % 2 ? -1 : +1)) * radius; break;
					case 3: pos = AxesDir(yaw, (Randomf() * 2 - 1) * pitch) * radius; break;
				}
				OctreeNode* n = o0.GetAddNode(pos, -3);
				Pointcloud::Point& p = n->Add<Pointcloud::Point>();
				p.SetPosition(pos);
				//LOG(i << ": " << pos.ToString() + ": " + HexStr(n));
				yaw += step;
			}
		}
		#else
		
		for(int i = 0; i < points; i++) {
			float yaw, pitch;
			if (random_points) {
				yaw = Randomf() * M_PI * 2;
				float f = (Randomf() * 2 - 1);
				pitch = f * (M_PI / 2);
			}
			else {
				float f = ((float)i / (float)points);
				yaw = f * M_PI * 2;
				pitch = fmodf(f * M_PI * 40, M_PI) - M_PI/2;
			}
			
			vec3 pos = AxesDir(yaw, pitch) * radius;
			OctreeNode* n = o0.GetAddNode(pos, -3);
			Pointcloud::Point& p = n->Add<Pointcloud::Point>();
			p.SetPosition(pos);
			//LOG(pos.ToString() + ": " + HexStr(n));
		}
		#endif
		
		Size res(1520,1080);
		
		VirtualStereoCamera cam;
		cam.SetResolution(res);
		
		// Fisheye lens camera with ~150 degrees from bottom left to top right
		// Values are relative to the resolution and physical lens angles.
		float fov = 150;
		float eye_dist = 0.068f;
		cam.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		
		vec3 pos(0, 0, 0);
		quat orient = AxesQuat(0,0,0);
		cam.SetPerspective(fov, 1.0, 0.1, 10.0);
		cam.SetEyeDistance(eye_dist);
		
		DescriptorImage l_img, r_img;
		l_img.SetResolution(res);
		r_img.SetResolution(res);
		
		VirtualStereoUncamera uncam;
		uncam.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		uncam.SetEyeDistance(eye_dist);
		uncam.SetDistanceLimit(0);
		
		float yaw = 0, sideways = 0;
		float sidways_dist = 0.25;
		for(int i = 0; i < 100; i++) {
			float yaw_deg = yaw / M_PI * 180;
			LOG(i << ": " << yaw_deg << ", " << sin(sideways));
			
			orient = AxesQuat(yaw,0,0);
			
			vec3 pos0;
			switch (0) {
				case 0: pos0 = pos + vec3(sin(sideways) * sidways_dist, 0, 0); break;
				case 1: pos0 = pos + vec3(0, 0, sin(sideways) * sidways_dist); break;
				case 2: pos0 = pos + vec3(sin(sideways) * sidways_dist, 0, cos(sideways) * sidways_dist); break;
			}
			
			cam.SetWorld(pos0, orient);
			cam.Render(o0, l_img, r_img);
			
			//LOG("DESCRIPTOR COUNT: " << l_img.GetDescriptors().GetCount() << ", " << r_img.GetDescriptors().GetCount());
			
			uncam.Unrender(l_img, r_img, o1);
			
			if (i) yaw += 0.1;
			sideways += 0.1;
		}
		
	}
	
	// WMR motion controller test
	if (tests & (1 << 6)) {
		WmrMotionControllerModel wmr_ctrl;
		WmrMotionControllerTracker wmr_tracker;
		Octree o0, o1;
		o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		
		TODO
	}
	
	// Fake HMD + controllers setup
	if (tests & (1 << 7)) {
		VrSystemTestGenerator gen;
		
		TODO
	}
	
}
