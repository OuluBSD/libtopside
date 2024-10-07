#ifndef _TextLib_ExampleProcess_h_
#define _TextLib_ExampleProcess_h_


BEGIN_TEXTLIB_NAMESPACE


class ExampleProcess : public SolverBase {
	
public:
	enum {
		PHASE_GENERATE,
		PHASE_GENERATE_DETAILS,
		
		PHASE_COUNT,
	};
	
	Profile* p = 0;
	
	struct Task : Moveable<Task> {
		int year, category, year_i;
	};
	Vector<Task> tasks;
	
public:
	typedef ExampleProcess CLASSNAME;
	ExampleProcess();
	
	int GetPhaseCount() const override;
	int GetBatchCount(int phase) const override;
	int GetSubBatchCount(int phase, int batch) const override;
	void DoPhase() override;
	
	static ExampleProcess& Get(Profile& p);
	
private:
	void Generate();
	void GenerateDetails();
	
};


END_TEXTLIB_NAMESPACE


#endif
