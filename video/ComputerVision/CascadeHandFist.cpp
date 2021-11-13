#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN

void LoadCascadeHandFist(Cascade& c) {
	c.classifiers.SetCount(17);
	auto sc_iter = c.classifiers.Begin();
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(2);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 9 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 9 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(5);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 19 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 16 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 10 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 16 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(4);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 23 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 23 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 16 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 11 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(4);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 22 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 22 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 10 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 15 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 15 << 3 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(7);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 18 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 18 << 10 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 21 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 20 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 10 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 1 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 12 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 6 << 10 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 15 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 15 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 15 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 15 << 2 << 6 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(5);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 19 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 20 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 16 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 14 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 7 << 12 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(9);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 20 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 2 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 11 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 11 << 9 << 2;
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
			v  << 10 << 9 << 5 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 17 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 18 << 2 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 12 << 17 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 17 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(8);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 18 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 19 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 17 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 15 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 15 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 22 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 22 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 19 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 20 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 5 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 5 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 4 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 2 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(10);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 16 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 20 << 2 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 18 << 2 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 18 << 1 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 17 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 18 << 1 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 3 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 3 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 13 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 18 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 16 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 16 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 4 << 4 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(8);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 17 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 18 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 17 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 18 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 17 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 17 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 17 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 17 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 19 << 8 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 19 << 4 << 1 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 13 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 20 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 20 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 22 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 22 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 12 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 5 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 2 << 17 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 1 << 17 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 15 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 18 << 3 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 19 << 1 << 1 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 17 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 18 << 1 << 1 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 17 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 23 << 12 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 23 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 3 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 24 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 12 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 12 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 24 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 5 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 4 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(10);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 18 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 19 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 14 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 7 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 16 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 17 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 15 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 17 << 2 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 1 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 17 << 1 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 20 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 20 << 4 << 1 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 21 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 11 << 2 << 2;
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
			v  << 15 << 20 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 21 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 18 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 18 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 12 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 1 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 3 << 2 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 3 << 1 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 18 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 6 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 9 << 3 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 23 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 23 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 20 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 20 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 15 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 2 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(12);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 17 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 7 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 7 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 22 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 3 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 3 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 1 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 16 << 3 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 16 << 1 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 16 << 3 << 1 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 17 << 1 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 22 << 13 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 23 << 13 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 4 << 2 << 3;
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
			v  << 14 << 15 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 16 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 1 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 1 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 17 << 4 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 18 << 4 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 2 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 21 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 21 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 12 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 4 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 20 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 20 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 17 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 17 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 2 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 21 << 14 << 1 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 7 << 24 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 7 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 3 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(12);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 3 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 18 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 21 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 4 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 1 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 1 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 20 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 4 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 2 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 14 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 7 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 20 << 2 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 20 << 2 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 7 << 2 << 2;
		}
	}
}

NAMESPACE_TOPSIDE_END

