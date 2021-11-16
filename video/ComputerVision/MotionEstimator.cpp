#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


bool have_collinear_points(Vector<keypoint_t>& points, int count) {
	int i = (count - 1);
	double dx1 = 0.0, dy1 = 0.0, dx2 = 0.0, dy2 = 0.0;
	
	// check that the i-th selected point does not belong
	// to a line connecting some previously selected points
	for (int j = 0; j < i; ++j) {
		dx1 = points[j].x - points[i].x;
		dy1 = points[j].y - points[i].y;
		for (int k = 0; k < j; ++k) {
			dx2 = points[k].x - points[i].x;
			dy2 = points[k].y - points[i].y;
			if (abs(dx2*dy1 - dy2*dx1) <= EPSILON*(abs(dx1) + abs(dy1) + abs(dx2) + abs(dy2)))
				return true;
		}
	}
	return false;
}




void homography2d::error(const Vector<keypoint_t>& from, const Vector<keypoint_t>& to, const FloatMat& model, Vector<double>& err) {
	const auto& m = model.data;
	
	auto f = from.Begin();
	auto t = to.Begin();
	for (auto& e : err) {
		const keypoint_t& pt0 = *f;
		const keypoint_t& pt1 = *t;
		
		double ww = 1.0 / (m[6] * pt0.x + m[7] * pt0.y + 1.0);
		double dx = (m[0] * pt0.x + m[1] * pt0.y + m[2]) * ww - pt1.x;
		double dy = (m[3] * pt0.x + m[4] * pt0.y + m[5]) * ww - pt1.y;
		e = (dx * dx + dy * dy);
		
		f++;
		t++;
	}
}

bool homography2d::check_subset(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, int count) {
	// seems to reject good subsets actually
	//if( have_collinear_points(from, count) || have_collinear_points(to, count) ) {
	//return false;
	//}
	if (count == 4) {
		int negative = 0;
		
		keypoint_t fp0 = from[0], fp1 = from[1], fp2 = from[2], fp3 = from[3];
		keypoint_t tp0 = to[0], tp1 = to[1], tp2 = to[2], tp3 = to[3];
		
		// set1
		double A11 = fp0.x, A12 = fp0.y, A13 = 1.0;
		double A21 = fp1.x, A22 = fp1.y, A23 = 1.0;
		double A31 = fp2.x, A32 = fp2.y, A33 = 1.0;
		
		double B11 = tp0.x, B12 = tp0.y, B13 = 1.0;
		double B21 = tp1.x, B22 = tp1.y, B23 = 1.0;
		double B31 = tp2.x, B32 = tp2.y, B33 = 1.0;
		
		double detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
		double detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
		
		if (detA*detB < 0)
			negative++;
		
		// set2
		A11 = fp1.x, A12 = fp1.y;
		A21 = fp2.x, A22 = fp2.y;
		A31 = fp3.x, A32 = fp3.y;
		
		B11 = tp1.x, B12 = tp1.y;
		B21 = tp2.x, B22 = tp2.y;
		B31 = tp3.x, B32 = tp3.y;
		
		detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
		detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
		
		if (detA*detB < 0)
			negative++;
			
		// set3
		A11 = fp0.x, A12 = fp0.y;
		A21 = fp2.x, A22 = fp2.y;
		A31 = fp3.x, A32 = fp3.y;
		
		B11 = tp0.x, B12 = tp0.y;
		B21 = tp2.x, B22 = tp2.y;
		B31 = tp3.x, B32 = tp3.y;
		
		detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
		detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
		
		if (detA*detB < 0)
			negative++;
			
		// set4
		A11 = fp0.x, A12 = fp0.y;
		A21 = fp1.x, A22 = fp1.y;
		A31 = fp3.x, A32 = fp3.y;
		
		B11 = tp0.x, B12 = tp0.y;
		B21 = tp1.x, B22 = tp1.y;
		B31 = tp3.x, B32 = tp3.y;
		
		detA = determinant_3x3(A11, A12, A13, A21, A22, A23, A31, A32, A33);
		detB = determinant_3x3(B11, B12, B13, B21, B22, B23, B31, B32, B33);
		
		if (detA*detB < 0)
			negative++;
			
		if (negative != 0 && negative != 4) {
			return false;
		}
	}
	return true; // all good
}

