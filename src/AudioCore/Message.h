#ifndef _MIDIMESSAGE_H_INCLUDED
#define _MIDIMESSAGE_H_INCLUDED

NAMESPACE_MIDI_BEGIN
using namespace UPP;

enum {
	MIDIMETA_SEQNUM		= 0x00, // 2 bytes.		Sequence number. The number of a sequence. At delta time 0
	MIDIMETA_TEXT		= 0x01, // variable		Some text	Anywhere
	MIDIMETA_COPYRIGHT	= 0x02, // variable		A copyright notice	At delta time 0 in the first track
	MIDIMETA_TRACKNAME	= 0x03, // variable		A track name	At delta time 0
	MIDIMETA_INSTRNAME	= 0x04, // variable		The name of an instrument in the current track	Anywhere
	MIDIMETA_LYRICS		= 0x05, // variable		Lyrics, usually a syllable per quarter note	Anywhere
	MIDIMETA_MARKER		= 0x06, // variable		The text of a marker	Anywhere
	MIDIMETA_CUEPOINT	= 0x07, // variable		The text of a cue, usually to prompt for some action from the user	Anywhere
	MIDIMETA_CHPREFIX	= 0x20, // 1 byte		A channel number (following meta events will apply to this channel)		Anywhere
	MIDIMETA_TRACKEND	= 0x2F, // 0			At the end of each track
	MIDIMETA_TEMPO		= 0x51, // 3			The number of microseconds per beat		Anywhere, but usually in the first track
	MIDIMETA_SMPTE		= 0x54, // 5			SMPTE time to denote playback offset from the beginning		Anywhere
	MIDIMETA_TIMESIG	= 0x58, // 4			Time signature, metronome clicks, and size of a beat in 32nd notes	Anywhere
	MIDIMETA_KEYSIG		= 0x59, // 2			A key signature		Anywhere
	MIDIMETA_CUSTOM		= 0x7F,
};

