#include "MidiFile.h"


NAMESPACE_MIDI_BEGIN

String GetEventCtrlString(int ctrl_num) {
	// MIDICTRL_ITEM(83 ,	01010011 ,	53 ,	General Purpose Controller 8 ,	0-127 ,	LSB)
#define MIDICTRL_ITEM(dec, bin, hex, name, arg0, used_as) if (ctrl_num == dec) return #name;
	MIDICTRL_LIST
#undef MIDICTRL_ITEM
	return "<invalid>";
}

//////////////////////////////
//
// Message::Message -- Constructor.
//

Message::Message() {
	// do nothing
}


Message::Message(int command) {
	this->SetCount(1);
	(*this)[0] = (uint8)command;
}


Message::Message(int command, int p1) {
	this->SetCount(2);
	(*this)[0] = (uint8)command;
	(*this)[1] = (uint8)p1;
}


Message::Message(int command, int p1, int p2) {
	this->SetCount(3);
	(*this)[0] = (uint8)command;
	(*this)[1] = (uint8)p1;
	(*this)[2] = (uint8)p2;
}


Message::Message(const Message& message) {
	(*this) = message;
}


Message::Message(const Vector<uint8>& message) {
	SetMessage(message);
}


Message::Message(const Vector<char>& message) {
	SetMessage(message);
}


Message::Message(const Vector<int>& message) {
	SetMessage(message);
}



//////////////////////////////
//
// Message::~Message -- Deconstructor.
//

Message::~Message() {
	SetCount(0);
}



//////////////////////////////
//
// Message::operator= --
//

Message& Message::operator=(const Message & message) {
	/*if (this == &message) {
		return *this;
	}*/
	
	SetMessage(message);
	
	return *this;
}


/*Message& Message::operator=(const MsgVec& bytes) {
	SetMessage(bytes);
	return *this;
}*/

Message& Message::operator=(const Vector<uint8>& bytes) {
	/*if (this == &bytes) {
		return *this;
	}*/
	
	SetMessage(bytes);
	
	return *this;
}

Message& Message::operator=(const Vector<char>& bytes) {
	SetMessage(bytes);
	return *this;
}


Message& Message::operator=(const Vector<int>& bytes) {
	SetMessage(bytes);
	return *this;
}



//////////////////////////////
//
// Message::SetSize -- Change the size of the message byte list.
//

void Message::SetSize(int asize) {
	MsgVec::SetCount(asize);
}



//////////////////////////////
//
// Message::getSize -- Return the size of the MIDI message bytes.
//

int Message::GetCount() const {
	return MsgVec::GetCount();
}



//////////////////////////////
//
// Message::SetSizeToCommand -- Set the number of parameters if the
//   command byte is set in the range from 0x80 to 0xef.  Any newly
//   added parameter bytes will be set to 0.
//

int Message::SetSizeToCommand() {
	int osize = MsgVec::GetCount();
	
	if (osize < 1) {
		return 0;
	}
	
	int command = GetCommandNibble();
	
	if (command < 0) {
		return 0;
	}
	
	int bytecount = 1;
	
	switch (command) {
	
	case 0x80:
		bytecount = 2;
		break;  // Note Off
		
	case 0x90:
		bytecount = 2;
		break;  // Note On
		
	case 0xA0:
		bytecount = 2;
		break;  // Aftertouch
		
	case 0xB0:
		bytecount = 2;
		break;  // Continuous Controller
		
	case 0xC0:
		bytecount = 1;
		break;  // Patch Change
		
	case 0xD0:
		bytecount = 1;
		break;  // Channel Pressure
		
	case 0xE0:
		bytecount = 2;
		break;  // Pitch Bend
		
	case 0xF0:
	
	default:
		return 0;
	}
	
	if (bytecount + 1 < osize) {
		SetCount(bytecount + 1);
		
		for (int i = osize; i < bytecount + 1; i++) {
			(*this)[i] = 0;
		}
	}
	
	return (int)GetCount();
}


int Message::ResizeToCommand() {
	return SetSizeToCommand();
}



//////////////////////////////
//
// Message::GetTempoMicro -- Returns the number of microseconds per
//      quarter note if the Message is a tempo meta message.
//      Returns -1 if the MIDI message is not a tempo meta message.
//

int Message::GetTempoMicro() const {
	if (!IsTempo()) {
		return -1;
	}
	
	else {
		return ((*this)[3] << 16) + ((*this)[4] << 8) + (*this)[5];
	}
}


int Message::GetTempoMicroseconds() const {
	return GetTempoMicro();
}



