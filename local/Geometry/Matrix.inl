NAMESPACE_TOPSIDE_BEGIN

template <class T, int I>
Vec<T,I> Vec<T,I>::operator*(const Matrix<T,I,I>& m) const {
	Vec<T,I> r;
	for(int i = 0; i < I; i++) {
		T& d = r[i];
		d = 0;
		for(int j = 0; j < I; j++)
			d += data[j] *m[j][i];
	}
	return r;
}


NAMESPACE_TOPSIDE_END
