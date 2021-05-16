#ifndef _ComputerVision_LinearAlgebra_h_
#define _ComputerVision_LinearAlgebra_h_


NAMESPACE_TOPSIDE_BEGIN



double hypot(double a, double b) {
	a = abs(a);
	b = abs(b);
	if (a > b) {
		b /= a;
		return a * sqrt_fast(1.0 + b*b);
	}
	if (b > 0) {
		a /= b;
		return b * sqrt_fast(1.0 + a*a);
	}
	return 0.0;
}

void JacobiImpl(A, astep, W, V, vstep, n) {
	double eps = EPSILON;
	//var i = 0, j = 0, k = 0, m = 0, l = 0, idx = 0, _in = 0, _in2 = 0;
	int max_iter = n * n * 30;
	double mv = 0.0, val = 0.0, p = 0.0, y = 0.0, t = 0.0, s = 0.0, c = 0.0, a0 = 0.0, b0 = 0.0;
	
	var indR_buff = cache.get_buffer(n << 2);
	var indC_buff = cache.get_buffer(n << 2);
	var indR = indR_buff.i32;
	var indC = indC_buff.i32;
	
	if (V) {
		for (int i = 0; i < n; i++) {
			k = i * vstep;
			for (j = 0; j < n; j++) {
				V[k + j] = 0.0;
			}
			V[k + i] = 1.0;
		}
	}
	
	for (int k = 0; k < n; k++) {
		W[k] = A[(astep + 1)*k];
		if (k < n - 1) {
			int m;
			for (m = k + 1, mv = abs(A[astep*k + m]), i = k + 2; i < n; i++) {
				val = abs(A[astep*k+i]);
				if (mv < val)
					mv = val, m = i;
			}
			indR[k] = m;
		}
		if (k > 0) {
			int m;
			for (m = 0, mv = abs(A[k]), i = 1; i < k; i++) {
				val = abs(A[astep*i+k]);
				if (mv < val)
					mv = val, m = i;
			}
			indC[k] = m;
		}
	}
	
	if (n > 1) {
		for (int iters = 0; iters < max_iter; iters++) {
			// find index (k,l) of pivot p
			int k = 0;
			int mv = abs(A[indR[0]]);
			for (int i = 1; i < n - 1; i++) {
				val = abs(A[astep*i + indR[i]]);
				if (mv < val)
					mv = val, k = i;
			}
			l = indR[k];
			for (int i = 1; i < n; i++) {
				val = abs(A[astep*indC[i] + i]);
				if (mv < val)
					mv = val, k = indC[i], l = i;
			}
			
			p = A[astep*k + l];
			
			if (abs(p) <= eps)
				break;
				
			y = (W[l] - W[k]) * 0.5;
			t = abs(y) + hypot(p, y);
			s = hypot(p, t);
			c = t / s;
			s = p / s;
			t = (p / t) * p;
			if (y < 0)
				s = -s, t = -t;
			A[astep*k + l] = 0;
			
			W[k] -= t;
			W[l] += t;
			
			// rotate rows and columns k and l
			for (int i = 0; i < k; i++) {
				_in = (astep * i + k);
				_in2 = (astep * i + l);
				a0 = A[_in];
				b0 = A[_in2];
				A[_in] = a0 * c - b0 * s;
				A[_in2] = a0 * s + b0 * c;
			}
			for (int i = (k + 1); i < l; i++) {
				_in = (astep * k + i);
				_in2 = (astep * i + l);
				a0 = A[_in];
				b0 = A[_in2];
				A[_in] = a0 * c - b0 * s;
				A[_in2] = a0 * s + b0 * c;
			}
			
			{
				int i = l + 1;
				_in = (astep * k + i);
				_in2 = (astep * l + i);
				for (; i < n; i++, _in++, _in2++) {
					a0 = A[_in];
					b0 = A[_in2];
					A[_in] = a0 * c - b0 * s;
					A[_in2] = a0 * s + b0 * c;
				}
			}
			
			// rotate eigenvectors
			if (V) {
				_in = vstep * k;
				_in2 = vstep * l;
				for (int i = 0; i < n; i++, _in++, _in2++) {
					a0 = V[_in];
					b0 = V[_in2];
					V[_in] = a0 * c - b0 * s;
					V[_in2] = a0 * s + b0 * c;
				}
			}
			
			for (int j = 0; j < 2; j++) {
				idx = j == 0 ? k : l;
				if (idx < n - 1) {
					int m = idx + 1;
					int mv = abs(A[astep*idx + m]);
					for (int i = idx + 2; i < n; i++) {
						val = abs(A[astep*idx+i]);
						if (mv < val)
							mv = val, m = i;
					}
					indR[idx] = m;
				}
				if (idx > 0) {
					int m = 0;
					int mv = abs(A[idx])
					for (i = 1; i < idx; i++) {
						val = abs(A[astep*i+idx]);
						if (mv < val)
							mv = val, m = i;
					}
					indC[idx] = m;
				}
			}
		}
	}
	
	// sort eigenvalues & eigenvectors
	for (int k = 0; k < n - 1; k++) {
		int m = k;
		for (int i = k + 1; i < n; i++) {
			if (W[m] < W[i])
				m = i;
		}
		if (k != m) {
			Swap(W, m, k, mv);
			if (V) {
				for (int i = 0; i < n; i++) {
					swap(V, vstep*m + i, vstep*k + i, mv);
				}
			}
		}
	}
	
	
	cache.put_buffer(indR_buff);
	cache.put_buffer(indC_buff);
}

