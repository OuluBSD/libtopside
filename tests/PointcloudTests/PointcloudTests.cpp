#include <Pointcloud/Pointcloud.h>
using namespace TS;


int CalcLens();


CONSOLE_APP_MAIN {
	//MemoryBreakpoint(17450);
	
	SetCoutLog();
	
	CalcLens();
	
	{
		float eye_dist = 0.068;
		vec3 pt(0,0,-1);
		vec3 eye(eye_dist/2,0,0);
		vec3 out;
		
		bool b = CalculateStereoTarget(
			(pt + eye).GetNormalized(),
			(pt - eye).GetNormalized(),
			eye_dist,
			out);
		DUMP(out);
		ASSERT(b && IsClose(out, pt));
	}
	
	{
		float eye_dist = 0.068;
		vec3 pt(0,0,-1);
		vec3 eye(eye_dist/2,0,0);
		vec3 out;
		
		LensPoly lp;
		lp.SetAnglePixel(13.13f, 750.16f, 15.1442f, -35.6897f);
		lp.SetSize(Size(2048, 2048));
		vec3 l_local0 = (pt + eye).GetNormalized();
		vec3 r_local0 = (pt - eye).GetNormalized();
		vec3 l_local1 = lp.Unproject(lp.Project(l_local0));
		vec3 r_local1 = lp.Unproject(lp.Project(r_local0));
		ASSERT(IsClose(l_local0, l_local1));
		ASSERT(IsClose(r_local0, r_local1));
		
		bool b = CalculateStereoTarget(
			l_local1,
			r_local1,
			eye_dist,
			out);
		DUMP(out);
		ASSERT(b && IsClose(out, pt));
	}
	
	{
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
	
	{
		Octree o0, o1;
		o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		o1.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		int points = 500;
		float radius = 1;
		bool random_points = 1;
		
		#if 1
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
			OctreeNode* n = o0.GetAddNode(pos, 0);
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
		
		float yaw = 0;
		for(int i = 0; i < 100; i++) {
			float yaw_deg = yaw / M_PI * 180;
			LOG(i << ": " << yaw_deg);
			
			orient = AxesQuat(yaw,0,0);
			
			cam.SetWorld(pos, orient);
			cam.Render(o0, l_img, r_img);
			
			uncam.Unrender(l_img, r_img, o1);
			
			yaw += 0.1;
		}
		
	}
	
}
