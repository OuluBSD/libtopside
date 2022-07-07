#include <Pointcloud/Pointcloud.h>
using namespace TS;


int CalcLens();


CONSOLE_APP_MAIN {
	//MemoryBreakpoint(17450);
	
	SetCoutLog();
	
	CalcLens();
	
	
	{
		Octree o0, o1;
		o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		o1.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
		
		int points = 500;
		float radius = 3;
		bool random_points = 1;
		
		#if 1
		{
			vec3 pos = AxesDir(0, 0) * radius;
			//vec3 pos = AxesDir(0, M_PI*0.1) * radius;
			OctreeNode* n = o0.GetAddNode(pos, 0);
			Pointcloud::Point& p = n->Add<Pointcloud::Point>();
			p.SetPosition(pos);
		}
		#else
		
		for(int i = 0; i < points; i++) {
			float yaw, pitch;
			if (random_points) {
				yaw = Randomf() * M_PI * 2;
				pitch = (Randomf() * 2 - 1) * (M_PI / 2);
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
		
		float yaw = 0;
		for(int i = 0; i < 100; i++) {
			orient = AxesQuat(yaw,0,0);
			
			cam.SetWorld(pos, orient);
			cam.Render(o0, l_img, r_img);
			
			uncam.Unrender(l_img, r_img, o1);
			
			yaw += 0.1;
		}
		
	}
	
	
}
