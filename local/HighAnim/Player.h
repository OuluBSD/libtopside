#ifndef _HighAnim_Player_h_
#define _HighAnim_Player_h_

NAMESPACE_TOPSIDE_BEGIN



struct AnimKeypointPlayer : Moveable<AnimKeypointPlayer> {
	static const int E_COUNT = AnimKeypoint::E_COUNT;
	using ValueType = AnimKeypoint::ValueType;
	
	int kpi, next_kpi;
	int idx[2][E_COUNT];
	
	TransformCurve curve[E_COUNT];
	double angle[2];
	Point position[2];
	Point anchor[2];
	
	
	String ToString() const;
	double GetFraction(double kpi, int i) const;
	TransformCurve GetCurve(ValueType t) const;
	double GetAngle(double kpi) const;
	Point GetPosition(double kpi) const;
	Point GetAnchor(double kpi) const;
	
};

class AnimObjectPlayer {
	AnimObjectPlayer* parent = this;
	Array<AnimObjectPlayer> objs;
	Vector<AnimKeypointPlayer> kps;
	AnimObject* o = 0;
	
public:
	AnimObjectPlayer& SetObject(AnimObject& o) {this->o = &o; return *this;}
	
	void Compile();
	void Recompile(bool deep=true);
	void Destruct();
	void Paint(Draw& d, const AnimFrameHeader& f);
	
	AnimKeypointPlayer* FindCompiledKeypoint(int kpi);
	AnimObjectPlayer* FindObjectPlayer(AnimObject& o);
	
};

class AnimScenePlayer {
	AnimObjectPlayer root;
	AnimScene* s = 0;
	
public:
	AnimScenePlayer& SetScene(AnimScene& s) {this->s = &s; return *this;}
	
	void Compile();
	void Paint(Draw& d, const AnimFrameHeader& f);
	AnimObjectPlayer* FindObjectPlayer(AnimObject& o);
	
};

class AnimPlayer {
	Array<AnimScenePlayer> scenes;
	Animation* a = 0;
	TimeStop ts;
	double time = 0;
	int kpi = 0;
	bool is_external_time = false;
	bool is_playing = false;
	bool is_first_playing_frame = false;
	
	Vector<AnimAction> actions;
	
	
	void UpdateInternalTime();
	void UpdateKeypointIndex();
	void IncreaseTime(double dt);
	void DoAction(AnimAction& a);
	
	AnimObjectPlayer* FindObjectPlayer(AnimObject& o);
	
public:
	typedef AnimPlayer CLASSNAME;
	AnimPlayer();
	
	AnimPlayer& SetAnimation(Animation& a) {Clear(); this->a = &a; return *this;}
	
	void Clear();
	void Compile();
	void Recompile(AnimObject& o);
	void Play();
	void Stop();
	void Data();
	void Update(double dt);
	void Paint(Draw& d);
	void AddTimedRemoveObject(int ms, AnimObject& o, Callback call_after=Callback());
	
	AnimPlayer& SetExternalTime(bool b=true);
	
	
	
	Callback WhenSceneEnd;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
