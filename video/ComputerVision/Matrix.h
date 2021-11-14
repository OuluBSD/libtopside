#ifndef _ComputerVision_Matrix_h_
#define _ComputerVision_Matrix_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T>
void identity(matrix_t<T>& M, int value = 1) {
	auto& src = M.data;
	int rows = M.rows;
	int cols = M.cols;
	int cols_1 = (cols + 1);
	int len = rows * cols;
	int k = len;
	while (--len >= 0)
		src[len] = 0.0;
	len = k;
	k = 0;
	while (k < len)  {
		src[k] = value;
		k = k + cols_1;
	}
}

template <class T>
void transpose(matrix_t<T>& At, const matrix_t<T>& A) {
	int nrows = A.rows;
	int ncols = A.cols;
	int Ai = 0, Ati = 0, pAt = 0;
	const auto& ad = A.data
	auto& = At.data;
	
	for (int i = 0; i < nrows; Ati += 1, Ai += ncols, i++) {
		pAt = Ati;
		for (int j = 0; j < ncols; pAt += nrows, j++)
			atd[pAt] = ad[Ai+j];
	}
}

// C = A * B
template <class T>
void multiply(matrix_t<T>& C, const matrix_t<T>& A, const matrix_t<T>& B) {
	int Ap = 0;
	int Cp = 0;
	int ncols = A.cols;
	int nrows = A.rows;
	int mcols = B.cols;
	const auto& ad = A.data;
	const auto& bd = B.data;
	auto& cd = C.data;
	
	for (int i = 0; i < nrows; Ap += ncols, i++) {
		for (int p_B = 0, j = 0; j < mcols; Cp++, p_B++, j++) {
			int pB = p_B;
			int pA = Ap;
			double sum = 0.0;
			for (int k = 0; k < ncols; pA++, pB += mcols, k++) {
				sum += ad[pA] * bd[pB];
			}
			cd[Cp] = sum;
		}
	}
}

// C = A * B'
template <class T>
void multiply_ABt(matrix_t<T>& C, const matrix_t<T>& A, const matrix_t<T>& B) {
	int Ap = 0, Cp = 0;
	int ncols = A.cols, nrows = A.rows, mrows = B.rows;
	const auto& ad = A.data;
	const auto&bd = B.data;
	auto& cd = C.data;
	
	for (int i = 0; i < nrows; Ap += ncols, i++) {
		for (int pB = 0, j = 0; j < mrows; Cp++, j++) {
			int pA = Ap;
			double sum = 0.0;
			for (int k = 0; k < ncols; pA++, pB++, k++) {
				sum += ad[pA] * bd[pB];
			}
			cd[Cp] = sum;
		}
	}
}

// C = A' * B
template <class T>
void multiply_AtB(matrix_t<T>& C, const matrix_t<T>& A, const matrix_t<T>& B) {
	int Ap = 0;
	int Cp = 0;
	int ncols = A.cols, nrows = A.rows, mcols = B.cols;
	const auto& ad = A.data;
	const auto& bd = B.data;
	auto& cd = C.data;
	
	for (int i = 0; i < ncols; Ap++, i++) {
		for (int p_B = 0, j = 0; j < mcols; Cp++, p_B++, j++) {
			int pB = p_B;
			int pA = Ap;
			double sum = 0.0;
			for (int k = 0; k < nrows; pA += ncols, pB += mcols, k++) {
				sum += ad[pA] * bd[pB];
			}
			cd[Cp] = sum;
		}
	}
}

// C = A * A'
template <class T>
void multiply_AAt(matrix_t<T>& C, const matrix_t<T>& A) {
	int pCdiag = 0, p_A = 0, pA = 0;
	int ncols = A.cols, nrows = A.rows;
	const auto& ad = A.data;
	auto& cd = C.data;
	double sum = 0.0;
	
	for (int i = 0; i < nrows; pCdiag += nrows + 1, p_A = pA, i++) {
		int pC = pCdiag;
		int pCt = pCdiag;
		int pB = p_A;
		for (int j = i; j < nrows; pC++, pCt += nrows, j++) {
			pA = p_A;
			sum = 0.0;
			for (int k = 0; k < ncols; k++) {
				sum += ad[pA++] * ad[pB++];
			}
			cd[pC] = sum
					 cd[pCt] = sum;
		}
	}
}

// C = A' * A
template <class T>
void multiply_AtA(matrix_t<T>& C, const matrix_t<T>& A) {
	//var i = 0, j = 0, k = 0;
	//var p_A = 0, pA = 0, pB = 0, p_C = 0, pC = 0, p_CC = 0;
	int ncols = A.cols, nrows = A.rows;
	const auto& ad = A.data;
	auto& cd = C.data;
	double sum = 0.0;
	
	for (int i = 0, p_C = 0; i < ncols; p_C += ncols, i++) {
		int p_A = i;
		int p_CC = p_C + i;
		int pC = p_CC;
		for (int j = i; j < ncols; pC++, p_CC += ncols, j++) {
			int pA = p_A;
			int pB = j;
			doublesum = 0.0;
			for (int k = 0; k < nrows; pA += ncols, pB += ncols, k++) {
				sum += ad[pA] * ad[pB];
			}
			cd[pC] = sum;
			cd[p_CC] = sum;
		}
	}
}