//////////////////////////////
//
// Message::GetTempoSeconds -- Returns the number of seconds per
//      quarter note.  Returns -1.0 if the MIDI message is not a
//      tempo meta message.
//

double Message::GetTempoSeconds() const {
	int microseconds = GetTempoMicroseconds();
	
	if (microseconds < 0) {
		return -1.0;
	}
	
	else {
		return (double)microseconds / 1000000.0;
	}
}



//////////////////////////////
//
// Message::GetTempoBPM -- Returns the tempo in terms of beats per minute.
//   Returns -1 if the Message is note a tempo meta message.
//

double Message::GetTempoBPM() const {
	int microseconds = GetTempoMicroseconds();
	
	if (microseconds < 0) {
		return -1.0;
	}
	
	return 60000000.0 / (double)microseconds;
}



//////////////////////////////
//
// Message::GetTempoTPS -- Returns the tempo in terms of ticks per seconds.
//

double Message::GetTempoTPS(int tpq) const {
	int microseconds = GetTempoMicroseconds();
	
	if (microseconds < 0) {
		return -1.0;
	}
	
	else {
		return tpq * 1000000.0 / (double)microseconds;
	}
}



//////////////////////////////
//
// Message::GetTempoSPT -- Returns the tempo in terms of seconds per tick.
//

double Message::GetTempoSPT(int tpq) const {
	int microseconds = GetTempoMicroseconds();
	
	if (microseconds < 0) {
		return -1.0;
	}
	
	else {
		return (double)microseconds / 1000000.0 / tpq;
	}
}



//////////////////////////////
//
// Message::IsMeta -- Returns true if message is a Meta message
//      (when the command byte is 0xff).
//

int Message::IsMeta() const {
	if (GetCount() == 0) {
		return 0;
	}
	
	else if ((*this)[0] != 0xff) {
		return 0;
	}
	
	else if (GetCount() < 3) {
		// meta message is ill-formed.
		// meta messages must have at least three bytes:
		//    0: 0xff == meta message marker
		//    1: meta message type
		//    2: meta message data bytes to follow
		return 0;
	}
	
	else {
		return 1;
	}
}


int Message::IsMetaMessage() const {
	return IsMeta();
}



//////////////////////////////
//
// Message::IsNoteOff -- Returns true if the command nibble is 0x80
//     or if the command nibble is 0x90 with p2=0 velocity.
//

int Message::IsNoteOff() const {
	if (GetCount() != 3) {
		return 0;
	}
	
	else if (((*this)[0] & 0xf0) == 0x80) {
		return 1;
	}
	
	else if ((((*this)[0] & 0xf0) == 0x90) && ((*this)[2] == 0)) {
		return 1;
	}
	
	else {
		return 0;
	}
}



//////////////////////////////
//
// Message::IsNoteOn -- Returns true if the command byte is in the 0x90
//    range and the velocity is non-zero
//

int Message::IsNoteOn() const {
	if (GetCount() != 3) {
		return 0;
	}
	
	else if (((*this)[0] & 0xf0) != 0x90) {
		return 0;
	}
	
	else if ((*this)[2] == 0) {
		return 0;
	}
	
	else {
		return 1;
	}
}



//////////////////////////////
//
// Message::IsNote -- Returns true if either a note-on or a note-off
//     message.
//

int Message::IsNote() const {
	return IsNoteOn() || IsNoteOff();
}



//////////////////////////////
//
// Message::IsAftertouch -- Returns true if the command byte is in the 0xA0
//    range.
//

int Message::IsAftertouch() const {
	if (GetCount() != 3) {
		return 0;
	}
	
	else if (((*this)[0] & 0xf0) != 0xA0) {
		return 0;
	}
	
	else {
		return 1;
	}
}



//////////////////////////////
//
// Message::IsController -- Returns true if the command byte is in the 0xB0
//    range.
//

int Message::IsController() const {
	if (GetCount() != 3) {
		return 0;
	}
	
	else if (((*this)[0] & 0xf0) != 0xB0) {
		return 0;
	}
	
	else {
		return 1;
	}
}



//////////////////////////////
//
// Message::IsTimbre -- Returns true of a patch change message
//    (command nibble 0xc0).
//

int Message::IsTimbre() const {
	if (((*this)[0] & 0xf0) != 0xc0) {
		return 0;
	}
	
	else if (GetCount() != 2) {
		return 0;
	}
	
	else {
		return 1;
	}
}


int Message::IsPatchChange() const {
	return IsTimbre();
}



