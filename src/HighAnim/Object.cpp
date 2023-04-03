#include "HighAnim.h"
#include <Geometry/Geometry.h>

NAMESPACE_TOPSIDE_BEGIN



AnimKeypoint::AnimKeypoint() {
	Clear();
}

void AnimKeypoint::Clear() {
	idx = 0;
	memset(curve, 0, sizeof(curve));
	angle = 0;
	anchor.x = anchor.y = 0;
	position.x = position.y = 0;
	enabled_mask = 0;
}





AnimObject::AnimObject() {
	Clear();
}

void AnimObject::Clear() {
	kps.Clear();
	objs.Clear();
	type = V_VOID;
	fnt_h = 0;
	anim_len = 0;
	
	RealizeKeypoint();
}

void AnimObject::RealizeKeypoint() {
	if (kps.IsEmpty()) {
		AnimKeypoint& kp = kps.Add();
		kp.idx = 0;
	}
}

void AnimObject::RemoveChild(AnimObject* o) {
	int i = 0;
	for (AnimObject& s : objs) {
		if (&s == o) {
			objs.Remove(i);
			return;
		}
		i++;
	}
	ASSERT_(0, "child not found");
}


AnimObject& AnimObject::SetText(String s, int fnt_h, Color clr) {
	type = V_TEXT;
	str = s;
	this->fnt_h = fnt_h;
	this->clr = clr;
	return *this;
}

AnimObject& AnimObject::SetPolygon(Color clr) {
	type = V_POLYGON;
	this->clr = clr;
	return *this;
}

AnimObject& AnimObject::SetLength(int i) {
	i = max(1, i);
	anim_len = i;
	return *this;
}

AnimObject& AnimObject::SetAnchorPointAverage() {
	AnimKeypoint& kp = kps[0];
	ASSERT(kp.idx == 0);
	if (pts.IsEmpty()) {
		kp.SetAnchor(Point(0,0));
	}
	else {
		Point pt(0,0);
		for (const Point& p : pts)
			pt += p;
		pt /= pts.GetCount();
		kp.SetAnchor(pt);
	}
	return *this;
}

AnimObject& AnimObject::SetPosition(Point p) {
	AnimKeypoint& kp = kps[0];
	ASSERT(kp.idx == 0);
	kp.SetPosition(p);
	return *this;
}

AnimKeypoint& AnimObject::GetAddKeypoint(int idx) {
	int i = 0;
	for (AnimKeypoint& k : kps) {
		if (k.idx == idx)
			return k;
		if (k.idx > idx) {
			AnimKeypoint& kp = kps.Insert(i);
			kp.idx = idx;
			return kp;
		}
		i++;
	}
	AnimKeypoint& kp = kps.Add();
	kp.idx = idx;
	return kp;
}

void AnimObject::Paint(Draw& d, const AnimFrameHeader& f, const AnimKeypointPlayer& kp) {
	
	if (type == V_VOID)
		return;
	
	double kpif = f.time * (double)f.keypoints_per_second;
	double angle = kp.GetAngle(kpif);
	Point pos = kp.GetPosition(kpif);
	Point anchor = kp.GetAnchor(kpif);
	Point tl = pos - anchor;
	
	mat2 rot = Rotation2x2((float)angle);
	
	//LOG("AnimObject::Paint: angle=" << angle);
	
	if (type == V_TEXT) {
		Font fnt = SansSerif(fnt_h);
		d.DrawText(tl.x, tl.y, str, fnt, clr);
	}
	else if (type == V_POLYGON) {
		static thread_local Vector<Point> pts;
		pts.SetCount(this->pts.GetCount());
		auto it = pts.Begin();
		
		vec2 rotated_anchor = vec2 {(float)anchor.x, (float)anchor.y} * rot;
		vec2 rotated_tl = vec2 {(float)pos.x, (float)pos.y} - rotated_anchor;
		
		for (const Point& src_ : this->pts) {
			Point& dst = *it;
			Point rel = src_ - tl;
			
			vec2 rotated = vec2 {(float)rel.x, (float)rel.y} * rot;
			vec2 rotated_translated = rotated + rotated_tl;
			
			dst.x = (int)rotated_translated[0];
			dst.y = (int)rotated_translated[1];
			it++;
		}
		d.DrawPolygon(pts, clr);
	}
	else {
		ASSERT_(0, "invalid type");
	}
	
}


NAMESPACE_TOPSIDE_END
