topic "class Voicer : public Audio, private Moveable<Voicer> ";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:Voicer`:`:class:%- [@(0.0.255) class]_[* Voicer]_:_[@(0.0.255) public]_[*@3 A
udio], [@(0.0.255) private]_[*@3 Moveable]<[* Voicer]>_&]
[s2; voice manager class.&]
[s2; &]
[s2;     This class can be used to manage a group of AUDIO instrument&]
[s2;     classes.  Individual voices can be controlled via unique 
note&]
[s2;     tags.  Instrument groups can be controlled by group number.&]
[s2; &]
[s2;     A previously constructed AUDIO instrument class is linked 
with a&]
[s2;     voice manager using the addInstrument() function.  An optional&]
[s2;     group number argument can be specified to the addInstrument()&]
[s2;     function as well (default group `= 0).  The voice manager 
does not&]
[s2;     delete any instrument instances ... it is the responsibility 
of&]
[s2;     the user to allocate and deallocate all instruments.&]
[s2; &]
[s2;     The Tick() function returns the mix of all sounding voices. 
 Each&]
[s2;     noteOn returns a unique tag (credits to the NeXT MusicKit), 
so you&]
[s2;     can send control changes to specific voices within an ensemble.&]
[s2;     Alternately, control changes can be sent to all voices in 
a given&]
[s2;     group.&]
[s3;%- &]
[s0; ]]