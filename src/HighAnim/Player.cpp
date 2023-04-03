#include "HighAnim.h"

NAMESPACE_TOPSIDE_BEGIN



String AnimKeypointPlayer::ToString() const {
	String s;
	for(int i = 0; i < E_COUNT; i++) {
		s << "(" << idx[0][i] << "," << idx[1][i] << ")";
	}
	return s;
}

double AnimKeypointPlayer::GetFraction(double kpif, int i) const {
	ASSERT(i >= 0 && i < E_COUNT);
	int begin = idx[0][i];
	int end = idx[1][i];
	int range = end - begin;
	int kpi = (int)kpif;
	if (kpi < begin || !range)
		return 0;
	if (kpi > end)
		return 1;
	double a = kpif - begin;
	double d = a / (double)range;
	switch (curve[i]) {
		case TC_LINEAR:				break;
		case TC_SINUSOID:			d = (0.5 - 0.5 * FastCos(d * M_PI)); break;
		case TC_SINUSOID_LOWER:		d = (1.0 - FastCos(d * 0.5 * M_PI)); break;
		case TC_SINUSOID_HIGHER:	d = -FastCos((d * 0.5 + 0.5) * M_PI); break;
		default:					break;
	}
	return d;
}

TransformCurve AnimKeypointPlayer::GetCurve(ValueType t) const {
	AnimKeypoint::ChkVT(t);
	return curve[t];
}

double AnimKeypointPlayer::GetAngle(double kpi) const {
	double f = GetFraction(kpi, AnimKeypoint::E_ANGLE);
	return angle[0] * (1.0 - f) + angle[1] * f;
}

Point AnimKeypointPlayer::GetPosition(double kpi) const {
	double f = GetFraction(kpi, AnimKeypoint::E_POS);
	Point r;
	r.x = (int)(position[0].x * (1.0f - f) + position[1].x * f);
	r.y = (int)(position[0].y * (1.0f - f) + position[1].y * f);
	return r;
}

Point AnimKeypointPlayer::GetAnchor(double kpi) const {
	double f = GetFraction(kpi, AnimKeypoint::E_ANCHOR);
	Point r;
	r.x = (int)(anchor[0].x * (1.0 - f) + anchor[1].x * f);
	r.y = (int)(anchor[0].y * (1.0 - f) + anchor[1].y * f);
	return r;
}






void AnimObjectPlayer::Destruct() {
	ASSERT(parent);
	if (!parent)
		return;
	
	parent->o->RemoveChild(o);
	parent->Recompile();
}

void AnimObjectPlayer::Recompile(bool deep) {
	ASSERT(o);
	Index<int> rm_list;
	for(int i = 0; i < objs.GetCount(); i++)
		rm_list.Add(i);
	
	for (AnimObject& o : this->o->objs) {
		int obj_i = 0;
		bool found = false;
		for (AnimObjectPlayer& p : objs) {
			if (p.o == &o) {
				rm_list.RemoveKey(obj_i);
				found = true;
				if (deep)
					p.Recompile();
			}
			obj_i++;
		}
		if (!found) {
			AnimObjectPlayer& p = objs.Add();
			p.parent = this;
			p.SetObject(o);
			p.Compile();
		}
	}
	
	if (rm_list.GetCount())
		objs.Remove(rm_list.GetKeys());
	
}

