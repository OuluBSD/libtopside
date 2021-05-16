#include "Statistics.h"


NAMESPACE_TOPSIDE_BEGIN

Vector<int> RandomNumberGenerator::Permutation(int num) {
	Vector<int> v;
	v.SetCount(num);
	for(int& i : v)
		i = Random(num);
	return v;
}

NAMESPACE_TOPSIDE_END
