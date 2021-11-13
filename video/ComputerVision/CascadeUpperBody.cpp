#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN

void LoadCascadeUpperBody(Cascade& c) {
	c.classifiers.SetCount(30);
	auto sc_iter = c.classifiers.Begin();
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
			v  << 5 << 5 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 22 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 11 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 3 << 5 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 22 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 8 << -1;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 16 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 8 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 4 << -1;
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
			v  << 7 << 3 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 2 << 7 << 2;
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
			v  << 2 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 5 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 20 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 10 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 22 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 8 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 16 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 5 << 3 << 2;
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
			v  << 6 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 5 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 22 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 22 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 22 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 11 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 3 << 4 << 3;
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
			v  << 6 << 2 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 4 << -1;
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
			v  << 13 << 5 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 18 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 3 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 4 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(46);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 22 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 11 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 5 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 10 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 13 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 13 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 16 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 8 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 9 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 3 << 6 << 2;
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
			v  << 2 << 12 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 22 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 10 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 10 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 11 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 22 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 11 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 11 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 7 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 22 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 11 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 4 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 2 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 12 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 12 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 4 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 22 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 11 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 18 << 2 << 3;
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
			v  << 6 << 5 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 5 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 16 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 22 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 11 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 2 << 7 << 3;
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
			v  << 10 << 2 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 20 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 10 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 18 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 2 << 6 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(58);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 9 << 3;
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
			v  << 10 << 4 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 6 << -1;
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
			v  << 11 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 22 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 11 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 7 << 3 << 2;
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
			v  << 1 << 4 << 16 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 9 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 2 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 7 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 18 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 9 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 17 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 5 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(44);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 8 << 2 << 3;
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
			v  << 6 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 16 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 8 << 7 << 2;
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
			v  << 7 << 2 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 3 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 2 << 6 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(44);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 18 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 18 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 12 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 5 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 3 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 1 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 6 << 2;
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
			v  << 11 << 11 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 10 << 2 << 2;
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
			v  << 5 << 6 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 5 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 1 << 2;
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
			v  << 14 << 0 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 20 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 10 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 7 << 2 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(61);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 14 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 17 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 17 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 4 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 4 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 2 << 8 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 5 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 17 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 17 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 2 << 8 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 15 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 15 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 2 << 8 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(72);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 8 << 3 << 2;
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
			v  << 10 << 4 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 16 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 3 << 2;
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
			v  << 11 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 11 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 5 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 6 << -1;
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
			v  << 2 << 3 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 7 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 7 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 7 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 14 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 7 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 7 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(75);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 18 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 3 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 3 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 13 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 13 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 3 << 5 << 2;
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
			v  << 8 << 9 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 9 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 15 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 5 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 5 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 16 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 8 << -1;
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
			v  << 2 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 7 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 16 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 17 << 16 << 1 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(67);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 16 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 7 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 14 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 16 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 18 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 18 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 16 << 1 << 3;
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
			v  << 13 << 5 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 14 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 18 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 18 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 18 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 12 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 6 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 10 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 7 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 2 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 2 << 12 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(88);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 22 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 11 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 11 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 8 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 18 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 9 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 6 << 9 << -1;
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
			v  << 9 << 3 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 5 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 4 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 2 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 20 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 10 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 7 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 7 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 5 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 9 << 2 << 2;
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
			v  << 9 << 3 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 6 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 11 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 7 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(80);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 7 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 14 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 7 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 14 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 7 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 14 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 7 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 7 << 2 << 2;
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
			v  << 6 << 4 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 5 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 11 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 3 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 2 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 21 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 7 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 16 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 13 << 20 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 10 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 4 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(103);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 20 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 15 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 22 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 18 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 18 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 10 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 8 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 2 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 13 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 12 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 5 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 2 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 3 << 17 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 1 << 17 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 3 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 18 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 5 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(83);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 15 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 15 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 8 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 17 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 17 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 22 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 7 << 2 << 2;
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
			v  << 7 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 13 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 13 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 3 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 18 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 3 << 4 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(101);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 8 << 2;
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
			v  << 10 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 2 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 21 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 7 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 3 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 1 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 22 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 11 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 7 << 2 << 3;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 15 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 5 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 15 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 5 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 10 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 5 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 8 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 4 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 10 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 6 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 8 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 4 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(104);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 10 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 2 << 12 << -1;
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
			v  << 19 << 0 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 0 << 1 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 1 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 22 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 11 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 11 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 11 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 11 << 2 << 3;
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
			v  << 0 << 9 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 10 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 10 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 15 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 11 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 16 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 16 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 22 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 5 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 5 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 14 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 18 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 5 << 9 << 2;
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
			v  << 8 << 9 << 6 << 2 << 9;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(111);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 17 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 17 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 9 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 13 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 6 << 2;
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
			v  << 2 << 8 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 6 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 4 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 2 << 18 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 12 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 6 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 18 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 4 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 16 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 8 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 7 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 11 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 11 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 7 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 7 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 10 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 10 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 16 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 2 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 4 << 6 << -1;
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
			v  << 5 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 22 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 1 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 1 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 12 << 1 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(107);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 16 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 8 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 18 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 9 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 9 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 16 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 16 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 14 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 16 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 14 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 14 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 9 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 18 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 4 << -1;
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
			v  << 14 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 15 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 3 << 8 << 3;
		}
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
			v  << 10 << 0 << 5 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 15 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 5 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 6 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 16 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 8 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 14 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 21 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 7 << 18 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 5 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 5 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 8 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 6 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 8 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 8 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 3 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 5 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 5 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 5 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(107);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 3 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 5 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 14 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 7 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 6 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 6 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 16 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 17 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 3 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 5 << 1 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 11 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 11 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 3 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 1 << 18 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 9 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 15 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 13 << 2;
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
			v  << 6 << 0 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 11 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 9 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 9 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 2 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 4 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 9 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 7 << 2 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 14 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 7 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 7 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 10 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 5 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 4 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 18 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 8 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 13 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 13 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 4 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(123);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 20 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 10 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 20 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 10 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 15 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 5 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 6 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 6 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 8 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 16 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 8 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 8 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 3 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 17 << 16 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 3 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 3 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 14 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 7 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 7 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 5 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 5 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 22 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 11 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 11 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 20 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 10 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 15 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 14 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 14 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 6 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 2 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 12 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 15 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 16 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 16 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 10 << 1 << 3;
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
			v  << 11 << 11 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 16 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 18 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 9 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 12 << 2 << -1;
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
			v  << 13 << 6 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 17 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 17 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 7 << -1;
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
			v  << 8 << 4 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 8 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 11 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 9 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 3 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(127);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 6 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 6 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 11 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 11 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 2 << -1;
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
			v  << 10 << 13 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 2 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 12 << 1 << 2;
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
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 4 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 2 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 1 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 3 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 11 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 11 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 11 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 20 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 10 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 2 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 8 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 2 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 1 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 8 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 8 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 10 << 9 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 18 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 9 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 18 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 9 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 20 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 10 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 9 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 9 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 15 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 13 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 13 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 16 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 16 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 16 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 16 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 1 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 14 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 14 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 10 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 5 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 10 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 5 << 9 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 5 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 9 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 10 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 18 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 1 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 16 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 6 << 2 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(152);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 4 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 18 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 7 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 7 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 10 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 2 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 5 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 5 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 17 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 17 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 2 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 1 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 3 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 6 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 5 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 16 << 15 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 17 << 15 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 16 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 14 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 7 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 14 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 7 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 4 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 16 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 16 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 14 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 15 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 18 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 4 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 2 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 15 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 9 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 15 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 15 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 6 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 9 << 6 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 3 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 6 << 4 << 12 << -1;
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
			v  << 3 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 5 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 8 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 8 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 15 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 15 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 7 << 3 << -1;
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
			v  << 18 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 21 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 7 << 2 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 7 << 4 << -1;
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
			v  << 11 << 2 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 10 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 5 << 12 << -1;
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
			v  << 3 << 7 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 9 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 11 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 4 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 2 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 11 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 3 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 3 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 1 << 15 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 5 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 4 << 3 << 2;
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
			v  << 11 << 0 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 6 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 6 << 5 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(135);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 11 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 18 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 9 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 16 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 16 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 7 << 3 << 8 << -1;
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
			v  << 13 << 10 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 22 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 11 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 5 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 3 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 6 << 3 << 3;
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
			v  << 13 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 14 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 7 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 1 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 7 << 6 << -1;
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
			v  << 5 << 11 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 13 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 13 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 2 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 20 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 10 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 4 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 8 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 3 << 4 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 8 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 11 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 7 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 10 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 5 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 5 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 15 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 5 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 10 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 8 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 11 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 8 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 4 << 11 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 8 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 8 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 3 << 5 << 2;
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
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 13 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 18 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 3 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 16 << 18 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 9 << 16 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 16 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 14 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 14 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 15 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 15 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 14 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 10 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 10 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 10 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 10 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 10 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 5 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 17 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 17 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 14 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 13 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 11 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 6 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 6 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 20 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 10 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 11 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 18 << 0 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 2 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 5 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 8 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 9 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 9 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 14 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 10 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 5 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 10 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 1 << 13 << 3;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(135);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 12 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 4 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 4 << -1;
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
			v  << 15 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 3 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 3 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 2 << 11 << 2;
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
			v  << 10 << 2 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 5 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 2 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 4 << 1 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 9 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 9 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 10 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 17 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 17 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 10 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 13 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 8 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 11 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 5 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 11 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 13 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 6 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 0 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 8 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 3 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 20 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 10 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 8 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 8 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 8 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 3 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 6 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 3 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 18 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 9 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 21 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 7 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 4 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 10 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 10 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 9 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 9 << 3 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 10 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 11 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 11 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 3 << 6 << 3 << 2;
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
			v  << 2 << 0 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 5 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 3 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 3 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 4 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 18 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 9 << 6 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 16 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 17 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 4 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 8 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 14 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 13 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 14 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 17 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 14 << 17 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 4 << 4 << 3;
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
			v  << 11 << 7 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 6 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 12 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 4 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 2 << 3 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 20 << 3 << 1 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 12 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 4 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 3 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 1 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 7 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 10 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 14 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 0 << 4 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 0 << 2 << 8 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 15 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 15 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 13 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 13 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 5 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 5 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 14 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 4 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 5 << 16 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 9 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 8 << 3 << 5 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 3 << 3 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 7 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 6 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 3 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 3 << 3 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 1 << 14 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 4 << 22 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 11 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 6 << 11 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 12 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 14 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 14 << 7 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 16 << 7 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 12 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 3 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 6 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 6 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 5 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 5 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 8 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 4 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 4 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 8 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 5 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 4 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 16 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 6 << 8 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 14 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 7 << 20 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 10 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 2 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 5 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 13 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 13 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 6 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 3 << 15 << 2;
		}
	}
	{
		ComplexCascadeClassifier& sc = *sc_iter++;
		sc.classifiers.SetCount(143);
		auto cf_iter = sc.classifiers.Begin();
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 4 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 4 << 7 << -1;
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
			v  << 9 << 1 << 7 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 7 << 2 << 2;
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
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 12 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 4 << 3 << 2;
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
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 6 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 6 << 3 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 3 << 6 << 2;
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
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 13 << 9 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 13 << 3 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 12 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 15 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 4 << 3 << 2;
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
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 6 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 2 << 7 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 4 << 9 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 3 << 4 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 12 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 14 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 8 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 6 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 4 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 6 << 6 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 5 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 6 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 16 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 0 << 16 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 12 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 0 << 12 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 3 << 6 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 2 << 18 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 6 << 3 << 9;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 2 << 3 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 3 << 1 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 9 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 9 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 1 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 4 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 14 << 12 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 14 << 6 << 2 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 16 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 3 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 12 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 12 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 2 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 2 << 4 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 14 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 8 << 7 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 2 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 1 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 9 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 2 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 9 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 10 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 8 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 7 << 4 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 3 << 4 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 12 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 2 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 8 << 1 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 7 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 8 << 7 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 13 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 13 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 9 << 4 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 2 << 9 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 6 << 6 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 2 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 0 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 3 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 14 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 0 << 7 << 3 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 3 << 7 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 16 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 15 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 7 << 15 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 7 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 12 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 4 << 6 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 14 << 16 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 0 << 7 << 16 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 3 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 4 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 2 << 10 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 0 << 10 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 16 << 7 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 6 << 1 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 12 << 6 << 5 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 9 << 11 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 7 << 3 << 11 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 15 << 8 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 4 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 3 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 2 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 1 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 9 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 1 << 3 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 3 << 16 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 3 << 8 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 1 << 4 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 8 << 12 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 7 << 3 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 12 << 3 << 5 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 15 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 15 << 9 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 0 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 13 << 1 << 3;
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
			v  << 12 << 1 << 2 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 1 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 1 << 2 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 1 << 1 << 15 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 6 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 2 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 19 << 1 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 2 << 6 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 7 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 0 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 0 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 0 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 5 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 7 << 5 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 2 << 3 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 2 << 1 << 13 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 17 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 6 << 17 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 3 << 18 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 4 << 18 << 1 << 3;
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
			v  << 11 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 11 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 13 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 6 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 5 << 6 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 13 << 1 << 8 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 4 << 8 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 1 << 12 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 1 << 4 << 12 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 2 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 2 << 4 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 2 << 2 << 12 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 0 << 2 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 0 << 1 << 14 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 7 << 15 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 6 << 7 << 5 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 1 << 7 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 3 << 7 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(3);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 4 << 20 << 14 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 4 << 10 << 7 << 2;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 11 << 10 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 2 << 6 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 2 << 2 << 8 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 2 << 13 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 0 << 1 << 13 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 1 << 9 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 1 << 3 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 9 << 6 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 9 << 2 << 6 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 5 << 8 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 8 << 14 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 9 << 14 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 7 << 20 << 2 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 7 << 10 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 10 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 0 << 5 << 10 << 2;
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
			v  << 5 << 1 << 15 << 10 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 1 << 5 << 10 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 9 << 18 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 0 << 10 << 18 << 2 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 8 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 10 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 8 << 10 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 10 << 2 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 6 << 10 << 12 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 11 << 10 << 10 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 8 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 5 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 8 << 5 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 17 << 11 << 5 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 8 << 11 << 4 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 11 << 2 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 5 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 6 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 9 << 13 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 2 << 10 << 13 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 16 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 13 << 8 << 3 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 5 << 12 << 8 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 9 << 12 << 4 << 4 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 8 << 6 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 14 << 11 << 6 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 10 << 12 << 3 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 11 << 12 << 1 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 7 << 11 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 10 << 11 << 3 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 9 << 4 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 4 << 3 << 4 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 12 << 1 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 15 << 1 << 3 << 9 << 3;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 1 << 1 << 9 << 9 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 4 << 1 << 3 << 9 << 3;
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
			v  << 4 << 6 << 4 << 6 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 6 << 2 << 6 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 7 << 5 << 12 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 10 << 5 << 6 << 7 << 2;
		}
		{
			SimpleCascadeClassifier& cf = *cf_iter++;
			cf.threshold = 2.78100360429512e180;
			cf.left_val = 2.78100360429512e180;
			cf.right_val = 2.78100360429512e180;
			cf.features.SetCount(2);
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 3 << 5 << 12 << 7 << -1;
			Vector<int>& v = cf.features[i];
			v.Reserve(5);
			v  << 6 << 5 << 6 << 7 << 2;
		}
	}
}

NAMESPACE_TOPSIDE_END

