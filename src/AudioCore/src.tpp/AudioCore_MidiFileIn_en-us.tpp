topic "class MidiFileIn : public Audio";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:MidiFileIn`:`:class:%- [@(0.0.255) class]_[* MidiFileIn]_:_[@(0.0.255) pub
lic]_[*@3 Audio]&]
[s2; A standard MIDI file reading/parsing class.&]
[s2; &]
[s2;     This class can be used to read events from a standard MIDI 
file.&]
[s2;     Event bytes are copied to a C`+`+ vector and must be subsequently&]
[s2;     interpreted by the user.  The function GetNextMidiEvent() 
skips&]
[s2;     meta and sysex events, returning only MIDI channel messages.&]
[s2;     Event delta`-times are returned in the form of `"ticks`" 
and a&]
[s2;     function is provided to determine the current `"seconds 
per tick`".&]
[s2;     Tempo changes are internally tracked by the class and reflected 
in&]
[s2;     the values returned by the function GetTickSeconds().&]
[s3;%- &]
[s0; ]]