//$ class TopWindow {

private:
	TS::Ecs::CoreWindow* cw = NULL;
	int id;
	
	
	void CreateCoreWindow();
	void UpdateFromTransform2D();
	
public:
	void Init(TS::Ecs::CoreWindow* cw, int id);
	
	TS::Ecs::CoreWindow* GetWindow() const {return cw;}
	
	
//$ };
