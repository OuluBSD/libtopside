#ifndef _Net_Loops_h_
#define _Net_Loops_h_


LOOP2(TestCenterNetOrderSrc, Customer, NetCustomerHandler)
LOOP3(TestNetCenterAudioSink, Customer, DefNetCenterAudioSink, DefAudioHardwareSink)
LOOP3(TestNetAudioSrc, NetCustomer, DefCenterNetMidiSink, DefNetCenterAudioSink)


#endif
