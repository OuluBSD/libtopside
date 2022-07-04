#ifndef _ComputerVision_LinearAlgebra_h_
#define _ComputerVision_LinearAlgebra_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T>
void Swap(Vector<T>& A, int i0, int i1, T& t) {
	t = A[i0];
	A[i0] = A[i1];
	A[i1] = t;
}

double hypot(double a, double b);

template <class T>
void JacobiImpl(Vector<T>& A, int astep, Vector<T>& W, Vector<T>* V, int vstep, int n) {
	double eps = EPSILON;
	int i = 0, j = 0, k = 0, m = 0, l = 0, idx = 0, _in = 0, _in2 = 0;
	int max_iter = n * n * 30;
	T mv = 0, val = 0, p = 0, y = 0, t = 0, s = 0, c = 0, a0 = 0, b0 = 0;
	
	static thread_local Vector<int> indR;
	static thread_local Vector<int> indC;
	indR.SetCount(n << 2);
	indC.SetCount(n << 2);
	
	Vector<T>& v = *V;
		
	if (V) {
		for (int i = 0; i < n; i++) {
			k = i * vstep;
			for (j = 0; j < n; j++) {
				(*V)[k + j] = 0.0;
			}
			v[k + i] = 1.0;
		}
	}
	
	for (int k = 0; k < n; k++) {
		W[k] = A[(astep + 1)*k];
		if (k < n - 1) {
			int m;
			for (m = k + 1, mv = Abs(A[astep*k + m]), i = k + 2; i < n; i++) {
				val = Abs(A[astep*k+i]);
				if (mv < val)
					mv = val, m = i;
			}
			indR[k] = m;
		}
		if (k > 0) {
			int m;
			for (m = 0, mv = Abs(A[k]), i = 1; i < k; i++) {
				val = Abs(A[astep*i+k]);
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
			int mv = Abs(A[indR[0]]);
			for (int i = 1; i < n - 1; i++) {
				val = Abs(A[astep*i + indR[i]]);
				if (mv < val)
					mv = val, k = i;
			}
			l = indR[k];
			for (int i = 1; i < n; i++) {
				val = Abs(A[astep*indC[i] + i]);
				if (mv < val)
					mv = val, k = indC[i], l = i;
			}
			
			p = A[astep*k + l];
			
			if (Abs(p) <= eps)
				break;
				
			y = (W[l] - W[k]) * 0.5;
			t = Abs(y) + hypot(p, y);
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
					a0 = v[_in];
					b0 = v[_in2];
					v[_in] = a0 * c - b0 * s;
					v[_in2] = a0 * s + b0 * c;
				}
			}
			
			for (int j = 0; j < 2; j++) {
				idx = j == 0 ? k : l;
				if (idx < n - 1) {
					int m = idx + 1;
					int mv = Abs(A[astep*idx + m]);
					for (int i = idx + 2; i < n; i++) {
						val = Abs(A[astep*idx+i]);
						if (mv < val)
							mv = val, m = i;
					}
					indR[idx] = m;
				}
				if (idx > 0) {
					int m = 0;
					int mv = Abs(A[idx]);
					for (i = 1; i < idx; i++) {
						val = Abs(A[astep*i+idx]);
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
					Swap(v, vstep*m + i, vstep*k + i, mv);
				}
			}
		}
	}
	
}

