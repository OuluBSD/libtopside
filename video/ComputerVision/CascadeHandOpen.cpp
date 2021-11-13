#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN

void LoadCascadeHandOpen(Cascade& c) {
	c.classifiers.SetCount(15);
	auto sc_iter = c.classifiers.Begin();
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(7);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 24 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 12 << 21 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 21 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 19 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 19 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 10 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 5 << 22 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 10 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 5 << 22 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(11);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 4 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 2 << 22 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 4 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 2 << 22 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 21 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 7 << 21 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 19 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 19 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 17 << 21 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 21 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 7 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 7 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 11 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 11 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 23 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 23 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 2 << 3 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(20);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 24 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 23 << 19 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 24 << 19 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 21 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 7 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 5 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 7 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 24 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 4 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 8 << 25 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 19 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 19 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 16 << 1 << 9 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(17);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 6 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 24 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 8 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 1 << 24 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 8 << 25 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 19 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 19 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 24 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 4 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 4 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 23 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 24 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 12 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 23 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 7 << 23 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 1 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(20);
		auto cf_iter = sc.classifiers.Begin();
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
			v  << 24 << 5 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 15 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 19 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 19 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 16 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 16 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 14 << 7 << 2;
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
			v  << 0 << 0 << 25 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 25 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 2 << 4 << 2;
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
			v  << 23 << 1 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 25 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 25 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 21 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(24);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 10 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 5 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 12 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 2 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 1 << 24 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 1 << 1 << 2 << -1;
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
			v  << 1 << 1 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 15 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 9 << 3;
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
			v  << 9 << 10 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 18 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 19 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 3 << 2;
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
			v  << 4 << 3 << 16 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 16 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 21 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 21 << 12 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(32);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 8 << 25 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 6 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 16 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 8 << 21 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 4 << 19 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 2 << 19 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 10 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 15 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 7 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 7 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 22 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 22 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 10 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 17 << 24 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 21 << 24 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 19 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 19 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 21 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 22 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 22 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 17 << 21 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 21 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 6 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 25 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 25 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 10 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 23 << 1 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(33);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 4 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 21 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 21 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 20 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 20 << 1 << 1 << 2;
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
			v  << 3 << 23 << 19 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 24 << 19 << 1 << 2;
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
			v  << 0 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 2 << 2;
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
			v  << 0 << 0 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 19 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 19 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 25 << 4 << 2;
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
			v  << 9 << 1 << 7 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 9 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 23 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 23 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 5 << 7 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 2 << 1 << -1;
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
			v  << 19 << 9 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 13 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 12 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 25 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 25 << 2 << 2;
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
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 23 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 23 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 6 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(43);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 6 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 23 << 19 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 24 << 19 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 23 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 23 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 24 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 8 << 7 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 16 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 8 << 24 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 16 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 21 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 22 << 5 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 19 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 20 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 1 << 1 << 2;
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
			v  << 12 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 19 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 21 << 14 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 2 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 24 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 15 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 15 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 19 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 20 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 15 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 15 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 15 << 9 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 11 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 11 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 23 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 23 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 1 << 9 << 2;
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
			v  << 12 << 0 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 19 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 19 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 15 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 20 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 2 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(45);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 11 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 18 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 21 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 7 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 25 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 25 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 14 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 10 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 10 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 14 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 15 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 15 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 5 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 22 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 22 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 4 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 0 << 2 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 4 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 25 << 2;
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
			v  << 24 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 25 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 25 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 21 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 19 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 22 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 19 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 22 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 23 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 24 << 14 << 1 << 2;
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
			v  << 2 << 1 << 21 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 22 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 20 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 11 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 11 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 9 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 9 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 20 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 22 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 23 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 23 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 9 << 1 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 13 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 1 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 1 << 8 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(52);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 21 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 21 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 23 << 22 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 24 << 22 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 24 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 19 << 19 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 22 << 19 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 24 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 24 << 6 << 1 << 2;
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
			v  << 4 << 9 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 6 << 3 << 9;
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
			v  << 0 << 1 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 15 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 5 << 25 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 16 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 8 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 20 << 21 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 21 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 11 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 10 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 24 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 24 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 22 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 20 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 10 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 5 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 1 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 19 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 21 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 19 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 19 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 8 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 12 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 25 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 25 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 1 << 3 << 2;
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
			v  << 1 << 7 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 1 << -1;
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
			v  << 0 << 8 << 2 << 1 << -1;
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
			v  << 12 << 6 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 19 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 19 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 23 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 23 << 1 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(56);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 5 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 5 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 16 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 20 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 8 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 8 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 19 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 21 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 17 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 20 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 25 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 25 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 17 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 17 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 21 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 23 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 24 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 20 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 20 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 20 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 20 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 20 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 20 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 20 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 20 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 2 << 2 << -1;
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
			v  << 0 << 0 << 1 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 17 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 25 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 25 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 5 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 9 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 1 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 21 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 23 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 4 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 7 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 23 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 23 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(51);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 24 << 23 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 12 << 23 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 18 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 19 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 21 << 5 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 7 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 7 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 7 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 10 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 24 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 24 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 18 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 18 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 0 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 11 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 1 << 22 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 25 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 23 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 20 << 23 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 23 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 24 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 24 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 24 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 24 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 6 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 20 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 21 << 5 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 20 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 21 << 5 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 12 << 2 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 15 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 2 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 7 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 12 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 2 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 1 << 2 << 2 << -1;
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
			v  << 0 << 0 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 5 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 1 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 7 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 24 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 24 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 17 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 5 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 23 << 5 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(66);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 18 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 18 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 18 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 13 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 10 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 5 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 15 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 5 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 19 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 17 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 20 << 3 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 6 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 1 << 2 << 20 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 6 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 2 << 20 << 3;
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
			v  << 1 << 13 << 2 << 1 << -1;
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
			v  << 22 << 14 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 14 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 12 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 25 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 25 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 22 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 12 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 4 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 22 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 11 << 11 << 2;
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
			v  << 10 << 4 << 5 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 1 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 15 << 6 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 24 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 17 << 24 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 19 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 20 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 21 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 19 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 20 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 22 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 23 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 4 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 24 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 20 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 20 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 1 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 24 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 20 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 20 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 20 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 20 << 1 << 1 << 2;
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
			v  << 16 << 4 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 23 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 22 << 15 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 22 << 5 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 23 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 23 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 20 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 17 << 11 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 19 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 15 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 15 << 6 << 3;
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
			v  << 1 << 4 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 3 << 1 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 8 << 1 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(74);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 5 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 17 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 17 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 11 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 11 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 9 << 1 << 2 << 2;
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
			v  << 9 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 0 << 3 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 1 << 24 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 24 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 24 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 12 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 1 << 21 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 4 << 2 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 2 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 2 << -1;
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
			v  << 1 << 4 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 10 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 22 << 2 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 22 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 3 << 4 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 2 << 10 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 13 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 2 << 10 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 21 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 10 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 8 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 4 << 8 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 21 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 21 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 12 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 4 << 8 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 4 << 8 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 1 << 3 << -1;
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
			v  << 6 << 11 << 1 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 11 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 13 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 1 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 17 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 18 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 0 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 1 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 1 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 24 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 1 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 2 << -1;
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
			v  << 8 << 0 << 1 << 2 << -1;
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
			v  << 13 << 0 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 1 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 1 << 4 << 3;
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
			v  << 7 << 0 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 20 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 10 << 8 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 6 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 6 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 23 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 23 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 23 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 23 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 1 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 19 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 21 << 11 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 20 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 21 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 17 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 21 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 17 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 24 << 21 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 17 << 1 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 21 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 1 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 12 << 6 << 2;
		}
	}
}

NAMESPACE_TOPSIDE_END

