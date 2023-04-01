#include "High.h"

namespace UPP {

#define LTIMING(x) // RTIMING(x)

Vector<HiValue>& HiValue::CloneArray()
{
	LTIMING("CloneArray");
	ASSERT(IsArray());
	if(array->refcount != 1) {
		HiArray *c = new HiArray;
		c->array <<= array->array;
		array->Release();
		array = c;
	}
	hash = 0;
	return array->array;
}

const Vector<HiValue>& HiValue::GetArray() const
{
	ASSERT(IsArray());
	return array->array;
}

HiValue& HiValue::ArrayGet(int i) {
	ASSERT(IsArray());
	return array->array[i];
}

const HiValue& HiValue::ArrayGet(int i) const {
	ASSERT(IsArray());
	return array->array[i];
}

HiValue HiValue::ArrayGetMid(int i, int n) const
{
	LTIMING("ArrayGet");
	const Vector<HiValue>& sa = GetArray();
	ASSERT(i >= 0 && i + n <= sa.GetCount());
	HiValue t;
	t.SetEmptyArray();
	t.array->array.Append(sa, i, n);
	return t;
}

HiValue& HiValue::operator[](int i) {
	ASSERT(IsArray());
	return array->array[i];
}

HiValue HiValue::operator()(int i) const {
	if (IsArray() && i >= 0 && i < array->array.GetCount())
		return array->array[i];
	else
		return HiValue();
}

HiValue HiValue::operator()(int i, HiValue def) const {
	if (IsArray() && i >= 0 && i < array->array.GetCount())
		return array->array[i];
	else
		return def;
}

const HiValue& HiValue::operator[](int i) const {
	ASSERT(IsArray());
	return array->array[i];
}

void HiValue::SetEmptyArray()
{
	Free();
	type = HIGH_ARRAY;
	hash = 0;
	array = new HiArray;
}

bool HiValue::ArraySet(int i, HiValue val)
{
	LTIMING("ArraySet");
	ASSERT(IsArray());
	if (!IsArray())
		return false;
	Vector<HiValue>& ta = array->array; //CloneArray();
	if(i > max_total || i - ta.GetCount() + total > max_total)
		return false;
	array->array.At(i) = val;
	return true;
}

bool HiValue::ArrayRemoveValue(HiValue val) {
	ASSERT(IsArray());
	if (!IsArray())
		return false;
	int i = 0;
	bool removed = false;
	auto& ta = array->array;
	for (const HiValue& v : ta) {
		if (v == val) {
			ta.Remove(i--);
			removed = true;
		}
		i++;
	}
	return removed;
}

HiValue& HiValue::ArrayAdd(HiValue val)
{
	LTIMING("ArrayAdd");
	ASSERT(IsVoid() || IsArray());
	if(IsVoid() || !IsArray())
		SetEmptyArray();
	return array->array.Add(val);
}

bool HiValue::Replace(int i, int n, HiValue a)
{
	LTIMING("Array Replace");
	ASSERT(IsArray());
	if (!IsArray())
		return false;
	ASSERT(i >= 0);
	Vector<HiValue>& ta = array->array; //CloneArray();
	if(i > max_total || i + n > max_total || i + n - ta.GetCount() + total > max_total)
		return false;
	if(i > 0)
		ta.At(i - 1);
	const Vector<HiValue>& sa = a.GetArray();
	int q = sa.GetCount() - n;
	if(q > 0)
		ta.InsertN(i, q);
	else
		ta.Remove(i, -q);
	//int last = sa.GetCount()-1 + i;
	//if (last >= ta.GetCount())
	//	return false;
	for(q = 0; q < sa.GetCount(); q++)
		ta[q + i] = sa[q];
	return true;
}

bool HiValue::Append(HiValue a)
{
	if(IsVoid())
		SetEmptyArray();
	return Replace(0, GetCount(), a);
}

HiValue::operator WString() const
{
	#if LIBTOPSIDE
	LTIMING("operator WString");
	WStringStream s;
	if(IsArray()) {
		const Vector<HiValue>& a = GetArray();
		for(int i = 0; i < a.GetCount(); i++) {
			if(a[i].IsInt()) {
				int c = a[i].GetInt();
				if(c >= 0 && c < 65536)
					s.Cat(c);
			}
		}
	}
	return WString(s);
	#else
	LTIMING("operator WString");
	WString s;
	if(IsArray()) {
		const Vector<HiValue>& a = GetArray();
		for(int i = 0; i < a.GetCount(); i++) {
			if(a[i].IsInt()) {
				int c = a[i].GetInt();
				if(c >= 0 && c < 65536)
					s.Cat(c);
			}
		}
	}
	return s;
	#endif
}

void HiValue::InitString(const WString& s)
{
	type = HIGH_ARRAY;
	array = new HiArray();
	hash = 0;
	Vector<HiValue>& a = array->array;
	a.SetCount(s.GetCount());
	for(int i = 0; i < s.GetCount(); i++)
		a[i] = (int64)s[i];
	total++;
}

int   HiValue::GetTotalCount()
{
	return total;
}

void  HiValue::SetMaxTotalCount(int n)
{
	max_total = n;
}

int   HiValue::GetMaxTotalCount()
{
	return max_total;
}

HiValue::HiValue()
{
	type = HIGH_VOID; hash = 0; total++;
}

HiValue::HiValue(double n)
{
	number = n;
	type = HIGH_DOUBLE;
	hash = 0;
	total++;
}

HiValue::HiValue(int64 n)
{
	i64 = n;
	type = HIGH_INT64;
	hash = 0;
	total++;
}

HiValue::HiValue(int n)
{
	i64 = n;
	type = HIGH_INT64;
	hash = 0;
	total++;
}

HiValue::HiValue(AtomBase& a) {
	atom = &a;
	type = HIGH_ATOM;
	hash = (size_t)&a;
	total++;
}

}
