topic "class Iir : public Filter";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:Iir`:`:class:%- [@(0.0.255) class]_[* Iir]_:_[@(0.0.255) public]_[*@3 Filter
]&]
[s2; general infinite impulse response filter class.&]
[s2; &]
[s2;     This class provides a generic digital filter structure that 
can be&]
[s2;     used to implement IIR filters.  For filters containing only&]
[s2;     feedforward terms, the Fir class is slightly more efficient.&]
[s2; &]
[s2;     In particular, this class implements the standard difference&]
[s2;     equation:&]
[s2; &]
[s2;     a`[0`]`*y`[n`] `= b`[0`]`*x`[n`] `+ ... `+ b`[nb`]`*x`[n`-nb`] 
`-&]
[s2;                 a`[1`]`*y`[n`-1`] `- ... `- a`[na`]`*y`[n`-na`]&]
[s2; &]
[s2;     If a`[0`] is not equal to 1, the filter coeffcients are 
normalized&]
[s2;     by a`[0`].&]
[s2; &]
[s2;     The `\e gain parameter is applied at the filter input and 
does not&]
[s2;     affect the coefficient values.  The default gain value is 
1.0.&]
[s2;     This structure results in one extra multiply per computed 
sample,&]
[s2;     but allows easy control of the overall filter gain.&]
[s3;%- &]
[s0; ]]