//////////////////////////////
//
// Message::IsPressure -- Returns true of a channel pressure message
//    (command nibble 0xd0).
//

int Message::IsPressure() const {
	if (((*this)[0] & 0xf0) != 0xd0) {
		return 0;
	}
	
	else if (GetCount() != 2) {
		return 0;
	}
	
	else {
		return 1;
	}
}



//////////////////////////////
//
// Message::IsPitchbend -- Returns true of a pitch-bend message
//    (command nibble 0xe0).
//

int Message::IsPitchbend() const {
	if (((*this)[0] & 0xf0) != 0xe0) {
		return 0;
	}
	
	else if (GetCount() != 3) {
		return 0;
	}
	
	else {
		return 1;
	}
}



///////////////////////////////
//
// Message::GetMettype -- returns the meta-message type for the
//     Message.  If the message is not a meta message, then returns
//     -1.
//

int Message::GetMettype() const {
	if (!IsMetaMessage()) {
		return -1;
	}
	
	else {
		return (int)(*this)[1];
	}
}



//////////////////////////////
//
// Message::IsTempo -- Returns true if message is a meta message
//      describing tempo (meta message type 0x51).
//

int Message::IsTempo() const {
	if (!IsMetaMessage()) {
		return 0;
	}
	
	else if ((*this)[1] != 0x51) {
		return 0;
	}
		
	else if (GetCount() != 6) {
		// Meta tempo message can only be 6 bytes long.
		return 0;
	}
	else {
		return 1;
	}
}



//////////////////////////////
//
// Message::IsEndOfTrack -- Returns true if message is a meta message
//      for end-of-track (meta message type 0x2f).
//

int Message::IsEndOfTrack() const {
	return GetMettype() == 0x2f ? 1 : 0;
}



//////////////////////////////
//
// Message::GetP0 -- Return index 1 byte, or -1 if it doesn't exist.
//

int Message::GetP0() const {
	return GetCount() < 1 ? -1 : (*this)[0];
}



//////////////////////////////
//
// Message::GetP1 -- Return index 1 byte, or -1 if it doesn't exist.
//

int Message::GetP1() const {
	return GetCount() < 2 ? -1 : (*this)[1];
}



//////////////////////////////
//
// Message::GetP2 -- Return index 2 byte, or -1 if it doesn't exist.
//

int Message::GetP2() const {
	return GetCount() < 3 ? -1 : (*this)[2];
}



//////////////////////////////
//
// Message::GetP3 -- Return index 3 byte, or -1 if it doesn't exist.
//

int Message::GetP3() const {
	return GetCount() < 4 ? -1 : (*this)[3];
}



//////////////////////////////
//
// Message::GetKeyNumber -- Return the key number (such as 60 for
//    middle C).  If the message does not have a note parameter, then
//    return -1;  if the key is invalid (above 127 in value), then
//    limit to the range 0 to 127.
//

int Message::GetKeyNumber() const {
	if (IsNote() || IsAftertouch()) {
		int output = GetP1();
		
		if (output < 0) {
			return output;
		}
		
		else {
			return 0xff & output;
		}
	}
	
	else {
		return -1;
	}
}



//////////////////////////////
//
// Message::GetVelocity -- Return the key veolocity.  If the message
//   is not a note-on or a note-off, then return -1.  If the value is
//   out of the range 0-127, then chop off the high-bits.
//

int Message::GetVelocity() const {
	if (IsNote()) {
		int output = GetP2();
		
		if (output < 0) {
			return output;
		}
		
		else {
			return 0xff & output;
		}
	}
	
	else {
		return -1;
	}
}



//////////////////////////////
//
// Message::SetP0 -- Set the command byte.
//   If the Message is too short, add extra spaces to
//   allow for P0.  The value should be in the range from
//   128 to 255, but this function will not babysit you.
//

void Message::SetP0(int value) {
	if (GetCount() < 1) {
		SetCount(1);
	}
	
	(*this)[0] = value;
}



//////////////////////////////
//
// Message::SetP1 -- Set the first parameter value.
//   If the Message is too short, add extra spaces to
//   allow for P1.  The command byte will be undefined if
//   it was added.  The value should be in the range from
//   0 to 127, but this function will not babysit you.
//

void Message::SetP1(int value) {
	if (GetCount() < 2) {
		SetCount(2);
	}
	
	(*this)[1] = value;
}



//////////////////////////////
//
// Message::SetP2 -- Set the second paramter value.
//     If the Message is too short, add extra spaces
//     to allow for P2.  The command byte and/or the P1 value
//     will be undefined if extra space needs to be added and
//     those slots are created.  The value should be in the range
//     from 0 to 127, but this function will not babysit you.
//

