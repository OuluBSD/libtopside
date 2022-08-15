topic "class Messenger : public Audio";
[ $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[{_}%EN-US 
[s1;:AudioCore`:`:Messenger`:`:class:%- [@(0.0.255) class]_[* Messenger]_:_[@(0.0.255) publi
c]_[*@3 Audio]&]
[s2; input control message parser.&]
[s2; &]
[s2;     This class reads and parses control messages from a variety 
of&]
[s2;     sources, such as a scorefile, MIDI port, socket connection, 
or&]
[s2;     stdin.  MIDI messages are retrieved using the RtMidi class. 
 All&]
[s2;     other input sources (scorefile, socket, or stdin) are assumed 
to&]
[s2;     provide SKINI formatted messages.  This class can be compiled 
with&]
[s2;     generic, non`-realtime support, in which case only scorefile&]
[s2;     reading is possible.&]
[s2; &]
[s2;     The various `\e realtime message acquisition mechanisms 
(from MIDI,&]
[s2;     socket, or stdin) take place asynchronously, filling the 
message&]
[s2;     queue.  A call to popMessage() will pop the next available 
control&]
[s2;     message from the queue and return it via the referenced 
Message&]
[s2;     structure.  When a `\e non`-realtime scorefile is Set, it 
is not&]
[s2;     possible to start reading realtime input messages (from 
MIDI,&]
[s2;     socket, or stdin).  Likewise, it is not possible to read 
from a&]
[s2;     scorefile when a realtime input mechanism is running.&]
[s2; &]
[s2;     When MIDI input is started, input is also automatically 
read from&]
[s2;     stdin.  This allows for program termination via the terminal&]
[s2;     window.  An `_`_SK`_Exit`_ message is pushed onto the stack 
whenever&]
[s2;     an `"exit`" or `"Exit`" message is received from stdin or 
when all&]
[s2;     socket connections close and no stdin thread is running.&]
[s2; &]
[s2;     This class is primarily for use in AUDIO example programs 
but it is&]
[s2;     generic enough to work in many other contexts.&]
[s3;%- &]
[s0; ]]