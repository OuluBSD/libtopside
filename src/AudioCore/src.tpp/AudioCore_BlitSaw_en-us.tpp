topic "class BlitSaw : public Generator";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:codeitem]
[{_}%EN-US 
[s1;:AudioCore`:`:BlitSaw`:`:class:%- [@(0.0.255) class]_[* BlitSaw]_:_[@(0.0.255) public]_[*@3 G
enerator]&]
[s2; Band`-limited sawtooth wave class.&]
[s2; &]
[s2;     This class generates a band`-limited sawtooth waveform using 
a&]
[s2;     closed`-form algorithm reported by Stilson and Smith in 
`"Alias`-Free&]
[s2;     Digital Synthesis of Classic Analog Waveforms`", 1996.  
The user&]
[s2;     can specify both the fundamental frequency of the sawtooth 
and the&]
[s2;     number of harmonics contained in the resulting signal.&]
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
[s4;%- &]
[s5;:AudioCore`:`:BlitSaw`:`:Tick`(`):%- [_^AudioCore`:`:AudioFloat^ AudioFloat]_[* Tick](
)&]
[s2;   The code below implements the BLIT algorithm of Stilson and&]
[s2;   Smith, followed by a summation and filtering operation to 
produce&]
[s2;   a sawtooth waveform.  After experimenting with various approaches&]
[s2;   to calculate the average value of the BLIT over one period, 
I&]
[s2;   found that an estimate of C2`_ `= 1.0 / period (in samples) 
worked&]
[s2;   most consistently.  A `"leaky integrator`" is then applied 
to the&]
[s2;   difference of the BLIT output and C2`_. (GPS `- 1 October 
2005)&]
[s2; &]
[s2;   A fully  optimized version of this code would replace the 
two sin &]
[s2;   calls with a pair of fast sin oscillators, for which stable 
fast &]
[s2;   two`-multiply algorithms are well known. In the spirit of 
AUDIO,&]
[s2;   which favors clarity over performance, the optimization has 
&]
[s2;   not been made here.&]
[s2; &]
[s2;   Avoid a divide by zero, or use of a denormalized divisor &]
[s2;   at the sinc peak, which has a limiting value of m`_ / p`_.&]
[s3;%- &]
[s0; ]]