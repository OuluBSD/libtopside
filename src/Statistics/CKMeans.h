#ifndef _Statistics_CKMeans_h_
#define _Statistics_CKMeans_h_

NAMESPACE_TOPSIDE_BEGIN

typedef Vector<int> VecInt;
typedef Vector<double> VecFloat;
typedef Vector<Vector<double>> MatFloat;


MatFloat CreateMatrix(int columns, int rows);
VecFloat SortVector(const VecFloat& v);
int GetCountUniqueSorted(const VecFloat& sorted);
double SumSquares(int j, int i, const VecFloat& sums, const Vector<double>& sum_of_squares);
void FillMatrixColumn(
    int min_i,
    int max_i,
    int cluster,
    MatFloat& matrix,
    MatFloat& backtrack_matrix,
    const VecFloat& sums,
    const VecFloat& sum_of_squares
);
void FillMatrices(const VecFloat& data, MatFloat& matrix, MatFloat& backtrack_matrix);
MatFloat CKMeans(const VecFloat& x, int cluster_count);

NAMESPACE_TOPSIDE_END

#endif
