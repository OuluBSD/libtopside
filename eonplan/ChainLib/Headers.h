
HEADER2(CustomerAtom,		AtomReceiptSink,	customer,	CenterReceipt,	CenterOrder)
HEADER2(TestRealtimeSrc,	CenterSourceAsync,	source,		CenterOrder,	CenterAudio)
HEADER2(TestRealtimeSink,	CenterSinkSync,		sink,		CenterAudio,	CenterReceipt)

HEADER_ACTION(CustomerAtom,		customer.test.single)
HEADER_ACTION(TestRealtimeSrc,	center.audio.src.test)
HEADER_ACTION(TestRealtimeSink,	center.audio.sink.test.realtime)


//HEADER(AccelCustomer,		AccelReceiptOrder)
//HEADER(NetCustomer,		NetReceiptOrder)