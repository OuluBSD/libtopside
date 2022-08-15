topic "class FileLoop : protected FileWvIn";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:FileLoop`:`:class:%- [@(0.0.255) class]_[* FileLoop]_:_[@(0.0.255) protect
ed]_[*@3 FileWvIn]&]
[s2; file looping / oscillator class.&]
[s2; &]
[s2;     This class provides audio file looping functionality.  Any 
audio&]
[s2;     file that can be loaded by FileRead can be looped using 
this&]
[s2;     class.&]
[s2; &]
[s2;     FileLoop supports multi`-channel data.  It is important 
to&]
[s2;     distinguish the Tick() method that computes a single frame 
(and&]
[s2;     returns only the specified sample of a multi`-channel frame) 
from&]
[s2;     the overloaded one that takes an AudioFrames object for&]
[s2;     multi`-channel and/or multi`-frame data.&]
[s3;%- &]
[s0; ]]