template <class T>
void JacobiSVDImpl(Vector<T>& At, double astep, Vector<T>& _W, Vector<T>* Vt, double vstep, int m, int n, int n1) {
	struct PoolNode {
		Vector<double> f64;
	};
	struct Cache {
		ArrayMap<int, PoolNode> nodes;
		PoolNode& GetBuffer(int sz) {
			int i = nodes.Find(sz);
			if (i >= 0)
				return nodes[i];
			PoolNode& n = nodes.Add(i);
			n.f64.SetSize(sz);
			return n;
		}
		static Cache& Local() {static Cache c; return c;}
	};
	
	Cache& cache = Cache::Local();
	double eps = EPSILON * 2.0;
	double minval = FLT_MIN;
	int max_iter = max(m, 30);
	int seed = 0x1234;
	double val = 0.0, val0 = 0.0, asum = 0.0;
	
	PoolNode* W_buff = cache.get_buffer(n << 3);
	auto& W = W_buff->f64;
	
	for (int i = 0; i < n; i++) {
		double sd = 0;
		for (int k = 0; k < m; k++) {
			int j = (int)(i*astep + k);
			double t = At[j];
			sd += t * t;
		}
		W[i] = sd;
		
		if (Vt) {
			for (int k = 0; k < n; k++) {
				int j = (int)(i*vstep + k);
				(*Vt)[j] = 0;
			}
			int j = (int)(i*vstep + i);
			(*Vt)[j] = 1;
		}
	}
	
	for (int iter = 0; iter < max_iter; iter++) {
		bool changed = false;
		
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int Ai = (int)(i * astep);
				int Aj = (int)(j * astep);
				double a = W[i];
				double p = 0;
				double b = W[j];
				
				p += At[Ai] * At[Aj];
				p += At[Ai+1] * At[Aj+1];
				
				for (int k = 2; k < m; k++)
					p += At[Ai+k] * At[Aj+k];
					
				if (Abs(p) <= eps*FastSqrt(a*b))
					continue;
					
				p *= 2.0;
				double beta = a - b;
				double gamma = hypot(p, beta);
				double s, c;
				if (beta < 0) {
					double delta = (gamma - beta) * 0.5;
					s = FastSqrt(delta / gamma);
					c = (p / (gamma * s * 2.0));
				}
				else {
					c = FastSqrt((gamma + beta) / (gamma * 2.0));
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
					auto& v = *Vt;
					int Vi = (int)(i * vstep);
					int Vj = (int)(j * vstep);
					
					t0 = c * v[Vi] + s * v[Vj];
					t1 = -s * v[Vi] + c * v[Vj];
					v[Vi] = t0;
					v[Vj] = t1;
					
					t0 = c * v[Vi+1] + s * v[Vj+1];
					t1 = -s * v[Vi+1] + c * v[Vj+1];
					v[Vi+1] = t0;
					v[Vj+1] = t1;
					
					for (int k = 2; k < n; k++) {
						t0 = c * v[Vi+k] + s * v[Vj+k];
						t1 = -s * v[Vi+k] + c * v[Vj+k];
						v[Vi+k] = t0;
						v[Vj+k] = t1;
					}
				}
			}
		}
		if (changed == false)
			break;
	}
	
	double sd = 0;
	for (int i = 0; i < n; i++) {
		sd = 0;
		for (int k = 0; k < m; k++) {
			int j = (int)(i*astep + k);
			double t = At[j];
			sd += t * t;
		}
		W[i] = FastSqrt(sd);
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
				double t;
				for (int k = 0; k < m; k++) {
					int a = (int)(i*astep + k);
					int b = (int)(j*astep + k);
					Swap(At, a, b, t);
				}
				
				for (int k = 0; k < n; k++) {
					int a = (int)(i*vstep + k);
					int b = (int)(j*vstep + k);
					Swap(*Vt, a, b, t);
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
				int a = (int)(i*astep + k);
				At[a] = val;
			}
			for (int iter = 0; iter < 2; iter++) {
				for (int j = 0; j < i; j++) {
					sd = 0;
					for (int k = 0; k < m; k++) {
						int a = (int)(i*astep + k);
						int b = (int)(j*astep + k);
						sd += At[a] * At[b];
					}
					double asum = 0.0;
					for (int k = 0; k < m; k++) {
						int a = (int)(i*astep + k);
						int b = (int)(j*astep + k);
						double t = (At[a] - sd * At[b]);
						At[a] = t;
						asum += Abs(t);
					}
					asum = asum ? 1.0 / asum : 0;
					for (int k = 0; k < m; k++) {
						int a = (int)(i*astep + k);
						At[a] *= asum;
					}
				}
			}
			sd = 0;
			for (int k = 0; k < m; k++) {
				int a = (int)(i*astep + k);
				double t = At[a];
				sd += t * t;
			}
			sd = FastSqrt(sd);
		}
		
		double s = (1.0 / sd);
		for (int k = 0; k < m; k++) {
			int a = (int)(i*astep + k);
			At[a] *= s;
		}
	}
	
	cache.put_buffer(W_buff);
}


bool LUSolve(DMatrix<float>& A, DMatrix<float>& B);