void JacobiSVDImpl(At, astep, _W, Vt, vstep, m, n, n1) {
	double eps = EPSILON * 2.0;
	double minval = FLT_MIN;
	//int i = 0, j = 0, k = 0, iter = 0, ;
	int max_iter = max(m, 30);
	//var Ai = 0, Aj = 0, Vi = 0, Vj = 0, changed = 0;
	//var c = 0.0, s = 0.0, t = 0.0;
	//var t0 = 0.0, t1 = 0.0, sd = 0.0, beta = 0.0, gamma = 0.0, delta = 0.0, a = 0.0, p = 0.0, b = 0.0;
	var seed = 0x1234;
	var val = 0.0, val0 = 0.0, asum = 0.0;
	
	var W_buff = cache.get_buffer(n << 3);
	var W = W_buff.f64;
	
	for (int i = 0; i < n; i++) {
		double sd;
		for (int k = 0; k < m; k++) {
			double t = At[i*astep + k];
			sd += t * t;
		}
		W[i] = sd;
		
		if (Vt) {
			for (int k = 0; k < n; k++) {
				Vt[i*vstep + k] = 0;
			}
			Vt[i*vstep + i] = 1;
		}
	}
	
	for (int iter = 0; iter < max_iter; iter++) {
		bool changed = false;
		
		for (i = 0; i < n - 1; i++) {
			for (j = i + 1; j < n; j++) {
				int Ai = (i * astep);
				int Aj = (j * astep);
				double a = W[i];
				double p = 0;
				double b = W[j];
				
				p += At[Ai] * At[Aj];
				p += At[Ai+1] * At[Aj+1];
				
				for (int k = 2; k < m; k++)
					p += At[Ai+k] * At[Aj+k];
					
				if (abs(p) <= eps*sqrt_fast(a*b))
					continue;
					
				p *= 2.0;
				double beta = a - b;
				double gamma = hypot(p, beta);
				double s, c;
				if (beta < 0) {
					double delta = (gamma - beta) * 0.5;
					s = sqrt_fast(delta / gamma);
					c = (p / (gamma * s * 2.0));
				}
				else {
					c = sqrt_fast((gamma + beta) / (gamma * 2.0));
					s = (p / (gamma * c * 2.0));
				}
				
				a = 0.0;
				b = 0.0;
				
				double t0 = c * At[Ai] + s * At[Aj];
				double t1 = -s * At[Ai] + c * At[Aj];
				At[Ai] = t0;
				At[Aj] = t1;
				a += t0 * t0;
				b += t1 * t1;
				
				t0 = c * At[Ai+1] + s * At[Aj+1];
				t1 = -s * At[Ai+1] + c * At[Aj+1];
				At[Ai+1] = t0;
				At[Aj+1] = t1;
				a += t0 * t0;
				b += t1 * t1;
				
				for (int k = 2; k < m; k++) {
					t0 = c * At[Ai+k] + s * At[Aj+k];
					t1 = -s * At[Ai+k] + c * At[Aj+k];
					At[Ai+k] = t0;
					At[Aj+k] = t1;
					
					a += t0 * t0;
					b += t1 * t1;
				}
				
				W[i] = a;
				W[j] = b;
				
				changed = true;
				
				if (Vt) {
					int Vi = (i * vstep);
					int Vj = (j * vstep);
					
					t0 = c * Vt[Vi] + s * Vt[Vj];
					t1 = -s * Vt[Vi] + c * Vt[Vj];
					Vt[Vi] = t0;
					Vt[Vj] = t1;
					
					t0 = c * Vt[Vi+1] + s * Vt[Vj+1];
					t1 = -s * Vt[Vi+1] + c * Vt[Vj+1];
					Vt[Vi+1] = t0;
					Vt[Vj+1] = t1;
					
					for (int k = 2; k < n; k++) {
						t0 = c * Vt[Vi+k] + s * Vt[Vj+k];
						t1 = -s * Vt[Vi+k] + c * Vt[Vj+k];
						Vt[Vi+k] = t0;
						Vt[Vj+k] = t1;
					}
				}
			}
		}
		if (changed == false)
			break;
	}
	
	for (int i = 0; i < n; i++) {
		double sd = 0;
		for (int k = 0; k < m; k++) {
			double t = At[i*astep + k];
			sd += t * t;
		}
		W[i] = sqrt_fast(sd);
	}
	
	for (int i = 0; i < n - 1; i++) {
		int j = i;
		for (int k = i + 1; k < n; k++) {
			if (W[j] < W[k])
				j = k;
		}
		if (i != j) {
			Swap(W, i, j, sd);
			if (Vt) {
				for (int k = 0; k < m; k++) {
					swap(At, i*astep + k, j*astep + k, t);
				}
				
				for (int k = 0; k < n; k++) {
					swap(Vt, i*vstep + k, j*vstep + k, t);
				}
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		_W[i] = W[i];
	}
	
	if (!Vt) {
		cache.put_buffer(W_buff);
		return;
	}
	
	for (int i = 0; i < n1; i++) {
	
		double sd = i < n ? W[i] : 0;
		
		while (sd <= minval) {
			// if we got a zero singular value, then in order to get the corresponding left singular vector
			// we generate a random vector, project it to the previously computed left singular vectors,
			// subtract the projection and normalize the difference.
			double val0 = (1.0 / m);
			for (int k = 0; k < m; k++) {
				seed = (seed * 214013 + 2531011);
				val = (((seed >> 16) & 0x7fff) & 256) != 0 ? val0 : -val0;
				At[i*astep + k] = val;
			}
			for (int iter = 0; iter < 2; iter++) {
				for (int j = 0; j < i; j++) {
					sd = 0;
					for (int k = 0; k < m; k++) {
						sd += At[i*astep + k] * At[j*astep + k];
					}
					double asum = 0.0;
					for (int k = 0; k < m; k++) {
						t = (At[i*astep + k] - sd * At[j*astep + k]);
						At[i*astep + k] = t;
						asum += abs(t);
					}
					asum = asum ? 1.0 / asum : 0;
					for (int k = 0; k < m; k++) {
						At[i*astep + k] *= asum;
					}
				}
			}
			sd = 0;
			for (int k = 0; k < m; k++) {
				t = At[i*astep + k];
				sd += t * t;
			}
			sd = sqrt_fast(sd);
		}
		
		s = (1.0 / sd);
		for (int k = 0; k < m; k++) {
			At[i*astep + k] *= s;
		}
	}
	
	cache.put_buffer(W_buff);
}


bool lu_solve(A, B) {
	//var i = 0, j = 0, k = 0, p = 1, astep = A.cols;
	var ad = A.data, bd = B.data;
	//var t, alpha, d, s;
	
	for (int i = 0; i < astep; i++) {
		int k = i;
		for (int j = i + 1; j < astep; j++) {
			if (abs(ad[j*astep + i]) > abs(ad[k*astep+i])) {
				k = j;
			}
		}
		
		if (abs(ad[k*astep+i]) < EPSILON) {
			return false; // FAILED
		}
		
		if (k != i) {
			for (int j = i; j < astep; j++) {
				swap(ad, i*astep + j, k*astep + j, t);
			}
			
			swap(bd, i, k, t);
			p = -p;
		}
		
		double d = -1.0 / ad[i*astep+i];
		
		for (int j = i + 1; j < astep; j++) {
			double alpha = ad[j*astep+i] * d;
			
			for (int k = i + 1; k < astep; k++) {
				ad[j*astep+k] += alpha * ad[i*astep+k];
			}
			
			bd[j] += alpha * bd[i];
		}
		
		ad[i*astep+i] = -d;
	}
	
	for (int i = astep - 1; i >= 0; i--) {
		double s = bd[i];
		for (int k = i + 1; k < astep; k++) {
			s -= ad[i*astep+k] * bd[k];
		}
		bd[i] = s * ad[i*astep+i];
	}
	
	return true; // OK
}


bool cholesky_solve(A, B) {
	//var col = 0, row = 0, col2 = 0, cs = 0, rs = 0, i = 0, j = 0;
	int size = A.cols;
	var ad = A.data, bd = B.data;
	//var val, inv_diag;
	
	for (int col = 0; col < size; col++) {
		double inv_diag = 1.0;
		int cs = (col * size);
		int rs = cs;
		for (int row = col; row < size; row++) {
			// correct for the parts of cholesky already computed
			double val = ad[(rs+col)];
			for (int col2 = 0; col2 < col; col2++) {
				val -= ad[(col2*size+col)] * ad[(rs+col2)];
			}
			if (row == col) {
				// this is the diagonal element so don't divide
				ad[(rs+col)] = val;
				if (val == 0) {
					return 0; // FAILED
				}
				inv_diag = 1.0 / val;
			}
			else {
				// cache the value without division in the upper half
				ad[(cs+row)] = val;
				// divide my the diagonal element for all others
				ad[(rs+col)] = val * inv_diag;
			}
			rs = (rs + size);
		}
	}
	
	// first backsub through L
	{
		int cs = 0;
		for (int i = 0; i < size; i++) {
			double val = bd[i];
			for (int j = 0; j < i; j++) {
				val -= ad[(cs+j)] * bd[j];
			}
			bd[i] = val;
			cs = (cs + size);
		}
	}
	
	// backsub through diagonal
	{
		int cs = 0;
		for (int i = 0; i < size; i++) {
			bd[i] /= ad[(cs + i)];
			cs = (cs + size);
		}
	}
	
	// backsub through L Transpose
	for (int i = (size - 1); i >= 0; i--) {
		double val = bd[i];
		int j = (i + 1);
		int cs = (j * size);
		for (; j < size; j++) {
			val -= ad[(cs + i)] * bd[j];
			cs = (cs + size);
		}
		bd[i] = val;
	}
	
	return 1;
}


void svd_decompose(A, W, U, V, int options = 0) {
	//var at = 0, i = 0, j = 0, m = _m, n = _n;
	int _m = A.rows;
	int _n = A.cols
			 var dt = A.type | C1_t; // we only work with single channel
	         
	bool at = false;
	if (m < n) {
		at = true;
		Swap(m, n);
	}
	
	var a_buff = cache.get_buffer((m * m) << 3);
	var w_buff = cache.get_buffer(n << 3);
	var v_buff = cache.get_buffer((n * n) << 3);
	
	matrix_t a_mt(m, m, dt, a_buff.data);
	matrix_t w_mt(1, n, dt, w_buff.data);
	matrix_t v_mt(n, n, dt, v_buff.data);
	
	if (!at {
	// transpose
	transpose(a_mt, A);
	}
	else {
		int i;
		for (i = 0; i < _n*_m; i++) {
			a_mt.data[i] = A.data[i];
		}
		for (; i < n*m; i++) {
			a_mt.data[i] = 0;
		}
	}
	
	JacobiSVDImpl(a_mt.data, m, w_mt.data, v_mt.data, n, m, n, m);
	
	if (W) {
	int i;
	for (i = 0; i < n; i++) {
			W.data[i] = w_mt.data[i];
		}
		for (; i < _n; i++) {
			W.data[i] = 0;
		}
	}
	
	if (!at) {
	if (U && (options & SVD_U_T)) {
			int i = m * m;
			while (--i >= 0) {
				U.data[i] = a_mt.data[i];
			}
		}
		else
			if (U) {
				transpose(U, a_mt);
			}
			
		if (V && (options & SVD_V_T)) {
			int i = n * n;
			while (--i >= 0) {
				V.data[i] = v_mt.data[i];
			}
		}
		else
			if (V) {
				transpose(V, v_mt);
			}
	}
	else {
		if (U && (options & SVD_U_T)) {
			int i = n * n;
			while (--i >= 0) {
				U.data[i] = v_mt.data[i];
			}
		}
		else
			if (U) {
				transpose(U, v_mt);
			}
			
		if (V && (options & SVD_V_T)) {
			int i = m * m;
			while (--i >= 0) {
				V.data[i] = a_mt.data[i];
			}
		}
		else
			if (V) {
				transpose(V, a_mt);
			}
	}
	
	cache.put_buffer(a_buff);
	cache.put_buffer(w_buff);
	cache.put_buffer(v_buff);
}


void svd_solve(A, X, B) {
	//var i = 0, j = 0, k = 0;
	var pu = 0, pv = 0;
	var nrows = A.rows, ncols = A.cols;
	//double sum = 0.0, xsum = 0.0, tol = 0.0;
	var dt = A.type | C1_t;
	
	var u_buff = cache.get_buffer((nrows * nrows) << 3);
	var w_buff = cache.get_buffer(ncols << 3);
	var v_buff = cache.get_buffer((ncols * ncols) << 3);
	
	matrix_t u_mt(nrows, nrows, dt, u_buff.data);
	matrix_t w_mt(1, ncols, dt, w_buff.data);
	matrix_t v_mt(ncols, ncols, dt, v_buff.data);
	
	var bd = B.data;
	ud = u_mt.data;
	wd = w_mt.data;
	vd = v_mt.data;
	
	svd_decompose(A, w_mt, u_mt, v_mt, 0);
	
	double tol = EPSILON * wd[0] * ncols;
	
	for (int i = 0; i < ncols; i++, pv += ncols) {
		double xsum = 0.0;
		for (int j = 0; j < ncols; j++) {
			if (wd[j] > tol) {
				double sum = 0.0;
				for (int k = 0, pu = 0; k < nrows; k++, pu += ncols) {
					sum += ud[pu + j] * bd[k];
				}
				xsum += sum * vd[pv + j] / wd[j];
			}
		}
		X.data[i] = xsum;
	}
	
	cache.put_buffer(u_buff);
	cache.put_buffer(w_buff);
	cache.put_buffer(v_buff);
}


void svd_invert(Ai, A) {
	//var i = 0, j = 0, k = 0;
	//var pu = 0, pv = 0, pa = 0;
	int nrows = A.rows, ncols = A.cols;
	//var sum = 0.0, tol = 0.0;
	var dt = A.type | C1_t;
	
	var u_buff = cache.get_buffer((nrows * nrows) << 3);
	var w_buff = cache.get_buffer(ncols << 3);
	var v_buff = cache.get_buffer((ncols * ncols) << 3);
	
	matrix_t u_mt(nrows, nrows, dt, u_buff.data);
	matrix_t w_mt(1, ncols, dt, w_buff.data);
	matrix_t v_mt(ncols, ncols, dt, v_buff.data);
	
	var id = Ai.data;
	ud = u_mt.data;
	wd = w_mt.data;
	vd = v_mt.data;
	
	svd_decompose(A, w_mt, u_mt, v_mt, 0);
	
	double tol = EPSILON * wd[0] * ncols;
	
	for (int i = 0; i < ncols; i++, pv += ncols) {
		for (int j = 0, pu = 0; j < nrows; j++, pa++) {
			double sum = 0.0;
			for (int k = 0; k < ncols; k++, pu++) {
				if (wd[k] > tol)
					sum += vd[pv + k] * ud[pu] / wd[k];
			}
			id[pa] = sum;
		}
	}
	
	cache.put_buffer(u_buff);
	cache.put_buffer(w_buff);
	cache.put_buffer(v_buff);
}


void eigenVV(A, vects, vals) {
	int n = A.cols;
	var dt = A.type | C1_t;
	
	var a_buff = cache.get_buffer((n * n) << 3);
	var w_buff = cache.get_buffer(n << 3);
	matrix_t a_mt(n, n, dt, a_buff.data);
	matrix_t w_mt(1, n, dt, w_buff.data);
	
	int i = n * n;
	while (--i >= 0) {
		a_mt.data[i] = A.data[i];
	}
	
	JacobiImpl(a_mt.data, n, w_mt.data, vects ? vects.data : NULL, n, n);
	
	if (vals) {
		while (--n >= 0) {
			vals.data[n] = w_mt.data[n];
		}
	}
	
	cache.put_buffer(a_buff);
	cache.put_buffer(w_buff);
}

}

NAMESPACE_TOPSIDE_END

#endif
