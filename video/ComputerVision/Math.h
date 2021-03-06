#ifndef _ComputerVision_Math_h_
#define _ComputerVision_Math_h_


NAMESPACE_TOPSIDE_BEGIN

template <class T>
void GetGaussianKernel(int size, double sigma, Vector<T>& kernel) {
	double sum = 0.0;
	static thread_local Vector<double> _kernel;
	_kernel.SetCount(size);
	
	if ((size&1) == 1 && size <= 7 && sigma <= 0) {
		switch (size >> 1) {
		case 0:
			_kernel[0] = 1.0;
			sum = 1.0;
			break;
		case 1:
			_kernel[0] = 0.25, _kernel[1] = 0.5, _kernel[2] = 0.25;
			sum = 0.25 + 0.5 + 0.25;
			break;
		case 2:
			_kernel[0] = 0.0625, _kernel[1] = 0.25, _kernel[2] = 0.375,
						 _kernel[3] = 0.25, _kernel[4] = 0.0625;
			sum = 0.0625 + 0.25 + 0.375 + 0.25 + 0.0625;
			break;
		case 3:
			_kernel[0] = 0.03125, _kernel[1] = 0.109375, _kernel[2] = 0.21875,
						 _kernel[3] = 0.28125, _kernel[4] = 0.21875, _kernel[5] = 0.109375, _kernel[6] = 0.03125;
			sum = 0.03125 + 0.109375 + 0.21875 + 0.28125 + 0.21875 + 0.109375 + 0.03125;
			break;
		}
	}
	else {
		double sigma_x = sigma > 0 ? sigma : ((size - 1) * 0.5 - 1.0) * 0.3 + 0.8;
		double scale_2x = -0.5 / (sigma_x * sigma_x);
		
		for (int i = 0; i < size; ++i) {
			double x = i - (size - 1) * 0.5;
			double t = exp_fast(scale_2x * x * x);
			
			_kernel[i] = t;
			sum += t;
		}
	}
	
	if (std::is_same<byte, T>::value) {
		// int based kernel
		sum = 256.0 / sum;
		for (int i = 0; i < size; ++i) {
			kernel[i] = (T)(_kernel[i] * sum + 0.5);
		}
	}
	else {
		// classic kernel
		sum = 1.0 / sum;
		for (int i = 0; i < size; ++i) {
			kernel[i] = kernel[i] = (T)(_kernel[i] * sum);
		}
	}
	
}


