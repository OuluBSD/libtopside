NAMESPACE_TOPSIDE_BEGIN

#if 1
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
#else
template <class T, int I>
Vec<T,I> Vec<T,I>::operator*(const Matrix<T,I,I>& m) const {
	Vec<T,I> r;
	for(int i = 0; i < I; i++) {
		T& d = r[i];
		d = 0;
		for(int j = 0; j < I; j++)
			d += data[i] * m[i][j];
	}
	return r;
}
#endif


NAMESPACE_TOPSIDE_END