// various small matrix operations
template <class T>
void identity_3x3(matrix_t<T>& M, int value = 1) {
	auto& dt = M.data;
	dt[0] = value;
	dt[4] = value;
	dt[8] = value;
	dt[1] = 0;
	dt[2] = 0;
	dt[3] = 0;
	dt[5] = 0;
	dt[6] = 0;
	dt[7] = 0;
}

template <class T>
void invert_3x3(const matrix_t<T>&from, matrix_t<T>& to) {
	double A = from.data, invA = to.data;
	double t1 = A[4];
	double t2 = A[8];
	double t4 = A[5];
	double t5 = A[7];
	double t8 = A[0];
	
	double t9 = t8 * t1;
	double t11 = t8 * t4;
	double t13 = A[3];
	double t14 = A[1];
	double t15 = t13 * t14;
	double t17 = A[2];
	double t18 = t13 * t17;
	double t20 = A[6];
	double t21 = t20 * t14;
	double t23 = t20 * t17;
	double t26 = 1.0 / (t9 * t2 - t11 * t5 - t15 * t2 + t18 * t5 + t21 * t4 - t23 * t1);
	invA[0] = (t1 * t2 - t4 * t5) * t26;
	invA[1] = -(t14 * t2 - t17 * t5) * t26;
	invA[2] = -(-t14 * t4 + t17 * t1) * t26;
	invA[3] = -(t13 * t2 - t4 * t20) * t26;
	invA[4] = (t8 * t2 - t23) * t26;
	invA[5] = -(t11 - t18) * t26;
	invA[6] = -(-t13 * t5 + t1 * t20) * t26;
	invA[7] = -(t8 * t5 - t21) * t26;
	invA[8] = (t9 - t15) * t26;
}

// C = A * B
template <class T>
void multiply_3x3(matrix_t<T>& C, const matrix_t<T>& A, const matrix_t<T>& B) {
	double Cd = C.data, Ad = A.data, Bd = B.data;
	double m1_0 = Ad[0], m1_1 = Ad[1], m1_2 = Ad[2];
	double m1_3 = Ad[3], m1_4 = Ad[4], m1_5 = Ad[5];
	double m1_6 = Ad[6], m1_7 = Ad[7], m1_8 = Ad[8];
	
	double m2_0 = Bd[0], m2_1 = Bd[1], m2_2 = Bd[2];
	double m2_3 = Bd[3], m2_4 = Bd[4], m2_5 = Bd[5];
	double m2_6 = Bd[6], m2_7 = Bd[7], m2_8 = Bd[8];
	
	Cd[0] = m1_0 * m2_0 + m1_1 * m2_3 + m1_2 * m2_6;
	Cd[1] = m1_0 * m2_1 + m1_1 * m2_4 + m1_2 * m2_7;
	Cd[2] = m1_0 * m2_2 + m1_1 * m2_5 + m1_2 * m2_8;
	Cd[3] = m1_3 * m2_0 + m1_4 * m2_3 + m1_5 * m2_6;
	Cd[4] = m1_3 * m2_1 + m1_4 * m2_4 + m1_5 * m2_7;
	Cd[5] = m1_3 * m2_2 + m1_4 * m2_5 + m1_5 * m2_8;
	Cd[6] = m1_6 * m2_0 + m1_7 * m2_3 + m1_8 * m2_6;
	Cd[7] = m1_6 * m2_1 + m1_7 * m2_4 + m1_8 * m2_7;
	Cd[8] = m1_6 * m2_2 + m1_7 * m2_5 + m1_8 * m2_8;
}

template <class T>
double mat3x3_determinant(const matrix_t<T>& M) {
	const auto& md = M.data;
	return  md[0] * md[4] * md[8] -
			md[0] * md[5] * md[7] -
			md[3] * md[1] * md[8] +
			md[3] * md[2] * md[7] +
			md[6] * md[1] * md[5] -
			md[6] * md[2] * md[4];
}

template <class T>
double determinant_3x3(	const matrix_t<T>& M11, const matrix_t<T>& M12, const matrix_t<T>& M13,
						const matrix_t<T>& M21, const matrix_t<T>& M22, const matrix_t<T>& M23,
						const matrix_t<T>& M31, const matrix_t<T>& M32, const matrix_t<T>& M33) {
	return  M11 * M22 * M33 - M11 * M23 * M32 -
			M21 * M12 * M33 + M21 * M13 * M32 +
			M31 * M12 * M23 - M31 * M13 * M22;
}

NAMESPACE_TOPSIDE_END

#endif