void Message::SetP2(int value) {
	if (GetCount() < 3) {
		SetCount(3);
	}
	
	(*this)[2] = value;
}



//////////////////////////////
//
// Message::SetP3 -- Set the third paramter value.
//     If the Message is too short, add extra spaces
//     to allow for P3.  The command byte and/or the P1/P2 values
//     will be undefined if extra space needs to be added and
//     those slots are created.  The value should be in the range
//     from 0 to 127, but this function will not babysit you.
//

void Message::SetP3(int value) {
	if (GetCount() < 4) {
		SetCount(4);
	}
	
	(*this)[3] = value;
}



//////////////////////////////
//
// Message::SetKeyNumber -- Set the note on/off key number (or
//    aftertouch key).  Ignore if not note or aftertouch message.
//    Limits the input value to the range from 0 to 127.
//

void Message::SetKeyNumber(int value) {
	if (IsNote() || IsAftertouch()) {
		SetP1(value & 0xff);
	}
	
	else {
		// don't do anything since this is not a note-related message.
	}
}



//////////////////////////////
//
// Message::SetVelocity -- Set the note on/off velocity; ignore
//   if note a note message.  Limits the input value to the range
//   from 0 to 127.
//

void Message::SetVelocity(int value) {
	if (IsNote()) {
		SetP2(value & 0xff);
	}
	
	else {
		// don't do anything since this is not a note-related message.
	}
}



//////////////////////////////
//
// Message::GetCommandNibble -- Returns the top 4 bits of the (*this)[0]
//    entry, or -1 if there is not (*this)[0].
//

int Message::GetCommandNibble() const {
	if (GetCount() < 1) {
		return -1;
	}
	
	else {
		return (*this)[0] & 0xf0;
	}
}



//////////////////////////////
//
// Message::GetCommandByte -- Return the command byte or -1 if not
//    allocated.
//

int Message::GetCommandByte() const {
	if (GetCount() < 1) {
		return -1;
	}
	
	else {
		return (*this)[0];
	}
}



//////////////////////////////
//
// Message::GetChannelNibble -- Returns the bottom 4 bites of the
//      (*this)[0] entry, or -1 if there is not (*this)[0].  Should be refined
//      to return -1 if the top nibble is 0xf0, since those commands are
//      not channel specific.
//

int Message::GetChannelNibble() const {
	if (GetCount() < 1) {
		return -1;
	}
	
	else {
		return (*this)[0] & 0x0f;
	}
}


int Message::GetChannel() const {
	return GetChannelNibble();
}



//////////////////////////////
//
// Message::SetCommandByte --
//

void Message::SetCommandByte(int value) {
	if (GetCount() < 1) {
		SetCount(1);
	}
	
	else {
		(*this)[0] = (uint8)(value & 0xff);
	}
}

void Message::SetCommand(int value) {
	SetCommandByte(value);
}



//////////////////////////////
//
// Message::SetCommand -- Set the command byte and parameter bytes
//   for a Message.  The size of the message will be adjusted to
//   the number of input parameters.
//

void Message::SetCommand(int value, int p1) {
	this->SetCount(2);
	(*this)[0] = (uint8)value;
	(*this)[1] = (uint8)p1;
}


void Message::SetCommand(int value, int p1, int p2) {
	this->SetCount(3);
	(*this)[0] = (uint8)value;
	(*this)[1] = (uint8)p1;
	(*this)[2] = (uint8)p2;
}



//////////////////////////////
//
// Message::SetCommandNibble --
//

void Message::SetCommandNibble(int value) {
	if (this->GetCount() < 1) {
		this->SetCount(1);
	}
	
	if (value <= 0x0f) {
		(*this)[0] = ((*this)[0] & 0x0f) | ((uint8)((value << 4) & 0xf0));
	}
	
	else {
		(*this)[0] = ((*this)[0] & 0x0f) | ((uint8)(value & 0xf0));
	}
}




//////////////////////////////
//
// Message::SetChannelNibble --
//

void Message::SetChannelNibble(int value) {
	if (this->GetCount() < 1) {
		this->SetCount(1);
	}
	
	(*this)[0] = ((*this)[0] & 0xf0) | ((uint8)(value & 0x0f));
}


void Message::SetChannel(int value) {
	SetChannelNibble(value);
}



//////////////////////////////
//
// Message::SetParameters -- Set the second and optionally the
//     third MIDI byte of a MIDI message.  The command byte will not
//     be altered, and will be set to 0 if it currently does not exist.
//

