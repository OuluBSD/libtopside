#ifndef _AccelCore_CompGroup_h_
#define _AccelCore_CompGroup_h_

NAMESPACE_TOPSIDE_BEGIN



class AccelComponentGroup : public RefScopeEnabler<AccelComponentGroup,AccelContextConnector> {
	RTTI_DECL_R0(AccelComponentGroup)
	COPY_PANIC(AccelComponentGroup);
	
public:
	LinkedList<AccelComponentRef> comps;
	LinkedList<ExchangePointRef> expts;
	Vector<uint32> gl_stages;
	
	LinkedList<TypeCls> group_classes;
	
	
public:
	
	
	AccelComponentGroup();
	bool				Open();
	void				Clear();
	void				CreatePackets();
	void				Close();
	void				CloseTemporary();
	void				FindComponents();
	void				UpdateCompFlags();
	AccelComponentRef	GetComponentById(int id) const;
	void				Add(AccelComponentRef r) {comps.FindAdd(r); UpdateCompFlags();}
	void				Remove(AccelComponentRef r) {comps.RemoveKey(r); UpdateCompFlags();}
	void				FindUniqueInputs(AcceleratorHeaderVector& v);
	bool				LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code);
	void				ConnectInputs(AcceleratorHeaderVector& v);
	void				UpdateBuffers();
	bool				CheckInputTextures();
	bool				IsLast(const AccelComponent* comp) const;
	
	template <class T> void AddContext() {group_classes.FindAdd(AsTypeCls<T>());}
	template <class T> bool HasContext() const {return HasContext(AsTypeCls<T>());}
	bool HasContext(TypeCls type) const {return group_classes.Find(type) != 0;}
	const LinkedList<TypeCls>& GetGroupClasses() const {return group_classes;}
	
#if HAVE_OPENGL
	void				Ogl_ProcessStage(AccelComponentRef s, GLuint gl_stage);
	void				Ogl_ClearPipeline();
	void				Ogl_CreatePipeline();
#endif
	
};



NAMESPACE_TOPSIDE_END

#endif
