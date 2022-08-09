#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


GeomStagedVideo::GeomStagedVideo() {
	
}

void GeomStagedVideo::Start() {
	Stop();
	flag.Start(1);
	Thread::Start(THISBACK(Process));
}

void GeomStagedVideo::Stop() {
	flag.Stop();
}

void GeomStagedVideo::Process() {
	
	int img_i = 0;
	while (flag.IsRunning()) {
		const char* stage_name;
		int next_stage = STAGE_END;
		
		ASSERT(position < uncam.frames.GetCount());
		if (position < 0 || position >= uncam.frames.GetCount())
			break;
		
		UncameraFrame& from = position > 0 ? uncam.frames[position-1] : uncam.incremental;
		UncameraFrame& to   = uncam.frames[position];
		
		if (stage == STAGE_IMAGES_DIRECTORY) {
			stage_name = "image loading";
			next_stage = STAGE_DESCRIPTORS;
			
			String filepath = AppendFileName(directory, IntStr(position) + ".jpg");
			LOG("Loading " << filepath);
			Image img = StreamRaster::LoadFileAny(filepath);
			
			Size sz = img.GetSize();
			Size single_sz(sz.cx / 2, sz.cy);
			
			Image l_img, r_img;
			to.l_img = Crop(img, RectC(           0, 0, single_sz.cx, single_sz.cy));
			to.r_img = Crop(img, RectC(single_sz.cx, 0, single_sz.cx, single_sz.cy));
			
			to.l_dimg.SetResolution(single_sz);
			to.r_dimg.SetResolution(single_sz);
			
			// Resolution: 1 / (1 << __3__) = 0.125 meters
			// Size: 1 << __8__ = 256x256x256 meters
			to.otree.Initialize(-3, 8);
		}
		else if (stage == STAGE_DESCRIPTORS) {
			stage_name = "keypoints & descriptors";
			next_stage = STAGE_STEREO_KEYPOINTS;
			
			orb.SetInput(to.l_img);
			int lc = orb.DetectKeypoints(to.l_dimg, point_limit);
			orb.SetInput(to.r_img);
			int rc = orb.DetectKeypoints(to.r_dimg, point_limit);
			
			//DUMP(to.l_dimg); DUMP(to.r_dimg);
		}
		else if (stage == STAGE_STEREO_KEYPOINTS) {
			stage_name = "stereo keypoints";
			next_stage = STAGE_PROCESS_MESH;
			
			uncam.StageStereoKeypoints(from, to);
			
		}
		else if (stage == STAGE_PROCESS_MESH) {
			stage_name = "process mesh";
			next_stage = STAGE_SOLVE_TRANSFORM;
			
			uncam.ProcessTriangles(to);
			
		}
		else if (stage == STAGE_SOLVE_TRANSFORM) {
			stage_name = "solve transform";
			next_stage = STAGE_PROCESS_TRANSFORM;
			
			uncam.SolveTransform(from, to);
			
		}
		else if (stage == STAGE_PROCESS_TRANSFORM) {
			stage_name = "process transform";
			next_stage = STAGE_END;
			
			uncam.StageProcessTransform(from, to);
			
		}
			
		position++;
		if (position >= video_length) {
			stage = next_stage;
			position = 0;
			LOG("GeomStagedVideo: " << String(stage_name) << " took " << ts.ToString());
			ts.Reset();
			if (next_stage == STAGE_END)
				break;
		}
	}
	
	LOG("GeomStagedVideo: finished");
	
	flag.DecreaseRunning();
}

void GeomStagedVideo::LoadDirectory(String dir, int fps, String name) {
	GeomVideo::LoadDirectory(dir, fps, name);
	video_length = min(video_length, 10);
	uncam.frames.SetCount(video_length);
	stage = STAGE_IMAGES_DIRECTORY;
	Start();
}

void GeomStagedVideo::SetWmrCamera() {
	eye_dist = 0.12;
	uncam.SetAnglePixel(17.4932f, 153.022f, 175.333f, -25.7489f);
	uncam.SetEyeDistance(eye_dist);
	uncam.SetYLevelHeight(10);
	uncam.SetEyeOutwardAngle(DEG2RAD(35.50));
	uncam.SetDistanceLimit(128); // max 256, lower is stricter
}

	 
void GeomStagedVideo::Update(double dt) {
	
}


NAMESPACE_TOPSIDE_END
