#include "Statistics.h"


NAMESPACE_OULU_BEGIN

Vector<int> RandomNumberGenerator::Permutation(int num) {
	Vector<int> v;
	v.SetCount(num);
	for(int& i : v)
		i = Random(num);
	return v;
}

NAMESPACE_OULU_END
