#ifndef _Net_Loops_h_
#define _Net_Loops_h_

NAMESPACE_PLAN_BEGIN


LOOP2(TestCenterNetOrderSrc, Customer, NetCustomerHandler)
LOOP3(TestNetCenterAudioSink, Customer, DefNetCenterAudioSink, DefAudioHardwareSink)
LOOP3(TestNetAudioSrc, NetCustomer, DefCenterNetMidiSink, DefNetCenterAudioSink)


NAMESPACE_PLAN_END

#endif
