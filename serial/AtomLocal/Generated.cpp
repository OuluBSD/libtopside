#include "AtomLocal.h"

namespace TS {

namespace Serial {

AtomTypeCls CustomerAtom::GetAtomType()
{
	return ATOM0(CUSTOMER_ATOM, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
}

void CustomerAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls CustomerAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSrc::GetAtomType()
{
	return ATOM0(TEST_REALTIME_SRC, SOURCE, CENTER, ORDER, CENTER, AUDIO);
}

void TestRealtimeSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls TestRealtimeSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSink::GetAtomType()
{
	return ATOM0(TEST_REALTIME_SINK, SINK, CENTER, AUDIO, CENTER, RECEIPT);
}

void TestRealtimeSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls TestRealtimeSink::GetType() const
{
	return GetAtomType();
}

}

}

