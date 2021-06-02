//$ class TopWindow {

private:
	TS::CoreWindow* cw = NULL;
	int id;
	
public:
	void Init(TS::CoreWindow* cw, int id);
	
	TS::CoreWindow* GetWindow() const {return cw;}
	
	
//$ };