void Message::SetParameters(int p1) {
	int oldsize = (int)GetCount();
	SetCount(2);
	(*this)[1] = (uint8)p1;
	
	if (oldsize < 1) {
		(*this)[0] = 0;
	}
}


void Message::SetParameters(int p1, int p2) {
	int oldsize = (int)GetCount();
	SetCount(3);
	(*this)[1] = (uint8)p1;
	(*this)[2] = (uint8)p2;
	
	if (oldsize < 1) {
		(*this)[0] = 0;
	}
}


//////////////////////////////
//
// Message::SetMessage --  Set the contents of MIDI bytes to the
//   input list of bytes.
//

/*void Message::SetMessage(const MsgVec& message) {
	this->SetCount(message.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = message[i];
	}
}*/

void Message::SetMessage(const Vector<uint8>& message) {
	this->SetCount(message.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = message[i];
	}
}


void Message::SetMessage(const Vector<char>& message) {
	SetCount(message.GetCount());
	
	for (int i = 0; i < (int)GetCount(); i++) {
		(*this)[i] = (uint8)message[i];
	}
}


void Message::SetMessage(const Vector<int>& message) {
	SetCount(message.GetCount());
	
	for (int i = 0; i < (int)GetCount(); i++) {
		(*this)[i] = (uint8)message[i];
	}
}



//////////////////////////////
//
// Message::SetSpelling -- Encode a Plus accidental state for a note.
//    For example, if a note's key number is 60, the enharmonic pitch name
//    could be any of these possibilities:
//        C, B-sharp, D-double-flat
//    MIDI note 60 is ambiguous as to which of these names are intended,
//    so MIDIPlus allows these mappings to be preserved for later recovery.
//    See Chapter 5 (pp. 99-104) of Beyond MIDI (1997).
//
//    The first parameter is the diatonic pitch number (or pitch class
//    if the octave is set to 0):
//       octave * 7 + 0 = C pitches
//       octave * 7 + 1 = D pitches
//       octave * 7 + 2 = E pitches
//       octave * 7 + 3 = F pitches
//       octave * 7 + 4 = G pitches
//       octave * 7 + 5 = A pitches
//       octave * 7 + 6 = B pitches
//
//    The second parameter is the semitone alteration (accidental).
//    0 = natural state, 1 = sharp, 2 = double sharp, -1 = flat,
//    -2 = double flat.
//
//    Only note-on messages can be processed (other messages will be
//    silently ignored).
//

void Message::SetSpelling(int base7, int accidental) {
	if (!IsNoteOn()) {
		return;
	}
	
	// The bottom two bits of the attack velocity are used for the
	// spelling, so need to make sure the velocity will not accidentally
	// be set to zero (and make the note-on a note-off).
	
	if (GetVelocity() < 4) {
		SetVelocity(4);
	}
	
	int dpc = base7 % 7;
	
	uint8 spelling = 0;
	
	// Table 5.1, page 101 in Beyond MIDI (1997)
	// http://beyondmidi.ccarh.org/beyondmidi-600dpi.pdf
	
	switch (dpc) {
	
	case 0:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Cbb
			
		case - 1:
			spelling = 1;
			break; // Cb
			
		case  0:
			spelling = 2;
			break; // C
			
		case + 1:
			spelling = 2;
			break; // C#
			
		case + 2:
			spelling = 3;
			break; // C##
		}
		
		break;
		
	case 1:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Dbb
			
		case - 1:
			spelling = 1;
			break; // Db
			
		case  0:
			spelling = 2;
			break; // D
			
		case + 1:
			spelling = 3;
			break; // D#
			
		case + 2:
			spelling = 3;
			break; // D##
		}
		
		break;
		
	case 2:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Ebb
			
		case - 1:
			spelling = 2;
			break; // Eb
			
		case  0:
			spelling = 2;
			break; // E
			
		case + 1:
			spelling = 3;
			break; // E#
			
		case + 2:
			spelling = 3;
			break; // E##
		}
		
		break;
		
	case 3:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Fbb
			
		case - 1:
			spelling = 1;
			break; // Fb
			
		case  0:
			spelling = 2;
			break; // F
			
		case + 1:
			spelling = 2;
			break; // F#
			
		case + 2:
			spelling = 3;
			break; // F##
			
		case + 3:
			spelling = 3;
			break; // F###
		}
		
		break;
		
	case 4:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Gbb
			
		case - 1:
			spelling = 1;
			break; // Gb
			
		case  0:
			spelling = 2;
			break; // G
			
		case + 1:
			spelling = 2;
			break; // G#
			
		case + 2:
			spelling = 3;
			break; // G##
		}
		
		break;
		
	case 5:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Abb
			
		case - 1:
			spelling = 1;
			break; // Ab
			
		case  0:
			spelling = 2;
			break; // A
			
		case + 1:
			spelling = 3;
			break; // A#
			
		case + 2:
			spelling = 3;
			break; // A##
		}
		
		break;
		
	case 6:
	
		switch (accidental) {
		
		case - 2:
			spelling = 1;
			break; // Bbb
			
		case - 1:
			spelling = 2;
			break; // Bb
			
		case  0:
			spelling = 2;
			break; // B
			
		case + 1:
			spelling = 3;
			break; // B#
			
		case + 2:
			spelling = 3;
			break; // B##
		}
		
		break;
		
	}
	
	uint8 vel = GetVelocity();
	
	// suppress any previous content in the first two bits:
	vel = vel & 0xFC;
	// insert the spelling code:
	vel = vel | spelling;
	SetVelocity(vel);
}



