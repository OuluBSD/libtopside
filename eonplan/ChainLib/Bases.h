#ifndef _ChainLib_Bases_h_
#define _ChainLib_Bases_h_


BASE2(ReceiptOrder,				CenterReceipt,	CenterOrder)
BASE2(OrderAudio,				CenterOrder,	CenterAudio)
BASE2(AudioReceipt,				CenterAudio,	CenterReceipt)
BASE3(OrderAudioWithAccel,		CenterOrder,	SinkAccelAudio,		CenterAudio)
BASE3(AudioReceiptWithAccel,	CenterAudio,	SrcAccelAudio,		CenterReceipt)
BASE3(CenterAccelOrderSide,		CenterOrder,	SrcAccelOrder,		CenterReceipt)



#endif