void AnimObjectPlayer::Compile() {
	
	// Sub-objects
	objs.Clear();
	
	objs.SetCount(o->objs.GetCount());
	for(int i = 0; i < objs.GetCount(); i++) {
		AnimObjectPlayer& s = objs[i];
		s.parent = this;
		s.SetObject(o->objs[i]).Compile();
	}
	
	
	// Keypoints
	kps.Clear();
	
	kps.SetCount(o->kps.GetCount());
	auto src = o->kps.Begin();
	auto src_end = o->kps.End();
	
	static const int c = AnimKeypoint::E_COUNT;
	const AnimKeypoint* data[2][c];
	for(int i = 0; i < c; i++)
		data[0][i] = data[1][i] = &*src;
	int idx[2][c];
	memset(idx, 0, sizeof(idx));
	
	AnimKeypointPlayer* prev_dst = 0;
	for (AnimKeypointPlayer& dst : kps) {
		ASSERT(src != src_end);
		dst.kpi = src->idx;
		if (prev_dst)
			prev_dst->next_kpi = src->idx;
		
		// check if current src is enabled for E_
		bool update[c];
		int update_count = 0;
		for(int i = 0; i < c; i++) {
			bool& b = update[i];
			b = src->Is(i);
			if (b) {
				data[1][i] = data[0][i] = &*src;
				idx[1][i] = idx[0][i] = src->idx;
				update_count++;
			}
		}
		// update next if current have changed
		if (update_count) {
			auto next_src = src;
			ASSERT(next_src != src_end);
			next_src++;
			while (next_src != src_end) {
				for(int i = 0; i < c; i++) {
					bool& b = update[i];
					if (!b)
						continue;
					if (next_src->Is(i)) {
						data[1][i] = &*next_src;
						idx[1][i] = next_src->idx;
						b = false;
						update_count--;
						ASSERT(update_count >= 0);
					}
				}
				if (!update_count)
					break;
				next_src++;
			}
		}
		
		// update next...
		for(int i = 0; i < c; i++)
			dst.curve[i] = data[0][i]->curve[i];
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < c; j++)
				dst.idx[i][j] = idx[i][j];
			dst.angle[i]	= data[i][AnimKeypoint::E_ANGLE]->angle;
			dst.position[i]	= data[i][AnimKeypoint::E_POS]->position;
			dst.anchor[i]	= data[i][AnimKeypoint::E_ANCHOR]->anchor;
		}
		
		prev_dst = &dst;
		src++;
	}
	if (prev_dst)
		prev_dst->next_kpi = -1;
	
	//DUMPC(kps);
}

void AnimObjectPlayer::Paint(Draw& d, const AnimFrameHeader& f) {
	for (AnimObjectPlayer& sub : objs)
		sub.Paint(d, f);
	
	AnimKeypointPlayer* kp = FindCompiledKeypoint(f.kpi);
	ASSERT(kp);
	if (kp) {
		//LOG("AnimObjectPlayer::Paint: found " << kp->kpi);
		o->Paint(d, f, *kp);
	}
	else {
		//LOG("AnimObjectPlayer::Paint: not found");
	}
}

AnimKeypointPlayer* AnimObjectPlayer::FindCompiledKeypoint(int kpi) {
	AnimKeypointPlayer* prev = 0;
	for (AnimKeypointPlayer& kp : kps) {
		if (kpi < kp.kpi && prev)
			return prev;
		prev = &kp;
	}
	return prev;
}

AnimObjectPlayer* AnimObjectPlayer::FindObjectPlayer(AnimObject& o) {
	if (this->o == &o)
		return this;
	
	AnimObjectPlayer* r = 0;
	for (AnimObjectPlayer& p : objs)
		if ((r = p.FindObjectPlayer(o)))
			break;
	return r;
}





void AnimScenePlayer::Compile() {
	root.SetObject(s->GetRoot());
	root.Compile();
}

void AnimScenePlayer::Paint(Draw& d, const AnimFrameHeader& f) {
	root.Paint(d,f);
}

AnimObjectPlayer* AnimScenePlayer::FindObjectPlayer(AnimObject& o) {
	return root.FindObjectPlayer(o);
}






AnimPlayer::AnimPlayer() {
	Clear();
	
	
}
	
void AnimPlayer::Clear() {
	a = 0;
	time = 0;
	kpi = 0;
	scenes.Clear();
	actions.Clear();
	is_external_time = false;
	is_playing = false;
	is_first_playing_frame = false;
}

void AnimPlayer::Compile() {
	ASSERT(a);
	if (!a) return;
	
	scenes.Clear();
	
	scenes.SetCount(a->scenes.GetCount());
	for(int i = 0; i < scenes.GetCount(); i++)
		scenes[i].SetScene(a->scenes[i]).Compile();
	
}

