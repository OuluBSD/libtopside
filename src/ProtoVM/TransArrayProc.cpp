#include "ProtoVM.h"


void Grid::SetSize(int w, int h, int mem) {
	sz = Size(w,h);
	int area = sz.GetArea();
	grid.SetCount(area);
	this->mem.SetCount(mem);
	
}

void Grid::Tick() {
	for (DynTrans& t : grid) {
		if (t.mem_in < 0 || t.mem_out < 0)
			continue;
		GridMem& mem_in = this->mem[t.mem_in];
		GridMem& mem_out = this->mem[t.mem_out];
		
		for(int i = 0; i < LINE_COUNT; i++)
			t.lines[i].Reset();
		
		for(int i = 0; i < LINE_COUNT-1; i++) {
			DynLine& line = t.lines[i];
			DynLine& next_line = t.lines[i+1];
			for(int j = 0; j < ITEM_COUNT; j++) {
				DynItem& from = line.items[j];
				DynItem& to = next_line.items[j];
				
				bool from_value = 0;
				if (line.mem_in)
					from_value = mem_in.u64 & (1ULL << i);
				
				// DynLine -> ch values
				TODO
			}
		}
		TODO
	}
}

void GridProgrammer::SetBlockIn(int block_x, int block_y, int line) {
	int j = g.GetPos(block_x, block_y);
	DynTrans& t = g.grid[j];
	ASSERT(line >= 0 && line < LINE_COUNT);
	t.lines[line].mem_in = true;
}

void GridProgrammer::SetBlockMem(int block_x, int block_y, int mem_in, int mem_out) {
	int j = g.GetPos(block_x, block_y);
	DynTrans& t = g.grid[j];
	t.mem_in = mem_in;
	t.mem_out = mem_out;
}

void GridProgrammer::SetLine(int block_x, int block_y, int line, int i, int ch_in0, int ch_in1, int ch_out0) {
	int j = g.GetPos(block_x, block_y);
	DynTrans& t = g.grid[j];
	ASSERT(line >= 0 && line < LINE_COUNT);
	DynLine& l = t.lines[line];
	DynItem& in0 = l.Get(ch_in0, i);
	in0.ch_out = ch_out0;
	in0.trans_in = ch_in1;
}

void MemoryProgrammer::SetBit(int block_x, int block_y, int line, bool value) {
	int j = g.GetPos(block_x, block_y);
	GridMem& mem = g.mem[g.GetPos(block_x, block_y)];
	if (value)
		mem.u64 |= 1ULL << line;
	else
		mem.u64 &= ~(1ULL << line);
}


void TransArrayProc::InitTest(int i) {
	test = i;
	
	if (test == 0) {
		grid.SetSize(1,1, 2);
		GridProgrammer prog(grid);
		prog.SetBlockMem(0,0, 0,1);
		prog.SetBlockIn(0,0, 0); // connect block(0,0) line 0 channel in (from block (-1,0))
		prog.SetLine(0,0, 0,0, 0,1,2); // In block(0,0) and line 0: connect ch0 to ch2 with ch1 as trans amp
		prog.SetLine(0,0, 1,0, 0,1,0);
		 
		
		
	}
	else Panic("Invalid test id");
	
}

void TransArrayProc::Tick() {
	if (test >= 0) {
		if (test == 0) {
			if (iter == 0) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(0,0,0, true); // set block(-1,0) ch0 value true
				// -> AND output false
			}
			else if (iter == 1) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(0,0,1, true);
				// -> AND output false
			}
			else if (iter == 1) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(0,0,0, true);
				mprog.SetBit(0,0,1, true);
				// -> AND output false
			}
		}
	}
	
	grid.Tick();
	
	TODO
	
	iter++;
}
