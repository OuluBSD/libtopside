topic "class Guitar : public Audio";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:Guitar`:`:class:%- [@(0.0.255) class]_[* Guitar]_:_[@(0.0.255) public]_[*@3 A
udio]&]
[s2; guitar model class.&]
[s2; &]
[s2;     This class implements a guitar model with an arbitrary number 
of&]
[s2;     strings (specified during instantiation).  Each string is&]
[s2;     represented by an Audio`::Twang object.  The model supports 
commuted&]
[s2;     synthesis, as discussed by Smith and Karjalainen.  It also 
includes&]
[s2;     a basic body coupling model and supports feedback.&]
[s2; &]
[s2;     This class does not attempt voice management.  Rather, most&]
[s2;     functions support a parameter to specify a particular string&]
[s2;     number and string (voice) management is assumed to occur&]
[s2;     externally.  Note that this class does not inherit from&]
[s2;     Audio`::Instrument because of API inconsistencies.&]
[s2; &]
[s2;     This is a digital waveguide model, making its use possibly 
subject&]
[s2;     to patents held by Stanford University, Yamaha, and others.&]
[s2; &]
[s2;     Control Change Numbers: &]
[s2;        `- Bridge Coupling Gain `= 2&]
[s2;        `- Pluck Position `= 4&]
[s2;        `- Loop Gain `= 11&]
[s2;        `- Coupling Filter Pole `= 1&]
[s2;        `- Pick Filter Pole `= 128&]
[s3;%- &]
[s0; ]]