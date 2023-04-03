topic "class DelayL : public Filter";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:DelayL`:`:class:%- [@(0.0.255) class]_[* DelayL]_:_[@(0.0.255) public]_[*@3 F
ilter]&]
[s2; linear interpolating delay line class.&]
[s2; &]
[s2;     This class implements a fractional`-GetCount digital delay`-line 
using&]
[s2;     first`-order linear interpolation.  If the delay and maximum 
GetCount&]
[s2;     are not specified during instantiation, a fixed maximum 
GetCount of&]
[s2;     4095 and a delay of zero is Set.&]
[s2; &]
[s2;     Linear interpolation is an efficient technique for achieving&]
[s2;     fractional delay GetCounts, though it does introduce high`-frequency&]
[s2;     signal attenuation to varying degrees depending on the fractional&]
[s2;     delay Setting.  The use of higher order Lagrange interpolators 
can&]
[s2;     typically improve (minimize) this attenuation characteristic.&]
[s2; &]
[s3;%- &]
[s0; ]]