#ifndef _HighAnim_Animation_h_
#define _HighAnim_Animation_h_

NAMESPACE_TOPSIDE_BEGIN

class Animation {
	int keys_per_second = 4;
	
public:
	Array<AnimScene> scenes;
	int active_scene = 0;
	
	
public:
	typedef Animation CLASSNAME;
	Animation();
	
	void Clear();
	
	AnimScene& AddScene(String name);
	AnimScene& GetActiveScene() {return scenes[active_scene];}
	
	int GetKeysFromTime(double seconds);
	int GetKeysPerSecond() const {return keys_per_second;}
	
};


NAMESPACE_TOPSIDE_END

#endif
