#include "Edit3D.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


SoftRendCtrl::SoftRendCtrl() {
	
}

void SoftRendCtrl::Paint(Draw& d) {
	DefaultPreFrame();
	
	
}

void SoftRendCtrl::DefaultPreFrame() {
	//ASSERT(rend);
	rend.SetClearValue(conf->background_clr, 255);
	rend.DrawDefault(fb);
	rend.SetSmoothShading();
	rend.SetDepthTest(true);
	rend.SetTriangleBacksideCulling(true);
	rend.SetDepthOrderLess(true);
	#if IS_NEGATIVE_Z
	rend.SetTriangleFrontsideCCW(true);
	#else
	rend.SetTriangleFrontsideCCW(false);
	#endif
	rend.SetViewport(GetSize());
}

void SoftRendCtrl::ProcessStage() {
	rend.SetDrawBuffers(GVar::COLOR0_EXT);
	
	RendVer(OnProcess);
	
	fb.ClearData(GVar::COLOR_BUFFER);
	fb.ClearData(GVar::DEPTH_BUFFER);
	//fb.ClearData(GVar::STENCIL_BUFFER);
	
	pipe.Begin();
	rend.SetTarget(pipe, fb);
	rend.Begin();
	
	ProgramState* prev_prog = 0;
	for (ModelState& m : data->models.GetValues()) {
		
		for (DataObject& o : m.objects) {
			if (!o.is_visible)
				continue;
			
			
			prog.BeginObject();
			
			
			o.Paint(m);
			
			prog.EndObject();
		}
	}
	
	Gfxrend.End();
	
}



NAMESPACE_TOPSIDE_END

#endif