//////////////////////////////
//
// Message::GetSpelling -- Return the diatonic pitch class and accidental
//    for a note-on's key number.  The MIDI file must be encoded with MIDIPlus
//    pitch spelling codes for this function to return valid data; otherwise,
//    it will return a neutral fixed spelling for each MIDI key.
//
//    The first parameter will be filled in with the base-7 diatonic pitch:
//        pc + octave * 7
//     where pc is the numbers 0 through 6 representing the pitch classes
//     C through B, the octave is MIDI octave (not the scientific pitch
//     octave which is one less than the MIDI ocatave, such as C4 = middle C).
//     The second number is the accidental for the base-7 pitch.
//

void Message::GetSpelling(int& base7, int& accidental) {
	if (!IsNoteOn()) {
		return;
	}
	
	base7 = -123456;
	
	accidental = 123456;
	int base12   = GetKeyNumber();
	int octave   = base12 / 12;
	int base12pc = base12 - octave * 12;
	int base7pc  = 0;
	int spelling = 0x03 & GetVelocity();
	
	// Table 5.1, page 101 in Beyond MIDI (1997)
	// http://beyondmidi.ccarh.org/beyondmidi-600dpi.pdf
	
	switch (base12pc) {
	
	case 0:
	
		switch (spelling) {
		
		case 1:
			base7pc = 1;
			accidental = -2;
			break;  // Dbb
			
		case 0:
		
		case 2:
			base7pc = 0;
			accidental =  0;
			break;  // C
			
		case 3:
			base7pc = 6;
			accidental = + 1;
			octave--;
			break;  // B#
		}
		
		break;
		
	case 1:
	
		switch (spelling) {
		
		case 1:
			base7pc = 1;
			accidental = -1;
			break;  // Db
			
		case 0:
		
		case 2:
			base7pc = 0;
			accidental = + 1;
			break;  // C#
			
		case 3:
			base7pc = 6;
			accidental = + 2;
			octave--;
			break;  // B##
		}
		
		break;
		
	case 2:
	
		switch (spelling) {
		
		case 1:
			base7pc = 2;
			accidental = -2;
			break;  // Ebb
			
		case 0:
		
		case 2:
			base7pc = 1;
			accidental =  0;
			break;  // D
			
		case 3:
			base7pc = 0;
			accidental = + 2;
			break;  // C##
		}
		
		break;
		
	case 3:
	
		switch (spelling) {
		
		case 1:
			base7pc = 3;
			accidental = -2;
			break;  // Fbb
			
		case 0:
		
		case 2:
			base7pc = 2;
			accidental = -1;
			break;  // Eb
			
		case 3:
			base7pc = 1;
			accidental = + 1;
			break;  // D#
		}
		
		break;
		
	case 4:
	
		switch (spelling) {
		
		case 1:
			base7pc = 3;
			accidental = -1;
			break;  // Fb
			
		case 2:
			base7pc = 2;
			accidental =  0;
			break;  // E
			
		case 3:
			base7pc = 1;
			accidental = + 2;
			break;  // D##
		}
		
		break;
		
	case 5:
	
		switch (spelling) {
		
		case 1:
			base7pc = 4;
			accidental = -2;
			break;  // Gbb
			
		case 0:
		
		case 2:
			base7pc = 3;
			accidental =  0;
			break;  // F
			
		case 3:
			base7pc = 2;
			accidental = + 1;
			break;  // E#
		}
		
		break;
		
	case 6:
	
		switch (spelling) {
		
		case 1:
			base7pc = 4;
			accidental = -1;
			break;  // Gb
			
		case 0:
		
		case 2:
			base7pc = 3;
			accidental = + 1;
			break;  // F#
			
		case 3:
			base7pc = 2;
			accidental = + 2;
			break;  // E##
		}
		
		break;
		
	case 7:
	
		switch (spelling) {
		
		case 1:
			base7pc = 5;
			accidental = -2;
			break;  // Abb
			
		case 0:
		
		case 2:
			base7pc = 4;
			accidental =  0;
			break;  // G
			
		case 3:
			base7pc = 3;
			accidental = + 2;
			break;  // F##
		}
		
		break;
		
	case 8:
	
		switch (spelling) {
		
		case 1:
			base7pc = 5;
			accidental = -1;
			break;  // Ab
			
		case 0:
		
		case 2:
			base7pc = 4;
			accidental = + 1;
			break;  // G#
			
		case 3:
			base7pc = 3;
			accidental = + 3;
			break;  // F###
		}
		
		break;
		
	case 9:
	
		switch (spelling) {
		
		case 1:
			base7pc = 6;
			accidental = -2;
			break;  // Bbb
			
		case 0:
		
		case 2:
			base7pc = 5;
			accidental =  0;
			break;  // A
			
		case 3:
			base7pc = 4;
			accidental = + 2;
			break;  // G##
		}
		
		break;
		
	case 10:
	
		switch (spelling) {
		
		case 1:
			base7pc = 0;
			accidental = -2;
			octave++;
			break;  // Cbb
			
		case 0:
		
		case 2:
			base7pc = 6;
			accidental = -1;
			break;  // Bb
			
		case 3:
			base7pc = 5;
			accidental = + 1;
			break;  // A#
		}
		
		break;
		
	case 11:
	
		switch (spelling) {
		
		case 1:
			base7pc = 0;
			accidental = -1;
			octave++;
			break;  // Cb
			
		case 0:
		
		case 2:
			base7pc = 6;
			accidental =  0;
			break;  // B
			
		case 3:
			base7pc = 5;
			accidental = + 2;
			break;  // A##
		}
		
		break;
		
	}
	
	base7 = base7pc + 7 * octave;
}