bool homography2d::run(const Vector<keypoint_t>& from, Vector<keypoint_t>& to, FloatMat& model) {
	auto& md = model.data;
	auto& t0d = T0.data;
	auto& t1d = T1.data;
	auto& LtL = mLtL.data;
	
	int count = from.GetCount();
	
	double x = 0.0, y = 0.0, X = 0.0, Y = 0.0;
	
	// norm
	double smx = 0.0, smy = 0.0, cmx = 0.0, cmy = 0.0, sMx = 0.0, sMy = 0.0, cMx = 0.0, cMy = 0.0;
	
	for (int i = 0; i < count; ++i) {
		cmx += to[i].x;
		cmy += to[i].y;
		cMx += from[i].x;
		cMy += from[i].y;
	}
	
	cmx /= count;
	cmy /= count;
	cMx /= count;
	cMy /= count;
	
	for (int i = 0; i < count; ++i) {
		smx += abs(to[i].x - cmx);
		smy += abs(to[i].y - cmy);
		sMx += abs(from[i].x - cMx);
		sMy += abs(from[i].y - cMy);
	}
	
	if (   abs(smx) < EPSILON
		|| abs(smy) < EPSILON
		|| abs(sMx) < EPSILON
		|| abs(sMy) < EPSILON)
		return 0;
		
	smx = count / smx;
	smy = count / smy;
	sMx = count / sMx;
	sMy = count / sMy;
	
	t0d[0] = sMx;
	t0d[1] = 0;
	t0d[2] = -cMx * sMx;
	t0d[3] = 0;
	t0d[4] = sMy;
	t0d[5] = -cMy * sMy;
	t0d[6] = 0;
	t0d[7] = 0;
	t0d[8] = 1;
	
	t1d[0] = 1.0 / smx;
	t1d[1] = 0;
	t1d[2] = cmx;
	t1d[3] = 0;
	t1d[4] = 1.0 / smy;
	t1d[5] = cmy;
	t1d[6] = 0;
	t1d[7] = 0;
	t1d[8] = 1;
	//
	
	// construct system
	{
		int i = 81;
		while (--i >= 0) {
			LtL[i] = 0.0;
		}
	}
	for (int i = 0; i < count; ++i) {
		x = (to[i].x - cmx) * smx;
		y = (to[i].y - cmy) * smy;
		X = (from[i].x - cMx) * sMx;
		Y = (from[i].y - cMy) * sMy;
		
		LtL[0] += X * X;
		LtL[1] += X * Y;
		LtL[2] += X;
		
		LtL[6] += X * -x * X;
		LtL[7] += X * -x * Y;
		LtL[8] += X * -x;
		LtL[10] += Y * Y;
		LtL[11] += Y;
		
		LtL[15] += Y * -x * X;
		LtL[16] += Y * -x * Y;
		LtL[17] += Y * -x;
		LtL[20] += 1.0;
		
		LtL[24] += -x * X;
		LtL[25] += -x * Y;
		LtL[26] += -x;
		LtL[30] += X * X;
		LtL[31] += X * Y;
		LtL[32] += X;
		LtL[33] += X * -y * X;
		LtL[34] += X * -y * Y;
		LtL[35] += X * -y;
		LtL[40] += Y * Y;
		LtL[41] += Y;
		LtL[42] += Y * -y * X;
		LtL[43] += Y * -y * Y;
		LtL[44] += Y * -y;
		LtL[50] += 1.0;
		LtL[51] += -y * X;
		LtL[52] += -y * Y;
		LtL[53] += -y;
		LtL[60] += -x * X * -x * X + -y * X * -y * X;
		LtL[61] += -x * X * -x * Y + -y * X * -y * Y;
		LtL[62] += -x * X * -x + -y * X * -y;
		LtL[70] += -x * Y * -x * Y + -y * Y * -y * Y;
		LtL[71] += -x * Y * -x + -y * Y * -y;
		LtL[80] += -x * -x + -y * -y;
	}
	//
	
	// symmetry
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < i; ++j)
			LtL[i*9+j] = LtL[j*9+i];
	}
	
	eigenVV(mLtL, &Evec);
	
	const auto& evd = Evec.data;
	md[0] = evd[72], md[1] = evd[73], md[2] = evd[74];
	md[3] = evd[75], md[4] = evd[76], md[5] = evd[77];
	md[6] = evd[78], md[7] = evd[79], md[8] = evd[80];
	
	// denormalize
	multiply_3x3(model, T1, model);
	multiply_3x3(model, model, T0);
	
	// set bottom right to 1.0
	x = 1.0 / md[8];
	md[0] *= x;
	md[1] *= x;
	md[2] *= x;
	md[3] *= x;
	md[4] *= x;
	md[5] *= x;
	md[6] *= x;
	md[7] *= x;
	md[8] = 1.0;
	
	return true;
}


NAMESPACE_TOPSIDE_END
