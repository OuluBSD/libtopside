#ifndef _Local_Neural_h_
#define _Local_Neural_h_

NAMESPACE_TOPSIDE_BEGIN

struct VolumeData : Moveable<VolumeData> {
	int W = 0;
	int H = 0;
	int D = 0;
	int size = 0;
	Vector<double> d;
	
	
	void Init(int w, int h, int d) {
		W = w;
		H = h;
		D = d;
		size = W * H * D;
		this->d.SetCount(size);
	}
	void ToDepthVolume(VolumeData& out) const {
		out.Init(1, 1, W*H*D);
		for (int i = 0; i < size; i++)
			out.d[i] = d[i];
	}
	
	int GetPos(int x, int y, int z) const {
		ASSERT(x >= 0 && x < W && y >= 0 && y < H && z >= 0 && z < D);
		return ((x * H + y) * D + z);
	}
	
	void Set(int x, int y, int z, double value) {d[GetPos(x,y,z)] = value;}
	void Add(int x, int y, int z, double value) {d[GetPos(x,y,z)] += value;}
	void AddMax(int x, int y, int z, double value, double max) {double& v = d[GetPos(x,y,z)]; v = min(max, v+value);}
	double Get(int x, int y, int z) const {return d[GetPos(x,y,z)];}
};


struct Volume : Moveable<Volume> {
	int W = 0;
	int H = 0;
	int D = 0;
	int size = 0;
	Vector<double> d, g;
	
	
	Volume() {}
	Volume(int w, int h, int d) : W(w), H(h), D(d) {}
	Volume(const Volume& v) {*this = v;}
	
	void operator=(const Volume& s) {
		W = s.W;
		H = s.H;
		D = s.D;
		size = s.size;
		CopyHeapless(s.d, d);
		CopyHeapless(s.g, g);
	}
	void Serialize(Stream& s) {
		s % W % H % D % size % d % g;
	}
	void PostInit() {
		ASSERT(d.GetCount());
		W = 1;
		H = 1;
		D = d.GetCount();
		size = d.GetCount();
		g.SetCount(d.GetCount(), 0);
	}
	void Init(int w, int h, int d) {
		W = w;
		H = h;
		D = d;
		size = W * H * D;
		this->d.SetCount(size);
		this->g.SetCount(size);
		
		RandomGaussian& rand = GetRandomGaussian(size);
		for(int i = 0; i < size; i++) {
			this->d[i] = rand;
			this->g[i] = 0.0;
		}
	}
	void Init(int w, int h, int d, double v) {
		W = w;
		H = h;
		D = d;
		size = W * H * D;
		this->d.SetCount(size);
		this->g.SetCount(size);
		
		for(int i = 0; i < size; i++) {
			this->d[i] = v;
			this->g[i] = 0.0;
		}
	}
	
	void ZeroGradients() {
		for(int i = 0; i < size; i++)
			g[i] = 0.0;
	}
	
	void operator=(const VolumeData& v) {
		W = v.W;
		H = v.H;
		D = v.D;
		size = v.size;
		d.SetCount(size);
		g.SetCount(size);
		for(int i = 0; i < size; i++)
			d[i] = v.d[i];
	}
	
	int GetPos(int x, int y, int z) const {
		ASSERT(x >= 0 && x < W && y >= 0 && y < H && z >= 0 && z < D);
		return ((x * H + y) * D + z);
	}
	
	void Set(int x, int y, int z, double value) {d[GetPos(x,y,z)] = value;}
	void Add(int x, int y, int z, double value) {d[GetPos(x,y,z)] += value;}
	double Get(int x, int y, int z) const {return d[GetPos(x,y,z)];}
};







struct SimpleExperience : Moveable<SimpleExperience> {
	Volume input0, input1;
	int action0;
	double reward1;
	void Serialize(Stream& s) {
		s	% input0 % input1
			% action0
			% reward1;
	}
};




// A simple artifical neural network with fully-connected layers and Adadelta trainer.

struct Neural {
	typedef enum : int {
		L_INVALID,
		L_INPUT,
		L_FC,
		L_ACT_TANH,
		L_REGR,
		L_INPROXY,
		L_MUPLEX_ACT_TANH,
	} LayerType;
	
	typedef enum {
		BW_INVALID,
		BW_VECTOR,
		BW_POS,
	} BackwardType;
	
	struct Layer : Moveable<Layer> {
		int type = L_INVALID;
		int w = 0, h = 0, d = 0;
		int neuron_count = 0;
		int count = 0;
		int start = 0, len = 0;
		int in_count = 0;
		double bias = 0.0;
		double l1_decay_mul = 0.0;
		double l2_decay_mul = 0.0;
		Vector<int> ivec;
		Vector<Volume> filters;
		Volume bias_filter;
		Volume out;
		
		void Serialize(Stream& s) {
			s	% type
				% w % h % d
				% neuron_count
				% count
				% start % len
				% in_count
				% bias
				% l1_decay_mul
				% l2_decay_mul
				% ivec
				% filters
				% bias_filter
				% out
				;
		}
	};
	
	struct ParametersAndGradients : Moveable<ParametersAndGradients> {
		int l;
		int f;
		int w, h, d, len;
	};
	
	
	// Neural network
	Vector<Layer> layers;
	double l1_decay = 0.0;
	double l2_decay = 0.0;
	int batch_size = 50;
	int input_total = 0;
	
	// Trainer
	int iter_count;
	double last_loss;
	double l1_decay_loss;
	double l2_decay_loss;
	double ro;
	double eps;
	Vector<double> gsum;
	Vector<double> xsum;
	
	Vector<Vector<ParametersAndGradients>> pg;
	Mutex lock;
	
	void Serialize(Stream& s) {
		s	% layers
			% l1_decay
			% l2_decay
			% batch_size
			% input_total
			
			% iter_count
			% last_loss
			% l1_decay_loss
			% l2_decay_loss
			% ro
			% eps
			% gsum
			% xsum;
	}
	void SetBatchSize(int i) {batch_size = i;}
	void SetL1Decay(double d) {l1_decay = d;}
	void SetL2Decay(double d) {l2_decay = d;}
	void AddInput(int w, int h, int d);
	void AddFullyConnected(int neuron_count, double l1_decay_mul=0.0, double l2_decay_mul=1.0, double bias=0.0);
	void AddActivationTanh();
	void AddRegression(int count);
	void AddInputProxy(int start, int len);
	void AddMultiplexerActivationTanh(const Vector<int>& src_layers, int src_output_size);
	
	int  GetLayerCount() const {return layers.GetCount();}
	void GetVolumeDim(int l, int& w, int& h, int& d);
	
	void Init(int batch_size, double l1_decay, double l2_decay);
	Volume& Forward(Volume& input);
	double Backward(const Volume& output);
	void Adadelta();
};

NAMESPACE_TOPSIDE_END

#endif