//////////////////////////////
//
// Message::SetMetaTempo -- Input tempo is in quarter notes per minute
//   (meta message #0x51).
//

void Message::SetMetaTempo(double tempo) {
	int microseconds = (int)(60.0 / tempo * 1000000.0 + 0.5);
	SetTempoMicroseconds(microseconds);
}



//////////////////////////////
//
// Message::SetTempo -- Alias for Message::SetMetaTempo().
//

void Message::SetTempo(double tempo) {
	SetMetaTempo(tempo);
}



//////////////////////////////
//
// Message::SetTempoMicroseconds -- Set the tempo in terms
//   of microseconds per quarter note.
//

void Message::SetTempoMicroseconds(int microseconds) {
	SetCount(6);
	(*this)[0] = 0xff;
	(*this)[1] = 0x51;
	(*this)[2] = 3;
	(*this)[3] = (microseconds >> 16) & 0xff;
	(*this)[4] = (microseconds >>  8) & 0xff;
	(*this)[5] = (microseconds >>  0) & 0xff;
}



//////////////////////////////
//
// Message::MakeTimeSignature -- create a time signature meta message
//      (meta #0x58).  The "bottom" parameter should be a power of two;
//      otherwise, it will be forced to be the next highest power of two,
//      as MIDI time signatures must have a power of two in the denominator.
//
// Default values:
//     clocks_per_click     == 24 (quarter note)
//     num_32nds_per_quarter ==  8 (8 32nds per quarter note)
//
// Time signature of 4/4 would be:
//    top    = 4
//    bottom = 4 (converted to 2 in the MIDI file for 2nd power of 2).
//    clocks_per_click = 24 (2 eighth notes based on num_32nds_per_quarter)
//    num_32nds_per_quarter = 8
//
// Time signature of 6/8 would be:
//    top    = 6
//    bottom = 8 (converted to 3 in the MIDI file for 3rd power of 2).
//    clocks_per_click = 36 (3 eighth notes based on num_32nds_per_quarter)
//    num_32nds_per_quarter = 8
//

