#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


bool OverlapSystem::Initialize() {
	return true;
}

void OverlapSystem::Start() {
	
}

void OverlapSystem::Update(double dt) {
	
}

void OverlapSystem::Stop() {
	
}

void OverlapSystem::Uninitialize() {
	
}












Overlap::Overlap() {
	
}

void Overlap::Initialize() {
	auto sys = GetEntity().GetMachine().Get<OverlapSystem>();
	if (sys)
		sys->Add(this);
}

void Overlap::Uninitialize() {
	auto sys = GetEntity().GetMachine().Get<OverlapSystem>();
	if (sys)
		sys->Remove(this);
}



OverlapDetector::OverlapDetector() {
	
}

void OverlapDetector::Initialize() {
	
}

void OverlapDetector::Uninitialize() {
	
}





void CreateFlatOctreeEntityFromStringLevel(Rect r, EntityPoolRef parent, const Vector<String>& lines, const ArrayMap<int, EntityRef>& map_char_ents) {
	int width = r.Width();
	int height = r.Height();
	int w_2 = width / 2;
	int h_2 = height / 2;
	if (w_2 < 1 && h_2 < 1)
		return;
	
	if (width == 1 && height == 1) {
		if (r.top >= lines.GetCount() || r.left >= lines[r.top].GetCount())
			throw Exc("internal error");
		int cls = lines[r.top][r.left];
		int i = map_char_ents.Find(cls);
		if (i < 0)
			throw Exc("could not find class id");
		EntityRef ent = map_char_ents[i];
		Ref<OverlapSink> sink = ent->FindOverlapSink();
		if (!sink)
			throw Exc("class entity does not have OverlapSink interface");
		
		ASSERT(parent.IsEmpty());
		EntityRef item = parent->Create<DefaultOctreeNode>();
		OverlapDetector& detector = *item->Get<OverlapDetector>();
		Ref<OverlapSource> src = detector.AsOverlapSource();
		ASSERT(src);
		src->LinkManually(*sink);
	}
	else {
		int h = 2;
		if (h_2 < 1) {
			h_2 = 1;
			h = 1;
		}
		
		int w = 2;
		if (w_2 < 1) {
			w_2 = 1;
			w = 1;
		}
		
		ASSERT(parent.IsEmpty());
		for (int y = 0; y < h; y++) {
			String lstr = y == 0 ? "top" : "bottom";
			for (int x = 0; x < w; x++) {
				String rstr = x == 0 ? "left" : "right";
				String name = lstr + rstr;
				Rect r2 = RectC(
					r.left + x * w_2,
					r.top + y * h_2,
					w_2,
					h_2);
				EntityPoolRef child = parent->AddPool(name);
				CreateFlatOctreeEntityFromStringLevel(r2, child, lines, map_char_ents);
			}
		}
	}
}

void CreateOctreeEntityFromString(EntityPoolRef octree_root, String map_str, const ArrayMap<int, EntityRef>& map_char_ents) {
	try {
		Vector<String> lines = Split(map_str, "\n");
		if (lines.IsEmpty())
			throw Exc("No lines");
		int width = lines[0].GetCount();
		int depth = lines.GetCount();
		if (width < 2 || depth < 2)
			throw Exc("Too small resolution. At least 2x2 is expected");
		for(String& line : lines)
			if (line.GetCount() != width)
				throw Exc("Unexpected length in line");
		Rect r = RectC(0,0, width, depth);
		CreateFlatOctreeEntityFromStringLevel(r, octree_root, lines, map_char_ents);
		
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
}

NAMESPACE_OULU_END
