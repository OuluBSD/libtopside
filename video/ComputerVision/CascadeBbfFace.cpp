#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN

void LoadCascadeBbfFace(Cascade& c) {
	c.count = 16;
	c.width = 24;
	c.height = 24;
	c.stage_classifiers.SetCount(16);
	auto sc_iter = c.stage_classifiers.Begin();
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 4;
		sc.threshold = -4.57753;
		sc.features.SetCount(4);
		sc.alpha.SetCount(8);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 5 << 8 << 11;
			cf.py << 2 << 2 << 6 << 3;
			cf.pz << 2 << 1 << 1 << 0;
			cf.nx << 8 << 4 << 0 << 0;
			cf.ny << 4 << 4 << 0 << 0;
			cf.nz << 1 << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 6 << 7;
			cf.py << 7 << 13 << 0;
			cf.pz << 1 << 0 << -1;
			cf.nx << 2 << 3 << 4;
			cf.ny << 5 << 4 << 4;
			cf.nz << 2 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 3 << 10 << 13 << 11;
			cf.py << 1 << 0 << 3 << 2 << 2;
			cf.pz << 1 << 2 << 0 << 0 << 0;
			cf.nx << 0 << 11 << 0 << 11 << 11;
			cf.ny << 0 << 2 << 3 << 1 << 1;
			cf.nz << 1 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 12 << 12 << 9 << 12;
			cf.py << 4 << 13 << 12 << 7 << 11;
			cf.pz << 1 << 0 << 0 << 1 << 0;
			cf.nx << 8 << 0 << 8 << 2 << 11;
			cf.ny << 4 << 0 << 8 << 5 << 1;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		*a_iter++ = -2.879683;
		*a_iter++ = 2.879683;
		*a_iter++ = -1.569341;
		*a_iter++ = 1.569341;
		*a_iter++ = -1.286131;
		*a_iter++ = 1.286131;
		*a_iter++ = -1.157626;
		*a_iter++ = 1.157626;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 4;
		sc.threshold = -4.339908;
		sc.features.SetCount(4);
		sc.alpha.SetCount(8);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 12 << 3 << 11 << 17;
			cf.py << 3 << 3 << 1 << 4 << 13;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 4 << 3 << 8 << 15 << 15;
			cf.ny << 4 << 5 << 4 << 8 << 8;
			cf.nz << 1 << 2 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 7 << 6 << 3 << 3;
			cf.py << 13 << 13 << 4 << 2 << 7;
			cf.pz << 0 << 0 << 1 << 2 << 1;
			cf.nx << 4 << 8 << 3 << 0 << 15;
			cf.ny << 4 << 4 << 4 << 3 << 8;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 2 << 11;
			cf.py << 3 << 2 << 5;
			cf.pz << 2 << 2 << 0;
			cf.nx << 3 << 8 << 3;
			cf.ny << 4 << 4 << 4;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 13 << 9 << 11 << 7;
			cf.py << 2 << 1 << 2 << 1 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 23 << 11 << 23 << 22 << 23;
			cf.ny << 1 << 0 << 2 << 0 << 0;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		*a_iter++ = -2.466029;
		*a_iter++ = 2.466029;
		*a_iter++ = -1.83951;
		*a_iter++ = 1.83951;
		*a_iter++ = -1.060559;
		*a_iter++ = 1.060559;
		*a_iter++ = -1.094927;
		*a_iter++ = 1.094927;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 7;
		sc.threshold = -5.052474;
		sc.features.SetCount(7);
		sc.alpha.SetCount(14);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 13 << 3 << 11 << 10;
			cf.py << 13 << 2 << 1 << 4 << 3;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 4 << 8 << 8 << 3 << 7;
			cf.ny << 2 << 8 << 4 << 5 << 4;
			cf.nz << 2 << 0 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 7 << 3 << 6 << 6;
			cf.py << 4 << 12 << 2 << 13 << 14;
			cf.pz << 1 << 0 << 2 << 0 << 0;
			cf.nx << 8 << 3 << 4 << 4 << 3;
			cf.ny << 4 << 4 << 2 << 0 << 2;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 4 << 5 << 3 << 3;
			cf.py << 2 << 1 << 3 << 1 << 1;
			cf.pz << 0 << 1 << 0 << 1 << -1;
			cf.nx << 1 << 0 << 1 << 1 << 0;
			cf.ny << 1 << 3 << 2 << 0 << 4;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 3 << 2;
			cf.py << 11 << 13 << 10 << 7 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 2;
			cf.nx << 4 << 1 << 8 << 2 << 0;
			cf.ny << 4 << 1 << 12 << 0 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 13 << 1;
			cf.py << 7 << 19 << 4;
			cf.pz << 1 << -1 << -1;
			cf.nx << 4 << 7 << 4;
			cf.ny << 5 << 8 << 2;
			cf.nz << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 8 << 16 << 4 << 4;
			cf.py << 12 << 1 << 2 << 0 << 0;
			cf.pz << 0 << 1 << 0 << 2 << -1;
			cf.nx << 11 << 22 << 11 << 23 << 23;
			cf.ny << 2 << 0 << 1 << 1 << 5;
			cf.nz << 1 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 17 << 17;
			cf.py << 6 << 11 << 12;
			cf.pz << 0 << 0 << 0;
			cf.nx << 15 << 1 << 11;
			cf.ny << 9 << 1 << 1;
			cf.nz << 0 << -1 << -1;
		}
		*a_iter++ = -2.15689;
		*a_iter++ = 2.15689;
		*a_iter++ = -1.718246;
		*a_iter++ = 1.718246;
		*a_iter++ = -0.9651329;
		*a_iter++ = 0.9651329;
		*a_iter++ = -0.994809;
		*a_iter++ = 0.994809;
		*a_iter++ = -0.8802466;
		*a_iter++ = 0.8802466;
		*a_iter++ = -0.8486741;
		*a_iter++ = 0.8486741;
		*a_iter++ = -0.8141777;
		*a_iter++ = 0.8141777;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 13;
		sc.threshold = -5.7744;
		sc.features.SetCount(13);
		sc.alpha.SetCount(26);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 10 << 3 << 12 << 14;
			cf.py << 5 << 3 << 1 << 2 << 2;
			cf.pz << 1 << 0 << 2 << 0 << 0;
			cf.nx << 3 << 4 << 14 << 8 << 4;
			cf.ny << 5 << 4 << 8 << 4 << 2;
			cf.nz << 2 << 1 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 6 << 11 << 5 << 12;
			cf.py << 4 << 13 << 4 << 2 << 4;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 1 << 4 << 8 << 1 << 1;
			cf.ny << 2 << 4 << 4 << 4 << 3;
			cf.nz << 0 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 18 << 6 << 12;
			cf.py << 12 << 4 << 8;
			cf.pz << 0 << 1 << 0;
			cf.nx << 7 << 4 << 8;
			cf.ny << 4 << 2 << 4;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 5 << 6 << 3 << 17;
			cf.py << 13 << 12 << 3 << 8 << 13;
			cf.pz << 0 << 0 << 1 << 1 << 0;
			cf.nx << 3 << 3 << 0 << 1 << 8;
			cf.ny << 4 << 5 << 5 << 10 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 7 << 16 << 7 << 7;
			cf.py << 1 << 1 << 2 << 0 << 0;
			cf.pz << 0 << 1 << 0 << 1 << -1;
			cf.nx << 23 << 23 << 23 << 11 << 5;
			cf.ny << 2 << 14 << 1 << 2 << 1;
			cf.nz << 0 << 0 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 18 << 16;
			cf.py << 7 << 14 << 2;
			cf.pz << 1 << 0 << -1;
			cf.nx << 8 << 4 << 9;
			cf.ny << 10 << 2 << 4;
			cf.nz << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 16 << 1 << 22;
			cf.py << 7 << 4 << 5 << 11;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 3 << 9 << 4 << 2;
			cf.ny << 4 << 9 << 7 << 5;
			cf.nz << 1 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 7 << 8 << 8 << 9;
			cf.py << 0 << 2 << 2 << 1 << 1;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 1 << 0 << 0;
			cf.ny << 15 << 16 << 19 << 0 << 14;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 4 << 7 << 8 << 12;
			cf.py << 2 << 5 << 6 << 7 << 10;
			cf.pz << 2 << 2 << 1 << 1 << 0;
			cf.nx << 8 << 5 << 10 << 0 << 0;
			cf.ny << 4 << 2 << 5 << 3 << 14;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 0;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 3 << 14;
			cf.ny << 4 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 8 << 18 << 4 << 4;
			cf.py << 3 << 1 << 3 << 0 << 0;
			cf.pz << 0 << 1 << 0 << 2 << -1;
			cf.nx << 21 << 22 << 5 << 11 << 22;
			cf.ny << 0 << 1 << 0 << 1 << 2;
			cf.nz << 0 << 0 << 2 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 8 << 2 << 11;
			cf.py << 13 << 12 << 2 << 7;
			cf.pz << 0 << 0 << 2 << 0;
			cf.nx << 4 << 0 << 23 << 3;
			cf.ny << 4 << 1 << 1 << 11;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 18 << 8 << 9 << 15;
			cf.py << 4 << 16 << 7 << 7 << 23;
			cf.pz << 2 << 0 << 1 << 1 << 0;
			cf.nx << 0 << 1 << 1 << 1 << 1;
			cf.ny << 10 << 21 << 23 << 22 << 22;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		*a_iter++ = -1.956565;
		*a_iter++ = 1.956565;
		*a_iter++ = -1.262438;
		*a_iter++ = 1.262438;
		*a_iter++ = -1.056941;
		*a_iter++ = 1.056941;
		*a_iter++ = -0.9712509;
		*a_iter++ = 0.9712509;
		*a_iter++ = -0.8261028;
		*a_iter++ = 0.8261028;
		*a_iter++ = -0.8456506;
		*a_iter++ = 0.8456506;
		*a_iter++ = -0.6652113;
		*a_iter++ = 0.6652113;
		*a_iter++ = -0.6026287;
		*a_iter++ = 0.6026287;
		*a_iter++ = -0.6915425;
		*a_iter++ = 0.6915425;
		*a_iter++ = -0.5539286;
		*a_iter++ = 0.5539286;
		*a_iter++ = -0.5515072;
		*a_iter++ = 0.5515072;
		*a_iter++ = -0.6685884;
		*a_iter++ = 0.6685884;
		*a_iter++ = -0.465607;
		*a_iter++ = 0.465607;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 20;
		sc.threshold = -5.606853;
		sc.features.SetCount(20);
		sc.alpha.SetCount(40);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 11 << 6 << 14 << 9;
			cf.py << 13 << 4 << 4 << 3 << 3;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 14 << 4 << 8 << 7 << 8;
			cf.ny << 8 << 4 << 4 << 4 << 8;
			cf.nz << 0 << 1 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 9 << 10 << 11 << 11;
			cf.py << 7 << 2 << 2 << 3 << 3;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 3 << 8 << 4 << 2 << 5;
			cf.ny << 4 << 4 << 10 << 2 << 8;
			cf.nz << 1 << 1 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 5 << 12;
			cf.py << 12 << 9 << 10 << 12 << 11;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 2 << 1 << 3 << 0 << 0;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 18 << 9 << 9 << 12;
			cf.py << 7 << 14 << 19 << 5 << 11;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 23 << 4 << 23 << 23 << 8;
			cf.ny << 13 << 5 << 14 << 16 << 4;
			cf.nz << 0 << 2 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 6 << 1;
			cf.py << 13 << 11 << 12 << 6 << 5;
			cf.pz << 0 << 0 << 0 << -1 << -1;
			cf.nx << 4 << 6 << 8 << 4 << 9;
			cf.ny << 2 << 8 << 4 << 4 << 4;
			cf.nz << 2 << 1 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 11 << 11 << 6;
			cf.py << 5 << 5 << 6 << 13;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 8 << 3 << 2 << 8;
			cf.ny << 4 << 4 << 17 << 2;
			cf.nz << 1 << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 14 << 12 << 15 << 13;
			cf.py << 0 << 2 << 2 << 2 << 2;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 22 << 23 << 22 << 23 << 7;
			cf.ny << 0 << 3 << 1 << 2 << 4;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 15 << 18 << 19 << 9;
			cf.py << 12 << 11 << 12 << 12 << 9;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 2 << 22 << 23 << 21;
			cf.ny << 4 << 1 << 1 << 2 << 20;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 7 << 7;
			cf.py << 0 << 2 << 2;
			cf.pz << 1 << 0 << -1;
			cf.nx << 1 << 2 << 2;
			cf.ny << 2 << 0 << 2;
			cf.nz << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 11 << 11;
			cf.py << 6 << 9 << 8;
			cf.pz << 1 << 0 << 0;
			cf.nx << 9 << 2 << 8;
			cf.ny << 9 << 4 << 5;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 7 << 6 << 6;
			cf.py << 4 << 23 << 21 << 22;
			cf.pz << 2 << 0 << 0 << 0;
			cf.nx << 9 << 3 << 8 << 17;
			cf.ny << 21 << 2 << 5 << 1;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 8;
			cf.py << 4 << 12;
			cf.pz << 2 << 0;
			cf.nx << 3 << 0;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 5 << 1 << 8 << 4;
			cf.py << 15 << 12 << 3 << 23 << 12;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 23 << 10 << 22 << 21 << 11;
			cf.nz << 0 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 5;
			cf.py << 13 << 4;
			cf.pz << 0 << 2;
			cf.nx << 23 << 4;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 17;
			cf.py << 2 << 3;
			cf.pz << 0 << 0;
			cf.nx << 19 << 20;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 1 << 8 << 17 << 4;
			cf.py << 14 << 2 << 13 << 6 << 12;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 8 << 13 << 15 << 15 << 7;
			cf.ny << 10 << 9 << 15 << 14 << 8;
			cf.nz << 1 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 5;
			cf.py << 7 << 4;
			cf.pz << 1 << -1;
			cf.nx << 4 << 13;
			cf.ny << 2 << 21;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 4 << 2;
			cf.ny << 7 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 14 << 3 << 11;
			cf.py << 3 << 23 << 2 << 5;
			cf.pz << 2 << 0 << 2 << 0;
			cf.nx << 7 << 8 << 2 << 16;
			cf.ny << 8 << 0 << 1 << 15;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 8;
			cf.py << 0 << 0;
			cf.pz << 0 << 0;
			cf.nx << 2 << 2;
			cf.ny << 3 << 5;
			cf.nz << 2 << 2;
		}
		*a_iter++ = -1.95797;
		*a_iter++ = 1.95797;
		*a_iter++ = -1.225984;
		*a_iter++ = 1.225984;
		*a_iter++ = -0.8310246;
		*a_iter++ = 0.8310246;
		*a_iter++ = -0.8315741;
		*a_iter++ = 0.8315741;
		*a_iter++ = -0.7973616;
		*a_iter++ = 0.7973616;
		*a_iter++ = -0.7661959;
		*a_iter++ = 0.7661959;
		*a_iter++ = -0.6042118;
		*a_iter++ = 0.6042118;
		*a_iter++ = -0.6506833;
		*a_iter++ = 0.6506833;
		*a_iter++ = -0.4808219;
		*a_iter++ = 0.4808219;
		*a_iter++ = -0.6079504;
		*a_iter++ = 0.6079504;
		*a_iter++ = -0.5163994;
		*a_iter++ = 0.5163994;
		*a_iter++ = -0.5268142;
		*a_iter++ = 0.5268142;
		*a_iter++ = -0.4935685;
		*a_iter++ = 0.4935685;
		*a_iter++ = -0.4427544;
		*a_iter++ = 0.4427544;
		*a_iter++ = -0.4053949;
		*a_iter++ = 0.4053949;
		*a_iter++ = -0.4701274;
		*a_iter++ = 0.4701274;
		*a_iter++ = -0.4387648;
		*a_iter++ = 0.4387648;
		*a_iter++ = -0.4305499;
		*a_iter++ = 0.4305499;
		*a_iter++ = -0.4042607;
		*a_iter++ = 0.4042607;
		*a_iter++ = -0.4372088;
		*a_iter++ = 0.4372088;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 22;
		sc.threshold = -5.679317;
		sc.features.SetCount(22);
		sc.alpha.SetCount(44);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 3 << 17 << 14 << 13;
			cf.py << 4 << 0 << 13 << 2 << 3;
			cf.pz << 0 << 2 << 0 << 0 << 0;
			cf.nx << 7 << 4 << 14 << 23 << 11;
			cf.ny << 8 << 4 << 8 << 4 << 0;
			cf.nz << 1 << 1 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 12 << 6 << 12 << 12;
			cf.py << 12 << 8 << 3 << 10 << 9;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 9 << 8 << 15 << 15;
			cf.ny << 4 << 8 << 4 << 8 << 8;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 2 << 10;
			cf.py << 1 << 4 << 1;
			cf.pz << 1 << 2 << 0;
			cf.nx << 2 << 3 << 8;
			cf.ny << 5 << 4 << 4;
			cf.nz << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 17 << 6 << 6 << 16;
			cf.py << 2 << 12 << 4 << 14 << 12;
			cf.pz << 2 << 0 << 1 << 0 << 0;
			cf.nx << 8 << 3 << 7 << 5 << 15;
			cf.ny << 4 << 4 << 4 << 4 << 8;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 6 << 7 << 4 << 8;
			cf.py << 3 << 3 << 3 << 1 << 3;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 1;
			cf.ny << 5 << 4 << 3 << 2 << 0;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 18 << 9 << 0;
			cf.py << 14 << 7 << 0;
			cf.pz << 0 << 1 << -1;
			cf.nx << 8 << 14 << 8;
			cf.ny << 10 << 9 << 4;
			cf.nz << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 18 << 13;
			cf.pz << 0 << 0;
			cf.nx << 10 << 3;
			cf.ny << 16 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 11 << 6;
			cf.py << 10 << 12 << 11 << 13 << 6;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 5 << 21 << 22 << 22 << 22;
			cf.ny << 4 << 22 << 17 << 19 << 18;
			cf.nz << 2 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 9 << 15 << 4;
			cf.py << 7 << 7 << 23 << 4;
			cf.pz << 1 << 1 << 0 << 2;
			cf.nx << 8 << 5 << 0 << 3;
			cf.ny << 4 << 18 << 4 << 9;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 12 << 11 << 11;
			cf.py << 4 << 4 << 4 << 5 << 5;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 6 << 8 << 2 << 8;
			cf.ny << 4 << 9 << 9 << 2 << 4;
			cf.nz << 1 << 1 << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 3 << 3 << 4;
			cf.py << 10 << 9 << 14 << 13 << 15;
			cf.pz << 1 << 1 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 5 << 9 << 10 << 19 << 18;
			cf.nz << 2 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 13 << 12;
			cf.pz << 0 << 0;
			cf.nx << 9 << 2;
			cf.ny << 15 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 4 << 3 << 3 << 4;
			cf.py << 5 << 11 << 6 << 9 << 12;
			cf.pz << 1 << 0 << 1 << 0 << 0;
			cf.nx << 6 << 2 << 11 << 11 << 0;
			cf.ny << 9 << 1 << 5 << 20 << 18;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 9 << 17 << 19 << 16;
			cf.py << 2 << 0 << 2 << 2 << 1;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 22 << 23 << 11 << 23 << 23;
			cf.ny << 0 << 2 << 0 << 1 << 1;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 5 << 6 << 7 << 6;
			cf.py << 17 << 16 << 15 << 23 << 22;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 6 << 2 << 5 << 23;
			cf.ny << 8 << 1 << 2 << 3 << 1;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 11 << 10 << 6;
			cf.py << 14 << 13 << 18 << 4 << 22;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 3 << 2 << 4 << 1 << 2;
			cf.ny << 19 << 4 << 23 << 13 << 16;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 16 << 11 << 17;
			cf.py << 7 << 11 << 8 << 12;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 7 << 14 << 10 << 4;
			cf.ny << 4 << 7 << 10 << 4;
			cf.nz << 1 << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 4 << 2;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 9;
			cf.py << 0 << 1;
			cf.pz << 1 << 0;
			cf.nx << 4 << 5;
			cf.ny << 1 << 0;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 16;
			cf.py << 3 << 3;
			cf.pz << 0 << 0;
			cf.nx << 9 << 14;
			cf.ny << 4 << 21;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 1;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 8 << 9;
			cf.ny << 7 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 8 << 3;
			cf.pz << 0 << 2;
			cf.nx << 20 << 0;
			cf.ny << 3 << 3;
			cf.nz << 0 << -1;
		}
		*a_iter++ = -1.581077;
		*a_iter++ = 1.581077;
		*a_iter++ = -1.389689;
		*a_iter++ = 1.389689;
		*a_iter++ = -0.8733094;
		*a_iter++ = 0.8733094;
		*a_iter++ = -0.8525177;
		*a_iter++ = 0.8525177;
		*a_iter++ = -0.7416304;
		*a_iter++ = 0.7416304;
		*a_iter++ = -0.6609002;
		*a_iter++ = 0.6609002;
		*a_iter++ = -0.7119043;
		*a_iter++ = 0.7119043;
		*a_iter++ = -0.6204438;
		*a_iter++ = 0.6204438;
		*a_iter++ = -0.6638519;
		*a_iter++ = 0.6638519;
		*a_iter++ = -0.5518876;
		*a_iter++ = 0.5518876;
		*a_iter++ = -0.4898991;
		*a_iter++ = 0.4898991;
		*a_iter++ = -0.5508243;
		*a_iter++ = 0.5508243;
		*a_iter++ = -0.4635525;
		*a_iter++ = 0.4635525;
		*a_iter++ = -0.5163159;
		*a_iter++ = 0.5163159;
		*a_iter++ = -0.4495338;
		*a_iter++ = 0.4495338;
		*a_iter++ = -0.4515036;
		*a_iter++ = 0.4515036;
		*a_iter++ = -0.5130473;
		*a_iter++ = 0.5130473;
		*a_iter++ = -0.4694233;
		*a_iter++ = 0.4694233;
		*a_iter++ = -0.4022514;
		*a_iter++ = 0.4022514;
		*a_iter++ = -0.405569;
		*a_iter++ = 0.405569;
		*a_iter++ = -0.4151817;
		*a_iter++ = 0.4151817;
		*a_iter++ = -0.3352302;
		*a_iter++ = 0.3352302;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 32;
		sc.threshold = -5.363782;
		sc.features.SetCount(32);
		sc.alpha.SetCount(64);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 9 << 6 << 8 << 14;
			cf.py << 4 << 2 << 13 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 15 << 0 << 9 << 5;
			cf.ny << 2 << 7 << 3 << 8 << 8;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 16 << 3 << 6 << 11;
			cf.py << 3 << 13 << 1 << 4 << 3;
			cf.pz << 0 << 0 << 2 << 1 << 0;
			cf.nx << 7 << 4 << 8 << 14 << 14;
			cf.ny << 4 << 4 << 4 << 8 << 8;
			cf.nz << 1 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 19 << 18 << 19 << 19;
			cf.py << 6 << 13 << 13 << 12 << 12;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 23 << 5 << 23 << 23 << 11;
			cf.ny << 12 << 2 << 13 << 14 << 8;
			cf.nz << 0 << 2 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 6;
			cf.py << 11 << 13 << 12 << 10 << 6;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 6 << 8 << 3 << 9 << 9;
			cf.ny << 8 << 4 << 4 << 4 << 4;
			cf.nz << 1 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 3 << 5 << 8 << 11;
			cf.py << 12 << 8 << 3 << 11 << 8;
			cf.pz << 0 << 1 << 1 << 0 << 0;
			cf.nx << 4 << 0 << 1 << 1 << 9;
			cf.ny << 4 << 3 << 4 << 3 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 3 << 12 << 14 << 12;
			cf.py << 1 << 0 << 1 << 2 << 3;
			cf.pz << 0 << 2 << 0 << 0 << 0;
			cf.nx << 7 << 9 << 8 << 4 << 4;
			cf.ny << 5 << 4 << 10 << 2 << 2;
			cf.nz << 1 << 1 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 16 << 12 << 15 << 8;
			cf.py << 12 << 23 << 7 << 11 << 8;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 6 << 10 << 12 << 4;
			cf.ny << 4 << 4 << 10 << 6 << 3;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 4 << 5 << 2 << 2;
			cf.py << 13 << 14 << 14 << 7 << 7;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 0 << 0 << 0 << 0 << 1;
			cf.ny << 15 << 4 << 14 << 13 << 17;
			cf.nz << 0 << 2 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 7 << 7;
			cf.pz << 1 << -1;
			cf.nx << 4 << 7;
			cf.ny << 5 << 8;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 4 << 6 << 5 << 4;
			cf.py << 2 << 2 << 14 << 6 << 9;
			cf.pz << 1 << 1 << 0 << 1 << 1;
			cf.nx << 23 << 23 << 23 << 23 << 11;
			cf.ny << 0 << 3 << 2 << 1 << 0;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 2 << 3;
			cf.py << 23 << 4 << 7;
			cf.pz << 0 << 2 << 1;
			cf.nx << 10 << 21 << 23;
			cf.ny << 21 << 9 << 2;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 21 << 21 << 10 << 12;
			cf.py << 13 << 12 << 8 << 8 << 12;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 8 << 16 << 3 << 3 << 11;
			cf.ny << 4 << 8 << 4 << 3 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 21;
			cf.py << 4 << 12;
			cf.pz << 2 << -1;
			cf.nx << 2 << 3;
			cf.ny << 5 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 5 << 6 << 8 << 7;
			cf.py << 0 << 2 << 1 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 2 << 2 << 2 << 2;
			cf.ny << 0 << 0 << 1 << 2 << 2;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 2 << 2 << 11 << 10;
			cf.py << 10 << 12 << 8 << 11 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 5 << 2 << 4 << 2;
			cf.ny << 4 << 1 << 4 << 2 << 2;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 15 << 16 << 8 << 17;
			cf.py << 2 << 1 << 0 << 2;
			cf.pz << 0 << 0 << 1 << 0;
			cf.nx << 19 << 20 << 0 << 8;
			cf.ny << 1 << 2 << 11 << 10;
			cf.nz << 0 << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 16;
			cf.py << 12 << 12;
			cf.pz << 0 << 0;
			cf.nx << 8 << 9;
			cf.ny << 5 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 0 << 0;
			cf.py << 12 << 13 << 0 << 0;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 10 << 10 << 9 << 10;
			cf.ny << 10 << 12 << 13 << 11;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 10 << 8;
			cf.py << 5 << 2 << 6;
			cf.pz << 0 << -1 << -1;
			cf.nx << 8 << 12 << 4;
			cf.ny << 4 << 17 << 4;
			cf.nz << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 21 << 10 << 20 << 20;
			cf.py << 11 << 13 << 7 << 13 << 14;
			cf.pz << 1 << 0 << 1 << 0 << 0;
			cf.nx << 23 << 23 << 11 << 23 << 17;
			cf.ny << 23 << 22 << 11 << 21 << 21;
			cf.nz << 0 << 0 << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 3 << 9;
			cf.pz << 2 << 1;
			cf.nx << 9 << 23;
			cf.ny << 4 << 22;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 2 << 2 << 5;
			cf.py << 11 << 5 << 4 << 20;
			cf.pz << 1 << 2 << 2 << 0;
			cf.nx << 4 << 23 << 11 << 23;
			cf.ny << 10 << 22 << 11 << 21;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 5;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 8 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 5;
			cf.py << 4 << 9;
			cf.pz << 2 << 1;
			cf.nx << 10 << 10;
			cf.ny << 16 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 0;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 3 << 12 << 13 << 6;
			cf.py << 11 << 5 << 23 << 23 << 7;
			cf.pz << 1 << 2 << 0 << 0 << 1;
			cf.nx << 1 << 0 << 0 << 0 << 0;
			cf.ny << 23 << 20 << 19 << 21 << 21;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 10 << 9 << 6 << 13 << 13;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 8 << 8 << 4 << 4 << 9;
			cf.ny << 4 << 11 << 5 << 4 << 5;
			cf.nz << 1 << 1 << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 18;
			cf.py << 8 << 15;
			cf.pz << 1 << 0;
			cf.nx << 15 << 4;
			cf.ny << 15 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 13;
			cf.py << 6 << 17;
			cf.pz << 1 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 19 << 10 << 20 << 18 << 18;
			cf.py << 2 << 0 << 2 << 2 << 2;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 22 << 23 << 22 << 11 << 23;
			cf.ny << 1 << 3 << 0 << 1 << 2;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 2 << 2 << 2 << 6;
			cf.py << 7 << 2 << 5 << 4 << 14;
			cf.pz << 1 << 2 << 2 << 2 << 0;
			cf.nx << 16 << 7 << 9 << 15 << 23;
			cf.ny << 8 << 0 << 3 << 11 << 2;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 10 << 9 << 9 << 5;
			cf.py << 2 << 0 << 0 << 1 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 3 << 2 << 3 << 2 << 2;
			cf.ny << 11 << 3 << 9 << 5 << 5;
			cf.nz << 1 << 2 << 1 << 2 << -1;
		}
		*a_iter++ = -1.490426;
		*a_iter++ = 1.490426;
		*a_iter++ = -1.21428;
		*a_iter++ = 1.21428;
		*a_iter++ = -0.8124863;
		*a_iter++ = 0.8124863;
		*a_iter++ = -0.7307594;
		*a_iter++ = 0.7307594;
		*a_iter++ = -0.7377259;
		*a_iter++ = 0.7377259;
		*a_iter++ = -0.5982859;
		*a_iter++ = 0.5982859;
		*a_iter++ = -0.6451736;
		*a_iter++ = 0.6451736;
		*a_iter++ = -0.6117417;
		*a_iter++ = 0.6117417;
		*a_iter++ = -0.5438949;
		*a_iter++ = 0.5438949;
		*a_iter++ = -0.4563701;
		*a_iter++ = 0.4563701;
		*a_iter++ = -0.4975362;
		*a_iter++ = 0.4975362;
		*a_iter++ = -0.4707373;
		*a_iter++ = 0.4707373;
		*a_iter++ = -0.5013868;
		*a_iter++ = 0.5013868;
		*a_iter++ = -0.5139018;
		*a_iter++ = 0.5139018;
		*a_iter++ = -0.4728007;
		*a_iter++ = 0.4728007;
		*a_iter++ = -0.4839748;
		*a_iter++ = 0.4839748;
		*a_iter++ = -0.4852528;
		*a_iter++ = 0.4852528;
		*a_iter++ = -0.5768956;
		*a_iter++ = 0.5768956;
		*a_iter++ = -0.3635091;
		*a_iter++ = 0.3635091;
		*a_iter++ = -0.419009;
		*a_iter++ = 0.419009;
		*a_iter++ = -0.3854715;
		*a_iter++ = 0.3854715;
		*a_iter++ = -0.3409591;
		*a_iter++ = 0.3409591;
		*a_iter++ = -0.3440222;
		*a_iter++ = 0.3440222;
		*a_iter++ = -0.3375895;
		*a_iter++ = 0.3375895;
		*a_iter++ = -0.3367032;
		*a_iter++ = 0.3367032;
		*a_iter++ = -0.3708106;
		*a_iter++ = 0.3708106;
		*a_iter++ = -0.3260956;
		*a_iter++ = 0.3260956;
		*a_iter++ = -0.3657681;
		*a_iter++ = 0.3657681;
		*a_iter++ = -0.35188;
		*a_iter++ = 0.35188;
		*a_iter++ = -0.3845758;
		*a_iter++ = 0.3845758;
		*a_iter++ = -0.2832236;
		*a_iter++ = 0.2832236;
		*a_iter++ = -0.2865156;
		*a_iter++ = 0.2865156;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 45;
		sc.threshold = -5.479836;
		sc.features.SetCount(45);
		sc.alpha.SetCount(90);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 6 << 17 << 6 << 9;
			cf.py << 2 << 13 << 13 << 4 << 3;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 3 << 9 << 4 << 8 << 14;
			cf.ny << 5 << 8 << 4 << 4 << 8;
			cf.nz << 2 << 0 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 8 << 11 << 6 << 7;
			cf.py << 1 << 2 << 3 << 14 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 4 << 0 << 0;
			cf.ny << 4 << 2 << 4 << 1 << 0;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 11 << 11 << 11;
			cf.py << 2 << 4 << 10 << 8 << 6;
			cf.pz << 2 << 2 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 3 << 23 << 23;
			cf.ny << 4 << 4 << 4 << 16 << 18;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 16 << 17 << 15 << 9;
			cf.py << 2 << 2 << 2 << 2 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 22 << 22 << 21 << 23 << 23;
			cf.ny << 1 << 2 << 0 << 5 << 4;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 3 << 17 << 18 << 6;
			cf.py << 11 << 2 << 11 << 11 << 4;
			cf.pz << 0 << 2 << 0 << 0 << 1;
			cf.nx << 3 << 8 << 1 << 4 << 23;
			cf.ny << 4 << 4 << 3 << 9 << 4;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 4 << 0;
			cf.pz << 2 << -1;
			cf.nx << 7 << 4;
			cf.ny << 8 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 12 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 10 << 15;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 2 << 7 << 1;
			cf.py << 7 << 7 << 3 << 4;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 0 << 2 << 1 << 2;
			cf.ny << 6 << 20 << 14 << 16;
			cf.nz << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 12 << 12 << 13 << 9;
			cf.py << 23 << 5 << 6 << 5 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 18 << 2 << 8 << 14;
			cf.ny << 4 << 9 << 0 << 12 << 7;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 10 << 13 << 11 << 9;
			cf.py << 0 << 3 << 2 << 3 << 2;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 11 << 22 << 22 << 22;
			cf.ny << 2 << 6 << 15 << 2 << 0;
			cf.nz << 2 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 7 << 5 << 8 << 5;
			cf.py << 23 << 12 << 12 << 12 << 13;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 18 << 3 << 1 << 22;
			cf.ny << 4 << 4 << 4 << 2 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 22 << 22 << 22 << 21 << 22;
			cf.py << 9 << 11 << 10 << 14 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 23 << 23 << 11 << 1 << 22;
			cf.ny << 23 << 23 << 11 << 2 << 0;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 18 << 7;
			cf.pz << 0 << 1;
			cf.nx << 10 << 8;
			cf.ny << 16 << 19;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 12 << 11 << 6 << 6;
			cf.py << 4 << 4 << 4 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 3 << 8 << 7 << 8 << 4;
			cf.ny << 5 << 4 << 4 << 10 << 4;
			cf.nz << 2 << 1 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 12 << 4 << 15;
			cf.py << 13 << 12 << 0 << 11;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 13 << 14 << 13 << 14;
			cf.ny << 9 << 12 << 10 << 13;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 3 << 3;
			cf.pz << 2 << -1;
			cf.nx << 9 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 7 << 0;
			cf.py << 7 << 5 << 5;
			cf.pz << 1 << -1 << -1;
			cf.nx << 4 << 15 << 9;
			cf.ny << 5 << 14 << 9;
			cf.nz << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 20 << 7 << 10 << 16;
			cf.py << 17 << 12 << 6 << 4 << 23;
			cf.pz << 0 << 0 << 1 << 1 << 0;
			cf.nx << 1 << 2 << 2 << 1 << 1;
			cf.ny << 3 << 0 << 1 << 2 << 2;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 1 << 1 << 11 << 2;
			cf.py << 16 << 4 << 5 << 12 << 14;
			cf.pz << 0 << 1 << 1 << 0 << 0;
			cf.nx << 4 << 6 << 3 << 19 << 1;
			cf.ny << 4 << 2 << 5 << 19 << 2;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 15 << 14 << 14;
			cf.py << 1 << 1 << 0;
			cf.pz << 0 << 0 << 0;
			cf.nx << 4 << 8 << 4;
			cf.ny << 3 << 4 << 2;
			cf.nz << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 3 << 1 << 2 << 7;
			cf.py << 8 << 12 << 4 << 9 << 13;
			cf.pz << 1 << 0 << 2 << 1 << 0;
			cf.nx << 1 << 1 << 0 << 0 << 0;
			cf.ny << 21 << 20 << 18 << 17 << 9;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 15 << 17 << 16 << 16;
			cf.py << 12 << 12 << 22 << 23 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 3 << 16 << 1 << 0;
			cf.ny << 8 << 6 << 8 << 3 << 9;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 17 << 18 << 18 << 18;
			cf.py << 6 << 12 << 12 << 13 << 13;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 23 << 23 << 20 << 11 << 11;
			cf.ny << 12 << 13 << 23 << 7 << 8;
			cf.nz << 0 << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 4 << 4;
			cf.ny << 10 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 22 << 19 << 12;
			cf.py << 5 << 8 << 14 << 9;
			cf.pz << 2 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 4 << 2;
			cf.ny << 4 << 4 << 1 << 2;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 21;
			cf.py << 7 << 14;
			cf.pz << 1 << -1;
			cf.nx << 4 << 2;
			cf.ny << 7 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 4 << 17;
			cf.py << 3 << 1 << 6;
			cf.pz << 0 << 1 << -1;
			cf.nx << 3 << 4 << 5;
			cf.ny << 0 << 2 << 1;
			cf.nz << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 15 << 7 << 14 << 0;
			cf.py << 3 << 1 << 3 << 7;
			cf.pz << 0 << 1 << 0 << -1;
			cf.nx << 8 << 18 << 17 << 18;
			cf.ny << 0 << 1 << 1 << 2;
			cf.nz << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 6;
			cf.py << 10 << 11 << 12 << 13 << 6;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 8 << 15 << 15 << 4 << 8;
			cf.ny << 10 << 10 << 9 << 2 << 4;
			cf.nz << 0 << 0 << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 12;
			cf.py << 13 << 11;
			cf.pz << 0 << -1;
			cf.nx << 9 << 8;
			cf.ny << 4 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 10 << 9 << 12 << 11 << 4;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 9 << 8 << 9 << 9;
			cf.ny << 10 << 4 << 4 << 5 << 5;
			cf.nz << 1 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 0 << 1;
			cf.py << 1 << 9 << 8;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 3 << 3;
			cf.ny << 7 << 15 << 16;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 15 << 23;
			cf.pz << 0 << 0;
			cf.nx << 9 << 18;
			cf.ny << 21 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 4 << 19 << 18 << 8;
			cf.py << 12 << 3 << 12 << 17 << 6;
			cf.pz << 0 << 2 << 0 << 0 << 1;
			cf.nx << 23 << 23 << 11 << 22 << 16;
			cf.ny << 0 << 1 << 0 << 21 << -1;
			cf.nz << 0 << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 13 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 20 << 10 << 10 << 21;
			cf.py << 13 << 14 << 10 << 7 << 11;
			cf.pz << 0 << 0 << 1 << 1 << 0;
			cf.nx << 4 << 4 << 4 << 5 << 5;
			cf.ny << 18 << 17 << 19 << 20 << 20;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 11 << 13;
			cf.pz << 1 << 0;
			cf.nx << 12 << 4;
			cf.ny << 17 << 17;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 13 << 1;
			cf.pz << 0 << -1;
			cf.nx << 1 << 2;
			cf.ny << 1 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 7;
			cf.py << 17 << 7;
			cf.pz << 0 << 1;
			cf.nx << 14 << 4;
			cf.ny << 15 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 11;
			cf.py << 3 << 8;
			cf.pz << 2 << 0;
			cf.nx << 13 << 13;
			cf.ny << 9 << 8;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 9 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 6 << 9;
			cf.py << 9 << 10 << 11;
			cf.pz << 0 << -1 << -1;
			cf.nx << 2 << 1 << 5;
			cf.ny << 2 << 1 << 6;
			cf.nz << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 5 << 5 << 1;
			cf.py << 11 << 11 << 11 << 3;
			cf.pz << 1 << 0 << 1 << 2;
			cf.nx << 0 << 0 << 5 << 4;
			cf.ny << 23 << 22 << 0 << 0;
			cf.nz << 0 << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 7 << 17 << 15 << 16;
			cf.py << 1 << 0 << 2 << 2 << 0;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 7 << 4 << 7 << 4 << 8;
			cf.ny << 5 << 2 << 4 << 3 << 4;
			cf.nz << 1 << 2 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 11 << 23;
			cf.pz << 1 << 0;
			cf.nx << 12 << 4;
			cf.ny << 21 << 2;
			cf.nz << 0 << -1;
		}
		*a_iter++ = -1.5358;
		*a_iter++ = 1.5358;
		*a_iter++ = -0.8580514;
		*a_iter++ = 0.8580514;
		*a_iter++ = -0.862521;
		*a_iter++ = 0.862521;
		*a_iter++ = -0.71775;
		*a_iter++ = 0.71775;
		*a_iter++ = -0.6832222;
		*a_iter++ = 0.6832222;
		*a_iter++ = -0.5736298;
		*a_iter++ = 0.5736298;
		*a_iter++ = -0.5028217;
		*a_iter++ = 0.5028217;
		*a_iter++ = -0.5091788;
		*a_iter++ = 0.5091788;
		*a_iter++ = -0.579194;
		*a_iter++ = 0.579194;
		*a_iter++ = -0.4924942;
		*a_iter++ = 0.4924942;
		*a_iter++ = -0.5489055;
		*a_iter++ = 0.5489055;
		*a_iter++ = -0.452819;
		*a_iter++ = 0.452819;
		*a_iter++ = -0.4748324;
		*a_iter++ = 0.4748324;
		*a_iter++ = -0.4150403;
		*a_iter++ = 0.4150403;
		*a_iter++ = -0.4820464;
		*a_iter++ = 0.4820464;
		*a_iter++ = -0.4840212;
		*a_iter++ = 0.4840212;
		*a_iter++ = -0.3941872;
		*a_iter++ = 0.3941872;
		*a_iter++ = -0.3663507;
		*a_iter++ = 0.3663507;
		*a_iter++ = -0.3814835;
		*a_iter++ = 0.3814835;
		*a_iter++ = -0.3936426;
		*a_iter++ = 0.3936426;
		*a_iter++ = -0.304997;
		*a_iter++ = 0.304997;
		*a_iter++ = -0.3604256;
		*a_iter++ = 0.3604256;
		*a_iter++ = -0.3974041;
		*a_iter++ = 0.3974041;
		*a_iter++ = -0.4203486;
		*a_iter++ = 0.4203486;
		*a_iter++ = -0.3174435;
		*a_iter++ = 0.3174435;
		*a_iter++ = -0.3426336;
		*a_iter++ = 0.3426336;
		*a_iter++ = -0.449215;
		*a_iter++ = 0.449215;
		*a_iter++ = -0.3538784;
		*a_iter++ = 0.3538784;
		*a_iter++ = -0.3679703;
		*a_iter++ = 0.3679703;
		*a_iter++ = -0.3985452;
		*a_iter++ = 0.3985452;
		*a_iter++ = -0.2884028;
		*a_iter++ = 0.2884028;
		*a_iter++ = -0.2797264;
		*a_iter++ = 0.2797264;
		*a_iter++ = -0.2664214;
		*a_iter++ = 0.2664214;
		*a_iter++ = -0.2484857;
		*a_iter++ = 0.2484857;
		*a_iter++ = -0.2581492;
		*a_iter++ = 0.2581492;
		*a_iter++ = -0.2943778;
		*a_iter++ = 0.2943778;
		*a_iter++ = -0.2315507;
		*a_iter++ = 0.2315507;
		*a_iter++ = -0.2979337;
		*a_iter++ = 0.2979337;
		*a_iter++ = -0.2976173;
		*a_iter++ = 0.2976173;
		*a_iter++ = -0.2847965;
		*a_iter++ = 0.2847965;
		*a_iter++ = -0.2814763;
		*a_iter++ = 0.2814763;
		*a_iter++ = -0.2489068;
		*a_iter++ = 0.2489068;
		*a_iter++ = -0.2632427;
		*a_iter++ = 0.2632427;
		*a_iter++ = -0.3308292;
		*a_iter++ = 0.3308292;
		*a_iter++ = -0.279017;
		*a_iter++ = 0.279017;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 61;
		sc.threshold = -5.239104;
		sc.features.SetCount(61);
		sc.alpha.SetCount(122);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 8 << 11 << 15 << 6;
			cf.py << 3 << 6 << 5 << 3 << 4;
			cf.pz << 0 << 1 << 0 << 0 << 1;
			cf.nx << 3 << 9 << 14 << 8 << 4;
			cf.ny << 4 << 8 << 8 << 7 << 2;
			cf.nz << 1 << 0 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 12 << 10 << 6 << 9;
			cf.py << 3 << 3 << 2 << 13 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 5 << 2 << 2;
			cf.ny << 13 << 1 << 8 << 5 << 2;
			cf.nz << 0 << 1 << 1 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 5 << 11 << 11 << 4;
			cf.py << 9 << 13 << 10 << 11 << 6;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 4 << 15 << 9 << 3 << 3;
			cf.ny << 5 << 8 << 9 << 4 << 4;
			cf.nz << 1 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 16 << 8 << 17 << 17;
			cf.py << 1 << 2 << 0 << 2 << 2;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 23 << 23 << 23 << 23 << 23;
			cf.ny << 4 << 0 << 2 << 3 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 18 << 17 << 18;
			cf.py << 7 << 13 << 13 << 14;
			cf.pz << 1 << 0 << 0 << 0;
			cf.nx << 9 << 7 << 4 << 8;
			cf.ny << 4 << 10 << 2 << 4;
			cf.nz << 1 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 11 << 12 << 12 << 6;
			cf.py << 6 << 5 << 14 << 5 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 13 << 8 << 14 << 7 << 7;
			cf.ny << 16 << 4 << 7 << 4 << 4;
			cf.nz << 0 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 6 << 3 << 7 << 12;
			cf.py << 7 << 12 << 7 << 11 << 8;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 16 << 4 << 4 << 4 << 7;
			cf.ny << 8 << 4 << 4 << 4 << 4;
			cf.nz << 0 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 4 << 5 << 3 << 3;
			cf.py << 2 << 3 << 2 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 1 << 0 << 1 << 0 << 0;
			cf.ny << 0 << 3 << 1 << 1 << 2;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 9;
			cf.py << 11 << 6;
			cf.pz << 0 << 1;
			cf.nx << 14 << 5;
			cf.ny << 9 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 19 << 19 << 10 << 20;
			cf.py << 7 << 20 << 14 << 6 << 12;
			cf.pz << 1 << 0 << 0 << 1 << 0;
			cf.nx << 23 << 22 << 11 << 23 << 23;
			cf.ny << 21 << 23 << 9 << 20 << 20;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 5 << 1 << 1;
			cf.py << 8 << 6 << 6 << 9 << 4;
			cf.pz << 0 << 1 << 1 << 0 << 2;
			cf.nx << 3 << 3 << 3 << 2 << 5;
			cf.ny << 4 << 4 << 2 << 5 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 12 << 3 << 11 << 11;
			cf.py << 2 << 2 << 0 << 1 << 2;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 3 << 6 << 8 << 4 << 3;
			cf.ny << 2 << 9 << 4 << 4 << 5;
			cf.nz << 2 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 12 << 6;
			cf.py << 11 << 12 << 9;
			cf.pz << 0 << 0 << -1;
			cf.nx << 2 << 1 << 9;
			cf.ny << 6 << 1 << 14;
			cf.nz << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 3 << 17 << 16 << 16;
			cf.py << 4 << 2 << 14 << 23 << 13;
			cf.pz << 1 << 2 << 0 << 0 << 0;
			cf.nx << 8 << 10 << 21 << 5 << 1;
			cf.ny << 4 << 10 << 11 << 0 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 6 << 1 << 3 << 3;
			cf.py << 15 << 14 << 4 << 7 << 7;
			cf.pz << 0 << 0 << 2 << 1 << -1;
			cf.nx << 1 << 0 << 0 << 1 << 1;
			cf.ny << 5 << 8 << 7 << 18 << 17;
			cf.nz << 2 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 12 << 5 << 3;
			cf.py << 6 << 12 << 2 << 7;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 14 << 13 << 13 << 7;
			cf.ny << 12 << 10 << 9 << 8;
			cf.nz << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 15;
			cf.pz << 1 << 0;
			cf.nx << 3 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 10 << 12 << 2;
			cf.py << 18 << 18 << 18 << 3;
			cf.pz << 0 << 0 << 0 << 2;
			cf.nx << 11 << 17 << 4 << 16;
			cf.ny << 16 << 4 << 4 << 21;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 8 << 8 << 5 << 2;
			cf.py << 4 << 4 << 4 << 2 << 3;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 2 << 2 << 4 << 4 << 2;
			cf.ny << 1 << 2 << 10 << 5 << 4;
			cf.nz << 2 << 2 << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 18 << 14 << 18;
			cf.py << 7 << 16 << 23 << 15;
			cf.pz << 1 << 0 << 0 << 0;
			cf.nx << 14 << 3 << 1 << 0;
			cf.ny << 21 << 1 << 9 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 3;
			cf.py << 9 << 5;
			cf.pz << 0 << 2;
			cf.nx << 8 << 1;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 1 << 1;
			cf.pz << 1 << -1;
			cf.nx << 19 << 20;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 10 << 10;
			cf.py << 6 << 6 << 8;
			cf.pz << 1 << -1 << -1;
			cf.nx << 22 << 21 << 22;
			cf.ny << 13 << 18 << 12;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 4 << 1;
			cf.pz << 2 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 21 << 21 << 21 << 21;
			cf.py << 19 << 17 << 18 << 15 << 16;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 11 << 21 << 6 << 1 << 21;
			cf.ny << 17 << 1 << 10 << 0 << 2;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 3 << 4 << 4 << 4;
			cf.py << 23 << 13 << 14 << 16 << 13;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 21 << 22 << 22 << 22 << 22;
			cf.ny << 23 << 21 << 20 << 19 << 19;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 6 << 6;
			cf.pz << 0 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 23 << 11 << 23 << 23;
			cf.py << 8 << 12 << 6 << 11 << 10;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 4 << 3 << 8 << 8;
			cf.ny << 3 << 8 << 4 << 4 << 4;
			cf.nz << 1 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 9 << 4 << 7 << 10;
			cf.py << 2 << 1 << 0 << 2 << 1;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 5 << 5 << 6 << 4 << 4;
			cf.ny << 1 << 0 << 0 << 2 << 1;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 2;
			cf.py << 13 << 6;
			cf.pz << 0 << -1;
			cf.nx << 15 << 9;
			cf.ny << 15 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 4 << 9;
			cf.pz << 2 << 1;
			cf.nx << 3 << 13;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 6 << 2;
			cf.py << 10 << 22 << 4;
			cf.pz << 1 << 0 << 2;
			cf.nx << 4 << 2 << 1;
			cf.ny << 10 << 4 << 3;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 9 << 7;
			cf.pz << 0 << 1;
			cf.nx << 0 << 0;
			cf.ny << 23 << 22;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 7;
			cf.py << 0 << 1;
			cf.pz << 0 << 0;
			cf.nx << 4 << 4;
			cf.ny << 8 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 4 << 4 << 6 << 3;
			cf.py << 8 << 4 << 5 << 5 << 3;
			cf.pz << 1 << 2 << 2 << 1 << 2;
			cf.nx << 1 << 0 << 2 << 0 << 0;
			cf.ny << 1 << 0 << 0 << 2 << 4;
			cf.nz << 0 << 2 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 4 << 4;
			cf.py << 6 << 1 << 5;
			cf.pz << 1 << -1 << -1;
			cf.nx << 5 << 23 << 22;
			cf.ny << 4 << 13 << 7;
			cf.nz << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 6 << 5;
			cf.pz << 1 << 1;
			cf.nx << 6 << 0;
			cf.ny << 9 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 1 << 1 << 0 << 0;
			cf.py << 5 << 18 << 19 << 16 << 6;
			cf.pz << 2 << 0 << 0 << 0 << 1;
			cf.nx << 5 << 9 << 4 << 8 << 8;
			cf.ny << 8 << 7 << 3 << 7 << 7;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 12;
			cf.py << 23 << 23;
			cf.pz << 0 << 0;
			cf.nx << 7 << 6;
			cf.ny << 8 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 19;
			cf.py << 12 << 8;
			cf.pz << 0 << 0;
			cf.nx << 18 << 5;
			cf.ny << 8 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 8 << 6 << 4 << 4;
			cf.py << 3 << 23 << 14 << 6 << 9;
			cf.pz << 2 << 0 << 0 << 1 << 1;
			cf.nx << 0 << 0 << 0 << 0 << 1;
			cf.ny << 21 << 20 << 5 << 19 << 23;
			cf.nz << 0 << 0 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 22;
			cf.py << 4 << 14;
			cf.pz << 0 << -1;
			cf.nx << 3 << 8;
			cf.ny << 1 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 0 << 1 << 1;
			cf.py << 6 << 8 << 3 << 12 << 7;
			cf.pz << 1 << 1 << 2 << 0 << 1;
			cf.nx << 21 << 21 << 19 << 10 << 10;
			cf.ny << 14 << 16 << 23 << 9 << 9;
			cf.nz << 0 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 23 << 2;
			cf.pz << 0 << 2;
			cf.nx << 10 << 3;
			cf.ny << 21 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 9 << 9;
			cf.ny << 11 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 11 << 23 << 23 << 23;
			cf.py << 18 << 10 << 19 << 20 << 16;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 3 << 3 << 2 << 3 << 2;
			cf.ny << 15 << 16 << 10 << 17 << 9;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 14;
			cf.py << 7 << 18;
			cf.pz << 1 << 0;
			cf.nx << 7 << 10;
			cf.ny << 8 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 6 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 17 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 3 << 3;
			cf.py << 11 << 17 << 19;
			cf.pz << 1 << 0 << 0;
			cf.nx << 7 << 7 << 4;
			cf.ny << 8 << 8 << 5;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 6 << 5;
			cf.pz << 1 << -1;
			cf.nx << 2 << 9;
			cf.ny << 4 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 8 << 9 << 2 << 2;
			cf.py << 18 << 13 << 12 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 2 << -1;
			cf.nx << 23 << 11 << 23 << 11 << 11;
			cf.ny << 13 << 6 << 14 << 7 << 8;
			cf.nz << 0 << 1 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 11;
			cf.py << 6 << 13;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 10;
			cf.py << 0 << 6;
			cf.pz << 1 << 1;
			cf.nx << 9 << 4;
			cf.ny << 6 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 10 << 9;
			cf.py << 8 << 6 << 0;
			cf.pz << 1 << -1 << -1;
			cf.nx << 2 << 2 << 2;
			cf.ny << 15 << 16 << 9;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 15 << 0;
			cf.py << 2 << 2 << 5;
			cf.pz << 0 << 0 << -1;
			cf.nx << 17 << 17 << 18;
			cf.ny << 0 << 1 << 2;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 10 << 9;
			cf.ny << 12 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 7 << 8;
			cf.pz << 1 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 19 << 18 << 10 << 5 << 20;
			cf.pz << 0 << 0 << 1 << 2 << 0;
			cf.nx << 4 << 8 << 2 << 4 << 4;
			cf.ny << 4 << 15 << 5 << 10 << 10;
			cf.nz << 1 << 0 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 13 << 18;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 22 << 22 << 11 << 22;
			cf.py << 16 << 13 << 7 << 6 << 14;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 13 << 7 << 15 << 14 << 14;
			cf.ny << 6 << 3 << 7 << 6 << 6;
			cf.nz << 0 << 1 << 0 << 0 << -1;
		}
		*a_iter++ = -1.428861;
		*a_iter++ = 1.428861;
		*a_iter++ = -0.8591837;
		*a_iter++ = 0.8591837;
		*a_iter++ = -0.7734305;
		*a_iter++ = 0.7734305;
		*a_iter++ = -0.653446;
		*a_iter++ = 0.653446;
		*a_iter++ = -0.6262547;
		*a_iter++ = 0.6262547;
		*a_iter++ = -0.5231782;
		*a_iter++ = 0.5231782;
		*a_iter++ = -0.4984303;
		*a_iter++ = 0.4984303;
		*a_iter++ = -0.4913187;
		*a_iter++ = 0.4913187;
		*a_iter++ = -0.4852198;
		*a_iter++ = 0.4852198;
		*a_iter++ = -0.4906681;
		*a_iter++ = 0.4906681;
		*a_iter++ = -0.4126248;
		*a_iter++ = 0.4126248;
		*a_iter++ = -0.4590814;
		*a_iter++ = 0.4590814;
		*a_iter++ = -0.4653825;
		*a_iter++ = 0.4653825;
		*a_iter++ = -0.41796;
		*a_iter++ = 0.41796;
		*a_iter++ = -0.4357392;
		*a_iter++ = 0.4357392;
		*a_iter++ = -0.4087982;
		*a_iter++ = 0.4087982;
		*a_iter++ = -0.4594812;
		*a_iter++ = 0.4594812;
		*a_iter++ = -0.4858794;
		*a_iter++ = 0.4858794;
		*a_iter++ = -0.371358;
		*a_iter++ = 0.371358;
		*a_iter++ = -0.3894534;
		*a_iter++ = 0.3894534;
		*a_iter++ = -0.3127168;
		*a_iter++ = 0.3127168;
		*a_iter++ = -0.4012654;
		*a_iter++ = 0.4012654;
		*a_iter++ = -0.3370552;
		*a_iter++ = 0.3370552;
		*a_iter++ = -0.3534712;
		*a_iter++ = 0.3534712;
		*a_iter++ = -0.384345;
		*a_iter++ = 0.384345;
		*a_iter++ = -0.2688805;
		*a_iter++ = 0.2688805;
		*a_iter++ = -0.3500203;
		*a_iter++ = 0.3500203;
		*a_iter++ = -0.282712;
		*a_iter++ = 0.282712;
		*a_iter++ = -0.3742119;
		*a_iter++ = 0.3742119;
		*a_iter++ = -0.3219074;
		*a_iter++ = 0.3219074;
		*a_iter++ = -0.2544953;
		*a_iter++ = 0.2544953;
		*a_iter++ = -0.3355513;
		*a_iter++ = 0.3355513;
		*a_iter++ = -0.267267;
		*a_iter++ = 0.267267;
		*a_iter++ = -0.2932047;
		*a_iter++ = 0.2932047;
		*a_iter++ = -0.2404618;
		*a_iter++ = 0.2404618;
		*a_iter++ = -0.2354372;
		*a_iter++ = 0.2354372;
		*a_iter++ = -0.2657955;
		*a_iter++ = 0.2657955;
		*a_iter++ = -0.2293701;
		*a_iter++ = 0.2293701;
		*a_iter++ = -0.2708918;
		*a_iter++ = 0.2708918;
		*a_iter++ = -0.2340181;
		*a_iter++ = 0.2340181;
		*a_iter++ = -0.2464815;
		*a_iter++ = 0.2464815;
		*a_iter++ = -0.2944239;
		*a_iter++ = 0.2944239;
		*a_iter++ = -0.240796;
		*a_iter++ = 0.240796;
		*a_iter++ = -0.3029642;
		*a_iter++ = 0.3029642;
		*a_iter++ = -0.2684602;
		*a_iter++ = 0.2684602;
		*a_iter++ = -0.2495078;
		*a_iter++ = 0.2495078;
		*a_iter++ = -0.2539708;
		*a_iter++ = 0.2539708;
		*a_iter++ = -0.2989293;
		*a_iter++ = 0.2989293;
		*a_iter++ = -0.2391309;
		*a_iter++ = 0.2391309;
		*a_iter++ = -0.2531372;
		*a_iter++ = 0.2531372;
		*a_iter++ = -0.250039;
		*a_iter++ = 0.250039;
		*a_iter++ = -0.2295077;
		*a_iter++ = 0.2295077;
		*a_iter++ = -0.2526125;
		*a_iter++ = 0.2526125;
		*a_iter++ = -0.2337182;
		*a_iter++ = 0.2337182;
		*a_iter++ = -0.1984756;
		*a_iter++ = 0.1984756;
		*a_iter++ = -0.3089996;
		*a_iter++ = 0.3089996;
		*a_iter++ = -0.2589053;
		*a_iter++ = 0.2589053;
		*a_iter++ = -0.296249;
		*a_iter++ = 0.296249;
		*a_iter++ = -0.245866;
		*a_iter++ = 0.245866;
		*a_iter++ = -0.2515206;
		*a_iter++ = 0.2515206;
		*a_iter++ = -0.2637299;
		*a_iter++ = 0.2637299;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 80;
		sc.threshold = -5.185898;
		sc.features.SetCount(80);
		sc.alpha.SetCount(160);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 17 << 13 << 10 << 15;
			cf.py << 9 << 13 << 3 << 3 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 14 << 6 << 9 << 4;
			cf.ny << 10 << 9 << 8 << 8 << 2;
			cf.nz << 1 << 0 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 11 << 8 << 10 << 9;
			cf.py << 7 << 4 << 3 << 3 << 3;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 2 << 1 << 5 << 0 << 0;
			cf.ny << 2 << 15 << 8 << 4 << 13;
			cf.nz << 2 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 4 << 17;
			cf.py << 7 << 9 << 8 << 6 << 11;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 8 << 8 << 8 << 3 << 0;
			cf.ny << 4 << 8 << 8 << 8 << 13;
			cf.nz << 1 << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 15 << 7 << 16 << 16;
			cf.py << 3 << 3 << 1 << 3 << 3;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 23 << 22 << 23 << 22 << 22;
			cf.ny << 6 << 2 << 14 << 3 << 4;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 4 << 7 << 15;
			cf.py << 4 << 2 << 6 << 17;
			cf.pz << 1 << 2 << 1 << 0;
			cf.nx << 3 << 8 << 3 << 14;
			cf.ny << 4 << 4 << 10 << 22;
			cf.nz << 1 << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 5 << 22;
			cf.py << 7 << 7 << 5;
			cf.pz << 1 << -1 << -1;
			cf.nx << 2 << 2 << 4;
			cf.ny << 5 << 2 << 7;
			cf.nz << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 6 << 5 << 6 << 3;
			cf.py << 0 << 1 << 2 << 2 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 0 << 1 << 1 << 0 << 1;
			cf.ny << 0 << 2 << 1 << 2 << 0;
			cf.nz << 2 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 11 << 5;
			cf.py << 11 << 10 << 13 << 12 << 6;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 15 << 14 << 5 << 2 << 8;
			cf.ny << 9 << 8 << 10 << 2 << 10;
			cf.nz << 0 << 0 << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 5 << 6 << 8 << 7;
			cf.py << 12 << 12 << 12 << 23 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 17 << 5 << 2 << 8;
			cf.ny << 4 << 0 << 10 << 2 << 10;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 10 << 10 << 19 << 20;
			cf.py << 8 << 10 << 9 << 15 << 13;
			cf.pz << 1 << 1 << 1 << 0 << 0;
			cf.nx << 23 << 11 << 5 << 23 << 23;
			cf.ny << 20 << 10 << 5 << 19 << 19;
			cf.nz << 0 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 13 << 3 << 10 << 12;
			cf.py << 2 << 0 << 0 << 1 << 1;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 3 << 3 << 6 << 7 << 7;
			cf.ny << 5 << 2 << 11 << 4 << 4;
			cf.nz << 2 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 7;
			cf.py << 17 << 6;
			cf.pz << 0 << 1;
			cf.nx << 14 << 0;
			cf.ny << 16 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 15 << 18 << 12 << 19;
			cf.py << 22 << 12 << 13 << 7 << 15;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 15 << 6 << 1 << 7;
			cf.ny << 4 << 8 << 22 << 5 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 9 << 18 << 19 << 8;
			cf.py << 2 << 1 << 3 << 3 << 1;
			cf.pz << 1 << 1 << 0 << 0 << 1;
			cf.nx << 23 << 23 << 23 << 11 << 11;
			cf.ny << 0 << 1 << 2 << 0 << 1;
			cf.nz << 0 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 23 << 0 << 1 << 8;
			cf.py << 14 << 5 << 0 << 17 << 1;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 8 << 14 << 15 << 18 << 14;
			cf.ny << 10 << 11 << 14 << 19 << 10;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 6;
			cf.py << 6 << 13;
			cf.pz << 1 << 0;
			cf.nx << 4 << 12;
			cf.ny << 10 << 14;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 23 << 11 << 23 << 13;
			cf.py << 3 << 10 << 4 << 11 << 12;
			cf.pz << 2 << 0 << 1 << 0 << 0;
			cf.nx << 7 << 4 << 9 << 8 << 8;
			cf.ny << 4 << 2 << 4 << 4 << 4;
			cf.nz << 1 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 5 << 11;
			cf.py << 4 << 2 << 4;
			cf.pz << 0 << 1 << -1;
			cf.nx << 5 << 2 << 4;
			cf.ny << 0 << 1 << 2;
			cf.nz << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 2 << 2 << 5 << 8;
			cf.py << 12 << 4 << 4 << 6 << 13;
			cf.pz << 0 << 2 << 1 << 1 << 0;
			cf.nx << 3 << 9 << 4 << 4 << 8;
			cf.ny << 4 << 0 << 2 << 2 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 5 << 22;
			cf.py << 7 << 4 << 20;
			cf.pz << 1 << -1 << -1;
			cf.nx << 8 << 19 << 4;
			cf.ny << 4 << 18 << 5;
			cf.nz << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 3 << 3 << 3 << 3;
			cf.py << 10 << 16 << 15 << 14 << 13;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 1 << 0;
			cf.ny << 10 << 20 << 5 << 23 << 21;
			cf.nz << 1 << 0 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 11;
			cf.py << 4 << 18;
			cf.pz << 0 << 0;
			cf.nx << 11 << 23;
			cf.ny << 17 << 13;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 8;
			cf.py << 16 << 7;
			cf.pz << 0 << 1;
			cf.nx << 8 << 3;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 5 << 14 << 12 << 3;
			cf.py << 4 << 7 << 4 << 5 << 3;
			cf.pz << 0 << 1 << 0 << 0 << 1;
			cf.nx << 21 << 20 << 21 << 21 << 21;
			cf.ny << 2 << 0 << 4 << 3 << 3;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 20 << 20 << 20 << 10;
			cf.py << 21 << 19 << 20 << 8;
			cf.pz << 0 << 0 << 0 << 1;
			cf.nx << 8 << 11 << 0 << 2;
			cf.ny << 10 << 8 << 1 << 3;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 7 << 12 << 8;
			cf.py << 12 << 12 << 8 << 11;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 9 << 5 << 5 << 18;
			cf.ny << 9 << 2 << 0 << 20;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 5 << 9;
			cf.py << 0 << 0 << 0;
			cf.pz << 0 << 1 << 0;
			cf.nx << 2 << 6 << 3;
			cf.ny << 3 << 7 << 4;
			cf.nz << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 18 << 9 << 17 << 17;
			cf.py << 15 << 14 << 7 << 14 << 14;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 21 << 21 << 21 << 22 << 20;
			cf.ny << 15 << 21 << 17 << 14 << 23;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 12 << 12 << 7 << 4;
			cf.py << 4 << 11 << 12 << 6 << 5;
			cf.pz << 1 << 0 << 0 << 1 << 2;
			cf.nx << 16 << 11 << 9 << 6 << 20;
			cf.ny << 8 << 4 << 11 << 10 << 23;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 11 << 10 << 11 << 11;
			cf.py << 23 << 4 << 4 << 5 << 23;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 11 << 11 << 7 << 3 << 20;
			cf.ny << 21 << 21 << 11 << 1 << 23;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 1;
			cf.py << 12 << 3;
			cf.pz << 0 << -1;
			cf.nx << 10 << 10;
			cf.ny << 3 << 2;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 4 << 15 << 9 << 9;
			cf.py << 8 << 4 << 23 << 7 << 7;
			cf.pz << 1 << 2 << 0 << 1 << -1;
			cf.nx << 5 << 3 << 3 << 3 << 2;
			cf.ny << 23 << 19 << 17 << 18 << 15;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 0;
			cf.py << 16 << 3;
			cf.pz << 0 << 2;
			cf.nx << 9 << 4;
			cf.ny << 15 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 3 << 7;
			cf.pz << 2 << 1;
			cf.nx << 3 << 8;
			cf.ny << 4 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 4 << 3;
			cf.py << 18 << 0 << 14;
			cf.pz << 0 << -1 << -1;
			cf.nx << 3 << 5 << 2;
			cf.ny << 5 << 8 << 5;
			cf.nz << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 1 << 10;
			cf.py << 2 << 1 << 7;
			cf.pz << 1 << -1 << -1;
			cf.nx << 0 << 0 << 0;
			cf.ny << 3 << 5 << 1;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 5 << 2;
			cf.py << 12 << 13 << 7 << 3;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 5 << 10 << 10 << 9;
			cf.ny << 6 << 9 << 10 << 13;
			cf.nz << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 9 << 1;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 1 << 1 << 0;
			cf.py << 4 << 10 << 12 << 13 << 5;
			cf.pz << 1 << 0 << 0 << 0 << 1;
			cf.nx << 4 << 4 << 8 << 7 << 7;
			cf.ny << 3 << 2 << 10 << 4 << 4;
			cf.nz << 2 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 4 << 3;
			cf.py << 1 << 1 << 2;
			cf.pz << 1 << -1 << -1;
			cf.nx << 4 << 5 << 3;
			cf.ny << 1 << 0 << 2;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 6 << 4;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 6 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 13 << 15 << 16 << 7;
			cf.py << 1 << 1 << 2 << 2 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 4 << 4 << 4 << 3 << 7;
			cf.ny << 2 << 2 << 4 << 2 << 4;
			cf.nz << 2 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 3 << 2 << 11 << 5;
			cf.py << 23 << 7 << 4 << 10 << 6;
			cf.pz << 0 << 1 << 2 << 0 << 1;
			cf.nx << 21 << 20 << 11 << 21 << 21;
			cf.ny << 21 << 23 << 8 << 20 << 20;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 6 << 13 << 12;
			cf.py << 7 << 3 << 5 << 6;
			cf.pz << 0 << 1 << 0 << 0;
			cf.nx << 3 << 0 << 5 << 10;
			cf.ny << 4 << 6 << 5 << 1;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 4 << 0;
			cf.pz << 0 << -1;
			cf.nx << 12 << 11;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 3 << 22 << 5;
			cf.py << 6 << 1 << 18 << 5;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 0 << 0 << 0 << 3;
			cf.ny << 14 << 3 << 12 << 18;
			cf.nz << 0 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 20 << 21;
			cf.py << 10 << 18 << 15;
			cf.pz << 1 << 0 << 0;
			cf.nx << 15 << 1 << 2;
			cf.ny << 7 << 0 << 8;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 4 << 7 << 13 << 4 << 6;
			cf.pz << 1 << 1 << 0 << 2 << 1;
			cf.nx << 5 << 9 << 8 << 4 << 4;
			cf.ny << 3 << 7 << 7 << 3 << 3;
			cf.nz << 1 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 12 << 14;
			cf.py << 2 << 2 << 2;
			cf.pz << 0 << 0 << 0;
			cf.nx << 4 << 4 << 4;
			cf.ny << 2 << 2 << 5;
			cf.nz << 2 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 4 << 6 << 2 << 12;
			cf.py << 7 << 9 << 7 << 4 << 10;
			cf.pz << 0 << 1 << 0 << 2 << 0;
			cf.nx << 6 << 1 << 2 << 5 << 2;
			cf.ny << 9 << 2 << 4 << 13 << 4;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 12 << 5;
			cf.pz << 0 << -1;
			cf.nx << 1 << 0;
			cf.ny << 7 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 8 << 1 << 16 << 6;
			cf.py << 6 << 6 << 4 << 8 << 11;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 13 << 5 << 4 << 4 << 13;
			cf.ny << 12 << 1 << 2 << 5 << 11;
			cf.nz << 0 << 2 << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 4 << 14;
			cf.pz << 1 << 0;
			cf.nx << 9 << 5;
			cf.ny << 7 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 6;
			cf.py << 4 << 14;
			cf.pz << 2 << 0;
			cf.nx << 9 << 2;
			cf.ny << 15 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 19 << 20 << 10 << 9;
			cf.py << 1 << 2 << 3 << 0 << 0;
			cf.pz << 1 << 0 << 0 << 1 << -1;
			cf.nx << 11 << 23 << 23 << 11 << 23;
			cf.ny << 0 << 3 << 1 << 1 << 2;
			cf.nz << 1 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 9;
			cf.py << 3 << 12;
			cf.pz << 2 << 0;
			cf.nx << 2 << 6;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 4 << 10 << 11 << 9 << 9;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 16 << 2 << 17 << 8 << 4;
			cf.ny << 10 << 2 << 9 << 4 << 4;
			cf.nz << 0 << 2 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 0;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 4 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 21;
			cf.py << 9 << 10;
			cf.pz << 0 << 0;
			cf.nx << 11 << 8;
			cf.ny << 18 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 7;
			cf.py << 23 << 9;
			cf.pz << 0 << 1;
			cf.nx << 7 << 13;
			cf.ny << 10 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 6 << 2;
			cf.py << 11 << 13 << 12 << 6 << 4;
			cf.pz << 0 << 0 << 0 << -1 << -1;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 14 << 13 << 6 << 12 << 11;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 6 << 11;
			cf.pz << 1 << -1;
			cf.nx << 15 << 15;
			cf.ny << 11 << 10;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 6 << 7 << 2;
			cf.py << 8 << 4 << 23 << 7;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 4 << 20 << 19 << 17;
			cf.ny << 0 << 3 << 1 << 1;
			cf.nz << 2 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 6 << 0;
			cf.pz << 1 << -1;
			cf.nx << 7 << 4;
			cf.ny << 8 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 15 << 15;
			cf.ny << 15 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 2 << 5 << 2 << 4;
			cf.py << 23 << 7 << 21 << 8 << 16;
			cf.pz << 0 << 1 << 0 << 1 << 0;
			cf.nx << 18 << 2 << 10 << 0 << 11;
			cf.ny << 9 << 3 << 23 << 5 << 3;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 9 << 8 << 10 << 4;
			cf.py << 0 << 2 << 2 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 4 << 3 << 2 << 2 << 5;
			cf.ny << 7 << 3 << 4 << 2 << 17;
			cf.nz << 0 << 1 << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 7;
			cf.py << 5 << 6;
			cf.pz << 1 << -1;
			cf.nx << 11 << 11;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 5 << 6 << 11;
			cf.py << 8 << 10 << 5 << 5 << 9;
			cf.pz << 0 << 0 << 1 << 1 << 0;
			cf.nx << 13 << 16 << 11 << 14 << 4;
			cf.ny << 9 << 13 << 11 << 20 << 23;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 14;
			cf.py << 14 << 22;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 11;
			cf.py << 4 << 5;
			cf.pz << 2 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 7;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 0 << 0;
			cf.pz << 0 << 1;
			cf.nx << 0 << 4;
			cf.ny << 0 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 4 << 9;
			cf.py << 5 << 5 << 2 << 9 << 23;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 11 << 12 << 10 << 9 << 5;
			cf.ny << 2 << 2 << 2 << 2 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 14 << 15;
			cf.py << 1 << 1 << 0;
			cf.pz << 0 << 0 << 0;
			cf.nx << 4 << 7 << 4;
			cf.ny << 2 << 4 << 4;
			cf.nz << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 0;
			cf.py << 14 << 5;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 17;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 7 << 16 << 19 << 4;
			cf.py << 13 << 6 << 23 << 13 << 3;
			cf.pz << 0 << 1 << 0 << 0 << 2;
			cf.nx << 5 << 2 << 3 << 4 << 4;
			cf.ny << 1 << 1 << 4 << 1 << 3;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 7 << 6;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 4 << 4;
			cf.ny << 3 << 3;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 19 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 12;
			cf.ny << 10 << 17;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 6 << 2 << 4 << 11;
			cf.py << 14 << 4 << 2 << 1 << 5;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 3 << 4 << 3 << 4 << 3;
			cf.ny << 13 << 17 << 14 << 16 << 15;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		*a_iter++ = -1.368326;
		*a_iter++ = 1.368326;
		*a_iter++ = -0.7706897;
		*a_iter++ = 0.7706897;
		*a_iter++ = -0.8378147;
		*a_iter++ = 0.8378147;
		*a_iter++ = -0.6120624;
		*a_iter++ = 0.6120624;
		*a_iter++ = -0.5139189;
		*a_iter++ = 0.5139189;
		*a_iter++ = -0.475913;
		*a_iter++ = 0.475913;
		*a_iter++ = -0.5161374;
		*a_iter++ = 0.5161374;
		*a_iter++ = -0.5407743;
		*a_iter++ = 0.5407743;
		*a_iter++ = -0.4216105;
		*a_iter++ = 0.4216105;
		*a_iter++ = -0.4418693;
		*a_iter++ = 0.4418693;
		*a_iter++ = -0.4435335;
		*a_iter++ = 0.4435335;
		*a_iter++ = -0.4052076;
		*a_iter++ = 0.4052076;
		*a_iter++ = -0.429305;
		*a_iter++ = 0.429305;
		*a_iter++ = -0.3431154;
		*a_iter++ = 0.3431154;
		*a_iter++ = -0.4231203;
		*a_iter++ = 0.4231203;
		*a_iter++ = -0.39171;
		*a_iter++ = 0.39171;
		*a_iter++ = -0.362345;
		*a_iter++ = 0.362345;
		*a_iter++ = -0.320267;
		*a_iter++ = 0.320267;
		*a_iter++ = -0.3331602;
		*a_iter++ = 0.3331602;
		*a_iter++ = -0.3552034;
		*a_iter++ = 0.3552034;
		*a_iter++ = -0.3784556;
		*a_iter++ = 0.3784556;
		*a_iter++ = -0.3295428;
		*a_iter++ = 0.3295428;
		*a_iter++ = -0.3587038;
		*a_iter++ = 0.3587038;
		*a_iter++ = -0.2861332;
		*a_iter++ = 0.2861332;
		*a_iter++ = -0.3403258;
		*a_iter++ = 0.3403258;
		*a_iter++ = -0.3989002;
		*a_iter++ = 0.3989002;
		*a_iter++ = -0.2631159;
		*a_iter++ = 0.2631159;
		*a_iter++ = -0.3272156;
		*a_iter++ = 0.3272156;
		*a_iter++ = -0.2816567;
		*a_iter++ = 0.2816567;
		*a_iter++ = -0.3125926;
		*a_iter++ = 0.3125926;
		*a_iter++ = -0.3146982;
		*a_iter++ = 0.3146982;
		*a_iter++ = -0.2521825;
		*a_iter++ = 0.2521825;
		*a_iter++ = -0.2434554;
		*a_iter++ = 0.2434554;
		*a_iter++ = -0.3435378;
		*a_iter++ = 0.3435378;
		*a_iter++ = -0.3161172;
		*a_iter++ = 0.3161172;
		*a_iter++ = -0.2805027;
		*a_iter++ = 0.2805027;
		*a_iter++ = -0.3303579;
		*a_iter++ = 0.3303579;
		*a_iter++ = -0.2725089;
		*a_iter++ = 0.2725089;
		*a_iter++ = -0.2575051;
		*a_iter++ = 0.2575051;
		*a_iter++ = -0.3210646;
		*a_iter++ = 0.3210646;
		*a_iter++ = -0.2986997;
		*a_iter++ = 0.2986997;
		*a_iter++ = -0.2408925;
		*a_iter++ = 0.2408925;
		*a_iter++ = -0.2456291;
		*a_iter++ = 0.2456291;
		*a_iter++ = -0.283655;
		*a_iter++ = 0.283655;
		*a_iter++ = -0.246986;
		*a_iter++ = 0.246986;
		*a_iter++ = -0.29159;
		*a_iter++ = 0.29159;
		*a_iter++ = -0.2513559;
		*a_iter++ = 0.2513559;
		*a_iter++ = -0.2433728;
		*a_iter++ = 0.2433728;
		*a_iter++ = -0.2377905;
		*a_iter++ = 0.2377905;
		*a_iter++ = -0.2089327;
		*a_iter++ = 0.2089327;
		*a_iter++ = -0.1978434;
		*a_iter++ = 0.1978434;
		*a_iter++ = -0.3017699;
		*a_iter++ = 0.3017699;
		*a_iter++ = -0.2339661;
		*a_iter++ = 0.2339661;
		*a_iter++ = -0.193256;
		*a_iter++ = 0.193256;
		*a_iter++ = -0.2278285;
		*a_iter++ = 0.2278285;
		*a_iter++ = -0.24382;
		*a_iter++ = 0.24382;
		*a_iter++ = -0.2216769;
		*a_iter++ = 0.2216769;
		*a_iter++ = -0.1941995;
		*a_iter++ = 0.1941995;
		*a_iter++ = -0.2129081;
		*a_iter++ = 0.2129081;
		*a_iter++ = -0.2270319;
		*a_iter++ = 0.2270319;
		*a_iter++ = -0.2393942;
		*a_iter++ = 0.2393942;
		*a_iter++ = -0.2132518;
		*a_iter++ = 0.2132518;
		*a_iter++ = -0.1867741;
		*a_iter++ = 0.1867741;
		*a_iter++ = -0.2394237;
		*a_iter++ = 0.2394237;
		*a_iter++ = -0.2005917;
		*a_iter++ = 0.2005917;
		*a_iter++ = -0.2445217;
		*a_iter++ = 0.2445217;
		*a_iter++ = -0.2229078;
		*a_iter++ = 0.2229078;
		*a_iter++ = -0.2342967;
		*a_iter++ = 0.2342967;
		*a_iter++ = -0.2481784;
		*a_iter++ = 0.2481784;
		*a_iter++ = -0.2735603;
		*a_iter++ = 0.2735603;
		*a_iter++ = -0.2187604;
		*a_iter++ = 0.2187604;
		*a_iter++ = -0.1677239;
		*a_iter++ = 0.1677239;
		*a_iter++ = -0.2248867;
		*a_iter++ = 0.2248867;
		*a_iter++ = -0.2505358;
		*a_iter++ = 0.2505358;
		*a_iter++ = -0.1867706;
		*a_iter++ = 0.1867706;
		*a_iter++ = -0.1904305;
		*a_iter++ = 0.1904305;
		*a_iter++ = -0.1939881;
		*a_iter++ = 0.1939881;
		*a_iter++ = -0.2249474;
		*a_iter++ = 0.2249474;
		*a_iter++ = -0.1762483;
		*a_iter++ = 0.1762483;
		*a_iter++ = -0.2299974;
		*a_iter++ = 0.2299974;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 115;
		sc.threshold = -5.15192;
		sc.features.SetCount(115);
		sc.alpha.SetCount(230);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 14 << 7 << 10 << 6;
			cf.py << 3 << 3 << 12 << 4 << 4;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 14 << 3 << 14 << 9 << 3;
			cf.ny << 7 << 4 << 8 << 8 << 5;
			cf.nz << 0 << 1 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 18 << 16 << 17 << 15;
			cf.py << 1 << 13 << 1 << 2 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 23 << 23 << 8 << 11 << 22;
			cf.ny << 3 << 4 << 4 << 8 << 0;
			cf.nz << 0 << 0 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 6 << 6 << 7 << 12;
			cf.py << 12 << 13 << 4 << 12 << 5;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 0 << 0 << 8 << 4 << 0;
			cf.ny << 0 << 2 << 4 << 4 << 2;
			cf.nz << 0 << 0 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 13 << 7;
			cf.py << 13 << 18 << 6;
			cf.pz << 0 << 0 << 1;
			cf.nx << 13 << 5 << 6;
			cf.ny << 16 << 3 << 8;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 12 << 9 << 13 << 11;
			cf.py << 3 << 3 << 3 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 4 << 15 << 4 << 4;
			cf.ny << 2 << 5 << 10 << 4 << 4;
			cf.nz << 2 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 3 << 12;
			cf.py << 7 << 9 << 8 << 3 << 10;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 4 << 8 << 15 << 9 << 9;
			cf.ny << 4 << 4 << 8 << 8 << 8;
			cf.nz << 1 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 3 << 4 << 4 << 2;
			cf.py << 22 << 12 << 13 << 14 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 2 << 0 << 1 << 1 << 1;
			cf.ny << 23 << 5 << 22 << 21 << 21;
			cf.nz << 0 << 2 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 8 << 8;
			cf.pz << 1 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 11 << 0;
			cf.py << 10 << 12 << 11 << 13 << 2;
			cf.pz << 0 << 0 << 0 << -1 << -1;
			cf.nx << 8 << 13 << 13 << 13 << 13;
			cf.ny << 10 << 8 << 9 << 11 << 10;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 16 << 15 << 17 << 18;
			cf.py << 12 << 23 << 11 << 12 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 8 << 9 << 3 << 13;
			cf.ny << 4 << 4 << 12 << 3 << 10;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 16 << 6 << 5;
			cf.py << 14 << 13 << 4 << 5;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 8 << 15 << 4 << 7;
			cf.ny << 10 << 14 << 4 << 8;
			cf.nz << 1 << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 10 << 20 << 21 << 19;
			cf.py << 14 << 7 << 13 << 12 << 22;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 22 << 23 << 11 << 23 << 23;
			cf.ny << 23 << 22 << 11 << 21 << 20;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 13 << 1 << 18;
			cf.py << 14 << 23 << 3 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 2 << 10 << 5 << 9;
			cf.ny << 2 << 9 << 8 << 14;
			cf.nz << 2 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 4 << 7 << 9 << 8;
			cf.py << 1 << 0 << 2 << 0 << 1;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 2 << 3 << 5 << 3 << 3;
			cf.ny << 2 << 4 << 8 << 3 << 3;
			cf.nz << 2 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 2 << 2 << 11;
			cf.py << 6 << 4 << 5 << 7;
			cf.pz << 0 << 2 << 2 << 0;
			cf.nx << 3 << 0 << 5 << 3;
			cf.ny << 4 << 9 << 8 << 3;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 10 << 9 << 12 << 12;
			cf.py << 11 << 2 << 1 << 10 << 10;
			cf.pz << 0 << 1 << 1 << 0 << -1;
			cf.nx << 22 << 11 << 5 << 22 << 23;
			cf.ny << 1 << 1 << 0 << 0 << 3;
			cf.nz << 0 << 1 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 5 << 10 << 7 << 11;
			cf.py << 14 << 3 << 0 << 4;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 4 << 4 << 4 << 4;
			cf.ny << 17 << 18 << 15 << 16;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 3 << 2 << 2;
			cf.py << 16 << 12 << 20 << 15 << 17;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 12 << 8 << 4 << 15 << 15;
			cf.ny << 17 << 4 << 4 << 8 << 8;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 1 << 6 << 12;
			cf.py << 11 << 10 << 3 << 6 << 10;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 0 << 0 << 1 << 0 << 2;
			cf.ny << 4 << 0 << 2 << 1 << 0;
			cf.nz << 0 << 2 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 20 << 21 << 21 << 14;
			cf.py << 9 << 16 << 11 << 8 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 17 << 6 << 15 << 0 << 2;
			cf.ny << 8 << 23 << 13 << 2 << 0;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 9 << 9 << 5;
			cf.py << 14 << 18 << 23 << 14;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 9 << 5 << 5 << 12;
			cf.ny << 21 << 5 << 3 << 1;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 4 << 3;
			cf.ny << 4 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 8 << 11 << 4 << 10;
			cf.py << 3 << 3 << 2 << 1 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 19 << 20 << 19 << 20 << 20;
			cf.ny << 0 << 3 << 1 << 2 << 2;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 1;
			cf.py << 7 << 4;
			cf.pz << 1 << -1;
			cf.nx << 4 << 7;
			cf.ny << 5 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 1 << 5 << 1;
			cf.py << 10 << 12 << 6 << 6 << 5;
			cf.pz << 0 << 0 << 1 << 1 << 1;
			cf.nx << 16 << 3 << 2 << 4 << 4;
			cf.ny << 10 << 4 << 2 << 4 << 4;
			cf.nz << 0 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 0;
			cf.py << 17 << 0;
			cf.pz << 0 << -1;
			cf.nx << 7 << 4;
			cf.ny << 8 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 10 << 9 << 9 << 9;
			cf.py << 2 << 2 << 2 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 2 << 3 << 3 << 2;
			cf.ny << 0 << 3 << 2 << 1 << 4;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 15 << 17 << 16;
			cf.py << 8 << 10 << 11 << 11;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 14 << 1 << 1 << 2;
			cf.ny << 9 << 5 << 7 << 0;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 5 << 9;
			cf.py << 8 << 6 << 12;
			cf.pz << 0 << 1 << 0;
			cf.nx << 3 << 4 << 18;
			cf.ny << 4 << 2 << 22;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 1 << 7 << 3 << 3;
			cf.py << 13 << 4 << 13 << 7 << 7;
			cf.pz << 0 << 2 << 0 << 1 << -1;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 16 << 15 << 8 << 13 << 14;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 16;
			cf.py << 13 << 10;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 23 << 11 << 23 << 23;
			cf.py << 5 << 12 << 4 << 16 << 15;
			cf.pz << 2 << 0 << 1 << 0 << 0;
			cf.nx << 3 << 2 << 4 << 5 << 5;
			cf.ny << 4 << 2 << 4 << 11 << 11;
			cf.nz << 1 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 10 << 3 << 23;
			cf.py << 7 << 7 << 3 << 16;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 5 << 23 << 11 << 22;
			cf.ny << 4 << 13 << 7 << 16;
			cf.nz << 2 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 14 << 13 << 15 << 16;
			cf.py << 1 << 0 << 0 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 9 << 8 << 8 << 8;
			cf.ny << 2 << 4 << 9 << 4 << 4;
			cf.nz << 2 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 15;
			cf.ny << 1 << 8;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 6 << 9;
			cf.pz << 1 << 0;
			cf.nx << 10 << 10;
			cf.ny << 10 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 0 << 0 << 0 << 0;
			cf.py << 5 << 4 << 11 << 9 << 12;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 9 << 8 << 2 << 4 << 7;
			cf.ny << 7 << 7 << 2 << 4 << 7;
			cf.nz << 0 << 0 << 2 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 9 << 8;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 4 << 1;
			cf.pz << 2 << -1;
			cf.nx << 8 << 6;
			cf.ny << 7 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 5 << 7 << 6 << 11;
			cf.py << 12 << 5 << 13 << 13 << 22;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 23 << 23 << 23 << 22 << 22;
			cf.ny << 20 << 19 << 21 << 23 << 23;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 17;
			cf.py << 6 << 9;
			cf.pz << 1 << -1;
			cf.nx << 3 << 3;
			cf.ny << 10 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 11;
			cf.py << 23 << 5;
			cf.pz << 0 << 0;
			cf.nx << 7 << 3;
			cf.ny << 10 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 8 << 8;
			cf.pz << 1 << 1;
			cf.nx << 9 << 4;
			cf.ny << 15 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 2 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 11;
			cf.py << 21 << 10;
			cf.pz << 0 << 1;
			cf.nx << 2 << 3;
			cf.ny << 11 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 11 << 3;
			cf.py << 13 << 12 << 11 << 4;
			cf.pz << 0 << 0 << 0 << -1;
			cf.nx << 14 << 13 << 13 << 6;
			cf.ny << 13 << 11 << 10 << 5;
			cf.nz << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 9 << 19;
			cf.ny << 4 << 14;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 5 << 7;
			cf.py << 5 << 0 << 6;
			cf.pz << 1 << -1 << -1;
			cf.nx << 10 << 21 << 5;
			cf.ny << 0 << 5 << 3;
			cf.nz << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 13;
			cf.py << 3 << 15;
			cf.pz << 0 << -1;
			cf.nx << 17 << 7;
			cf.ny << 23 << 8;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 2 << 2;
			cf.py << 15 << 7 << 19;
			cf.pz << 0 << 1 << -1;
			cf.nx << 2 << 8 << 4;
			cf.ny << 5 << 14 << 9;
			cf.nz << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 3 << 6;
			cf.py << 10 << 2 << 4;
			cf.pz << 0 << 2 << 1;
			cf.nx << 3 << 8 << 4;
			cf.ny << 4 << 14 << 9;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 3;
			cf.py << 18 << 3;
			cf.pz << 0 << -1;
			cf.nx << 12 << 14;
			cf.ny << 17 << 9;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 1 << 10;
			cf.py << 14 << 10 << 10;
			cf.pz << 0 << -1 << -1;
			cf.nx << 9 << 6 << 2;
			cf.ny << 13 << 18 << 2;
			cf.nz << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 13 << 11;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 7 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 21 << 17;
			cf.pz << 0 << 0;
			cf.nx << 9 << 3;
			cf.ny << 5 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 4 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 2 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 1 << 5;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 1 << 0;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 1;
			cf.py << 13 << 5;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 1;
			cf.py << 4 << 3 << 2 << 12 << 15;
			cf.pz << 1 << 1 << 2 << 0 << 0;
			cf.nx << 5 << 9 << 4 << 8 << 8;
			cf.ny << 3 << 6 << 3 << 6 << 6;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 5;
			cf.py << 0 << 2;
			cf.pz << 1 << -1;
			cf.nx << 2 << 1;
			cf.ny << 0 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 15 << 4 << 20;
			cf.py << 8 << 23 << 4 << 8;
			cf.pz << 1 << 0 << 2 << 0;
			cf.nx << 6 << 0 << 3 << 4;
			cf.ny << 9 << 2 << 13 << 6;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 10 << 20;
			cf.py << 10 << 9 << 11 << 8;
			cf.pz << 0 << 0 << 0 << -1;
			cf.nx << 21 << 20 << 21 << 21;
			cf.ny << 18 << 23 << 19 << 17;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 8;
			cf.py << 7 << 5;
			cf.pz << 1 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 11;
			cf.py << 3 << 4;
			cf.pz << 2 << 1;
			cf.nx << 8 << 7;
			cf.ny << 5 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 1 << 3;
			cf.pz << 1 << -1;
			cf.nx << 3 << 6;
			cf.ny << 0 << 0;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 9;
			cf.py << 16 << 8;
			cf.pz << 0 << 1;
			cf.nx << 14 << 6;
			cf.ny << 15 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 13 << 5;
			cf.pz << 0 << -1;
			cf.nx << 5 << 5;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 14 << 4 << 15 << 12;
			cf.py << 1 << 1 << 1 << 2 << 1;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 6 << 4 << 3 << 2 << 10;
			cf.ny << 22 << 8 << 2 << 1 << 7;
			cf.nz << 0 << 1 << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 8 << 6 << 5 << 5;
			cf.py << 1 << 0 << 0 << 1 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 4 << 4 << 4 << 8;
			cf.ny << 4 << 3 << 2 << 5 << 10;
			cf.nz << 2 << 2 << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 8;
			cf.py << 17 << 0;
			cf.pz << 0 << -1;
			cf.nx << 2 << 5;
			cf.ny << 5 << 8;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 0;
			cf.py << 7 << 3;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 21;
			cf.py << 11 << 20;
			cf.pz << 1 << 0;
			cf.nx << 11 << 4;
			cf.ny << 17 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 10 << 4 << 17 << 10;
			cf.py << 3 << 6 << 3 << 11 << 5;
			cf.pz << 1 << 0 << 1 << 0 << 0;
			cf.nx << 21 << 20 << 9 << 19 << 10;
			cf.ny << 4 << 3 << 0 << 2 << 1;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 23;
			cf.py << 10 << 10;
			cf.pz << 0 << -1;
			cf.nx << 23 << 23;
			cf.ny << 21 << 22;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 20 << 19 << 20 << 20;
			cf.py << 0 << 3 << 1 << 2 << 2;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 11 << 23 << 11 << 23 << 5;
			cf.ny << 1 << 2 << 0 << 1 << 0;
			cf.nz << 1 << 0 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 8 << 7;
			cf.py << 4 << 10 << 11;
			cf.pz << 1 << 0 << 0;
			cf.nx << 8 << 3 << 4;
			cf.ny << 9 << 4 << 4;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 13 << 10 << 4;
			cf.py << 14 << 23 << 1 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 15 << 14 << 8 << 8;
			cf.ny << 13 << 12 << 8 << 9;
			cf.nz << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 9;
			cf.py << 5 << 8;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 7 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 8 << 4 << 7 << 7;
			cf.py << 2 << 3 << 3 << 11 << 11;
			cf.pz << 2 << 1 << 2 << 1 << -1;
			cf.nx << 0 << 0 << 1 << 0 << 0;
			cf.ny << 4 << 6 << 15 << 3 << 2;
			cf.nz << 1 << 1 << 0 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 1;
			cf.py << 12 << 1;
			cf.pz << 0 << -1;
			cf.nx << 1 << 10;
			cf.ny << 2 << 11;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 2 << 3 << 7;
			cf.py << 0 << 1 << 4 << 3 << 11;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 9 << 11 << 9 << 6 << 12;
			cf.ny << 2 << 1 << 1 << 0 << 2;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 11;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 1 << 1 << 1;
			cf.py << 15 << 10 << 19 << 16 << 18;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 4 << 5 << 3 << 5 << 6;
			cf.ny << 4 << 19 << 9 << 18 << 19;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 20;
			cf.py << 11 << 12 << 13 << 13 << 18;
			cf.pz << 0 << 0 << 0 << -1 << -1;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 4 << 2 << 7 << 6 << 12;
			cf.nz << 1 << 2 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 9 << 11;
			cf.pz << 0 << 0;
			cf.nx << 10 << 4;
			cf.ny << 5 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 9 << 6;
			cf.pz << 0 << 1;
			cf.nx << 13 << 13;
			cf.ny << 10 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 5 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 3;
			cf.ny << 5 << 5;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 9;
			cf.py << 10 << 6;
			cf.pz << 0 << 1;
			cf.nx << 4 << 1;
			cf.ny << 2 << 2;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 4;
			cf.py << 19 << 12;
			cf.pz << 0 << -1;
			cf.nx << 14 << 8;
			cf.ny << 17 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 2 << 13 << 2;
			cf.py << 12 << 6 << 9 << 3;
			cf.pz << 0 << 1 << -1 << -1;
			cf.nx << 1 << 0 << 1 << 0;
			cf.ny << 16 << 14 << 11 << 15;
			cf.nz << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 4 << 4;
			cf.ny << 4 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 11 << 12 << 6 << 10;
			cf.py << 2 << 1 << 2 << 1 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 4 << 6 << 4 << 6 << 2;
			cf.ny << 4 << 0 << 9 << 1 << 8;
			cf.nz << 0 << 0 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 4 << 7 << 2 << 2;
			cf.py << 19 << 20 << 23 << 8 << 9;
			cf.pz << 0 << 0 << 0 << 1 << 1;
			cf.nx << 7 << 0 << 5 << 6 << 2;
			cf.ny << 10 << 5 << 4 << 1 << 8;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 18 << 17 << 18 << 18;
			cf.py << 15 << 16 << 14 << 20 << 17;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 15 << 2 << 2 << 5 << 2;
			cf.ny << 8 << 0 << 2 << 9 << 4;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 13 << 13 << 18;
			cf.py << 11 << 12 << 12 << 20;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 1 << 3 << 10 << 10;
			cf.ny << 1 << 6 << 12 << 11;
			cf.nz << 2 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 0 << 1;
			cf.pz << 1 << 1;
			cf.nx << 19 << 4;
			cf.ny << 2 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 4 << 2;
			cf.pz << 1 << 2;
			cf.nx << 8 << 4;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 11 << 22 << 13 << 13;
			cf.py << 8 << 3 << 3 << 12 << 12;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 15 << 7 << 14 << 13 << 8;
			cf.ny << 7 << 3 << 6 << 6 << 3;
			cf.nz << 0 << 1 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 11 << 19;
			cf.py << 7 << 3 << 0;
			cf.pz << 1 << -1 << -1;
			cf.nx << 23 << 23 << 11;
			cf.ny << 16 << 12 << 7;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 8;
			cf.py << 23 << 7;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 5 << 4;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 10;
			cf.py << 6 << 13;
			cf.pz << 1 << -1;
			cf.nx << 2 << 3;
			cf.ny << 4 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 11 << 2;
			cf.pz << 1 << 2;
			cf.nx << 9 << 2;
			cf.ny << 5 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 22;
			cf.py << 22 << 21;
			cf.pz << 0 << 0;
			cf.nx << 3 << 0;
			cf.ny << 5 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 10;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 20 << 10;
			cf.ny << 23 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 3 << 3 << 4;
			cf.py << 5 << 3 << 4 << 9;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 14 << 4 << 3 << 11;
			cf.ny << 2 << 1 << 1 << 3;
			cf.nz << 0 << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 15 << 15 << 3;
			cf.py << 1 << 1 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 7 << 4 << 4;
			cf.ny << 8 << 2 << 3;
			cf.nz << 1 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 0 << 0;
			cf.py << 3 << 4 << 6;
			cf.pz << 2 << 2 << 1;
			cf.nx << 0 << 21 << 4;
			cf.ny << 23 << 14 << 3;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 4 << 5 << 3 << 4;
			cf.py << 9 << 11 << 8 << 4 << 8;
			cf.pz << 1 << 1 << 1 << 2 << 1;
			cf.nx << 21 << 21 << 10 << 19 << 19;
			cf.ny << 3 << 4 << 1 << 0 << 0;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 21 << 20 << 20 << 21;
			cf.py << 18 << 21 << 20 << 17;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 8 << 1 << 4 << 2;
			cf.ny << 10 << 0 << 2 << 4;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 14;
			cf.pz << 1 << 0;
			cf.nx << 3 << 5;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 0 << 23;
			cf.py << 20 << 2 << 13;
			cf.pz << 0 << -1 << -1;
			cf.nx << 12 << 2 << 9;
			cf.ny << 19 << 2 << 7;
			cf.nz << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 6;
			cf.py << 22 << 11;
			cf.pz << 0 << -1;
			cf.nx << 20 << 18;
			cf.ny << 12 << 23;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 15 << 15 << 16 << 8;
			cf.py << 2 << 1 << 2 << 2 << 1;
			cf.pz << 1 << 0 << 0 << 0 << 1;
			cf.nx << 1 << 1 << 1 << 1 << 1;
			cf.ny << 16 << 10 << 17 << 18 << 18;
			cf.nz << 0 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 5 << 3 << 5 << 8;
			cf.py << 14 << 2 << 1 << 4 << 1;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 23 << 23 << 23 << 23 << 23;
			cf.ny << 18 << 15 << 16 << 14 << 17;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 2 << 3 << 2;
			cf.py << 16 << 17 << 15 << 20 << 11;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 22 << 2 << 1 << 23;
			cf.ny << 20 << 11 << 5 << 0 << 17;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		*a_iter++ = -1.299972;
		*a_iter++ = 1.299972;
		*a_iter++ = -0.7630804;
		*a_iter++ = 0.7630804;
		*a_iter++ = -0.5530378;
		*a_iter++ = 0.5530378;
		*a_iter++ = -0.5444703;
		*a_iter++ = 0.5444703;
		*a_iter++ = -0.5207701;
		*a_iter++ = 0.5207701;
		*a_iter++ = -0.5035143;
		*a_iter++ = 0.5035143;
		*a_iter++ = -0.4514416;
		*a_iter++ = 0.4514416;
		*a_iter++ = -0.4897723;
		*a_iter++ = 0.4897723;
		*a_iter++ = -0.5006264;
		*a_iter++ = 0.5006264;
		*a_iter++ = -0.4626049;
		*a_iter++ = 0.4626049;
		*a_iter++ = -0.4375402;
		*a_iter++ = 0.4375402;
		*a_iter++ = -0.3742565;
		*a_iter++ = 0.3742565;
		*a_iter++ = -0.3873996;
		*a_iter++ = 0.3873996;
		*a_iter++ = -0.3715484;
		*a_iter++ = 0.3715484;
		*a_iter++ = -0.356248;
		*a_iter++ = 0.356248;
		*a_iter++ = -0.3216189;
		*a_iter++ = 0.3216189;
		*a_iter++ = -0.3983409;
		*a_iter++ = 0.3983409;
		*a_iter++ = -0.3191891;
		*a_iter++ = 0.3191891;
		*a_iter++ = -0.3242173;
		*a_iter++ = 0.3242173;
		*a_iter++ = -0.352804;
		*a_iter++ = 0.352804;
		*a_iter++ = -0.3562318;
		*a_iter++ = 0.3562318;
		*a_iter++ = -0.3592398;
		*a_iter++ = 0.3592398;
		*a_iter++ = -0.2557584;
		*a_iter++ = 0.2557584;
		*a_iter++ = -0.2747951;
		*a_iter++ = 0.2747951;
		*a_iter++ = -0.2747554;
		*a_iter++ = 0.2747554;
		*a_iter++ = -0.2980481;
		*a_iter++ = 0.2980481;
		*a_iter++ = -0.288767;
		*a_iter++ = 0.288767;
		*a_iter++ = -0.3895318;
		*a_iter++ = 0.3895318;
		*a_iter++ = -0.2786896;
		*a_iter++ = 0.2786896;
		*a_iter++ = -0.2763841;
		*a_iter++ = 0.2763841;
		*a_iter++ = -0.2704816;
		*a_iter++ = 0.2704816;
		*a_iter++ = -0.2075489;
		*a_iter++ = 0.2075489;
		*a_iter++ = -0.3104773;
		*a_iter++ = 0.3104773;
		*a_iter++ = -0.2580337;
		*a_iter++ = 0.2580337;
		*a_iter++ = -0.2448334;
		*a_iter++ = 0.2448334;
		*a_iter++ = -0.3054279;
		*a_iter++ = 0.3054279;
		*a_iter++ = -0.2335804;
		*a_iter++ = 0.2335804;
		*a_iter++ = -0.2972322;
		*a_iter++ = 0.2972322;
		*a_iter++ = -0.2270521;
		*a_iter++ = 0.2270521;
		*a_iter++ = -0.2134621;
		*a_iter++ = 0.2134621;
		*a_iter++ = -0.2261655;
		*a_iter++ = 0.2261655;
		*a_iter++ = -0.2091024;
		*a_iter++ = 0.2091024;
		*a_iter++ = -0.2478928;
		*a_iter++ = 0.2478928;
		*a_iter++ = -0.2468972;
		*a_iter++ = 0.2468972;
		*a_iter++ = -0.1919746;
		*a_iter++ = 0.1919746;
		*a_iter++ = -0.2756623;
		*a_iter++ = 0.2756623;
		*a_iter++ = -0.2629717;
		*a_iter++ = 0.2629717;
		*a_iter++ = -0.2198653;
		*a_iter++ = 0.2198653;
		*a_iter++ = -0.2174434;
		*a_iter++ = 0.2174434;
		*a_iter++ = -0.2193626;
		*a_iter++ = 0.2193626;
		*a_iter++ = -0.1956262;
		*a_iter++ = 0.1956262;
		*a_iter++ = -0.1720459;
		*a_iter++ = 0.1720459;
		*a_iter++ = -0.1781067;
		*a_iter++ = 0.1781067;
		*a_iter++ = -0.1773484;
		*a_iter++ = 0.1773484;
		*a_iter++ = -0.1793871;
		*a_iter++ = 0.1793871;
		*a_iter++ = -0.1973396;
		*a_iter++ = 0.1973396;
		*a_iter++ = -0.2397262;
		*a_iter++ = 0.2397262;
		*a_iter++ = -0.2164685;
		*a_iter++ = 0.2164685;
		*a_iter++ = -0.2214348;
		*a_iter++ = 0.2214348;
		*a_iter++ = -0.2265941;
		*a_iter++ = 0.2265941;
		*a_iter++ = -0.2075436;
		*a_iter++ = 0.2075436;
		*a_iter++ = -0.224407;
		*a_iter++ = 0.224407;
		*a_iter++ = -0.2291992;
		*a_iter++ = 0.2291992;
		*a_iter++ = -0.2223506;
		*a_iter++ = 0.2223506;
		*a_iter++ = -0.1639398;
		*a_iter++ = 0.1639398;
		*a_iter++ = -0.1732374;
		*a_iter++ = 0.1732374;
		*a_iter++ = -0.1808631;
		*a_iter++ = 0.1808631;
		*a_iter++ = -0.1860962;
		*a_iter++ = 0.1860962;
		*a_iter++ = -0.1781604;
		*a_iter++ = 0.1781604;
		*a_iter++ = -0.2108322;
		*a_iter++ = 0.2108322;
		*a_iter++ = -0.238639;
		*a_iter++ = 0.238639;
		*a_iter++ = -0.1942083;
		*a_iter++ = 0.1942083;
		*a_iter++ = -0.1949161;
		*a_iter++ = 0.1949161;
		*a_iter++ = -0.1953729;
		*a_iter++ = 0.1953729;
		*a_iter++ = -0.2317591;
		*a_iter++ = 0.2317591;
		*a_iter++ = -0.2335136;
		*a_iter++ = 0.2335136;
		*a_iter++ = -0.2282835;
		*a_iter++ = 0.2282835;
		*a_iter++ = -0.2148716;
		*a_iter++ = 0.2148716;
		*a_iter++ = -0.1588127;
		*a_iter++ = 0.1588127;
		*a_iter++ = -0.1566765;
		*a_iter++ = 0.1566765;
		*a_iter++ = -0.1644839;
		*a_iter++ = 0.1644839;
		*a_iter++ = -0.2386947;
		*a_iter++ = 0.2386947;
		*a_iter++ = -0.1704126;
		*a_iter++ = 0.1704126;
		*a_iter++ = -0.2213945;
		*a_iter++ = 0.2213945;
		*a_iter++ = -0.1740398;
		*a_iter++ = 0.1740398;
		*a_iter++ = -0.2451678;
		*a_iter++ = 0.2451678;
		*a_iter++ = -0.2120524;
		*a_iter++ = 0.2120524;
		*a_iter++ = -0.1886646;
		*a_iter++ = 0.1886646;
		*a_iter++ = -0.2824447;
		*a_iter++ = 0.2824447;
		*a_iter++ = -0.1900364;
		*a_iter++ = 0.1900364;
		*a_iter++ = -0.2179183;
		*a_iter++ = 0.2179183;
		*a_iter++ = -0.2257696;
		*a_iter++ = 0.2257696;
		*a_iter++ = -0.2023404;
		*a_iter++ = 0.2023404;
		*a_iter++ = -0.1886901;
		*a_iter++ = 0.1886901;
		*a_iter++ = -0.1850663;
		*a_iter++ = 0.1850663;
		*a_iter++ = -0.2035414;
		*a_iter++ = 0.2035414;
		*a_iter++ = -0.1930174;
		*a_iter++ = 0.1930174;
		*a_iter++ = -0.1898282;
		*a_iter++ = 0.1898282;
		*a_iter++ = -0.166664;
		*a_iter++ = 0.166664;
		*a_iter++ = -0.1646143;
		*a_iter++ = 0.1646143;
		*a_iter++ = -0.1543475;
		*a_iter++ = 0.1543475;
		*a_iter++ = -0.1366289;
		*a_iter++ = 0.1366289;
		*a_iter++ = -0.1636837;
		*a_iter++ = 0.1636837;
		*a_iter++ = -0.2547716;
		*a_iter++ = 0.2547716;
		*a_iter++ = -0.1281869;
		*a_iter++ = 0.1281869;
		*a_iter++ = -0.1509159;
		*a_iter++ = 0.1509159;
		*a_iter++ = -0.1447827;
		*a_iter++ = 0.1447827;
		*a_iter++ = -0.1626126;
		*a_iter++ = 0.1626126;
		*a_iter++ = -0.2387014;
		*a_iter++ = 0.2387014;
		*a_iter++ = -0.257116;
		*a_iter++ = 0.257116;
		*a_iter++ = -0.1719175;
		*a_iter++ = 0.1719175;
		*a_iter++ = -0.1646742;
		*a_iter++ = 0.1646742;
		*a_iter++ = -0.1717041;
		*a_iter++ = 0.1717041;
		*a_iter++ = -0.2039217;
		*a_iter++ = 0.2039217;
		*a_iter++ = -0.1796907;
		*a_iter++ = 0.1796907;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 153;
		sc.threshold = -4.971032;
		sc.features.SetCount(153);
		sc.alpha.SetCount(306);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 13 << 18 << 10 << 16;
			cf.py << 2 << 2 << 13 << 3 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 21 << 7 << 14 << 23 << 23;
			cf.ny << 16 << 7 << 8 << 3 << 13;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 15 << 14;
			cf.py << 9 << 10 << 11 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 9 << 9 << 8 << 14 << 3;
			cf.ny << 9 << 8 << 5 << 9 << 5;
			cf.nz << 0 << 0 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 11 << 7 << 6 << 8;
			cf.py << 12 << 8 << 12 << 12 << 11;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 3 << 9 << 9;
			cf.ny << 4 << 4 << 4 << 9 << 9;
			cf.nz << 1 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 8 << 4 << 10 << 6;
			cf.py << 2 << 2 << 1 << 3 << 13;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 1 << 1 << 5 << 1 << 1;
			cf.ny << 2 << 3 << 8 << 4 << 16;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 16 << 6 << 17 << 15;
			cf.py << 2 << 17 << 4 << 12 << 12;
			cf.pz << 2 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 8 << 15 << 1 << 1;
			cf.ny << 4 << 4 << 8 << 16 << 16;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 18 << 15 << 8 << 17;
			cf.py << 12 << 23 << 6 << 12;
			cf.pz << 0 << 0 << 1 << 0;
			cf.nx << 15 << 4 << 10 << 5;
			cf.ny << 21 << 8 << 14 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 17 << 9 << 19 << 19;
			cf.py << 3 << 1 << 0 << 3 << 3;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 22 << 11 << 23 << 23 << 23;
			cf.ny << 0 << 1 << 2 << 3 << 4;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 5 << 5 << 10;
			cf.py << 18 << 15 << 14 << 18;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 10 << 11 << 2 << 0;
			cf.ny << 16 << 7 << 12 << 7;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 12;
			cf.py << 4 << 6;
			cf.pz << 2 << 0;
			cf.nx << 3 << 12;
			cf.ny << 4 << 19;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 4 << 5 << 2 << 2;
			cf.py << 3 << 3 << 3 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 0 << 0 << 1 << 0 << 0;
			cf.ny << 3 << 4 << 0 << 1 << 2;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 8 << 10;
			cf.py << 13 << 12 << 12 << 1 << 18;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 13 << 8 << 7 << 14 << 9;
			cf.ny << 10 << 10 << 7 << 13 << 4;
			cf.nz << 0 << 1 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 4 << 12 << 14 << 12;
			cf.py << 12 << 3 << 9 << 10 << 8;
			cf.pz << 0 << 2 << 0 << 0 << 0;
			cf.nx << 14 << 7 << 11 << 2 << 9;
			cf.ny << 8 << 4 << 7 << 5 << 4;
			cf.nz << 0 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 9 << 7;
			cf.py << 7 << 23 << 15;
			cf.pz << 1 << -1 << -1;
			cf.nx << 4 << 4 << 2;
			cf.ny << 9 << 7 << 5;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 17 << 5;
			cf.py << 3 << 23 << 4;
			cf.pz << 2 << 0 << 2;
			cf.nx << 23 << 2 << 4;
			cf.ny << 23 << 16 << 4;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 9 << 9 << 10 << 8;
			cf.py << 1 << 0 << 1 << 0 << 2;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 2 << 5 << 4 << 2 << 2;
			cf.ny << 2 << 19 << 11 << 4 << 1;
			cf.nz << 2 << 0 << 1 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 3 << 8 << 4 << 7;
			cf.py << 23 << 9 << 13 << 8 << 16;
			cf.pz << 0 << 1 << 0 << 1 << 0;
			cf.nx << 8 << 2 << 5 << 3 << 2;
			cf.ny << 8 << 15 << 1 << 1 << 1;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 14 << 5;
			cf.pz << 0 << -1;
			cf.nx << 1 << 9;
			cf.ny << 3 << 13;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 8 << 1 << 8 << 6;
			cf.py << 12 << 12 << 3 << 23 << 12;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 1 << 1 << 2 << 1 << 1;
			cf.ny << 22 << 21 << 23 << 20 << 20;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 21 << 19 << 21 << 20;
			cf.py << 13 << 8 << 20 << 10 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 16 << 0 << 14 << 23 << 1;
			cf.ny << 8 << 1 << 23 << 10 << 20;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 16 << 13 << 14 << 14;
			cf.py << 3 << 3 << 3 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 18 << 19 << 18 << 9 << 17;
			cf.ny << 2 << 2 << 1 << 1 << 0;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 9;
			cf.py << 14 << 4;
			cf.pz << 0 << -1;
			cf.nx << 9 << 18;
			cf.ny << 4 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 20;
			cf.py << 17 << 21;
			cf.pz << 0 << 0;
			cf.nx << 12 << 3;
			cf.ny << 17 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 4 << 1;
			cf.ny << 10 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 8 << 4 << 9 << 9;
			cf.py << 2 << 2 << 0 << 2 << 2;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 5 << 5 << 4 << 6 << 3;
			cf.ny << 0 << 1 << 2 << 0 << 0;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 5;
			cf.py << 3 << 5;
			cf.pz << 2 << -1;
			cf.nx << 3 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 0 << 1 << 3 << 4 << 4;
			cf.pz << 2 << 2 << 1 << 1 << -1;
			cf.nx << 20 << 20 << 19 << 20 << 19;
			cf.ny << 21 << 20 << 23 << 19 << 22;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 18;
			cf.py << 8 << 16;
			cf.pz << 1 << 0;
			cf.nx << 14 << 6;
			cf.ny << 15 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 4 << 7;
			cf.py << 3 << 3 << 9;
			cf.pz << 2 << 2 << 1;
			cf.nx << 8 << 9 << 7;
			cf.ny << 4 << 11 << 4;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 14 << 4 << 7 << 7;
			cf.py << 4 << 23 << 3 << 6 << 6;
			cf.pz << 1 << 0 << 2 << 1 << -1;
			cf.nx << 2 << 0 << 2 << 1 << 3;
			cf.ny << 20 << 4 << 21 << 10 << 23;
			cf.nz << 0 << 2 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 4 << 8 << 9 << 10;
			cf.py << 3 << 8 << 13 << 23 << 23;
			cf.pz << 2 << 1 << 0 << 0 << 0;
			cf.nx << 10 << 4 << 0 << 3 << 3;
			cf.ny << 21 << 3 << 0 << 3 << 23;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 10 << 11;
			cf.py << 6 << 5 << 5;
			cf.pz << 0 << 0 << 0;
			cf.nx << 14 << 6 << 1;
			cf.ny << 7 << 9 << 5;
			cf.nz << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 11 << 6;
			cf.py << 11 << 12 << 10 << 13 << 6;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 9 << 13 << 13 << 13 << 4;
			cf.ny << 4 << 9 << 10 << 11 << 2;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 11;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 2;
			cf.py << 4 << 11;
			cf.pz << 2 << 0;
			cf.nx << 8 << 8;
			cf.ny << 15 << 15;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 13 << 12 << 12;
			cf.py << 10 << 11 << 13 << 12 << 12;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 0 << 0 << 0 << 1 << 0;
			cf.ny << 13 << 2 << 12 << 5 << 14;
			cf.nz << 0 << 2 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 1 << 1;
			cf.py << 4 << 3 << 11 << 15 << 13;
			cf.pz << 1 << 2 << 0 << 0 << 0;
			cf.nx << 2 << 3 << 3 << 1 << 0;
			cf.ny << 2 << 4 << 4 << 5 << 14;
			cf.nz << 2 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 11;
			cf.py << 12 << 10;
			cf.pz << 0 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 8 << 9 << 9 << 9;
			cf.py << 15 << 7 << 8 << 10 << 7;
			cf.pz << 0 << 1 << 1 << 1 << 1;
			cf.nx << 22 << 23 << 21 << 22 << 11;
			cf.ny << 20 << 16 << 23 << 19 << 9;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 12 << 13 << 14 << 15;
			cf.py << 1 << 0 << 0 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 9 << 4 << 7 << 7;
			cf.ny << 2 << 3 << 1 << 8 << 8;
			cf.nz << 2 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 9;
			cf.py << 14 << 19;
			cf.pz << 0 << -1;
			cf.nx << 6 << 10;
			cf.ny << 0 << 2;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 12;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 3 << 3;
			cf.ny << 1 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 5 << 5;
			cf.py << 18 << 3 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 8 << 7 << 8;
			cf.ny << 4 << 8 << 10;
			cf.nz << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 18;
			cf.py << 6 << 11;
			cf.pz << 1 << 0;
			cf.nx << 9 << 1;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 11;
			cf.py << 9 << 7;
			cf.pz << 0 << 0;
			cf.nx << 7 << 7;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 11 << 23 << 11 << 23;
			cf.py << 13 << 4 << 12 << 7 << 10;
			cf.pz << 0 << 1 << 0 << 1 << 0;
			cf.nx << 7 << 4 << 8 << 15 << 15;
			cf.ny << 9 << 2 << 4 << 8 << 8;
			cf.nz << 0 << 2 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 1 << 0;
			cf.pz << 0 << 1;
			cf.nx << 4 << 1;
			cf.ny << 1 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 7 << 6;
			cf.pz << 0 << 1;
			cf.nx << 6 << 4;
			cf.ny << 9 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 5 << 6 << 5 << 5;
			cf.py << 8 << 6 << 11 << 6;
			cf.pz << 1 << 1 << 1 << 0;
			cf.nx << 23 << 0 << 4 << 5;
			cf.ny << 0 << 2 << 2 << 1;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 4;
			cf.py << 13 << 3;
			cf.pz << 0 << -1;
			cf.nx << 15 << 4;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 0;
			cf.py << 8 << 0;
			cf.pz << 1 << -1;
			cf.nx << 9 << 2;
			cf.ny << 15 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 15 << 16 << 14 << 14;
			cf.py << 0 << 1 << 1 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 4 << 8 << 8 << 15;
			cf.ny << 4 << 5 << 4 << 11 << 23;
			cf.nz << 2 << 2 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 11 << 3 << 14;
			cf.py << 14 << 22 << 1 << 0;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 8 << 15 << 7 << 16;
			cf.ny << 2 << 3 << 1 << 3;
			cf.nz << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 12;
			cf.py << 6 << 17;
			cf.pz << 1 << -1;
			cf.nx << 2 << 1;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 12 << 12 << 7 << 7;
			cf.py << 5 << 6 << 5 << 14 << 14;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 10 << 3 << 10 << 1 << 10;
			cf.ny << 13 << 8 << 11 << 3 << 10;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 15 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 16 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 4 << 2 << 1 << 2;
			cf.py << 4 << 0 << 1 << 1 << 0;
			cf.pz << 1 << 1 << 1 << 2 << 1;
			cf.nx << 4 << 9 << 1 << 5 << 1;
			cf.ny << 3 << 4 << 4 << 5 << 5;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 3 << 1;
			cf.pz << 0 << 2;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 0;
			cf.py << 21 << 0;
			cf.pz << 0 << -1;
			cf.nx << 6 << 8;
			cf.ny << 8 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 11;
			cf.py << 4 << 18;
			cf.pz << 0 << -1;
			cf.nx << 5 << 7;
			cf.ny << 0 << 2;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 7;
			cf.py << 0 << 3;
			cf.pz << 1 << -1;
			cf.nx << 20 << 10;
			cf.ny << 0 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 4 << 1 << 5;
			cf.py << 0 << 6 << 8 << 4;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 6 << 15 << 4 << 14;
			cf.ny << 3 << 5 << 1 << 5;
			cf.nz << 1 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 9 << 2;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 3 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 6;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 0;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 0 << 7;
			cf.ny << 7 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 7 << 3;
			cf.pz << 1 << -1;
			cf.nx << 15 << 4;
			cf.ny << 14 << 4;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 1 << 2 << 2;
			cf.py << 20 << 7 << 18 << 17;
			cf.pz << 0 << 1 << 0 << 0;
			cf.nx << 9 << 5 << 5 << 4;
			cf.ny << 5 << 4 << 18 << 4;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 3 << 1;
			cf.pz << 2 << -1;
			cf.nx << 23 << 23;
			cf.ny << 14 << 13;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 4;
			cf.py << 6 << 1;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 22 << 22 << 11 << 11 << 11;
			cf.py << 12 << 13 << 4 << 6 << 6;
			cf.pz << 0 << 0 << 1 << 1 << -1;
			cf.nx << 4 << 4 << 4 << 4 << 3;
			cf.ny << 16 << 15 << 18 << 14 << 11;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 10;
			cf.py << 0 << 1;
			cf.pz << 1 << 0;
			cf.nx << 2 << 2;
			cf.ny << 2 << 2;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 6;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 15 << 4;
			cf.ny << 2 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 2;
			cf.py << 10 << 20;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 19;
			cf.py << 3 << 8;
			cf.pz << 2 << 0;
			cf.nx << 8 << 21;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 6 << 7 << 6 << 2;
			cf.py << 6 << 15 << 13 << 14 << 3;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 21 << 22 << 19 << 21 << 10;
			cf.ny << 6 << 12 << 0 << 3 << 2;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 12 << 15 << 14 << 13;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 3 << 1 << 3 << 4;
			cf.ny << 19 << 16 << 3 << 15 << 4;
			cf.nz << 0 << 0 << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 2 << 3;
			cf.pz << 2 << 2;
			cf.nx << 8 << 4;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 0 << 0 << 0 << 5;
			cf.py << 10 << 9 << 11 << 21;
			cf.pz << 1 << 1 << -1 << -1;
			cf.nx << 12 << 4 << 3 << 11;
			cf.ny << 3 << 1 << 1 << 3;
			cf.nz << 0 << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 1;
			cf.py << 0 << 0;
			cf.pz << 1 << 2;
			cf.nx << 1 << 4;
			cf.ny << 2 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 5 << 1 << 0 << 1;
			cf.py << 14 << 23 << 7 << 5 << 9;
			cf.pz << 0 << 0 << 1 << 1 << 1;
			cf.nx << 0 << 0 << 7 << 9 << 11;
			cf.ny << 23 << 22 << 4 << 9 << 3;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 8 << 8;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 9;
			cf.py << 11 << 3;
			cf.pz << 1 << -1;
			cf.nx << 3 << 2;
			cf.ny << 14 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 4 << 5 << 4;
			cf.py << 8 << 20 << 22 << 16;
			cf.pz << 1 << 0 << 0 << 0;
			cf.nx << 8 << 2 << 11 << 3;
			cf.ny << 7 << 4 << 15 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 2 << 3;
			cf.py << 2 << 1 << 0;
			cf.pz << 0 << 0 << 0;
			cf.nx << 0 << 0 << 15;
			cf.ny << 1 << 0 << 11;
			cf.nz << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 22;
			cf.py << 6 << 7;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 0 << 5;
			cf.py << 19 << 10 << 2;
			cf.pz << 0 << -1 << -1;
			cf.nx << 3 << 4 << 6;
			cf.ny << 5 << 5 << 9;
			cf.nz << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 15;
			cf.py << 8 << 22;
			cf.pz << 1 << 0;
			cf.nx << 7 << 4;
			cf.ny << 10 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 7 << 6;
			cf.pz << 1 << 1;
			cf.nx << 10 << 1;
			cf.ny << 9 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 11;
			cf.py << 4 << 3;
			cf.pz << 0 << -1;
			cf.nx << 5 << 9;
			cf.ny << 0 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 13 << 14 << 12 << 15;
			cf.py << 1 << 2 << 2 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 8 << 4 << 7 << 4;
			cf.ny << 2 << 4 << 3 << 4 << 4;
			cf.nz << 2 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 8 << 2;
			cf.py << 14 << 5 << 8;
			cf.pz << 0 << -1 << -1;
			cf.nx << 6 << 8 << 9;
			cf.ny << 3 << 2 << 2;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 6 << 8;
			cf.py << 7 << 4 << 12;
			cf.pz << 1 << 1 << 0;
			cf.nx << 3 << 8 << 9;
			cf.ny << 5 << 2 << 2;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 16 << 3;
			cf.pz << 0 << 2;
			cf.nx << 13 << 7;
			cf.ny << 15 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 0;
			cf.py << 7 << 9;
			cf.pz << 1 << -1;
			cf.nx << 2 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 6 << 8 << 7 << 7;
			cf.py << 0 << 1 << 0 << 0 << 0;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 7 << 9 << 4 << 3 << 4;
			cf.ny << 9 << 7 << 4 << 2 << 2;
			cf.nz << 1 << 1 << 1 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 4 << 16;
			cf.py << 4 << 4 << 6;
			cf.pz << 1 << 2 << 0;
			cf.nx << 2 << 2 << 2;
			cf.ny << 0 << 0 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 5 << 5;
			cf.ny << 2 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 7 << 20;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 21;
			cf.py << 10 << 18;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 10 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 13;
			cf.py << 6 << 23;
			cf.pz << 1 << -1;
			cf.nx << 10 << 10;
			cf.ny << 11 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 9 << 5 << 10 << 10;
			cf.py << 9 << 13 << 6 << 10 << 10;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 21 << 21 << 21 << 10 << 21;
			cf.ny << 18 << 20 << 19 << 11 << 17;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 7 << 6;
			cf.pz << 1 << 1;
			cf.nx << 8 << 1;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 14 << 7;
			cf.pz << 0 << -1;
			cf.nx << 13 << 13;
			cf.ny << 13 << 11;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 4 << 5;
			cf.pz << 2 << 2;
			cf.nx << 12 << 5;
			cf.ny << 16 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 3 << 20;
			cf.py << 3 << 9 << 2;
			cf.pz << 2 << -1 << -1;
			cf.nx << 0 << 0 << 0;
			cf.ny << 7 << 4 << 13;
			cf.nz << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 4 << 2;
			cf.pz << 1 << 2;
			cf.nx << 1 << 0;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 9 << 11;
			cf.py << 2 << 1 << 2;
			cf.pz << 0 << 0 << 0;
			cf.nx << 2 << 2 << 0;
			cf.ny << 2 << 2 << 13;
			cf.nz << 2 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 10;
			cf.py << 23 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 1 << 1;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 6 << 3 << 4;
			cf.py << 8 << 6 << 4 << 2;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 1 << 1 << 1 << 4;
			cf.ny << 9 << 7 << 8 << 20;
			cf.nz << 1 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 4 << 4 << 10 << 3;
			cf.py << 9 << 16 << 13 << 12 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 11 << 3 << 17 << 4;
			cf.ny << 8 << 11 << 9 << 0 << 4;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 6 << 8;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 7 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 13;
			cf.ny << 5 << 9;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 8 << 2;
			cf.pz << 1 << -1;
			cf.nx << 16 << 4;
			cf.ny << 14 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 16 << 15;
			cf.pz << 0 << 0;
			cf.nx << 1 << 20;
			cf.ny << 23 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 2 << 3;
			cf.ny << 5 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 8;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 10 << 10;
			cf.ny << 1 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 21;
			cf.py << 18 << 16;
			cf.pz << 0 << 0;
			cf.nx << 10 << 3;
			cf.ny << 17 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 23 << 4;
			cf.pz << 0 << 2;
			cf.nx << 5 << 11;
			cf.ny << 3 << 7;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 3 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 1 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 5 << 9 << 8 << 9;
			cf.py << 8 << 12 << 13 << 18;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 6 << 5 << 2 << 5;
			cf.ny << 8 << 4 << 7 << 11;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 0 << 0;
			cf.pz << 0 << 2;
			cf.nx << 5 << 5;
			cf.ny << 3 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 12 << 13;
			cf.pz << 0 << 0;
			cf.nx << 9 << 1;
			cf.ny << 14 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 16 << 9 << 4 << 15;
			cf.py << 11 << 13 << 8 << 4 << 12;
			cf.pz << 1 << 0 << 1 << 2 << 0;
			cf.nx << 3 << 3 << 3 << 3 << 4;
			cf.ny << 4 << 2 << 1 << 3 << 0;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 7 << 6;
			cf.pz << 1 << -1;
			cf.nx << 19 << 8;
			cf.ny << 17 << 11;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 15 << 12 << 13 << 13;
			cf.py << 2 << 2 << 2 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 20 << 9 << 19 << 20 << 4;
			cf.ny << 14 << 2 << 5 << 15 << 1;
			cf.nz << 0 << 1 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 8;
			cf.py << 20 << 7;
			cf.pz << 0 << 1;
			cf.nx << 4 << 9;
			cf.ny << 2 << 2;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 11 << 5;
			cf.pz << 1 << 2;
			cf.nx << 13 << 19;
			cf.ny << 20 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 11 << 3;
			cf.py << 20 << 20 << 5;
			cf.pz << 0 << 0 << -1;
			cf.nx << 11 << 12 << 6;
			cf.ny << 21 << 21 << 10;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 14;
			cf.pz << 1 << 0;
			cf.nx << 3 << 13;
			cf.ny << 4 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 9;
			cf.pz << 2 << 1;
			cf.nx << 2 << 11;
			cf.ny << 8 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 5 << 5;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 6 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 23;
			cf.py << 5 << 9;
			cf.pz << 1 << 0;
			cf.nx << 8 << 2;
			cf.ny << 11 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 23;
			cf.py << 12 << 9;
			cf.pz << 0 << -1;
			cf.nx << 11 << 22;
			cf.ny << 10 << 21;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 12;
			cf.py << 7 << 7;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 7 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 8;
			cf.py << 18 << 1;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 8 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 17;
			cf.py << 11 << 11;
			cf.pz << 0 << 0;
			cf.nx << 15 << 2;
			cf.ny << 9 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 3 << 0;
			cf.pz << 2 << -1;
			cf.nx << 9 << 10;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 13;
			cf.py << 20 << 21;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 20 << 4 << 18 << 19;
			cf.py << 17 << 16 << 5 << 22 << 20;
			cf.pz << 0 << 0 << 2 << 0 << 0;
			cf.nx << 8 << 11 << 5 << 6 << 2;
			cf.ny << 10 << 15 << 11 << 10 << 1;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 5 << 6;
			cf.py << 8 << 10 << 10;
			cf.pz << 1 << 1 << 1;
			cf.nx << 11 << 8 << 22;
			cf.ny << 19 << 2 << 15;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 2 << 13;
			cf.py << 7 << 10 << 10;
			cf.pz << 1 << -1 << -1;
			cf.nx << 11 << 11 << 23;
			cf.ny << 8 << 9 << 14;
			cf.nz << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 6 << 1 << 5 << 10;
			cf.py << 7 << 14 << 1 << 9 << 2;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 11 << 0 << 1 << 5 << 1;
			cf.ny << 14 << 12 << 18 << 5 << 19;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 21 << 21 << 10;
			cf.py << 16 << 17 << 10;
			cf.pz << 0 << 0 << 1;
			cf.nx << 5 << 5 << 1;
			cf.ny << 9 << 9 << 18;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 21;
			cf.py << 6 << 17;
			cf.pz << 1 << -1;
			cf.nx << 20 << 10;
			cf.ny << 7 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 11;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 6 << 13;
			cf.ny << 2 << 4;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 4 << 7 << 9;
			cf.py << 3 << 4 << 10 << 3;
			cf.pz << 2 << 2 << 1 << 1;
			cf.nx << 21 << 2 << 15 << 5;
			cf.ny << 0 << 0 << 0 << 2;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 11 << 11;
			cf.py << 7 << 6 << 9;
			cf.pz << 1 << 1 << 1;
			cf.nx << 23 << 4 << 9;
			cf.ny << 23 << 5 << 6;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 15;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 23 << 11 << 23 << 23;
			cf.py << 11 << 22 << 10 << 21 << 20;
			cf.pz << 1 << 0 << 1 << 0 << 0;
			cf.nx << 10 << 9 << 19 << 10 << 10;
			cf.ny << 10 << 11 << 20 << 9 << 9;
			cf.nz << 1 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 23;
			cf.py << 13 << 22;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 1;
			cf.py << 19 << 0;
			cf.pz << 0 << -1;
			cf.nx << 11 << 12;
			cf.ny << 22 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 8;
			cf.py << 4 << 3;
			cf.pz << 1 << -1;
			cf.nx << 5 << 23;
			cf.ny << 2 << 7;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 6 << 20;
			cf.pz << 1 << -1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 6;
			cf.nz << 1 << 1;
		}
		*a_iter++ = -1.135386;
		*a_iter++ = 1.135386;
		*a_iter++ = -0.90908;
		*a_iter++ = 0.90908;
		*a_iter++ = -0.591378;
		*a_iter++ = 0.591378;
		*a_iter++ = -0.5556534;
		*a_iter++ = 0.5556534;
		*a_iter++ = -0.508415;
		*a_iter++ = 0.508415;
		*a_iter++ = -0.4464489;
		*a_iter++ = 0.4464489;
		*a_iter++ = -0.4463241;
		*a_iter++ = 0.4463241;
		*a_iter++ = -0.4985226;
		*a_iter++ = 0.4985226;
		*a_iter++ = -0.4424638;
		*a_iter++ = 0.4424638;
		*a_iter++ = -0.4300093;
		*a_iter++ = 0.4300093;
		*a_iter++ = -0.4231341;
		*a_iter++ = 0.4231341;
		*a_iter++ = -0.4087428;
		*a_iter++ = 0.4087428;
		*a_iter++ = -0.337448;
		*a_iter++ = 0.337448;
		*a_iter++ = -0.3230151;
		*a_iter++ = 0.3230151;
		*a_iter++ = -0.3084427;
		*a_iter++ = 0.3084427;
		*a_iter++ = -0.3235494;
		*a_iter++ = 0.3235494;
		*a_iter++ = -0.2589281;
		*a_iter++ = 0.2589281;
		*a_iter++ = -0.2970292;
		*a_iter++ = 0.2970292;
		*a_iter++ = -0.2957065;
		*a_iter++ = 0.2957065;
		*a_iter++ = -0.3997619;
		*a_iter++ = 0.3997619;
		*a_iter++ = -0.3535901;
		*a_iter++ = 0.3535901;
		*a_iter++ = -0.2725396;
		*a_iter++ = 0.2725396;
		*a_iter++ = -0.2649725;
		*a_iter++ = 0.2649725;
		*a_iter++ = -0.3103888;
		*a_iter++ = 0.3103888;
		*a_iter++ = -0.3117775;
		*a_iter++ = 0.3117775;
		*a_iter++ = -0.258962;
		*a_iter++ = 0.258962;
		*a_iter++ = -0.2689202;
		*a_iter++ = 0.2689202;
		*a_iter++ = -0.2127024;
		*a_iter++ = 0.2127024;
		*a_iter++ = -0.2436322;
		*a_iter++ = 0.2436322;
		*a_iter++ = -0.3120574;
		*a_iter++ = 0.3120574;
		*a_iter++ = -0.278601;
		*a_iter++ = 0.278601;
		*a_iter++ = -0.2649072;
		*a_iter++ = 0.2649072;
		*a_iter++ = -0.2766509;
		*a_iter++ = 0.2766509;
		*a_iter++ = -0.2367237;
		*a_iter++ = 0.2367237;
		*a_iter++ = -0.2658049;
		*a_iter++ = 0.2658049;
		*a_iter++ = -0.2103463;
		*a_iter++ = 0.2103463;
		*a_iter++ = -0.1911522;
		*a_iter++ = 0.1911522;
		*a_iter++ = -0.2535425;
		*a_iter++ = 0.2535425;
		*a_iter++ = -0.2434696;
		*a_iter++ = 0.2434696;
		*a_iter++ = -0.2180788;
		*a_iter++ = 0.2180788;
		*a_iter++ = -0.2496873;
		*a_iter++ = 0.2496873;
		*a_iter++ = -0.2700969;
		*a_iter++ = 0.2700969;
		*a_iter++ = -0.2565479;
		*a_iter++ = 0.2565479;
		*a_iter++ = -0.2737741;
		*a_iter++ = 0.2737741;
		*a_iter++ = -0.1675507;
		*a_iter++ = 0.1675507;
		*a_iter++ = -0.2551417;
		*a_iter++ = 0.2551417;
		*a_iter++ = -0.2067648;
		*a_iter++ = 0.2067648;
		*a_iter++ = -0.1636834;
		*a_iter++ = 0.1636834;
		*a_iter++ = -0.2129306;
		*a_iter++ = 0.2129306;
		*a_iter++ = -0.1656758;
		*a_iter++ = 0.1656758;
		*a_iter++ = -0.1919369;
		*a_iter++ = 0.1919369;
		*a_iter++ = -0.2031763;
		*a_iter++ = 0.2031763;
		*a_iter++ = -0.2062327;
		*a_iter++ = 0.2062327;
		*a_iter++ = -0.257795;
		*a_iter++ = 0.257795;
		*a_iter++ = -0.2951823;
		*a_iter++ = 0.2951823;
		*a_iter++ = -0.202316;
		*a_iter++ = 0.202316;
		*a_iter++ = -0.2022234;
		*a_iter++ = 0.2022234;
		*a_iter++ = -0.2132906;
		*a_iter++ = 0.2132906;
		*a_iter++ = -0.1653278;
		*a_iter++ = 0.1653278;
		*a_iter++ = -0.1648474;
		*a_iter++ = 0.1648474;
		*a_iter++ = -0.1593352;
		*a_iter++ = 0.1593352;
		*a_iter++ = -0.173565;
		*a_iter++ = 0.173565;
		*a_iter++ = -0.1688778;
		*a_iter++ = 0.1688778;
		*a_iter++ = -0.1519705;
		*a_iter++ = 0.1519705;
		*a_iter++ = -0.1812202;
		*a_iter++ = 0.1812202;
		*a_iter++ = -0.1967481;
		*a_iter++ = 0.1967481;
		*a_iter++ = -0.1852954;
		*a_iter++ = 0.1852954;
		*a_iter++ = -0.231778;
		*a_iter++ = 0.231778;
		*a_iter++ = -0.2036251;
		*a_iter++ = 0.2036251;
		*a_iter++ = -0.1609324;
		*a_iter++ = 0.1609324;
		*a_iter++ = -0.2160205;
		*a_iter++ = 0.2160205;
		*a_iter++ = -0.202619;
		*a_iter++ = 0.202619;
		*a_iter++ = -0.1854761;
		*a_iter++ = 0.1854761;
		*a_iter++ = -0.1832038;
		*a_iter++ = 0.1832038;
		*a_iter++ = -0.2001141;
		*a_iter++ = 0.2001141;
		*a_iter++ = -0.1418333;
		*a_iter++ = 0.1418333;
		*a_iter++ = -0.1704773;
		*a_iter++ = 0.1704773;
		*a_iter++ = -0.1586261;
		*a_iter++ = 0.1586261;
		*a_iter++ = -0.1587582;
		*a_iter++ = 0.1587582;
		*a_iter++ = -0.1899489;
		*a_iter++ = 0.1899489;
		*a_iter++ = -0.147716;
		*a_iter++ = 0.147716;
		*a_iter++ = -0.2260467;
		*a_iter++ = 0.2260467;
		*a_iter++ = -0.2393598;
		*a_iter++ = 0.2393598;
		*a_iter++ = -0.1582373;
		*a_iter++ = 0.1582373;
		*a_iter++ = -0.1702498;
		*a_iter++ = 0.1702498;
		*a_iter++ = -0.1737398;
		*a_iter++ = 0.1737398;
		*a_iter++ = -0.1462529;
		*a_iter++ = 0.1462529;
		*a_iter++ = -0.1396517;
		*a_iter++ = 0.1396517;
		*a_iter++ = -0.1629625;
		*a_iter++ = 0.1629625;
		*a_iter++ = -0.1446933;
		*a_iter++ = 0.1446933;
		*a_iter++ = -0.1811657;
		*a_iter++ = 0.1811657;
		*a_iter++ = -0.1336427;
		*a_iter++ = 0.1336427;
		*a_iter++ = -0.1924813;
		*a_iter++ = 0.1924813;
		*a_iter++ = -0.145752;
		*a_iter++ = 0.145752;
		*a_iter++ = -0.1600259;
		*a_iter++ = 0.1600259;
		*a_iter++ = -0.1297;
		*a_iter++ = 0.1297;
		*a_iter++ = -0.2076199;
		*a_iter++ = 0.2076199;
		*a_iter++ = -0.151006;
		*a_iter++ = 0.151006;
		*a_iter++ = -0.1914568;
		*a_iter++ = 0.1914568;
		*a_iter++ = -0.2138162;
		*a_iter++ = 0.2138162;
		*a_iter++ = -0.1856916;
		*a_iter++ = 0.1856916;
		*a_iter++ = -0.1843047;
		*a_iter++ = 0.1843047;
		*a_iter++ = -0.1526846;
		*a_iter++ = 0.1526846;
		*a_iter++ = -0.132832;
		*a_iter++ = 0.132832;
		*a_iter++ = -0.1751311;
		*a_iter++ = 0.1751311;
		*a_iter++ = -0.1643908;
		*a_iter++ = 0.1643908;
		*a_iter++ = -0.1482706;
		*a_iter++ = 0.1482706;
		*a_iter++ = -0.1622298;
		*a_iter++ = 0.1622298;
		*a_iter++ = -0.1884979;
		*a_iter++ = 0.1884979;
		*a_iter++ = -0.1633604;
		*a_iter++ = 0.1633604;
		*a_iter++ = -0.1554166;
		*a_iter++ = 0.1554166;
		*a_iter++ = -0.1405332;
		*a_iter++ = 0.1405332;
		*a_iter++ = -0.1772398;
		*a_iter++ = 0.1772398;
		*a_iter++ = -0.1410008;
		*a_iter++ = 0.1410008;
		*a_iter++ = -0.1362301;
		*a_iter++ = 0.1362301;
		*a_iter++ = -0.1709087;
		*a_iter++ = 0.1709087;
		*a_iter++ = -0.1584613;
		*a_iter++ = 0.1584613;
		*a_iter++ = -0.1188814;
		*a_iter++ = 0.1188814;
		*a_iter++ = -0.1423888;
		*a_iter++ = 0.1423888;
		*a_iter++ = -0.1345565;
		*a_iter++ = 0.1345565;
		*a_iter++ = -0.1835986;
		*a_iter++ = 0.1835986;
		*a_iter++ = -0.1445329;
		*a_iter++ = 0.1445329;
		*a_iter++ = -0.1385826;
		*a_iter++ = 0.1385826;
		*a_iter++ = -0.1558917;
		*a_iter++ = 0.1558917;
		*a_iter++ = -0.1476053;
		*a_iter++ = 0.1476053;
		*a_iter++ = -0.1370722;
		*a_iter++ = 0.1370722;
		*a_iter++ = -0.2362666;
		*a_iter++ = 0.2362666;
		*a_iter++ = -0.2907774;
		*a_iter++ = 0.2907774;
		*a_iter++ = -0.165636;
		*a_iter++ = 0.165636;
		*a_iter++ = -0.1644407;
		*a_iter++ = 0.1644407;
		*a_iter++ = -0.1443394;
		*a_iter++ = 0.1443394;
		*a_iter++ = -0.1438823;
		*a_iter++ = 0.1438823;
		*a_iter++ = -0.1476964;
		*a_iter++ = 0.1476964;
		*a_iter++ = -0.1956593;
		*a_iter++ = 0.1956593;
		*a_iter++ = -0.2417519;
		*a_iter++ = 0.2417519;
		*a_iter++ = -0.1659315;
		*a_iter++ = 0.1659315;
		*a_iter++ = -0.1466254;
		*a_iter++ = 0.1466254;
		*a_iter++ = -0.2034909;
		*a_iter++ = 0.2034909;
		*a_iter++ = -0.2128771;
		*a_iter++ = 0.2128771;
		*a_iter++ = -0.1665429;
		*a_iter++ = 0.1665429;
		*a_iter++ = -0.1387131;
		*a_iter++ = 0.1387131;
		*a_iter++ = -0.1298823;
		*a_iter++ = 0.1298823;
		*a_iter++ = -0.1329495;
		*a_iter++ = 0.1329495;
		*a_iter++ = -0.1769587;
		*a_iter++ = 0.1769587;
		*a_iter++ = -0.136653;
		*a_iter++ = 0.136653;
		*a_iter++ = -0.1254359;
		*a_iter++ = 0.1254359;
		*a_iter++ = -0.1673022;
		*a_iter++ = 0.1673022;
		*a_iter++ = -0.1602519;
		*a_iter++ = 0.1602519;
		*a_iter++ = -0.1897245;
		*a_iter++ = 0.1897245;
		*a_iter++ = -0.1893579;
		*a_iter++ = 0.1893579;
		*a_iter++ = -0.157935;
		*a_iter++ = 0.157935;
		*a_iter++ = -0.1472589;
		*a_iter++ = 0.1472589;
		*a_iter++ = -0.1614193;
		*a_iter++ = 0.1614193;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 203;
		sc.threshold = -4.769677;
		sc.features.SetCount(203);
		sc.alpha.SetCount(406);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 5 << 14 << 9 << 7;
			cf.py << 9 << 13 << 3 << 1 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 1 << 0 << 5 << 14 << 9;
			cf.ny << 5 << 3 << 8 << 8 << 9;
			cf.nz << 2 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 13 << 11 << 17 << 12;
			cf.py << 2 << 2 << 4 << 13 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 22 << 8 << 23 << 22;
			cf.ny << 8 << 15 << 11 << 12 << 3;
			cf.nz << 1 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 11 << 11 << 11 << 16;
			cf.py << 4 << 8 << 7 << 9 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 8 << 14 << 9 << 9;
			cf.ny << 4 << 4 << 8 << 8 << 8;
			cf.nz << 1 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 12 << 12 << 8 << 3;
			cf.py << 11 << 7 << 8 << 10 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 2;
			cf.nx << 8 << 4 << 4 << 4 << 0;
			cf.ny << 4 << 4 << 4 << 11 << 0;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 19 << 17 << 18 << 9 << 9;
			cf.py << 3 << 2 << 3 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 21 << 21 << 10 << 22 << 22;
			cf.ny << 1 << 2 << 0 << 4 << 3;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 4 << 6;
			cf.pz << 2 << 1;
			cf.nx << 8 << 7;
			cf.ny << 4 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 17 << 17 << 13 << 12;
			cf.py << 18 << 15 << 16 << 18 << 18;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 13 << 19 << 5 << 20 << 6;
			cf.ny << 16 << 4 << 1 << 19 << 0;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 7 << 4 << 5 << 5;
			cf.py << 15 << 23 << 6 << 12 << 16;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 3 << 14 << 14 << 6 << 6;
			cf.ny << 4 << 11 << 11 << 9 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 9 << 6 << 3 << 11;
			cf.py << 2 << 2 << 5 << 3 << 2;
			cf.pz << 0 << 0 << 1 << 2 << 0;
			cf.nx << 3 << 4 << 2 << 5 << 5;
			cf.ny << 4 << 11 << 2 << 8 << 8;
			cf.nz << 1 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 1 << 5 << 3 << 3;
			cf.py << 14 << 4 << 15 << 7 << 7;
			cf.pz << 0 << 2 << 0 << 1 << -1;
			cf.nx << 0 << 0 << 1 << 1 << 1;
			cf.ny << 7 << 8 << 18 << 17 << 5;
			cf.nz << 1 << 1 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 9 << 5 << 3;
			cf.py << 14 << 14 << 0 << 3 << 7;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 7 << 7 << 14 << 8 << 13;
			cf.ny << 7 << 8 << 13 << 10 << 10;
			cf.nz << 1 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 7 << 9;
			cf.pz << 1 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 21 << 17;
			cf.py << 7 << 11 << 23;
			cf.pz << 1 << 0 << 0;
			cf.nx << 21 << 9 << 3;
			cf.ny << 23 << 5 << 5;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 11 << 9 << 10 << 11;
			cf.py << 2 << 0 << 1 << 1 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 5 << 6 << 4 << 3;
			cf.ny << 8 << 4 << 18 << 7 << 4;
			cf.nz << 1 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 22 << 3 << 19 << 10;
			cf.py << 20 << 9 << 4 << 22 << 3;
			cf.pz << 0 << 0 << 2 << 0 << 1;
			cf.nx << 8 << 20 << 8 << 3 << 2;
			cf.ny << 4 << 3 << 6 << 4 << 3;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 9 << 2;
			cf.ny << 15 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 13;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 20 << 21;
			cf.ny << 1 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 2 << 7 << 6 << 8;
			cf.py << 0 << 2 << 3 << 3 << 3;
			cf.pz << 2 << 1 << 0 << 0 << 0;
			cf.nx << 1 << 2 << 1 << 1 << 1;
			cf.ny << 0 << 0 << 4 << 3 << 3;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 10;
			cf.py << 9 << 11;
			cf.pz << 0 << 0;
			cf.nx << 6 << 3;
			cf.ny << 9 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 6;
			cf.py << 10 << 11 << 13 << 12 << 6;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 10 << 2 << 1 << 10 << 10;
			cf.ny << 10 << 4 << 2 << 11 << 9;
			cf.nz << 0 << 1 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 18 << 11 << 17 << 15;
			cf.py << 11 << 12 << 8 << 12 << 11;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 14 << 0 << 19 << 0 << 10;
			cf.ny << 9 << 3 << 14 << 8 << 9;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 5 << 9 << 5 << 8;
			cf.py << 21 << 18 << 20 << 23;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 3 << 1;
			cf.ny << 20 << 3 << 4 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 3 << 2;
			cf.pz << 2 << 2;
			cf.nx << 3 << 12;
			cf.ny << 4 << 23;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 1 << 1 << 1 << 1;
			cf.py << 2 << 16 << 14 << 13 << 12;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 9 << 4 << 7;
			cf.ny << 9 << 3 << 4 << 2 << 9;
			cf.nz << 1 << 2 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 9;
			cf.py << 3 << 7;
			cf.pz << 2 << -1;
			cf.nx << 4 << 9;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 16 << 17 << 15 << 8;
			cf.py << 3 << 3 << 3 << 18 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 1 << 2 << 2 << 1 << 3;
			cf.ny << 5 << 3 << 2 << 6 << 0;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 17;
			cf.py << 4 << 14;
			cf.pz << 2 << 0;
			cf.nx << 15 << 7;
			cf.ny << 15 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 12 << 3;
			cf.py << 3 << 13 << 3;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 17 << 4;
			cf.ny << 3 << 19 << 4;
			cf.nz << 2 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 5 << 12 << 2;
			cf.py << 9 << 6 << 19 << 4;
			cf.pz << 1 << 1 << 0 << 2;
			cf.nx << 12 << 17 << 4 << 4;
			cf.ny << 18 << 19 << 4 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 19 << 20 << 20 << 19;
			cf.py << 7 << 14 << 13 << 14 << 13;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 11 << 23 << 23 << 23 << 23;
			cf.ny << 9 << 15 << 13 << 16 << 14;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 0 << 0 << 0 << 2;
			cf.py << 5 << 6 << 5 << 14;
			cf.pz << 1 << 1 << 2 << 0;
			cf.nx << 0 << 3 << 3 << 17;
			cf.ny << 23 << 5 << 5 << 9;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 4;
			cf.py << 23 << 5;
			cf.pz << 0 << 2;
			cf.nx << 9 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 5 << 10 << 12;
			cf.py << 3 << 3 << 23 << 23;
			cf.pz << 1 << 1 << 0 << 0;
			cf.nx << 11 << 1 << 1 << 4;
			cf.ny << 21 << 3 << 5 << 5;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 9 << 4;
			cf.pz << 1 << 2;
			cf.nx << 4 << 9;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 23 << 23 << 23 << 23;
			cf.py << 14 << 9 << 13 << 11 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 6 << 13 << 7 << 8 << 8;
			cf.ny << 9 << 6 << 3 << 3 << 3;
			cf.nz << 1 << 0 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 4 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 8;
			cf.ny << 1 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 12;
			cf.py << 4 << 18;
			cf.pz << 2 << 0;
			cf.nx << 12 << 0;
			cf.ny << 16 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 2;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 16 << 4;
			cf.ny << 1 << 0;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 5 << 3;
			cf.ny << 19 << 9;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 20 << 19 << 20 << 21;
			cf.py << 2 << 0 << 1 << 3;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 11 << 5 << 23 << 11;
			cf.ny << 0 << 0 << 1 << 1;
			cf.nz << 1 << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 7 << 5;
			cf.pz << 0 << 0;
			cf.nx << 8 << 5;
			cf.ny << 3 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 22 << 21 << 22 << 22 << 22;
			cf.py << 20 << 22 << 18 << 19 << 16;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 2 << 3 << 3 << 15 << 15;
			cf.ny << 4 << 5 << 4 << 7 << 7;
			cf.nz << 1 << 2 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 15 << 14 << 14;
			cf.py << 1 << 1 << 1;
			cf.pz << 0 << 0 << -1;
			cf.nx << 17 << 18 << 16;
			cf.ny << 1 << 2 << 1;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 16 << 16 << 15;
			cf.py << 2 << 1 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 7 << 4 << 2 << 11;
			cf.ny << 11 << 2 << 1 << 4;
			cf.nz << 1 << 2 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 18 << 0 << 0 << 0;
			cf.py << 14 << 6 << 5 << 4;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 19 << 19 << 19 << 19;
			cf.ny << 16 << 19 << 17 << 18;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 5 << 5 << 0;
			cf.py << 14 << 1 << 4 << 4;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 11 << 8 << 2 << 15;
			cf.ny << 17 << 14 << 1 << 9;
			cf.nz << 0 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 19 << 21;
			cf.pz << 0 << 0;
			cf.nx << 10 << 2;
			cf.ny << 15 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 4;
			cf.py << 4 << 6;
			cf.pz << 1 << 1;
			cf.nx << 3 << 3;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 1 << 13;
			cf.pz << 2 << 0;
			cf.nx << 7 << 2;
			cf.ny << 1 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 15 << 10 << 4 << 7;
			cf.py << 23 << 3 << 1 << 7;
			cf.pz << 0 << 1 << 2 << 1;
			cf.nx << 0 << 4 << 1 << 1;
			cf.ny << 0 << 2 << 0 << -1900147915;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 12 << 11;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 2 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 1 << 0;
			cf.py << 9 << 4 << 3 << 2 << 6;
			cf.pz << 0 << 1 << 2 << 1 << 1;
			cf.nx << 9 << 4 << 2 << 16 << 16;
			cf.ny << 7 << 4 << 2 << 8 << 8;
			cf.nz << 0 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 4 << 9 << 4 << 4;
			cf.py << 12 << 5 << 6 << 3 << 4;
			cf.pz << 0 << 2 << 1 << 2 << -1;
			cf.nx << 4 << 3 << 3 << 2 << 3;
			cf.ny << 23 << 19 << 21 << 16 << 18;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 14 << 13;
			cf.pz << 0 << 0;
			cf.nx << 3 << 10;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 4 << 4 << 2 << 2;
			cf.py << 8 << 11 << 7 << 4 << 4;
			cf.pz << 1 << 1 << 1 << 2 << -1;
			cf.nx << 20 << 18 << 19 << 20 << 19;
			cf.ny << 4 << 0 << 2 << 3 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 12 << 14 << 8 << 16;
			cf.py << 2 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 3 << 15 << 3 << 2 << 2;
			cf.ny << 2 << 9 << 7 << 2 << 2;
			cf.nz << 2 << 0 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 11 << 11 << 11;
			cf.py << 10 << 12 << 11 << 12 << 12;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 13 << 13 << 20 << 10 << 13;
			cf.ny << 9 << 11 << 8 << 4 << 10;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 8 << 13;
			cf.ny << 4 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 7;
			cf.py << 20 << 3;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 10 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 10 << 17;
			cf.py << 9 << 3 << 5;
			cf.pz << 0 << -1 << -1;
			cf.nx << 1 << 3 << 1;
			cf.ny << 5 << 16 << 6;
			cf.nz << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 5;
			cf.pz << 2 << -1;
			cf.nx << 8 << 3;
			cf.ny << 14 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 9 << 12 << 10;
			cf.py << 2 << 2 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 4 << 4 << 4 << 10;
			cf.ny << 5 << 5 << 0 << 16;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 9 << 12;
			cf.py << 2 << 2 << 2;
			cf.pz << 1 << -1 << -1;
			cf.nx << 4 << 7 << 2;
			cf.ny << 3 << 1 << 0;
			cf.nz << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 12;
			cf.pz << 2 << 0;
			cf.nx << 7 << 4;
			cf.ny << 6 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 12 << 6 << 3;
			cf.py << 12 << 11 << 21 << 7;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 1 << 0 << 0 << 0;
			cf.ny << 13 << 3 << 6 << 5;
			cf.nz << 0 << 2 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 1 << 3;
			cf.py << 21 << 8 << 18;
			cf.pz << 0 << 1 << 0;
			cf.nx << 11 << 20 << 0;
			cf.ny << 17 << 17 << 6;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 8;
			cf.py << 3 << 12;
			cf.pz << 2 << 0;
			cf.nx << 2 << 20;
			cf.ny << 4 << 17;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 3 << 4 << 3 << 2;
			cf.py << 10 << 14 << 14 << 15 << 13;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 1 << 0 << 0;
			cf.ny << 21 << 20 << 23 << 19 << 19;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 15;
			cf.py << 7 << 4;
			cf.pz << 1 << -1;
			cf.nx << 3 << 8;
			cf.ny << 4 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 19 << 14 << 12 << 15 << 4;
			cf.py << 8 << 12 << 10 << 16 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 2;
			cf.nx << 8 << 0 << 12 << 4 << 0;
			cf.ny << 4 << 1 << 12 << 2 << 19;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 9;
			cf.py << 15 << 3;
			cf.pz << 0 << -1;
			cf.nx << 8 << 15;
			cf.ny << 9 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 2 << 3 << 4 << 9;
			cf.py << 9 << 4 << 3 << 8 << 23;
			cf.pz << 1 << 2 << 1 << 1 << 0;
			cf.nx << 11 << 23 << 23 << 11 << 11;
			cf.ny << 0 << 2 << 3 << 1 << 1;
			cf.nz << 1 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 7;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 3 << 4;
			cf.ny << 10 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 9 << 8 << 5;
			cf.py << 12 << 15 << 13 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 3 << 12 << 14 << 13;
			cf.ny << 0 << 3 << 3 << 3;
			cf.nz << 2 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 6 << 5;
			cf.pz << 0 << 0;
			cf.nx << 8 << 11;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 20 << 21 << 21 << 21;
			cf.py << 18 << 21 << 17 << 19 << 19;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 2 << 5 << 4 << 4 << 5;
			cf.ny << 5 << 12 << 11 << 10 << 10;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 1 << 1 << 1;
			cf.py << 10 << 11 << 7 << 9 << 8;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 11 << 23 << 23 << 23 << 23;
			cf.ny << 10 << 20 << 21 << 19 << 19;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 8 << 7 << 3 << 1;
			cf.py << 14 << 13 << 13 << 2 << 2;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 1 << 10 << 2 << 2 << 10;
			cf.ny << 2 << 13 << 4 << 16 << 12;
			cf.nz << 2 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 18;
			cf.py << 12 << 12;
			cf.pz << 0 << 0;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 0;
			cf.py << 5 << 20;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 0 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 22 << 22 << 22 << 11 << 23;
			cf.py << 16 << 15 << 14 << 6 << 13;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 16 << 15 << 7 << 9 << 9;
			cf.ny << 15 << 8 << 4 << 10 << 10;
			cf.nz << 0 << 0 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 3 << 1;
			cf.pz << 0 << 2;
			cf.nx << 8 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 4 << 1;
			cf.pz << 1 << -1;
			cf.nx << 6 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 2 << 6;
			cf.py << 6 << 3 << 4;
			cf.pz << 1 << 2 << 1;
			cf.nx << 10 << 0 << 4;
			cf.ny << 9 << 4 << 3;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 8 << 4 << 10;
			cf.py << 4 << 23 << 7 << 23;
			cf.pz << 2 << 0 << 1 << 0;
			cf.nx << 9 << 4 << 11 << 9;
			cf.ny << 21 << 5 << 16 << 0;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 13 << 0;
			cf.pz << 0 << -1;
			cf.nx << 8 << 2;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 1 << 4;
			cf.pz << 1 << -1;
			cf.nx << 3 << 5;
			cf.ny << 0 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 0 << 0;
			cf.pz << 0 << 2;
			cf.nx << 2 << 10;
			cf.ny << 1 << 6;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 2;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 21 << 5;
			cf.ny << 15 << 4;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 10 << 9;
			cf.pz << 0 << 0;
			cf.nx << 0 << 3;
			cf.ny << 13 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 9;
			cf.py << 13 << 0;
			cf.pz << 0 << -1;
			cf.nx << 3 << 3;
			cf.ny << 4 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 13 << 13 << 14 << 14;
			cf.py << 12 << 10 << 11 << 13 << 13;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 9 << 8 << 4 << 5 << 7;
			cf.ny << 4 << 4 << 2 << 2 << 4;
			cf.nz << 0 << 0 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 4 << 1;
			cf.py << 2 << 0 << 0;
			cf.pz << 0 << 0 << 1;
			cf.nx << 0 << 7 << 4;
			cf.ny << 0 << 3 << 2;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 5 << 0;
			cf.pz << 0 << -1;
			cf.nx << 8 << 6;
			cf.ny << 4 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 0 << 0;
			cf.py << 20 << 2 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 12 << 3 << 10;
			cf.ny << 3 << 1 << 3;
			cf.nz << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 11 << 10 << 13 << 13;
			cf.py << 0 << 0 << 0 << 2 << 2;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 5 << 5 << 4 << 5;
			cf.ny << 14 << 0 << 2 << 6 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 11;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << -1715597992;
			cf.py << 19 << 9;
			cf.pz << 0 << -1;
			cf.nx << 7 << 14;
			cf.ny << 10 << 17;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 9 << 0;
			cf.pz << 0 << -1;
			cf.nx << 1 << 12;
			cf.ny << 2 << 10;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 9;
			cf.py << 13 << 17;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 7;
			cf.py << 1 << 9;
			cf.pz << 1 << -1;
			cf.nx << 18 << 4;
			cf.ny << 14 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 7;
			cf.py << 23 << 9;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 7;
			cf.py << 17 << 9;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 0 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 20 << 1;
			cf.pz << 0 << -1;
			cf.nx << 5 << 3;
			cf.ny << 21 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 0 << 1;
			cf.py << 3 << 6 << 15;
			cf.pz << 2 << 1 << 0;
			cf.nx << 10 << 8 << 3;
			cf.ny << 6 << 4 << 2;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 18 << 8;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 8 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 2 << 2;
			cf.pz << 1 << 1;
			cf.nx << 8 << 9;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 11 << 5;
			cf.pz << 1 << 2;
			cf.nx << 13 << 3;
			cf.ny << 19 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 6;
			cf.py << 1 << 11;
			cf.pz << 2 << -1;
			cf.nx << 3 << 2;
			cf.ny << 1 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 4;
			cf.py << 10 << 5;
			cf.pz << 1 << 2;
			cf.nx << 8 << 4;
			cf.ny << 10 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 12;
			cf.py << 11 << 20;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 6 << 10;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 12;
			cf.py << 2 << 20;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 15;
			cf.py << 5 << 21;
			cf.pz << 1 << -1;
			cf.nx << 10 << 9;
			cf.ny << 3 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 9;
			cf.py << 1 << 0;
			cf.pz << 0 << 1;
			cf.nx << 19 << 3;
			cf.ny << 0 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 5;
			cf.py << 13 << 5;
			cf.pz << 0 << 2;
			cf.nx << 23 << 6;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 8;
			cf.py << 3 << 1;
			cf.pz << 2 << -1;
			cf.nx << 9 << 9;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 7 << 7;
			cf.pz << 1 << -1;
			cf.nx << 5 << 3;
			cf.ny << 23 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 3;
			cf.py << 6 << 4;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 0 << 17;
			cf.py << 20 << 3 << 21;
			cf.pz << 0 << -1 << -1;
			cf.nx << 11 << 11 << 11;
			cf.ny << 7 << 9 << 10;
			cf.nz << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 23 << 23 << 12;
			cf.py << 10 << 11 << 21 << 20 << 12;
			cf.pz << 1 << 1 << 0 << 0 << 0;
			cf.nx << 8 << 3 << 6 << 7 << 7;
			cf.ny << 4 << 5 << 11 << 11 << 11;
			cf.nz << 1 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 11 << 10;
			cf.pz << 0 << 0;
			cf.nx << 9 << 3;
			cf.ny << 2 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 14;
			cf.py << 19 << 19;
			cf.pz << 0 << 0;
			cf.nx << 12 << 13;
			cf.ny << 18 << 17;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 14 << 12 << 15 << 14;
			cf.py << 0 << 0 << 1 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 8 << 4 << 7 << 7;
			cf.ny << 3 << 4 << 2 << 5 << 5;
			cf.nz << 2 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 5;
			cf.py << 10 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 2 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 10;
			cf.py << 6 << 10;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 18 << 8 << 4 << 16;
			cf.py << 6 << 12 << 9 << 4 << 13;
			cf.pz << 1 << 0 << 1 << 2 << 0;
			cf.nx << 3 << 4 << 3 << 5 << 5;
			cf.ny << 0 << 2 << 3 << 1 << 1;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 8 << 0;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 4 << 5;
			cf.pz << 2 << -1;
			cf.nx << 4 << 2;
			cf.ny << 14 << 7;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 4 << 4 << 3;
			cf.py << 11 << 12 << 12 << 2;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 1 << 2 << 1 << 2;
			cf.ny << 11 << 14 << 12 << 16;
			cf.nz << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 0;
			cf.py << 11 << 0;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 21 << 11;
			cf.pz << 0 << 1;
			cf.nx << 3 << 2;
			cf.ny << 10 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 3 << 13;
			cf.py << 2 << 0 << 2;
			cf.pz << 0 << 2 << 0;
			cf.nx << 7 << 16 << 1;
			cf.ny << 10 << 4 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 2 << 5;
			cf.pz << 1 << 0;
			cf.nx << 6 << 18;
			cf.ny << 1 << 19;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 16;
			cf.py << 0 << 16;
			cf.pz << 1 << -1;
			cf.nx << 11 << 2;
			cf.ny << 5 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 13 << 1;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 22 << 21;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 18 << 18;
			cf.pz << 0 << 0;
			cf.nx << 5 << 8;
			cf.ny << 9 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 20 << 18;
			cf.pz << 0 << 0;
			cf.nx << 8 << 3;
			cf.ny << 5 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 2;
			cf.py << 17 << 1;
			cf.pz << 0 << -1;
			cf.nx << 14 << 13;
			cf.ny << 15 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 2 << 3;
			cf.pz << 2 << 2;
			cf.nx << 8 << 3;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 18 << 18 << 8 << 7;
			cf.py << 6 << 11 << 11 << 7 << 9;
			cf.pz << 1 << 0 << -1 << -1 << -1;
			cf.nx << 5 << 13 << 5 << 11 << 5;
			cf.ny << 3 << 11 << 0 << 8 << 2;
			cf.nz << 2 << 0 << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 0 << 5 << 4 << 7;
			cf.py << 15 << 0 << 4 << 0 << 9;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 8 << 7 << 4 << 16 << 6;
			cf.ny << 17 << 12 << 9 << 10 << 12;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 7;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 9 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 0 << 22 << 4;
			cf.py << 4 << 4 << 23 << 0;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 2 << 4 << 2 << 5;
			cf.ny << 0 << 1 << 2 << 9;
			cf.nz << 2 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 9 << 10 << 10 << 8;
			cf.py << 0 << 1 << 1 << 2 << 0;
			cf.pz << 1 << 1 << 1 << 1 << 1;
			cf.nx << 4 << 16 << 16 << 16 << 6;
			cf.ny << 2 << 11 << 11 << 11 << 12;
			cf.nz << 2 << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 6 << 5;
			cf.pz << 1 << 1;
			cf.nx << 0 << 4;
			cf.ny << 3 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 3 << 4;
			cf.py << 5 << 9 << 8;
			cf.pz << 1 << -1 << -1;
			cf.nx << 11 << 23 << 23;
			cf.ny << 7 << 12 << 11;
			cf.nz << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 12 << 7;
			cf.py << 19 << 19 << 10;
			cf.pz << 0 << 0 << 1;
			cf.nx << 13 << 5 << 19;
			cf.ny << 20 << 15 << 22;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 12;
			cf.py << 12 << 13;
			cf.pz << 0 << 0;
			cf.nx << 9 << 10;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 12;
			cf.py << 1 << 13;
			cf.pz << 2 << -1;
			cf.nx << 2 << 7;
			cf.ny << 2 << 13;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 8 << 9;
			cf.pz << 1 << 1;
			cf.nx << 19 << 7;
			cf.ny << 23 << 13;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 7 << 23 << 15;
			cf.py << 11 << 12 << 4 << 21;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 2 << 5 << 1 << 10;
			cf.ny << 6 << 6 << 2 << 13;
			cf.nz << 0 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 9;
			cf.py << 3 << 3;
			cf.pz << 0 << 0;
			cf.nx << 2 << 3;
			cf.ny << 2 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 3 << 4;
			cf.pz << 2 << -1;
			cf.nx << 3 << 6;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 11;
			cf.py << 20 << 16;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 20;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 7;
			cf.py << 7 << 5;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 11 << 3;
			cf.pz << 1 << 2;
			cf.nx << 5 << 5;
			cf.ny << 3 << 5;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 3;
			cf.py << 11 << 5;
			cf.pz << 1 << -1;
			cf.nx << 4 << 1;
			cf.ny << 12 << 3;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 11;
			cf.py << 6 << 4;
			cf.pz << 1 << -1;
			cf.nx << 10 << 20;
			cf.ny << 9 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 2 << 2 << 1;
			cf.py << 15 << 13 << 16 << 14 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 15 << 8 << 9 << 8 << 4;
			cf.ny << 11 << 6 << 5 << 5 << 4;
			cf.nz << 0 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 2;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 7 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 11;
			cf.py << 1 << 3;
			cf.pz << 2 << 1;
			cf.nx << 10 << 10;
			cf.ny << 3 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 11;
			cf.py << 13 << 18;
			cf.pz << 0 << -1;
			cf.nx << 6 << 9;
			cf.ny << 9 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 1 << 2 << 5 << 6;
			cf.py << 14 << 4 << 9 << 15 << 23;
			cf.pz << 0 << 2 << 1 << 0 << 0;
			cf.nx << 4 << 9 << 18 << 16 << 17;
			cf.ny << 0 << 1 << 1 << 0 << 0;
			cf.nz << 2 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 17;
			cf.py << 0 << 0;
			cf.pz << 0 << 0;
			cf.nx << 23 << 23;
			cf.ny << 5 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 8;
			cf.py << 20 << 6;
			cf.pz << 0 << -1;
			cf.nx << 5 << 6;
			cf.ny << 12 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 15;
			cf.py << 15 << 0;
			cf.pz << 0 << -1;
			cf.nx << 6 << 3;
			cf.ny << 16 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 20;
			cf.py << 7 << 8;
			cf.pz << 0 << 0;
			cf.nx << 18 << 11;
			cf.ny << 9 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 4;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 3 << 15;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 2;
			cf.pz << 1 << 2;
			cf.nx << 5 << 5;
			cf.ny << 2 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 20;
			cf.py << 1 << 20;
			cf.pz << 1 << -1;
			cf.nx << 15 << 17;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 16 << 4;
			cf.pz << 0 << 2;
			cf.nx << 4 << 0;
			cf.ny << 10 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 8;
			cf.py << 5 << 0;
			cf.pz << 1 << -1;
			cf.nx << 1 << 1;
			cf.ny << 10 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 0;
			cf.py << 3 << 0;
			cf.pz << 0 << -1;
			cf.nx << 23 << 11;
			cf.ny << 4 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 19 << 10 << 20;
			cf.py << 21 << 8 << 18;
			cf.pz << 0 << 1 << 0;
			cf.nx << 3 << 6 << 20;
			cf.ny << 5 << 11 << 14;
			cf.nz << 2 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 1 << 6 << 5;
			cf.py << 7 << 4 << 23 << 22;
			cf.pz << 1 << 2 << 0 << 0;
			cf.nx << 9 << 19 << 20 << 4;
			cf.ny << 8 << 11 << 9 << 2;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 11;
			cf.pz << 2 << 1;
			cf.nx << 12 << 10;
			cf.ny << 21 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 0 << 2 << 2;
			cf.py << 6 << 1 << 4 << 1;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 0 << 0 << 0 << 0;
			cf.ny << 5 << 8 << 9 << 4;
			cf.nz << 1 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 13 << 6 << 11 << 9;
			cf.py << 0 << 3 << 1 << 1 << 2;
			cf.pz << 2 << 0 << 1 << 0 << 0;
			cf.nx << 7 << 20 << 16 << 4 << 7;
			cf.ny << 7 << 2 << 19 << 2 << 6;
			cf.nz << 1 << 0 << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 5 << 2 << 6;
			cf.py << 7 << 7 << 4 << 11;
			cf.pz << 0 << 0 << 2 << 1;
			cf.nx << 7 << 1 << 21 << 0;
			cf.ny << 8 << 4 << 11 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 3 << 2;
			cf.pz << 2 << 2;
			cf.nx << 8 << 9;
			cf.ny << 3 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 13;
			cf.py << 3 << 5;
			cf.pz << 1 << 0;
			cf.nx << 4 << 3;
			cf.ny << 2 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 12 << 13 << 11;
			cf.py << 0 << 1 << 1 << 1;
			cf.pz << 2 << 0 << 0 << 0;
			cf.nx << 8 << 9 << 13 << 0;
			cf.ny << 4 << 1 << 16 << 3;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 4 << 14;
			cf.pz << 0 << -1;
			cf.nx << 5 << 10;
			cf.ny << 1 << 2;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 12;
			cf.py << 21 << 21;
			cf.pz << 0 << 0;
			cf.nx << 10 << 11;
			cf.ny << 19 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 12;
			cf.py << 6 << 21;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 7;
			cf.py << 19 << 0;
			cf.pz << 0 << -1;
			cf.nx << 6 << 5;
			cf.ny << 9 << 11;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 10 << 10;
			cf.py << 10 << 12 << 11 << 13 << 13;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 7 << 13 << 6 << 12 << 7;
			cf.ny << 10 << 6 << 3 << 6 << 11;
			cf.nz << 0 << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 11;
			cf.py << 6 << 12;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 15 << 16 << 15 << 17;
			cf.py << 1 << 0 << 0 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 13 << 7 << 6 << 12 << 12;
			cf.ny << 5 << 4 << 3 << 6 << 6;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 1 << 3;
			cf.pz << 2 << 1;
			cf.nx << 1 << 5;
			cf.ny << 1 << 3;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 13 << 6;
			cf.pz << 0 << 1;
			cf.nx << 4 << 9;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 3;
			cf.py << 4 << 3;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 3 << 6;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 1;
			cf.pz << 0 << 1;
			cf.nx << 5 << 5;
			cf.ny << 7 << 21;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 19 << 17;
			cf.ny << 1 << 0;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 11 << 5 << 0;
			cf.py << 6 << 1 << 1 << 22;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 0 << 10 << 10 << 1;
			cf.ny << 6 << 12 << 13 << 4;
			cf.nz << 1 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 17;
			cf.py << 6 << 13;
			cf.pz << 1 << 0;
			cf.nx << 14 << 17;
			cf.ny << 9 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 8;
			cf.py << 0 << 4;
			cf.pz << 2 << -1;
			cf.nx << 9 << 8;
			cf.ny << 1 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 14;
			cf.py << 13 << 9;
			cf.pz << 0 << -1;
			cf.nx << 23 << 23;
			cf.ny << 21 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 9;
			cf.py << 9 << 3;
			cf.pz << 0 << -1;
			cf.nx << 6 << 3;
			cf.ny << 2 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 9;
			cf.py << 3 << 3;
			cf.pz << 2 << -1;
			cf.nx << 17 << 9;
			cf.ny << 12 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 7;
			cf.py << 18 << 16;
			cf.pz << 0 << -1;
			cf.nx << 5 << 2;
			cf.ny << 9 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 0 << 1;
			cf.pz << 1 << -1;
			cf.nx << 4 << 5;
			cf.ny << 1 << 0;
			cf.nz << 0 << 0;
		}
		*a_iter++ = -1.149973;
		*a_iter++ = 1.149973;
		*a_iter++ = -0.6844773;
		*a_iter++ = 0.6844773;
		*a_iter++ = -0.6635048;
		*a_iter++ = 0.6635048;
		*a_iter++ = -0.4888349;
		*a_iter++ = 0.4888349;
		*a_iter++ = -0.4267976;
		*a_iter++ = 0.4267976;
		*a_iter++ = -0.42581;
		*a_iter++ = 0.42581;
		*a_iter++ = -0.4815853;
		*a_iter++ = 0.4815853;
		*a_iter++ = -0.4091859;
		*a_iter++ = 0.4091859;
		*a_iter++ = -0.3137414;
		*a_iter++ = 0.3137414;
		*a_iter++ = -0.333986;
		*a_iter++ = 0.333986;
		*a_iter++ = -0.3891196;
		*a_iter++ = 0.3891196;
		*a_iter++ = -0.4167691;
		*a_iter++ = 0.4167691;
		*a_iter++ = -0.3186609;
		*a_iter++ = 0.3186609;
		*a_iter++ = -0.2957171;
		*a_iter++ = 0.2957171;
		*a_iter++ = -0.3210062;
		*a_iter++ = 0.3210062;
		*a_iter++ = -0.2725684;
		*a_iter++ = 0.2725684;
		*a_iter++ = -0.2452176;
		*a_iter++ = 0.2452176;
		*a_iter++ = -0.2812662;
		*a_iter++ = 0.2812662;
		*a_iter++ = -0.3029622;
		*a_iter++ = 0.3029622;
		*a_iter++ = -0.3293745;
		*a_iter++ = 0.3293745;
		*a_iter++ = -0.3441536;
		*a_iter++ = 0.3441536;
		*a_iter++ = -0.2946918;
		*a_iter++ = 0.2946918;
		*a_iter++ = -0.2890545;
		*a_iter++ = 0.2890545;
		*a_iter++ = -0.1949205;
		*a_iter++ = 0.1949205;
		*a_iter++ = -0.2176102;
		*a_iter++ = 0.2176102;
		*a_iter++ = -0.259519;
		*a_iter++ = 0.259519;
		*a_iter++ = -0.2690931;
		*a_iter++ = 0.2690931;
		*a_iter++ = -0.2130294;
		*a_iter++ = 0.2130294;
		*a_iter++ = -0.2316308;
		*a_iter++ = 0.2316308;
		*a_iter++ = -0.2798562;
		*a_iter++ = 0.2798562;
		*a_iter++ = -0.2146988;
		*a_iter++ = 0.2146988;
		*a_iter++ = -0.2332089;
		*a_iter++ = 0.2332089;
		*a_iter++ = -0.2470614;
		*a_iter++ = 0.2470614;
		*a_iter++ = -0.22043;
		*a_iter++ = 0.22043;
		*a_iter++ = -0.2272045;
		*a_iter++ = 0.2272045;
		*a_iter++ = -0.2583686;
		*a_iter++ = 0.2583686;
		*a_iter++ = -0.2072299;
		*a_iter++ = 0.2072299;
		*a_iter++ = -0.1834971;
		*a_iter++ = 0.1834971;
		*a_iter++ = -0.2332656;
		*a_iter++ = 0.2332656;
		*a_iter++ = -0.3271297;
		*a_iter++ = 0.3271297;
		*a_iter++ = -0.2401937;
		*a_iter++ = 0.2401937;
		*a_iter++ = -0.2006316;
		*a_iter++ = 0.2006316;
		*a_iter++ = -0.2401947;
		*a_iter++ = 0.2401947;
		*a_iter++ = -0.2475346;
		*a_iter++ = 0.2475346;
		*a_iter++ = -0.2579532;
		*a_iter++ = 0.2579532;
		*a_iter++ = -0.2466235;
		*a_iter++ = 0.2466235;
		*a_iter++ = -0.1787582;
		*a_iter++ = 0.1787582;
		*a_iter++ = -0.2036892;
		*a_iter++ = 0.2036892;
		*a_iter++ = -0.1665028;
		*a_iter++ = 0.1665028;
		*a_iter++ = -0.157651;
		*a_iter++ = 0.157651;
		*a_iter++ = -0.2036997;
		*a_iter++ = 0.2036997;
		*a_iter++ = -0.2040734;
		*a_iter++ = 0.2040734;
		*a_iter++ = -0.1792532;
		*a_iter++ = 0.1792532;
		*a_iter++ = -0.2174767;
		*a_iter++ = 0.2174767;
		*a_iter++ = -0.1876948;
		*a_iter++ = 0.1876948;
		*a_iter++ = -0.1883137;
		*a_iter++ = 0.1883137;
		*a_iter++ = -0.1923872;
		*a_iter++ = 0.1923872;
		*a_iter++ = -0.2620218;
		*a_iter++ = 0.2620218;
		*a_iter++ = -0.1659873;
		*a_iter++ = 0.1659873;
		*a_iter++ = -0.1475948;
		*a_iter++ = 0.1475948;
		*a_iter++ = -0.1731607;
		*a_iter++ = 0.1731607;
		*a_iter++ = -0.2059256;
		*a_iter++ = 0.2059256;
		*a_iter++ = -0.1586309;
		*a_iter++ = 0.1586309;
		*a_iter++ = -0.1607668;
		*a_iter++ = 0.1607668;
		*a_iter++ = -0.1975101;
		*a_iter++ = 0.1975101;
		*a_iter++ = -0.2130745;
		*a_iter++ = 0.2130745;
		*a_iter++ = -0.1898872;
		*a_iter++ = 0.1898872;
		*a_iter++ = -0.2052598;
		*a_iter++ = 0.2052598;
		*a_iter++ = -0.1599397;
		*a_iter++ = 0.1599397;
		*a_iter++ = -0.1770134;
		*a_iter++ = 0.1770134;
		*a_iter++ = -0.1888249;
		*a_iter++ = 0.1888249;
		*a_iter++ = -0.1515406;
		*a_iter++ = 0.1515406;
		*a_iter++ = -0.1907771;
		*a_iter++ = 0.1907771;
		*a_iter++ = -0.1698406;
		*a_iter++ = 0.1698406;
		*a_iter++ = -0.2079535;
		*a_iter++ = 0.2079535;
		*a_iter++ = -0.1966967;
		*a_iter++ = 0.1966967;
		*a_iter++ = -0.1631391;
		*a_iter++ = 0.1631391;
		*a_iter++ = -0.2158666;
		*a_iter++ = 0.2158666;
		*a_iter++ = -0.2891774;
		*a_iter++ = 0.2891774;
		*a_iter++ = -0.1581556;
		*a_iter++ = 0.1581556;
		*a_iter++ = -0.1475359;
		*a_iter++ = 0.1475359;
		*a_iter++ = -0.1806169;
		*a_iter++ = 0.1806169;
		*a_iter++ = -0.1782238;
		*a_iter++ = 0.1782238;
		*a_iter++ = -0.166044;
		*a_iter++ = 0.166044;
		*a_iter++ = -0.1576919;
		*a_iter++ = 0.1576919;
		*a_iter++ = -0.1741775;
		*a_iter++ = 0.1741775;
		*a_iter++ = -0.1427265;
		*a_iter++ = 0.1427265;
		*a_iter++ = -0.169588;
		*a_iter++ = 0.169588;
		*a_iter++ = -0.1486712;
		*a_iter++ = 0.1486712;
		*a_iter++ = -0.1533565;
		*a_iter++ = 0.1533565;
		*a_iter++ = -0.1601464;
		*a_iter++ = 0.1601464;
		*a_iter++ = -0.1978414;
		*a_iter++ = 0.1978414;
		*a_iter++ = -0.1746566;
		*a_iter++ = 0.1746566;
		*a_iter++ = -0.1794736;
		*a_iter++ = 0.1794736;
		*a_iter++ = -0.1896567;
		*a_iter++ = 0.1896567;
		*a_iter++ = -0.1666197;
		*a_iter++ = 0.1666197;
		*a_iter++ = -0.1969351;
		*a_iter++ = 0.1969351;
		*a_iter++ = -0.2321735;
		*a_iter++ = 0.2321735;
		*a_iter++ = -0.1592485;
		*a_iter++ = 0.1592485;
		*a_iter++ = -0.1671464;
		*a_iter++ = 0.1671464;
		*a_iter++ = -0.1688885;
		*a_iter++ = 0.1688885;
		*a_iter++ = -0.1868042;
		*a_iter++ = 0.1868042;
		*a_iter++ = -0.1301138;
		*a_iter++ = 0.1301138;
		*a_iter++ = -0.1330094;
		*a_iter++ = 0.1330094;
		*a_iter++ = -0.1268423;
		*a_iter++ = 0.1268423;
		*a_iter++ = -0.1820868;
		*a_iter++ = 0.1820868;
		*a_iter++ = -0.188102;
		*a_iter++ = 0.188102;
		*a_iter++ = -0.1580814;
		*a_iter++ = 0.1580814;
		*a_iter++ = -0.1302653;
		*a_iter++ = 0.1302653;
		*a_iter++ = -0.1787262;
		*a_iter++ = 0.1787262;
		*a_iter++ = -0.1658453;
		*a_iter++ = 0.1658453;
		*a_iter++ = -0.1240772;
		*a_iter++ = 0.1240772;
		*a_iter++ = -0.1315621;
		*a_iter++ = 0.1315621;
		*a_iter++ = -0.1756341;
		*a_iter++ = 0.1756341;
		*a_iter++ = -0.1429438;
		*a_iter++ = 0.1429438;
		*a_iter++ = -0.1351775;
		*a_iter++ = 0.1351775;
		*a_iter++ = -0.2035692;
		*a_iter++ = 0.2035692;
		*a_iter++ = -0.126767;
		*a_iter++ = 0.126767;
		*a_iter++ = -0.128847;
		*a_iter++ = 0.128847;
		*a_iter++ = -0.1393648;
		*a_iter++ = 0.1393648;
		*a_iter++ = -0.1755962;
		*a_iter++ = 0.1755962;
		*a_iter++ = -0.1308445;
		*a_iter++ = 0.1308445;
		*a_iter++ = -0.1703894;
		*a_iter++ = 0.1703894;
		*a_iter++ = -0.1461334;
		*a_iter++ = 0.1461334;
		*a_iter++ = -0.1368683;
		*a_iter++ = 0.1368683;
		*a_iter++ = -0.1244085;
		*a_iter++ = 0.1244085;
		*a_iter++ = -0.1718163;
		*a_iter++ = 0.1718163;
		*a_iter++ = -0.1415624;
		*a_iter++ = 0.1415624;
		*a_iter++ = -0.1752024;
		*a_iter++ = 0.1752024;
		*a_iter++ = -0.1666463;
		*a_iter++ = 0.1666463;
		*a_iter++ = -0.1407325;
		*a_iter++ = 0.1407325;
		*a_iter++ = -0.1258317;
		*a_iter++ = 0.1258317;
		*a_iter++ = -0.1416511;
		*a_iter++ = 0.1416511;
		*a_iter++ = -0.1420816;
		*a_iter++ = 0.1420816;
		*a_iter++ = -0.1562547;
		*a_iter++ = 0.1562547;
		*a_iter++ = -0.1542952;
		*a_iter++ = 0.1542952;
		*a_iter++ = -0.1158829;
		*a_iter++ = 0.1158829;
		*a_iter++ = -0.1392875;
		*a_iter++ = 0.1392875;
		*a_iter++ = -0.1610095;
		*a_iter++ = 0.1610095;
		*a_iter++ = -0.154644;
		*a_iter++ = 0.154644;
		*a_iter++ = -0.1416235;
		*a_iter++ = 0.1416235;
		*a_iter++ = -0.2028817;
		*a_iter++ = 0.2028817;
		*a_iter++ = -0.1106779;
		*a_iter++ = 0.1106779;
		*a_iter++ = -0.0923166;
		*a_iter++ = 0.0923166;
		*a_iter++ = -0.116446;
		*a_iter++ = 0.116446;
		*a_iter++ = -0.1701578;
		*a_iter++ = 0.1701578;
		*a_iter++ = -0.1277995;
		*a_iter++ = 0.1277995;
		*a_iter++ = -0.1946177;
		*a_iter++ = 0.1946177;
		*a_iter++ = -0.1394509;
		*a_iter++ = 0.1394509;
		*a_iter++ = -0.1370145;
		*a_iter++ = 0.1370145;
		*a_iter++ = -0.1446031;
		*a_iter++ = 0.1446031;
		*a_iter++ = -0.1665215;
		*a_iter++ = 0.1665215;
		*a_iter++ = -0.1435822;
		*a_iter++ = 0.1435822;
		*a_iter++ = -0.1559354;
		*a_iter++ = 0.1559354;
		*a_iter++ = -0.159186;
		*a_iter++ = 0.159186;
		*a_iter++ = -0.1193338;
		*a_iter++ = 0.1193338;
		*a_iter++ = -0.1236954;
		*a_iter++ = 0.1236954;
		*a_iter++ = -0.1209139;
		*a_iter++ = 0.1209139;
		*a_iter++ = -0.1267385;
		*a_iter++ = 0.1267385;
		*a_iter++ = -0.1232397;
		*a_iter++ = 0.1232397;
		*a_iter++ = -0.1299632;
		*a_iter++ = 0.1299632;
		*a_iter++ = -0.130202;
		*a_iter++ = 0.130202;
		*a_iter++ = -0.1202975;
		*a_iter++ = 0.1202975;
		*a_iter++ = -0.1525378;
		*a_iter++ = 0.1525378;
		*a_iter++ = -0.1123073;
		*a_iter++ = 0.1123073;
		*a_iter++ = -0.1605678;
		*a_iter++ = 0.1605678;
		*a_iter++ = -0.1406867;
		*a_iter++ = 0.1406867;
		*a_iter++ = -0.1354273;
		*a_iter++ = 0.1354273;
		*a_iter++ = -0.1393192;
		*a_iter++ = 0.1393192;
		*a_iter++ = -0.1278263;
		*a_iter++ = 0.1278263;
		*a_iter++ = -0.1172073;
		*a_iter++ = 0.1172073;
		*a_iter++ = -0.1153493;
		*a_iter++ = 0.1153493;
		*a_iter++ = -0.1356318;
		*a_iter++ = 0.1356318;
		*a_iter++ = -0.1316614;
		*a_iter++ = 0.1316614;
		*a_iter++ = -0.1374489;
		*a_iter++ = 0.1374489;
		*a_iter++ = -0.1018254;
		*a_iter++ = 0.1018254;
		*a_iter++ = -0.1473336;
		*a_iter++ = 0.1473336;
		*a_iter++ = -0.1289687;
		*a_iter++ = 0.1289687;
		*a_iter++ = -0.1299183;
		*a_iter++ = 0.1299183;
		*a_iter++ = -0.1178391;
		*a_iter++ = 0.1178391;
		*a_iter++ = -0.1619059;
		*a_iter++ = 0.1619059;
		*a_iter++ = -0.1842569;
		*a_iter++ = 0.1842569;
		*a_iter++ = -0.1829095;
		*a_iter++ = 0.1829095;
		*a_iter++ = -0.1939918;
		*a_iter++ = 0.1939918;
		*a_iter++ = -0.1395362;
		*a_iter++ = 0.1395362;
		*a_iter++ = -0.1774673;
		*a_iter++ = 0.1774673;
		*a_iter++ = -0.1688216;
		*a_iter++ = 0.1688216;
		*a_iter++ = -0.1671747;
		*a_iter++ = 0.1671747;
		*a_iter++ = -0.1850178;
		*a_iter++ = 0.1850178;
		*a_iter++ = -0.1106695;
		*a_iter++ = 0.1106695;
		*a_iter++ = -0.1258323;
		*a_iter++ = 0.1258323;
		*a_iter++ = -0.1246819;
		*a_iter++ = 0.1246819;
		*a_iter++ = -0.09892193;
		*a_iter++ = 0.09892193;
		*a_iter++ = -0.1399638;
		*a_iter++ = 0.1399638;
		*a_iter++ = -0.1228375;
		*a_iter++ = 0.1228375;
		*a_iter++ = -0.1756236;
		*a_iter++ = 0.1756236;
		*a_iter++ = -0.1360307;
		*a_iter++ = 0.1360307;
		*a_iter++ = -0.1266574;
		*a_iter++ = 0.1266574;
		*a_iter++ = -0.1372135;
		*a_iter++ = 0.1372135;
		*a_iter++ = -0.1175947;
		*a_iter++ = 0.1175947;
		*a_iter++ = -0.1330075;
		*a_iter++ = 0.1330075;
		*a_iter++ = -0.1396152;
		*a_iter++ = 0.1396152;
		*a_iter++ = -0.2088443;
		*a_iter++ = 0.2088443;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 301;
		sc.threshold = -4.887516;
		sc.features.SetCount(301);
		sc.alpha.SetCount(602);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 11 << 8 << 14 << 10;
			cf.py << 6 << 9 << 3 << 3 << 4;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 7 << 19 << 7 << 13;
			cf.ny << 11 << 8 << 8 << 5 << 8;
			cf.nz << 1 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 3 << 13 << 12 << 12;
			cf.py << 4 << 6 << 4 << 4 << 8;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 2 << 5 << 2 << 10 << 10;
			cf.ny << 2 << 8 << 5 << 8 << 8;
			cf.nz << 2 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 5 << 3 << 7 << 7;
			cf.py << 2 << 3 << 1 << 2 << 2;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 2 << 2 << 1 << 2 << 1;
			cf.ny << 3 << 1 << 2 << 2 << 2;
			cf.nz << 0 << 0 << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 3 << 6 << 12 << 8;
			cf.py << 4 << 2 << 4 << 10 << 17;
			cf.pz << 2 << 2 << 1 << 0 << 0;
			cf.nx << 4 << 8 << 8 << 2 << 1;
			cf.ny << 4 << 4 << 4 << 2 << 2;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 19 << 17 << 9 << 16;
			cf.py << 1 << 2 << 2 << 0 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 23 << 23 << 22 << 22 << 22;
			cf.ny << 4 << 3 << 1 << 0 << 2;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 15 << 4 << 14;
			cf.py << 23 << 4 << 18;
			cf.pz << 0 << 2 << 0;
			cf.nx << 7 << 0 << 5;
			cf.ny << 10 << 4 << 9;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 16 << 11 << 17;
			cf.py << 8 << 6 << 11 << 7 << 11;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 4 << 14 << 14 << 1;
			cf.ny << 4 << 4 << 8 << 8 << 5;
			cf.nz << 1 << 1 << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 12;
			cf.py << 13 << 10 << 11 << 12 << 12;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 4 << 1 << 2 << 9;
			cf.ny << 8 << 10 << 2 << 4 << 15;
			cf.nz << 0 << 1 << 2 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 0;
			cf.py << 14 << 17;
			cf.pz << 0 << -1;
			cf.nx << 20 << 19;
			cf.ny << 15 << 22;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 3 << 1 << 3 << 5;
			cf.py << 13 << 15 << 6 << 14 << 22;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 0 << 0 << 1 << 0 << 0;
			cf.ny << 11 << 21 << 23 << 5 << 5;
			cf.nz << 1 << 0 << 0 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 2 << 10 << 4 << 3;
			cf.py << 19 << 4 << 13 << 16 << 13;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 3 << 20 << 7 << 4 << 0;
			cf.ny << 4 << 19 << 5 << 1 << 5;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 15 << 3;
			cf.ny << 15 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 17 << 12 << 11;
			cf.py << 14 << 15 << 18 << 18;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 11 << 4 << 1 << 0;
			cf.ny << 17 << 20 << 8 << 5;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 2 << 1 << 2 << 11;
			cf.py << 14 << 4 << 1 << 1 << 18;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 5 << 5 << 3 << 5 << 2;
			cf.ny << 18 << 17 << 7 << 9 << 2;
			cf.nz << 0 << 0 << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 19 << 20 << 15 << 20;
			cf.py << 17 << 20 << 12 << 12 << 8;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 17 << 0 << 5 << 2 << 2;
			cf.ny << 8 << 4 << 9 << 2 << 2;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 8;
			cf.py << 7 << 11;
			cf.pz << 1 << -1;
			cf.nx << 7 << 8;
			cf.ny << 7 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 16 << 14 << 8 << 8;
			cf.py << 2 << 2 << 2 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 20 << 11 << 21 << 18 << 19;
			cf.ny << 3 << 6 << 5 << 1 << 2;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 18 << 9 << 8;
			cf.py << 23 << 21 << 7 << 8;
			cf.pz << 0 << 0 << 1 << 1;
			cf.nx << 8 << 17 << 10 << 18;
			cf.ny << 4 << 12 << 2 << 1;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 2 << 9 << 4 << 8;
			cf.py << 7 << 3 << 12 << 12 << 23;
			cf.pz << 1 << 1 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 3 << 1 << 2 << 4 << 4;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 8 << 5;
			cf.py << 22 << 23 << 9;
			cf.pz << 0 << 0 << 1;
			cf.nx << 9 << 4 << 2;
			cf.ny << 21 << 4 << 0;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 7 << 7;
			cf.pz << 1 << -1;
			cf.nx << 3 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 11 << 10 << 3 << 17;
			cf.py << 0 << 1 << 2 << 3 << 1;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 5 << 8 << 4 << 3 << 3;
			cf.ny << 9 << 4 << 7 << 10 << 10;
			cf.nz << 1 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 22 << 11 << 22;
			cf.py << 12 << 5 << 14;
			cf.pz << 0 << 1 << 0;
			cf.nx << 23 << 23 << 3;
			cf.ny << 22 << 23 << 8;
			cf.nz << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 11;
			cf.py << 7 << 5;
			cf.pz << 1 << -1;
			cf.nx << 8 << 2;
			cf.ny << 14 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 16 << 2 << 4;
			cf.py << 14 << 13 << 5 << 0;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 8 << 9 << 15 << 8;
			cf.ny << 8 << 9 << 14 << 7;
			cf.nz << 1 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 16;
			cf.py << 6 << 13;
			cf.pz << 1 << -1;
			cf.nx << 2 << 1;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 0 << 1 << 2 << 1;
			cf.py << 15 << 2 << 16 << 19 << 12;
			cf.pz << 0 << 2 << 0 << 0 << 0;
			cf.nx << 8 << 7 << 4 << 9 << 9;
			cf.ny << 5 << 11 << 4 << 5 << 5;
			cf.nz << 1 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 7;
			cf.py << 11 << 12;
			cf.pz << 0 << 0;
			cf.nx << 9 << 1;
			cf.ny << 10 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 13;
			cf.py << 17 << 10;
			cf.pz << 0 << -1;
			cf.nx << 7 << 4;
			cf.ny << 8 << 4;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 7 << 8 << 9;
			cf.py << 0 << 0 << 1 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 5 << 4 << 5 << 6;
			cf.ny << 1 << 0 << 2 << 1 << 0;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 4 << 3;
			cf.pz << 2 << 2;
			cf.nx << 3 << 21;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 11 << 5 << 2 << 11;
			cf.py << 12 << 10 << 6 << 11 << 11;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 15 << 16 << 7 << 7;
			cf.ny << 5 << 10 << 11 << 10 << 10;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 14 << 1 << 11 << 11;
			cf.py << 2 << 2 << 3 << 2 << 2;
			cf.pz << 0 << 0 << 2 << 0 << -1;
			cf.nx << 3 << 0 << 0 << 1 << 0;
			cf.ny << 23 << 15 << 14 << 9 << 8;
			cf.nz << 0 << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 2;
			cf.py << 13 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 4 << 1;
			cf.pz << 0 << -1;
			cf.nx << 11 << 3;
			cf.ny << 3 << 0;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 3 << 3;
			cf.pz << 2 << -1;
			cf.nx << 11 << 23;
			cf.ny << 8 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 22 << 22 << 22;
			cf.py << 16 << 18 << 9;
			cf.pz << 0 << 0 << 0;
			cf.nx << 13 << 2 << 0;
			cf.ny << 17 << 3 << 5;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 10 << 13 << 14 << 11;
			cf.py << 2 << 2 << 1 << 2 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 3 << 8 << 6 << 6;
			cf.ny << 2 << 5 << 4 << 11 << 11;
			cf.nz << 2 << 2 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 1 << 1;
			cf.py << 14 << 0 << 1;
			cf.pz << 0 << -1 << -1;
			cf.nx << 8 << 15 << 7;
			cf.ny << 1 << 2 << 0;
			cf.nz << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 20 << 23;
			cf.pz << 0 << 0;
			cf.nx << 3 << 3;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 7 << 2;
			cf.pz << 1 << -1;
			cf.nx << 4 << 3;
			cf.ny << 23 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 3 << 6;
			cf.py << 5 << 2 << 4;
			cf.pz << 2 << 2 << 1;
			cf.nx << 3 << 1 << 2;
			cf.ny << 5 << 17 << 0;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 8;
			cf.py << 17 << 6;
			cf.pz << 0 << 1;
			cf.nx << 13 << 10;
			cf.ny << 16 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 7 << 14 << 13 << 14;
			cf.py << 1 << 0 << 0 << 0 << 1;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 4 << 4 << 4 << 8 << 8;
			cf.ny << 5 << 3 << 2 << 10 << 10;
			cf.nz << 2 << 2 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 9 << 4 << 5 << 4;
			cf.py << 13 << 12 << 9 << 5 << 7;
			cf.pz << 0 << 0 << 1 << 1 << 1;
			cf.nx << 22 << 21 << 22 << 22 << 22;
			cf.ny << 4 << 0 << 3 << 2 << 2;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 17;
			cf.py << 16 << 13;
			cf.pz << 0 << 0;
			cf.nx << 14 << 21;
			cf.ny << 8 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 10;
			cf.py << 4 << 9;
			cf.pz << 0 << -1;
			cf.nx << 16 << 10;
			cf.ny << 3 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 0 << 1 << 0;
			cf.py << 17 << 16 << 7 << 15 << 8;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 3 << 8 << 9 << 7;
			cf.ny << 3 << 3 << 6 << 6 << 6;
			cf.nz << 1 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 2 << 3;
			cf.pz << 2 << 2;
			cf.nx << 8 << 3;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 2;
			cf.py << 17 << 4;
			cf.pz << 0 << 2;
			cf.nx << 10 << 12;
			cf.ny << 15 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 14 << 12;
			cf.pz << 0 << 0;
			cf.nx << 9 << 10;
			cf.ny << 13 << 11;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 5 << 5;
			cf.pz << 0 << 0;
			cf.nx << 3 << 4;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 10 << 8 << 11 << 11;
			cf.py << 13 << 2 << 12 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 10 << 1 << 1 << 10 << 1;
			cf.ny << 12 << 5 << 3 << 13 << 1;
			cf.nz << 0 << 1 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 10;
			cf.py << 4 << 2;
			cf.pz << 1 << -1;
			cf.nx << 4 << 6;
			cf.ny << 4 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 20;
			cf.py << 21 << 22;
			cf.pz << 0 << 0;
			cf.nx << 15 << 8;
			cf.ny << 5 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 3 << 3;
			cf.pz << 2 << 2;
			cf.nx << 9 << 17;
			cf.ny << 4 << 15;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 2 << 4;
			cf.py << 3 << 3 << 7;
			cf.pz << 2 << -1 << -1;
			cf.nx << 7 << 4 << 4;
			cf.ny << 6 << 5 << 4;
			cf.nz << 1 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 9 << 16 << 17 << 17;
			cf.py << 1 << 2 << 1 << 1 << 1;
			cf.pz << 1 << 1 << 0 << 0 << -1;
			cf.nx << 2 << 2 << 4 << 2 << 4;
			cf.ny << 16 << 14 << 22 << 15 << 21;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 18 << 0;
			cf.pz << 0 << -1;
			cf.nx << 2 << 5;
			cf.ny << 5 << 8;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 8;
			cf.py << 11 << 11;
			cf.pz << 0 << 0;
			cf.nx << 15 << 5;
			cf.ny << 8 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 3;
			cf.py << 4 << 3;
			cf.pz << 2 << -1;
			cf.nx << 1 << 6;
			cf.ny << 4 << 14;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 7 << 11;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 7 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 10 << 22;
			cf.pz << 1 << 0;
			cf.nx << 4 << 3;
			cf.ny << 10 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 19;
			cf.py << 4 << 21;
			cf.pz << 2 << -1;
			cf.nx << 11 << 11;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 4 << 20;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 23 << 23 << 23 << 23;
			cf.py << 7 << 13 << 19 << 20 << 21;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 3 << 2 << 8 << 8;
			cf.ny << 11 << 5 << 5 << 23 << 23;
			cf.nz << 1 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 0 << 2;
			cf.pz << 0 << 0;
			cf.nx << 0 << 6;
			cf.ny << 0 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 12 << 1;
			cf.pz << 0 << -1;
			cf.nx << 23 << 23;
			cf.ny << 13 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 11 << 23 << 11 << 11;
			cf.py << 13 << 7 << 12 << 5 << 6;
			cf.pz << 0 << 1 << 0 << 1 << 1;
			cf.nx << 6 << 3 << 8 << 7 << 7;
			cf.ny << 12 << 4 << 4 << 11 << 11;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 5;
			cf.py << 15 << 5;
			cf.pz << 0 << -1;
			cf.nx << 10 << 10;
			cf.ny << 11 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 19 << 8;
			cf.pz << 0 << 1;
			cf.nx << 11 << 19;
			cf.ny << 18 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 6;
			cf.py << 3 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 15;
			cf.ny << 1 << 0;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 14 << 5 << 13 << 12;
			cf.py << 23 << 3 << 23 << 23;
			cf.pz << 0 << 1 << 0 << 0;
			cf.nx << 12 << 0 << 1 << 4;
			cf.ny << 21 << 3 << 2 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 5;
			cf.py << 12 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 7;
			cf.ny << 3 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 8;
			cf.py << 5 << 3;
			cf.pz << 2 << -1;
			cf.nx << 5 << 22;
			cf.ny << 3 << 11;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 6;
			cf.py << 3 << 12;
			cf.pz << 2 << 0;
			cf.nx << 3 << 5;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 0 << 6;
			cf.pz << 2 << -1;
			cf.nx << 14 << 6;
			cf.ny << 4 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 11;
			cf.py << 1 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 4;
			cf.py << 4 << 3;
			cf.pz << 1 << 1;
			cf.nx << 5 << 8;
			cf.ny << 0 << 10;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 1;
			cf.py << 22 << 1;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 4 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 2;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 5 << 5;
			cf.ny << 1 << 0;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 4 << 3;
			cf.pz << 1 << 1;
			cf.nx << 7 << 5;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 22 << 3;
			cf.pz << 0 << 2;
			cf.nx << 4 << 9;
			cf.ny << 10 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 8 << 10;
			cf.pz << 1 << -1;
			cf.nx << 5 << 3;
			cf.ny << 23 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 21 << 9;
			cf.pz << 0 << -1;
			cf.nx << 11 << 23;
			cf.ny << 6 << 10;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 18 << 8;
			cf.ny << 18 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 19 << 0;
			cf.pz << 0 << -1;
			cf.nx << 6 << 5;
			cf.ny << 9 << 11;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 10 << 9 << 7 << 8;
			cf.py << 0 << 1 << 0 << 1 << 0;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 4 << 6 << 8 << 8;
			cf.ny << 2 << 4 << 9 << 4 << 4;
			cf.nz << 2 << 1 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 9 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 4;
			cf.py << 23 << 3;
			cf.pz << 0 << -1;
			cf.nx << 12 << 9;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 10 << 3;
			cf.pz << 1 << 2;
			cf.nx << 0 << 2;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 14;
			cf.py << 18 << 0;
			cf.pz << 0 << -1;
			cf.nx << 12 << 8;
			cf.ny << 16 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 18 << 7 << 5;
			cf.py << 14 << 8 << 0 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 8 << 6 << 8 << 5;
			cf.ny << 11 << 12 << 5 << 5;
			cf.nz << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 2 << 2;
			cf.pz << 1 << 1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 10;
			cf.py << 20 << 20;
			cf.pz << 0 << 0;
			cf.nx << 11 << 10;
			cf.ny << 19 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 10;
			cf.py << 16 << 20;
			cf.pz << 0 << -1;
			cf.nx << 8 << 7;
			cf.ny << 4 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 1 << 3;
			cf.py << 20 << 4 << 21;
			cf.pz << 0 << 2 << 0;
			cf.nx << 3 << 4 << 0;
			cf.ny << 10 << 1 << 0;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 7 << 3 << 6 << 6;
			cf.py << 15 << 14 << 7 << 16 << 19;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 18 << 19 << 16 << 17 << 17;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 6 << 12;
			cf.pz << 1 << 0;
			cf.nx << 8 << 15;
			cf.ny << 4 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 1 << 3 << 2 << 0 << 4;
			cf.pz << 2 << 2 << 2 << 2 << 1;
			cf.nx << 13 << 8 << 14 << 4 << 7;
			cf.ny << 23 << 6 << 23 << 3 << 9;
			cf.nz << 0 << 1 << 0 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 3 << 5;
			cf.pz << 2 << 1;
			cf.nx << 10 << 8;
			cf.ny << 11 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 8 << 5;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 18 << 9 << 16 << 4;
			cf.py << 12 << 13 << 6 << 23 << 3;
			cf.pz << 0 << 0 << 1 << 0 << 2;
			cf.nx << 6 << 3 << 6 << 2 << 7;
			cf.ny << 2 << 3 << 0 << 1 << 0;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 18;
			cf.py << 12 << 13;
			cf.pz << 0 << -1;
			cf.nx << 2 << 8;
			cf.ny << 3 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 3 << 3;
			cf.ny << 5 << 0;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 19;
			cf.py << 7 << 8;
			cf.pz << 1 << 0;
			cf.nx << 8 << 3;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 0;
			cf.py << 6 << 0;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 7 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 17 << 18;
			cf.ny << 0 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 4 << 4 << 1;
			cf.py << 14 << 7 << 3 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 3 << 16 << 3 << 7;
			cf.ny << 1 << 15 << 5 << 13;
			cf.nz << 2 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 9;
			cf.py << 6 << 11;
			cf.pz << 1 << 0;
			cf.nx << 3 << 23;
			cf.ny << 4 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 17 << 4 << 16 << 16;
			cf.py << 2 << 3 << 1 << 3 << 3;
			cf.pz << 1 << 0 << 2 << 0 << -1;
			cf.nx << 2 << 3 << 3 << 2 << 3;
			cf.ny << 1 << 7 << 2 << 3 << 3;
			cf.nz << 2 << 1 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 22 << 9;
			cf.pz << 0 << 1;
			cf.nx << 10 << 3;
			cf.ny << 21 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 6 << 3;
			cf.pz << 0 << -1;
			cf.nx << 8 << 5;
			cf.ny << 4 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 8 << 3;
			cf.pz << 0 << -1;
			cf.nx << 14 << 5;
			cf.ny << 14 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 8;
			cf.py << 3 << 2;
			cf.pz << 0 << -1;
			cf.nx << 8 << 2;
			cf.ny << 18 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 19 << 11;
			cf.pz << 0 << 1;
			cf.nx << 9 << 4;
			cf.ny << 5 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 15 << 13 << 14 << 4;
			cf.py << 6 << 12 << 9 << 11 << 4;
			cf.pz << 1 << 0 << 0 << 0 << 2;
			cf.nx << 7 << 3 << 8 << 4 << 5;
			cf.ny << 0 << 3 << 0 << 2 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 13 << 7 << 8 << 9;
			cf.py << 0 << 1 << 1 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 4 << 4 << 4 << 8;
			cf.ny << 8 << 3 << 4 << 2 << 4;
			cf.nz << 1 << 2 << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 1;
			cf.py << 6 << 0;
			cf.pz << 1 << -1;
			cf.nx << 11 << 7;
			cf.ny << 3 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 0;
			cf.py << 13 << 2;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 13 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 17;
			cf.py << 6 << 13;
			cf.pz << 1 << 0;
			cf.nx << 8 << 1;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 11 << 3 << 6 << 17;
			cf.py << 4 << 4 << 1 << 2 << 14;
			cf.pz << 0 << 0 << 2 << 1 << 0;
			cf.nx << 6 << 23 << 23 << 6 << 23;
			cf.ny << 5 << 7 << 6 << 6 << 14;
			cf.nz << 1 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 22;
			cf.py << 4 << 17;
			cf.pz << 2 << -1;
			cf.nx << 4 << 8;
			cf.ny << 5 << 7;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 14;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 4 << 7;
			cf.ny << 2 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 17;
			cf.py << 12 << 7;
			cf.pz << 0 << -1;
			cf.nx << 14 << 10;
			cf.ny << 11 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 2 << 9 << 15;
			cf.py << 5 << 11 << 1 << 13;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 11 << 3 << 3 << 13;
			cf.ny << 1 << 1 << 0 << 1;
			cf.nz << 0 << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 21;
			cf.py << 15 << 22;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 8 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 21 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 5;
			cf.ny << 11 << 21;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 7;
			cf.py << 2 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 5 << 11;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 10 << 4;
			cf.pz << 0 << -1;
			cf.nx << 13 << 12;
			cf.ny << 3 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 2 << 2;
			cf.pz << 1 << 1;
			cf.nx << 7 << 1;
			cf.ny << 8 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 1 << 0 << 0;
			cf.py << 12 << 4 << 14 << 0 << 2;
			cf.pz << 0 << 1 << 0 << 2 << 2;
			cf.nx << 9 << 5 << 8 << 4 << 4;
			cf.ny << 6 << 3 << 6 << 3 << 3;
			cf.nz << 0 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 0 << 0 << 3 << 2;
			cf.py << 6 << 5 << 0 << 8 << 2;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 23 << 7 << 22 << 11 << 4;
			cf.ny << 12 << 6 << 14 << 4 << 3;
			cf.nz << 0 << 1 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 12 << 4 << 8;
			cf.py << 12 << 11 << 3 << 10;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 0 << 0 << 0 << 0;
			cf.ny << 2 << 1 << 0 << 3;
			cf.nz << 1 << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 7 << 6;
			cf.pz << 1 << -1;
			cf.nx << 16 << 4;
			cf.ny << 12 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 1 << 3 << 3 << 3;
			cf.py << 14 << 8 << 20 << 21 << 21;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 20 << 10 << 21 << 21 << 21;
			cf.ny << 23 << 11 << 21 << 23 << 20;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 13;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 7 << 21;
			cf.ny << 8 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 3;
			cf.py << 17 << 4;
			cf.pz << 0 << 2;
			cf.nx << 11 << 10;
			cf.ny << 15 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 0 << 19 << 2;
			cf.py << 15 << 2 << 23 << 10;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 6 << 8 << 16 << 2;
			cf.ny << 13 << 11 << 10 << 2;
			cf.nz << 0 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 14 << 7;
			cf.pz << 0 << 1;
			cf.nx << 3 << 1;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 17 << 5 << 10;
			cf.py << 19 << 15 << 14 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 4 << 12 << 6 << 12;
			cf.ny << 4 << 18 << 9 << 22;
			cf.nz << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 13 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 5 << 4 << 5 << 3;
			cf.py << 2 << 1 << 2 << 2 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 7 << 4 << 9 << 18 << 18;
			cf.ny << 4 << 4 << 7 << 14 << 14;
			cf.nz << 1 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 3 << 20 << 1;
			cf.py << 6 << 3 << 18 << 0;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 13 << 11 << 5 << 22;
			cf.ny << 12 << 6 << 2 << 17;
			cf.nz << 0 << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 8 << 5;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 7;
			cf.py << 14 << 7;
			cf.pz << 0 << 1;
			cf.nx << 16 << 11;
			cf.ny << 14 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 3 << 1;
			cf.pz << 0 << -1;
			cf.nx << 9 << 5;
			cf.ny << 0 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 10;
			cf.py << 5 << 8;
			cf.pz << 2 << 1;
			cf.nx << 5 << 14;
			cf.ny << 9 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 23 << 4;
			cf.pz << 0 << 2;
			cf.nx << 2 << 2;
			cf.ny << 5 << 5;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 9 << 11 << 10 << 10;
			cf.py << 2 << 2 << 1 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 2 << 3 << 2 << 4 << 5;
			cf.ny << 4 << 10 << 2 << 4 << 3;
			cf.nz << 2 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 5;
			cf.py << 15 << 1;
			cf.pz << 0 << -1;
			cf.nx << 20 << 19;
			cf.ny << 14 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 20 << 18;
			cf.pz << 0 << 0;
			cf.nx << 2 << 1;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 18 << 3;
			cf.pz << 0 << 2;
			cf.nx << 11 << 3;
			cf.ny << 16 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 8;
			cf.py << 6 << 10;
			cf.pz << 1 << 0;
			cf.nx << 9 << 0;
			cf.ny << 9 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 10;
			cf.py << 21 << 7;
			cf.pz << 0 << 1;
			cf.nx << 7 << 2;
			cf.ny << 3 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 4 << 7;
			cf.pz << 1 << -1;
			cf.nx << 23 << 5;
			cf.ny << 9 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 4 << 5 << 3 << 4;
			cf.py << 0 << 1 << 1 << 2 << 2;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 1 << 0 << 1 << 1 << 1;
			cf.ny << 2 << 1 << 0 << 1 << 1;
			cf.nz << 0 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 8 << 3;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 15;
			cf.py << 7 << 19;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 11 << 5;
			cf.pz << 1 << 2;
			cf.nx << 7 << 8;
			cf.ny << 9 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 11;
			cf.py << 9 << 6;
			cf.pz << 0 << 1;
			cf.nx << 22 << 22;
			cf.ny << 23 << 23;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 23;
			cf.py << 21 << 20;
			cf.pz << 0 << 0;
			cf.nx << 2 << 2;
			cf.ny << 5 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 4;
			cf.py << 12 << 2;
			cf.pz << 0 << -1;
			cf.nx << 9 << 8;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 14;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 7 << 18;
			cf.ny << 1 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 22;
			cf.py << 1 << 2;
			cf.pz << 0 << 0;
			cf.nx << 23 << 23;
			cf.ny << 1 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 9 << 10;
			cf.pz << 1 << 1;
			cf.nx << 8 << 0;
			cf.ny << 15 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 11 << 6;
			cf.py << 10 << 11 << 11;
			cf.pz << 0 << 0 << -1;
			cf.nx << 23 << 23 << 23;
			cf.ny << 19 << 21 << 20;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 23 << 23 << 6 << 6;
			cf.py << 21 << 22 << 22 << 3 << 6;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 8 << 8 << 8 << 17 << 4;
			cf.ny << 7 << 10 << 8 << 16 << 5;
			cf.nz << 1 << 1 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 23;
			cf.py << 1 << 22;
			cf.pz << 0 << -1;
			cf.nx << 7 << 2;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 14;
			cf.py << 3 << 10;
			cf.pz << 1 << -1;
			cf.nx << 5 << 3;
			cf.ny << 2 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 13 << 7;
			cf.pz << 0 << 1;
			cf.nx << 4 << 10;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 15 << 6;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 18 << 17;
			cf.pz << 0 << -1;
			cf.nx << 7 << 6;
			cf.ny << 10 << 7;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 11;
			cf.py << 3 << 8;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 4;
			cf.py << 5 << 7;
			cf.pz << 0 << 1;
			cf.nx << 17 << 10;
			cf.ny << 4 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 8 << 16 << 15 << 15;
			cf.py << 0 << 0 << 1 << 0 << 1;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 7 << 4 << 7 << 4 << 4;
			cf.ny << 7 << 5 << 8 << 1 << 1;
			cf.nz << 1 << 2 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 11;
			cf.py << 5 << 6;
			cf.pz << 0 << -1;
			cf.nx << 4 << 5;
			cf.ny << 2 << 2;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 16;
			cf.py << 8 << 10;
			cf.pz << 0 << 0;
			cf.nx << 7 << 2;
			cf.ny << 3 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 8;
			cf.py << 4 << 11;
			cf.pz << 1 << 0;
			cf.nx << 10 << 1;
			cf.ny << 9 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 1;
			cf.py << 4 << 2;
			cf.pz << 2 << -1;
			cf.nx << 23 << 23;
			cf.ny << 15 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 8 << 2 << 4 << 9;
			cf.py << 1 << 1 << 0 << 1 << 2;
			cf.pz << 0 << 0 << 2 << 1 << 0;
			cf.nx << 8 << 3 << 8 << 4 << 4;
			cf.ny << 6 << 2 << 4 << 2 << 2;
			cf.nz << 1 << 2 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 6;
			cf.py << 10 << 5;
			cf.pz << 0 << -1;
			cf.nx << 13 << 7;
			cf.ny << 6 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 10 << 5;
			cf.pz << 1 << 2;
			cf.nx << 10 << 8;
			cf.ny << 10 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 9 << 14;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 2 << 15;
			cf.py << 3 << 1 << 22;
			cf.pz << 1 << -1 << -1;
			cf.nx << 15 << 9 << 4;
			cf.ny << 0 << 1 << 0;
			cf.nz << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 19;
			cf.py << 9 << 21;
			cf.pz << 1 << 0;
			cf.nx << 2 << 17;
			cf.ny << 5 << 14;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 2 << 1;
			cf.py << 2 << 10 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 4 << 9;
			cf.ny << 3 << 2 << 6;
			cf.nz << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 2;
			cf.py << 6 << 10;
			cf.pz << 1 << -1;
			cf.nx << 21 << 22;
			cf.ny << 16 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 16;
			cf.py << 4 << 23;
			cf.pz << 0 << -1;
			cf.nx << 7 << 3;
			cf.ny << 3 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 13 << 14;
			cf.pz << 0 << 0;
			cf.nx << 1 << 2;
			cf.ny << 18 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 5;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 13;
			cf.ny << 2 << 11;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 17;
			cf.py << 3 << 3;
			cf.pz << 0 << 0;
			cf.nx << 19 << 19;
			cf.ny << 1 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 0 << 5;
			cf.pz << 1 << -1;
			cf.nx << 12 << 3;
			cf.ny << 5 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 18 << 4;
			cf.ny << 4 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 13 << 2 << 10 << 15;
			cf.py << 11 << 12 << 13 << 17 << 23;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 12 << 13 << 4 << 3 << 8;
			cf.ny << 4 << 4 << 1 << 0 << 3;
			cf.nz << 0 << 0 << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 2 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 7 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 5 << 1;
			cf.pz << 0 << -1;
			cf.nx << 18 << 4;
			cf.ny << 12 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 4;
			cf.py << 11 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 7;
			cf.ny << 2 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 2;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 0;
			cf.py << 7 << 7;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 0 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 9;
			cf.py << 0 << 2;
			cf.pz << 2 << 1;
			cf.nx << 6 << 4;
			cf.ny << 3 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 9 << 4;
			cf.pz << 1 << 2;
			cf.nx << 13 << 5;
			cf.ny << 18 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 23 << 23;
			cf.py << 2 << 8 << 7;
			cf.pz << 2 << 0 << 0;
			cf.nx << 10 << 12 << 1;
			cf.ny << 4 << 1 << 0;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 0;
			cf.py << 3 << 3;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 10 << 5;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 4 << 11;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 2;
			cf.py << 14 << 11;
			cf.pz << 0 << -1;
			cf.nx << 10 << 11;
			cf.ny << 4 << 13;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 21 << 23;
			cf.pz << 0 << 0;
			cf.nx << 7 << 0;
			cf.ny << 21 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 8 << 5;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 8 << 8;
			cf.pz << 0 << 0;
			cf.nx << 6 << 14;
			cf.ny << 9 << 15;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 6;
			cf.py << 4 << 8;
			cf.pz << 0 << -1;
			cf.nx << 16 << 8;
			cf.ny << 0 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 6 << 0 << 9;
			cf.py << 0 << 8 << 5 << 23;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 12 << 2 << 6 << 10;
			cf.ny << 5 << 0 << 3 << 5;
			cf.nz << 0 << 2 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 3 << 9;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 5;
			cf.py << 8 << 23;
			cf.pz << 1 << 0;
			cf.nx << 8 << 9;
			cf.ny << 15 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 18;
			cf.py << 8 << 0;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 9 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 4 << 21;
			cf.pz << 2 << 0;
			cf.nx << 13 << 11;
			cf.ny << 8 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 8 << 8;
			cf.pz << 0 << 0;
			cf.nx << 6 << 1;
			cf.ny << 8 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 20 << 7;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 10 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 8 << 7;
			cf.pz << 1 << -1;
			cf.nx << 1 << 2;
			cf.ny << 4 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 10;
			cf.py << 5 << 13;
			cf.pz << 1 << -1;
			cf.nx << 3 << 6;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 6 << 3;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 4 << 4;
			cf.pz << 1 << -1;
			cf.nx << 5 << 11;
			cf.ny << 2 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 23 << 11 << 23 << 11;
			cf.py << 4 << 9 << 5 << 10 << 6;
			cf.pz << 1 << 0 << 1 << 0 << 1;
			cf.nx << 7 << 14 << 13 << 7 << 3;
			cf.ny << 9 << 5 << 6 << 4 << 4;
			cf.nz << 0 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 5;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 9 << 20;
			cf.ny << 1 << 4;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 20;
			cf.py << 0 << 3;
			cf.pz << 0 << 0;
			cf.nx << 4 << 6;
			cf.ny << 11 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 5 << 20 << 5;
			cf.py << 14 << 3 << 23 << 4;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 8 << 15 << 7 << 16;
			cf.ny << 8 << 14 << 6 << 15;
			cf.nz << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 20;
			cf.py << 5 << 17;
			cf.pz << 0 << -1;
			cf.nx << 7 << 3;
			cf.ny << 10 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 12 << 7;
			cf.py << 3 << 7 << 10;
			cf.pz << 2 << 0 << 0;
			cf.nx << 2 << 2 << 3;
			cf.ny << 3 << 2 << 2;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 5 << 7;
			cf.py << 7 << 10 << 10;
			cf.pz << 1 << -1 << -1;
			cf.nx << 10 << 10 << 18;
			cf.ny << 10 << 9 << 23;
			cf.nz << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 14 << 4;
			cf.py << 3 << 3 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 4 << 8;
			cf.ny << 3 << 2 << 6;
			cf.nz << 2 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 12;
			cf.py << 4 << 17;
			cf.pz << 2 << 0;
			cf.nx << 13 << 1;
			cf.ny << 15 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 20;
			cf.py << 9 << 22;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 2 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 2;
			cf.py << 3 << 6;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 15 << 10 << 1;
			cf.py << 12 << 2 << 3;
			cf.pz << 0 << -1 << -1;
			cf.nx << 7 << 5 << 10;
			cf.ny << 2 << 1 << 1;
			cf.nz << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 11 << 10 << 12 << 12;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 8 << 4 << 16 << 5 << 10;
			cf.ny << 4 << 4 << 10 << 3 << 6;
			cf.nz << 1 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 10;
			cf.py << 3 << 5;
			cf.pz << 2 << -1;
			cf.nx << 3 << 6;
			cf.ny << 0 << 1;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 8 << 7 << 2 << 12;
			cf.py << 14 << 13 << 13 << 16 << 0;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 10 << 1 << 10 << 1 << 1;
			cf.ny << 13 << 2 << 12 << 4 << 9;
			cf.nz << 0 << 2 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 14 << 13;
			cf.py << 1 << 2 << 1;
			cf.pz << 1 << 0 << 0;
			cf.nx << 8 << 21 << 10;
			cf.ny << 4 << 23 << 12;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 19;
			cf.py << 22 << 21;
			cf.pz << 0 << 0;
			cf.nx << 20 << 1;
			cf.ny << 22 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 12;
			cf.py << 19 << 22;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 0 << 1;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 9 << 21 << 4;
			cf.py << 13 << 3 << 19 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 9 << 9 << 9 << 5;
			cf.ny << 13 << 14 << 12 << 6;
			cf.nz << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 12 << 13 << 14;
			cf.py << 22 << 22 << 22 << 22;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 13 << 2 << 4 << 5;
			cf.ny << 20 << 0 << 0 << 6;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 1;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 0 << 1;
			cf.pz << 2 << 2;
			cf.nx << 9 << 4;
			cf.ny << 6 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 0;
			cf.py << 10 << 1;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 3 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 3 << 1;
			cf.pz << 1 << 2;
			cf.nx << 12 << 18;
			cf.ny << 17 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 3 << 4;
			cf.py << 4 << 3 << 9;
			cf.pz << 2 << 2 << 1;
			cf.nx << 0 << 3 << 17;
			cf.ny << 0 << 1 << 18;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 5 << 1;
			cf.ny << 11 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 17;
			cf.py << 20 << 6;
			cf.pz << 0 << -1;
			cf.nx << 5 << 2;
			cf.ny << 9 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 11;
			cf.py << 18 << 2;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 9 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 15;
			cf.py << 2 << 2;
			cf.pz << 0 << 0;
			cf.nx << 17 << 12;
			cf.ny << 2 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 4;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 7 << 5;
			cf.ny << 23 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 23 << 23;
			cf.pz << 0 << 0;
			cf.nx << 7 << 11;
			cf.ny << 10 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 10;
			cf.py << 3 << 18;
			cf.pz << 2 << -1;
			cf.nx << 9 << 9;
			cf.ny << 5 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 10;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 4 << 23;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 8 << 1;
			cf.pz << 1 << -1;
			cf.nx << 15 << 12;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 3 << 10;
			cf.pz << 2 << 1;
			cf.nx << 10 << 1;
			cf.ny << 20 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 10 << 11;
			cf.pz << 0 << 0;
			cf.nx << 22 << 3;
			cf.ny << 5 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 17 << 17 << 9 << 18;
			cf.py << 0 << 1 << 0 << 1 << 0;
			cf.pz << 1 << 0 << 0 << 1 << 0;
			cf.nx << 11 << 8 << 9 << 4 << 4;
			cf.ny << 23 << 4 << 6 << 2 << 2;
			cf.nz << 0 << 1 << 0 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 4 << 4;
			cf.pz << 1 << -1;
			cf.nx << 13 << 4;
			cf.ny << 9 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 4 << 8 << 7 << 7;
			cf.py << 3 << 1 << 3 << 3 << 3;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 4 << 2 << 5 << 3 << 2;
			cf.ny << 1 << 15 << 1 << 4 << 13;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 7;
			cf.py << 13 << 7;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 2;
			cf.py << 1 << 12;
			cf.pz << 2 << 0;
			cf.nx << 9 << 21;
			cf.ny << 5 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 0;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 19 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 1;
			cf.py << 5 << 9;
			cf.pz << 0 << -1;
			cf.nx << 16 << 15;
			cf.ny << 3 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 6;
			cf.py << 17 << 15;
			cf.pz << 0 << 0;
			cf.nx << 11 << 0;
			cf.ny << 16 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 11 << 0 << 3;
			cf.py << 16 << 8 << 7 << 1;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 10 << 5 << 10 << 5;
			cf.ny << 11 << 9 << 10 << 8;
			cf.nz << 0 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 4 << 14;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 17;
			cf.py << 6 << 13;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 11;
			cf.py << 3 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 15;
			cf.ny << 1 << 2;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 11;
			cf.py << 18 << 4;
			cf.pz << 0 << -1;
			cf.nx << 5 << 5;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 7 << 4;
			cf.pz << 1 << 2;
			cf.nx << 4 << 3;
			cf.ny << 5 << 7;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 4;
			cf.py << 15 << 4;
			cf.pz << 0 << -1;
			cf.nx << 11 << 8;
			cf.ny << 14 << 19;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 13;
			cf.py << 13 << 20;
			cf.pz << 0 << 0;
			cf.nx << 13 << 4;
			cf.ny << 18 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 4;
			cf.py << 6 << 3;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 5 << 11 << 5 << 10;
			cf.py << 1 << 1 << 3 << 0 << 0;
			cf.pz << 0 << 2 << 1 << 2 << 1;
			cf.nx << 7 << 14 << 15 << 4 << 8;
			cf.ny << 3 << 6 << 11 << 3 << 4;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 15 << 10;
			cf.pz << 0 << -1;
			cf.nx << 21 << 22;
			cf.ny << 14 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 0;
			cf.py << 20 << 0;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 6 << 13 << 11 << 7;
			cf.py << 1 << 1 << 1 << 2 << 1;
			cf.pz << 0 << 1 << 0 << 0 << 1;
			cf.nx << 7 << 6 << 8 << 5 << 5;
			cf.ny << 4 << 15 << 4 << 16 << 16;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 22 << 21 << 21;
			cf.py << 14 << 15 << 17;
			cf.pz << 0 << 0 << 0;
			cf.nx << 5 << 9 << 4;
			cf.ny << 0 << 5 << 0;
			cf.nz << 2 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 2;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 23 << 11;
			cf.ny << 16 << 8;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 21 << 21 << 0 << 18;
			cf.py << 14 << 15 << 5 << 4;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 8 << 8 << 9 << 4;
			cf.ny << 7 << 8 << 10 << 5;
			cf.nz << 1 << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 5;
			cf.py << 18 << 1;
			cf.pz << 0 << -1;
			cf.nx << 23 << 23;
			cf.ny << 16 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 14;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 4 << 4;
			cf.ny << 2 << 3;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 6;
			cf.py << 6 << 5;
			cf.pz << 1 << -1;
			cf.nx << 14 << 11;
			cf.ny << 1 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 17;
			cf.py << 2 << 8;
			cf.pz << 2 << 0;
			cf.nx << 8 << 3;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 8;
			cf.py << 13 << 10;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 8 << 3;
			cf.pz << 0 << 1;
			cf.nx << 1 << 11;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 8;
			cf.py << 5 << 0;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 3 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 3;
			cf.pz << 1 << 2;
			cf.nx << 1 << 18;
			cf.ny << 5 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 6 << 6;
			cf.pz << 0 << 1;
			cf.nx << 7 << 12;
			cf.ny << 5 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 1;
			cf.py << 0 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 9 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 10 << 11;
			cf.pz << 0 << 0;
			cf.nx << 0 << 5;
			cf.ny << 5 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 1;
			cf.py << 23 << 4;
			cf.pz << 0 << 2;
			cf.nx << 0 << 0;
			cf.ny << 13 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 6 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 4 << 5;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 6 << 5;
			cf.pz << 1 << 1;
			cf.nx << 3 << 9;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 9 << 13;
			cf.pz << 0 << -1;
			cf.nx << 4 << 10;
			cf.ny << 3 << 7;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 9 << 6 << 10 << 10;
			cf.py << 2 << 2 << 1 << 2 << 2;
			cf.pz << 0 << 0 << 1 << 0 << -1;
			cf.nx << 7 << 5 << 6 << 5 << 6;
			cf.ny << 0 << 2 << 2 << 1 << 1;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		*a_iter++ = -1.119615;
		*a_iter++ = 1.119615;
		*a_iter++ = -0.8169953;
		*a_iter++ = 0.8169953;
		*a_iter++ = -0.5291213;
		*a_iter++ = 0.5291213;
		*a_iter++ = -0.4904488;
		*a_iter++ = 0.4904488;
		*a_iter++ = -0.4930982;
		*a_iter++ = 0.4930982;
		*a_iter++ = -0.4106179;
		*a_iter++ = 0.4106179;
		*a_iter++ = -0.4246842;
		*a_iter++ = 0.4246842;
		*a_iter++ = -0.3802383;
		*a_iter++ = 0.3802383;
		*a_iter++ = -0.3364358;
		*a_iter++ = 0.3364358;
		*a_iter++ = -0.3214186;
		*a_iter++ = 0.3214186;
		*a_iter++ = -0.3210798;
		*a_iter++ = 0.3210798;
		*a_iter++ = -0.2993167;
		*a_iter++ = 0.2993167;
		*a_iter++ = -0.3426336;
		*a_iter++ = 0.3426336;
		*a_iter++ = -0.3199184;
		*a_iter++ = 0.3199184;
		*a_iter++ = -0.3061071;
		*a_iter++ = 0.3061071;
		*a_iter++ = -0.2758972;
		*a_iter++ = 0.2758972;
		*a_iter++ = -0.307559;
		*a_iter++ = 0.307559;
		*a_iter++ = -0.3009565;
		*a_iter++ = 0.3009565;
		*a_iter++ = -0.2015739;
		*a_iter++ = 0.2015739;
		*a_iter++ = -0.2603266;
		*a_iter++ = 0.2603266;
		*a_iter++ = -0.2772993;
		*a_iter++ = 0.2772993;
		*a_iter++ = -0.2184913;
		*a_iter++ = 0.2184913;
		*a_iter++ = -0.2306681;
		*a_iter++ = 0.2306681;
		*a_iter++ = -0.1983223;
		*a_iter++ = 0.1983223;
		*a_iter++ = -0.219476;
		*a_iter++ = 0.219476;
		*a_iter++ = -0.2528421;
		*a_iter++ = 0.2528421;
		*a_iter++ = -0.2436416;
		*a_iter++ = 0.2436416;
		*a_iter++ = -0.3032886;
		*a_iter++ = 0.3032886;
		*a_iter++ = -0.2556071;
		*a_iter++ = 0.2556071;
		*a_iter++ = -0.256217;
		*a_iter++ = 0.256217;
		*a_iter++ = -0.1930298;
		*a_iter++ = 0.1930298;
		*a_iter++ = -0.2735898;
		*a_iter++ = 0.2735898;
		*a_iter++ = -0.1814703;
		*a_iter++ = 0.1814703;
		*a_iter++ = -0.2054824;
		*a_iter++ = 0.2054824;
		*a_iter++ = -0.1986146;
		*a_iter++ = 0.1986146;
		*a_iter++ = -0.1769226;
		*a_iter++ = 0.1769226;
		*a_iter++ = -0.1775257;
		*a_iter++ = 0.1775257;
		*a_iter++ = -0.2167927;
		*a_iter++ = 0.2167927;
		*a_iter++ = -0.1823633;
		*a_iter++ = 0.1823633;
		*a_iter++ = -0.158428;
		*a_iter++ = 0.158428;
		*a_iter++ = -0.1778321;
		*a_iter++ = 0.1778321;
		*a_iter++ = -0.1826777;
		*a_iter++ = 0.1826777;
		*a_iter++ = -0.1979903;
		*a_iter++ = 0.1979903;
		*a_iter++ = -0.1898326;
		*a_iter++ = 0.1898326;
		*a_iter++ = -0.1835506;
		*a_iter++ = 0.1835506;
		*a_iter++ = -0.196786;
		*a_iter++ = 0.196786;
		*a_iter++ = -0.1871528;
		*a_iter++ = 0.1871528;
		*a_iter++ = -0.1772414;
		*a_iter++ = 0.1772414;
		*a_iter++ = -0.1985514;
		*a_iter++ = 0.1985514;
		*a_iter++ = -0.2144078;
		*a_iter++ = 0.2144078;
		*a_iter++ = -0.2742303;
		*a_iter++ = 0.2742303;
		*a_iter++ = -0.224055;
		*a_iter++ = 0.224055;
		*a_iter++ = -0.2132534;
		*a_iter++ = 0.2132534;
		*a_iter++ = -0.1552127;
		*a_iter++ = 0.1552127;
		*a_iter++ = -0.1568276;
		*a_iter++ = 0.1568276;
		*a_iter++ = -0.1630086;
		*a_iter++ = 0.1630086;
		*a_iter++ = -0.1458232;
		*a_iter++ = 0.1458232;
		*a_iter++ = -0.1559541;
		*a_iter++ = 0.1559541;
		*a_iter++ = -0.1720131;
		*a_iter++ = 0.1720131;
		*a_iter++ = -0.1708434;
		*a_iter++ = 0.1708434;
		*a_iter++ = -0.1624431;
		*a_iter++ = 0.1624431;
		*a_iter++ = -0.1814161;
		*a_iter++ = 0.1814161;
		*a_iter++ = -0.1552639;
		*a_iter++ = 0.1552639;
		*a_iter++ = -0.1242354;
		*a_iter++ = 0.1242354;
		*a_iter++ = -0.1552139;
		*a_iter++ = 0.1552139;
		*a_iter++ = -0.1694359;
		*a_iter++ = 0.1694359;
		*a_iter++ = -0.1801481;
		*a_iter++ = 0.1801481;
		*a_iter++ = -0.1387182;
		*a_iter++ = 0.1387182;
		*a_iter++ = -0.1409679;
		*a_iter++ = 0.1409679;
		*a_iter++ = -0.1486724;
		*a_iter++ = 0.1486724;
		*a_iter++ = -0.1779553;
		*a_iter++ = 0.1779553;
		*a_iter++ = -0.1524595;
		*a_iter++ = 0.1524595;
		*a_iter++ = -0.1788086;
		*a_iter++ = 0.1788086;
		*a_iter++ = -0.1671479;
		*a_iter++ = 0.1671479;
		*a_iter++ = -0.1376197;
		*a_iter++ = 0.1376197;
		*a_iter++ = -0.1511808;
		*a_iter++ = 0.1511808;
		*a_iter++ = -0.1524632;
		*a_iter++ = 0.1524632;
		*a_iter++ = -0.1198986;
		*a_iter++ = 0.1198986;
		*a_iter++ = -0.1382641;
		*a_iter++ = 0.1382641;
		*a_iter++ = -0.1148901;
		*a_iter++ = 0.1148901;
		*a_iter++ = -0.1131803;
		*a_iter++ = 0.1131803;
		*a_iter++ = -0.1273508;
		*a_iter++ = 0.1273508;
		*a_iter++ = -0.1405125;
		*a_iter++ = 0.1405125;
		*a_iter++ = -0.1322132;
		*a_iter++ = 0.1322132;
		*a_iter++ = -0.1386966;
		*a_iter++ = 0.1386966;
		*a_iter++ = -0.1275621;
		*a_iter++ = 0.1275621;
		*a_iter++ = -0.1180573;
		*a_iter++ = 0.1180573;
		*a_iter++ = -0.1238803;
		*a_iter++ = 0.1238803;
		*a_iter++ = -0.1428389;
		*a_iter++ = 0.1428389;
		*a_iter++ = -0.1694437;
		*a_iter++ = 0.1694437;
		*a_iter++ = -0.1290855;
		*a_iter++ = 0.1290855;
		*a_iter++ = -0.152026;
		*a_iter++ = 0.152026;
		*a_iter++ = -0.1398282;
		*a_iter++ = 0.1398282;
		*a_iter++ = -0.1890736;
		*a_iter++ = 0.1890736;
		*a_iter++ = -0.2280428;
		*a_iter++ = 0.2280428;
		*a_iter++ = -0.1325099;
		*a_iter++ = 0.1325099;
		*a_iter++ = -0.1342873;
		*a_iter++ = 0.1342873;
		*a_iter++ = -0.1463841;
		*a_iter++ = 0.1463841;
		*a_iter++ = -0.1983567;
		*a_iter++ = 0.1983567;
		*a_iter++ = -0.1585711;
		*a_iter++ = 0.1585711;
		*a_iter++ = -0.1260154;
		*a_iter++ = 0.1260154;
		*a_iter++ = -0.1426774;
		*a_iter++ = 0.1426774;
		*a_iter++ = -0.1554278;
		*a_iter++ = 0.1554278;
		*a_iter++ = -0.1361201;
		*a_iter++ = 0.1361201;
		*a_iter++ = -0.1181856;
		*a_iter++ = 0.1181856;
		*a_iter++ = -0.1255941;
		*a_iter++ = 0.1255941;
		*a_iter++ = -0.1113275;
		*a_iter++ = 0.1113275;
		*a_iter++ = -0.1506576;
		*a_iter++ = 0.1506576;
		*a_iter++ = -0.1202859;
		*a_iter++ = 0.1202859;
		*a_iter++ = -0.2159751;
		*a_iter++ = 0.2159751;
		*a_iter++ = -0.144315;
		*a_iter++ = 0.144315;
		*a_iter++ = -0.1379194;
		*a_iter++ = 0.1379194;
		*a_iter++ = -0.1805758;
		*a_iter++ = 0.1805758;
		*a_iter++ = -0.1465612;
		*a_iter++ = 0.1465612;
		*a_iter++ = -0.1328856;
		*a_iter++ = 0.1328856;
		*a_iter++ = -0.1532173;
		*a_iter++ = 0.1532173;
		*a_iter++ = -0.1590635;
		*a_iter++ = 0.1590635;
		*a_iter++ = -0.1462229;
		*a_iter++ = 0.1462229;
		*a_iter++ = -0.1350012;
		*a_iter++ = 0.1350012;
		*a_iter++ = -0.1195634;
		*a_iter++ = 0.1195634;
		*a_iter++ = -0.1173221;
		*a_iter++ = 0.1173221;
		*a_iter++ = -0.1192867;
		*a_iter++ = 0.1192867;
		*a_iter++ = -0.1595013;
		*a_iter++ = 0.1595013;
		*a_iter++ = -0.1209751;
		*a_iter++ = 0.1209751;
		*a_iter++ = -0.157129;
		*a_iter++ = 0.157129;
		*a_iter++ = -0.1527274;
		*a_iter++ = 0.1527274;
		*a_iter++ = -0.1373708;
		*a_iter++ = 0.1373708;
		*a_iter++ = -0.1318313;
		*a_iter++ = 0.1318313;
		*a_iter++ = -0.1273391;
		*a_iter++ = 0.1273391;
		*a_iter++ = -0.1271365;
		*a_iter++ = 0.1271365;
		*a_iter++ = -0.1528693;
		*a_iter++ = 0.1528693;
		*a_iter++ = -0.1590476;
		*a_iter++ = 0.1590476;
		*a_iter++ = -0.1581911;
		*a_iter++ = 0.1581911;
		*a_iter++ = -0.1183023;
		*a_iter++ = 0.1183023;
		*a_iter++ = -0.1559822;
		*a_iter++ = 0.1559822;
		*a_iter++ = -0.1214999;
		*a_iter++ = 0.1214999;
		*a_iter++ = -0.1283378;
		*a_iter++ = 0.1283378;
		*a_iter++ = -0.1542583;
		*a_iter++ = 0.1542583;
		*a_iter++ = -0.1336377;
		*a_iter++ = 0.1336377;
		*a_iter++ = -0.1800416;
		*a_iter++ = 0.1800416;
		*a_iter++ = -0.1710931;
		*a_iter++ = 0.1710931;
		*a_iter++ = -0.1621737;
		*a_iter++ = 0.1621737;
		*a_iter++ = -0.1239002;
		*a_iter++ = 0.1239002;
		*a_iter++ = -0.1432928;
		*a_iter++ = 0.1432928;
		*a_iter++ = -0.1392447;
		*a_iter++ = 0.1392447;
		*a_iter++ = -0.1383938;
		*a_iter++ = 0.1383938;
		*a_iter++ = -0.1357633;
		*a_iter++ = 0.1357633;
		*a_iter++ = -0.1175842;
		*a_iter++ = 0.1175842;
		*a_iter++ = -0.1085318;
		*a_iter++ = 0.1085318;
		*a_iter++ = -0.1148885;
		*a_iter++ = 0.1148885;
		*a_iter++ = -0.1320396;
		*a_iter++ = 0.1320396;
		*a_iter++ = -0.1351204;
		*a_iter++ = 0.1351204;
		*a_iter++ = -0.1581518;
		*a_iter++ = 0.1581518;
		*a_iter++ = -0.1459574;
		*a_iter++ = 0.1459574;
		*a_iter++ = -0.1180068;
		*a_iter++ = 0.1180068;
		*a_iter++ = -0.1464196;
		*a_iter++ = 0.1464196;
		*a_iter++ = -0.1179543;
		*a_iter++ = 0.1179543;
		*a_iter++ = -0.1004204;
		*a_iter++ = 0.1004204;
		*a_iter++ = -0.129466;
		*a_iter++ = 0.129466;
		*a_iter++ = -0.1534244;
		*a_iter++ = 0.1534244;
		*a_iter++ = -0.137897;
		*a_iter++ = 0.137897;
		*a_iter++ = -0.1226545;
		*a_iter++ = 0.1226545;
		*a_iter++ = -0.1281182;
		*a_iter++ = 0.1281182;
		*a_iter++ = -0.1201471;
		*a_iter++ = 0.1201471;
		*a_iter++ = -0.1448701;
		*a_iter++ = 0.1448701;
		*a_iter++ = -0.129098;
		*a_iter++ = 0.129098;
		*a_iter++ = -0.1388764;
		*a_iter++ = 0.1388764;
		*a_iter++ = -0.09605773;
		*a_iter++ = 0.09605773;
		*a_iter++ = -0.1411021;
		*a_iter++ = 0.1411021;
		*a_iter++ = -0.1295693;
		*a_iter++ = 0.1295693;
		*a_iter++ = -0.1371739;
		*a_iter++ = 0.1371739;
		*a_iter++ = -0.1167579;
		*a_iter++ = 0.1167579;
		*a_iter++ = -0.1400486;
		*a_iter++ = 0.1400486;
		*a_iter++ = -0.1214224;
		*a_iter++ = 0.1214224;
		*a_iter++ = -0.1287835;
		*a_iter++ = 0.1287835;
		*a_iter++ = -0.1197646;
		*a_iter++ = 0.1197646;
		*a_iter++ = -0.1192358;
		*a_iter++ = 0.1192358;
		*a_iter++ = -0.1218651;
		*a_iter++ = 0.1218651;
		*a_iter++ = -0.1564816;
		*a_iter++ = 0.1564816;
		*a_iter++ = -0.1172391;
		*a_iter++ = 0.1172391;
		*a_iter++ = -0.1342268;
		*a_iter++ = 0.1342268;
		*a_iter++ = -0.1492471;
		*a_iter++ = 0.1492471;
		*a_iter++ = -0.1157299;
		*a_iter++ = 0.1157299;
		*a_iter++ = -0.1046703;
		*a_iter++ = 0.1046703;
		*a_iter++ = -0.1255571;
		*a_iter++ = 0.1255571;
		*a_iter++ = -0.1100135;
		*a_iter++ = 0.1100135;
		*a_iter++ = -0.1501592;
		*a_iter++ = 0.1501592;
		*a_iter++ = -0.1155712;
		*a_iter++ = 0.1155712;
		*a_iter++ = -0.1145563;
		*a_iter++ = 0.1145563;
		*a_iter++ = -0.1013425;
		*a_iter++ = 0.1013425;
		*a_iter++ = -0.1145783;
		*a_iter++ = 0.1145783;
		*a_iter++ = -0.1328031;
		*a_iter++ = 0.1328031;
		*a_iter++ = -0.1077413;
		*a_iter++ = 0.1077413;
		*a_iter++ = -0.1064996;
		*a_iter++ = 0.1064996;
		*a_iter++ = -0.119117;
		*a_iter++ = 0.119117;
		*a_iter++ = -0.1213217;
		*a_iter++ = 0.1213217;
		*a_iter++ = -0.1260969;
		*a_iter++ = 0.1260969;
		*a_iter++ = -0.1156494;
		*a_iter++ = 0.1156494;
		*a_iter++ = -0.1268126;
		*a_iter++ = 0.1268126;
		*a_iter++ = -0.1070999;
		*a_iter++ = 0.1070999;
		*a_iter++ = -0.1112365;
		*a_iter++ = 0.1112365;
		*a_iter++ = -0.1243916;
		*a_iter++ = 0.1243916;
		*a_iter++ = -0.1283152;
		*a_iter++ = 0.1283152;
		*a_iter++ = -0.1166925;
		*a_iter++ = 0.1166925;
		*a_iter++ = -0.08997633;
		*a_iter++ = 0.08997633;
		*a_iter++ = -0.158384;
		*a_iter++ = 0.158384;
		*a_iter++ = -0.1211178;
		*a_iter++ = 0.1211178;
		*a_iter++ = -0.109083;
		*a_iter++ = 0.109083;
		*a_iter++ = -0.1030818;
		*a_iter++ = 0.1030818;
		*a_iter++ = -0.14406;
		*a_iter++ = 0.14406;
		*a_iter++ = -0.1458713;
		*a_iter++ = 0.1458713;
		*a_iter++ = -0.1559082;
		*a_iter++ = 0.1559082;
		*a_iter++ = -0.1058868;
		*a_iter++ = 0.1058868;
		*a_iter++ = -0.101013;
		*a_iter++ = 0.101013;
		*a_iter++ = -0.1642301;
		*a_iter++ = 0.1642301;
		*a_iter++ = -0.123685;
		*a_iter++ = 0.123685;
		*a_iter++ = -0.1467589;
		*a_iter++ = 0.1467589;
		*a_iter++ = -0.1109359;
		*a_iter++ = 0.1109359;
		*a_iter++ = -0.1673655;
		*a_iter++ = 0.1673655;
		*a_iter++ = -0.1239984;
		*a_iter++ = 0.1239984;
		*a_iter++ = -0.1039509;
		*a_iter++ = 0.1039509;
		*a_iter++ = -0.1089378;
		*a_iter++ = 0.1089378;
		*a_iter++ = -0.1545085;
		*a_iter++ = 0.1545085;
		*a_iter++ = -0.1200862;
		*a_iter++ = 0.1200862;
		*a_iter++ = -0.1105608;
		*a_iter++ = 0.1105608;
		*a_iter++ = -0.1235262;
		*a_iter++ = 0.1235262;
		*a_iter++ = -0.08496153;
		*a_iter++ = 0.08496153;
		*a_iter++ = -0.1181372;
		*a_iter++ = 0.1181372;
		*a_iter++ = -0.1139467;
		*a_iter++ = 0.1139467;
		*a_iter++ = -0.1189317;
		*a_iter++ = 0.1189317;
		*a_iter++ = -0.1266519;
		*a_iter++ = 0.1266519;
		*a_iter++ = -0.09470736;
		*a_iter++ = 0.09470736;
		*a_iter++ = -0.1336735;
		*a_iter++ = 0.1336735;
		*a_iter++ = -0.08726601;
		*a_iter++ = 0.08726601;
		*a_iter++ = -0.1304782;
		*a_iter++ = 0.1304782;
		*a_iter++ = -0.1186529;
		*a_iter++ = 0.1186529;
		*a_iter++ = -0.1355944;
		*a_iter++ = 0.1355944;
		*a_iter++ = -0.09568801;
		*a_iter++ = 0.09568801;
		*a_iter++ = -0.1282618;
		*a_iter++ = 0.1282618;
		*a_iter++ = -0.1625632;
		*a_iter++ = 0.1625632;
		*a_iter++ = -0.1167652;
		*a_iter++ = 0.1167652;
		*a_iter++ = -0.1001301;
		*a_iter++ = 0.1001301;
		*a_iter++ = -0.1292419;
		*a_iter++ = 0.1292419;
		*a_iter++ = -0.1904213;
		*a_iter++ = 0.1904213;
		*a_iter++ = -0.1511542;
		*a_iter++ = 0.1511542;
		*a_iter++ = -0.09814394;
		*a_iter++ = 0.09814394;
		*a_iter++ = -0.1171564;
		*a_iter++ = 0.1171564;
		*a_iter++ = -0.09806486;
		*a_iter++ = 0.09806486;
		*a_iter++ = -0.09217615;
		*a_iter++ = 0.09217615;
		*a_iter++ = -0.08505645;
		*a_iter++ = 0.08505645;
		*a_iter++ = -0.1573637;
		*a_iter++ = 0.1573637;
		*a_iter++ = -0.1419174;
		*a_iter++ = 0.1419174;
		*a_iter++ = -0.1298601;
		*a_iter++ = 0.1298601;
		*a_iter++ = -0.1120613;
		*a_iter++ = 0.1120613;
		*a_iter++ = -0.1158363;
		*a_iter++ = 0.1158363;
		*a_iter++ = -0.1090957;
		*a_iter++ = 0.1090957;
		*a_iter++ = -0.1204516;
		*a_iter++ = 0.1204516;
		*a_iter++ = -0.1139852;
		*a_iter++ = 0.1139852;
		*a_iter++ = -0.09642479;
		*a_iter++ = 0.09642479;
		*a_iter++ = -0.1410872;
		*a_iter++ = 0.1410872;
		*a_iter++ = -0.1142779;
		*a_iter++ = 0.1142779;
		*a_iter++ = -0.1043991;
		*a_iter++ = 0.1043991;
		*a_iter++ = -0.09736463;
		*a_iter++ = 0.09736463;
		*a_iter++ = -0.1451046;
		*a_iter++ = 0.1451046;
		*a_iter++ = -0.1205668;
		*a_iter++ = 0.1205668;
		*a_iter++ = -0.09881445;
		*a_iter++ = 0.09881445;
		*a_iter++ = -0.1612822;
		*a_iter++ = 0.1612822;
		*a_iter++ = -0.1175681;
		*a_iter++ = 0.1175681;
		*a_iter++ = -0.1522528;
		*a_iter++ = 0.1522528;
		*a_iter++ = -0.161752;
		*a_iter++ = 0.161752;
		*a_iter++ = -0.1582938;
		*a_iter++ = 0.1582938;
		*a_iter++ = -0.1208202;
		*a_iter++ = 0.1208202;
		*a_iter++ = -0.1016003;
		*a_iter++ = 0.1016003;
		*a_iter++ = -0.1232059;
		*a_iter++ = 0.1232059;
		*a_iter++ = -0.09583025;
		*a_iter++ = 0.09583025;
		*a_iter++ = -0.101399;
		*a_iter++ = 0.101399;
		*a_iter++ = -0.1178752;
		*a_iter++ = 0.1178752;
		*a_iter++ = -0.1215972;
		*a_iter++ = 0.1215972;
		*a_iter++ = -0.1294932;
		*a_iter++ = 0.1294932;
		*a_iter++ = -0.115827;
		*a_iter++ = 0.115827;
		*a_iter++ = -0.1008645;
		*a_iter++ = 0.1008645;
		*a_iter++ = -0.0969919;
		*a_iter++ = 0.0969919;
		*a_iter++ = -0.1022144;
		*a_iter++ = 0.1022144;
		*a_iter++ = -0.09878768;
		*a_iter++ = 0.09878768;
		*a_iter++ = -0.1339052;
		*a_iter++ = 0.1339052;
		*a_iter++ = -0.09279961;
		*a_iter++ = 0.09279961;
		*a_iter++ = -0.1047606;
		*a_iter++ = 0.1047606;
		*a_iter++ = -0.1141163;
		*a_iter++ = 0.1141163;
		*a_iter++ = -0.12676;
		*a_iter++ = 0.12676;
		*a_iter++ = -0.1252763;
		*a_iter++ = 0.1252763;
		*a_iter++ = -0.09775003;
		*a_iter++ = 0.09775003;
		*a_iter++ = -0.09169116;
		*a_iter++ = 0.09169116;
		*a_iter++ = -0.1006496;
		*a_iter++ = 0.1006496;
		*a_iter++ = -0.09493293;
		*a_iter++ = 0.09493293;
		*a_iter++ = -0.1213694;
		*a_iter++ = 0.1213694;
		*a_iter++ = -0.1109243;
		*a_iter++ = 0.1109243;
		*a_iter++ = -0.1115973;
		*a_iter++ = 0.1115973;
		*a_iter++ = -0.07979327;
		*a_iter++ = 0.07979327;
		*a_iter++ = -0.09220953;
		*a_iter++ = 0.09220953;
		*a_iter++ = -0.1028913;
		*a_iter++ = 0.1028913;
		*a_iter++ = -0.125351;
		*a_iter++ = 0.125351;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 391;
		sc.threshold = -4.665692;
		sc.features.SetCount(391);
		sc.alpha.SetCount(782);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 9 << 11 << 17 << 12;
			cf.py << 2 << 3 << 9 << 13 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 21 << 8 << 7 << 20 << 13;
			cf.ny << 16 << 10 << 7 << 7 << 9;
			cf.nz << 0 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 10 << 6 << 11 << 13;
			cf.py << 9 << 3 << 13 << 3 << 4;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 10 << 4 << 5 << 10 << 2;
			cf.ny << 9 << 10 << 8 << 8 << 2;
			cf.nz << 0 << 1 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 9 << 7 << 8 << 8;
			cf.py << 3 << 3 << 3 << 3 << 3;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 0 << 0 << 0 << 4 << 9;
			cf.ny << 4 << 2 << 3 << 10 << 8;
			cf.nz << 0 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 2 << 16 << 6 << 8;
			cf.py << 16 << 2 << 11 << 4 << 11;
			cf.pz << 0 << 2 << 0 << 1 << 0;
			cf.nx << 3 << 8 << 4 << 1 << 1;
			cf.ny << 4 << 4 << 4 << 5 << 13;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 13 << 9;
			cf.py << 23 << 18 << 10;
			cf.pz << 0 << 0 << 1;
			cf.nx << 14 << 15 << 8;
			cf.ny << 21 << 22 << 3;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 16 << 19 << 17 << 17;
			cf.py << 1 << 2 << 3 << 2 << 2;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 23 << 23 << 23 << 23 << 23;
			cf.ny << 6 << 2 << 1 << 3 << 5;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 12 << 12;
			cf.py << 10 << 11 << 12 << 13 << 13;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 8 << 14 << 4 << 6;
			cf.ny << 2 << 4 << 7 << 4 << 8;
			cf.nz << 2 << 1 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 2 << 3 << 6 << 4;
			cf.py << 6 << 10 << 12 << 23 << 13;
			cf.pz << 1 << 1 << 0 << 0 << 0;
			cf.nx << 2 << 0 << 0 << 1 << 1;
			cf.ny << 23 << 5 << 10 << 21 << 21;
			cf.nz << 0 << 2 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 16 << 12 << 4 << 12;
			cf.py << 6 << 17 << 7 << 2 << 8;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 8 << 8 << 12 << 0 << 6;
			cf.ny << 4 << 4 << 16 << 0 << 8;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 18 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 10 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 9 << 2 << 0 << 12;
			cf.py << 6 << 6 << 21 << 4 << 8;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 8 << 4 << 9 << 7 << 7;
			cf.ny << 10 << 2 << 4 << 5 << 8;
			cf.nz << 1 << 2 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 10 << 10 << 18 << 19;
			cf.py << 10 << 8 << 7 << 14 << 14;
			cf.pz << 1 << 1 << 1 << 0 << 0;
			cf.nx << 21 << 23 << 22 << 22 << 11;
			cf.ny << 23 << 19 << 21 << 22 << 10;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 3 << 15 << 4 << 19;
			cf.py << 14 << 0 << 5 << 5 << 14;
			cf.pz << 0 << -1 << -1 << -1 << -1;
			cf.nx << 12 << 17 << 15 << 3 << 8;
			cf.ny << 18 << 18 << 14 << 2 << 10;
			cf.nz << 0 << 0 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 11 << 3 << 11 << 4;
			cf.py << 23 << 7 << 9 << 8 << 8;
			cf.pz << 0 << 0 << 1 << 0 << 1;
			cf.nx << 8 << 0 << 10 << 0 << 8;
			cf.ny << 8 << 2 << 8 << 4 << 10;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 11 << 12 << 8 << 4;
			cf.py << 3 << 0 << 0 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 2 << 3 << 4 << 3 << 3;
			cf.ny << 14 << 5 << 0 << 1 << 2;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 11;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 5 << 2;
			cf.ny << 9 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 1 << 0 << 10 << 1;
			cf.py << 0 << 0 << 2 << 12 << 6;
			cf.pz << 0 << 2 << 2 << 0 << 1;
			cf.nx << 4 << 6 << 2 << 8 << 8;
			cf.ny << 4 << 11 << 2 << 4 << 4;
			cf.nz << 1 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 15;
			cf.py << 4 << 12;
			cf.pz << 2 << 0;
			cf.nx << 4 << 6;
			cf.ny << 5 << 11;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 4 << 16 << 14 << 14;
			cf.py << 8 << 4 << 23 << 18 << 18;
			cf.pz << 1 << 2 << 0 << 0 << -1;
			cf.nx << 0 << 2 << 1 << 1 << 0;
			cf.ny << 2 << 0 << 3 << 2 << 3;
			cf.nz << 1 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 7 << 7 << 18 << 19;
			cf.py << 7 << 11 << 8 << 7 << 7;
			cf.pz << 0 << 1 << 1 << 0 << 0;
			cf.nx << 17 << 5 << 8 << 2 << 0;
			cf.ny << 8 << 0 << 7 << 5 << 3;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 14;
			cf.py << 12 << 3;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 5 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 8 << 16 << 11 << 11;
			cf.py << 5 << 6 << 12 << 4 << 4;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 14 << 13 << 5 << 9 << 5;
			cf.ny << 13 << 10 << 1 << 4 << 2;
			cf.nz << 0 << 0 << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 14 << 16 << 8 << 8;
			cf.py << 2 << 2 << 2 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 9 << 18 << 19 << 18 << 17;
			cf.ny << 0 << 0 << 2 << 1 << 0;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 15;
			cf.py << 12 << 11;
			cf.pz << 0 << 0;
			cf.nx << 14 << 4;
			cf.ny << 9 << 15;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 11 << 11;
			cf.py << 3 << 4 << 5;
			cf.pz << 2 << 1 << 1;
			cf.nx << 14 << 3 << 18;
			cf.ny << 6 << 5 << 0;
			cf.nz << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 14 << 17 << 15 << 9;
			cf.py << 2 << 2 << 2 << 2 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 21 << 20 << 11 << 21 << 21;
			cf.ny << 2 << 0 << 7 << 3 << 3;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 1 << 1 << 1 << 5;
			cf.py << 12 << 9 << 7 << 3 << 6;
			cf.pz << 0 << 0 << 1 << 1 << 1;
			cf.nx << 4 << 8 << 3 << 4 << 17;
			cf.ny << 4 << 4 << 0 << 8 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 9 << 2;
			cf.ny << 4 << 17;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 5;
			cf.py << 16 << 9;
			cf.pz << 0 << 1;
			cf.nx << 10 << 17;
			cf.ny << 16 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 5 << 9 << 15;
			cf.py << 14 << 9 << 11 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 10 << 1 << 9 << 4;
			cf.ny << 9 << 2 << 13 << 7;
			cf.nz << 0 << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 5 << 10 << 7 << 10;
			cf.py << 7 << 12 << 2 << 13 << 3;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 5 << 2 << 3 << 3 << 2;
			cf.ny << 23 << 15 << 17 << 16 << 14;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 7;
			cf.py << 8 << 10;
			cf.pz << 0 << -1;
			cf.nx << 7 << 14;
			cf.ny << 5 << 8;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 16;
			cf.py << 7 << 23;
			cf.pz << 1 << 0;
			cf.nx << 4 << 4;
			cf.ny << 2 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 14 << 18 << 4 << 17;
			cf.py << 0 << 0 << 4 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 8 << 8 << 16 << 9 << 9;
			cf.ny << 5 << 4 << 11 << 7 << 7;
			cf.nz << 1 << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 13 << 7 << 8 << 4;
			cf.py << 9 << 12 << 6 << 11 << 5;
			cf.pz << 0 << 0 << 1 << 1 << 2;
			cf.nx << 23 << 23 << 16 << 9 << 9;
			cf.ny << 0 << 1 << 11 << 7 << 7;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 7 << 2;
			cf.py << 21 << 23 << 4;
			cf.pz << 0 << 0 << 2;
			cf.nx << 4 << 1 << 16;
			cf.ny << 10 << 5 << 11;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 3 << 1;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 2 << 1 << 0 << 1;
			cf.py << 7 << 13 << 12 << 4 << 13;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 18 << 9 << 9 << 19 << 19;
			cf.ny << 23 << 5 << 11 << 19 << 19;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 10 << 12;
			cf.py << 6 << 2 << 5;
			cf.pz << 1 << -1 << -1;
			cf.nx << 10 << 0 << 0;
			cf.ny << 12 << 1 << 3;
			cf.nz << 0 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 0;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 19 << 17 << 10 << 14 << 18;
			cf.py << 2 << 1 << 7 << 0 << 1;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 3 << 3 << 3 << 7 << 5;
			cf.ny << 9 << 10 << 7 << 23 << 18;
			cf.nz << 1 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 14 << 4;
			cf.ny << 15 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 15;
			cf.py << 1 << 3;
			cf.pz << 1 << 0;
			cf.nx << 16 << 19;
			cf.ny << 1 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 1 << 2 << 11;
			cf.py << 11 << 12 << 1 << 13 << 12;
			cf.pz << 0 << 0 << -1 << -1 << -1;
			cf.nx << 12 << 17 << 8 << 16 << 8;
			cf.ny << 7 << 12 << 11 << 16 << 6;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 11 << 10 << 12 << 5;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 8 << 4 << 3 << 4 << 4;
			cf.ny << 4 << 5 << 2 << 4 << 4;
			cf.nz << 1 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 6 << 1 << 3 << 2 << 3;
			cf.py << 13 << 3 << 3 << 4 << 10;
			cf.pz << 0 << 2 << 1 << 1 << 1;
			cf.nx << 0 << 1 << 0 << 0 << 0;
			cf.ny << 2 << 0 << 5 << 4 << 4;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 1;
			cf.py << 4 << 3;
			cf.pz << 0 << -1;
			cf.nx << 16 << 15;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 3 << 0;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 15;
			cf.py << 18 << 14;
			cf.pz << 0 << -1;
			cf.nx << 4 << 14;
			cf.ny << 4 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 6;
			cf.py << 3 << 4;
			cf.pz << 2 << 1;
			cf.nx << 9 << 5;
			cf.ny << 14 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 6;
			cf.py << 1 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 0 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 0;
			cf.py << 4 << 2;
			cf.pz << 0 << -1;
			cf.nx << 5 << 3;
			cf.ny << 1 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 1 << 0 << 0;
			cf.py << 16 << 15 << 17 << 6 << 9;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 9 << 5 << 4 << 9 << 8;
			cf.ny << 7 << 3 << 3 << 6 << 7;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 1;
			cf.py << 8 << 15;
			cf.pz << 1 << -1;
			cf.nx << 9 << 8;
			cf.ny << 9 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 19;
			cf.py << 19 << 22;
			cf.pz << 0 << 0;
			cf.nx << 7 << 0;
			cf.ny << 3 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 4 << 2 << 5 << 5;
			cf.py << 12 << 6 << 3 << 5 << 5;
			cf.pz << 0 << 1 << 2 << 1 << -1;
			cf.nx << 22 << 21 << 20 << 21 << 22;
			cf.ny << 17 << 20 << 22 << 19 << 16;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 2 << 6;
			cf.pz << 1 << 0;
			cf.nx << 8 << 3;
			cf.ny << 3 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 9 << 4;
			cf.pz << 1 << 1;
			cf.nx << 12 << 4;
			cf.ny << 17 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 1 << 0;
			cf.py << 5 << 13 << 3;
			cf.pz << 2 << 0 << 2;
			cf.nx << 0 << 4 << 11;
			cf.ny << 23 << 5 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 6 << 3;
			cf.pz << 0 << 1;
			cf.nx << 4 << 4;
			cf.ny << 3 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 7 << 3;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 4 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 13 << 12 << 12 << 12;
			cf.py << 12 << 13 << 11 << 10 << 10;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 10 << 8 << 8 << 16 << 15;
			cf.ny << 7 << 4 << 10 << 11 << 10;
			cf.nz << 0 << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 4 << 2;
			cf.ny << 5 << 5;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 17;
			cf.py << 17 << 7;
			cf.pz << 0 << -1;
			cf.nx << 5 << 2;
			cf.ny << 9 << 4;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 3 << 5;
			cf.pz << 2 << 2;
			cf.nx << 12 << 8;
			cf.ny << 16 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 2 << 0;
			cf.pz << 1 << 1;
			cf.nx << 0 << 4;
			cf.ny << 0 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 5 << 0;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 0 << 6 << 4 << 22;
			cf.py << 23 << 2 << 4 << 12;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 7 << 6 << 8 << 5;
			cf.ny << 1 << 1 << 2 << 1;
			cf.nz << 1 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 10;
			cf.py << 0 << 9;
			cf.pz << 1 << -1;
			cf.nx << 2 << 4;
			cf.ny << 3 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 8;
			cf.py << 15 << 13;
			cf.pz << 0 << -1;
			cf.nx << 23 << 11;
			cf.ny << 13 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 4;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 18 << 20;
			cf.ny << 4 << 7;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 20 << 20 << 10 << 20;
			cf.py << 17 << 22 << 19 << 10 << 21;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 5 << 5 << 3 << 14 << 7;
			cf.ny << 9 << 9 << 0 << 8 << 4;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 7 << 13 << 7 << 3;
			cf.py << 6 << 12 << 3 << 0 << 3;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 1 << 5 << 0 << 0 << 2;
			cf.ny << 16 << 6 << 13 << 5 << 4;
			cf.nz << 0 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 9 << 5;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 9 << 13;
			cf.py << 19 << 22 << 8;
			cf.pz << 0 << -1 << -1;
			cf.nx << 13 << 4 << 4;
			cf.ny << 17 << 2 << 5;
			cf.nz << 0 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 4;
			cf.py << 9 << 3;
			cf.pz << 0 << 2;
			cf.nx << 7 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 2 << 4 << 2;
			cf.py << 23 << 4 << 8 << 3;
			cf.pz << 0 << 2 << 1 << 2;
			cf.nx << 14 << 0 << 4 << 11;
			cf.ny << 19 << 3 << 5 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 10 << 8 << 7 << 11;
			cf.py << 2 << 2 << 2 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 6 << 5 << 3 << 4 << 4;
			cf.ny << 0 << 1 << 0 << 2 << 2;
			cf.nz << 0 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 4;
			cf.py << 13 << 6;
			cf.pz << 0 << -1;
			cf.nx << 15 << 4;
			cf.ny << 8 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 8;
			cf.py << 1 << 2;
			cf.pz << 2 << -1;
			cf.nx << 5 << 4;
			cf.ny << 2 << 2;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 13 << 14 << 15 << 15;
			cf.py << 1 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 9 << 4 << 18 << 8;
			cf.ny << 5 << 9 << 4 << 18 << 11;
			cf.nz << 2 << 1 << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 2 << 6;
			cf.pz << 2 << 1;
			cf.nx << 22 << 9;
			cf.ny << 23 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 19;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 21 << 22;
			cf.ny << 2 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 5;
			cf.py << 8 << 6;
			cf.pz << 0 << 1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 14;
			cf.py << 13 << 17;
			cf.pz << 0 << 0;
			cf.nx << 14 << 4;
			cf.ny << 16 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 6 << 3;
			cf.pz << 1 << -1;
			cf.nx << 1 << 0;
			cf.ny << 2 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 21;
			cf.py << 21 << 14;
			cf.pz << 0 << -1;
			cf.nx << 7 << 5;
			cf.ny << 0 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 10;
			cf.py << 23 << 7;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 18;
			cf.py << 3 << 8;
			cf.pz << 2 << 0;
			cf.nx << 8 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 7;
			cf.py << 2 << 11;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 3 << 5 << 6 << 1;
			cf.py << 7 << 14 << 2 << 2 << 4;
			cf.pz << 1 << 0 << 0 << 0 << 2;
			cf.nx << 8 << 4 << 4 << 7 << 7;
			cf.ny << 7 << 5 << 4 << 9 << 9;
			cf.nz << 1 << 2 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 6 << 3;
			cf.pz << 1 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 20 << 4 << 10 << 10;
			cf.py << 9 << 16 << 4 << 10 << 8;
			cf.pz << 1 << 0 << 2 << 1 << 1;
			cf.nx << 4 << 2 << 3 << 5 << 3;
			cf.ny << 11 << 5 << 6 << 12 << 5;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 11;
			cf.py << 4 << 18;
			cf.pz << 1 << -1;
			cf.nx << 8 << 6;
			cf.ny << 4 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 8;
			cf.py << 5 << 23;
			cf.pz << 2 << 0;
			cf.nx << 9 << 4;
			cf.ny << 0 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 1 << 2 << 2 << 2;
			cf.py << 12 << 6 << 12 << 11 << 11;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 13 << 12 << 11 << 14 << 7;
			cf.nz << 0 << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 14;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 23 << 23 << 22 << 22;
			cf.py << 8 << 12 << 6 << 13 << 14;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 13 << 8 << 7 << 6 << 6;
			cf.ny << 6 << 3 << 3 << 9 << 9;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 23 << 23 << 22;
			cf.py << 7 << 12 << 6 << 13;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 11 << 23 << 23 << 23;
			cf.ny << 6 << 13 << 17 << 10;
			cf.nz << 1 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 19 << 5 << 9 << 16 << 10;
			cf.pz << 0 << 2 << 1 << 0 << 1;
			cf.nx << 5 << 2 << 1 << 2 << 2;
			cf.ny << 18 << 10 << 5 << 9 << 9;
			cf.nz << 0 << 1 << 2 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 23 << 14;
			cf.ny << 23 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 1;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 10;
			cf.py << 4 << 8;
			cf.pz << 0 << -1;
			cf.nx << 8 << 8;
			cf.ny << 2 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 10 << 11;
			cf.py << 1 << 6 << 13;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 4 << 2;
			cf.ny << 3 << 8 << 2;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 8 << 2;
			cf.pz << 1 << 2;
			cf.nx << 10 << 5;
			cf.ny << 10 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 16;
			cf.py << 20 << 21;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 10;
			cf.py << 7 << 8;
			cf.pz << 1 << -1;
			cf.nx << 7 << 4;
			cf.ny << 20 << 7;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 11 << 11 << 11 << 11;
			cf.py << 10 << 12 << 13 << 11 << 11;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 11 << 12 << 16 << 3 << 8;
			cf.ny << 6 << 6 << 10 << 1 << 8;
			cf.nz << 0 << 0 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 4 << 2;
			cf.pz << 0 << 1;
			cf.nx << 7 << 7;
			cf.ny << 8 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 23 << 23 << 23 << 23 << 23;
			cf.py << 22 << 20 << 21 << 19 << 19;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 6 << 3 << 4 << 3;
			cf.ny << 19 << 23 << 15 << 20 << 16;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 4 << 14;
			cf.py << 12 << 3 << 8;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 2 << 10;
			cf.ny << 10 << 3 << 13;
			cf.nz << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 18;
			cf.py << 13 << 23;
			cf.pz << 0 << -1;
			cf.nx << 5 << 5;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 2 << 10;
			cf.py << 17 << 4 << 17;
			cf.pz << 0 << 2 << 0;
			cf.nx << 11 << 0 << 22;
			cf.ny << 15 << 2 << 4;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 3 << 0;
			cf.py << 15 << 4 << 8;
			cf.pz << 0 << -1 << -1;
			cf.nx << 14 << 11 << 4;
			cf.ny << 9 << 17 << 7;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 16;
			cf.py << 2 << 1;
			cf.pz << 0 << 0;
			cf.nx << 9 << 11;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 21 << 23;
			cf.pz << 0 << 0;
			cf.nx << 4 << 0;
			cf.ny << 3 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 2;
			cf.py << 20 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 9;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 1;
			cf.py << 19 << 3;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 9 << 21;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 19;
			cf.py << 21 << 22;
			cf.pz << 0 << 0;
			cf.nx << 19 << 0;
			cf.ny << 23 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 2 << 3 << 2;
			cf.py << 6 << 6 << 9 << 4;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 4 << 9 << 19 << 19;
			cf.ny << 5 << 10 << 17 << 18;
			cf.nz << 2 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 4 << 8;
			cf.pz << 2 << 1;
			cf.nx << 4 << 9;
			cf.ny << 10 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 22;
			cf.py << 8 << 12;
			cf.pz << 0 << -1;
			cf.nx << 7 << 4;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 1;
			cf.py << 5 << 2;
			cf.pz << 0 << -1;
			cf.nx << 9 << 11;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 2 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 9;
			cf.py << 13 << 7;
			cf.pz << 0 << 1;
			cf.nx << 9 << 5;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 0 << 0 << 9 << 13;
			cf.py << 3 << 3 << 7 << 3;
			cf.pz << 2 << -1 << -1 << -1;
			cf.nx << 2 << 4 << 4 << 11;
			cf.ny << 1 << 2 << 8 << 5;
			cf.nz << 2 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 6 << 5 << 6 << 6;
			cf.py << 0 << 0 << 2 << 1 << 1;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 2 << 2 << 2 << 1 << 1;
			cf.ny << 21 << 19 << 20 << 16 << 17;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 22 << 10;
			cf.pz << 0 << -1;
			cf.nx << 7 << 4;
			cf.ny << 10 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 7 << 3;
			cf.pz << 1 << 2;
			cf.nx << 8 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 17 << 8 << 15 << 7 << 15;
			cf.py << 13 << 6 << 16 << 5 << 12;
			cf.pz << 0 << 1 << 0 << 1 << 0;
			cf.nx << 5 << 4 << 6 << 3 << 4;
			cf.ny << 1 << 2 << 1 << 0 << 3;
			cf.nz << 0 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 9 << 11 << 12 << 10;
			cf.py << 0 << 1 << 2 << 2 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 16 << 7 << 4 << 4;
			cf.ny << 9 << 23 << 9 << 3 << 2;
			cf.nz << 1 << 0 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 11;
			cf.py << 1 << 4;
			cf.pz << 2 << -1;
			cf.nx << 8 << 7;
			cf.ny << 4 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 4 << 5 << 8;
			cf.py << 13 << 2 << 1 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 9 << 4 << 9 << 9;
			cf.ny << 9 << 5 << 10 << 11;
			cf.nz << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 11;
			cf.py << 10 << 11;
			cf.pz << 0 << -1;
			cf.nx << 2 << 6;
			cf.ny << 2 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 3;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 22 << 22;
			cf.ny << 20 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 1 << 2;
			cf.pz << 0 << 0;
			cf.nx << 5 << 10;
			cf.ny << 1 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 3;
			cf.py << 18 << 1;
			cf.pz << 0 << -1;
			cf.nx << 16 << 15;
			cf.ny << 4 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 7;
			cf.py << 4 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 11;
			cf.py << 23 << 17;
			cf.pz << 0 << 0;
			cf.nx << 11 << 21;
			cf.ny << 16 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 2;
			cf.py << 0 << 6;
			cf.pz << 1 << -1;
			cf.nx << 16 << 16;
			cf.ny << 9 << 11;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 20 << 20;
			cf.pz << 0 << 0;
			cf.nx << 11 << 3;
			cf.ny << 21 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 19 << 20 << 9;
			cf.py << 21 << 18 << 11;
			cf.pz << 0 << 0 << 1;
			cf.nx << 17 << 4 << 11;
			cf.ny << 19 << 2 << 0;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 5 << 2;
			cf.pz << 0 << 1;
			cf.nx << 7 << 9;
			cf.ny << 7 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 4 << 4 << 8 << 4;
			cf.py << 4 << 4 << 5 << 10 << 3;
			cf.pz << 1 << 1 << 2 << 0 << 2;
			cf.nx << 11 << 22 << 11 << 23 << 23;
			cf.ny << 0 << 0 << 1 << 3 << 3;
			cf.nz << 1 << 0 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 14;
			cf.py << 10 << 23;
			cf.pz << 1 << 0;
			cf.nx << 7 << 2;
			cf.ny << 10 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 14;
			cf.py << 6 << 23;
			cf.pz << 1 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 2;
			cf.py << 19 << 3;
			cf.pz << 0 << -1;
			cf.nx << 10 << 12;
			cf.ny << 18 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 3;
			cf.py << 4 << 1;
			cf.pz << 0 << 2;
			cf.nx << 6 << 6;
			cf.ny << 11 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 18 << 10 << 20 << 19 << 19;
			cf.pz << 0 << 1 << 0 << 0 << -1;
			cf.nx << 11 << 10 << 14 << 12 << 13;
			cf.ny << 2 << 2 << 2 << 2 << 2;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 2 << 9;
			cf.py << 14 << 5 << 10;
			cf.pz << 0 << -1 << -1;
			cf.nx << 11 << 10 << 5;
			cf.ny << 10 << 13 << 5;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 3 << 7;
			cf.pz << 2 << 1;
			cf.nx << 3 << 10;
			cf.ny << 4 << 13;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 21 << 7;
			cf.pz << 0 << -1;
			cf.nx << 10 << 21;
			cf.ny << 7 << 15;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 10;
			cf.py << 16 << 8;
			cf.pz << 0 << 1;
			cf.nx << 8 << 2;
			cf.ny << 10 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 6 << 7;
			cf.pz << 1 << -1;
			cf.nx << 12 << 11;
			cf.ny << 11 << 7;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 11;
			cf.py << 4 << 20;
			cf.pz << 2 << 0;
			cf.nx << 11 << 10;
			cf.ny << 19 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 5;
			cf.py << 13 << 3;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 1;
			cf.py << 23 << 3;
			cf.pz << 0 << 2;
			cf.nx << 14 << 6;
			cf.ny << 12 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 11 << 7;
			cf.ny << 3 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 6;
			cf.py << 2 << 17;
			cf.pz << 0 << -1;
			cf.nx << 4 << 6;
			cf.ny << 4 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 19;
			cf.py << 5 << 6;
			cf.pz << 0 << -1;
			cf.nx << 9 << 3;
			cf.ny << 9 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 13 << 13 << 13 << 12;
			cf.py << 9 << 11 << 12 << 13 << 10;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 2 << 4 << 4 << 4 << 4;
			cf.ny << 7 << 18 << 17 << 14 << 14;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 6 << 6;
			cf.pz << 1 << -1;
			cf.nx << 20 << 18;
			cf.ny << 18 << 23;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 4 << 14;
			cf.pz << 1 << -1;
			cf.nx << 9 << 4;
			cf.ny << 2 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 9;
			cf.py << 4 << 18;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 0;
			cf.py << 18 << 4;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 5 << 4;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 3 << 6 << 6;
			cf.py << 8 << 4 << 6 << 5;
			cf.pz << 1 << 2 << 1 << 1;
			cf.nx << 10 << 4 << 13 << 0;
			cf.ny << 10 << 4 << 9 << 22;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 8;
			cf.py << 18 << 11;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 8 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 2 << 10 << 2;
			cf.py << 14 << 1 << 10 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 8 << 8 << 17 << 8;
			cf.ny << 4 << 5 << 12 << 6;
			cf.nz << 1 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 11 << 9 << 4 << 10;
			cf.py << 1 << 1 << 0 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 8 << 4 << 7 << 15 << 15;
			cf.ny << 7 << 2 << 4 << 17 << 17;
			cf.nz << 1 << 2 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 11 << 8;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 3;
			cf.py << 13 << 8;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 5 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 2;
			cf.py << 8 << 3;
			cf.pz << 0 << 2;
			cf.nx << 3 << 1;
			cf.ny << 5 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 5 << 7 << 8 << 6;
			cf.py << 9 << 7 << 7 << 7 << 7;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 7 << 3 << 0 << 2 << 15;
			cf.ny << 8 << 0 << 1 << 18 << 17;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 8;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 11 << 8 << 10 << 12;
			cf.py << 0 << 2 << 10 << 2 << 3;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 3 << 2 << 10 << 2 << 2;
			cf.ny << 6 << 4 << 11 << 3 << 3;
			cf.nz << 0 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 8 << 19;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 1 << 1;
			cf.pz << 2 << -1;
			cf.nx << 7 << 17;
			cf.ny << 1 << 2;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 15 << 14 << 13 << 7;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 6 << 4 << 8 << 3 << 11;
			cf.ny << 3 << 4 << 4 << 1 << 6;
			cf.nz << 1 << 1 << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 8 << 5;
			cf.pz << 0 << -1;
			cf.nx << 13 << 4;
			cf.ny << 10 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 9;
			cf.py << 0 << 2;
			cf.pz << 2 << 1;
			cf.nx << 4 << 11;
			cf.ny << 0 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 15;
			cf.py << 2 << 2;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 17;
			cf.py << 9 << 22;
			cf.pz << 1 << 0;
			cf.nx << 8 << 20;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 14 << 22;
			cf.pz << 0 << -1;
			cf.nx << 3 << 11;
			cf.ny << 3 << 3;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 1 << 0;
			cf.pz << 1 << 2;
			cf.nx << 5 << 8;
			cf.ny << 3 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 4 << 8;
			cf.pz << 2 << 1;
			cf.nx << 9 << 5;
			cf.ny << 15 << 19;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 1 << 1;
			cf.pz << 0 << 1;
			cf.nx << 10 << 10;
			cf.ny << 6 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 6;
			cf.py << 10 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 7 << 3;
			cf.py << 5 << 2 << 6;
			cf.pz << 0 << 1 << -1;
			cf.nx << 17 << 16 << 17;
			cf.ny << 1 << 1 << 2;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 3 << 3;
			cf.pz << 0 << 0;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 0 << 8;
			cf.pz << 2 << -1;
			cf.nx << 3 << 4;
			cf.ny << 0 << 0;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 2 << 4 << 1 << 2;
			cf.py << 13 << 3 << 9 << 2 << 5;
			cf.pz << 0 << 2 << 1 << 2 << 2;
			cf.nx << 9 << 5 << 10 << 4 << 10;
			cf.ny << 5 << 1 << 3 << 0 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 5 << 9;
			cf.pz << 1 << 0;
			cf.nx << 0 << 2;
			cf.ny << 23 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 11;
			cf.py << 21 << 8;
			cf.pz << 0 << 1;
			cf.nx << 10 << 0;
			cf.ny << 17 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 1;
			cf.py << 22 << 9;
			cf.pz << 0 << 1;
			cf.nx << 22 << 5;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 5 << 6;
			cf.ny << 10 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 3 << 17 << 7;
			cf.py << 8 << 2 << 10 << 11;
			cf.pz << 0 << 2 << 0 << 1;
			cf.nx << 6 << 10 << 5 << 23;
			cf.ny << 9 << 21 << 1 << 23;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 7 << 2;
			cf.pz << 1 << 2;
			cf.nx << 8 << 9;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 14 << 6;
			cf.pz << 0 << 1;
			cf.nx << 8 << 8;
			cf.ny << 13 << 13;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 6 << 8;
			cf.py << 20 << 3 << 20;
			cf.pz << 0 << -1 << -1;
			cf.nx << 5 << 3 << 12;
			cf.ny << 9 << 5 << 18;
			cf.nz << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 9;
			cf.py << 1 << 3;
			cf.pz << 1 << 0;
			cf.nx << 2 << 8;
			cf.ny << 5 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 9;
			cf.py << 21 << 3;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 5 << 5;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 9;
			cf.py << 7 << 11;
			cf.pz << 1 << -1;
			cf.nx << 2 << 2;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 4 << 3 << 1;
			cf.py << 14 << 21 << 19 << 6;
			cf.pz << 0 << 0 << 0 << 1;
			cf.nx << 10 << 16 << 4 << 5;
			cf.ny << 8 << 1 << 7 << 6;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 4 << 3 << 1;
			cf.py << 5 << 21 << 19 << 6;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 21 << 10 << 5 << 11;
			cf.ny << 4 << 2 << 3 << 4;
			cf.nz << 0 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 17;
			cf.py << 3 << 8;
			cf.pz << 2 << 0;
			cf.nx << 17 << 2;
			cf.ny << 9 << 22;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 12;
			cf.py << 14 << 20;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 12;
			cf.py << 9 << 20;
			cf.pz << 0 << -1;
			cf.nx << 11 << 23;
			cf.ny << 8 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 11;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 8 << 15;
			cf.ny << 7 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 15;
			cf.py << 13 << 8;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 6 << 7;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 15;
			cf.py << 14 << 8;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 12 << 13;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 0 << 1;
			cf.pz << 2 << 2;
			cf.nx << 15 << 4;
			cf.ny << 5 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 17;
			cf.py << 2 << 2;
			cf.pz << 0 << 0;
			cf.nx << 20 << 8;
			cf.ny << 3 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 3 << 2;
			cf.py << 10 << 6 << 1;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 3 << 2;
			cf.ny << 3 << 4 << 2;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 4 << 6;
			cf.pz << 0 << -1;
			cf.nx << 6 << 13;
			cf.ny << 0 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 8 << 2;
			cf.ny << 7 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 1;
			cf.py << 12 << 4;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 5 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 15;
			cf.py << 15 << 14;
			cf.pz << 0 << -1;
			cf.nx << 3 << 11;
			cf.ny << 4 << 13;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 9 << 11 << 14 << 12;
			cf.py << 0 << 2 << 0 << 0 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 5 << 4 << 4 << 3 << 4;
			cf.ny << 4 << 4 << 18 << 7 << 17;
			cf.nz << 1 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 12 << 11;
			cf.py << 22 << 22 << 22;
			cf.pz << 0 << 0 << 0;
			cf.nx << 11 << 12 << 13;
			cf.ny << 20 << 20 << 20;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 13;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 7 << 6;
			cf.ny << 8 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 23 << 4;
			cf.pz << 0 << -1;
			cf.nx << 5 << 9;
			cf.ny << 1 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 14;
			cf.py << 19 << 19;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 10 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 23;
			cf.py << 11 << 9;
			cf.pz << 0 << 0;
			cf.nx << 23 << 23;
			cf.ny << 0 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 3;
			cf.py << 23 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 1;
			cf.ny << 23 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 1;
			cf.py << 7 << 4;
			cf.pz << 1 << -1;
			cf.nx << 19 << 10;
			cf.ny << 20 << 9;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 1;
			cf.py << 9 << 4;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 3 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 13 << 13;
			cf.pz << 0 << 0;
			cf.nx << 4 << 5;
			cf.ny << 4 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 19 << 20 << 20 << 10 << 10;
			cf.py << 0 << 0 << 2 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 1 << 1;
			cf.nx << 7 << 7 << 15 << 4 << 4;
			cf.ny << 4 << 13 << 7 << 4 << 4;
			cf.nz << 1 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 23;
			cf.py << 6 << 5;
			cf.pz << 0 << -1;
			cf.nx << 18 << 18;
			cf.ny << 17 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 9 << 2;
			cf.pz << 1 << 2;
			cf.nx << 14 << 18;
			cf.ny << 9 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 13;
			cf.py << 16 << 5;
			cf.pz << 0 << -1;
			cf.nx << 5 << 4;
			cf.ny << 7 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 8 << 10;
			cf.pz << 1 << 1;
			cf.nx << 4 << 1;
			cf.ny << 5 << 3;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 11;
			cf.py << 13 << 4;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 14 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 20 << 17;
			cf.pz << 0 << 0;
			cf.nx << 12 << 12;
			cf.ny << 22 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 6 << 7;
			cf.pz << 1 << -1;
			cf.nx << 21 << 21;
			cf.ny << 13 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 10;
			cf.py << 4 << 23;
			cf.pz << 2 << 0;
			cf.nx << 10 << 2;
			cf.ny << 21 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 3 << 6;
			cf.pz << 1 << 0;
			cf.nx << 11 << 0;
			cf.ny << 17 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 21 << 9;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 18 << 22;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 5;
			cf.py << 18 << 9;
			cf.pz << 0 << -1;
			cf.nx << 6 << 7;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 4;
			cf.py << 16 << 3;
			cf.pz << 0 << -1;
			cf.nx << 23 << 23;
			cf.ny << 16 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 0;
			cf.py << 7 << 4;
			cf.pz << 1 << -1;
			cf.nx << 3 << 8;
			cf.ny << 7 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 16;
			cf.py << 11 << 12;
			cf.pz << 0 << 0;
			cf.nx << 8 << 5;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 7 << 5;
			cf.pz << 0 << 0;
			cf.nx << 17 << 17;
			cf.ny << 11 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 13 << 12 << 3 << 3;
			cf.py << 6 << 23 << 23 << 3 << 3;
			cf.pz << 1 << 0 << 0 << 2 << -1;
			cf.nx << 0 << 1 << 0 << 0 << 0;
			cf.ny << 2 << 13 << 4 << 5 << 6;
			cf.nz << 2 << 0 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 7 << 8;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 1 << 0;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 12;
			cf.py << 1 << 7;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 12 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 1;
			cf.py << 7 << 4;
			cf.pz << 1 << 2;
			cf.nx << 8 << 0;
			cf.ny << 15 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 14 << 8;
			cf.pz << 0 << -1;
			cf.nx << 2 << 4;
			cf.ny << 1 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 3 << 1;
			cf.pz << 2 << -1;
			cf.nx << 9 << 9;
			cf.ny << 5 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 2 << 3;
			cf.pz << 1 << -1;
			cf.nx << 11 << 12;
			cf.ny << 23 << 23;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 22 << 22;
			cf.ny << 19 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 2 << 9;
			cf.py << 20 << 9 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 1 << 10 << 11;
			cf.ny << 2 << 11 << 9;
			cf.nz << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 9 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 6;
			cf.py << 7 << 16;
			cf.pz << 0 << -1;
			cf.nx << 17 << 17;
			cf.ny << 9 << 6;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 1 << 9;
			cf.py << 6 << 3 << 4;
			cf.pz << 1 << -1 << -1;
			cf.nx << 2 << 9 << 2;
			cf.ny << 5 << 13 << 3;
			cf.nz << 2 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 10 << 10 << 9 << 2;
			cf.py << 12 << 11 << 2 << 10;
			cf.pz << 0 << 0 << -1 << -1;
			cf.nx << 6 << 11 << 3 << 13;
			cf.ny << 2 << 4 << 1 << 4;
			cf.nz << 1 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 4 << 8;
			cf.pz << 2 << 1;
			cf.nx << 4 << 4;
			cf.ny << 15 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 0;
			cf.py << 4 << 8;
			cf.pz << 1 << -1;
			cf.nx << 13 << 13;
			cf.ny << 9 << 10;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 8 << 17;
			cf.ny << 4 << 12;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 16;
			cf.py << 11 << 6;
			cf.pz << 0 << 0;
			cf.nx << 16 << 17;
			cf.ny << 5 << 12;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 11;
			cf.py << 9 << 7;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 9 << 20;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 11 << 20;
			cf.py << 4 << 7 << 23;
			cf.pz << 0 << -1 << -1;
			cf.nx << 8 << 9 << 4;
			cf.ny << 4 << 6 << 4;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 18 << 17;
			cf.pz << 0 << 0;
			cf.nx << 9 << 6;
			cf.ny << 7 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 4 << 19;
			cf.py << 3 << 2 << 9;
			cf.pz << 2 << 2 << 0;
			cf.nx << 2 << 14 << 11;
			cf.ny << 5 << 3 << 9;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 19;
			cf.py << 13 << 9;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 7;
			cf.py << 19 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 5;
			cf.ny << 6 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 4 << 4 << 2;
			cf.py << 13 << 9 << 8 << 4;
			cf.pz << 0 << 1 << 1 << 2;
			cf.nx << 13 << 0 << 0 << 14;
			cf.ny << 18 << 11 << 6 << 1;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 15;
			cf.py << 8 << 10;
			cf.pz << 0 << 0;
			cf.nx << 14 << 11;
			cf.ny << 9 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 8 << 5;
			cf.pz << 1 << 2;
			cf.nx << 4 << 4;
			cf.ny << 10 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 6 << 16 << 14;
			cf.py << 1 << 1 << 1 << 7;
			cf.pz << 2 << 1 << 0 << 0;
			cf.nx << 10 << 1 << 1 << 2;
			cf.ny << 8 << 5 << 10 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 3 << 1 << 2;
			cf.py << 3 << 1 << 0 << 2;
			cf.pz << 0 << 0 << 1 << 0;
			cf.nx << 0 << 0 << 0 << 0;
			cf.ny << 1 << 1 << 2 << 0;
			cf.nz << 0 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 6 << 7;
			cf.pz << 1 << 1;
			cf.nx << 8 << 0;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 3 << 0;
			cf.pz << 0 << 1;
			cf.nx << 2 << 2;
			cf.ny << 1 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 6;
			cf.py << 19 << 18;
			cf.pz << 0 << 0;
			cf.nx << 2 << 10;
			cf.ny << 5 << 8;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 5;
			cf.py << 21 << 11;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 11 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 9;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 8 << 7;
			cf.ny << 10 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 18 << 19 << 16 << 19;
			cf.py << 3 << 12 << 12 << 23 << 13;
			cf.pz << 2 << 0 << 0 << 0 << 0;
			cf.nx << 2 << 8 << 3 << 2 << 2;
			cf.ny << 4 << 23 << 10 << 5 << 5;
			cf.nz << 2 << 0 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 6 << 11;
			cf.pz << 1 << 0;
			cf.nx << 8 << 3;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 12;
			cf.py << 4 << 13;
			cf.pz << 2 << 0;
			cf.nx << 10 << 5;
			cf.ny << 15 << 21;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 9;
			cf.py << 4 << 23;
			cf.pz << 2 << 0;
			cf.nx << 19 << 4;
			cf.ny << 9 << 3;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 8 << 15;
			cf.pz << 1 << 0;
			cf.nx << 6 << 1;
			cf.ny << 18 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 0;
			cf.py << 20 << 3;
			cf.pz << 0 << -1;
			cf.nx << 2 << 10;
			cf.ny << 5 << 17;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 6 << 3;
			cf.py << 2 << 7 << 3;
			cf.pz << 0 << -1 << -1;
			cf.nx << 5 << 4 << 2;
			cf.ny << 9 << 7 << 2;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 6;
			cf.py << 12 << 7;
			cf.pz << 0 << -1;
			cf.nx << 2 << 10;
			cf.ny << 0 << 1;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 5 << 1;
			cf.py << 15 << 5 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 9 << 4 << 18;
			cf.ny << 2 << 0 << 4;
			cf.nz << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 2;
			cf.py << 12 << 6;
			cf.pz << 0 << -1;
			cf.nx << 8 << 16;
			cf.ny << 4 << 11;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 7 << 13 << 4;
			cf.py << 0 << 0 << 1;
			cf.pz << 1 << 0 << -1;
			cf.nx << 18 << 4 << 4;
			cf.ny << 13 << 2 << 3;
			cf.nz << 0 << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 11;
			cf.py << 10 << 6;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 15 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 9 << 12 << 8;
			cf.py << 8 << 17 << 11;
			cf.pz << 1 << 0 << 1;
			cf.nx << 12 << 0 << 20;
			cf.ny << 16 << 9 << 13;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 5 << 8;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 3;
			cf.py << 9 << 8;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 11 << 5;
			cf.pz << 1 << 2;
			cf.nx << 11 << 5;
			cf.ny << 21 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 13;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 4 << 4;
			cf.ny << 5 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 4;
			cf.py << 4 << 3;
			cf.pz << 0 << -1;
			cf.nx << 12 << 10;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 9 << 7;
			cf.ny << 9 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 6 << 6;
			cf.py << 4 << 4 << 4;
			cf.pz << 1 << -1 << -1;
			cf.nx << 13 << 8 << 7;
			cf.ny << 8 << 3 << 4;
			cf.nz << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 2 << 11;
			cf.pz << 1 << 1;
			cf.nx << 10 << 11;
			cf.ny << 22 << 22;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 9;
			cf.py << 13 << 7;
			cf.pz << 0 << 1;
			cf.nx << 8 << 14;
			cf.ny << 4 << 12;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 5;
			cf.py << 13 << 3;
			cf.pz << 0 << 2;
			cf.nx << 16 << 22;
			cf.ny << 13 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 4 << 3 << 4;
			cf.py << 4 << 3 << 4 << 5;
			cf.pz << 2 << 2 << 2 << 2;
			cf.nx << 21 << 5 << 17 << 7;
			cf.ny << 0 << 2 << 5 << 23;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 16;
			cf.py << 0 << 1;
			cf.pz << 2 << 0;
			cf.nx << 15 << 1;
			cf.ny << 23 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 6;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 15 << 6;
			cf.ny << 2 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 14 << 5;
			cf.py << 9 << 15 << 2;
			cf.pz << 0 << -1 << -1;
			cf.nx << 11 << 1 << 11;
			cf.ny << 10 << 3 << 11;
			cf.nz << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 1;
			cf.py << 6 << 2;
			cf.pz << 1 << -1;
			cf.nx << 1 << 1;
			cf.ny << 2 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 1 << 0;
			cf.pz << 1 << 2;
			cf.nx << 10 << 4;
			cf.ny << 2 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 8 << 9;
			cf.pz << 1 << 1;
			cf.nx << 23 << 4;
			cf.ny << 23 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 10 << 2;
			cf.pz << 0 << -1;
			cf.nx << 18 << 10;
			cf.ny << 0 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 4;
			cf.py << 7 << 3;
			cf.pz << 0 << 2;
			cf.nx << 8 << 4;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 5 << 4;
			cf.pz << 1 << -1;
			cf.nx << 11 << 11;
			cf.ny << 5 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 14 << 15 << 16;
			cf.py << 0 << 0 << 1;
			cf.pz << 0 << 0 << 0;
			cf.nx << 8 << 5 << 15;
			cf.ny << 7 << 2 << 10;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 1 << 1;
			cf.pz << 2 << -1;
			cf.nx << 17 << 18;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 8;
			cf.py << 15 << 7;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 5 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 0;
			cf.py << 6 << 17;
			cf.pz << 1 << -1;
			cf.nx << 3 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 8;
			cf.py << 17 << 9;
			cf.pz << 0 << -1;
			cf.nx << 7 << 6;
			cf.ny << 8 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 15 << 6;
			cf.ny << 14 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 12;
			cf.py << 8 << 19;
			cf.pz << 1 << 0;
			cf.nx << 13 << 10;
			cf.ny << 17 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 12;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 6 << 11;
			cf.ny << 3 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 1 << 6 << 1;
			cf.py << 10 << 3 << 23 << 8;
			cf.pz << 1 << 2 << 0 << 1;
			cf.nx << 17 << 10 << 23 << 0;
			cf.ny << 9 << 2 << 20 << 3;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 2 << 8;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 4 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 16;
			cf.py << 1 << 6;
			cf.pz << 2 << 0;
			cf.nx << 8 << 4;
			cf.ny << 2 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 3 << 0;
			cf.pz << 2 << -1;
			cf.nx << 9 << 5;
			cf.ny << 2 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 16;
			cf.py << 5 << 23;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 6 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 0 << 0 << 0 << 0;
			cf.py << 3 << 2 << 12 << 5;
			cf.pz << 2 << 2 << 0 << 1;
			cf.nx << 2 << 3 << 2 << 13;
			cf.ny << 5 << 5 << 2 << 19;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 10 << 11;
			cf.pz << 0 << 0;
			cf.nx << 5 << 5;
			cf.ny << 1 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 0 << 4;
			cf.pz << 2 << -1;
			cf.nx << 2 << 2;
			cf.ny << 10 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 16 << 2 << 8 << 4;
			cf.py << 14 << 0 << 11 << 5;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 18 << 14 << 7 << 7;
			cf.ny << 13 << 14 << 8 << 6;
			cf.nz << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 2 << 2;
			cf.pz << 0 << 0;
			cf.nx << 5 << 14;
			cf.ny << 4 << 14;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 5;
			cf.py << 11 << 20;
			cf.pz << 1 << 0;
			cf.nx << 11 << 4;
			cf.ny << 0 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 3 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 4 << 3;
			cf.py << 5 << 5 << 3;
			cf.pz << 0 << -1 << -1;
			cf.nx << 11 << 3 << 10;
			cf.ny << 2 << 0 << 2;
			cf.nz << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 15;
			cf.py << 1 << 1;
			cf.pz << 0 << -1;
			cf.nx << 7 << 4;
			cf.ny << 5 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 5 << 2 << 6;
			cf.py << 22 << 8 << 4 << 19;
			cf.pz << 0 << 1 << 2 << 0;
			cf.nx << 9 << 5 << 0 << 3;
			cf.ny << 20 << 5 << 22 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 4 << 10;
			cf.py << 3 << 9 << 12;
			cf.pz << 2 << 1 << 0;
			cf.nx << 0 << 10 << 0;
			cf.ny << 0 << 5 << 0;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 6;
			cf.py << 0 << 7;
			cf.pz << 0 << -1;
			cf.nx << 20 << 19;
			cf.ny << 14 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 14 << 15;
			cf.pz << 0 << -1;
			cf.nx << 2 << 1;
			cf.ny << 5 << 7;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 7;
			cf.py << 9 << 11;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 9;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 15 << 10;
			cf.ny << 9 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 0 << 1;
			cf.pz << 2 << 2;
			cf.nx << 9 << 7;
			cf.ny << 6 << 17;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 3 << 15;
			cf.py << 3 << 4 << 6;
			cf.pz << 2 << 1 << 0;
			cf.nx << 0 << 2 << 22;
			cf.ny << 5 << 8 << 9;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 15 << 15 << 15 << 1;
			cf.py << 12 << 6 << 6 << 1;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 4 << 7 << 13 << 4;
			cf.ny << 4 << 7 << 12 << 2;
			cf.nz << 2 << 1 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 15;
			cf.py << 12 << 6;
			cf.pz << 0 << -1;
			cf.nx << 9 << 1;
			cf.ny << 14 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 12;
			cf.py << 11 << 12;
			cf.pz << 0 << 0;
			cf.nx << 9 << 5;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 23 << 6 << 7;
			cf.py << 23 << 3 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 19 << 16 << 17;
			cf.ny << 17 << 14 << 15;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 2 << 7;
			cf.pz << 1 << -1;
			cf.nx << 11 << 23;
			cf.ny << 10 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 0 << 0;
			cf.py << 4 << 9 << 2;
			cf.pz << 1 << 0 << 2;
			cf.nx << 2 << 0 << 0;
			cf.ny << 9 << 2 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 0;
			cf.py << 11 << 9;
			cf.pz << 0 << -1;
			cf.nx << 1 << 0;
			cf.ny << 18 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 10 << 6;
			cf.pz << 0 << 1;
			cf.nx << 10 << 6;
			cf.ny << 10 << 18;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 12;
			cf.py << 13 << 13;
			cf.pz << 0 << -1;
			cf.nx << 5 << 11;
			cf.ny << 1 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 19;
			cf.py << 5 << 22;
			cf.pz << 1 << -1;
			cf.nx << 4 << 12;
			cf.ny << 1 << 5;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 6;
			cf.py << 0 << 0;
			cf.pz << 0 << 0;
			cf.nx << 3 << 12;
			cf.ny << 0 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 6;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 12 << 12;
			cf.ny << 10 << 11;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 1 << 3 << 2;
			cf.py << 20 << 9 << 21 << 19;
			cf.pz << 0 << 1 << 0 << 0;
			cf.nx << 20 << 20 << 5 << 12;
			cf.ny << 10 << 15 << 2 << 10;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 1;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 11 << 11;
			cf.py << 1 << 3 << 4;
			cf.pz << 2 << 1 << 1;
			cf.nx << 3 << 3 << 7;
			cf.ny << 5 << 5 << 0;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 6 << 7;
			cf.py << 10 << 5 << 6;
			cf.pz << 1 << 1 << 1;
			cf.nx << 23 << 3 << 7;
			cf.ny << 0 << 5 << 0;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 2 << 14;
			cf.pz << 1 << -1;
			cf.nx << 7 << 3;
			cf.ny << 12 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 13 << 3;
			cf.ny << 12 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 18;
			cf.py << 11 << 4;
			cf.pz << 0 << -1;
			cf.nx << 23 << 11;
			cf.ny << 19 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 12 << 3;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 11 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 0 << 11;
			cf.pz << 1 << -1;
			cf.nx << 3 << 3;
			cf.ny << 19 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 11 << 11;
			cf.pz << 1 << -1;
			cf.nx << 13 << 15;
			cf.ny << 6 << 5;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 9 << 9;
			cf.pz << 0 << -1;
			cf.nx << 5 << 11;
			cf.ny << 1 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 4 << 8 << 3;
			cf.py << 6 << 2 << 4 << 3;
			cf.pz << 0 << 2 << 1 << 2;
			cf.nx << 7 << 0 << 15 << 8;
			cf.ny << 8 << 8 << 16 << 7;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 22 << 20;
			cf.pz << 0 << 0;
			cf.nx << 2 << 8;
			cf.ny << 5 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 11 << 0;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 3 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 12 << 7;
			cf.pz << 0 << 1;
			cf.nx << 3 << 1;
			cf.ny << 23 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 11 << 5;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 10 << 10;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 5 << 4;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 2 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 3 << 5;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 23 << 22;
			cf.pz << 0 << 0;
			cf.nx << 9 << 0;
			cf.ny << 7 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 16 << 15;
			cf.pz << 0 << 0;
			cf.nx << 0 << 14;
			cf.ny << 23 << 12;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 8;
			cf.py << 22 << 0;
			cf.pz << 0 << -1;
			cf.nx << 5 << 3;
			cf.ny << 0 << 1;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 13;
			cf.py << 7 << 7;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 17 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 20;
			cf.py << 15 << 16;
			cf.pz << 0 << 0;
			cf.nx << 7 << 3;
			cf.ny << 9 << 17;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 12 << 11 << 13 << 11;
			cf.py << 2 << 2 << 1 << 2 << 2;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 10 << 18 << 21 << 21 << 19;
			cf.ny << 3 << 1 << 13 << 11 << 2;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 3;
			cf.py << 6 << 1;
			cf.pz << 0 << 2;
			cf.nx << 15 << 18;
			cf.ny << 8 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 3;
			cf.py << 8 << 1;
			cf.pz << 0 << -1;
			cf.nx << 9 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 15 << 18;
			cf.pz << 0 << -1;
			cf.nx << 3 << 3;
			cf.ny << 0 << 1;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 2 << 3;
			cf.pz << 2 << 2;
			cf.nx << 7 << 3;
			cf.ny << 11 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 17 << 9;
			cf.pz << 0 << -1;
			cf.nx << 11 << 10;
			cf.ny << 15 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 10;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 3 << 4;
			cf.pz << 0 << -1;
			cf.nx << 9 << 10;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 11;
			cf.py << 13 << 10;
			cf.pz << 0 << 1;
			cf.nx << 14 << 7;
			cf.ny << 5 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 5 << 4;
			cf.pz << 2 << 2;
			cf.nx << 9 << 8;
			cf.ny << 3 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 4 << 15;
			cf.py << 5 << 4 << 7;
			cf.pz << 0 << -1 << -1;
			cf.nx << 3 << 4 << 2;
			cf.ny << 7 << 11 << 5;
			cf.nz << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 15 << 4;
			cf.pz << 0 << -1;
			cf.nx << 5 << 9;
			cf.ny << 7 << 15;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 7;
			cf.py << 0 << 1;
			cf.pz << 1 << -1;
			cf.nx << 11 << 11;
			cf.ny << 8 << 7;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 1 << 1 << 1;
			cf.py << 11 << 12 << 10 << 9 << 9;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 5 << 8 << 16 << 11;
			cf.ny << 4 << 3 << 8 << 8 << 6;
			cf.nz << 1 << 1 << 0 << 0 << 0;
		}
		*a_iter++ = -1.059083;
		*a_iter++ = 1.059083;
		*a_iter++ = -0.7846122;
		*a_iter++ = 0.7846122;
		*a_iter++ = -0.445116;
		*a_iter++ = 0.445116;
		*a_iter++ = -0.4483277;
		*a_iter++ = 0.4483277;
		*a_iter++ = -0.3905999;
		*a_iter++ = 0.3905999;
		*a_iter++ = -0.378925;
		*a_iter++ = 0.378925;
		*a_iter++ = -0.387461;
		*a_iter++ = 0.387461;
		*a_iter++ = -0.3110541;
		*a_iter++ = 0.3110541;
		*a_iter++ = -0.3565056;
		*a_iter++ = 0.3565056;
		*a_iter++ = -0.3812617;
		*a_iter++ = 0.3812617;
		*a_iter++ = -0.3325142;
		*a_iter++ = 0.3325142;
		*a_iter++ = -0.2787282;
		*a_iter++ = 0.2787282;
		*a_iter++ = -0.3238869;
		*a_iter++ = 0.3238869;
		*a_iter++ = -0.2993499;
		*a_iter++ = 0.2993499;
		*a_iter++ = -0.2807737;
		*a_iter++ = 0.2807737;
		*a_iter++ = -0.2855285;
		*a_iter++ = 0.2855285;
		*a_iter++ = -0.227755;
		*a_iter++ = 0.227755;
		*a_iter++ = -0.2031261;
		*a_iter++ = 0.2031261;
		*a_iter++ = -0.2071574;
		*a_iter++ = 0.2071574;
		*a_iter++ = -0.2534142;
		*a_iter++ = 0.2534142;
		*a_iter++ = -0.2266871;
		*a_iter++ = 0.2266871;
		*a_iter++ = -0.2229078;
		*a_iter++ = 0.2229078;
		*a_iter++ = -0.2716325;
		*a_iter++ = 0.2716325;
		*a_iter++ = -0.3046938;
		*a_iter++ = 0.3046938;
		*a_iter++ = -0.2271601;
		*a_iter++ = 0.2271601;
		*a_iter++ = -0.1987651;
		*a_iter++ = 0.1987651;
		*a_iter++ = -0.1953664;
		*a_iter++ = 0.1953664;
		*a_iter++ = -0.2178737;
		*a_iter++ = 0.2178737;
		*a_iter++ = -0.2285148;
		*a_iter++ = 0.2285148;
		*a_iter++ = -0.1891073;
		*a_iter++ = 0.1891073;
		*a_iter++ = -0.2926469;
		*a_iter++ = 0.2926469;
		*a_iter++ = -0.2094783;
		*a_iter++ = 0.2094783;
		*a_iter++ = -0.1478037;
		*a_iter++ = 0.1478037;
		*a_iter++ = -0.1707579;
		*a_iter++ = 0.1707579;
		*a_iter++ = -0.146439;
		*a_iter++ = 0.146439;
		*a_iter++ = -0.2462321;
		*a_iter++ = 0.2462321;
		*a_iter++ = -0.2319978;
		*a_iter++ = 0.2319978;
		*a_iter++ = -0.1781651;
		*a_iter++ = 0.1781651;
		*a_iter++ = -0.1471349;
		*a_iter++ = 0.1471349;
		*a_iter++ = -0.1953006;
		*a_iter++ = 0.1953006;
		*a_iter++ = -0.2145108;
		*a_iter++ = 0.2145108;
		*a_iter++ = -0.1567881;
		*a_iter++ = 0.1567881;
		*a_iter++ = -0.2024617;
		*a_iter++ = 0.2024617;
		*a_iter++ = -0.1883198;
		*a_iter++ = 0.1883198;
		*a_iter++ = -0.1996976;
		*a_iter++ = 0.1996976;
		*a_iter++ = -0.129233;
		*a_iter++ = 0.129233;
		*a_iter++ = -0.2142242;
		*a_iter++ = 0.2142242;
		*a_iter++ = -0.2473748;
		*a_iter++ = 0.2473748;
		*a_iter++ = -0.1880902;
		*a_iter++ = 0.1880902;
		*a_iter++ = -0.1874572;
		*a_iter++ = 0.1874572;
		*a_iter++ = -0.1495984;
		*a_iter++ = 0.1495984;
		*a_iter++ = -0.1608525;
		*a_iter++ = 0.1608525;
		*a_iter++ = -0.1698402;
		*a_iter++ = 0.1698402;
		*a_iter++ = -0.1898871;
		*a_iter++ = 0.1898871;
		*a_iter++ = -0.1350238;
		*a_iter++ = 0.1350238;
		*a_iter++ = -0.1727032;
		*a_iter++ = 0.1727032;
		*a_iter++ = -0.1593352;
		*a_iter++ = 0.1593352;
		*a_iter++ = -0.1476968;
		*a_iter++ = 0.1476968;
		*a_iter++ = -0.1428431;
		*a_iter++ = 0.1428431;
		*a_iter++ = -0.1766261;
		*a_iter++ = 0.1766261;
		*a_iter++ = -0.1453226;
		*a_iter++ = 0.1453226;
		*a_iter++ = -0.1929885;
		*a_iter++ = 0.1929885;
		*a_iter++ = -0.1337582;
		*a_iter++ = 0.1337582;
		*a_iter++ = -0.1629078;
		*a_iter++ = 0.1629078;
		*a_iter++ = -0.09973085;
		*a_iter++ = 0.09973085;
		*a_iter++ = -0.117276;
		*a_iter++ = 0.117276;
		*a_iter++ = -0.1399242;
		*a_iter++ = 0.1399242;
		*a_iter++ = -0.1613189;
		*a_iter++ = 0.1613189;
		*a_iter++ = -0.1145695;
		*a_iter++ = 0.1145695;
		*a_iter++ = -0.1191093;
		*a_iter++ = 0.1191093;
		*a_iter++ = -0.12259;
		*a_iter++ = 0.12259;
		*a_iter++ = -0.1641114;
		*a_iter++ = 0.1641114;
		*a_iter++ = -0.1419878;
		*a_iter++ = 0.1419878;
		*a_iter++ = -0.2183465;
		*a_iter++ = 0.2183465;
		*a_iter++ = -0.1566968;
		*a_iter++ = 0.1566968;
		*a_iter++ = -0.1288216;
		*a_iter++ = 0.1288216;
		*a_iter++ = -0.1422831;
		*a_iter++ = 0.1422831;
		*a_iter++ = -0.2000107;
		*a_iter++ = 0.2000107;
		*a_iter++ = -0.1817265;
		*a_iter++ = 0.1817265;
		*a_iter++ = -0.1793796;
		*a_iter++ = 0.1793796;
		*a_iter++ = -0.1428926;
		*a_iter++ = 0.1428926;
		*a_iter++ = -0.1182032;
		*a_iter++ = 0.1182032;
		*a_iter++ = -0.1150421;
		*a_iter++ = 0.1150421;
		*a_iter++ = -0.1336584;
		*a_iter++ = 0.1336584;
		*a_iter++ = -0.1656178;
		*a_iter++ = 0.1656178;
		*a_iter++ = -0.1386549;
		*a_iter++ = 0.1386549;
		*a_iter++ = -0.1387461;
		*a_iter++ = 0.1387461;
		*a_iter++ = -0.1313023;
		*a_iter++ = 0.1313023;
		*a_iter++ = -0.1360391;
		*a_iter++ = 0.1360391;
		*a_iter++ = -0.1305505;
		*a_iter++ = 0.1305505;
		*a_iter++ = -0.1323399;
		*a_iter++ = 0.1323399;
		*a_iter++ = -0.1502891;
		*a_iter++ = 0.1502891;
		*a_iter++ = -0.1488859;
		*a_iter++ = 0.1488859;
		*a_iter++ = -0.1126628;
		*a_iter++ = 0.1126628;
		*a_iter++ = -0.1233623;
		*a_iter++ = 0.1233623;
		*a_iter++ = -0.1702106;
		*a_iter++ = 0.1702106;
		*a_iter++ = -0.1629639;
		*a_iter++ = 0.1629639;
		*a_iter++ = -0.1337706;
		*a_iter++ = 0.1337706;
		*a_iter++ = -0.1290384;
		*a_iter++ = 0.1290384;
		*a_iter++ = -0.1165519;
		*a_iter++ = 0.1165519;
		*a_iter++ = -0.1412778;
		*a_iter++ = 0.1412778;
		*a_iter++ = -0.1470204;
		*a_iter++ = 0.1470204;
		*a_iter++ = -0.221378;
		*a_iter++ = 0.221378;
		*a_iter++ = -0.1472619;
		*a_iter++ = 0.1472619;
		*a_iter++ = -0.1357071;
		*a_iter++ = 0.1357071;
		*a_iter++ = -0.1416513;
		*a_iter++ = 0.1416513;
		*a_iter++ = -0.1050208;
		*a_iter++ = 0.1050208;
		*a_iter++ = -0.1480033;
		*a_iter++ = 0.1480033;
		*a_iter++ = -0.1899871;
		*a_iter++ = 0.1899871;
		*a_iter++ = -0.1466249;
		*a_iter++ = 0.1466249;
		*a_iter++ = -0.1076952;
		*a_iter++ = 0.1076952;
		*a_iter++ = -0.1035096;
		*a_iter++ = 0.1035096;
		*a_iter++ = -0.156697;
		*a_iter++ = 0.156697;
		*a_iter++ = -0.1364115;
		*a_iter++ = 0.1364115;
		*a_iter++ = -0.1512889;
		*a_iter++ = 0.1512889;
		*a_iter++ = -0.1252851;
		*a_iter++ = 0.1252851;
		*a_iter++ = -0.12063;
		*a_iter++ = 0.12063;
		*a_iter++ = -0.1059134;
		*a_iter++ = 0.1059134;
		*a_iter++ = -0.1140398;
		*a_iter++ = 0.1140398;
		*a_iter++ = -0.1359912;
		*a_iter++ = 0.1359912;
		*a_iter++ = -0.1231201;
		*a_iter++ = 0.1231201;
		*a_iter++ = -0.1231867;
		*a_iter++ = 0.1231867;
		*a_iter++ = -0.09789923;
		*a_iter++ = 0.09789923;
		*a_iter++ = -0.1590213;
		*a_iter++ = 0.1590213;
		*a_iter++ = -0.1002206;
		*a_iter++ = 0.1002206;
		*a_iter++ = -0.1518339;
		*a_iter++ = 0.1518339;
		*a_iter++ = -0.1055203;
		*a_iter++ = 0.1055203;
		*a_iter++ = -0.1012579;
		*a_iter++ = 0.1012579;
		*a_iter++ = -0.1094956;
		*a_iter++ = 0.1094956;
		*a_iter++ = -0.1429592;
		*a_iter++ = 0.1429592;
		*a_iter++ = -0.1108838;
		*a_iter++ = 0.1108838;
		*a_iter++ = -0.1116475;
		*a_iter++ = 0.1116475;
		*a_iter++ = -0.1735371;
		*a_iter++ = 0.1735371;
		*a_iter++ = -0.1067758;
		*a_iter++ = 0.1067758;
		*a_iter++ = -0.1290406;
		*a_iter++ = 0.1290406;
		*a_iter++ = -0.1156822;
		*a_iter++ = 0.1156822;
		*a_iter++ = -0.09668217;
		*a_iter++ = 0.09668217;
		*a_iter++ = -0.1170053;
		*a_iter++ = 0.1170053;
		*a_iter++ = -0.1252092;
		*a_iter++ = 0.1252092;
		*a_iter++ = -0.1135158;
		*a_iter++ = 0.1135158;
		*a_iter++ = -0.1105896;
		*a_iter++ = 0.1105896;
		*a_iter++ = -0.1038175;
		*a_iter++ = 0.1038175;
		*a_iter++ = -0.1210459;
		*a_iter++ = 0.1210459;
		*a_iter++ = -0.1078878;
		*a_iter++ = 0.1078878;
		*a_iter++ = -0.1050808;
		*a_iter++ = 0.1050808;
		*a_iter++ = -0.1428227;
		*a_iter++ = 0.1428227;
		*a_iter++ = -0.16646;
		*a_iter++ = 0.16646;
		*a_iter++ = -0.1013508;
		*a_iter++ = 0.1013508;
		*a_iter++ = -0.120693;
		*a_iter++ = 0.120693;
		*a_iter++ = -0.1088972;
		*a_iter++ = 0.1088972;
		*a_iter++ = -0.1381026;
		*a_iter++ = 0.1381026;
		*a_iter++ = -0.1109115;
		*a_iter++ = 0.1109115;
		*a_iter++ = -0.07921549;
		*a_iter++ = 0.07921549;
		*a_iter++ = -0.1057832;
		*a_iter++ = 0.1057832;
		*a_iter++ = -0.09385827;
		*a_iter++ = 0.09385827;
		*a_iter++ = -0.1486035;
		*a_iter++ = 0.1486035;
		*a_iter++ = -0.1247401;
		*a_iter++ = 0.1247401;
		*a_iter++ = -0.09451327;
		*a_iter++ = 0.09451327;
		*a_iter++ = -0.1272805;
		*a_iter++ = 0.1272805;
		*a_iter++ = -0.09616206;
		*a_iter++ = 0.09616206;
		*a_iter++ = -0.09051084;
		*a_iter++ = 0.09051084;
		*a_iter++ = -0.1138458;
		*a_iter++ = 0.1138458;
		*a_iter++ = -0.1047581;
		*a_iter++ = 0.1047581;
		*a_iter++ = -0.1382394;
		*a_iter++ = 0.1382394;
		*a_iter++ = -0.1122203;
		*a_iter++ = 0.1122203;
		*a_iter++ = -0.1052936;
		*a_iter++ = 0.1052936;
		*a_iter++ = -0.1239318;
		*a_iter++ = 0.1239318;
		*a_iter++ = -0.1241439;
		*a_iter++ = 0.1241439;
		*a_iter++ = -0.1259012;
		*a_iter++ = 0.1259012;
		*a_iter++ = -0.1211701;
		*a_iter++ = 0.1211701;
		*a_iter++ = -0.1344131;
		*a_iter++ = 0.1344131;
		*a_iter++ = -0.1127778;
		*a_iter++ = 0.1127778;
		*a_iter++ = -0.1609745;
		*a_iter++ = 0.1609745;
		*a_iter++ = -0.1901382;
		*a_iter++ = 0.1901382;
		*a_iter++ = -0.1618962;
		*a_iter++ = 0.1618962;
		*a_iter++ = -0.1230398;
		*a_iter++ = 0.1230398;
		*a_iter++ = -0.1319311;
		*a_iter++ = 0.1319311;
		*a_iter++ = -0.143141;
		*a_iter++ = 0.143141;
		*a_iter++ = -0.1143306;
		*a_iter++ = 0.1143306;
		*a_iter++ = -0.09390938;
		*a_iter++ = 0.09390938;
		*a_iter++ = -0.1154161;
		*a_iter++ = 0.1154161;
		*a_iter++ = -0.1141205;
		*a_iter++ = 0.1141205;
		*a_iter++ = -0.1098048;
		*a_iter++ = 0.1098048;
		*a_iter++ = -0.08870072;
		*a_iter++ = 0.08870072;
		*a_iter++ = -0.1122444;
		*a_iter++ = 0.1122444;
		*a_iter++ = -0.1114147;
		*a_iter++ = 0.1114147;
		*a_iter++ = -0.118571;
		*a_iter++ = 0.118571;
		*a_iter++ = -0.1107775;
		*a_iter++ = 0.1107775;
		*a_iter++ = -0.1259167;
		*a_iter++ = 0.1259167;
		*a_iter++ = -0.1105176;
		*a_iter++ = 0.1105176;
		*a_iter++ = -0.1020691;
		*a_iter++ = 0.1020691;
		*a_iter++ = -0.09607863;
		*a_iter++ = 0.09607863;
		*a_iter++ = -0.095737;
		*a_iter++ = 0.095737;
		*a_iter++ = -0.1054349;
		*a_iter++ = 0.1054349;
		*a_iter++ = -0.1137856;
		*a_iter++ = 0.1137856;
		*a_iter++ = -0.1192043;
		*a_iter++ = 0.1192043;
		*a_iter++ = -0.1113264;
		*a_iter++ = 0.1113264;
		*a_iter++ = -0.1093137;
		*a_iter++ = 0.1093137;
		*a_iter++ = -0.1010919;
		*a_iter++ = 0.1010919;
		*a_iter++ = -0.09625901;
		*a_iter++ = 0.09625901;
		*a_iter++ = -0.09338459;
		*a_iter++ = 0.09338459;
		*a_iter++ = -0.1142944;
		*a_iter++ = 0.1142944;
		*a_iter++ = -0.1038877;
		*a_iter++ = 0.1038877;
		*a_iter++ = -0.09772862;
		*a_iter++ = 0.09772862;
		*a_iter++ = -0.1375298;
		*a_iter++ = 0.1375298;
		*a_iter++ = -0.1394776;
		*a_iter++ = 0.1394776;
		*a_iter++ = -0.09454765;
		*a_iter++ = 0.09454765;
		*a_iter++ = -0.1203246;
		*a_iter++ = 0.1203246;
		*a_iter++ = -0.08684943;
		*a_iter++ = 0.08684943;
		*a_iter++ = -0.1135622;
		*a_iter++ = 0.1135622;
		*a_iter++ = -0.1058181;
		*a_iter++ = 0.1058181;
		*a_iter++ = -0.1082152;
		*a_iter++ = 0.1082152;
		*a_iter++ = -0.1411355;
		*a_iter++ = 0.1411355;
		*a_iter++ = -0.09978846;
		*a_iter++ = 0.09978846;
		*a_iter++ = -0.1057874;
		*a_iter++ = 0.1057874;
		*a_iter++ = -0.1415366;
		*a_iter++ = 0.1415366;
		*a_iter++ = -0.09981014;
		*a_iter++ = 0.09981014;
		*a_iter++ = -0.09261151;
		*a_iter++ = 0.09261151;
		*a_iter++ = -0.1737173;
		*a_iter++ = 0.1737173;
		*a_iter++ = -0.1580335;
		*a_iter++ = 0.1580335;
		*a_iter++ = -0.09594668;
		*a_iter++ = 0.09594668;
		*a_iter++ = -0.09336013;
		*a_iter++ = 0.09336013;
		*a_iter++ = -0.1102373;
		*a_iter++ = 0.1102373;
		*a_iter++ = -0.08546557;
		*a_iter++ = 0.08546557;
		*a_iter++ = -0.09945057;
		*a_iter++ = 0.09945057;
		*a_iter++ = -0.1146358;
		*a_iter++ = 0.1146358;
		*a_iter++ = -0.1324734;
		*a_iter++ = 0.1324734;
		*a_iter++ = -0.1422296;
		*a_iter++ = 0.1422296;
		*a_iter++ = -0.0993799;
		*a_iter++ = 0.0993799;
		*a_iter++ = -0.08381049;
		*a_iter++ = 0.08381049;
		*a_iter++ = -0.1270714;
		*a_iter++ = 0.1270714;
		*a_iter++ = -0.1091738;
		*a_iter++ = 0.1091738;
		*a_iter++ = -0.1314881;
		*a_iter++ = 0.1314881;
		*a_iter++ = -0.1085159;
		*a_iter++ = 0.1085159;
		*a_iter++ = -0.09247554;
		*a_iter++ = 0.09247554;
		*a_iter++ = -0.08121645;
		*a_iter++ = 0.08121645;
		*a_iter++ = -0.1059589;
		*a_iter++ = 0.1059589;
		*a_iter++ = -0.08307793;
		*a_iter++ = 0.08307793;
		*a_iter++ = -0.1033103;
		*a_iter++ = 0.1033103;
		*a_iter++ = -0.1056706;
		*a_iter++ = 0.1056706;
		*a_iter++ = -0.1032803;
		*a_iter++ = 0.1032803;
		*a_iter++ = -0.126684;
		*a_iter++ = 0.126684;
		*a_iter++ = -0.09341601;
		*a_iter++ = 0.09341601;
		*a_iter++ = -0.0768357;
		*a_iter++ = 0.0768357;
		*a_iter++ = -0.103053;
		*a_iter++ = 0.103053;
		*a_iter++ = -0.1051872;
		*a_iter++ = 0.1051872;
		*a_iter++ = -0.09114946;
		*a_iter++ = 0.09114946;
		*a_iter++ = -0.1329341;
		*a_iter++ = 0.1329341;
		*a_iter++ = -0.0927083;
		*a_iter++ = 0.0927083;
		*a_iter++ = -0.114175;
		*a_iter++ = 0.114175;
		*a_iter++ = -0.09889318;
		*a_iter++ = 0.09889318;
		*a_iter++ = -0.08856485;
		*a_iter++ = 0.08856485;
		*a_iter++ = -0.105421;
		*a_iter++ = 0.105421;
		*a_iter++ = -0.1092704;
		*a_iter++ = 0.1092704;
		*a_iter++ = -0.08729085;
		*a_iter++ = 0.08729085;
		*a_iter++ = -0.1141057;
		*a_iter++ = 0.1141057;
		*a_iter++ = -0.1530774;
		*a_iter++ = 0.1530774;
		*a_iter++ = -0.0812972;
		*a_iter++ = 0.0812972;
		*a_iter++ = -0.1143335;
		*a_iter++ = 0.1143335;
		*a_iter++ = -0.1175777;
		*a_iter++ = 0.1175777;
		*a_iter++ = -0.1371729;
		*a_iter++ = 0.1371729;
		*a_iter++ = -0.1394356;
		*a_iter++ = 0.1394356;
		*a_iter++ = -0.1016308;
		*a_iter++ = 0.1016308;
		*a_iter++ = -0.1125547;
		*a_iter++ = 0.1125547;
		*a_iter++ = -0.096726;
		*a_iter++ = 0.096726;
		*a_iter++ = -0.1036631;
		*a_iter++ = 0.1036631;
		*a_iter++ = -0.08702514;
		*a_iter++ = 0.08702514;
		*a_iter++ = -0.1264807;
		*a_iter++ = 0.1264807;
		*a_iter++ = -0.1465688;
		*a_iter++ = 0.1465688;
		*a_iter++ = -0.08781464;
		*a_iter++ = 0.08781464;
		*a_iter++ = -0.08552605;
		*a_iter++ = 0.08552605;
		*a_iter++ = -0.1145072;
		*a_iter++ = 0.1145072;
		*a_iter++ = -0.1378489;
		*a_iter++ = 0.1378489;
		*a_iter++ = -0.1013312;
		*a_iter++ = 0.1013312;
		*a_iter++ = -0.1020083;
		*a_iter++ = 0.1020083;
		*a_iter++ = -0.1015816;
		*a_iter++ = 0.1015816;
		*a_iter++ = -0.08407101;
		*a_iter++ = 0.08407101;
		*a_iter++ = -0.08296485;
		*a_iter++ = 0.08296485;
		*a_iter++ = -0.08033655;
		*a_iter++ = 0.08033655;
		*a_iter++ = -0.09003615;
		*a_iter++ = 0.09003615;
		*a_iter++ = -0.07504954;
		*a_iter++ = 0.07504954;
		*a_iter++ = -0.1224941;
		*a_iter++ = 0.1224941;
		*a_iter++ = -0.09347814;
		*a_iter++ = 0.09347814;
		*a_iter++ = -0.09555575;
		*a_iter++ = 0.09555575;
		*a_iter++ = -0.09810025;
		*a_iter++ = 0.09810025;
		*a_iter++ = -0.1237068;
		*a_iter++ = 0.1237068;
		*a_iter++ = -0.1283586;
		*a_iter++ = 0.1283586;
		*a_iter++ = -0.1082763;
		*a_iter++ = 0.1082763;
		*a_iter++ = -0.1018145;
		*a_iter++ = 0.1018145;
		*a_iter++ = -0.1175161;
		*a_iter++ = 0.1175161;
		*a_iter++ = -0.1252279;
		*a_iter++ = 0.1252279;
		*a_iter++ = -0.1370559;
		*a_iter++ = 0.1370559;
		*a_iter++ = -0.09941339;
		*a_iter++ = 0.09941339;
		*a_iter++ = -0.08506938;
		*a_iter++ = 0.08506938;
		*a_iter++ = -0.1260902;
		*a_iter++ = 0.1260902;
		*a_iter++ = -0.1014152;
		*a_iter++ = 0.1014152;
		*a_iter++ = -0.09728694;
		*a_iter++ = 0.09728694;
		*a_iter++ = -0.0937491;
		*a_iter++ = 0.0937491;
		*a_iter++ = -0.09587429;
		*a_iter++ = 0.09587429;
		*a_iter++ = -0.09516036;
		*a_iter++ = 0.09516036;
		*a_iter++ = -0.07375173;
		*a_iter++ = 0.07375173;
		*a_iter++ = -0.09332487;
		*a_iter++ = 0.09332487;
		*a_iter++ = -0.09020733;
		*a_iter++ = 0.09020733;
		*a_iter++ = -0.1133381;
		*a_iter++ = 0.1133381;
		*a_iter++ = -0.154218;
		*a_iter++ = 0.154218;
		*a_iter++ = -0.09692168;
		*a_iter++ = 0.09692168;
		*a_iter++ = -0.07960904;
		*a_iter++ = 0.07960904;
		*a_iter++ = -0.08947089;
		*a_iter++ = 0.08947089;
		*a_iter++ = -0.07830286;
		*a_iter++ = 0.07830286;
		*a_iter++ = -0.0990005;
		*a_iter++ = 0.0990005;
		*a_iter++ = -0.1041293;
		*a_iter++ = 0.1041293;
		*a_iter++ = -0.09572501;
		*a_iter++ = 0.09572501;
		*a_iter++ = -0.08230575;
		*a_iter++ = 0.08230575;
		*a_iter++ = -0.09194901;
		*a_iter++ = 0.09194901;
		*a_iter++ = -0.1076971;
		*a_iter++ = 0.1076971;
		*a_iter++ = -0.1027782;
		*a_iter++ = 0.1027782;
		*a_iter++ = -0.1028538;
		*a_iter++ = 0.1028538;
		*a_iter++ = -0.1013992;
		*a_iter++ = 0.1013992;
		*a_iter++ = -0.09087585;
		*a_iter++ = 0.09087585;
		*a_iter++ = -0.1100706;
		*a_iter++ = 0.1100706;
		*a_iter++ = -0.1094934;
		*a_iter++ = 0.1094934;
		*a_iter++ = -0.1107879;
		*a_iter++ = 0.1107879;
		*a_iter++ = -0.1026915;
		*a_iter++ = 0.1026915;
		*a_iter++ = -0.1017572;
		*a_iter++ = 0.1017572;
		*a_iter++ = -0.07984776;
		*a_iter++ = 0.07984776;
		*a_iter++ = -0.09015413;
		*a_iter++ = 0.09015413;
		*a_iter++ = -0.129987;
		*a_iter++ = 0.129987;
		*a_iter++ = -0.09164982;
		*a_iter++ = 0.09164982;
		*a_iter++ = -0.1062788;
		*a_iter++ = 0.1062788;
		*a_iter++ = -0.1160203;
		*a_iter++ = 0.1160203;
		*a_iter++ = -0.08858603;
		*a_iter++ = 0.08858603;
		*a_iter++ = -0.09762964;
		*a_iter++ = 0.09762964;
		*a_iter++ = -0.1070694;
		*a_iter++ = 0.1070694;
		*a_iter++ = -0.09549046;
		*a_iter++ = 0.09549046;
		*a_iter++ = -0.1533034;
		*a_iter++ = 0.1533034;
		*a_iter++ = -0.08663316;
		*a_iter++ = 0.08663316;
		*a_iter++ = -0.09303018;
		*a_iter++ = 0.09303018;
		*a_iter++ = -0.09853582;
		*a_iter++ = 0.09853582;
		*a_iter++ = -0.09733371;
		*a_iter++ = 0.09733371;
		*a_iter++ = -0.1048555;
		*a_iter++ = 0.1048555;
		*a_iter++ = -0.09056041;
		*a_iter++ = 0.09056041;
		*a_iter++ = -0.07552283;
		*a_iter++ = 0.07552283;
		*a_iter++ = -0.08780631;
		*a_iter++ = 0.08780631;
		*a_iter++ = -0.1123953;
		*a_iter++ = 0.1123953;
		*a_iter++ = -0.1452948;
		*a_iter++ = 0.1452948;
		*a_iter++ = -0.1156423;
		*a_iter++ = 0.1156423;
		*a_iter++ = -0.08701142;
		*a_iter++ = 0.08701142;
		*a_iter++ = -0.09713334;
		*a_iter++ = 0.09713334;
		*a_iter++ = -0.09970888;
		*a_iter++ = 0.09970888;
		*a_iter++ = -0.08614129;
		*a_iter++ = 0.08614129;
		*a_iter++ = -0.07459861;
		*a_iter++ = 0.07459861;
		*a_iter++ = -0.09253517;
		*a_iter++ = 0.09253517;
		*a_iter++ = -0.09570092;
		*a_iter++ = 0.09570092;
		*a_iter++ = -0.09485535;
		*a_iter++ = 0.09485535;
		*a_iter++ = -0.1148365;
		*a_iter++ = 0.1148365;
		*a_iter++ = -0.1063193;
		*a_iter++ = 0.1063193;
		*a_iter++ = -0.09986686;
		*a_iter++ = 0.09986686;
		*a_iter++ = -0.07523412;
		*a_iter++ = 0.07523412;
		*a_iter++ = -0.1005881;
		*a_iter++ = 0.1005881;
		*a_iter++ = -0.08249716;
		*a_iter++ = 0.08249716;
		*a_iter++ = -0.1055866;
		*a_iter++ = 0.1055866;
		*a_iter++ = -0.134305;
		*a_iter++ = 0.134305;
		*a_iter++ = -0.1371056;
		*a_iter++ = 0.1371056;
		*a_iter++ = -0.09604689;
		*a_iter++ = 0.09604689;
		*a_iter++ = -0.1224268;
		*a_iter++ = 0.1224268;
		*a_iter++ = -0.09211478;
		*a_iter++ = 0.09211478;
		*a_iter++ = -0.1108371;
		*a_iter++ = 0.1108371;
		*a_iter++ = -0.1100547;
		*a_iter++ = 0.1100547;
		*a_iter++ = -0.0893897;
		*a_iter++ = 0.0893897;
		*a_iter++ = -0.08655951;
		*a_iter++ = 0.08655951;
		*a_iter++ = -0.07085816;
		*a_iter++ = 0.07085816;
		*a_iter++ = -0.08101028;
		*a_iter++ = 0.08101028;
		*a_iter++ = -0.08338046;
		*a_iter++ = 0.08338046;
		*a_iter++ = -0.08309588;
		*a_iter++ = 0.08309588;
		*a_iter++ = -0.09090584;
		*a_iter++ = 0.09090584;
		*a_iter++ = -0.08124564;
		*a_iter++ = 0.08124564;
		*a_iter++ = -0.09367843;
		*a_iter++ = 0.09367843;
		*a_iter++ = -0.1011747;
		*a_iter++ = 0.1011747;
		*a_iter++ = -0.09885045;
		*a_iter++ = 0.09885045;
		*a_iter++ = -0.08944266;
		*a_iter++ = 0.08944266;
		*a_iter++ = -0.08453859;
		*a_iter++ = 0.08453859;
		*a_iter++ = -0.08308847;
		*a_iter++ = 0.08308847;
		*a_iter++ = -0.136728;
		*a_iter++ = 0.136728;
		*a_iter++ = -0.1295144;
		*a_iter++ = 0.1295144;
		*a_iter++ = -0.1063965;
		*a_iter++ = 0.1063965;
		*a_iter++ = -0.07752328;
		*a_iter++ = 0.07752328;
		*a_iter++ = -0.09681524;
		*a_iter++ = 0.09681524;
		*a_iter++ = -0.07862345;
		*a_iter++ = 0.07862345;
		*a_iter++ = -0.08767746;
		*a_iter++ = 0.08767746;
		*a_iter++ = -0.09198041;
		*a_iter++ = 0.09198041;
		*a_iter++ = -0.09686489;
		*a_iter++ = 0.09686489;
	}
	{
		CascadeStageClassifier& sc = *sc_iter++;
		sc.count = 564;
		sc.threshold = -4.517456;
		sc.features.SetCount(564);
		sc.alpha.SetCount(1128);
		auto cf_iter = sc.features.Begin();
		auto a_iter = sc.alpha.Begin();
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 9 << 8 << 12 << 11;
			cf.py << 3 << 6 << 3 << 0 << 8;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 6 << 14 << 9 << 22 << 23;
			cf.ny << 8 << 7 << 8 << 17 << 3;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 13 << 11 << 14 << 12;
			cf.py << 9 << 4 << 4 << 4 << 5;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 6 << 10 << 4 << 15;
			cf.ny << 3 << 8 << 7 << 10 << 9;
			cf.nz << 1 << 1 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 7 << 5 << 6 << 8 << 8;
			cf.py << 2 << 13 << 2 << 1 << 1;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 3 << 0 << 4 << 1 << 0;
			cf.ny << 4 << 3 << 10 << 3 << 13;
			cf.nz << 1 << 1 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 2 << 2 << 11 << 16;
			cf.py << 9 << 4 << 2 << 7 << 11;
			cf.pz << 0 << 2 << 2 << 0 << 0;
			cf.nx << 8 << 4 << 1 << 14 << 0;
			cf.ny << 4 << 4 << 16 << 5 << 13;
			cf.nz << 1 << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 14;
			cf.py << 18 << 18;
			cf.pz << 0 << -1;
			cf.nx << 8 << 13;
			cf.ny << 10 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 15 << 17 << 16 << 8 << 18;
			cf.py << 1 << 2 << 1 << 0 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 21 << 22 << 22 << 22 << 22;
			cf.ny << 1 << 5 << 3 << 4 << 2;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 4;
			cf.py << 23 << 3;
			cf.pz << 0 << 2;
			cf.nx << 7 << 3;
			cf.ny << 10 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 6 << 4 << 3 << 11;
			cf.py << 10 << 11 << 8 << 3 << 8;
			cf.pz << 1 << 0 << 1 << 1 << 0;
			cf.nx << 3 << 5 << 6 << 3 << 0;
			cf.ny << 4 << 9 << 9 << 9 << 0;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 11 << 2;
			cf.py << 11 << 13 << 16;
			cf.pz << 0 << 0 << -1;
			cf.nx << 10 << 10 << 9;
			cf.ny << 10 << 11 << 14;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 4 << 5;
			cf.ny << 11 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 11 << 13 << 3 << 12;
			cf.py << 3 << 4 << 3 << 0 << 1;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 14 << 18 << 20 << 19 << 15;
			cf.ny << 13 << 1 << 15 << 2 << 18;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 20 << 14 << 10 << 12 << 12;
			cf.py << 12 << 12 << 4 << 10 << 11;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 9 << 2 << 9 << 9 << 9;
			cf.ny << 4 << 12 << 5 << 9 << 14;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 3 << 3 << 4 << 2;
			cf.py << 15 << 16 << 14 << 21 << 12;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 20 << 10 << 5 << 21 << 21;
			cf.nz << 0 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 8;
			cf.py << 16 << 7;
			cf.pz << 0 << 1;
			cf.nx << 14 << 0;
			cf.ny << 8 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 4 << 16 << 1;
			cf.py << 14 << 3 << 8 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 14 << 10 << 20 << 13;
			cf.ny << 13 << 5 << 16 << 9;
			cf.nz << 0 << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 8 << 2 << 3 << 3;
			cf.py << 7 << 2 << 1 << 2 << 4;
			cf.pz << 1 << -1 << -1 << -1 << -1;
			cf.nx << 1 << 9 << 2 << 1 << 1;
			cf.ny << 3 << 14 << 9 << 7 << 2;
			cf.nz << 1 << 0 << 1 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 1 << 3 << 2 << 3;
			cf.py << 2 << 1 << 2 << 4 << 3;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 3 << 1 << 2 << 0 << 0;
			cf.nz << 0 << 1 << 0 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 4 << 8 << 7 << 9;
			cf.py << 6 << 11 << 11 << 10;
			cf.pz << 1 << 0 << 0 << 0;
			cf.nx << 3 << 10 << 2 << 20;
			cf.ny << 4 << 4 << 4 << 8;
			cf.nz << 1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 8;
			cf.py << 3 << 11;
			cf.pz << 2 << -1;
			cf.nx << 8 << 2;
			cf.ny << 15 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 0;
			cf.py << 13 << 10;
			cf.pz << 0 << -1;
			cf.nx << 14 << 14;
			cf.ny << 11 << 10;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 22 << 22 << 22 << 5 << 22;
			cf.py << 16 << 18 << 17 << 2 << 15;
			cf.pz << 0 << 0 << 0 << 2 << 0;
			cf.nx << 8 << 4 << 15 << 6 << 6;
			cf.ny << 4 << 2 << 7 << 11 << 11;
			cf.nz << 1 << 2 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 9 << 8 << 17 << 15;
			cf.py << 12 << 6 << 6 << 22 << 12;
			cf.pz << 0 << 1 << 1 << 0 << 0;
			cf.nx << 11 << 23 << 23 << 23 << 22;
			cf.ny << 11 << 23 << 22 << 21 << 23;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 2 << 4 << 4 << 9;
			cf.py << 22 << 3 << 15 << 20 << 18;
			cf.pz << 0 << 2 << 0 << 0 << 0;
			cf.nx << 9 << 4 << 23 << 7 << 22;
			cf.ny << 8 << 4 << 22 << 19 << 23;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 6 << 9 << 7 << 3;
			cf.py << 3 << 3 << 3 << 3 << 1;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 5 << 5 << 4 << 4 << 4;
			cf.ny << 0 << 1 << 1 << 2 << 0;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 3 << 3;
			cf.pz << 2 << 2;
			cf.nx << 3 << 6;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 1 << 1 << 0 << 1 << 0;
			cf.py << 17 << 15 << 6 << 16 << 10;
			cf.pz << 0 << 0 << 1 << 0 << 0;
			cf.nx << 4 << 4 << 7 << 4 << 8;
			cf.ny << 2 << 5 << 9 << 4 << 4;
			cf.nz << 2 << 2 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 13 << 13;
			cf.py << 10 << 9 << 11 << 13 << 13;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 4 << 3 << 3 << 5 << 3;
			cf.ny << 21 << 18 << 17 << 23 << 16;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 5 << 6 << 5 << 9;
			cf.py << 13 << 7 << 9 << 23;
			cf.pz << 0 << 0 << 1 << 0;
			cf.nx << 6 << 15 << 7 << 5;
			cf.ny << 9 << 20 << 7 << 23;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 4 << 2;
			cf.pz << 1 << 2;
			cf.nx << 8 << 23;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 7;
			cf.py << 18 << 0;
			cf.pz << 0 << 0;
			cf.nx << 5 << 7;
			cf.ny << 8 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 6;
			cf.py << 11 << 16;
			cf.pz << 1 << 0;
			cf.nx << 10 << 9;
			cf.ny << 16 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 11 << 11;
			cf.py << 11 << 10 << 12 << 13;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 13 << 13 << 13 << 9;
			cf.ny << 11 << 9 << 10 << 4;
			cf.nz << 0 << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 12 << 6 << 7 << 6;
			cf.py << 7 << 11 << 8 << 4;
			cf.pz << 0 << 1 << 1 << 1;
			cf.nx << 10 << 0 << 19 << 7;
			cf.ny << 21 << 3 << 12 << 11;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 9 << 1;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 19;
			cf.py << 21 << 20;
			cf.pz << 0 << 0;
			cf.nx << 7 << 7;
			cf.ny << 3 << 13;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 9 << 13 << 11 << 5;
			cf.py << 0 << 2 << 2 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 6 << 4 << 5 << 5 << 5;
			cf.ny << 1 << 3 << 5 << 2 << 6;
			cf.nz << 0 << 0 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 3 << 2 << 5 << 7;
			cf.py << 11 << 3 << 3 << 7 << 17;
			cf.pz << 1 << 2 << 2 << 0 << 0;
			cf.nx << 23 << 5 << 11 << 5 << 5;
			cf.ny << 0 << 4 << 10 << 2 << 6;
			cf.nz << 0 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 17;
			cf.py << 12 << 3;
			cf.pz << 0 << -1;
			cf.nx << 20 << 19;
			cf.ny << 21 << 23;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 12 << 8;
			cf.pz << 0 << 0;
			cf.nx << 2 << 8;
			cf.ny << 2 << 16;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 5;
			cf.py << 4 << 5;
			cf.pz << 0 << -1;
			cf.nx << 7 << 8;
			cf.ny << 9 << 1;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 0 << 1;
			cf.pz << 1 << 1;
			cf.nx << 1 << 8;
			cf.ny << 5 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 12 << 10;
			cf.pz << 0 << 1;
			cf.nx << 2 << 20;
			cf.ny << 23 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 0 << 0 << 2;
			cf.py << 14 << 3 << 9 << 22;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 13 << 14 << 7 << 3;
			cf.ny << 6 << 7 << 11 << 1;
			cf.nz << 0 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 0;
			cf.py << 2 << 3;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 4 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 11;
			cf.py << 18 << 11;
			cf.pz << 0 << 1;
			cf.nx << 3 << 2;
			cf.ny << 1 << 21;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 17 << 14;
			cf.pz << 0 << -1;
			cf.nx << 4 << 5;
			cf.ny << 10 << 8;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 18;
			cf.py << 7 << 14;
			cf.pz << 1 << 0;
			cf.nx << 18 << 9;
			cf.ny << 17 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 8;
			cf.py << 4 << 22;
			cf.pz << 2 << 0;
			cf.nx << 4 << 3;
			cf.ny << 10 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 22;
			cf.py << 4 << 9;
			cf.pz << 2 << -1;
			cf.nx << 11 << 23;
			cf.ny << 8 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 23 << 5 << 5;
			cf.py << 8 << 2 << 1;
			cf.pz << 0 << 2 << 2;
			cf.nx << 10 << 10 << 2;
			cf.ny << 4 << 4 << 2;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 14 << 23;
			cf.pz << 0 << -1;
			cf.nx << 3 << 11;
			cf.ny << 4 << 13;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 1;
			cf.py << 19 << 13;
			cf.pz << 0 << -1;
			cf.nx << 9 << 12;
			cf.ny << 10 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 11 << 10;
			cf.pz << 1 << 1;
			cf.nx << 4 << 1;
			cf.ny << 5 << 11;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 12 << 4 << 8 << 8;
			cf.py << 3 << 5 << 2 << 9 << 8;
			cf.pz << 1 << 0 << 2 << 1 << 1;
			cf.nx << 23 << 23 << 23 << 23 << 23;
			cf.ny << 3 << 4 << 6 << 5 << 5;
			cf.nz << 0 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 9;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 13 << 13 << 13 << 7 << 7;
			cf.py << 11 << 10 << 9 << 6 << 6;
			cf.pz << 0 << 0 << 0 << 1 << -1;
			cf.nx << 5 << 5 << 15 << 5 << 2;
			cf.ny << 5 << 15 << 9 << 9 << 1;
			cf.nz << 0 << 0 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 7;
			cf.py << 21 << 7;
			cf.pz << 0 << 1;
			cf.nx << 14 << 10;
			cf.ny << 15 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 21 << 0;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 0;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 3 << 2;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 0;
			cf.py << 4 << 0;
			cf.pz << 0 << -1;
			cf.nx << 5 << 12;
			cf.ny << 0 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 14 << 16 << 12 << 15 << 13;
			cf.py << 0 << 1 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 8 << 8 << 4 << 9;
			cf.ny << 2 << 3 << 4 << 1 << 3;
			cf.nz << 2 << 1 << 1 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 17 << 2;
			cf.py << 11 << 14 << 1;
			cf.pz << 1 << -1 << -1;
			cf.nx << 9 << 8 << 17;
			cf.ny << 1 << 4 << 0;
			cf.nz << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 9;
			cf.py << 17 << 7;
			cf.pz << 0 << 1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 3 << 0;
			cf.pz << 1 << 2;
			cf.nx << 10 << 11;
			cf.ny << 6 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 21 << 21 << 21 << 20;
			cf.py << 17 << 16 << 19 << 18 << 21;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 0 << 0 << 0 << 0 << 0;
			cf.ny << 4 << 9 << 11 << 6 << 6;
			cf.nz << 1 << 0 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 0;
			cf.py << 7 << 1;
			cf.pz << 0 << -1;
			cf.nx << 8 << 11;
			cf.ny << 4 << 17;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 0 << 0 << 0;
			cf.py << 15 << 0 << 0 << 0;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 3 << 7 << 4 << 6;
			cf.ny << 2 << 7 << 5 << 9;
			cf.nz << 2 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 9;
			cf.py << 3 << 12;
			cf.pz << 2 << 0;
			cf.nx << 2 << 0;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 6 << 1;
			cf.pz << 1 << -1;
			cf.nx << 20 << 21;
			cf.ny << 19 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 22 << 22 << 11 << 22;
			cf.py << 1 << 4 << 3 << 3 << 2;
			cf.pz << 2 << 0 << 0 << 1 << -1;
			cf.nx << 7 << 13 << 14 << 8 << 15;
			cf.ny << 3 << 6 << 6 << 3 << 7;
			cf.nz << 1 << 0 << 0 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 19;
			cf.py << 5 << 15;
			cf.pz << 0 << -1;
			cf.nx << 16 << 4;
			cf.ny << 8 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 11 << 9;
			cf.pz << 1 << 1;
			cf.nx << 5 << 0;
			cf.ny << 3 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 3 << 4 << 2;
			cf.py << 6 << 7 << 5 << 3;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 13 << 14 << 11 << 11;
			cf.ny << 11 << 13 << 3 << 5;
			cf.nz << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 5 << 6;
			cf.pz << 0 << 0;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 9;
			cf.py << 6 << 17;
			cf.pz << 1 << 0;
			cf.nx << 9 << 4;
			cf.ny << 15 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 3 << 6;
			cf.py << 6 << 3 << 5;
			cf.pz << 1 << 2 << 1;
			cf.nx << 11 << 10 << 4;
			cf.ny << 8 << 11 << 5;
			cf.nz << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 0 << 1;
			cf.pz << 1 << -1;
			cf.nx << 19 << 17;
			cf.ny << 1 << 0;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 20;
			cf.py << 4 << 1;
			cf.pz << 0 << 0;
			cf.nx << 11 << 5;
			cf.ny << 0 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 8 << 9;
			cf.ny << 4 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 13 << 12;
			cf.ny << 6 << 5;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 3 << 11;
			cf.pz << 1 << -1;
			cf.nx << 3 << 17;
			cf.ny << 1 << 3;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 3 << 3;
			cf.ny << 1 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 18;
			cf.py << 2 << 7;
			cf.pz << 2 << 0;
			cf.nx << 8 << 1;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 6;
			cf.py << 8 << 2;
			cf.pz << 0 << 1;
			cf.nx << 8 << 9;
			cf.ny << 4 << 19;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 12 << 3 << 14;
			cf.py << 13 << 3 << 15;
			cf.pz << 0 << -1 << -1;
			cf.nx << 0 << 1 << 0;
			cf.ny << 16 << 18 << 15;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 1;
			cf.py << 3 << 4;
			cf.pz << 2 << -1;
			cf.nx << 7 << 14;
			cf.ny << 10 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 16;
			cf.py << 6 << 10;
			cf.pz << 1 << 0;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 11;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 7 << 23;
			cf.ny << 3 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 4 << 3 << 4 << 4;
			cf.py << 1 << 2 << 0 << 1 << 1;
			cf.pz << 1 << 0 << 1 << 0 << -1;
			cf.nx << 11 << 9 << 4 << 9 << 5;
			cf.ny << 6 << 5 << 3 << 6 << 3;
			cf.nz << 0 << 0 << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 0;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 2 << 5;
			cf.ny << 2 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 7;
			cf.py << 7 << 12;
			cf.pz << 0 << 0;
			cf.nx << 3 << 22;
			cf.ny << 3 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 1 << 1;
			cf.pz << 0 << 1;
			cf.nx << 2 << 6;
			cf.ny << 2 << 21;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 1;
			cf.py << 11 << 6;
			cf.pz << 0 << -1;
			cf.nx << 12 << 6;
			cf.ny << 5 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 10 << 5 << 11 << 10 << 10;
			cf.py << 4 << 3 << 4 << 6 << 5;
			cf.pz << 0 << 1 << 0 << 0 << 0;
			cf.nx << 4 << 7 << 13 << 8 << 4;
			cf.ny << 2 << 8 << 9 << 4 << 4;
			cf.nz << 2 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 7 << 8 << 7 << 8;
			cf.py << 11 << 3 << 4 << 7;
			cf.pz << 1 << 1 << 1 << 1;
			cf.nx << 0 << 7 << 3 << 8;
			cf.ny << 0 << 12 << 2 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 4 << 7;
			cf.pz << 2 << 1;
			cf.nx << 10 << 1;
			cf.ny << 7 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 19 << 5;
			cf.pz << 0 << -1;
			cf.nx << 11 << 5;
			cf.ny << 17 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 12;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 7 << 5;
			cf.ny << 8 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 8 << 4;
			cf.py << 2 << 9 << 4;
			cf.pz << 2 << 1 << 2;
			cf.nx << 3 << 19 << 3;
			cf.ny << 1 << 16 << 5;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 0 << 1;
			cf.pz << 1 << 0;
			cf.nx << 2 << 3;
			cf.ny << 15 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 4;
			cf.py << 2 << 0;
			cf.pz << 2 << -1;
			cf.nx << 9 << 16;
			cf.ny << 5 << 11;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 15;
			cf.py << 23 << 16;
			cf.pz << 0 << 0;
			cf.nx << 13 << 3;
			cf.ny << 15 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 0 << 1;
			cf.pz << 1 << -1;
			cf.nx << 3 << 7;
			cf.ny << 0 << 0;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 12 << 12;
			cf.pz << 0 << 0;
			cf.nx << 4 << 8;
			cf.ny << 5 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 1 << 2 << 4 << 5;
			cf.py << 1 << 0 << 0 << 0 << 6;
			cf.pz << 0 << 2 << 1 << 0 << 1;
			cf.nx << 4 << 8 << 7 << 8 << 6;
			cf.ny << 4 << 10 << 11 << 4 << 4;
			cf.nz << 1 << 0 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 12;
			cf.py << 15 << 8;
			cf.pz << 0 << -1;
			cf.nx << 7 << 15;
			cf.ny << 16 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 4 << 6;
			cf.ny << 2 << 8;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 4;
			cf.py << 19 << 23;
			cf.pz << 0 << -1;
			cf.nx << 7 << 14;
			cf.ny << 11 << 18;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 7 << 4;
			cf.pz << 1 << 2;
			cf.nx << 2 << 22;
			cf.ny << 5 << 19;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 15;
			cf.py << 7 << 17;
			cf.pz << 1 << 0;
			cf.nx << 14 << 4;
			cf.ny << 15 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 11;
			cf.py << 9 << 8;
			cf.pz << 1 << -1;
			cf.nx << 23 << 5;
			cf.ny << 19 << 4;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 1;
			cf.py << 7 << 9;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 7;
			cf.py << 6 << 9;
			cf.pz << 0 << 0;
			cf.nx << 4 << 11;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 0 << 5;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 0 << 4;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 22;
			cf.py << 5 << 20;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 23 << 11 << 11;
			cf.py << 17 << 9 << 8;
			cf.pz << 0 << 1 << 1;
			cf.nx << 13 << 8 << 8;
			cf.ny << 5 << 3 << 3;
			cf.nz << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 9;
			cf.py << 0 << 21;
			cf.pz << 0 << -1;
			cf.nx << 10 << 10;
			cf.ny << 2 << 1;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 11 << 11 << 11;
			cf.py << 11 << 13 << 10 << 12 << 12;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 11 << 13 << 12 << 3 << 8;
			cf.ny << 5 << 5 << 5 << 1 << 10;
			cf.nz << 0 << 0 << 0 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 8;
			cf.py << 11 << 11;
			cf.pz << 0 << 0;
			cf.nx << 9 << 16;
			cf.ny << 9 << 19;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 18;
			cf.py << 23 << 7;
			cf.pz << 0 << -1;
			cf.nx << 21 << 21;
			cf.ny << 7 << 13;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 7 << 8;
			cf.pz << 1 << 1;
			cf.nx << 5 << 21;
			cf.ny << 9 << 13;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 8;
			cf.py << 22 << 8;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 5 << 8 << 8 << 4;
			cf.py << 3 << 9 << 13 << 23 << 7;
			cf.pz << 2 << 1 << 0 << 0 << 1;
			cf.nx << 9 << 17 << 18 << 19 << 20;
			cf.ny << 0 << 0 << 0 << 2 << 3;
			cf.nz << 1 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 15 << 2;
			cf.py << 3 << 3 << 13;
			cf.pz << 0 << 0 << -1;
			cf.nx << 4 << 8 << 4;
			cf.ny << 3 << 6 << 2;
			cf.nz << 2 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 3 << 7;
			cf.pz << 2 << 1;
			cf.nx << 15 << 1;
			cf.ny << 15 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 3;
			cf.pz << 2 << 1;
			cf.nx << 3 << 18;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 3 << 0;
			cf.ny << 5 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 10 << 0;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 2 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 0;
			cf.py << 8 << 3;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 14;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 18;
			cf.py << 14 << 14;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 15 << 13;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 2 << 2;
			cf.py << 17 << 10 << 15;
			cf.pz << 0 << 1 << 0;
			cf.nx << 13 << 2 << 7;
			cf.ny << 19 << 11 << 0;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 17;
			cf.py << 0 << 2;
			cf.pz << 2 << 0;
			cf.nx << 8 << 5;
			cf.ny << 11 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 21;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 15 << 10;
			cf.ny << 3 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 13 << 8;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 22;
			cf.py << 3 << 4;
			cf.pz << 1 << -1;
			cf.nx << 4 << 2;
			cf.ny << 2 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 2 << 6 << 5;
			cf.py << 21 << 10 << 22 << 20;
			cf.pz << 0 << 1 << 0 << 0;
			cf.nx << 2 << 3 << 4 << 4;
			cf.ny << 11 << 21 << 23 << 23;
			cf.nz << 1 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 6 << 8;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 11 << 5 << 11;
			cf.py << 6 << 5 << 2 << 4;
			cf.pz << 1 << 1 << 2 << 1;
			cf.nx << 13 << 7 << 8 << 3;
			cf.ny << 7 << 3 << 5 << 2;
			cf.nz << 0 << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 7 << 8;
			cf.pz << 1 << 0;
			cf.nx << 3 << 11;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 1 << 5;
			cf.py << 3 << 3 << 11;
			cf.pz << 0 << -1 << -1;
			cf.nx << 16 << 4 << 8;
			cf.ny << 2 << 0 << 1;
			cf.nz << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 8 << 1;
			cf.pz << 0 << -1;
			cf.nx << 19 << 18;
			cf.ny << 20 << 23;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 4;
			cf.py << 10 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 14;
			cf.ny << 2 << 9;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 12 << 9 << 10 << 11;
			cf.py << 2 << 3 << 2 << 2 << 3;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 6 << 4 << 2 << 2 << 2;
			cf.ny << 18 << 9 << 3 << 2 << 2;
			cf.nz << 0 << 1 << 2 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 6 << 16;
			cf.pz << 1 << 0;
			cf.nx << 8 << 16;
			cf.ny << 5 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 2 << 3;
			cf.pz << 2 << 2;
			cf.nx << 8 << 17;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 5 << 2;
			cf.py << 5 << 6 << 4;
			cf.pz << 1 << -1 << -1;
			cf.nx << 0 << 0 << 0;
			cf.ny << 3 << 5 << 6;
			cf.nz << 2 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 0 << 0 << 0 << 0;
			cf.py << 6 << 15 << 16 << 13 << 14;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 5 << 8 << 6 << 8;
			cf.ny << 4 << 16 << 8 << 15 << 4;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 5;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 21 << 19 << 21 << 21 << 21;
			cf.py << 17 << 23 << 18 << 19 << 20;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 5 << 2 << 3 << 6 << 6;
			cf.ny << 12 << 5 << 5 << 12 << 12;
			cf.nz << 0 << 1 << 1 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 11 << 1;
			cf.pz << 1 << -1;
			cf.nx << 5 << 11;
			cf.ny << 3 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 5 << 3;
			cf.pz << 0 << 1;
			cf.nx << 6 << 15;
			cf.ny << 11 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 2;
			cf.py << 4 << 2;
			cf.pz << 1 << -1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 20 << 6;
			cf.pz << 0 << -1;
			cf.nx << 5 << 10;
			cf.ny << 11 << 17;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 4 << 7 << 11;
			cf.py << 7 << 4 << 5 << 8;
			cf.pz << 1 << 2 << 1 << 0;
			cf.nx << 13 << 10 << 5 << 21;
			cf.ny << 9 << 3 << 5 << 4;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 13;
			cf.py << 10 << 7;
			cf.pz << 0 << 0;
			cf.nx << 10 << 8;
			cf.ny << 9 << 18;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 8 << 5;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 5 << 2 << 5 << 8 << 4;
			cf.py << 8 << 4 << 14 << 23 << 7;
			cf.pz << 1 << 2 << 0 << 0 << 1;
			cf.nx << 18 << 4 << 16 << 17 << 17;
			cf.ny << 1 << 0 << 0 << 1 << 1;
			cf.nz << 0 << 2 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 2;
			cf.py << 2 << 4;
			cf.pz << 1 << -1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 1;
			cf.py << 8 << 15;
			cf.pz << 0 << -1;
			cf.nx << 8 << 3;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 7 << 2;
			cf.pz << 1 << -1;
			cf.nx << 6 << 6;
			cf.ny << 9 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 6 << 2;
			cf.pz << 1 << -1;
			cf.nx << 1 << 10;
			cf.ny << 16 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 7 << 2;
			cf.pz << 1 << -1;
			cf.nx << 8 << 9;
			cf.ny << 8 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 8 << 7 << 6 << 6;
			cf.py << 0 << 0 << 0 << 1 << 1;
			cf.pz << 1 << 0 << 0 << 0 << -1;
			cf.nx << 11 << 5 << 8 << 4 << 10;
			cf.ny << 5 << 3 << 4 << 4 << 5;
			cf.nz << 0 << 1 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 6;
			cf.py << 8 << 5;
			cf.pz << 0 << 0;
			cf.nx << 6 << 6;
			cf.ny << 8 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 5;
			cf.py << 19 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 21;
			cf.ny << 5 << 19;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 13 << 6;
			cf.pz << 0 << 1;
			cf.nx << 2 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 17 << 6;
			cf.pz << 0 << 1;
			cf.nx << 10 << 2;
			cf.ny << 15 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 13 << 19;
			cf.py << 11 << 12 << 8;
			cf.pz << 0 << 0 << -1;
			cf.nx << 12 << 3 << 8;
			cf.ny << 4 << 1 << 4;
			cf.nz << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 7 << 4;
			cf.py << 5 << 2 << 1;
			cf.pz << 0 << -1 << -1;
			cf.nx << 9 << 2 << 4;
			cf.ny << 11 << 3 << 6;
			cf.nz << 0 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 7;
			cf.py << 15 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 0 << 1;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 9 << 16 << 18 << 18;
			cf.py << 0 << 1 << 1 << 1 << 1;
			cf.pz << 1 << 1 << 0 << 0 << -1;
			cf.nx << 5 << 5 << 6 << 4 << 4;
			cf.ny << 21 << 20 << 23 << 17 << 18;
			cf.nz << 0 << 0 << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 7;
			cf.py << 1 << 1;
			cf.pz << 1 << 1;
			cf.nx << 20 << 19;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 10 << 11;
			cf.pz << 1 << 1;
			cf.nx << 3 << 3;
			cf.ny << 10 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 5;
			cf.py << 23 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 10 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 10;
			cf.py << 4 << 7;
			cf.pz << 2 << -1;
			cf.nx << 4 << 3;
			cf.ny << 23 << 21;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 21;
			cf.py << 11 << 18;
			cf.pz << 1 << 0;
			cf.nx << 10 << 4;
			cf.ny << 18 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 23;
			cf.py << 11 << 15;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 7 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 7 << 7;
			cf.pz << 1 << -1;
			cf.nx << 15 << 4;
			cf.ny << 14 << 4;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 2;
			cf.py << 9 << 20;
			cf.pz << 1 << 0;
			cf.nx << 21 << 3;
			cf.ny << 12 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 0 << 0;
			cf.pz << 1 << 2;
			cf.nx << 4 << 2;
			cf.ny << 0 << 19;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 3 << 0;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 1;
			cf.py << 5 << 0;
			cf.pz << 1 << -1;
			cf.nx << 12 << 10;
			cf.ny << 11 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 12;
			cf.py << 11 << 14;
			cf.pz << 1 << -1;
			cf.nx << 18 << 16;
			cf.ny << 21 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 18;
			cf.py << 1 << 5;
			cf.pz << 2 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 18 << 7;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 0 << 0;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 2;
			cf.py << 1 << 4;
			cf.pz << 0 << -1;
			cf.nx << 22 << 22;
			cf.ny << 13 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 15 << 20;
			cf.py << 14 << 21 << 10;
			cf.pz << 0 << -1 << -1;
			cf.nx << 15 << 7 << 7;
			cf.ny << 13 << 6 << 8;
			cf.nz << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 6 << 7;
			cf.pz << 1 << 1;
			cf.nx << 8 << 7;
			cf.ny << 4 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 3;
			cf.pz << 1 << 2;
			cf.nx << 5 << 10;
			cf.ny << 2 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 11;
			cf.py << 7 << 16;
			cf.pz << 0 << -1;
			cf.nx << 1 << 0;
			cf.ny << 17 << 4;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 18;
			cf.py << 17 << 18;
			cf.pz << 0 << -1;
			cf.nx << 8 << 14;
			cf.ny << 10 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 11;
			cf.py << 13 << 11;
			cf.pz << 0 << -1;
			cf.nx << 8 << 9;
			cf.ny << 12 << 9;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 2 << 2;
			cf.pz << 0 << 0;
			cf.nx << 3 << 3;
			cf.ny << 2 << 2;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 21 << 21 << 21;
			cf.py << 14 << 16 << 15;
			cf.pz << 0 << 0 << 0;
			cf.nx << 14 << 12 << 0;
			cf.ny << 5 << 12 << 6;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 21;
			cf.py << 6 << 15;
			cf.pz << 1 << -1;
			cf.nx << 5 << 1;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 8 << 0;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 2;
			cf.py << 9 << 1;
			cf.pz << 0 << -1;
			cf.nx << 3 << 5;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 1;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 17 << 8;
			cf.ny << 3 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 20 << 20;
			cf.ny << 17 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 7;
			cf.py << 3 << 6;
			cf.pz << 2 << -1;
			cf.nx << 9 << 9;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 17;
			cf.py << 4 << 1;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 2;
			cf.py << 11 << 0;
			cf.pz << 0 << -1;
			cf.nx << 5 << 14;
			cf.ny << 1 << 12;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 19;
			cf.py << 3 << 0;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 6 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 22;
			cf.py << 3 << 21;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 1 << 0;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 11 << 12;
			cf.pz << 0 << 0;
			cf.nx << 1 << 2;
			cf.ny << 1 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 3;
			cf.py << 8 << 1;
			cf.pz << 0 << 2;
			cf.nx << 13 << 1;
			cf.ny << 8 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 6;
			cf.py << 21 << 3;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 14;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 17 << 1;
			cf.ny << 12 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 3;
			cf.py << 12 << 1;
			cf.pz << 0 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 7 << 3;
			cf.pz << 0 << 1;
			cf.nx << 16 << 2;
			cf.ny << 3 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 7 << 20;
			cf.pz << 1 << -1;
			cf.nx << 9 << 8;
			cf.ny << 4 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 2;
			cf.py << 10 << 2;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 3 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 9;
			cf.py << 0 << 23;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 3 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 9;
			cf.py << 4 << 10;
			cf.pz << 1 << 0;
			cf.nx << 10 << 9;
			cf.ny << 9 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 6 << 9 << 10 << 8;
			cf.py << 20 << 23 << 18 << 23;
			cf.pz << 0 << 0 << 0 << 0;
			cf.nx << 9 << 22 << 1 << 2;
			cf.ny << 21 << 14 << 2 << 5;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 18;
			cf.py << 13 << 6;
			cf.pz << 0 << -1;
			cf.nx << 6 << 7;
			cf.ny << 9 << 11;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 18 << 19 << 20 << 19 << 20;
			cf.py << 15 << 19 << 16 << 20 << 17;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 11 << 22 << 23 << 23 << 23;
			cf.ny << 10 << 22 << 20 << 19 << 19;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 1 << 0;
			cf.pz << 1 << 1;
			cf.nx << 21 << 11;
			cf.ny << 0 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 0;
			cf.py << 9 << 3;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 2 << 1;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 23;
			cf.py << 2 << 18;
			cf.pz << 0 << -1;
			cf.nx << 15 << 18;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 3 << 12;
			cf.ny << 1 << 5;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 8;
			cf.py << 7 << 8;
			cf.pz << 1 << 1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 1 << 3;
			cf.pz << 2 << -1;
			cf.nx << 7 << 19;
			cf.ny << 9 << 15;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 16 << 6 << 4;
			cf.py << 21 << 5 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 4 << 19 << 8;
			cf.ny << 5 << 21 << 11;
			cf.nz << 2 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 6 << 6;
			cf.pz << 1 << -1;
			cf.nx << 10 << 10;
			cf.ny << 10 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 11;
			cf.py << 2 << 5;
			cf.pz << 1 << 0;
			cf.nx << 3 << 4;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 6 << 2;
			cf.py << 4 << 10 << 2;
			cf.pz << 1 << 1 << 2;
			cf.nx << 2 << 18 << 5;
			cf.ny << 0 << 11 << 5;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 7;
			cf.py << 9 << 7;
			cf.pz << 0 << -1;
			cf.nx << 12 << 3;
			cf.ny << 9 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 13;
			cf.py << 20 << 20;
			cf.pz << 0 << 0;
			cf.nx << 13 << 3;
			cf.ny << 21 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 7;
			cf.py << 5 << 3;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 1 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 2;
			cf.py << 21 << 5;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 5;
			cf.py << 6 << 0;
			cf.pz << 0 << 2;
			cf.nx << 21 << 4;
			cf.ny << 6 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 7 << 6;
			cf.pz << 1 << 1;
			cf.nx << 8 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 11;
			cf.py << 20 << 9;
			cf.pz << 0 << 1;
			cf.nx << 8 << 8;
			cf.ny << 10 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 21 << 12;
			cf.pz << 0 << -1;
			cf.nx << 2 << 7;
			cf.ny << 5 << 23;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 0 << 1 << 1 << 1 << 1;
			cf.py << 3 << 1 << 9 << 4 << 7;
			cf.pz << 2 << 2 << 1 << 1 << 1;
			cf.nx << 11 << 22 << 22 << 23 << 23;
			cf.ny << 10 << 21 << 22 << 19 << 20;
			cf.nz << 1 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 5;
			cf.py << 12 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 8;
			cf.ny << 4 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 4;
			cf.py << 7 << 10;
			cf.pz << 0 << -1;
			cf.nx << 9 << 15;
			cf.ny << 4 << 6;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 3 << 5;
			cf.pz << 2 << 1;
			cf.nx << 11 << 12;
			cf.ny << 11 << 23;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 14 << 7;
			cf.pz << 0 << 1;
			cf.nx << 4 << 17;
			cf.ny << 18 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 1 << 1;
			cf.py << 12 << 5 << 4;
			cf.pz << 0 << -1 << -1;
			cf.nx << 7 << 11 << 5;
			cf.ny << 1 << 2 << 1;
			cf.nz << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 6;
			cf.py << 3 << 9;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 6;
			cf.py << 22 << 9;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 9 << 10 << 11 << 11;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 16 << 5 << 10 << 4 << 8;
			cf.ny << 10 << 3 << 6 << 4 << 4;
			cf.nz << 0 << 1 << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 19;
			cf.py << 23 << 20;
			cf.pz << 0 << 0;
			cf.nx << 8 << 5;
			cf.ny << 11 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 7 << 2;
			cf.pz << 1 << 2;
			cf.nx << 8 << 4;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 8 << 14 << 8 << 7 << 4;
			cf.py << 6 << 12 << 8 << 6 << 3;
			cf.pz << 1 << 0 << 1 << 1 << 2;
			cf.nx << 2 << 6 << 6 << 7 << 7;
			cf.ny << 0 << 1 << 2 << 0 << 0;
			cf.nz << 2 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 1 << 2 << 3;
			cf.py << 15 << 18 << 21;
			cf.pz << 0 << 0 << 0;
			cf.nx << 19 << 5 << 18;
			cf.ny << 23 << 5 << 8;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 2;
			cf.py << 6 << 1;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 12 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 5;
			cf.py << 5 << 11;
			cf.pz << 2 << 1;
			cf.nx << 14 << 5;
			cf.ny << 19 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 4;
			cf.py << 4 << 4;
			cf.pz << 1 << -1;
			cf.nx << 11 << 5;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 4;
			cf.py << 6 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 5 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 2 << 4;
			cf.pz << 1 << 0;
			cf.nx << 8 << 8;
			cf.ny << 3 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 1 << 1;
			cf.pz << 1 << 2;
			cf.nx << 7 << 2;
			cf.ny << 4 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 0;
			cf.py << 20 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 5;
			cf.ny << 10 << 11;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 14;
			cf.py << 5 << 2;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 0 << 2;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 15;
			cf.py << 4 << 7;
			cf.pz << 1 << -1;
			cf.nx << 4 << 7;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 5;
			cf.py << 2 << 1;
			cf.pz << 0 << 1;
			cf.nx << 3 << 1;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 9;
			cf.py << 4 << 2;
			cf.pz << 0 << -1;
			cf.nx << 11 << 9;
			cf.ny << 1 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 4;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 3 << 7;
			cf.pz << 2 << 1;
			cf.nx << 6 << 8;
			cf.ny << 14 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 0;
			cf.py << 21 << 3;
			cf.pz << 0 << 2;
			cf.nx << 20 << 8;
			cf.ny << 10 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 5 << 8;
			cf.pz << 0 << -1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 2;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 13;
			cf.pz << 1 << 0;
			cf.nx << 3 << 2;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 10;
			cf.py << 9 << 7;
			cf.pz << 0 << 1;
			cf.nx << 7 << 9;
			cf.ny << 3 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 10;
			cf.py << 6 << 7;
			cf.pz << 0 << -1;
			cf.nx << 8 << 17;
			cf.ny << 4 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 10;
			cf.py << 4 << 10;
			cf.pz << 2 << 1;
			cf.nx << 5 << 4;
			cf.ny << 9 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 15 << 3 << 5 << 0;
			cf.py << 12 << 4 << 2 << 3;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 13 << 7 << 5 << 7;
			cf.ny << 12 << 6 << 0 << 7;
			cf.nz << 0 << 1 << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 2 << 3 << 16 << 17;
			cf.py << 3 << 4 << 6 << 6;
			cf.pz << 2 << 1 << 0 << 0;
			cf.nx << 16 << 16 << 8 << 16;
			cf.ny << 8 << 3 << 10 << 13;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 8;
			cf.py << 1 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 14;
			cf.py << 6 << 2;
			cf.pz << 1 << -1;
			cf.nx << 8 << 8;
			cf.ny << 6 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 10 << 0;
			cf.ny << 5 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 4 << 4;
			cf.pz << 0 << 0;
			cf.nx << 9 << 7;
			cf.ny << 3 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 10 << 13 << 6 << 12;
			cf.py << 2 << 2 << 2 << 1 << 2;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 4 << 18 << 18 << 13 << 13;
			cf.ny << 2 << 18 << 19 << 7 << 7;
			cf.nz << 2 << 0 << 0 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 13 << 13 << 13 << 2;
			cf.py << 13 << 12 << 11 << 3;
			cf.pz << 0 << 0 << 0 << -1;
			cf.nx << 4 << 6 << 8 << 11;
			cf.ny << 2 << 2 << 4 << 4;
			cf.nz << 2 << 1 << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 7;
			cf.py << 6 << 13;
			cf.pz << 1 << 0;
			cf.nx << 8 << 10;
			cf.ny << 4 << 22;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 7;
			cf.py << 4 << 17;
			cf.pz << 1 << -1;
			cf.nx << 0 << 1;
			cf.ny << 5 << 21;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 22 << 22;
			cf.pz << 0 << 0;
			cf.nx << 2 << 2;
			cf.ny << 13 << 13;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 4 << 4 << 3;
			cf.py << 22 << 23 << 19;
			cf.pz << 0 << 0 << 0;
			cf.nx << 8 << 12 << 3;
			cf.ny << 22 << 15 << 2;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 12;
			cf.py << 3 << 13;
			cf.pz << 0 << -1;
			cf.nx << 15 << 2;
			cf.ny << 10 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 3 << 3;
			cf.pz << 2 << -1;
			cf.nx << 8 << 4;
			cf.ny << 0 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 6 << 18;
			cf.pz << 1 << 0;
			cf.nx << 12 << 19;
			cf.ny << 17 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 2 << 1;
			cf.pz << 0 << 1;
			cf.nx << 5 << 4;
			cf.ny << 4 << 17;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 12 << 11;
			cf.py << 5 << 23 << 23;
			cf.pz << 2 << 0 << 0;
			cf.nx << 12 << 4 << 4;
			cf.ny << 21 << 17 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 0;
			cf.py << 21 << 5;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 7 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 17;
			cf.py << 12 << 11;
			cf.pz << 0 << 0;
			cf.nx << 8 << 11;
			cf.ny << 4 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 0;
			cf.py << 22 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 6;
			cf.ny << 1 << 0;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 9 << 5;
			cf.pz << 1 << 1;
			cf.nx << 23 << 11;
			cf.ny << 23 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 4 << 12 << 11 << 9 << 8;
			cf.py << 0 << 1 << 1 << 0 << 1;
			cf.pz << 1 << 0 << 0 << 0 << 0;
			cf.nx << 4 << 17 << 8 << 7 << 7;
			cf.ny << 2 << 13 << 4 << 4 << 4;
			cf.nz << 2 << 0 << 1 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 13;
			cf.py << 12 << 12;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 4;
			cf.py << 23 << 2;
			cf.pz << 0 << -1;
			cf.nx << 5 << 2;
			cf.ny << 23 << 6;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 8 << 16 << 0;
			cf.py << 5 << 15 << 6;
			cf.pz << 1 << -1 << -1;
			cf.nx << 23 << 23 << 11;
			cf.ny << 18 << 17 << 8;
			cf.nz << 0 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 16;
			cf.py << 4 << 15;
			cf.pz << 2 << -1;
			cf.nx << 2 << 2;
			cf.ny << 3 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 8;
			cf.py << 7 << 9;
			cf.pz << 1 << -1;
			cf.nx << 4 << 2;
			cf.ny << 10 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 22 << 1 << 9;
			cf.py << 23 << 2 << 3;
			cf.pz << 0 << -1 << -1;
			cf.nx << 2 << 2 << 5;
			cf.ny << 5 << 4 << 19;
			cf.nz << 2 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 20;
			cf.py << 5 << 15;
			cf.pz << 1 << -1;
			cf.nx << 2 << 1;
			cf.ny << 1 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 1 << 19;
			cf.pz << 1 << -1;
			cf.nx << 2 << 2;
			cf.ny << 5 << 4;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 21 << 0;
			cf.pz << 0 << -1;
			cf.nx << 6 << 5;
			cf.ny << 1 << 1;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 8;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 9 << 2;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 17 << 3 << 10;
			cf.py << 8 << 0 << 2;
			cf.pz << 0 << 2 << 0;
			cf.nx << 13 << 2 << 6;
			cf.ny << 15 << 5 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 6;
			cf.py << 20 << 21;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 10 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 0 << 1;
			cf.pz << 2 << 1;
			cf.nx << 7 << 20;
			cf.ny << 1 << 19;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 0 << 1;
			cf.pz << 1 << 0;
			cf.nx << 3 << 2;
			cf.ny << 4 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 4 << 19;
			cf.pz << 2 << 0;
			cf.nx << 5 << 2;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 3 << 3 << 4 << 7 << 7;
			cf.py << 1 << 0 << 0 << 0 << 1;
			cf.pz << 1 << 1 << 1 << 0 << 0;
			cf.nx << 5 << 4 << 10 << 8 << 8;
			cf.ny << 3 << 3 << 5 << 4 << 4;
			cf.nz << 1 << 1 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 5;
			cf.py << 0 << 3;
			cf.pz << 1 << -1;
			cf.nx << 1 << 0;
			cf.ny << 0 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 9;
			cf.py << 0 << 4;
			cf.pz << 2 << -1;
			cf.nx << 13 << 10;
			cf.ny << 0 << 0;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 14 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 0 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 4;
			cf.py << 13 << 3;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 0;
			cf.py << 6 << 2;
			cf.pz << 1 << -1;
			cf.nx << 1 << 6;
			cf.ny << 2 << 12;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 4;
			cf.py << 6 << 0;
			cf.pz << 0 << -1;
			cf.nx << 3 << 3;
			cf.ny << 8 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 5;
			cf.py << 1 << 5;
			cf.pz << 1 << -1;
			cf.nx << 17 << 17;
			cf.ny << 13 << 7;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 11;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 17;
			cf.py << 2 << 8;
			cf.pz << 1 << 0;
			cf.nx << 3 << 3;
			cf.ny << 1 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 13 << 6 << 6;
			cf.py << 22 << 11 << 10;
			cf.pz << 0 << 1 << 1;
			cf.nx << 13 << 12 << 11;
			cf.ny << 20 << 20 << 20;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 12;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 1 << 1;
			cf.pz << 1 << -1;
			cf.nx << 13 << 6;
			cf.ny << 0 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 8;
			cf.py << 3 << 9;
			cf.pz << 2 << 0;
			cf.nx << 8 << 16;
			cf.ny << 5 << 17;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 15;
			cf.py << 1 << 1;
			cf.pz << 0 << 0;
			cf.nx << 7 << 11;
			cf.ny << 8 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 18;
			cf.py << 21 << 23;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 4 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 5;
			cf.py << 0 << 2;
			cf.pz << 1 << -1;
			cf.nx << 15 << 11;
			cf.ny << 8 << 7;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 4;
			cf.py << 7 << 8;
			cf.pz << 1 << -1;
			cf.nx << 9 << 10;
			cf.ny << 13 << 11;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 10 << 4;
			cf.pz << 1 << 2;
			cf.nx << 22 << 4;
			cf.ny << 0 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 3;
			cf.py << 3 << 1;
			cf.pz << 0 << 2;
			cf.nx << 8 << 0;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 21;
			cf.py << 11 << 22;
			cf.pz << 0 << -1;
			cf.nx << 10 << 11;
			cf.ny << 11 << 9;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 0 << 1;
			cf.pz << 2 << 2;
			cf.nx << 2 << 21;
			cf.ny << 6 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 10 << 10 << 1;
			cf.py << 11 << 0 << 5;
			cf.pz << 0 << -1 << -1;
			cf.nx << 6 << 12 << 5;
			cf.ny << 2 << 5 << 2;
			cf.nz << 1 << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 10;
			cf.py << 5 << 6;
			cf.pz << 0 << 0;
			cf.nx << 12 << 19;
			cf.ny << 23 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 9 << 6;
			cf.pz << 0 << 1;
			cf.nx << 21 << 0;
			cf.ny << 23 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 12;
			cf.py << 19 << 15;
			cf.pz << 0 << 0;
			cf.nx << 13 << 0;
			cf.ny << 17 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 0;
			cf.py << 17 << 3;
			cf.pz << 0 << -1;
			cf.nx << 7 << 16;
			cf.ny << 8 << 19;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 8 << 1;
			cf.ny << 4 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 10;
			cf.py << 23 << 20;
			cf.pz << 0 << -1;
			cf.nx << 4 << 7;
			cf.ny << 5 << 10;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 9;
			cf.py << 22 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 10 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 1 << 1 << 5;
			cf.py << 4 << 2 << 1 << 2;
			cf.pz << 0 << 2 << 2 << 1;
			cf.nx << 13 << 5 << 8 << 0;
			cf.ny << 22 << 2 << 9 << 2;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 0 << 0;
			cf.pz << 1 << -1;
			cf.nx << 19 << 20;
			cf.ny << 1 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 22;
			cf.py << 6 << 8;
			cf.pz << 1 << 0;
			cf.nx << 4 << 4;
			cf.ny << 2 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 4 << 4;
			cf.pz << 2 << 1;
			cf.nx << 10 << 20;
			cf.ny << 10 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 12;
			cf.py << 6 << 15;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 2 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 4 << 10;
			cf.pz << 2 << -1;
			cf.nx << 3 << 6;
			cf.ny << 4 << 8;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 11 << 4;
			cf.py << 0 << 5 << 7;
			cf.pz << 1 << -1 << -1;
			cf.nx << 6 << 12 << 12;
			cf.ny << 1 << 1 << 2;
			cf.nz << 1 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 17;
			cf.py << 4 << 18;
			cf.pz << 0 << -1;
			cf.nx << 8 << 2;
			cf.ny << 10 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 17;
			cf.py << 10 << 18;
			cf.pz << 0 << -1;
			cf.nx << 8 << 8;
			cf.ny << 2 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 9;
			cf.py << 7 << 7;
			cf.pz << 1 << -1;
			cf.nx << 7 << 4;
			cf.ny << 6 << 3;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 21;
			cf.py << 0 << 0;
			cf.pz << 0 << -1;
			cf.nx << 11 << 6;
			cf.ny << 5 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 8 << 4;
			cf.pz << 0 << 2;
			cf.nx << 5 << 8;
			cf.ny << 9 << 16;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 2;
			cf.py << 5 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 15;
			cf.ny << 4 << 8;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 4 << 6;
			cf.pz << 1 << 1;
			cf.nx << 11 << 3;
			cf.ny << 7 << 9;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 3 << 3;
			cf.pz << 2 << 2;
			cf.nx << 2 << 2;
			cf.ny << 15 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 18;
			cf.py << 5 << 5;
			cf.pz << 0 << 0;
			cf.nx << 9 << 21;
			cf.ny << 2 << 10;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 14 << 7;
			cf.pz << 0 << 1;
			cf.nx << 3 << 4;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 3;
			cf.py << 3 << 1;
			cf.pz << 1 << -1;
			cf.nx << 19 << 10;
			cf.ny << 12 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 16;
			cf.py << 3 << 8;
			cf.pz << 1 << 0;
			cf.nx << 8 << 10;
			cf.ny << 20 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 5 << 2;
			cf.py << 21 << 8 << 4;
			cf.pz << 0 << 1 << 2;
			cf.nx << 10 << 6 << 3;
			cf.ny << 15 << 2 << 1;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 10 << 12;
			cf.pz << 0 << 0;
			cf.nx << 11 << 11;
			cf.ny << 2 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 3 << 2;
			cf.pz << 1 << 1;
			cf.nx << 8 << 11;
			cf.ny << 3 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 5 << 8;
			cf.pz << 0 << -1;
			cf.nx << 12 << 3;
			cf.ny << 3 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 7;
			cf.py << 2 << 1;
			cf.pz << 0 << 1;
			cf.nx << 5 << 5;
			cf.ny << 1 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 10 << 8;
			cf.pz << 0 << -1;
			cf.nx << 14 << 16;
			cf.ny << 10 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 10;
			cf.py << 7 << 8;
			cf.pz << 1 << -1;
			cf.nx << 2 << 6;
			cf.ny << 5 << 6;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 1 << 8;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 3 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 0;
			cf.py << 5 << 2;
			cf.pz << 1 << -1;
			cf.nx << 1 << 2;
			cf.ny << 2 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 12;
			cf.py << 1 << 9;
			cf.pz << 2 << -1;
			cf.nx << 16 << 17;
			cf.ny << 3 << 3;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 5 << 8;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 7 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 3;
			cf.py << 11 << 5;
			cf.pz << 0 << -1;
			cf.nx << 11 << 4;
			cf.ny << 0 << 0;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 10;
			cf.py << 6 << 6;
			cf.pz << 1 << -1;
			cf.nx << 0 << 0;
			cf.ny << 1 << 0;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 7;
			cf.py << 0 << 7;
			cf.pz << 1 << -1;
			cf.nx << 15 << 13;
			cf.ny << 8 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 1;
			cf.py << 15 << 0;
			cf.pz << 0 << -1;
			cf.nx << 18 << 18;
			cf.ny << 18 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 2;
			cf.py << 4 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 18;
			cf.ny << 4 << 15;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 14 << 13;
			cf.py << 2 << 7 << 8;
			cf.pz << 2 << 0 << 0;
			cf.nx << 10 << 0 << 2;
			cf.ny << 8 << 3 << 2;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 0;
			cf.py << 14 << 3;
			cf.pz << 0 << -1;
			cf.nx << 18 << 3;
			cf.ny << 12 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 8 << 3;
			cf.pz << 1 << 2;
			cf.nx << 13 << 4;
			cf.ny << 10 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 8 << 1;
			cf.ny << 4 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 8 << 3;
			cf.pz << 1 << -1;
			cf.nx << 12 << 7;
			cf.ny << 2 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 3;
			cf.py << 9 << 2;
			cf.pz << 0 << 2;
			cf.nx << 7 << 6;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 1;
			cf.py << 2 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 5;
			cf.py << 15 << 3;
			cf.pz << 0 << 2;
			cf.nx << 16 << 17;
			cf.ny << 14 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 11;
			cf.py << 19 << 13;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 11;
			cf.py << 8 << 1;
			cf.pz << 1 << -1;
			cf.nx << 3 << 3;
			cf.ny << 2 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 3 << 8 << 0;
			cf.py << 7 << 7 << 5;
			cf.pz << 1 << -1 << -1;
			cf.nx << 11 << 5 << 1;
			cf.ny << 11 << 7 << 5;
			cf.nz << 0 << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 9 << 0;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 12;
			cf.py << 7 << 1;
			cf.pz << 0 << -1;
			cf.nx << 16 << 7;
			cf.ny << 6 << 4;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 5;
			cf.py << 14 << 0;
			cf.pz << 0 << -1;
			cf.nx << 13 << 10;
			cf.ny << 0 << 0;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 11 << 12 << 13 << 12 << 7;
			cf.py << 0 << 1 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 1;
			cf.nx << 13 << 16 << 14 << 4 << 4;
			cf.ny << 18 << 23 << 18 << 5 << 5;
			cf.nz << 0 << 0 << 0 << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 5;
			cf.py << 12 << 4;
			cf.pz << 0 << -1;
			cf.nx << 7 << 7;
			cf.ny << 8 << 2;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 3;
			cf.py << 2 << 5;
			cf.pz << 0 << -1;
			cf.nx << 11 << 23;
			cf.ny << 7 << 13;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 19 << 20;
			cf.pz << 0 << 0;
			cf.nx << 9 << 4;
			cf.ny << 5 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 4;
			cf.py << 12 << 3;
			cf.pz << 0 << 2;
			cf.nx << 9 << 5;
			cf.ny << 4 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 0 << 1 << 21;
			cf.py << 6 << 0 << 7 << 16;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 11 << 6 << 11 << 5;
			cf.ny << 8 << 6 << 4 << 3;
			cf.nz << 1 << 1 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 7 << 5;
			cf.pz << 0 << -1;
			cf.nx << 9 << 10;
			cf.ny << 6 << 7;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 16 << 6;
			cf.ny << 0 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 3;
			cf.pz << 1 << 2;
			cf.nx << 1 << 21;
			cf.ny << 23 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 7 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 13;
			cf.ny << 4 << 10;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 4;
			cf.py << 0 << 4;
			cf.pz << 1 << -1;
			cf.nx << 4 << 2;
			cf.ny << 16 << 8;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 3 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 19 << 11;
			cf.pz << 0 << -1;
			cf.nx << 9 << 5;
			cf.ny << 21 << 9;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 17 << 9;
			cf.pz << 0 << 1;
			cf.nx << 0 << 5;
			cf.ny << 0 << 9;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 5;
			cf.py << 2 << 4;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 5 << 6;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 1 << 0;
			cf.pz << 1 << 2;
			cf.nx << 4 << 3;
			cf.ny << 3 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 0;
			cf.py << 7 << 2;
			cf.pz << 1 << -1;
			cf.nx << 5 << 5;
			cf.ny << 1 << 0;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 0;
			cf.py << 17 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 5 << 8;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 0 << 5;
			cf.pz << 2 << -1;
			cf.nx << 4 << 9;
			cf.ny << 2 << 7;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 13 << 8;
			cf.pz << 0 << -1;
			cf.nx << 23 << 11;
			cf.ny << 13 << 7;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 0 << 2;
			cf.pz << 1 << 0;
			cf.nx << 3 << 6;
			cf.ny << 11 << 18;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 6 << 5;
			cf.pz << 0 << -1;
			cf.nx << 1 << 1;
			cf.ny << 1 << 3;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 3 << 6 << 3 << 6;
			cf.py << 3 << 6 << 2 << 5;
			cf.pz << 2 << 1 << 2 << 1;
			cf.nx << 0 << 4 << 1 << 1;
			cf.ny << 0 << 22 << 17 << 0;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 9 << 15;
			cf.ny << 4 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 18;
			cf.py << 7 << 8;
			cf.pz << 1 << 0;
			cf.nx << 8 << 5;
			cf.ny << 4 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 4 << 5;
			cf.pz << 1 << -1;
			cf.nx << 5 << 6;
			cf.ny << 0 << 0;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 18;
			cf.py << 23 << 19;
			cf.pz << 0 << 0;
			cf.nx << 7 << 13;
			cf.ny << 10 << 20;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 6;
			cf.py << 2 << 0;
			cf.pz << 0 << 1;
			cf.nx << 4 << 1;
			cf.ny << 5 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 5 << 4;
			cf.pz << 2 << 2;
			cf.nx << 0 << 20;
			cf.ny << 4 << 4;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 5;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 12 << 6;
			cf.ny << 18 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 2 << 1 << 3 << 1 << 5;
			cf.py << 3 << 3 << 7 << 4 << 9;
			cf.pz << 2 << 2 << 1 << 2 << 1;
			cf.nx << 9 << 3 << 8 << 16 << 10;
			cf.ny << 5 << 3 << 10 << 6 << 7;
			cf.nz << 1 << -1 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 1;
			cf.py << 12 << 3;
			cf.pz << 0 << -1;
			cf.nx << 10 << 1;
			cf.ny << 11 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 0;
			cf.py << 10 << 7;
			cf.pz << 0 << -1;
			cf.nx << 14 << 7;
			cf.ny << 6 << 3;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 6 << 0;
			cf.ny << 2 << 18;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 8;
			cf.py << 3 << 0;
			cf.pz << 0 << 1;
			cf.nx << 17 << 1;
			cf.ny << 1 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 19;
			cf.py << 1 << 17;
			cf.pz << 0 << -1;
			cf.nx << 5 << 11;
			cf.ny << 2 << 5;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 12 << 12 << 12 << 6 << 12;
			cf.py << 10 << 11 << 12 << 6 << 9;
			cf.pz << 0 << 0 << 0 << 1 << 0;
			cf.nx << 13 << 3 << 12 << 6 << 6;
			cf.ny << 4 << 1 << 4 << 2 << 2;
			cf.nz << 0 << 2 << 0 << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 10;
			cf.py << 3 << 3;
			cf.pz << 0 << 0;
			cf.nx << 4 << 9;
			cf.ny << 4 << 17;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 0;
			cf.py << 13 << 5;
			cf.pz << 0 << 2;
			cf.nx << 8 << 18;
			cf.ny << 15 << 15;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 6 << 5;
			cf.pz << 1 << 1;
			cf.nx << 0 << 0;
			cf.ny << 9 << 4;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 2 << 15;
			cf.ny << 2 << 1;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 2 << 4 << 2;
			cf.py << 4 << 9 << 5;
			cf.pz << 2 << 1 << 2;
			cf.nx << 2 << 5 << 14;
			cf.ny << 0 << 1 << 4;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 12;
			cf.py << 20 << 20;
			cf.pz << 0 << 0;
			cf.nx << 6 << 10;
			cf.ny << 9 << 19;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 16 << 8;
			cf.pz << 0 << -1;
			cf.nx << 2 << 3;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 16 << 17 << 15 << 16 << 15;
			cf.py << 1 << 1 << 1 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << 0;
			cf.nx << 8 << 8 << 4 << 12 << 12;
			cf.ny << 8 << 7 << 2 << 23 << 23;
			cf.nz << 1 << 1 << 2 << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 4;
			cf.py << 6 << 12;
			cf.pz << 1 << -1;
			cf.nx << 8 << 13;
			cf.ny << 1 << 1;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 2;
			cf.py << 3 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 6 << 5;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 8;
			cf.py << 6 << 1;
			cf.pz << 1 << -1;
			cf.nx << 11 << 8;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 7 << 0;
			cf.pz << 1 << -1;
			cf.nx << 19 << 19;
			cf.ny << 18 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 2;
			cf.py << 1 << 1;
			cf.pz << 2 << 2;
			cf.nx << 22 << 11;
			cf.ny << 4 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 10;
			cf.py << 9 << 8;
			cf.pz << 1 << 1;
			cf.nx << 4 << 4;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 0 << 5;
			cf.pz << 0 << -1;
			cf.nx << 10 << 8;
			cf.ny << 2 << 2;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 8 << 7;
			cf.pz << 1 << 1;
			cf.nx << 8 << 2;
			cf.ny << 8 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 5;
			cf.py << 21 << 3;
			cf.pz << 0 << -1;
			cf.nx << 13 << 3;
			cf.ny << 20 << 5;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 11 << 2;
			cf.pz << 0 << -1;
			cf.nx << 1 << 0;
			cf.ny << 19 << 9;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 10;
			cf.py << 9 << 10;
			cf.pz << 1 << 1;
			cf.nx << 8 << 4;
			cf.ny << 10 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 9;
			cf.pz << 2 << 1;
			cf.nx << 2 << 11;
			cf.ny << 9 << 19;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 5;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 8 << 23;
			cf.ny << 4 << 9;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 4;
			cf.py << 2 << 4;
			cf.pz << 2 << 1;
			cf.nx << 5 << 9;
			cf.ny << 2 << 5;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 2 << 3;
			cf.pz << 1 << 1;
			cf.nx << 19 << 9;
			cf.ny << 6 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 4;
			cf.py << 5 << 10;
			cf.pz << 1 << -1;
			cf.nx << 10 << 22;
			cf.ny << 0 << 16;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 19 << 9 << 19;
			cf.py << 3 << 1 << 2;
			cf.pz << 0 << 1 << 0;
			cf.nx << 6 << 3 << 6;
			cf.ny << 10 << 3 << 0;
			cf.nz << 1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 10 << 3;
			cf.pz << 1 << 2;
			cf.nx << 23 << 14;
			cf.ny << 3 << 18;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 19 << 0;
			cf.pz << 0 << -1;
			cf.nx << 4 << 16;
			cf.ny << 4 << 11;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 22 << 23;
			cf.py << 3 << 22;
			cf.pz << 0 << -1;
			cf.nx << 9 << 3;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 2;
			cf.py << 12 << 4;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 10 << 5;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 5 << 13;
			cf.pz << 0 << -1;
			cf.nx << 11 << 3;
			cf.ny << 2 << 0;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 17;
			cf.py << 0 << 16;
			cf.pz << 1 << -1;
			cf.nx << 12 << 12;
			cf.ny << 5 << 6;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 4 << 3;
			cf.ny << 0 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 3;
			cf.py << 12 << 0;
			cf.pz << 0 << -1;
			cf.nx << 12 << 12;
			cf.ny << 13 << 12;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 4;
			cf.py << 11 << 14;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 4 << 6;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 7;
			cf.py << 7 << 8;
			cf.pz << 1 << 1;
			cf.nx << 3 << 0;
			cf.ny << 5 << 21;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 3;
			cf.py << 4 << 14;
			cf.pz << 2 << 0;
			cf.nx << 8 << 8;
			cf.ny << 7 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 11;
			cf.py << 20 << 7;
			cf.pz << 0 << -1;
			cf.nx << 21 << 21;
			cf.ny << 20 << 18;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 1;
			cf.py << 11 << 0;
			cf.pz << 0 << -1;
			cf.nx << 2 << 2;
			cf.ny << 15 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 1;
			cf.py << 8 << 0;
			cf.pz << 1 << -1;
			cf.nx << 8 << 4;
			cf.ny << 7 << 4;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 6;
			cf.py << 13 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 15;
			cf.py << 1 << 3;
			cf.pz << 1 << 0;
			cf.nx << 15 << 5;
			cf.ny << 1 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 1;
			cf.py << 20 << 10;
			cf.pz << 0 << -1;
			cf.nx << 6 << 8;
			cf.ny << 11 << 10;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 14;
			cf.py << 0 << 0;
			cf.pz << 1 << 0;
			cf.nx << 7 << 8;
			cf.ny << 7 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 17 << 4;
			cf.pz << 0 << -1;
			cf.nx << 12 << 5;
			cf.ny << 16 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 15 << 0;
			cf.pz << 0 << -1;
			cf.nx << 12 << 7;
			cf.ny << 17 << 8;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 1;
			cf.py << 14 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 6;
			cf.ny << 6 << 12;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 7;
			cf.py << 0 << 0;
			cf.pz << 0 << 0;
			cf.nx << 6 << 20;
			cf.ny << 5 << 5;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 2;
			cf.py << 22 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 8;
			cf.ny << 4 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 8 << 2 << 2 << 9;
			cf.py << 6 << 5 << 3 << 11;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 2 << 7 << 4 << 3;
			cf.ny << 2 << 1 << 0 << 2;
			cf.nz << 2 << 0 << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 12 << 6;
			cf.pz << 0 << 1;
			cf.nx << 8 << 2;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 11;
			cf.py << 19 << 8;
			cf.pz << 0 << -1;
			cf.nx << 13 << 13;
			cf.ny << 20 << 17;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 19;
			cf.py << 5 << 14;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 8 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 0;
			cf.py << 8 << 6;
			cf.pz << 1 << -1;
			cf.nx << 21 << 21;
			cf.ny << 16 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 12;
			cf.py << 7 << 6;
			cf.pz << 1 << -1;
			cf.nx << 2 << 7;
			cf.ny << 5 << 14;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 9;
			cf.py << 7 << 5;
			cf.pz << 1 << -1;
			cf.nx << 2 << 5;
			cf.ny << 5 << 9;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 5;
			cf.py << 15 << 6;
			cf.pz << 0 << -1;
			cf.nx << 3 << 12;
			cf.ny << 0 << 2;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 22;
			cf.py << 23 << 1;
			cf.pz << 0 << -1;
			cf.nx << 0 << 0;
			cf.ny << 2 << 3;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 1 << 2;
			cf.pz << 2 << 1;
			cf.nx << 8 << 0;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 1;
			cf.py << 9 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 2;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 1;
			cf.py << 0 << 0;
			cf.pz << 2 << 0;
			cf.nx << 2 << 3;
			cf.ny << 9 << 10;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 0;
			cf.py << 16 << 14;
			cf.pz << 0 << -1;
			cf.nx << 6 << 3;
			cf.ny << 23 << 14;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 3;
			cf.py << 2 << 3;
			cf.pz << 2 << 1;
			cf.nx << 13 << 3;
			cf.ny << 19 << 14;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 8 << 18;
			cf.pz << 0 << -1;
			cf.nx << 4 << 7;
			cf.ny << 1 << 2;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 4;
			cf.py << 5 << 6;
			cf.pz << 1 << 1;
			cf.nx << 2 << 2;
			cf.ny << 5 << 3;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 3;
			cf.py << 13 << 7;
			cf.pz << 0 << 1;
			cf.nx << 4 << 3;
			cf.ny << 4 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 5 << 6;
			cf.pz << 1 << 0;
			cf.nx << 2 << 1;
			cf.ny << 5 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 14;
			cf.py << 3 << 5;
			cf.pz << 1 << 0;
			cf.nx << 5 << 0;
			cf.ny << 16 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 2;
			cf.py << 18 << 5;
			cf.pz << 0 << 2;
			cf.nx << 11 << 4;
			cf.ny << 16 << 4;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 16;
			cf.py << 19 << 20;
			cf.pz << 0 << -1;
			cf.nx << 3 << 2;
			cf.ny << 10 << 5;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 3;
			cf.py << 3 << 1;
			cf.pz << 0 << 1;
			cf.nx << 1 << 3;
			cf.ny << 4 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 6;
			cf.py << 13 << 6;
			cf.pz << 0 << 1;
			cf.nx << 10 << 1;
			cf.ny << 12 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 3;
			cf.py << 6 << 2;
			cf.pz << 1 << -1;
			cf.nx << 4 << 8;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 9 << 3;
			cf.py << 21 << 2;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 1 << 0;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 4;
			cf.py << 1 << 0;
			cf.pz << 1 << -1;
			cf.nx << 8 << 6;
			cf.ny << 4 << 2;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 7;
			cf.py << 1 << 6;
			cf.pz << 2 << -1;
			cf.nx << 7 << 9;
			cf.ny << 6 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 8 << 3;
			cf.pz << 1 << 2;
			cf.nx << 10 << 5;
			cf.ny << 19 << 11;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 3 << 4;
			cf.pz << 2 << 2;
			cf.nx << 3 << 6;
			cf.ny << 4 << 6;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 11;
			cf.py << 5 << 20;
			cf.pz << 2 << 0;
			cf.nx << 11 << 5;
			cf.ny << 21 << 8;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 5 << 9 << 5;
			cf.py << 4 << 7 << 5;
			cf.pz << 2 << 0 << 2;
			cf.nx << 23 << 10 << 4;
			cf.ny << 23 << 3 << 22;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 11 << 9 << 7 << 1;
			cf.py << 13 << 8 << 11 << 10;
			cf.pz << 0 << -1 << -1 << -1;
			cf.nx << 8 << 2 << 11 << 12;
			cf.ny << 4 << 2 << 4 << 4;
			cf.nz << 1 << 2 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 7 << 6;
			cf.pz << 1 << 1;
			cf.nx << 0 << 4;
			cf.ny << 1 << 0;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 20;
			cf.py << 0 << 1;
			cf.pz << 0 << 0;
			cf.nx << 21 << 1;
			cf.ny << 0 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 5;
			cf.py << 11 << 0;
			cf.pz << 0 << -1;
			cf.nx << 11 << 0;
			cf.ny << 12 << 1;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 1 << 1;
			cf.pz << 0 << -1;
			cf.nx << 4 << 7;
			cf.ny << 5 << 4;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 12;
			cf.py << 4 << 23;
			cf.pz << 2 << -1;
			cf.nx << 13 << 15;
			cf.ny << 5 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 20;
			cf.py << 4 << 16;
			cf.pz << 0 << -1;
			cf.nx << 9 << 4;
			cf.ny << 2 << 1;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 13;
			cf.py << 2 << 2;
			cf.pz << 0 << 0;
			cf.nx << 4 << 16;
			cf.ny << 2 << 11;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 14;
			cf.py << 10 << 17;
			cf.pz << 0 << -1;
			cf.nx << 3 << 8;
			cf.ny << 0 << 2;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 12;
			cf.py << 1 << 2;
			cf.pz << 1 << 0;
			cf.nx << 19 << 10;
			cf.ny << 3 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 17 << 2 << 3 << 10;
			cf.py << 8 << 6 << 2 << 12;
			cf.pz << 0 << 1 << 2 << 0;
			cf.nx << 17 << 9 << 12 << 2;
			cf.ny << 9 << 22 << 13 << 5;
			cf.nz << 0 << -1 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 20 << 10;
			cf.py << 15 << 7;
			cf.pz << 0 << 1;
			cf.nx << 13 << 9;
			cf.ny << 7 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 0;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 10 << 3;
			cf.ny << 9 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 3;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 0 << 22;
			cf.ny << 14 << 6;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 3;
			cf.py << 4 << 0;
			cf.pz << 0 << 2;
			cf.nx << 16 << 3;
			cf.ny << 2 << 0;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 16;
			cf.py << 6 << 12;
			cf.pz << 1 << 0;
			cf.nx << 8 << 12;
			cf.ny << 4 << 7;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 5 << 11;
			cf.py << 0 << 5;
			cf.pz << 2 << 1;
			cf.nx << 10 << 1;
			cf.ny << 5 << 5;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 4;
			cf.py << 5 << 5;
			cf.pz << 0 << -1;
			cf.nx << 3 << 6;
			cf.ny << 2 << 3;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 11;
			cf.py << 11 << 12;
			cf.pz << 0 << 0;
			cf.nx << 23 << 7;
			cf.ny << 20 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 8;
			cf.py << 12 << 5;
			cf.pz << 0 << 1;
			cf.nx << 8 << 2;
			cf.ny << 2 << 1;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 6 << 11 << 11;
			cf.py << 11 << 23 << 20;
			cf.pz << 1 << 0 << 0;
			cf.nx << 11 << 3 << 22;
			cf.ny << 21 << 3 << 16;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 17 << 15;
			cf.py << 3 << 2;
			cf.pz << 0 << -1;
			cf.nx << 4 << 4;
			cf.ny << 3 << 2;
			cf.nz << 2 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 21 << 21;
			cf.py << 11 << 10;
			cf.pz << 0 << 0;
			cf.nx << 11 << 3;
			cf.ny << 6 << 2;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 21;
			cf.py << 22 << 10;
			cf.pz << 0 << -1;
			cf.nx << 20 << 10;
			cf.ny << 18 << 10;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 4 << 2;
			cf.py << 6 << 3;
			cf.pz << 1 << 2;
			cf.nx << 3 << 2;
			cf.ny << 4 << 3;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 16 << 0;
			cf.py << 18 << 11;
			cf.pz << 0 << -1;
			cf.nx << 8 << 7;
			cf.ny << 4 << 4;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 21;
			cf.py << 3 << 16;
			cf.pz << 0 << -1;
			cf.nx << 1 << 8;
			cf.ny << 2 << 14;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 8 << 1;
			cf.py << 3 << 0;
			cf.pz << 0 << -1;
			cf.nx << 11 << 11;
			cf.ny << 2 << 1;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 11 << 11;
			cf.py << 9 << 10 << 8;
			cf.pz << 1 << 1 << 1;
			cf.nx << 23 << 1 << 0;
			cf.ny << 23 << 9 << 11;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 3;
			cf.py << 2 << 1;
			cf.pz << 1 << 2;
			cf.nx << 7 << 1;
			cf.ny << 8 << 2;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 17;
			cf.py << 17 << 19;
			cf.pz << 0 << -1;
			cf.nx << 10 << 4;
			cf.ny << 16 << 9;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 7 << 1;
			cf.pz << 1 << -1;
			cf.nx << 11 << 0;
			cf.ny << 11 << 8;
			cf.nz << 0 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 5;
			cf.py << 11 << 4;
			cf.pz << 1 << 2;
			cf.nx << 5 << 5;
			cf.ny << 0 << 0;
			cf.nz << 2 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 6;
			cf.py << 3 << 6;
			cf.pz << 2 << 1;
			cf.nx << 8 << 0;
			cf.ny << 4 << 16;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 1;
			cf.py << 20 << 2;
			cf.pz << 0 << -1;
			cf.nx << 7 << 7;
			cf.ny << 11 << 9;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 11 << 13 << 4;
			cf.py << 16 << 21 << 3;
			cf.pz << 0 << 0 << 2;
			cf.nx << 14 << 16 << 5;
			cf.ny << 20 << 14 << 9;
			cf.nz << 0 << -1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 7 << 0;
			cf.py << 1 << 1;
			cf.pz << 1 << -1;
			cf.nx << 4 << 7;
			cf.ny << 2 << 4;
			cf.nz << 2 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 23 << 11;
			cf.py << 9 << 4;
			cf.pz << 0 << 1;
			cf.nx << 11 << 3;
			cf.ny << 1 << 3;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 13;
			cf.py << 23 << 23;
			cf.pz << 0 << 0;
			cf.nx << 13 << 13;
			cf.ny << 20 << 20;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 8;
			cf.py << 5 << 11;
			cf.pz << 0 << -1;
			cf.nx << 20 << 19;
			cf.ny << 18 << 20;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 5;
			cf.py << 22 << 4;
			cf.pz << 0 << -1;
			cf.nx << 2 << 9;
			cf.ny << 3 << 17;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 2;
			cf.py << 13 << 7;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 14 << 13;
			cf.py << 17 << 2;
			cf.pz << 0 << -1;
			cf.nx << 15 << 13;
			cf.ny << 19 << 15;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 12 << 23;
			cf.py << 8 << 22;
			cf.pz << 0 << -1;
			cf.nx << 7 << 10;
			cf.ny << 5 << 9;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 6;
			cf.py << 21 << 10;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 3 << 3;
			cf.nz << 1 << 1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 11;
			cf.py << 5 << 0;
			cf.pz << 0 << -1;
			cf.nx << 3 << 4;
			cf.ny << 17 << 16;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 3 << 1;
			cf.py << 18 << 8;
			cf.pz << 0 << 1;
			cf.nx << 14 << 4;
			cf.ny << 17 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 15 << 3;
			cf.py << 18 << 3;
			cf.pz << 0 << 2;
			cf.nx << 1 << 22;
			cf.ny << 0 << 1;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 13 << 3;
			cf.py << 9 << 3;
			cf.pz << 0 << -1;
			cf.nx << 0 << 1;
			cf.ny << 9 << 20;
			cf.nz << 1 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 1 << 1;
			cf.py << 1 << 0;
			cf.pz << 2 << 2;
			cf.nx << 9 << 23;
			cf.ny << 10 << 12;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 4;
			cf.Reserve(4);
			cf.px << 9 << 0 << 9 << 1;
			cf.py << 8 << 0 << 0 << 10;
			cf.pz << 1 << -1 << -1 << -1;
			cf.nx << 23 << 7 << 5 << 23;
			cf.ny << 20 << 7 << 5 << 19;
			cf.nz << 0 << 1 << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 18 << 18;
			cf.py << 12 << 12;
			cf.pz << 0 << -1;
			cf.nx << 8 << 4;
			cf.ny << 4 << 2;
			cf.nz << 1 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 3;
			cf.Reserve(3);
			cf.px << 0 << 4 << 1;
			cf.py << 3 << 5 << 3;
			cf.pz << 1 << -1 << -1;
			cf.nx << 16 << 11 << 8;
			cf.ny << 8 << 5 << 6;
			cf.nz << 0 << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 5;
			cf.Reserve(5);
			cf.px << 9 << 10 << 14 << 11 << 11;
			cf.py << 0 << 0 << 0 << 0 << 0;
			cf.pz << 0 << 0 << 0 << 0 << -1;
			cf.nx << 8 << 3 << 4 << 6 << 2;
			cf.ny << 22 << 9 << 5 << 4 << 0;
			cf.nz << 0 << 1 << 0 << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 5;
			cf.py << 2 << 2;
			cf.pz << 1 << 1;
			cf.nx << 7 << 3;
			cf.ny << 8 << 7;
			cf.nz << 0 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 5;
			cf.py << 15 << 2;
			cf.pz << 0 << -1;
			cf.nx << 3 << 10;
			cf.ny << 0 << 1;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 0 << 11;
			cf.py << 11 << 12;
			cf.pz << 1 << -1;
			cf.nx << 22 << 22;
			cf.ny << 14 << 13;
			cf.nz << 0 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 2;
			cf.py << 15 << 14;
			cf.pz << 0 << 0;
			cf.nx << 1 << 2;
			cf.ny << 11 << 8;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 11 << 6;
			cf.py << 0 << 7;
			cf.pz << 1 << -1;
			cf.nx << 19 << 5;
			cf.ny << 3 << 0;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 2 << 3;
			cf.py << 3 << 7;
			cf.pz << 2 << 1;
			cf.nx << 1 << 5;
			cf.ny << 5 << 0;
			cf.nz << 1 << -1;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 10 << 14;
			cf.py << 4 << 5;
			cf.pz << 0 << -1;
			cf.nx << 4 << 18;
			cf.ny << 2 << 12;
			cf.nz << 2 << 0;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 19 << 10;
			cf.py << 12 << 2;
			cf.pz << 0 << -1;
			cf.nx << 13 << 4;
			cf.ny << 10 << 2;
			cf.nz << 0 << 2;
		}
		{
			CascadeFeature& cf = *cf_iter++;
			cf.size = 2;
			cf.Reserve(2);
			cf.px << 6 << 1;
			cf.py << 21 << 6;
			cf.pz << 0 << -1;
			cf.nx << 6 << 5;
			cf.ny << 0 << 0;
			cf.nz << 1 << 1;
		}
		*a_iter++ = -1.044179;
		*a_iter++ = 1.044179;
		*a_iter++ = -0.6003138;
		*a_iter++ = 0.6003138;
		*a_iter++ = -0.4091282;
		*a_iter++ = 0.4091282;
		*a_iter++ = -0.4590148;
		*a_iter++ = 0.4590148;
		*a_iter++ = -0.4294004;
		*a_iter++ = 0.4294004;
		*a_iter++ = -0.3360846;
		*a_iter++ = 0.3360846;
		*a_iter++ = -0.3054186;
		*a_iter++ = 0.3054186;
		*a_iter++ = -0.2901743;
		*a_iter++ = 0.2901743;
		*a_iter++ = -0.3522417;
		*a_iter++ = 0.3522417;
		*a_iter++ = -0.3195838;
		*a_iter++ = 0.3195838;
		*a_iter++ = -0.2957309;
		*a_iter++ = 0.2957309;
		*a_iter++ = -0.2876727;
		*a_iter++ = 0.2876727;
		*a_iter++ = -0.263746;
		*a_iter++ = 0.263746;
		*a_iter++ = -0.26079;
		*a_iter++ = 0.26079;
		*a_iter++ = -0.2455714;
		*a_iter++ = 0.2455714;
		*a_iter++ = -0.2749847;
		*a_iter++ = 0.2749847;
		*a_iter++ = -0.2314217;
		*a_iter++ = 0.2314217;
		*a_iter++ = -0.2540871;
		*a_iter++ = 0.2540871;
		*a_iter++ = -0.2143416;
		*a_iter++ = 0.2143416;
		*a_iter++ = -0.2565697;
		*a_iter++ = 0.2565697;
		*a_iter++ = -0.1901272;
		*a_iter++ = 0.1901272;
		*a_iter++ = -0.2259981;
		*a_iter++ = 0.2259981;
		*a_iter++ = -0.2012333;
		*a_iter++ = 0.2012333;
		*a_iter++ = -0.244846;
		*a_iter++ = 0.244846;
		*a_iter++ = -0.2192845;
		*a_iter++ = 0.2192845;
		*a_iter++ = -0.2005951;
		*a_iter++ = 0.2005951;
		*a_iter++ = -0.2259;
		*a_iter++ = 0.2259;
		*a_iter++ = -0.1955758;
		*a_iter++ = 0.1955758;
		*a_iter++ = -0.2235332;
		*a_iter++ = 0.2235332;
		*a_iter++ = -0.170449;
		*a_iter++ = 0.170449;
		*a_iter++ = -0.1584628;
		*a_iter++ = 0.1584628;
		*a_iter++ = -0.216771;
		*a_iter++ = 0.216771;
		*a_iter++ = -0.1592909;
		*a_iter++ = 0.1592909;
		*a_iter++ = -0.1967292;
		*a_iter++ = 0.1967292;
		*a_iter++ = -0.1432268;
		*a_iter++ = 0.1432268;
		*a_iter++ = -0.2039949;
		*a_iter++ = 0.2039949;
		*a_iter++ = -0.1404068;
		*a_iter++ = 0.1404068;
		*a_iter++ = -0.1788201;
		*a_iter++ = 0.1788201;
		*a_iter++ = -0.1498714;
		*a_iter++ = 0.1498714;
		*a_iter++ = -0.1282541;
		*a_iter++ = 0.1282541;
		*a_iter++ = -0.1630182;
		*a_iter++ = 0.1630182;
		*a_iter++ = -0.1398111;
		*a_iter++ = 0.1398111;
		*a_iter++ = -0.1464143;
		*a_iter++ = 0.1464143;
		*a_iter++ = -0.1281712;
		*a_iter++ = 0.1281712;
		*a_iter++ = -0.1417014;
		*a_iter++ = 0.1417014;
		*a_iter++ = -0.1779164;
		*a_iter++ = 0.1779164;
		*a_iter++ = -0.2067174;
		*a_iter++ = 0.2067174;
		*a_iter++ = -0.1344947;
		*a_iter++ = 0.1344947;
		*a_iter++ = -0.1357351;
		*a_iter++ = 0.1357351;
		*a_iter++ = -0.1683191;
		*a_iter++ = 0.1683191;
		*a_iter++ = -0.1821768;
		*a_iter++ = 0.1821768;
		*a_iter++ = -0.2158307;
		*a_iter++ = 0.2158307;
		*a_iter++ = -0.1812857;
		*a_iter++ = 0.1812857;
		*a_iter++ = -0.1635445;
		*a_iter++ = 0.1635445;
		*a_iter++ = -0.1474934;
		*a_iter++ = 0.1474934;
		*a_iter++ = -0.1771993;
		*a_iter++ = 0.1771993;
		*a_iter++ = -0.151762;
		*a_iter++ = 0.151762;
		*a_iter++ = -0.1283184;
		*a_iter++ = 0.1283184;
		*a_iter++ = -0.1862675;
		*a_iter++ = 0.1862675;
		*a_iter++ = -0.1420491;
		*a_iter++ = 0.1420491;
		*a_iter++ = -0.1232165;
		*a_iter++ = 0.1232165;
		*a_iter++ = -0.1472696;
		*a_iter++ = 0.1472696;
		*a_iter++ = -0.1192156;
		*a_iter++ = 0.1192156;
		*a_iter++ = -0.1602034;
		*a_iter++ = 0.1602034;
		*a_iter++ = -0.1321473;
		*a_iter++ = 0.1321473;
		*a_iter++ = -0.1358101;
		*a_iter++ = 0.1358101;
		*a_iter++ = -0.1295821;
		*a_iter++ = 0.1295821;
		*a_iter++ = -0.1289102;
		*a_iter++ = 0.1289102;
		*a_iter++ = -0.123252;
		*a_iter++ = 0.123252;
		*a_iter++ = -0.1332227;
		*a_iter++ = 0.1332227;
		*a_iter++ = -0.1358887;
		*a_iter++ = 0.1358887;
		*a_iter++ = -0.1179559;
		*a_iter++ = 0.1179559;
		*a_iter++ = -0.1263694;
		*a_iter++ = 0.1263694;
		*a_iter++ = -0.1444876;
		*a_iter++ = 0.1444876;
		*a_iter++ = -0.1933141;
		*a_iter++ = 0.1933141;
		*a_iter++ = -0.1917886;
		*a_iter++ = 0.1917886;
		*a_iter++ = -0.119976;
		*a_iter++ = 0.119976;
		*a_iter++ = -0.1359937;
		*a_iter++ = 0.1359937;
		*a_iter++ = -0.1690073;
		*a_iter++ = 0.1690073;
		*a_iter++ = -0.1894222;
		*a_iter++ = 0.1894222;
		*a_iter++ = -0.1699422;
		*a_iter++ = 0.1699422;
		*a_iter++ = -0.1340361;
		*a_iter++ = 0.1340361;
		*a_iter++ = -0.1840622;
		*a_iter++ = 0.1840622;
		*a_iter++ = -0.1277397;
		*a_iter++ = 0.1277397;
		*a_iter++ = -0.138161;
		*a_iter++ = 0.138161;
		*a_iter++ = -0.1282241;
		*a_iter++ = 0.1282241;
		*a_iter++ = -0.1211334;
		*a_iter++ = 0.1211334;
		*a_iter++ = -0.1264628;
		*a_iter++ = 0.1264628;
		*a_iter++ = -0.137301;
		*a_iter++ = 0.137301;
		*a_iter++ = -0.1363356;
		*a_iter++ = 0.1363356;
		*a_iter++ = -0.1562568;
		*a_iter++ = 0.1562568;
		*a_iter++ = -0.1268735;
		*a_iter++ = 0.1268735;
		*a_iter++ = -0.1037859;
		*a_iter++ = 0.1037859;
		*a_iter++ = -0.1394322;
		*a_iter++ = 0.1394322;
		*a_iter++ = -0.1449225;
		*a_iter++ = 0.1449225;
		*a_iter++ = -0.1109657;
		*a_iter++ = 0.1109657;
		*a_iter++ = -0.1086931;
		*a_iter++ = 0.1086931;
		*a_iter++ = -0.1379135;
		*a_iter++ = 0.1379135;
		*a_iter++ = -0.1881974;
		*a_iter++ = 0.1881974;
		*a_iter++ = -0.1304956;
		*a_iter++ = 0.1304956;
		*a_iter++ = -0.09921777;
		*a_iter++ = 0.09921777;
		*a_iter++ = -0.1398624;
		*a_iter++ = 0.1398624;
		*a_iter++ = -0.1216469;
		*a_iter++ = 0.1216469;
		*a_iter++ = -0.1272741;
		*a_iter++ = 0.1272741;
		*a_iter++ = -0.1878236;
		*a_iter++ = 0.1878236;
		*a_iter++ = -0.1336894;
		*a_iter++ = 0.1336894;
		*a_iter++ = -0.1256289;
		*a_iter++ = 0.1256289;
		*a_iter++ = -0.1247231;
		*a_iter++ = 0.1247231;
		*a_iter++ = -0.18534;
		*a_iter++ = 0.18534;
		*a_iter++ = -0.1087805;
		*a_iter++ = 0.1087805;
		*a_iter++ = -0.1205676;
		*a_iter++ = 0.1205676;
		*a_iter++ = -0.1023182;
		*a_iter++ = 0.1023182;
		*a_iter++ = -0.1268422;
		*a_iter++ = 0.1268422;
		*a_iter++ = -0.14229;
		*a_iter++ = 0.14229;
		*a_iter++ = -0.1098174;
		*a_iter++ = 0.1098174;
		*a_iter++ = -0.1317018;
		*a_iter++ = 0.1317018;
		*a_iter++ = -0.1378142;
		*a_iter++ = 0.1378142;
		*a_iter++ = -0.127455;
		*a_iter++ = 0.127455;
		*a_iter++ = -0.1142944;
		*a_iter++ = 0.1142944;
		*a_iter++ = -0.1713488;
		*a_iter++ = 0.1713488;
		*a_iter++ = -0.1103035;
		*a_iter++ = 0.1103035;
		*a_iter++ = -0.1045221;
		*a_iter++ = 0.1045221;
		*a_iter++ = -0.1293015;
		*a_iter++ = 0.1293015;
		*a_iter++ = -0.09763183;
		*a_iter++ = 0.09763183;
		*a_iter++ = -0.1387213;
		*a_iter++ = 0.1387213;
		*a_iter++ = -0.09031167;
		*a_iter++ = 0.09031167;
		*a_iter++ = -0.1283052;
		*a_iter++ = 0.1283052;
		*a_iter++ = -0.1133462;
		*a_iter++ = 0.1133462;
		*a_iter++ = -0.09370681;
		*a_iter++ = 0.09370681;
		*a_iter++ = -0.1079269;
		*a_iter++ = 0.1079269;
		*a_iter++ = -0.1331913;
		*a_iter++ = 0.1331913;
		*a_iter++ = -0.08969902;
		*a_iter++ = 0.08969902;
		*a_iter++ = -0.104456;
		*a_iter++ = 0.104456;
		*a_iter++ = -0.09387466;
		*a_iter++ = 0.09387466;
		*a_iter++ = -0.1208988;
		*a_iter++ = 0.1208988;
		*a_iter++ = -0.1252011;
		*a_iter++ = 0.1252011;
		*a_iter++ = -0.1401277;
		*a_iter++ = 0.1401277;
		*a_iter++ = -0.1461381;
		*a_iter++ = 0.1461381;
		*a_iter++ = -0.1323763;
		*a_iter++ = 0.1323763;
		*a_iter++ = -0.09923889;
		*a_iter++ = 0.09923889;
		*a_iter++ = -0.1142899;
		*a_iter++ = 0.1142899;
		*a_iter++ = -0.09110853;
		*a_iter++ = 0.09110853;
		*a_iter++ = -0.1106607;
		*a_iter++ = 0.1106607;
		*a_iter++ = -0.125314;
		*a_iter++ = 0.125314;
		*a_iter++ = -0.09657895;
		*a_iter++ = 0.09657895;
		*a_iter++ = -0.103001;
		*a_iter++ = 0.103001;
		*a_iter++ = -0.1348857;
		*a_iter++ = 0.1348857;
		*a_iter++ = -0.1237793;
		*a_iter++ = 0.1237793;
		*a_iter++ = -0.1296943;
		*a_iter++ = 0.1296943;
		*a_iter++ = -0.1323385;
		*a_iter++ = 0.1323385;
		*a_iter++ = -0.08331554;
		*a_iter++ = 0.08331554;
		*a_iter++ = -0.08417589;
		*a_iter++ = 0.08417589;
		*a_iter++ = -0.1104431;
		*a_iter++ = 0.1104431;
		*a_iter++ = -0.117071;
		*a_iter++ = 0.117071;
		*a_iter++ = -0.1391725;
		*a_iter++ = 0.1391725;
		*a_iter++ = -0.1485189;
		*a_iter++ = 0.1485189;
		*a_iter++ = -0.1840393;
		*a_iter++ = 0.1840393;
		*a_iter++ = -0.123825;
		*a_iter++ = 0.123825;
		*a_iter++ = -0.1095287;
		*a_iter++ = 0.1095287;
		*a_iter++ = -0.1177869;
		*a_iter++ = 0.1177869;
		*a_iter++ = -0.1036409;
		*a_iter++ = 0.1036409;
		*a_iter++ = -0.09802581;
		*a_iter++ = 0.09802581;
		*a_iter++ = -0.09364054;
		*a_iter++ = 0.09364054;
		*a_iter++ = -0.09936022;
		*a_iter++ = 0.09936022;
		*a_iter++ = -0.1117201;
		*a_iter++ = 0.1117201;
		*a_iter++ = -0.10813;
		*a_iter++ = 0.10813;
		*a_iter++ = -0.1331861;
		*a_iter++ = 0.1331861;
		*a_iter++ = -0.1192122;
		*a_iter++ = 0.1192122;
		*a_iter++ = -0.09889761;
		*a_iter++ = 0.09889761;
		*a_iter++ = -0.1173456;
		*a_iter++ = 0.1173456;
		*a_iter++ = -0.1032917;
		*a_iter++ = 0.1032917;
		*a_iter++ = -0.09268551;
		*a_iter++ = 0.09268551;
		*a_iter++ = -0.1178563;
		*a_iter++ = 0.1178563;
		*a_iter++ = -0.1215065;
		*a_iter++ = 0.1215065;
		*a_iter++ = -0.1060437;
		*a_iter++ = 0.1060437;
		*a_iter++ = -0.1010044;
		*a_iter++ = 0.1010044;
		*a_iter++ = -0.1021683;
		*a_iter++ = 0.1021683;
		*a_iter++ = -0.09974968;
		*a_iter++ = 0.09974968;
		*a_iter++ = -0.1161528;
		*a_iter++ = 0.1161528;
		*a_iter++ = -0.08686721;
		*a_iter++ = 0.08686721;
		*a_iter++ = -0.08145259;
		*a_iter++ = 0.08145259;
		*a_iter++ = -0.0993706;
		*a_iter++ = 0.0993706;
		*a_iter++ = -0.1170885;
		*a_iter++ = 0.1170885;
		*a_iter++ = -0.07693779;
		*a_iter++ = 0.07693779;
		*a_iter++ = -0.09047233;
		*a_iter++ = 0.09047233;
		*a_iter++ = -0.09168442;
		*a_iter++ = 0.09168442;
		*a_iter++ = -0.1054105;
		*a_iter++ = 0.1054105;
		*a_iter++ = -0.09036177;
		*a_iter++ = 0.09036177;
		*a_iter++ = -0.1251949;
		*a_iter++ = 0.1251949;
		*a_iter++ = -0.09523847;
		*a_iter++ = 0.09523847;
		*a_iter++ = -0.103893;
		*a_iter++ = 0.103893;
		*a_iter++ = -0.143366;
		*a_iter++ = 0.143366;
		*a_iter++ = -0.148983;
		*a_iter++ = 0.148983;
		*a_iter++ = -0.08393174;
		*a_iter++ = 0.08393174;
		*a_iter++ = -0.08888026;
		*a_iter++ = 0.08888026;
		*a_iter++ = -0.09347861;
		*a_iter++ = 0.09347861;
		*a_iter++ = -0.1044838;
		*a_iter++ = 0.1044838;
		*a_iter++ = -0.1102144;
		*a_iter++ = 0.1102144;
		*a_iter++ = -0.1383415;
		*a_iter++ = 0.1383415;
		*a_iter++ = -0.1466476;
		*a_iter++ = 0.1466476;
		*a_iter++ = -0.1129741;
		*a_iter++ = 0.1129741;
		*a_iter++ = -0.1310915;
		*a_iter++ = 0.1310915;
		*a_iter++ = -0.1070648;
		*a_iter++ = 0.1070648;
		*a_iter++ = -0.07559007;
		*a_iter++ = 0.07559007;
		*a_iter++ = -0.08812082;
		*a_iter++ = 0.08812082;
		*a_iter++ = -0.1234272;
		*a_iter++ = 0.1234272;
		*a_iter++ = -0.1088022;
		*a_iter++ = 0.1088022;
		*a_iter++ = -0.08388703;
		*a_iter++ = 0.08388703;
		*a_iter++ = -0.07179593;
		*a_iter++ = 0.07179593;
		*a_iter++ = -0.1008961;
		*a_iter++ = 0.1008961;
		*a_iter++ = -0.0903007;
		*a_iter++ = 0.0903007;
		*a_iter++ = -0.08581345;
		*a_iter++ = 0.08581345;
		*a_iter++ = -0.09023431;
		*a_iter++ = 0.09023431;
		*a_iter++ = -0.09807321;
		*a_iter++ = 0.09807321;
		*a_iter++ = -0.09621402;
		*a_iter++ = 0.09621402;
		*a_iter++ = -0.1730195;
		*a_iter++ = 0.1730195;
		*a_iter++ = -0.08984631;
		*a_iter++ = 0.08984631;
		*a_iter++ = -0.09556661;
		*a_iter++ = 0.09556661;
		*a_iter++ = -0.1047576;
		*a_iter++ = 0.1047576;
		*a_iter++ = -0.07854313;
		*a_iter++ = 0.07854313;
		*a_iter++ = -0.08682118;
		*a_iter++ = 0.08682118;
		*a_iter++ = -0.1159761;
		*a_iter++ = 0.1159761;
		*a_iter++ = -0.133954;
		*a_iter++ = 0.133954;
		*a_iter++ = -0.1003048;
		*a_iter++ = 0.1003048;
		*a_iter++ = -0.09747544;
		*a_iter++ = 0.09747544;
		*a_iter++ = -0.09501058;
		*a_iter++ = 0.09501058;
		*a_iter++ = -0.1321566;
		*a_iter++ = 0.1321566;
		*a_iter++ = -0.09194706;
		*a_iter++ = 0.09194706;
		*a_iter++ = -0.09359276;
		*a_iter++ = 0.09359276;
		*a_iter++ = -0.1015916;
		*a_iter++ = 0.1015916;
		*a_iter++ = -0.1174192;
		*a_iter++ = 0.1174192;
		*a_iter++ = -0.1039931;
		*a_iter++ = 0.1039931;
		*a_iter++ = -0.09746733;
		*a_iter++ = 0.09746733;
		*a_iter++ = -0.128612;
		*a_iter++ = 0.128612;
		*a_iter++ = -0.1044899;
		*a_iter++ = 0.1044899;
		*a_iter++ = -0.1066385;
		*a_iter++ = 0.1066385;
		*a_iter++ = -0.08368626;
		*a_iter++ = 0.08368626;
		*a_iter++ = -0.1271919;
		*a_iter++ = 0.1271919;
		*a_iter++ = -0.1055946;
		*a_iter++ = 0.1055946;
		*a_iter++ = -0.08272876;
		*a_iter++ = 0.08272876;
		*a_iter++ = -0.1370564;
		*a_iter++ = 0.1370564;
		*a_iter++ = -0.08539379;
		*a_iter++ = 0.08539379;
		*a_iter++ = -0.1100343;
		*a_iter++ = 0.1100343;
		*a_iter++ = -0.0810217;
		*a_iter++ = 0.0810217;
		*a_iter++ = -0.1028728;
		*a_iter++ = 0.1028728;
		*a_iter++ = -0.1305065;
		*a_iter++ = 0.1305065;
		*a_iter++ = -0.1059506;
		*a_iter++ = 0.1059506;
		*a_iter++ = -0.1264646;
		*a_iter++ = 0.1264646;
		*a_iter++ = -0.08383843;
		*a_iter++ = 0.08383843;
		*a_iter++ = -0.09357698;
		*a_iter++ = 0.09357698;
		*a_iter++ = -0.074744;
		*a_iter++ = 0.074744;
		*a_iter++ = -0.07814045;
		*a_iter++ = 0.07814045;
		*a_iter++ = -0.0860097;
		*a_iter++ = 0.0860097;
		*a_iter++ = -0.120609;
		*a_iter++ = 0.120609;
		*a_iter++ = -0.09986512;
		*a_iter++ = 0.09986512;
		*a_iter++ = -0.08516476;
		*a_iter++ = 0.08516476;
		*a_iter++ = -0.07198783;
		*a_iter++ = 0.07198783;
		*a_iter++ = -0.07838409;
		*a_iter++ = 0.07838409;
		*a_iter++ = -0.1005142;
		*a_iter++ = 0.1005142;
		*a_iter++ = -0.09951857;
		*a_iter++ = 0.09951857;
		*a_iter++ = -0.07253998;
		*a_iter++ = 0.07253998;
		*a_iter++ = -0.09913739;
		*a_iter++ = 0.09913739;
		*a_iter++ = -0.0750036;
		*a_iter++ = 0.0750036;
		*a_iter++ = -0.0925809;
		*a_iter++ = 0.0925809;
		*a_iter++ = -0.1400287;
		*a_iter++ = 0.1400287;
		*a_iter++ = -0.1044404;
		*a_iter++ = 0.1044404;
		*a_iter++ = -0.07404339;
		*a_iter++ = 0.07404339;
		*a_iter++ = -0.07256833;
		*a_iter++ = 0.07256833;
		*a_iter++ = -0.1006995;
		*a_iter++ = 0.1006995;
		*a_iter++ = -0.1426043;
		*a_iter++ = 0.1426043;
		*a_iter++ = -0.1036529;
		*a_iter++ = 0.1036529;
		*a_iter++ = -0.1208443;
		*a_iter++ = 0.1208443;
		*a_iter++ = -0.1074245;
		*a_iter++ = 0.1074245;
		*a_iter++ = -0.1141448;
		*a_iter++ = 0.1141448;
		*a_iter++ = -0.1015809;
		*a_iter++ = 0.1015809;
		*a_iter++ = -0.1028822;
		*a_iter++ = 0.1028822;
		*a_iter++ = -0.1055682;
		*a_iter++ = 0.1055682;
		*a_iter++ = -0.09468699;
		*a_iter++ = 0.09468699;
		*a_iter++ = -0.1010098;
		*a_iter++ = 0.1010098;
		*a_iter++ = -0.1205054;
		*a_iter++ = 0.1205054;
		*a_iter++ = -0.08392956;
		*a_iter++ = 0.08392956;
		*a_iter++ = -0.08052297;
		*a_iter++ = 0.08052297;
		*a_iter++ = -0.09576507;
		*a_iter++ = 0.09576507;
		*a_iter++ = -0.09515692;
		*a_iter++ = 0.09515692;
		*a_iter++ = -0.1564745;
		*a_iter++ = 0.1564745;
		*a_iter++ = -0.07357238;
		*a_iter++ = 0.07357238;
		*a_iter++ = -0.1129262;
		*a_iter++ = 0.1129262;
		*a_iter++ = -0.1013265;
		*a_iter++ = 0.1013265;
		*a_iter++ = -0.08760761;
		*a_iter++ = 0.08760761;
		*a_iter++ = -0.08714771;
		*a_iter++ = 0.08714771;
		*a_iter++ = -0.09605039;
		*a_iter++ = 0.09605039;
		*a_iter++ = -0.09064677;
		*a_iter++ = 0.09064677;
		*a_iter++ = -0.08243857;
		*a_iter++ = 0.08243857;
		*a_iter++ = -0.08495858;
		*a_iter++ = 0.08495858;
		*a_iter++ = -0.08350249;
		*a_iter++ = 0.08350249;
		*a_iter++ = -0.07423234;
		*a_iter++ = 0.07423234;
		*a_iter++ = -0.07930799;
		*a_iter++ = 0.07930799;
		*a_iter++ = -0.06620023;
		*a_iter++ = 0.06620023;
		*a_iter++ = -0.07311919;
		*a_iter++ = 0.07311919;
		*a_iter++ = -0.1237938;
		*a_iter++ = 0.1237938;
		*a_iter++ = -0.1086814;
		*a_iter++ = 0.1086814;
		*a_iter++ = -0.06379798;
		*a_iter++ = 0.06379798;
		*a_iter++ = -0.07526021;
		*a_iter++ = 0.07526021;
		*a_iter++ = -0.08297097;
		*a_iter++ = 0.08297097;
		*a_iter++ = -0.08186337;
		*a_iter++ = 0.08186337;
		*a_iter++ = -0.07627362;
		*a_iter++ = 0.07627362;
		*a_iter++ = -0.1061638;
		*a_iter++ = 0.1061638;
		*a_iter++ = -0.08328494;
		*a_iter++ = 0.08328494;
		*a_iter++ = -0.1040895;
		*a_iter++ = 0.1040895;
		*a_iter++ = -0.07649056;
		*a_iter++ = 0.07649056;
		*a_iter++ = -0.07299058;
		*a_iter++ = 0.07299058;
		*a_iter++ = -0.09195198;
		*a_iter++ = 0.09195198;
		*a_iter++ = -0.0799088;
		*a_iter++ = 0.0799088;
		*a_iter++ = -0.07429346;
		*a_iter++ = 0.07429346;
		*a_iter++ = -0.09991702;
		*a_iter++ = 0.09991702;
		*a_iter++ = -0.09755385;
		*a_iter++ = 0.09755385;
		*a_iter++ = -0.1344138;
		*a_iter++ = 0.1344138;
		*a_iter++ = -0.1707917;
		*a_iter++ = 0.1707917;
		*a_iter++ = -0.0832545;
		*a_iter++ = 0.0832545;
		*a_iter++ = -0.08137793;
		*a_iter++ = 0.08137793;
		*a_iter++ = -0.08308659;
		*a_iter++ = 0.08308659;
		*a_iter++ = -0.07440414;
		*a_iter++ = 0.07440414;
		*a_iter++ = -0.07012744;
		*a_iter++ = 0.07012744;
		*a_iter++ = -0.08122943;
		*a_iter++ = 0.08122943;
		*a_iter++ = -0.08845462;
		*a_iter++ = 0.08845462;
		*a_iter++ = -0.0880345;
		*a_iter++ = 0.0880345;
		*a_iter++ = -0.09653392;
		*a_iter++ = 0.09653392;
		*a_iter++ = -0.08795691;
		*a_iter++ = 0.08795691;
		*a_iter++ = -0.1119045;
		*a_iter++ = 0.1119045;
		*a_iter++ = -0.1068308;
		*a_iter++ = 0.1068308;
		*a_iter++ = -0.08406359;
		*a_iter++ = 0.08406359;
		*a_iter++ = -0.1220414;
		*a_iter++ = 0.1220414;
		*a_iter++ = -0.1024235;
		*a_iter++ = 0.1024235;
		*a_iter++ = -0.1252897;
		*a_iter++ = 0.1252897;
		*a_iter++ = -0.1121234;
		*a_iter++ = 0.1121234;
		*a_iter++ = -0.0905415;
		*a_iter++ = 0.0905415;
		*a_iter++ = -0.08974435;
		*a_iter++ = 0.08974435;
		*a_iter++ = -0.1351578;
		*a_iter++ = 0.1351578;
		*a_iter++ = -0.1106442;
		*a_iter++ = 0.1106442;
		*a_iter++ = -0.08093913;
		*a_iter++ = 0.08093913;
		*a_iter++ = -0.09800762;
		*a_iter++ = 0.09800762;
		*a_iter++ = -0.07012823;
		*a_iter++ = 0.07012823;
		*a_iter++ = -0.07434949;
		*a_iter++ = 0.07434949;
		*a_iter++ = -0.08684816;
		*a_iter++ = 0.08684816;
		*a_iter++ = -0.08916388;
		*a_iter++ = 0.08916388;
		*a_iter++ = -0.08773159;
		*a_iter++ = 0.08773159;
		*a_iter++ = -0.07709608;
		*a_iter++ = 0.07709608;
		*a_iter++ = -0.07230518;
		*a_iter++ = 0.07230518;
		*a_iter++ = -0.09662156;
		*a_iter++ = 0.09662156;
		*a_iter++ = -0.07957632;
		*a_iter++ = 0.07957632;
		*a_iter++ = -0.07628441;
		*a_iter++ = 0.07628441;
		*a_iter++ = -0.08050202;
		*a_iter++ = 0.08050202;
		*a_iter++ = -0.1290593;
		*a_iter++ = 0.1290593;
		*a_iter++ = -0.09246182;
		*a_iter++ = 0.09246182;
		*a_iter++ = -0.09703662;
		*a_iter++ = 0.09703662;
		*a_iter++ = -0.07866445;
		*a_iter++ = 0.07866445;
		*a_iter++ = -0.1064783;
		*a_iter++ = 0.1064783;
		*a_iter++ = -0.1012339;
		*a_iter++ = 0.1012339;
		*a_iter++ = -0.06828389;
		*a_iter++ = 0.06828389;
		*a_iter++ = -0.1005039;
		*a_iter++ = 0.1005039;
		*a_iter++ = -0.07559687;
		*a_iter++ = 0.07559687;
		*a_iter++ = -0.06359878;
		*a_iter++ = 0.06359878;
		*a_iter++ = -0.08387002;
		*a_iter++ = 0.08387002;
		*a_iter++ = -0.07851323;
		*a_iter++ = 0.07851323;
		*a_iter++ = -0.08878569;
		*a_iter++ = 0.08878569;
		*a_iter++ = -0.07767654;
		*a_iter++ = 0.07767654;
		*a_iter++ = -0.08033338;
		*a_iter++ = 0.08033338;
		*a_iter++ = -0.09142797;
		*a_iter++ = 0.09142797;
		*a_iter++ = -0.08590585;
		*a_iter++ = 0.08590585;
		*a_iter++ = -0.1052318;
		*a_iter++ = 0.1052318;
		*a_iter++ = -0.08760062;
		*a_iter++ = 0.08760062;
		*a_iter++ = -0.09222192;
		*a_iter++ = 0.09222192;
		*a_iter++ = -0.07548828;
		*a_iter++ = 0.07548828;
		*a_iter++ = -0.08003344;
		*a_iter++ = 0.08003344;
		*a_iter++ = -0.1177076;
		*a_iter++ = 0.1177076;
		*a_iter++ = -0.1064964;
		*a_iter++ = 0.1064964;
		*a_iter++ = -0.08655553;
		*a_iter++ = 0.08655553;
		*a_iter++ = -0.09418112;
		*a_iter++ = 0.09418112;
		*a_iter++ = -0.07248163;
		*a_iter++ = 0.07248163;
		*a_iter++ = -0.07120974;
		*a_iter++ = 0.07120974;
		*a_iter++ = -0.06393114;
		*a_iter++ = 0.06393114;
		*a_iter++ = -0.07997487;
		*a_iter++ = 0.07997487;
		*a_iter++ = -0.1220941;
		*a_iter++ = 0.1220941;
		*a_iter++ = -0.09892518;
		*a_iter++ = 0.09892518;
		*a_iter++ = -0.08270271;
		*a_iter++ = 0.08270271;
		*a_iter++ = -0.10694;
		*a_iter++ = 0.10694;
		*a_iter++ = -0.05860771;
		*a_iter++ = 0.05860771;
		*a_iter++ = -0.091266;
		*a_iter++ = 0.091266;
		*a_iter++ = -0.06212559;
		*a_iter++ = 0.06212559;
		*a_iter++ = -0.09397538;
		*a_iter++ = 0.09397538;
		*a_iter++ = -0.08070447;
		*a_iter++ = 0.08070447;
		*a_iter++ = -0.08415587;
		*a_iter++ = 0.08415587;
		*a_iter++ = -0.08564455;
		*a_iter++ = 0.08564455;
		*a_iter++ = -0.07791811;
		*a_iter++ = 0.07791811;
		*a_iter++ = -0.06642259;
		*a_iter++ = 0.06642259;
		*a_iter++ = -0.08266167;
		*a_iter++ = 0.08266167;
		*a_iter++ = -0.1134986;
		*a_iter++ = 0.1134986;
		*a_iter++ = -0.1045267;
		*a_iter++ = 0.1045267;
		*a_iter++ = -0.07122085;
		*a_iter++ = 0.07122085;
		*a_iter++ = -0.07979415;
		*a_iter++ = 0.07979415;
		*a_iter++ = -0.07922347;
		*a_iter++ = 0.07922347;
		*a_iter++ = -0.09003421;
		*a_iter++ = 0.09003421;
		*a_iter++ = -0.08796449;
		*a_iter++ = 0.08796449;
		*a_iter++ = -0.07933279;
		*a_iter++ = 0.07933279;
		*a_iter++ = -0.08307947;
		*a_iter++ = 0.08307947;
		*a_iter++ = -0.08946349;
		*a_iter++ = 0.08946349;
		*a_iter++ = -0.07643384;
		*a_iter++ = 0.07643384;
		*a_iter++ = -0.07818534;
		*a_iter++ = 0.07818534;
		*a_iter++ = -0.07990991;
		*a_iter++ = 0.07990991;
		*a_iter++ = -0.09885664;
		*a_iter++ = 0.09885664;
		*a_iter++ = -0.08071329;
		*a_iter++ = 0.08071329;
		*a_iter++ = -0.06952112;
		*a_iter++ = 0.06952112;
		*a_iter++ = -0.06429706;
		*a_iter++ = 0.06429706;
		*a_iter++ = -0.06307229;
		*a_iter++ = 0.06307229;
		*a_iter++ = -0.08100137;
		*a_iter++ = 0.08100137;
		*a_iter++ = -0.07693623;
		*a_iter++ = 0.07693623;
		*a_iter++ = -0.06906625;
		*a_iter++ = 0.06906625;
		*a_iter++ = -0.07390462;
		*a_iter++ = 0.07390462;
		*a_iter++ = -0.06487217;
		*a_iter++ = 0.06487217;
		*a_iter++ = -0.1233681;
		*a_iter++ = 0.1233681;
		*a_iter++ = -0.06979273;
		*a_iter++ = 0.06979273;
		*a_iter++ = -0.08358669;
		*a_iter++ = 0.08358669;
		*a_iter++ = -0.109542;
		*a_iter++ = 0.109542;
		*a_iter++ = -0.08519717;
		*a_iter++ = 0.08519717;
		*a_iter++ = -0.07599857;
		*a_iter++ = 0.07599857;
		*a_iter++ = -0.06042816;
		*a_iter++ = 0.06042816;
		*a_iter++ = -0.06546304;
		*a_iter++ = 0.06546304;
		*a_iter++ = -0.1016245;
		*a_iter++ = 0.1016245;
		*a_iter++ = -0.08308787;
		*a_iter++ = 0.08308787;
		*a_iter++ = -0.07385708;
		*a_iter++ = 0.07385708;
		*a_iter++ = -0.0675163;
		*a_iter++ = 0.0675163;
		*a_iter++ = -0.09036695;
		*a_iter++ = 0.09036695;
		*a_iter++ = -0.09371335;
		*a_iter++ = 0.09371335;
		*a_iter++ = -0.1116088;
		*a_iter++ = 0.1116088;
		*a_iter++ = -0.05693741;
		*a_iter++ = 0.05693741;
		*a_iter++ = -0.06383983;
		*a_iter++ = 0.06383983;
		*a_iter++ = -0.05389843;
		*a_iter++ = 0.05389843;
		*a_iter++ = -0.08383191;
		*a_iter++ = 0.08383191;
		*a_iter++ = -0.07820822;
		*a_iter++ = 0.07820822;
		*a_iter++ = -0.07067557;
		*a_iter++ = 0.07067557;
		*a_iter++ = -0.07971948;
		*a_iter++ = 0.07971948;
		*a_iter++ = -0.07360668;
		*a_iter++ = 0.07360668;
		*a_iter++ = -0.07008027;
		*a_iter++ = 0.07008027;
		*a_iter++ = -0.08013378;
		*a_iter++ = 0.08013378;
		*a_iter++ = -0.08331605;
		*a_iter++ = 0.08331605;
		*a_iter++ = -0.07145702;
		*a_iter++ = 0.07145702;
		*a_iter++ = -0.0786394;
		*a_iter++ = 0.0786394;
		*a_iter++ = -0.06992679;
		*a_iter++ = 0.06992679;
		*a_iter++ = -0.05716495;
		*a_iter++ = 0.05716495;
		*a_iter++ = -0.05306006;
		*a_iter++ = 0.05306006;
		*a_iter++ = -0.08855639;
		*a_iter++ = 0.08855639;
		*a_iter++ = -0.07656397;
		*a_iter++ = 0.07656397;
		*a_iter++ = -0.06939272;
		*a_iter++ = 0.06939272;
		*a_iter++ = -0.07523742;
		*a_iter++ = 0.07523742;
		*a_iter++ = -0.08472299;
		*a_iter++ = 0.08472299;
		*a_iter++ = -0.08114341;
		*a_iter++ = 0.08114341;
		*a_iter++ = -0.06795517;
		*a_iter++ = 0.06795517;
		*a_iter++ = -0.0789013;
		*a_iter++ = 0.0789013;
		*a_iter++ = -0.07488741;
		*a_iter++ = 0.07488741;
		*a_iter++ = -0.09281972;
		*a_iter++ = 0.09281972;
		*a_iter++ = -0.09325498;
		*a_iter++ = 0.09325498;
		*a_iter++ = -0.1401587;
		*a_iter++ = 0.1401587;
		*a_iter++ = -0.1176284;
		*a_iter++ = 0.1176284;
		*a_iter++ = -0.08867597;
		*a_iter++ = 0.08867597;
		*a_iter++ = -0.08124232;
		*a_iter++ = 0.08124232;
		*a_iter++ = -0.09441235;
		*a_iter++ = 0.09441235;
		*a_iter++ = -0.08029452;
		*a_iter++ = 0.08029452;
		*a_iter++ = -0.08581848;
		*a_iter++ = 0.08581848;
		*a_iter++ = -0.1029819;
		*a_iter++ = 0.1029819;
		*a_iter++ = -0.09569118;
		*a_iter++ = 0.09569118;
		*a_iter++ = -0.07690893;
		*a_iter++ = 0.07690893;
		*a_iter++ = -0.09018228;
		*a_iter++ = 0.09018228;
		*a_iter++ = -0.1049209;
		*a_iter++ = 0.1049209;
		*a_iter++ = -0.08969413;
		*a_iter++ = 0.08969413;
		*a_iter++ = -0.08651891;
		*a_iter++ = 0.08651891;
		*a_iter++ = -0.08613331;
		*a_iter++ = 0.08613331;
		*a_iter++ = -0.07120468;
		*a_iter++ = 0.07120468;
		*a_iter++ = -0.08743959;
		*a_iter++ = 0.08743959;
		*a_iter++ = -0.07607158;
		*a_iter++ = 0.07607158;
		*a_iter++ = -0.1015547;
		*a_iter++ = 0.1015547;
		*a_iter++ = -0.08090879;
		*a_iter++ = 0.08090879;
		*a_iter++ = -0.07114079;
		*a_iter++ = 0.07114079;
		*a_iter++ = -0.08744835;
		*a_iter++ = 0.08744835;
		*a_iter++ = -0.06074904;
		*a_iter++ = 0.06074904;
		*a_iter++ = -0.06919871;
		*a_iter++ = 0.06919871;
		*a_iter++ = -0.07607774;
		*a_iter++ = 0.07607774;
		*a_iter++ = -0.094446;
		*a_iter++ = 0.094446;
		*a_iter++ = -0.07833429;
		*a_iter++ = 0.07833429;
		*a_iter++ = -0.06817555;
		*a_iter++ = 0.06817555;
		*a_iter++ = -0.0899739;
		*a_iter++ = 0.0899739;
		*a_iter++ = -0.09845223;
		*a_iter++ = 0.09845223;
		*a_iter++ = -0.0789418;
		*a_iter++ = 0.0789418;
		*a_iter++ = -0.07921373;
		*a_iter++ = 0.07921373;
		*a_iter++ = -0.07448032;
		*a_iter++ = 0.07448032;
		*a_iter++ = -0.1178165;
		*a_iter++ = 0.1178165;
		*a_iter++ = -0.08216686;
		*a_iter++ = 0.08216686;
		*a_iter++ = -0.08103286;
		*a_iter++ = 0.08103286;
		*a_iter++ = -0.0698147;
		*a_iter++ = 0.0698147;
		*a_iter++ = -0.08709008;
		*a_iter++ = 0.08709008;
		*a_iter++ = -0.08336259;
		*a_iter++ = 0.08336259;
		*a_iter++ = -0.06213589;
		*a_iter++ = 0.06213589;
		*a_iter++ = -0.07068045;
		*a_iter++ = 0.07068045;
		*a_iter++ = -0.06915676;
		*a_iter++ = 0.06915676;
		*a_iter++ = -0.07103416;
		*a_iter++ = 0.07103416;
		*a_iter++ = -0.06523849;
		*a_iter++ = 0.06523849;
		*a_iter++ = -0.0763476;
		*a_iter++ = 0.0763476;
		*a_iter++ = -0.07263038;
		*a_iter++ = 0.07263038;
		*a_iter++ = -0.07164396;
		*a_iter++ = 0.07164396;
		*a_iter++ = -0.08745559;
		*a_iter++ = 0.08745559;
		*a_iter++ = -0.06960181;
		*a_iter++ = 0.06960181;
		*a_iter++ = -0.08500098;
		*a_iter++ = 0.08500098;
		*a_iter++ = -0.0652326;
		*a_iter++ = 0.0652326;
		*a_iter++ = -0.07319714;
		*a_iter++ = 0.07319714;
		*a_iter++ = -0.06268125;
		*a_iter++ = 0.06268125;
		*a_iter++ = -0.07083135;
		*a_iter++ = 0.07083135;
		*a_iter++ = -0.07984517;
		*a_iter++ = 0.07984517;
		*a_iter++ = -0.1256265;
		*a_iter++ = 0.1256265;
		*a_iter++ = -0.1065412;
		*a_iter++ = 0.1065412;
		*a_iter++ = -0.08524323;
		*a_iter++ = 0.08524323;
		*a_iter++ = -0.09291364;
		*a_iter++ = 0.09291364;
		*a_iter++ = -0.07936567;
		*a_iter++ = 0.07936567;
		*a_iter++ = -0.08607723;
		*a_iter++ = 0.08607723;
		*a_iter++ = -0.07583416;
		*a_iter++ = 0.07583416;
		*a_iter++ = -0.07931928;
		*a_iter++ = 0.07931928;
		*a_iter++ = -0.07408357;
		*a_iter++ = 0.07408357;
		*a_iter++ = -0.1034404;
		*a_iter++ = 0.1034404;
		*a_iter++ = -0.1012127;
		*a_iter++ = 0.1012127;
		*a_iter++ = -0.07916689;
		*a_iter++ = 0.07916689;
		*a_iter++ = -0.08753651;
		*a_iter++ = 0.08753651;
		*a_iter++ = -0.06090366;
		*a_iter++ = 0.06090366;
		*a_iter++ = -0.07500103;
		*a_iter++ = 0.07500103;
		*a_iter++ = -0.1228709;
		*a_iter++ = 0.1228709;
		*a_iter++ = -0.06318201;
		*a_iter++ = 0.06318201;
		*a_iter++ = -0.0758542;
		*a_iter++ = 0.0758542;
		*a_iter++ = -0.0708909;
		*a_iter++ = 0.0708909;
		*a_iter++ = -0.1053542;
		*a_iter++ = 0.1053542;
		*a_iter++ = -0.08549521;
		*a_iter++ = 0.08549521;
		*a_iter++ = -0.07906308;
		*a_iter++ = 0.07906308;
		*a_iter++ = -0.0633878;
		*a_iter++ = 0.0633878;
		*a_iter++ = -0.0841791;
		*a_iter++ = 0.0841791;
		*a_iter++ = -0.07115511;
		*a_iter++ = 0.07115511;
		*a_iter++ = -0.07693949;
		*a_iter++ = 0.07693949;
		*a_iter++ = -0.07446749;
		*a_iter++ = 0.07446749;
		*a_iter++ = -0.1037929;
		*a_iter++ = 0.1037929;
		*a_iter++ = -0.07991005;
		*a_iter++ = 0.07991005;
		*a_iter++ = -0.07119439;
		*a_iter++ = 0.07119439;
		*a_iter++ = -0.0707134;
		*a_iter++ = 0.0707134;
		*a_iter++ = -0.08587362;
		*a_iter++ = 0.08587362;
		*a_iter++ = -0.07001236;
		*a_iter++ = 0.07001236;
		*a_iter++ = -0.07567115;
		*a_iter++ = 0.07567115;
		*a_iter++ = -0.0711893;
		*a_iter++ = 0.0711893;
		*a_iter++ = -0.06844895;
		*a_iter++ = 0.06844895;
		*a_iter++ = -0.1035118;
		*a_iter++ = 0.1035118;
		*a_iter++ = -0.08156618;
		*a_iter++ = 0.08156618;
		*a_iter++ = -0.07449593;
		*a_iter++ = 0.07449593;
		*a_iter++ = -0.0815436;
		*a_iter++ = 0.0815436;
		*a_iter++ = -0.09110878;
		*a_iter++ = 0.09110878;
		*a_iter++ = -0.06222534;
		*a_iter++ = 0.06222534;
		*a_iter++ = -0.1033841;
		*a_iter++ = 0.1033841;
		*a_iter++ = -0.06811687;
		*a_iter++ = 0.06811687;
		*a_iter++ = -0.06828443;
		*a_iter++ = 0.06828443;
		*a_iter++ = -0.05769408;
		*a_iter++ = 0.05769408;
		*a_iter++ = -0.05917684;
		*a_iter++ = 0.05917684;
		*a_iter++ = -0.08358868;
		*a_iter++ = 0.08358868;
	}
}

NAMESPACE_TOPSIDE_END

