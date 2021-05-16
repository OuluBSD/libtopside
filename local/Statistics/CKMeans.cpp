#include "Statistics.h"

NAMESPACE_TOPSIDE_BEGIN


MatFloat CreateMatrix(int columns, int rows) {
	MatFloat matrix;
	matrix.SetCount(columns);
	for (int i = 0; i < columns; i++)
		matrix[i].SetCount(rows, 0);
	return matrix;
}

VecFloat SortVector(const VecFloat& v) {
	VecFloat ret;
	ret <<= v;
	Sort(ret, StdLess<double>());
	return ret;
}

int GetCountUniqueSorted(const VecFloat& sorted) {
	int c = 0;
	int last;
	for (int i = 0; i < sorted.GetCount(); i++) {
		if (i == 0 || sorted[i] != last) {
			last = sorted[i];
			c++;
		}
	}
	return c;
}

double SumSquares(int j, int i, const VecFloat& sums, const Vector<double>& sum_of_squares) {
	double sji;
	if (j > 0) {
		double muji = (sums[i] - sums[j - 1]) / (i - j + 1);
		sji = sum_of_squares[i] - sum_of_squares[j - 1] - (i - j + 1) * muji * muji;
	}
	else {
		sji = sum_of_squares[i] - (sums[i] * sums[i]) / (i + 1);
	}
	if (sji < 0) {
		return 0;
	}
	return sji;
}


void FillMatrixColumn(
	int min_i,
	int max_i,
	int cluster,
	MatFloat& matrix,
	MatFloat& backtrack_matrix,
	const VecFloat& sums,
	const VecFloat& sum_of_squares
) {
	if (min_i > max_i) {
		return;
	}
	
	int i = floor((min_i + max_i) / 2);
	
	matrix[cluster][i] = matrix[cluster - 1][i - 1];
	backtrack_matrix[cluster][i] = i;
	
	int low_j = cluster;
	
	if (min_i > cluster) {
		low_j = max<double>(low_j, backtrack_matrix[cluster][min_i - 1]);
	}
	low_j = max<double>(low_j, backtrack_matrix[cluster - 1][i]);
	
	int high_j = i - 1;
	if (max_i < matrix[0].GetCount() - 1) {
		high_j = min<double>(high_j, backtrack_matrix[cluster][max_i + 1]);
	}
	
	double sji;
	double slow_ji;
	double ssqlow_j;
	double ssqj;
	for (int j = high_j; j >= low_j; --j) {
		sji = SumSquares(j, i, sums, sum_of_squares);
		
		if (sji + matrix[cluster - 1][low_j - 1] >= matrix[cluster][i]) {
			break;
		}
		
		slow_ji = SumSquares(low_j, i, sums, sum_of_squares);
		
		ssqlow_j = slow_ji + matrix[cluster - 1][low_j - 1];
		
		if (ssqlow_j < matrix[cluster][i]) {
			matrix[cluster][i] = ssqlow_j;
			backtrack_matrix[cluster][i] = low_j;
		}
		low_j++;
		
		ssqj = sji + matrix[cluster - 1][j - 1];
		if (ssqj < matrix[cluster][i]) {
			matrix[cluster][i] = ssqj;
			backtrack_matrix[cluster][i] = j;
		}
	}
	
	FillMatrixColumn(
		min_i,
		i - 1,
		cluster,
		matrix,
		backtrack_matrix,
		sums,
		sum_of_squares
	);
	FillMatrixColumn(
		i + 1,
		max_i,
		cluster,
		matrix,
		backtrack_matrix,
		sums,
		sum_of_squares
	);
}

void FillMatrices(const VecFloat& data, MatFloat& matrix, MatFloat& backtrack_matrix) {
	int c = matrix[0].GetCount();
	double shift = data[floor(c / 2)];
	
	VecFloat sums;
	VecFloat sum_of_squares;
	
	for (int i = 0, shifted; i < c; ++i) {
		shifted = data[i] - shift;
		if (i == 0) {
			sums.Add(shifted);
			sum_of_squares.Add(shifted * shifted);
		}
		else {
			sums.Add(sums[i - 1] + shifted);
			sum_of_squares.Add(sum_of_squares[i - 1] + shifted * shifted);
		}
		
		matrix[0][i] = SumSquares(0, i, sums, sum_of_squares);
		backtrack_matrix[0][i] = 0;
	}
	
	int min_i;
	for (int cluster = 1; cluster < matrix.GetCount(); ++cluster) {
		if (cluster < matrix.GetCount() - 1) {
			min_i = cluster;
		}
		else {
			min_i = c - 1;
		}
		
		FillMatrixColumn(
			min_i,
			c - 1,
			cluster,
			matrix,
			backtrack_matrix,
			sums,
			sum_of_squares
		);
	}
}



MatFloat CKMeans(const VecFloat& input, int cluster_count) {
	if (cluster_count > input.GetCount()) {
		throw new Exc("more clusters than values");
	}
	
	VecFloat sorted = SortVector(input);
	
	const int unique_count = GetCountUniqueSorted(sorted);
	
	if (unique_count == 1) {
		MatFloat ret;
		ret.Add() <<= sorted;
		return ret;
	}
	
	MatFloat matrix = CreateMatrix(cluster_count, sorted.GetCount());
	MatFloat backtrack_matrix = CreateMatrix(cluster_count, sorted.GetCount());
	
	FillMatrices(sorted, matrix, backtrack_matrix);
	
	MatFloat clusters;
	clusters.SetCount(backtrack_matrix.GetCount());
	int r_cluster = backtrack_matrix[0].GetCount() - 1;
	
	for (int cluster = backtrack_matrix.GetCount() - 1; cluster >= 0; cluster--) {
		int l_cluster = backtrack_matrix[cluster][r_cluster];
		clusters[cluster] = Slice(sorted, l_cluster, r_cluster + 1);
		if (cluster > 0)
			r_cluster = l_cluster - 1;
	}
	
	return clusters;
}



NAMESPACE_TOPSIDE_END