// model is 3x3 DMatrix
template <class T>
void Perspective4PointTransform(
	DMatrix<T>& model,
	double src_x0, double src_y0, double dst_x0, double dst_y0,
	double src_x1, double src_y1, double dst_x1, double dst_y1,
	double src_x2, double src_y2, double dst_x2, double dst_y2,
	double src_x3, double src_y3, double dst_x3, double dst_y3) {
	double t1 = src_x0;
	double t2 = src_x2;
	double t4 = src_y1;
	double t5 = t1 * t2 * t4;
	double t6 = src_y3;
	double t7 = t1 * t6;
	double t8 = t2 * t7;
	double t9 = src_y2;
	double t10 = t1 * t9;
	double t11 = src_x1;
	double t14 = src_y0;
	double t15 = src_x3;
	double t16 = t14 * t15;
	double t18 = t16 * t11;
	double t20 = t15 * t11 * t9;
	double t21 = t15 * t4;
	double t24 = t15 * t9;
	double t25 = t2 * t4;
	double t26 = t6 * t2;
	double t27 = t6 * t11;
	double t28 = t9 * t11;
	double t30 = 1.0 / (t21 - t24 - t25 + t26 - t27 + t28);
	double t32 = t1 * t15;
	double t35 = t14 * t11;
	double t41 = t4 * t1;
	double t42 = t6 * t41;
	double t43 = t14 * t2;
	double t46 = t16 * t9;
	double t48 = t14 * t9 * t11;
	double t51 = t4 * t6 * t2;
	double t55 = t6 * t14;
	double Hr0 = -(t8 - t5 + t10 * t11 - t11 * t7 - t16 * t2 + t18 - t20 + t21 * t2) * t30;
	double Hr1 = (t5 - t8 - t32 * t4 + t32 * t9 + t18 - t2 * t35 + t27 * t2 - t20) * t30;
	double Hr2 = t1;
	double Hr3 = (-t9 * t7 + t42 + t43 * t4 - t16 * t4 + t46 - t48 + t27 * t9 - t51) * t30;
	double Hr4 = (-t42 + t41 * t9 - t55 * t2 + t46 - t48 + t55 * t11 + t51 - t21 * t9) * t30;
	double Hr5 = t14;
	double Hr6 = (-t10 + t41 + t43 - t35 + t24 - t21 - t26 + t27) * t30;
	double Hr7 = (-t7 + t10 + t16 - t43 + t27 - t28 - t21 + t25) * t30;
	
	t1 = dst_x0;
	t2 = dst_x2;
	t4 = dst_y1;
	t5 = t1 * t2 * t4;
	t6 = dst_y3;
	t7 = t1 * t6;
	t8 = t2 * t7;
	t9 = dst_y2;
	t10 = t1 * t9;
	t11 = dst_x1;
	t14 = dst_y0;
	t15 = dst_x3;
	t16 = t14 * t15;
	t18 = t16 * t11;
	t20 = t15 * t11 * t9;
	t21 = t15 * t4;
	t24 = t15 * t9;
	t25 = t2 * t4;
	t26 = t6 * t2;
	t27 = t6 * t11;
	t28 = t9 * t11;
	t30 = 1.0 / (t21 - t24 - t25 + t26 - t27 + t28);
	t32 = t1 * t15;
	t35 = t14 * t11;
	t41 = t4 * t1;
	t42 = t6 * t41;
	t43 = t14 * t2;
	t46 = t16 * t9;
	t48 = t14 * t9 * t11;
	t51 = t4 * t6 * t2;
	t55 = t6 * t14;
	double Hl0 = -(t8 - t5 + t10 * t11 - t11 * t7 - t16 * t2 + t18 - t20 + t21 * t2) * t30;
	double Hl1 = (t5 - t8 - t32 * t4 + t32 * t9 + t18 - t2 * t35 + t27 * t2 - t20) * t30;
	double Hl2 = t1;
	double Hl3 = (-t9 * t7 + t42 + t43 * t4 - t16 * t4 + t46 - t48 + t27 * t9 - t51) * t30;
	double Hl4 = (-t42 + t41 * t9 - t55 * t2 + t46 - t48 + t55 * t11 + t51 - t21 * t9) * t30;
	double Hl5 = t14;
	double Hl6 = (-t10 + t41 + t43 - t35 + t24 - t21 - t26 + t27) * t30;
	double Hl7 = (-t7 + t10 + t16 - t43 + t27 - t28 - t21 + t25) * t30;
	
	// the following code computes R = Hl * inverse Hr
	t2 = Hr4 - Hr7 * Hr5;
	t4 = Hr0 * Hr4;
	t5 = Hr0 * Hr5;
	t7 = Hr3 * Hr1;
	t8 = Hr2 * Hr3;
	t10 = Hr1 * Hr6;
	double t12 = Hr2 * Hr6;
	double div = t4 - t5 * Hr7 - t7 + t8 * Hr7 + t10 * Hr5 - t12 * Hr4;
	ASSERT(div != 0.0);
	t15 = 1.0 / div;
	t18 = -Hr3 + Hr5 * Hr6;
	double t23 = -Hr3 * Hr7 + Hr4 * Hr6;
	t28 = -Hr1 + Hr2 * Hr7;
	double t31 = Hr0 - t12;
	t35 = Hr0 * Hr7 - t10;
	t41 = -Hr1 * Hr5 + Hr2 * Hr4;
	double t44 = t5 - t8;
	double t47 = t4 - t7;
	t48 = t2 * t15;
	double t49 = t28 * t15;
	double t50 = t41 * t15;
	
	model.SetSize(3,3,1);
	auto& mat = model.data;
	mat[0] = Hl0 * t48 + Hl1 * (t18 * t15) - Hl2 * (t23 * t15);
	mat[1] = Hl0 * t49 + Hl1 * (t31 * t15) - Hl2 * (t35 * t15);
	mat[2] = -Hl0 * t50 - Hl1 * (t44 * t15) + Hl2 * (t47 * t15);
	mat[3] = Hl3 * t48 + Hl4 * (t18 * t15) - Hl5 * (t23 * t15);
	mat[4] = Hl3 * t49 + Hl4 * (t31 * t15) - Hl5 * (t35 * t15);
	mat[5] = -Hl3 * t50 - Hl4 * (t44 * t15) + Hl5 * (t47 * t15);
	mat[6] = Hl6 * t48 + Hl7 * (t18 * t15) - t23 * t15;
	mat[7] = Hl6 * t49 + Hl7 * (t31 * t15) - t35 * t15;
	mat[8] = -Hl6 * t50 - Hl7 * (t44 * t15) + t47 * t15;
}

template <class T>
T Median(Vector<T>& array, int low, int high) {
	T w;
	T middle = 0, ll = 0, hh = 0, median = (low + high) >> 1;
	for (;;) {
		if (high <= low)
			return array[median];
		if (high == (low + 1)) {
			if (array[low] > array[high]) {
				w = array[low];
				array[low] = array[high];
				array[high] = w;
			}
			return array[median];
		}
		middle = ((low + high) >> 1);
		if (array[middle] > array[high]) {
			w = array[middle];
			array[middle] = array[high];
			array[high] = w;
		}
		if (array[low] > array[high]) {
			w = array[low];
			array[low] = array[high];
			array[high] = w;
		}
		if (array[middle] > array[low]) {
			w = array[middle];
			array[middle] = array[low];
			array[low] = w;
		}
		ll = (low + 1);
		w = array[middle];
		array[middle] = array[ll];
		array[ll] = w;
		hh = high;
		for (;;) {
			do
				++ll;
			while (array[low] > array[ll]);
			do
				--hh;
			while (array[hh] > array[low]);
			if (hh < ll)
				break;
			w = array[ll];
			array[ll] = array[hh];
			array[hh] = w;
		}
		w = array[low];
		array[low] = array[hh];
		array[hh] = w;
		if (hh <= median)
			low = ll;
		else
			if (hh >= median)
				high = (hh - 1);
	}
	return 0;
}


NAMESPACE_TOPSIDE_END

#endif
