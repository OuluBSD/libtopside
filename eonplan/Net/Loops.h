#ifndef _Net_Loops_h_
#define _Net_Loops_h_


LOOP2(TestCenterNetOrderSrc, Customer, NetCustomerHandler)
LOOP3(TestNetCenterAudioSink, Customer, NetCenterAudioSink, AudioSideSink)
LOOP3(TestNetAudioSrc, NetCustomer, CenterNetMidiSink, NetCenterAudioSink)


#endif
