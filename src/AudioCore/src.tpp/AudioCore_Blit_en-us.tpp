topic "class Blit : public Generator";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:Blit`:`:class:%- [@(0.0.255) class]_[* Blit]_:_[@(0.0.255) public]_[*@3 Gene
rator]&]
[s2; Band`-limited impulse train class.&]
[s2; &]
[s2;     This class generates a band`-limited impulse train using 
a&]
[s2;     closed`-form algorithm reported by Stilson and Smith in 
`"Alias`-Free&]
[s2;     Digital Synthesis of Classic Analog Waveforms`", 1996.  
The user&]
[s2;     can specify both the fundamental frequency of the impulse 
train&]
[s2;     and the number of harmonics contained in the resulting signal.&]
[s2; &]
[s2;     The signal is normalized so that the peak value is `+/`-1.0.&]
[s2; &]
[s2;     If nHarmonics is 0, then the signal will contain all harmonics 
up&]
[s2;     to half the sample rate.  Note, however, that this Setting 
may&]
[s2;     produce aliasing in the signal when the frequency is changing 
(no&]
[s2;     automatic modification of the number of harmonics is performed 
by&]
[s2;     the SetFrequency() function).&]
[s2; &]
[s3;%- &]
[s0; ]]