void AnimPlayer::Recompile(AnimObject& o) {
	AnimObjectPlayer* p = FindObjectPlayer(o);
	ASSERT(p);
	if (!p) return;
	
	p->Recompile();
}

void AnimPlayer::UpdateInternalTime() {
	if (!is_external_time) {
		IncreaseTime(ts.Seconds());
	}
	ts.Reset();
	UpdateKeypointIndex();
}

void AnimPlayer::UpdateKeypointIndex() {
	kpi = (int)(time * a->GetKeysPerSecond());
	AnimScene& s = a->GetActiveScene();
	int s_len = s.GetLength();
	if (is_playing && kpi >= s_len) {
		if (s.IsRepeating()) {
			kpi = 0;
			time = 0;
			ts.Reset();
		}
		else {
			kpi = s_len-1;
			Stop();
			WhenSceneEnd();
			return;
		}
	}
	kpi = max(0, min(kpi, s_len-1));
}

void AnimPlayer::Update(double dt) {
	ASSERT(is_external_time);
	IncreaseTime(dt);
	UpdateKeypointIndex();
}

void AnimPlayer::IncreaseTime(double dt) {
	time += dt;
	int i = 0;
	Vector<int> rm_list;
	for (AnimAction& a : actions) {
		a.time += dt;
		if (a.duration > 0 && a.time >= a.duration) {
			DoAction(a);
			rm_list << i;
		}
	}
	
	actions.Remove(rm_list);
}

void AnimPlayer::DoAction(AnimAction& a) {
	if (a.type == AnimAction::ACB_REMOVE_OBJECT) {
		ASSERT(a.o0);
		AnimObjectPlayer* op = FindObjectPlayer(*a.o0);
		ASSERT(op);
		if (op /*&& op->parent*/) {
			op->Destruct();
			//op->parent->RemoveChild(op);
		}
	}
	else {
		ASSERT_(0, "invalid action type");
	}
	
	a.WhenStop();
}

AnimObjectPlayer* AnimPlayer::FindObjectPlayer(AnimObject& o) {
	AnimObjectPlayer* r = 0;
	for (AnimScenePlayer& s : scenes) {
		r = s.FindObjectPlayer(o);
		if (r)
			break;
	}
	return r;
}

AnimPlayer& AnimPlayer::SetExternalTime(bool b) {
	is_external_time = b;
	return *this;
}

void AnimPlayer::Play() {
	ASSERT(scenes.GetCount());
	if (scenes.IsEmpty())
		return;
	AnimScene& s = a->GetActiveScene();
	if (s.GetLength() > 0) {
		is_playing = true;
		is_first_playing_frame = true;
	}
	else {
		is_playing = false;
	}
}

void AnimPlayer::Stop() {
	is_playing = false;
}

void AnimPlayer::Data() {
	if (is_first_playing_frame) {
		is_first_playing_frame = false;
		ts.Reset();
	}
	else {
		if (!is_external_time)
			UpdateInternalTime();
	}
}

bool AnimPlayer::IsRunning() const {
	return is_playing;
}

void AnimPlayer::Paint(Draw& d) {
	AnimFrameHeader f;
	f.kpi = kpi;
	f.time = time;
	f.keypoints_per_second = a->GetKeysPerSecond();
	//LOG("AnimPlayer::Paint: kpi=" << kpi << ", time=" << time << ", kps=" << f.keypoints_per_second);
	
	for (AnimScenePlayer& s : scenes)
		s.Paint(d, f);
	
}

void AnimPlayer::AddTimedRemoveObject(int ms, AnimObject& o, Callback call_after) {
	AnimAction& a = actions.Add();
	a.type = AnimAction::ACB_REMOVE_OBJECT;
	a.o0 = &o;
	a.WhenStop = call_after;
	a.duration = ms * 0.001;
}


NAMESPACE_TOPSIDE_END
