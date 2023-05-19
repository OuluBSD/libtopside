#ifndef _Edit3D_Remote_h_
#define _Edit3D_Remote_h_

NAMESPACE_TOPSIDE_BEGIN


class RemoteExchange {
	GeomProject* prj = 0;
	GeomWorldState* state = 0;
	GeomAnim* anim = 0;
	GeomStagedVideo* video = 0;
	
	bool data_sync = false;
	bool keypoint_sync = false;
	
	
	void SyncData(const GeomObjectState& o);
	void SyncEntity(const GeomObjectState& o);
	
public:
	typedef RemoteExchange CLASSNAME;
	RemoteExchange();
	
	void SetTarget(GeomProject& p, GeomWorldState& s, GeomAnim& a, GeomStagedVideo& v);
	void SetRequireAllSync();
	void SetRequireDataSync();
	void SetRequireKeypointSync();
	
	bool Update();
	
	
	
	GeomSerializer write, read;
	
};

NAMESPACE_TOPSIDE_END

#endif
