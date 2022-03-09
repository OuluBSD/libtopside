#include <High/High.h>


namespace UPP {

#define LTIMING(x)  // RTIMING(x)

String HiTypeName(int sv_type)
{
	switch(sv_type)
	{
	case HIGH_VOID:   return "void";
	case HIGH_DOUBLE: return "double";
	case HIGH_INT64:  return "int64";
	case HIGH_ARRAY:  return "array";
	case HIGH_MAP:    return "map";
	case HIGH_LAMBDA: return "lambda";
	default:         return Format("unknown(%d)", sv_type);
	}
}

int HiValue::total;
int HiValue::max_total = 1000000;

void HiValue::Free()
{
	LTIMING("Free");
	if(type == HIGH_ARRAY)
		array->Release();
	if(type == HIGH_MAP)
		map->Release();
	if(type == HIGH_LAMBDA)
		lambda->Release();
	type = HIGH_VOID;
	hash = 0;
}

HiValue::~HiValue()
{
	LTIMING("~HiValue");
	total--;
	Free();
}

void HiValue::Assign(const HiValue& s)
{
	LTIMING("Assign");
	type = s.type;
	hash = s.hash;
	switch(type) {
	case HIGH_ARRAY:
		array = s.array;
		array->Retain();
		break;
	case HIGH_MAP:
		map = s.map;
		map->Retain();
		break;
	case HIGH_LAMBDA:
		lambda = s.lambda;
		lambda->Retain();
		break;
	case HIGH_DOUBLE:
		number = s.number;
		break;
	case HIGH_INT64:
		i64 = s.i64;
		break;
	}
}

HiValue& HiValue::operator=(const HiValue& s)
{
	LTIMING("Sval=Sval");
	Free();
	Assign(s);
	return *this;
}

HiValue::HiValue(const HiValue& s)
{
	LTIMING("Sval(Sval)");
	Assign(s);
	total++;
}

HiLambda& HiValue::CreateLambda()
{
	Free();
	lambda = new HiLambda;
	type = HIGH_LAMBDA;
	hash = 0;
	return *lambda;
}

const HiLambda& HiValue::GetLambda() const
{
	ASSERT(IsLambda());
	return *lambda;
}

int HiValue::GetCount() const
{
	switch(type) {
	case HIGH_VOID:
		return 0;
	case HIGH_ARRAY:
		return array->array.GetCount();
	case HIGH_MAP:
		return map->count;
	}
	return 1;
}

hash_t HiValue::GetHashValue() const
{
	LTIMING("GetHashValue");
	if(hash == 0) {
		switch(type) {
		case HIGH_VOID:
			hash = 1;
			break;
		case HIGH_DOUBLE:
			hash = UPP::GetHashValue(number) | 0x80000;
			break;
		case HIGH_INT64:
			hash = UPP::GetHashValue(i64) | 0x80000;
			break;
		case HIGH_ARRAY:
			for(int i = 0; i < array->array.GetCount(); i++)
				hash = hash ^ array->array[i].GetHashValue();
			hash |= 0x40000;
			break;
		case HIGH_MAP:
			for(int i = 0; i < map->map.GetCount(); i++)
				if(!map->map[i].IsVoid())
					hash ^= map->map.GetKey(i).GetHashValue() ^ map->map[i].GetHashValue();
			hash |= 0x8000000;
			break;
		case HIGH_LAMBDA:
			hash = UPP::GetHashValue(lambda->code) | 0x4000000;
			break;
		}
	}
	return hash;
}

template <class T>
bool EqVector(const T& a, const T& b)
{
	if(a.GetCount() != b.GetCount())
		return false;
	for(int i = 0; i < a.GetCount(); i++)
		if(a[i] != b[i])
			return false;
	return true;
}

bool HiValue::operator==(const HiValue& a) const
{
	LTIMING("operator==");
	int i;
	switch(type) {
		case HIGH_VOID:
			return a.type == HIGH_VOID;
		case HIGH_INT64:
			if(a.type == HIGH_INT64)
				return i64 == a.i64;
		case HIGH_DOUBLE:
			return a.IsNumber() && GetNumber() == a.GetNumber();
		case HIGH_ARRAY:
			if(a.type != HIGH_ARRAY) return false;
			if(array->array.GetCount() != a.array->array.GetCount())
				return false;
			return EqVector(array->array, a.array->array);
		case HIGH_MAP: {
			if (a.type != HIGH_MAP) return false;
			if (map == a.map) return true;
			const VectorMap<HiValue, HiValue>& x = GetMap();
			const VectorMap<HiValue, HiValue>& y = a.GetMap();
			for(i = 0; i < x.GetCount(); i++) {
				int q = y.Find(x.GetKey(i));
				if(q < 0)
					return false;
				if(x[i] != y[q])
					return false;
			}
			for(i = 0; i < y.GetCount(); i++)
				if(x.Find(y.GetKey(i)) < 0)
					return false;
			return true;
		}
		case HIGH_LAMBDA:
			return lambda->code == a.lambda->code &&
			       EqVector(lambda->arg, a.lambda->arg) && EqVector(lambda->inout, a.lambda->inout);
	}
	return false;
}

String HiValue::ToString(int maxlen, int indent_step, bool hex, int indent) const
{
	String ind(' ', indent);
	StringStream r;
	String s;
	int i;
	switch(type) {
	case HIGH_DOUBLE:
		{
			s = ind;
			if((int64)number == number)
				s << IntStr64((int64)number);
			else
				s << TS::FormatScientific(number);
			
			if (hex && FitsInInt64(number) && (int64)number == number)
				s << " " << HexStr((int64)number);
			if (hex && number >= 0 && number < 65536 && (int)number == number)
				s << " " << AsCString(::UPP::AsString(WString((wchar_t)number, 1)));
			
			return s;
		}
	case HIGH_INT64:
		{
			s = ind;
			s << IntStr64(i64);
			if(hex)
				s << " " << HexStr(i64);
			if(hex && i64 >= 0 && i64 < 65536)
				s << " " << AsCString(::UPP::AsString(WString((int)i64, 1)));
			return s;
		}
	case HIGH_ARRAY:
		{
			const Vector<HiValue>& a = GetArray();
			int i;
			int c = min(100, a.GetCount());
			for(i = 0; i < a.GetCount(); i++) {
				if(!a[i].IsInt())
					break;
				int c = a[i].GetInt();
				if(c >= 32 && c < 256)
					s.Cat(c);
				else
					break;
			}
			if (i < a.GetCount()) {
				r << ind << "[ ";
				for(i = 0; i < c; i++) {
					if(i)
						r << ", ";
					r << array->array[i].ToString(maxlen, indent_step, hex, 0);
				}
				r << " ]";
				if (r.GetSize() >= maxlen) {
					r.Seek(0);
					r.SetSize(0);
					r << ind << "[\n";
					for(i = 0; i < c; i++) {
						if(i)
							r << ",\n";
						r << array->array[i].ToString(maxlen, indent_step, hex, indent + indent_step);
					}
					r.Put('\n');
					r << "\n" << ind << "]";
				}
				s = r.GetResult();
			}
			else {
				r << ind << "\"" << s << "\"";
				s = r.GetResult();
			}
			if(a.GetCount() > 100)
				s << ind << "\n...more than 100 elements";
			return s;
		}
	case HIGH_LAMBDA:
		r << ind << "@(";
		for(i = 0; i < lambda->arg.GetCount(); i++) {
			if(i)
				r << ", ";
			if(lambda->inout[i])
				r << "&";
			r << lambda->arg[i];
		}
		r << ")\n" << lambda->code;
		return r.GetResult();
	case HIGH_MAP:
		r << ind << "{ ";
		int c = min(map->map.GetCount(), 100);
		bool q = false;
		for(i = 0; i < c; i++) {
			if(q)
				r << ", ";
			r << map->map.GetKey(i).ToString(maxlen, indent_step, hex, 0)
			  << ":" << map->map[i].ToString(maxlen, indent_step, hex, 0);
			q = true;
		}
		r << " }";
		if(r.GetSize() >= maxlen) {
			r.Seek(0);
			r.SetSize(0);
			r << ind << "{\n";
			q = false;
			for(i = 0; i < c; i++) {
				if(q)
					r << ",\n";
				r << map->map.GetKey(i).ToString(maxlen, indent_step, hex, indent + indent_step)
				  << ":\n" << map->map[i].ToString(maxlen, indent_step, hex, indent + indent_step);
				q = true;
			}
			r << "\n" << ind << "}";
		}
		s = r.GetResult();
		if(map->map.GetCount() > 100)
			s << ind << "\n...more than 100 elements";
		return s;
	}
	return "void";
}

double HiValue::GetNumber() const
{
	if(type == HIGH_INT64)
		return (double)i64;
	if(type == HIGH_DOUBLE)
		return number;
	return 0;
}

int64 HiValue::GetInt64() const
{
	if(type == HIGH_INT64)
		return i64;
	if(type == HIGH_DOUBLE && number >= (double)INT64_MIN && number <= (double)INT64_MAX)
		return (int64)number;
	return 0;
}

bool HiValue::IsInt() const
{
	if(IsInt64()) {
		int64 n = GetInt64();
		return n >= INT_MIN && n <= INT_MAX;
	}
	if(IsNumber()) {
		double n = GetNumber();
		return n >= INT_MIN && n <= INT_MAX;
	}
	return false;
}

int HiValue::GetInt() const
{
	return IsInt() ? (int)GetInt64() : 0;
}

bool IsTrue(const HiValue& a)
{
	if(a.IsNumber())
		return a.GetNumber();
	return a.GetCount();
}

}
