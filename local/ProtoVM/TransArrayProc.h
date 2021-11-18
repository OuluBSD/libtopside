#ifndef _ProtoVM_TransArrayProc_h_
#define _ProtoVM_TransArrayProc_h_


typedef enum {
	OFF,
	SHORT_A,
	SHORT_B,
	TRANS_AB_A
} TrOpt;


struct DynTrans : Moveable<DynTrans> {
	
	
};

struct GridConf : Moveable<GridConf> {
	uint64 u64;
	
	
};

struct GridMem : Moveable<GridMem> {
	
	
};

struct Grid {
	Vector<DynTrans> grid;
	Vector<GridConf> confs;
	Vector<GridMem> mem;
	
};

struct GridProgrammer {
	Grid& g;
	
	GridProgrammer(Grid& g) : g(g) {}
	
	void SetBlockIn(int block_x, int block_y, int line);
	void SetLine(int block_x, int block_y, int line, int ch_in0, int ch_in1, int ch_out0);
};

struct MemoryProgrammer {
	Grid& g;
	
	MemoryProgrammer(Grid& g) : g(g) {}
	
	void SetBit(int block_x, int block_y, int line, bool value=true);
	
};

struct TransArrayProc {
	Grid grid;
	int iter = 0;
	int test = -1;
	
	
public:
	
	
	void InitTest(int i);
	void Tick();
	
};


#endif
