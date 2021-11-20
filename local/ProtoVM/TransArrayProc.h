#ifndef _ProtoVM_TransArrayProc_h_
#define _ProtoVM_TransArrayProc_h_


typedef enum {
	OFF,
	SHORT_A,
	SHORT_B,
	TRANS_AB_A
} TrOpt;


static const int LINE_COUNT = 8;
static const int CHANNEL_COUNT = 3;
static const int LINE_WIDTH = 3;
static const int ITEM_COUNT = CHANNEL_COUNT * LINE_WIDTH;


struct DynItem {
	char trans_in = -1;
	char ch_out = -1;
	
};

struct DynLine {
	ynItem items[ITEM_COUNT];
	bool mem_in = false;
	bool ch_values[CHANNEL_COUNT];
	
	int GetPos(int ch, int i) {ASSERT(ch < CHANNEL_COUNT && ch >= 0 && i >= 0 && i < LINE_WIDTH); return ch * LINE_WIDTH + i;}
	DynItem& Get(int ch, int i) {return items[GetPos(ch, i)];}
	
	void Reset() {
		for(int i = 0; i < CHANNEL_COUNT; i++)
			items[i] = false;
	}
};

struct DynTrans : Moveable<DynTrans> {
	
	DynLine lines[LINE_COUNT];
	int mem_in = -1;
	int mem_out = -1;
	
	
};

struct GridMem : Moveable<GridMem> {
	static_assert(LINE_COUNT <= sizeof(uint64)*8, "");
	
	uint64 u64 = 0;
	
};

struct Grid {
	Vector<DynTrans> grid;
	Vector<GridMem> mem;
	Size sz;
	
	
	int GetPos(int x, int y) {return x + y * sz.cx;}
	void SetSize(int w, int h, int mem);
	void Tick();
};

struct GridProgrammer {
	Grid& g;
	
	GridProgrammer(Grid& g) : g(g) {}
	
	void SetBlockIn(int block_x, int block_y, int line);
	void SetBlockMem(int block_x, int block_y, int mem_in, int mem_out);
	void SetLine(int block_x, int block_y, int line, int i, int ch_in0, int ch_in1, int ch_out0);
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