void Message::MakeTimeSignature(int top, int bottom, int clocks_per_click,
		int num_32nds_per_quarter) {
	int base2 = 0;
	
	while (bottom >>= 1)
		base2++;
		
	SetCount(7);
	
	(*this)[0] = 0xff;
	
	(*this)[1] = 0x58;
	
	(*this)[2] = 4;
	
	(*this)[3] = 0xff & top;
	
	(*this)[4] = 0xff & base2;
	
	(*this)[5] = 0xff & clocks_per_click;
	
	(*this)[6] = 0xff & num_32nds_per_quarter;
}



///////////////////////////////////////////////////////////////////////////
//
// make functions to create various MIDI message --
//


//////////////////////////////
//
// Message::MakeNoteOn -- create a note-on message.
//
// default value: channel = 0
//
// Note: The channel parameter used to be last, but makes more sense to
//   have it first...
//

void Message::MakeNoteOn(int channel, int key, int velocity) {
	SetCount(3);
	(*this)[0] = 0x90 | (0x0f & channel);
	(*this)[1] = key & 0x7f;
	(*this)[2] = velocity & 0x7f;
}



//////////////////////////////
//
// Message::MakeNoteOff -- create a note-off message.   If no
//   parameters are given, the current contents is presumed to be a
//   note-on message, which will be converted into a note-off message.
//
// default value: channel = 0
//
// Note: The channel parameter used to be last, but makes more sense to
//   have it first...
//


void Message::MakeNoteOff(int channel, int key, int velocity) {
	SetCount(3);
	(*this)[0] = 0x80 | (0x0f & channel);
	(*this)[1] = key & 0x7f;
	(*this)[2] = velocity & 0x7f;
}


void Message::MakeNoteOff(int channel, int key) {
	SetCount(3);
	(*this)[0] = 0x90 | (0x0f & channel);
	(*this)[1] = key & 0x7f;
	(*this)[2] = 0x00;
}


void Message::MakeNoteOff() {
	if (!IsNoteOn()) {
		SetCount(3);
		(*this)[0] = 0x90;
		(*this)[1] = 0;
		(*this)[2] = 0;
	}
	
	else {
		(*this)[2] = 0;
	}
}



/////////////////////////////
//
// Message::MakeController -- Create a controller message.
//

void Message::MakeController(int channel, int num, int value) {
	SetCount(0);
	Add(0xb0 | (0x0f & channel));
	Add(0x7f & num);
	Add(0x7f & value);
}



/////////////////////////////
//
// Message::MakePatchChange -- Create a patch-change message.
//

void Message::MakePatchChange(int channel, int patchnum) {
	SetCount(0);
	Add(0xc0 | (0x0f & channel));
	Add(0x7f & patchnum);
}


void Message::MakeTimbre(int channel, int patchnum) {
	MakePatchChange(channel, patchnum);
}



//////////////////////////////
//
// Message::MakeMetaMessage -- Create a Meta event with the
//   given text String as the parameter.  The length of the String should
//   not be longer than 127 characters at the moment (will have to check
//   if VLV sizes are allowed).
//

void Message::MakeMetaMessage(int mnum, String data) {
	SetCount(0);
	Add(0xff);
	Add(mnum & 0x7f); // I think max is 0x7f.
	int dsize = (int)data.GetCount();
	
	if (dsize > 127) {
		Add(127);
		
		for (int i = 0; i < 128; i++) {
			Add(data[i]);
		}
	}
	
	else {
		Add(data.GetCount());
		std::copy(data.begin(), data.end(), std::back_inserter(*this));
	}
}



//////////////////////////////
//
// Message::MakeCopyright -- Create a metaevent copyright message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeCopyright(String text) {
	MakeMetaMessage(0x02, text);
}



//////////////////////////////
//
// Message::MakeTrackName -- Create a metaevent track name message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeTrackName(String name) {
	MakeMetaMessage(0x03, name);
}



//////////////////////////////
//
// Message::MakeTrackName -- Create a metaevent instrument name message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeInstrumentName(String name) {
	MakeMetaMessage(0x04, name);
}



//////////////////////////////
//
// Message::MakeLyric -- Create a metaevent lyrics/text message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeLyric(String text) {
	MakeMetaMessage(0x05, text);
}



//////////////////////////////
//
// Message::MakeMarker -- Create a metaevent marker message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeMarker(String text) {
	MakeMetaMessage(0x06, text);
}



//////////////////////////////
//
// Message::MakeCue -- Create a metaevent cue-point message.
//    This is not a real MIDI message, but rather a pretend message for use
//    within Standard MIDI Files.
//

void Message::MakeCue(String text) {
	MakeMetaMessage(0x07, text);
}

NAMESPACE_MIDI_END