template<class T>
bool CholeskySolve(DMatrix<T>& A, DMatrix<T>& B) {
	int size = A.cols;
	Vector<T>& ad = A.data;
	Vector<T>& bd = B.data;
	
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
				ad[(rs+col)] = (T)val;
				if (val == 0) {
					return 0; // FAILED
				}
				inv_diag = 1.0 / val;
			}
			else {
				// cache the value without division in the upper half
				ad[(cs+row)] = (T)val;
				// divide my the diagonal element for all others
				ad[(rs+col)] = (T)(val * inv_diag);
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
			bd[i] = (T)val;
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
		bd[i] = (T)val;
	}
	
	return 1;
}

template <class T>
void SVDDecompose(const DMatrix<T>& A, DMatrix<T>* W, DMatrix<T>* U, DMatrix<T>* V, int options = 0) {
	DMatrix<T>& w = *W;
	DMatrix<T>& u = *U;
	DMatrix<T>& v = *V;
	
	int _m = A.rows;
	int _n = A.cols;
	int dt = 1; // we only work with single channel
	
	int m = _m, n = _n;
	bool at = false;
	if (m < n) {
		at = true;
		UPP::Swap(m, n);
	}
	
	DMatrix<T> a_mt(m, m, dt);
	DMatrix<T> w_mt(1, n, dt);
	DMatrix<T> v_mt(n, n, dt);
	
	if (!at) {
		// transpose
		Transpose(a_mt, A);
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
	
	JacobiSVDImpl(a_mt.data, m, w_mt.data, &v_mt.data, n, m, n, m);
	
	if (W) {
		int i;
		for (i = 0; i < n; i++) {
			w.data[i] = w_mt.data[i];
		}
		for (; i < _n; i++) {
			w.data[i] = 0;
		}
	}
	
	if (!at) {
		if (U && (options & SVD_U_T)) {
			int i = m * m;
			while (--i >= 0) {
				u.data[i] = a_mt.data[i];
			}
		}
		else if (U) {
			Transpose(u, a_mt);
		}
		
		if (V && (options & SVD_V_T)) {
			int i = n * n;
			while (--i >= 0) {
				v.data[i] = v_mt.data[i];
			}
		}
		else if (V) {
			Transpose(v, v_mt);
		}
	}
	else {
		if (U && (options & SVD_U_T)) {
			int i = n * n;
			while (--i >= 0) {
				u.data[i] = v_mt.data[i];
			}
		}
		else if (U) {
			Transpose(u, v_mt);
		}
			
		if (V && (options & SVD_V_T)) {
			int i = m * m;
			while (--i >= 0) {
				v.data[i] = a_mt.data[i];
			}
		}
		else if (V) {
			Transpose(v, a_mt);
		}
	}
}


template <class T>
void SVDSolve(const DMatrix<T>& A, DMatrix<T>& X, const DMatrix<T>& B) {
	int pu = 0, pv = 0;
	int nrows = A.rows, ncols = A.cols;
	int dt = 1;
	
	DMatrix<T> u_mt(nrows, nrows, dt);
	DMatrix<T> w_mt(1, ncols, dt);
	DMatrix<T> v_mt(ncols, ncols, dt);
	
	auto& bd = B.data;
	auto& ud = u_mt.data;
	auto& wd = w_mt.data;
	auto& vd = v_mt.data;
	
	SVDDecompose(A, w_mt, u_mt, v_mt, 0);
	
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
	
}


template <class T>
void SVDInvert(const DMatrix<T>& Ai, const DMatrix<T>& A) {
	int nrows = A.rows;
	int ncols = A.cols;
	int dt = A.channels ? A.channels : 1;
	
	DMatrix<T> u_mt(nrows, nrows, dt);
	DMatrix<T> w_mt(1, ncols, dt);
	DMatrix<T> v_mt(ncols, ncols, dt);
	
	auto& id = Ai.data;
	auto& ud = u_mt.data;
	auto& wd = w_mt.data;
	auto& vd = v_mt.data;
	
	SVDDecompose(A, w_mt, u_mt, v_mt, 0);
	
	double tol = EPSILON * wd[0] * ncols;
	
	for (int i = 0, pv = 0, pa = 0; i < ncols; i++, pv += ncols) {
		for (int j = 0, pu = 0; j < nrows; j++, pa++) {
			double sum = 0.0;
			for (int k = 0; k < ncols; k++, pu++) {
				if (wd[k] > tol)
					sum += vd[pv + k] * ud[pu] / wd[k];
			}
			id[pa] = sum;
		}
	}
}



void EigenVV(const FloatMat& A, FloatMat* vects=0, FloatMat* vals=0);


NAMESPACE_TOPSIDE_END

#endif
