#include <Pointcloud/Pointcloud.h>
using namespace TS;


int CalcLens();


CONSOLE_APP_MAIN {
	//MemoryBreakpoint(17450);
	
	SetCoutLog();
	
	CalcLens();
	
	dword tests = 0xFFFFFFFF;
	
	//tests = 1 << 4;
	
	
	if (tests & (1 << 0)) {
		float eye_dist = 0.068;
		axes2s eyes = LookAtStereoAngles(eye_dist, VEC_FWD);
		axes2s out;
		bool b = CalculateStereoTarget(
			eyes,
			eye_dist,
			out);
		DUMP(out);
		ASSERT(b && IsClose(out, VEC_FWD));
	}
	
	if (tests & (1 << 1)) {
		float eye_dist = 0.068;
		axes2s eyes = LookAtStereoAngles(eye_dist, VEC_FWD);
		axes2 l, r;
		AxesStereoMono(eyes, l, r);
		
		LensPoly lp;
		lp.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		lp.SetSize(Size(2048, 2048));
		
		axes2 l1 = lp.Unproject(lp.Project(l));
		axes2 r1 = lp.Unproject(lp.Project(r));
		ASSERT(IsClose(l, l1));
		ASSERT(IsClose(r, r1));
	}
	TODO
	#if 0
	if (tests & (1 << 2)) {
		float eye_dist = 0.068;
		vec3 pt(0,0,-1);
		vec3 eye(eye_dist/2,0,0);
		vec3 out;
		
		mat4 orient = AxesMat(M_PI/4,0,0);
		mat4 l_world = Translate( eye) * orient;
		mat4 r_world = Translate(-eye) * orient;							//!!!!
		
		LensPoly lp;
		lp.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		lp.SetSize(Size(2048, 2048));
		
		vec3 l_local0 = (pt.Embed() * l_world).Splice().GetNormalized();
		vec3 r_local0 = (pt.Embed() * r_world).Splice().GetNormalized();
		vec3 l_local1 = lp.Unproject(lp.Project(l_local0));
		vec3 r_local1 = lp.Unproject(lp.Project(r_local0));
		ASSERT(IsClose(l_local0, l_local1));
		ASSERT(IsClose(r_local0, r_local1));
		
		bool b = CalculateStereoTarget(
			l_local1,
			r_local1,
			eye_dist,
			out);
			
		out = (out.Embed() * orient.GetInverse()).Splice();					//!!!!
		
		DUMP(out);
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
		Octree o0, o1;
		o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		o1.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		int points = 500;
		float radius = 1;
		bool random_points = 1;
		#if 0
		{
			{
				vec3 pos = AxesDir(0, 0) * radius;
				OctreeNode* n = o0.GetAddNode(pos, 0);
				Pointcloud::Point& p = n->Add<Pointcloud::Point>();
				p.SetPosition(pos);
			}{
				vec3 pos = AxesDir(M_PI/8, 0) * radius;
				OctreeNode* n = o0.GetAddNode(pos, 0);
				Pointcloud::Point& p = n->Add<Pointcloud::Point>();
				p.SetPosition(pos);
			}
		}
		#elif 1
		points = 64;
		{
			float step = (M_PI*2) / points;
			float yaw = 0, pitch = M_PI/16;
			for(int i = 0; i < points; i++) {
				//vec3 pos = AxesDir(yaw, 0) * radius;
				vec3 pos = AxesDir(yaw, pitch) * radius;
				//vec3 pos = AxesDir(yaw, pitch * (i % 2 ? -1 : +1)) * radius;
				//vec3 pos = AxesDir(yaw, (Randomf() * 2 - 1) * pitch) * radius;
				OctreeNode* n = o0.GetAddNode(pos, -3);
				Pointcloud::Point& p = n->Add<Pointcloud::Point>();
				p.SetPosition(pos);
				LOG(i << ": " << pos.ToString() + ": " + HexStr(n));
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
			
			LOG(pos.ToString() + ": " + HexStr(n));
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
		
		/*uncam.dbg = true;
		uncam.dbg_l_local = vec3(+eye_dist/2,0,-1);
		uncam.dbg_r_local = vec3(+eye_dist/2,0,-1);*/
		
		float yaw = 0, sideways = 0;
		float sidways_dist = 0.25;
		for(int i = 0; i < 100; i++) {
			float yaw_deg = yaw / M_PI * 180;
			LOG(i << ": " << yaw_deg << ", " << sin(sideways));
			
			orient = AxesQuat(yaw,0,0);
			
			//vec3 pos0 = pos + vec3(sin(sideways) * sidways_dist, 0, 0);
			vec3 pos0 = pos + vec3(0, 0, sin(sideways) * sidways_dist);
			//vec3 pos0 = pos + vec3(sin(sideways) * sidways_dist, 0, cos(sideways) * sidways_dist);
			
			cam.SetWorld(pos0, orient);
			cam.Render(o0, l_img, r_img);
			
			//LOG("DESCRIPTOR COUNT: " << l_img.GetDescriptors().GetCount() << ", " << r_img.GetDescriptors().GetCount());
			
			uncam.Unrender(l_img, r_img, o1);
			
			if (i) yaw += 0.1;
			//sideways += 0.1;
		}
		
	}
	#endif
}
