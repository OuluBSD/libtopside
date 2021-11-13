#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN

void LoadCascadeMouth(Cascade& c) {
	c.classifiers.SetCount(17);
	auto sc_iter = c.classifiers.Begin();
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(13);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 8 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 3 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(13);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 14 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 11 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(29);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 15 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 11 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 11 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 14 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 11 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 2 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(34);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 10 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 24 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 9 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 14 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 2 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 2 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 8 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 4 << 1 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(42);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 11 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 13 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 13 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 3 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 3 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 24 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 20 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 4 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 3 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(64);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 5 << 2 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 21 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 7 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 24 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 11 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 11 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 20 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 10 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 9 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 1 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(57);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 6 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 13 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 13 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 13 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 13 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 24 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 4 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 2 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 1 << 4 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(64);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 11 << 5 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 9 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 9 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 12 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 12 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 4 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 22 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 11 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 20 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 10 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 16 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 8 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 12 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(77);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 21 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 13 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 22 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 11 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 18 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 9 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 7 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 7 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 11 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 12 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 5 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 21 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 7 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 5 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 22 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 11 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 12 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(73);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 5 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 6 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 18 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 16 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 8 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 4 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 2 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 5 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 20 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 14 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 6 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 7 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 7 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 4 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 3 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 22 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 11 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 11 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(102);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 8 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 21 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 20 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 2 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 2 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 6 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 12 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 14 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 2 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 6 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 6 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 2 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 16 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 8 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 5 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 24 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 3 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 1 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(115);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 16 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 8 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 8 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 6 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 13 << 2 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 24 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 2 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 21 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 21 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 7 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 22 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 11 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 13 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 1 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 2 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 10 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 21 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 18 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 9 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 24 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 12 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 12 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 2 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(128);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 24 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 5 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 12 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 13 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 13 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 11 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 21 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 6 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 2 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 14 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 2 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 5 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 4 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 4 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 8 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 3 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 10 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 4 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 24 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 8 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 8 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 9 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 14 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 13 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 13 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 13 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 13 << 4 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(113);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 12 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 6 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 8 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 14 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 15 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 7 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 2 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 15 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 14 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 14 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 14 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 2 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 16 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 2 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 3 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 2 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 9 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 1 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(172);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 16 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 24 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 12 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 22 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 2 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 7 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 7 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 24 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 8 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 10 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 4 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 9 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 6 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 2 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 14 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 2 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 20 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 14 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 6 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 4 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 10 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 5 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 2 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 15 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 14 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 6 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 14 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 1 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(201);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 5 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 9 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 16 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 12 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 7 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 21 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 4 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 20 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 10 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 2 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 18 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 4 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 14 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 3 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 20 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 10 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 14 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 14 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 5 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 5 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 4 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 7 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 10 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 5 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 14 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 3 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 1 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(218);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 7 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 21 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 7 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 18 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 24 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 12 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 12 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 21 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 5 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 13 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 13 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 6 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 21 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 12 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 12 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 21 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 10 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 5 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 8 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 5 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 2 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 2 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 1 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 12 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 4 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 13 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 14 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 12 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 8 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 5 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 6 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 2 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 9 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 24 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 12 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 3 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 16 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 12 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 15 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 14 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 2 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 5 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 20 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 7 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 12 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 18 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 9 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 9 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 2 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 4 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 5 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 8 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 10 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 20 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 8 << 1 << 1 << 2;
		}
	}
}

NAMESPACE_TOPSIDE_END

