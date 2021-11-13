#ifndef _ComputerVision_Cascade_h_
#define _ComputerVision_Cascade_h_

NAMESPACE_TOPSIDE_BEGIN


struct SimpleCascadeClassifier : Moveable<SimpleCascadeClassifier> {
	Vector<Vector<int>>		features;
	double					threshold;
	double					left_val;
	double					right_val;
	
	void Jsonize(JsonIO& json);
	
	
};

struct ComplexCascadeClassifier : Moveable<ComplexCascadeClassifier> {
	Vector<SimpleCascadeClassifier>		classifiers;
	
	void Jsonize(JsonIO& json);
	
	
};

struct ComplexCascade : Moveable<ComplexCascade> {
	Vector<ComplexCascadeClassifier>	classifiers;
	Vector<int>							size;
	bool								tilted;
	
	void Jsonize(JsonIO& json);
	String	GetCppLoader(String name) const;
	
	
};


struct CascadeFeature : Moveable<CascadeFeature> {
	int size;
	Vector<int> px;
	Vector<int> py;
	Vector<int> pz;
	Vector<int> nx;
	Vector<int> ny;
	Vector<int> nz;
	
	
	CascadeFeature() {
		size = 0;
	}
	
	void Reserve(int i) {
		px.Reserve(i);
		py.Reserve(i);
		pz.Reserve(i);
		nx.Reserve(i);
		ny.Reserve(i);
		nz.Reserve(i);
	}
	
	void Init2D(int i) {
		size = i;
		px.SetCount(i);
		py.SetCount(0);
		pz.SetCount(i);
		nx.SetCount(i);
		ny.SetCount(0);
		nz.SetCount(i);
		Zero();
	}
	
	void Zero() {
		for(int& i : px) i = 0;
		for(int& i : py) i = 0;
		for(int& i : pz) i = 0;
		for(int& i : nx) i = 0;
		for(int& i : ny) i = 0;
		for(int& i : nz) i = 0;
	}
	
	void Jsonize(JsonIO& json);
	
	
};

struct CascadeStageClassifier : Moveable<CascadeStageClassifier> {
	int						count;
	double					threshold;
	Vector<CascadeFeature>	features;
	Vector<CascadeFeature>	_features;
	Vector<double>			alpha;
	
	void Jsonize(JsonIO& json);
	
	
};

struct Cascade {
	int count;
	int width;
	int height;
	Vector<CascadeStageClassifier>	stage_classifiers;
	
	void	Jsonize(JsonIO& json);
	String	GetCppLoader(String name) const;
	
};


NAMESPACE_TOPSIDE_END

#endif