#define MIDICTRL_LIST \
	MIDICTRL_ITEM(0 ,	00000000 ,	00 ,	Bank Select ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(1 ,	00000001 ,	01 ,	Modulation Wheel or Lever ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(2 ,	00000010 ,	02 ,	Breath Controller ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(3 ,	00000011 ,	03 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(4 ,	00000100 ,	04 ,	Foot Controller ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(5 ,	00000101 ,	05 ,	Portamento Time ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(6 ,	00000110 ,	06 ,	Data Entry MSB ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(7 ,	00000111 ,	07 ,	Channel Volume (formerly Main Volume) ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(8 ,	00001000 ,	08 ,	Balance ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(9 ,	00001001 ,	09 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(10 ,	00001010 ,	0A ,	Pan ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(11 ,	00001011 ,	0B ,	Expression Controller ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(12 ,	00001100 ,	0C ,	Effect Control 1 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(13 ,	00001101 ,	0D ,	Effect Control 2 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(14 ,	00001110 ,	0E ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(15 ,	00001111 ,	0F ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(16 ,	00010000 ,	10 ,	General Purpose Controller 1 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(17 ,	00010001 ,	11 ,	General Purpose Controller 2 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(18 ,	00010010 ,	12 ,	General Purpose Controller 3 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(19 ,	00010011 ,	13 ,	General Purpose Controller 4 ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(20 ,	00010100 ,	14 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(21 ,	00010101 ,	15 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(22 ,	00010110 ,	16 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(23 ,	00010111 ,	17 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(24 ,	00011000 ,	18 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(25 ,	00011001 ,	19 ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(26 ,	00011010 ,	1A ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(27 ,	00011011 ,	1B ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(28 ,	00011100 ,	1C ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(29 ,	00011101 ,	1D ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(30 ,	00011110 ,	1E ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(31 ,	00011111 ,	1F ,	Undefined ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(32 ,	00100000 ,	20 ,	LSB for Control 0 (Bank Select) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(33 ,	00100001 ,	21 ,	LSB for Control 1 (Modulation Wheel or Lever) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(34 ,	00100010 ,	22 ,	LSB for Control 2 (Breath Controller) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(35 ,	00100011 ,	23 ,	LSB for Control 3 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(36 ,	00100100 ,	24 ,	LSB for Control 4 (Foot Controller) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(37 ,	00100101 ,	25 ,	LSB for Control 5 (Portamento Time) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(38 ,	00100110 ,	26 ,	LSB for Control 6 (Data Entry) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(39 ,	00100111 ,	27 ,	LSB for Control 7 (Channel Volume, formerly Main Volume) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(40 ,	00101000 ,	28 ,	LSB for Control 8 (Balance) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(41 ,	00101001 ,	29 ,	LSB for Control 9 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(42 ,	00101010 ,	2A ,	LSB for Control 10 (Pan) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(43 ,	00101011 ,	2B ,	LSB for Control 11 (Expression Controller) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(44 ,	00101100 ,	2C ,	LSB for Control 12 (Effect control 1) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(45 ,	00101101 ,	2D ,	LSB for Control 13 (Effect control 2) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(46 ,	00101110 ,	2E ,	LSB for Control 14 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(47 ,	00101111 ,	2F ,	LSB for Control 15 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(48 ,	00110000 ,	30 ,	LSB for Control 16 (General Purpose Controller 1) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(49 ,	00110001 ,	31 ,	LSB for Control 17 (General Purpose Controller 2) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(50 ,	00110010 ,	32 ,	LSB for Control 18 (General Purpose Controller 3) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(51 ,	00110011 ,	33 ,	LSB for Control 19 (General Purpose Controller 4) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(52 ,	00110100 ,	34 ,	LSB for Control 20 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(53 ,	00110101 ,	35 ,	LSB for Control 21 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(54 ,	00110110 ,	36 ,	LSB for Control 22 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(55 ,	00110111 ,	37 ,	LSB for Control 23 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(56 ,	00111000 ,	38 ,	LSB for Control 24 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(57 ,	00111001 ,	39 ,	LSB for Control 25 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(58 ,	00111010 ,	3A ,	LSB for Control 26 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(59 ,	00111011 ,	3B ,	LSB for Control 27 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(60 ,	00111100 ,	3C ,	LSB for Control 28 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(61 ,	00111101 ,	3D ,	LSB for Control 29 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(62 ,	00111110 ,	3E ,	LSB for Control 30 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(63 ,	00111111 ,	3F ,	LSB for Control 31 (Undefined) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(64 ,	01000000 ,	40 ,	Damper Pedal on/off (Sustain) ,	<=63 off & >=64 on ,	---) \
	MIDICTRL_ITEM(65 ,	01000001 ,	41 ,	Portamento On/Off ,	<=63 off & >=64 on ,	---) \
	MIDICTRL_ITEM(66 ,	01000010 ,	42 ,	Sostenuto On/Off ,	<=63 off & >=64 on ,	---) \
	MIDICTRL_ITEM(67 ,	01000011 ,	43 ,	Soft Pedal On/Off ,	<=63 off & >=64 on ,	---) \
	MIDICTRL_ITEM(68 ,	01000100 ,	44 ,	Legato Footswitch ,	<=63 Normal & >=64 Legato ,	---) \
	MIDICTRL_ITEM(69 ,	01000101 ,	45 ,	Hold 2 ,	<=63 off & >=64 on ,	---) \
	MIDICTRL_ITEM(70 ,	01000110 ,	46 ,	Sound Controller 1 (default: Sound Variation) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(71 ,	01000111 ,	47 ,	Sound Controller 2 (default: Timbre/Harmonic Intens.) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(72 ,	01001000 ,	48 ,	Sound Controller 3 (default: Release Time) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(73 ,	01001001 ,	49 ,	Sound Controller 4 (default: Attack Time) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(74 ,	01001010 ,	4A ,	Sound Controller 5 (default: Brightness) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(75 ,	01001011 ,	4B ,	Sound Controller 6 (default: Decay Time - see MMA RP-021) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(76 ,	01001100 ,	4C ,	Sound Controller 7 (default: Vibrato Rate - see MMA RP-021) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(77 ,	01001101 ,	4D ,	Sound Controller 8 (default: Vibrato Depth - see MMA RP-021) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(78 ,	01001110 ,	4E ,	Sound Controller 9 (default: Vibrato Delay - see MMA RP-021) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(79 ,	01001111 ,	4F ,	Sound Controller 10 (default undefined - see MMA RP-021) ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(80 ,	01010000 ,	50 ,	General Purpose Controller 5 ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(81 ,	01010001 ,	51 ,	General Purpose Controller 6 ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(82 ,	01010010 ,	52 ,	General Purpose Controller 7 ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(83 ,	01010011 ,	53 ,	General Purpose Controller 8 ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(84 ,	01010100 ,	54 ,	Portamento Control ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(85 ,	01010101 ,	55 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(86 ,	01010110 ,	56 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(87 ,	01010111 ,	57 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(88 ,	01011000 ,	58 ,	High Resolution Velocity Prefix ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(89 ,	01011001 ,	59 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(90 ,	01011010 ,	5A ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(91 ,	01011011 ,	5B ,	Effects 1 Depth, 0, 0) \
	MIDICTRL_ITEM(92 ,	01011100 ,	5C ,	Effects 2 Depth (formerly Tremolo Depth) ,	0-127 ,	---) \
	MIDICTRL_ITEM(93 ,	01011101 ,	5D ,	Effects 3 Depth, 0, 0) \
	MIDICTRL_ITEM(94 ,	01011110 ,	5E ,	Effects 4 Depth (formerly Celeste [Detune] Depth) ,	0-127 ,	---) \
	MIDICTRL_ITEM(95 ,	01011111 ,	5F ,	Effects 5 Depth (formerly Phaser Depth) ,	0-127 ,	---) \
	MIDICTRL_ITEM(96 ,	01100000 ,	60 ,	Data Increment (Data Entry +1) (see MMA RP-018) ,	N/A ,	---) \
	MIDICTRL_ITEM(97 ,	01100001 ,	61 ,	Data Decrement (Data Entry -1) (see MMA RP-018) ,	N/A ,	---) \
	MIDICTRL_ITEM(98 ,	01100010 ,	62 ,	Non-Registered Parameter Number (NRPN) - LSB ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(99 ,	01100011 ,	63 ,	Non-Registered Parameter Number (NRPN) - MSB ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(100 ,	01100100 ,	64 ,	Registered Parameter Number (RPN) - LSB* ,	0-127 ,	LSB) \
	MIDICTRL_ITEM(101 ,	01100101 ,	65 ,	Registered Parameter Number (RPN) - MSB* ,	0-127 ,	MSB) \
	MIDICTRL_ITEM(102 ,	01100110 ,	66 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(103 ,	01100111 ,	67 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(104 ,	01101000 ,	68 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(105 ,	01101001 ,	69 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(106 ,	01101010 ,	6A ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(107 ,	01101011 ,	6B ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(108 ,	01101100 ,	6C ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(109 ,	01101101 ,	6D ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(110 ,	01101110 ,	6E ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(111 ,	01101111 ,	6F ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(112 ,	01110000 ,	70 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(113 ,	01110001 ,	71 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(114 ,	01110010 ,	72 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(115 ,	01110011 ,	73 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(116 ,	01110100 ,	74 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(117 ,	01110101 ,	75 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(118 ,	01110110 ,	76 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(119 ,	01110111 ,	77 ,	Undefined ,	--- ,	---) \
	MIDICTRL_ITEM(120 ,	01111000 ,	78 ,	[Channel Mode Message] All Sound Off ,	0 ,	---) \
	MIDICTRL_ITEM(121 ,	01111001 ,	79 ,	[Channel Mode Message] Reset All Controllers, 0, 0) \
	MIDICTRL_ITEM(122 ,	01111010 ,	7A ,	[Channel Mode Message] Local Control On/Off ,	0 off & 127 on ,	---) \
	MIDICTRL_ITEM(123 ,	01111011 ,	7B ,	[Channel Mode Message] All Notes Off ,	0 ,	---) \
	MIDICTRL_ITEM(124 ,	01111100 ,	7C ,	[Channel Mode Message] Omni Mode Off (+ all notes off) ,	0 ,	---) \
	MIDICTRL_ITEM(125 ,	01111101 ,	7D ,	[Channel Mode Message] Omni Mode On (+ all notes off) ,	0 ,	---) \
	MIDICTRL_ITEM(126 ,	01111110 ,	7E ,	[Channel Mode Message] Mono Mode On (+ poly off & + all notes off), 0, 0) \
	MIDICTRL_ITEM(127 ,	01111111 ,	7F ,	[Channel Mode Message] Poly Mode On (+ mono off & +all notes off), 0, 0)

String GetEventCtrlString(int ctrl_num);

class Message : public Vector<uint8> {

public:
	typedef Vector<uint8> MsgVec;
	
	Message();
	Message(int command);
	Message(int command, int p1);
	Message(int command, int p1, int p2);
	Message(const Message& message);
	Message(const Vector<uint8>& message);
	Message(const Vector<char>& message);
	Message(const Vector<int>& message);
	
	~Message();
	
	Message&   operator= (const Message& message);
	//Message&   operator= (const MsgVec& bytes);
	Message&   operator= (const Vector<uint8>& bytes);
	Message&   operator= (const Vector<char>& bytes);
	Message&   operator= (const Vector<int>& bytes);
	void           SetSize(int asize);
	int            GetCount() const;
	int            SetSizeToCommand();
	int            ResizeToCommand();
	
	int            GetTempoMicro() const;
	int            GetTempoMicroseconds() const;
	float         GetTempoSeconds() const;
	float         GetTempoBPM() const;
	float         GetTempoTPS(int tpq) const;
	float         GetTempoSPT(int tpq) const;
	
	int            IsMetaMessage() const;
	int            IsMeta() const;
	int            IsNoteOff() const;
	int            IsNoteOn() const;
	int            IsNote() const;
	int            IsAftertouch() const;
	int            IsController() const;
	int            IsTimbre() const;
	int            IsPatchChange() const;
	int            IsPressure() const;
	int            IsPitchbend() const;
	
	int            GetP0() const;
	int            GetP1() const;
	int            GetP2() const;
	int            GetP3() const;
	int            GetKeyNumber() const;
	int            GetVelocity() const;
	
	void           SetP0(int value);
	void           SetP1(int value);
	void           SetP2(int value);
	void           SetP3(int value);
	void           SetKeyNumber(int value);
	void           SetVelocity(int value);
	
	int            GetCommandNibble() const;
	int            GetCommandByte() const;
	int            GetChannelNibble() const;
	int            GetChannel() const;
	
	void           SetCommandByte(int value);
	void           SetCommand(int value);
	void           SetCommand(int value, int p1);
	void           SetCommand(int value, int p1, int p2);
	void           SetCommandNibble(int value);
	void           SetChannelNibble(int value);
	void           SetChannel(int value);
	void           SetParameters(int p1, int p2);
	void           SetParameters(int p1);
	//void           SetMessage(const MsgVec& message);
	void           SetMessage(const Vector<uint8>& message);
	void           SetMessage(const Vector<char>& message);
	void           SetMessage(const Vector<int>& message);
	
	void           SetSpelling(int base7, int accidental);
	void           GetSpelling(int& base7, int& accidental);
	
	// helper functions to create various Messages
	void           MakeNoteOn(int channel, int key, int velocity);
	void           MakeNoteOff(int channel, int key, int velocity);
	void           MakeNoteOff(int channel, int key);
	void           MakeNoteOff();
	void           MakeController(int channel, int num, int value);
	void           MakePatchChange(int channel, int patchnum);
	void           MakeTimbre(int channel, int patchnum);
	
	// meta-message creation helper functions:
	void           MakeMetaMessage(int mnum, String data);
	void           MakeTrackName(String name);
	void           MakeInstrumentName(String name);
	void           MakeLyric(String text);
	void           MakeMarker(String text);
	void           MakeCue(String text);
	void           MakeCopyright(String text);
	void           MakeTempo(float tempo) {SetTempo(tempo);}
	void           MakeTimeSignature(int top, int bottom, int clocks_per_click = 24, int num32dsPerQuarter = 8);
	        
	// meta-message related functions:
	int            GetMettype() const;
	int            IsTempo() const;
	void           SetTempo(float tempo);
	void           SetTempoMicroseconds(int microseconds);
	void           SetMetaTempo(float tempo);
	int            IsEndOfTrack() const;
	
};

NAMESPACE_MIDI_END

#endif
