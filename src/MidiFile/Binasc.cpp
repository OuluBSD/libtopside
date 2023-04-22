#include "MidiFile.h"


NAMESPACE_MIDI_BEGIN


//////////////////////////////
//
// Binasc::Binasc -- Constructor: set the default option values.
//

Binasc::Binasc() {
	bytes_q    = 1; // option for printing HEX bytes when converting to ASCII
	comments_q = 0; // option for printing text comments when converting to ASCII
	midi_q     = 0; // option for printing ASCII as parsed MIDI file.
	max_line_length = 75;
	max_line_bytes  = 25;
}



//////////////////////////////
//
// Binasc::~Binasc -- Destructor.
//

Binasc::~Binasc() {
	// do nothing
}



//////////////////////////////
//
// Binasc::SetLineLength -- Set the maximum length of a line when converting
//    binary content into ASCII bytes.  If the input size is less than one,
//    set to the default value of 75 characters per line.
//

int Binasc::SetLineLength(int length) {
	if (length < 1) {
		max_line_length = 75;
	}
	
	else {
		max_line_length = length;
	}
	
	return max_line_length;
}



//////////////////////////////
//
// Binasc::GetLineLength -- Set the maximum length of a line when converting
//    binary content into ASCII bytes.
//

int Binasc::GetLineLength() {
	return max_line_length;
}



//////////////////////////////
//
// Binasc::SetLineBytes -- Set the maximum number of hex bytes in ASCII output.
//    If the input size is less than one, set to the default value of 25
//    hex bytes per line.
//

int Binasc::SetLineBytes(int length) {
	if (length < 1) {
		max_line_bytes = 25;
	}
	
	else {
		max_line_bytes = length;
	}
	
	return max_line_bytes;
}



//////////////////////////////
//
// Binasc::GetLineBytes -- Get the maximum number of hex bytes in ASCII output.
//

int Binasc::GetLineBytes() {
	return max_line_length;
}



//////////////////////////////
//
// Binasc::SetComments -- Display or not display printable characters
//    as comments when converting binary files to ASCII byte codes.
//

void Binasc::SetComments(int state) {
	comments_q = state ? 1 : 0;
}


void Binasc::SetCommentsOn() {
	SetComments(true);
}


void Binasc::SetCommentsOff() {
	SetComments(false);
}



//////////////////////////////
//
// Binasc::GetComments -- Get the comment display style for
//    showing comments in ASCII output;
//

int Binasc::GetComments() {
	return comments_q;
}



//////////////////////////////
//
// Binasc::SetBytes -- Display or not display hex codes (only
//    print ASCII printable characters).
//

void Binasc::SetBytes(int state) {
	bytes_q = state ? 1 : 0;
}


void Binasc::SetBytesOn() {
	SetBytes(true);
}


void Binasc::SetBytesOff() {
	SetBytes(false);
}


//////////////////////////////
//
// Binasc::GetBytes -- Get hex byte display status.
//

int Binasc::GetBytes() {
	return bytes_q;
}


//////////////////////////////
//
// Binasc::Set -- Display or not display parsed MIDI data.
//

void Binasc::Set(int state) {
	midi_q = state ? 1 : 0;
}


void Binasc::SetOn() {
	Set(true);
}


void Binasc::SetOff() {
	Set(false);
}



//////////////////////////////
//
// Binasc::Get -- Get the MIDI file printing style option state.
//

int Binasc::Get() {
	return midi_q;
}



//////////////////////////////
//
// Binasc::WriteToBinary -- Convert an ASCII representation of bytes into
//     the binary file that it describes.  Returns 0 if there was a problem
//     otherwise returns 1.
//

int Binasc::WriteToBinary(String outfile, String infile) {
	FileIn input;
	input.Open(infile);
	
	if (!input.IsOpen()) {
		LOG("Cannot open " << infile << " for reading in binasc.");
		return 0;
	}
	
	FileOut output;
	
	output.Open(outfile);
	
	if (!output.IsOpen()) {
		LOG("Cannot open " << outfile << " for reading in binasc.");
		return 0;
	}
	
	int status = WriteToBinary(output, input);
	
	input.Close();
	output.Close();
	return status;
}


int Binasc::WriteToBinary(String outfile, Stream& input) {
	FileOut output;
	output.Open(outfile);
	
	if (!output.IsOpen()) {
		LOG("Cannot open " << outfile << " for reading in binasc.");
		return 0;
	}
	
	int status = WriteToBinary(output, input);
	
	output.Close();
	return status;
}


int Binasc::WriteToBinary(Stream& out, String infile) {
	FileIn input;
	input.Open(infile);
	
	if (!input.IsOpen()) {
		LOG("Cannot open " << infile << " for reading in binasc.");
		return 0;
	}
	
	int status = WriteToBinary(out, input);
	
	input.Close();
	return status;
}


int Binasc::WriteToBinary(Stream& out, Stream& input) {
	String input_line;    // current line being Processed
	int  line_num = 0;    // current line number
	
	input_line = input.GetLine();
	line_num++;
	
	while (!input.IsEof()) {
		ProcessLine(out, input_line, line_num);
		input_line = input.GetLine();
		line_num++;
	}
	
	return 1;
}



//////////////////////////////
//
// Binasc::ReadFromBinary -- convert an ASCII representation of bytes into
//     the binary file that it describes.
//

int Binasc::ReadFromBinary(String outfile, String infile) {
	FileIn input;
	input.Open(infile);
	
	if (!input.IsOpen()) {
		LOG("Cannot open " << infile << " for reading in binasc.");
		return 0;
	}
	
	FileOut output;
	
	output.Open(outfile);
	
	if (!output.IsOpen()) {
		LOG("Cannot open " << outfile << " for reading in binasc.");
		return 0;
	}
	
	int status = ReadFromBinary(output, input);
	
	input.Close();
	output.Close();
	return status;
}


int Binasc::ReadFromBinary(String outfile, Stream& input) {
	FileOut output;
	output.Open(outfile);
	
	if (!output.IsOpen()) {
		LOG("Cannot open " << outfile << " for reading in binasc.");
		return 0;
	}
	
	int status = ReadFromBinary(output, input);
	
	output.Close();
	return status;
}


int Binasc::ReadFromBinary(Stream& out, String infile) {
	FileIn input;
	input.Open(infile);
	
	if (!input.IsOpen()) {
		LOG("Cannot open " << infile << " for reading in binasc.");
		return 0;
	}
	
	int status = ReadFromBinary(out, input);
	
	input.Close();
	return status;
}


int Binasc::ReadFromBinary(Stream& out, Stream& input) {
	int status;
	
	if (midi_q) {
		status = OutputStyle(out, input);
	}
	else if (!bytes_q) {
		status = OutputStyleAscii(out, input);
	}
	else if (bytes_q && comments_q) {
		status = OutputStyleBoth(out, input);
	}
	else {
		status = OutputStyleBinary(out, input);
	}
			
	return status;
}



///////////////////////////////////////////////////////////////////////////
//
// protected functions --
//

//////////////////////////////
//
// Binasc::OutputStyleAscii -- read an input file and output bytes in ascii
//    form, not displaying any blank lines.  Output words are not
//    broken unless they are longer than 75 characters.
//

int Binasc::OutputStyleAscii(Stream& out, Stream& input) {
	uint8 outputWord[256] = {0};   // storage for current word
	int index     = 0;             // current length of word
	int lineCount = 0;             // current length of line
	int type      = 0;             // 0=space, 1=printable
	int lastType  = 0;             // 0=space, 1=printable
	uint8 ch;                      // current input byte
	
	ch = input.Get();
	
	while (!input.IsEof()) {
		lastType = type;
		type = (isprint(ch) && !isspace(ch)) ? 1 : 0;
		
		if ((type == 1) && (lastType == 0)) {
			// start of a new word.  check where to put old word
			if (index + lineCount >= max_line_length) {  // put on next line
				outputWord[index] = '\0';
				out << '\n' << (const char*)outputWord;
				lineCount = index;
				index = 0;
			}
			
			else {                                   // put on current line
				outputWord[index] = '\0';
				
				if (lineCount != 0) {
					out << ' ';
					lineCount++;
				}
				
				out << (const char*)outputWord;
				
				lineCount += index;
				index = 0;
			}
		}
		
		if (type == 1) {
			outputWord[index++] = ch;
		}
		
		ch = input.Get();
	}
	
	if (index != 0) {
		out.PutEol();
	}
	
	return 1;
}



//////////////////////////////
//
// Binasc::OutputStyleBinary -- read an input binary file and output bytes
//     in ascii form, hexadecimal numbers only.
//

int Binasc::OutputStyleBinary(Stream& out, Stream& input) {
	int currentByte = 0;    // current byte output in line
	uint8 ch;               // current input byte
	
	ch = input.Get();
	
	if (input.IsEof()) {
		LOG("End of the file right away!");
		return 0;
	}
	
	while (!input.IsEof()) {
		if (ch < 0x10) {
			out << '0';
		}
		
		out << Format("%X ", (int)ch);
		
		currentByte++;
		
		if (currentByte >= max_line_bytes) {
			out << '\n';
			currentByte = 0;
		}
		
		ch = input.Get();
	}
	
	if (currentByte != 0) {
		out.PutEol();
	}
	
	return 1;
}



//////////////////////////////
//
// Binasc::OutputStyleBoth -- read an input file and output bytes in ASCII
//     form with both hexadecimal numbers and ascii representation
//

int Binasc::OutputStyleBoth(Stream& out, Stream& input) {
	uint8 asciiLine[256] = {0};    // storage for output line
	int currentByte = 0;           // current byte output in line
	int index = 0;                 // current character in asciiLine
	uint8 ch;                      // current input byte
	
	ch = input.Get();
	
	while (!input.IsEof()) {
		if (index == 0) {
			asciiLine[index++] = ';';
			out << ' ';
		}
		
		if (ch < 0x10) {
			out << '0';
		}
		
		out << Format("%X ", (int)ch);
		
		currentByte++;
		
		asciiLine[index++] = ' ';
		
		if (isprint(ch)) {
			asciiLine[index++] = ch;
		}
		
		else {
			asciiLine[index++] = ' ';
		}
		
		asciiLine[index++] = ' ';
		
		if (currentByte >= max_line_bytes) {
			out << '\n';
			asciiLine[index] = '\0';
			out << (const char*)asciiLine << "\n\n";
			currentByte = 0;
			index = 0;
		}
		
		ch = input.Get();
	}
	
	if (currentByte != 0) {
		out << '\n';
		asciiLine[index] = '\0';
		out << (const char*)asciiLine << '\n';
	}
	
	return 1;
}



///////////////////////////////
//
// ProcessLine -- read a line of input and output any specified bytes
//

int Binasc::ProcessLine(Stream& out, String input, int lineCount) {
	int status = 1;
	int i = 0;
	int length = (int)input.GetCount();
	String word;
	
	while (i < length) {
		if ((input[i] == ';') || (input[i] == '#') || (input[i] == '/')) {
			// comment to end of line, so ignore
			return 1;
		}
		
		else if ((input[i] == ' ') || (input[i] == '\n') || (input[i] == '\t')) {
			// ignore whitespace
			i++;
			continue;
		}
		
		else if (input[i] == '+') {
			i = GetWord(word, input, " \n\t", i);
			status = ProcessAsciiWord(out, word, lineCount);
		}
		
		else if (input[i] == '"') {
			i = GetWord(word, input, "\"", i);
			status = ProcessStringWord(out, word, lineCount);
		}
		
		else if (input[i] == 'v') {
			i = GetWord(word, input, " \n\t", i);
			status = ProcessVlvWord(out, word, lineCount);
		}
		
		else if (input[i] == 'p') {
			i = GetWord(word, input, " \n\t", i);
			status = ProcessPitchBendWord(out, word, lineCount);
		}
		
		else if (input[i] == 't') {
			i = GetWord(word, input, " \n\t", i);
			status = ProcessTempoWord(out, word, lineCount);
		}
		
		else {
			i = GetWord(word, input, " \n\t", i);
			
			if (word.Find('\'') != -1) {
				status = ProcessDecimalWord(out, word, lineCount);
			}
			
			else if ((word.Find(',') != -1) || (word.GetCount() > 2)) {
				status = ProcessBinaryWord(out, word, lineCount);
			}
			
			else {
				status = ProcessHexWord(out, word, lineCount);
			}
		}
								
		if (status == 0) {
			return 0;
		}
		
	}
	
	return 1;
}



//////////////////////////////
//
// Binasc::GetWord -- extract a sub String, stopping at any of the given
//   terminator characters.
//

int Binasc::GetWord(String& word, String input,
					String terminators, int index) {
	word = "";
	int i = index;
	int escape = 0;
	int ecount = 0;
	
	if (terminators.Find('"') != -1) {
		escape = 1;
	}
	
	while (i < (int)input.GetCount()) {
		if (escape && input[i] == '\"') {
			ecount++;
			i++;
			
			if (ecount >= 2) {
				break;
			}
		}
		
		if (escape && (i < (int)input.GetCount() - 1) && (input[i] == '\\')
			&& (input[i+1] == '"')) {
			word.Cat(input[i+1]);
			i += 2;
		}
		
		else
			if (terminators.Find(input[i]) == -1) {
				word.Cat(input[i]);
				i++;
			}
			
			else {
				i++;
				return i;
			}
	}
	
	return i;
}



///////////////////////////////
//
// Binasc::GetVLV -- read a Variable-Length Value from the file
//

int Binasc::GetVLV(Stream& infile, int& trackbytes) {
	int output = 0;
	uint8 ch;
	infile.Get((char*)&ch, 1);
	trackbytes++;
	output = (output << 7) | (0x7f & ch);
	
	while (ch >= 0x80) {
		infile.Get((char*)&ch, 1);
		trackbytes++;
		output = (output << 7) | (0x7f & ch);
	}
	
	return output;
}



//////////////////////////////
//
// Binasc::ReadEvent -- Read a delta time and then a MIDI message
//     (or meta message).  Returns 1 if not end-of-track meta message;
//     0 otherwise.
//

int Binasc::ReadEvent(Stream& out, Stream& infile, int& trackbytes,
		int& command) {
        
	// Read and print Variable Length Value for delta ticks
	int vlv = GetVLV(infile, trackbytes);
	
	StringStream output;
	
	output << "v" << IntStr(vlv) << "\t";
	
	String comment;
	
	int status = 1;
	uint8 ch;
	char byte1, byte2;
	infile.Get((char*)&ch, 1);
	trackbytes++;
	
	if (ch < 0x80) {
		// running status: command byte is previous one in data stream
		output << "   ";
	}
	
	else {
		// midi command byte
		output << Format("%X", (int)ch);
		command = ch;
		infile.Get((char*)&ch, 1);
		trackbytes++;
	}
	
	byte1 = ch;
	
	int metatype = 0;
	
	switch (command & 0xf0) {
	
	case 0x80:    // note-off: 2 bytes
		output << " '" << Format("%d", (int)byte1);
		infile.Get((char*)&ch, 1);
		trackbytes++;
		byte2 = ch;
		output << " '" << Format("%d", (int)byte2);
		
		if (comments_q) {
			comment += "note-off " + KeyToPitchName(byte1);
		}
		
		break;
		
	case 0x90:    // note-on: 2 bytes
		output << " '" << Format("%d", (int)byte1);
		infile.Get((char*)&ch, 1);
		trackbytes++;
		byte2 = ch;
		output << " '" << Format("%d", (int)byte2);
		
		if (comments_q) {
			if (byte2 == 0) {
				comment += "note-off " + KeyToPitchName(byte1);
			}
			
			else {
				comment += "note-on " + KeyToPitchName(byte1);
			}
		}
		
		break;
		
	case 0xA0:    // aftertouch: 2 bytes
		output << " '" << Format("%d", (int)byte1);
		infile.Get((char*)&ch, 1);
		trackbytes++;
		byte2 = ch;
		output << " '" << Format("%d", (int)byte2);
		
		if (comments_q) {
			comment += "after-touch";
		}
		
		break;
		
	case 0xB0:    // continuous controller: 2 bytes
		output << " '" << Format("%d", (int)byte1);
		infile.Get((char*)&ch, 1);
		trackbytes++;
		byte2 = ch;
		output << " '" << Format("%d", (int)byte2);
		
		if (comments_q) {
			comment += "controller";
		}
		
		break;
		
	case 0xE0:    // pitch-bend: 2 bytes
		output << " '" << Format("%d", (int)byte1);
		infile.Get((char*)&ch, 1);
		trackbytes++;
		byte2 = ch;
		output << " '" << Format("%d", (int)byte2);
		
		if (comments_q) {
			comment += "pitch-bend";
		}
		
		break;
		
	case 0xC0:    // patch change: 1 bytes
		output << " '" << Format("%d", (int)byte1);
		
		if (comments_q) {
			output << "\t";
			comment += "patch-change";
		}
		
		break;
		
	case 0xD0:    // channel pressure: 1 bytes
		output << " '" << Format("%d", (int)byte1);
		
		if (comments_q) {
			comment += "channel pressure";
		}
		
		break;
		
	case 0xF0:    // various system bytes: variable bytes
	
		switch (command) {
		
		case 0xf0:
			break;
			
		case 0xf7:
			// Read the first byte which is either 0xf0 or 0xf7.
			// Then a VLV byte count for the number of bytes
			// that remain in the message will follow.
			// Then read that number of bytes.
			{
				infile.SeekCur(-1); // putback
				infile.Put(&byte1, 1);
				trackbytes--;
				int length = GetVLV(infile, trackbytes);
				output << " v" << Format("%d", length);
				
				for (int i = 0; i < length; i++) {
					infile.Get((char*)&ch, 1);
					trackbytes++;
					
					if (ch < 0x10) {
						output << " 0" << Format("%X", (int)ch);
					}
					
					else {
						output << " " << Format("%X", (int)ch);
					}
				}
			}
			
			break;
			
		case 0xf1:
			break;
			
		case 0xf2:
			break;
			
		case 0xf3:
			break;
			
		case 0xf4:
			break;
			
		case 0xf5:
			break;
			
		case 0xf6:
			break;
			
		case 0xf8:
			break;
			
		case 0xf9:
			break;
			
		case 0xfa:
			break;
			
		case 0xfb:
			break;
			
		case 0xfc:
			break;
			
		case 0xfd:
			break;
			
		case 0xfe:
			LOG("Error command not yet handled");
			return 0;
			break;
			
		case 0xff: { // meta message
				metatype = ch;
				output << " " << Format("%X", metatype);
				int length = GetVLV(infile, trackbytes);
				output << " v" << Format("%d", length);
				
				switch (metatype) {
				
				case 0x00:  // sequence number
					// display two-byte big-endian decimal value.
					{
						infile.Get((char*)&ch, 1);
						trackbytes++;
						int number = ch;
						infile.Get((char*)&ch, 1);
						trackbytes++;
						number = (number << 8) | ch;
						output << " 2'" << number;
					}
					
					break;
					
				case 0x20: // MIDI channel prefix
				
				case 0x21: // MIDI port
					// display single-byte decimal number
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;
					break;
					
				case 0x51: // Tempo
					// display tempo as "t" word.
					{
						int number = 0;
						infile.Get((char*)&ch, 1);
						trackbytes++;
						number = (number << 8) | ch;
						infile.Get((char*)&ch, 1);
						trackbytes++;
						number = (number << 8) | ch;
						infile.Get((char*)&ch, 1);
						trackbytes++;
						number = (number << 8) | ch;
						double tempo = 1000000.0 / number * 60.0;
						output << " t" << tempo;
					}
					
					break;
					
				case 0x54: // SMPTE offset
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // hour
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // minutes
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // seconds
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // frames
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // subframes
					break;
					
				case 0x58: // time signature
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // numerator
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // denominator power
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // clocks per beat
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // 32nd notes per beat
					break;
					
				case 0x59: // key signature
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // accidentals
					infile.Get((char*)&ch, 1);
					trackbytes++;
					output << " '" << (int)ch;  // mode
					break;
					
				case 0x01: // text
				
				case 0x02: // copyright
				
				case 0x03: // track name
				
				case 0x04: // instrument name
				
				case 0x05: // lyric
				
				case 0x06: // marker
				
				case 0x07: // cue point
				
				case 0x08: // program name
				
				case 0x09: // device name
					output << " \"";
					
					for (int i = 0; i < length; i++) {
						infile.Get((char*)&ch, 1);
						trackbytes++;
						output.Put((char)ch);
					}
					
					output << "\"";
					
					break;
					
				default:
				
					for (int i = 0; i < length; i++) {
						infile.Get((char*)&ch, 1);
						trackbytes++;
						output << " ";
						
						if (ch < 0x10) {
							output << "0";
						}
						
						output << Format("%X", (int)ch);
					}
				}
				
				switch (metatype) {
				
				case 0x00:
					comment += "sequence number";
					break;
					
				case 0x01:
					comment += "text";
					break;
					
				case 0x02:
					comment += "copyright notice";
					break;
					
				case 0x03:
					comment += "track name";
					break;
					
				case 0x04:
					comment += "instrument name";
					break;
					
				case 0x05:
					comment += "lyric";
					break;
					
				case 0x06:
					comment += "marker";
					break;
					
				case 0x07:
					comment += "cue point";
					break;
					
				case 0x08:
					comment += "program name";
					break;
					
				case 0x09:
					comment += "device name";
					break;
					
				case 0x20:
					comment += "MIDI channel prefix";
					break;
					
				case 0x21:
					comment += "MIDI port";
					break;
					
				case 0x51:
					comment += "tempo";
					break;
					
				case 0x54:
					comment += "SMPTE offset";
					break;
					
				case 0x58:
					comment += "time signature";
					break;
					
				case 0x59:
					comment += "key signature";
					break;
					
				case 0x7f:
					comment += "system exclusive";
					break;
					
				case 0x2f:
					status = 0;
					comment += "end-of-track";
					break;
					
				default:
					comment += "meta-message";
				}
			}
			
			break;
			
		}
		
		break;
	}
	
	output.Seek(0);
	out << output.GetResult();
	
	if (comments_q) {
		out << "\t; " << comment;
	}
	
	return status;
}



/////////////////////////////
//
// Binasc::KeyToPitchName -- Convert a MIDI key number to scientific
//     pitch notation.
//

String Binasc::KeyToPitchName(int key) {
	int pc = key % 12;
	int octave = key / 12 - 1;
	StringStream output;
	
	switch (pc) {
	
	case  0:
		output << "C";
		break;
		
	case  1:
		output << "C#";
		break;
		
	case  2:
		output << "D";
		break;
		
	case  3:
		output << "D#";
		break;
		
	case  4:
		output << "E";
		break;
		
	case  5:
		output << "F";
		break;
		
	case  6:
		output << "F#";
		break;
		
	case  7:
		output << "G";
		break;
		
	case  8:
		output << "G#";
		break;
		
	case  9:
		output << "A";
		break;
		
	case 10:
		output << "A#";
		break;
		
	case 11:
		output << "B";
		break;
	}
	
	output << octave;
	
	output.Seek(0);
	return output.GetResult();
}



//////////////////////////////
//
// Binasc::OutputStyle -- Read an input file and output bytes parsed
//     as a MIDI file (return false if not a MIDI file).
//

int Binasc::OutputStyle(Stream& out, Stream& input) {
	uint8 ch;                      // current input byte
	StringStream tempout;
	input.Get((char*)&ch, 1);
	
	if (input.IsEof()) {
		LOG("End of the file right away!");
		return 0;
	}
	
	// Read the MIDI file header:
	
	// The first four bytes must be the characters "MThd"
	
	if (ch != 'M') {
		LOG("Not a MIDI file M");
		return 0;
	}
	
	input.Get((char*)&ch, 1);
	
	if (ch != 'T') {
		LOG("Not a MIDI file T");
		return 0;
	}
	
	input.Get((char*)&ch, 1);
	
	if (ch != 'h') {
		LOG("Not a MIDI file h");
		return 0;
	}
	
	input.Get((char*)&ch, 1);
	
	if (ch != 'd') {
		LOG("Not a MIDI file d");
		return 0;
	}
	
	tempout << "\"MThd\"";
	
	if (comments_q) {
		tempout << "\t\t\t; MIDI header chunk marker";
	}
	
	tempout << "\n";
	
	// The next four bytes are a big-endian byte count for the header
	// which should nearly always be "6".
	int headersize = 0;
	input.Get((char*)&ch, 1);
	headersize = (headersize << 8) | ch;
	input.Get((char*)&ch, 1);
	headersize = (headersize << 8) | ch;
	input.Get((char*)&ch, 1);
	headersize = (headersize << 8) | ch;
	input.Get((char*)&ch, 1);
	headersize = (headersize << 8) | ch;
	tempout << "4'" << headersize;
	
	if (comments_q) {
		tempout << "\t\t\t; bytes to follow in header chunk";
	}
	
	tempout << "\n";
	
	// First number in header is two-byte file type.
	int filetype = 0;
	input.Get((char*)&ch, 1);
	filetype = (filetype << 8) | ch;
	input.Get((char*)&ch, 1);
	filetype = (filetype << 8) | ch;
	tempout << "2'" << filetype;
	
	if (comments_q) {
		tempout << "\t\t\t; file format: Type-" << filetype << " (";
		
		switch (filetype) {
		
		case 0:
			tempout << "single track";
			break;
			
		case 1:
			tempout << "multitrack";
			break;
			
		case 2:
			tempout << "multisegment";
			break;
			
		default:
			tempout << "unknown";
			break;
		}
		
		tempout << ")";
	}
	
	tempout << "\n";
	
	// Second number in header is two-byte trackcount.
	int trackcount = 0;
	input.Get((char*)&ch, 1);
	trackcount = (trackcount << 8) | ch;
	input.Get((char*)&ch, 1);
	trackcount = (trackcount << 8) | ch;
	tempout << "2'" << trackcount;
	
	if (comments_q) {
		tempout << "\t\t\t; number of tracks";
	}
	
	tempout << "\n";
	
	// Third number is divisions.  This can be one of two types:
	// regular: top bit is 0: number of ticks per quarter note
	// SMPTE:   top bit is 1: first byte is negative frames, second is
	//          ticks per frame.
	uint8 byte1;
	uint8 byte2;
	input.Get((char*)&byte1, 1);
	input.Get((char*)&byte2, 1);
	
	if (byte1 & 0x80) {
		// SMPTE divisions
		tempout << "1'-" << 0xff - (int)byte1 + 1;
		
		if (comments_q) {
			tempout << "\t\t\t; SMPTE frames/second";
		}
		
		tempout << "\n";
		
		tempout << "1'" << Format("%d", (int)byte2);
		
		if (comments_q) {
			tempout << "\t\t\t; subframes per frame";
		}
		
		tempout << "\n";
	}
	
	else {
		// regular divisions
		int divisions = 0;
		divisions = (divisions << 8) | byte1;
		divisions = (divisions << 8) | byte2;
		tempout << "2'" << divisions;
		
		if (comments_q) {
			tempout << "\t\t\t; ticks per quarter note";
		}
		
		tempout << "\n";
	}
	
	// Print any strange bytes in header:
	for (int i = 0; i < headersize - 6; i++) {
		input.Get((char*)&ch, 1);
		
		if (ch < 0x10) {
			tempout.Put('0');
		}
		
		tempout << Format("%X", (int)ch);
	}
	
	if (headersize - 6 > 0) {
		tempout << "\t\t\t; unknown header bytes";
		tempout << "\n";
	}
	
	int trackbytes;
	
	for (int i = 0; i < trackcount; i++) {
		tempout << "\n;;; TRACK " << i << " ----------------------------------";
		
		input.Get((char*)&ch, 1);
		// The first four bytes of a track must be the characters "MTrk"
		
		if (ch != 'M') {
			LOG("Not a MIDI file M2");
			return 0;
		}
		
		input.Get((char*)&ch, 1);
		
		if (ch != 'T') {
			LOG("Not a MIDI file T2");
			return 0;
		}
		
		input.Get((char*)&ch, 1);
		
		if (ch != 'r') {
			LOG("Not a MIDI file r");
			return 0;
		}
		
		input.Get((char*)&ch, 1);
		
		if (ch != 'k') {
			LOG("Not a MIDI file k");
			return 0;
		}
		
		tempout << "\"MTrk\"";
		
		if (comments_q) {
			tempout << "\t\t\t; MIDI track chunk marker";
		}
		
		tempout << "\n";
		
		// The next four bytes are a big-endian byte count for the track
		int tracksize = 0;
		input.Get((char*)&ch, 1);
		tracksize = (tracksize << 8) | ch;
		input.Get((char*)&ch, 1);
		tracksize = (tracksize << 8) | ch;
		input.Get((char*)&ch, 1);
		tracksize = (tracksize << 8) | ch;
		input.Get((char*)&ch, 1);
		tracksize = (tracksize << 8) | ch;
		tempout << "4'" << tracksize;
		
		if (comments_q) {
			tempout << "\t\t\t; bytes to follow in track chunk";
		}
		
		tempout << "\n";
		
		trackbytes = 0;
		int command = 0;
		
		// Process MIDI events until the end of the track
		
		while (ReadEvent(tempout, input, trackbytes, command)) {
			tempout << "\n";
		};
		
		tempout << "\n";
		
		if (trackbytes != tracksize) {
			tempout << "; TRACK SIZE ERROR, ACTUAL SIZE: " << trackbytes << "\n";
		}
	}
	
	// print #define definitions if requested.
	
	
	// print main content of MIDI file parsing:
	tempout.Seek(0);
	out << tempout.GetResult();
	
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessDecimalWord -- interprets a decimal word into
//     constituent bytes
//

int Binasc::ProcessDecimalWord(Stream& out, String str, int line_num) {
	int length = (int)str.GetCount();        // length of ascii binary number
	int byteCount = -1;              // number of bytes to output
	int quoteIndex = -1;             // index of decimal specifier
	int signIndex = -1;              // index of any sign for number
	int periodIndex = -1;            // index of period for floating point
	int endiindex = -1;            // index of little endian specifier
	int i = 0;
	
	// make sure that all characters are valid
	
	for (int i = 0; i < length; i++) {
		switch (str[i]) {
		
		case '\'':
		
			if (quoteIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("extra quote in decimal number");
				return 0;
			}
			
			else {
				quoteIndex = i;
			}
			
			break;
			
		case '-':
		
			if (signIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("cannot have more than two minus signs in number");
				return 0;
			}
			
			else {
				signIndex = i;
			}
			
			if (i == 0 || str[i-1] != '\'') {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("minus sign must immediately follow quote mark");
				return 0;
			}
			
			break;
			
		case '.':
		
			if (quoteIndex == -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("cannot have decimal marker before quote");
				return 0;
			}
			
			if (periodIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("extra period in decimal number");
				return 0;
			}
			
			else {
				periodIndex = i;
			}
			
			break;
			
		case 'u':
		
		case 'U':
		
			if (quoteIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("cannot have endian specified after quote");
				return 0;
			}
			
			if (endiindex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("extra \"u\" in decimal number");
				return 0;
			}
			
			else {
				endiindex = i;
			}
			
			break;
			
		case '8':
		
		case '1':
		
		case '2':
		
		case '3':
		
		case '4':
		
			if (quoteIndex == -1 && byteCount != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("invalid byte specificaton before quote in " << "decimal number");
				return 0;
			}
			
			else
				if (quoteIndex == -1) {
					byteCount = str[i] - '0';
				}
				
			break;
			
		case '0':
		
		case '5':
		
		case '6':
		
		case '7':
		
		case '9':
		
			if (quoteIndex == -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("cannot have numbers before quote in decimal number");
				return 0;
			}
			
			break;
			
		default:
			LOG("Error on line " << line_num << " at token: " << str);
			LOG("Invalid character in decimal number"
			" (character number " << i << ")");
			return 0;
		}
	}
	
	// there must be a quote character to indicate a decimal number
	// and there must be a decimal number after the quote
	
	if (quoteIndex == -1) {
		LOG("Error on line " << line_num << " at token: " << str);
		LOG("there must be a quote to signify a decimal number");
		return 0;
	}
	
	else
	if (quoteIndex == length - 1) {
		LOG("Error on line " << line_num << " at token: " << str);
		LOG("there must be a decimal number after the quote");
		return 0;
	}
		
	// 8 byte decimal output can only occur if reading a double number
	
	if (periodIndex == -1 && byteCount == 8) {
		LOG("Error on line " << line_num << " at token: " << str);
		LOG("only floating-point numbers can use 8 bytes");
		return 0;
	}
	
	// default size for floating point numbers is 4 bytes
	
	if (periodIndex != -1) {
		if (byteCount == -1) {
			byteCount = 4;
		}
	}
	
	// Process any floating point numbers possibilities
	
	if (periodIndex != -1) {
		double doubleOutput = ScanDouble(str.Begin() + quoteIndex + 1);
		float  floatOutput  = (float)doubleOutput;
		
		switch (byteCount) {
		
		case 4:
		
			if (endiindex == -1) {
				WriteBigEndianFloat(out, floatOutput);
			}
			
			else {
				WriteLittleEndianFloat(out, floatOutput);
			}
			
			return 1;
			
			break;
			
		case 8:
		
			if (endiindex == -1) {
				WriteBigEndianDouble(out, doubleOutput);
			}
			
			else {
				WriteLittleEndianDouble(out, doubleOutput);
			}
			
			return 1;
			
			break;
			
		default:
			LOG("Error on line " << line_num << " at token: " << str);
			LOG("floating-point numbers can be only 4 or 8 bytes");
			return 0;
		}
	}
	
	// Process any integer decimal number possibilities
	
	// default integer size is one byte, if size is not specified, then
	// the number must be in the one byte range and cannot overflow
	// the byte if the size of the decimal number is not specified
	
	if (byteCount == -1) {
		if (signIndex != -1) {
			long tempLong = ScanInt(str.Begin() + quoteIndex + 1);
			
			if (tempLong > 127 || tempLong < -128) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("Decimal number out of range from -128 to 127");
				return 0;
			}
			
			char charOutput = (char)tempLong;
			
			out << charOutput;
			return 1;
		}
		
		else {
			uint32 tempLong = (uint32)ScanInt(str.Begin() + quoteIndex + 1);
			uint8 uint8Output = (uint8)tempLong;
			
			if (tempLong > 255) { // || (tempLong < 0)) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("Decimal number out of range from 0 to 255");
				return 0;
			}
			
			out << uint8Output;
			
			return 1;
		}
	}
	
	// left with an integer number with a specified number of bytes
	
	switch (byteCount) {
	
	case 1:
	
		if (signIndex != -1) {
			long tempLong = ScanInt(str.Begin() + quoteIndex + 1);
			char charOutput = (char)tempLong;
			out << charOutput;
			return 1;
		}
		
		else {
			uint32 tempLong = (uint32)ScanInt(str.Begin() + quoteIndex + 1);
			uint8 uint8Output = (uint8)tempLong;
			out << uint8Output;
			return 1;
		}
		
		break;
		
	case 2:
	
		if (signIndex != -1) {
			long tempLong = ScanInt(str.Begin() + quoteIndex + 1);
			short shortOutput = (short)tempLong;
			
			if (endiindex == -1) {
				WriteBigEndianShort(out, shortOutput);
			}
			
			else {
				WriteLittleEndianShort(out, shortOutput);
			}
			
			return 1;
		}
		
		else {
			uint32 tempLong = (uint32)ScanInt(str.Begin() + quoteIndex + 1);
			uint16 uint16Output = (uint16)tempLong;
			
			if (endiindex == -1) {
				WriteBigEndianUShort(out, uint16Output);
			}
			
			else {
				WriteLittleEndianUShort(out, uint16Output);
			}
			
			return 1;
		}
		
		break;
		
	case 3: {
			if (signIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << str);
				LOG("negative decimal numbers cannot be stored in 3 bytes");
				return 0;
			}
			
			uint32 tempLong = (uint32)ScanInt(str.Begin() + quoteIndex + 1);
			
			uint8 byte1 = (uint8)((tempLong & 0x00ff0000) >> 16);
			uint8 byte2 = (uint8)((tempLong & 0x0000ff00) >>  8);
			uint8 byte3 = (uint8)((tempLong & 0x000000ff));
			
			if (endiindex == -1) {
				out << byte1;
				out << byte2;
				out << byte3;
			}
			
			else {
				out << byte3;
				out << byte2;
				out << byte1;
			}
			
			return 1;
		}
		
		break;
		
	case 4:
	
		if (signIndex != -1) {
			long tempLong = ScanInt(str.Begin() + quoteIndex + 1);
			
			if (endiindex == -1) {
				WriteBigEndianLong(out, tempLong);
			}
			
			else {
				WriteLittleEndianLong(out, tempLong);
			}
			
			return 1;
		}
		
		else {
			uint32 tempuLong = (uint32)ScanInt(str.Begin() + quoteIndex + 1);
			
			if (endiindex == -1) {
				WriteBigEndianULong(out, tempuLong);
			}
			
			else {
				WriteLittleEndianULong(out, tempuLong);
			}
			
			return 1;
		}
		
		break;
		
	default:
		LOG("Error on line " << line_num << " at token: " << str);
		LOG("invalid byte count specification for decimal number");
		return 0;
	}
	
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessHexWord -- interprets a hexadecimal word and converts into
//     its binary byte form.
//

int Binasc::ProcessHexWord(Stream& out, String word, int line_num) {
	int length = (int)word.GetCount();
	uint8 outputByte;
	
	if (length > 2) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("Size of hexadecimal number is too large.  Max is ff.");
		return 0;
	}
	
	if (!isxdigit(word[0]) || (length == 2 && !isxdigit(word[1]))) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("Invalid character in hexadecimal number.");
		return 0;
	}
	
	outputByte = (uint8)strtol(word, (char**)NULL, 16);
	
	out << outputByte;
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessStringWord -- interprets a binary word into
//     its constituent byte
//

int Binasc::ProcessStringWord(Stream& out, String word, int line_num) {
	out << word;
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessAsciiWord -- interprets a binary word into
//     its constituent byte
//

int Binasc::ProcessAsciiWord(Stream& out, String word, int line_num) {
	int length = (int)word.GetCount();
	uint8 outputByte;
	
	if (word[0] != '+') {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("character byte must start with \'+\' sign: ");
		return 0;
	}
	
	if (length > 2) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("character byte word is too long -- specify only one character");
		return 0;
	}
	
	if (length == 2) {
		outputByte = (uint8)word[1];
	}
	
	else {
		outputByte = ' ';
	}
	
	out << outputByte;
	
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessBinaryWord -- interprets a binary word into
//     its constituent byte
//

int Binasc::ProcessBinaryWord(Stream& out, String word, int line_num) {
	int length = (int)word.GetCount();        // length of ascii binary number
	int commaIndex = -1;             // index location of comma in number
	int leftDigits = -1;             // number of digits to left of comma
	int rightDigits = -1;            // number of digits to right of comma
	int i = 0;
	
	// make sure that all characters are valid
	
	for (int i = 0; i < length; i++) {
		if (word [i] == ',') {
			if (commaIndex != -1) {
				LOG("Error on line " << line_num << " at token: " << word);
				LOG("extra comma in binary number");
				return 0;
			}
			
			else {
				commaIndex = i;
			}
		}
		
		else
			if (!(word[i] == '1' || word[i] == '0')) {
				LOG("Error on line " << line_num << " at token: " << word);
				LOG("Invalid character in binary number"
				" (character is " << word[i] << ")");
				return 0;
			}
	}
	
	// comma cannot start or end number
	
	if (commaIndex == 0) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("cannot start binary number with a comma");
		return 0;
	}
	
	else if (commaIndex == length - 1) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("cannot end binary number with a comma");
		return 0;
	}
		
	// figure out how many digits there are in binary number
	// number must be able to fit into one byte.
	
	if (commaIndex != -1) {
		leftDigits = commaIndex;
		rightDigits = length - commaIndex - 1;
	}
	
	else if (length > 8) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("too many digits in binary number");
		return 0;
	}
		
	// if there is a comma, then there cannot be more than 4 digits on a side
	
	if (leftDigits > 4) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("too many digits to left of comma");
		return 0;
	}
	
	if (rightDigits > 4) {
		LOG("Error on line " << line_num << " at token: " << word);
		LOG("too many digits to right of comma");
		return 0;
	}
	
	// OK, we have a valid binary number, so calculate the byte
	
	uint8 output = 0;
	
	// if no comma in binary number
	if (commaIndex == -1) {
		for (int i = 0; i < length; i++) {
			output = output << 1;
			output |= word[i] - '0';
		}
	}
	
	// if comma in binary number
	
	else {
		for (int i = 0; i < leftDigits; i++) {
			output = output << 1;
			output |= word[i] - '0';
		}
		
		output = output << (4 - rightDigits);
		
		for (int i = 0 + commaIndex + 1; i < rightDigits + commaIndex + 1; i++) {
			output = output << 1;
			output |= word[i] - '0';
		}
	}
	
	// send the byte to the output
	out << output;
	
	return 1;
}



//////////////////////////////
//
// Binasc::ProcessVlvWord -- print a number in Variable Length Value form.
//   The int is split into 7-bit groupings, the MSB's that are zero
//   are dropped.  A continuation bit is added as the MSbit to each
//   7-bit grouping.  The continuation bit is "1" if there is another
//   byte in the VLV; "0" for the last byte.  VLVs are always
//   big-endian.  The input word starts with the character "v" followed
//   without space by an integer.
//

int Binasc::ProcessVlvWord(Stream& out, String word, int line_num) {
	if (word.GetCount() < 2) {
		LOG("Error on line: " << line_num << ": 'v' needs to be followed immediately by a decimal digit");
		return 0;
	}
	
	if (!isdigit(word[1])) {
		LOG("Error on line: " << line_num << ": 'v' needs to be followed immediately by a decimal digit");
		return 0;
	}
	
	uint32 value = ScanInt(word.Begin() + 1);
	
	uint8 byte[5];
	byte[0] = (value >> 28) & 0x7f;
	byte[1] = (value >> 21) & 0x7f;
	byte[2] = (value >> 14) & 0x7f;
	byte[3] = (value >>  7) & 0x7f;
	byte[4] = (value >>  0) & 0x7f;
	
	int flag = 0;
	
	for (int i = 0; i < 4; i++) {
		if (byte[i] != 0) {
			flag = 1;
		}
		
		if (flag) {
			byte[i] |= 0x80;
		}
	}
	
	for (int i = 0; i < 5; i++) {
		if (byte[i] >= 0x80 || i == 4) {
			out << byte[i];
		}
	}
	
	return 1;
}



////////////////////////////
//
// Binasc::ProcessTempoWord -- convert a floating point tempo into
//   a three-byte number of microseconds per beat per minute value.
//

int Binasc::ProcessTempoWord(Stream& out, String word, int line_num) {
	if (word.GetCount() < 2) {
		LOG("Error on line: " << line_num << ": 't' needs to be followed immediately by " << "a floating-point number");
		return 0;
	}
	
	if (!(isdigit(word[1]) || word[1] == '.' || word[1] == '-' || word[1] == '+')) {
		LOG("Error on line: " << line_num << ": 't' needs to be followed immediately by " << "a floating-point number");
		return 0;
	}
	
	double value = ScanDouble(word.Begin() + 1);
	
	if (value < 0.0) {
		value = -value;
	}
	
	int intval = int(60.0 * 1000000.0 / value + 0.5);
	
	uint8 byte0 = intval & 0xff;
	uint8 byte1 = (intval >>  8) & 0xff;
	uint8 byte2 = (intval >> 16) & 0xff;
	out << byte2 << byte1 << byte0;
	return 1;
}



////////////////////////////
//
// Binasc::ProcessPitchBendWord -- convert a floating point number in
//   the range from +1.0 to -1.0 into a 14-point integer with -1.0 mapping
//   to 0 and +1.0 mapping to 2^15-1.  This integer will be packed into
//   two bytes, with the LSB coming first and containing the bottom
//   7-bits of the 14-bit value, then the MSB coming second and containing
//   the top 7-bits of the 14-bit value.

int Binasc::ProcessPitchBendWord(Stream& out, String word,
		int line_num) {
	if (word.GetCount() < 2) {
		LOG("Error on line: " << line_num
		<< ": 'p' needs to be followed immediately by "
		<< "a floating-point number");
		return 0;
	}
	
	if (!(isdigit(word[1]) || word[1] == '.' || word[1] == '-'
		  || word[1] == '+')) {
		LOG("Error on line: " << line_num
		<< ": 'p' needs to be followed immediately by "
		<< "a floating-point number");
		return 0;
	}
	
	double value = ScanDouble(word.Begin() + 1);
	
	if (value > 1.0) {
		value = 1.0;
	}
	
	if (value < -1.0) {
		value = -1.0;
	}
	
	int intval = (int)(((1 << 13) - 0.5)  * (value + 1.0) + 0.5);
	
	uint8 LSB = intval & 0x7f;
	uint8 MSB = (intval >>  7) & 0x7f;
	out << LSB << MSB;
	return 1;
}



///////////////////////////////////////////////////////////////////////////
//
// Ordered byte writing functions --
//

//////////////////////////////
//
// Binasc::WriteLittleEndianUShort --
//

Stream& Binasc::WriteLittleEndianUShort(Stream& out, uint16 value) {
	union { char bytes[2];
		uint16 us;
	} data;
	data.us = value;
	out << data.bytes[0];
	out << data.bytes[1];
	return out;
}



//////////////////////////////
//
// Binasc::WriteBigEndianUShort --
//

Stream& Binasc::WriteBigEndianUShort(Stream& out, uint16 value) {
	union { char bytes[2];
		uint16 us;
	} data;
	data.us = value;
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// Binasc::WriteLittleEndianShort --
//

Stream& Binasc::WriteLittleEndianShort(Stream& out, short value) {
	union { char bytes[2];
		short s;
	} data;
	data.s = value;
	out << data.bytes[0];
	out << data.bytes[1];
	return out;
}



//////////////////////////////
//
// WriteBigEndianShort --
//

Stream& Binasc::WriteBigEndianShort(Stream& out, short value) {
	union { char bytes[2];
		short s;
	} data;
	data.s = value;
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// Binasc::WriteLittleEndianULong --
//

Stream& Binasc::WriteLittleEndianULong(Stream& out, uint32 value) {
	union { char bytes[4];
		uint32 ul;
	} data;
	data.ul = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// Binasc::WriteBigEndianULong --
//

Stream& Binasc::WriteBigEndianULong(Stream& out, uint32 value) {
	union { char bytes[4];
		long ul;
	} data;
	data.ul = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// Binasc::WriteLittleEndianLong --
//

Stream& Binasc::WriteLittleEndianLong(Stream& out, long value) {
	union { char bytes[4];
		long l;
	} data;
	data.l = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// Binasc::WriteBigEndianLong --
//

Stream& Binasc::WriteBigEndianLong(Stream& out, long value) {
	union { char bytes[4];
		long l;
	} data;
	data.l = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
	
}



//////////////////////////////
//
// Binasc::WriteBigEndianFloat --
//

Stream& Binasc::WriteBigEndianFloat(Stream& out, float value) {
	union { char bytes[4];
		float f;
	} data;
	data.f = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// Binasc::WriteLittleEndianFloat --
//

Stream& Binasc::WriteLittleEndianFloat(Stream& out, float value) {
	union { char bytes[4];
		float f;
	} data;
	data.f = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// Binasc::WriteBigEndianDouble --
//

Stream& Binasc::WriteBigEndianDouble(Stream& out, double value) {
	union { char bytes[8];
		double d;
	} data;
	data.d = value;
	out << data.bytes[7];
	out << data.bytes[6];
	out << data.bytes[5];
	out << data.bytes[4];
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// Binasc::WriteLittleEndianDouble --
//

Stream& Binasc::WriteLittleEndianDouble(Stream& out, double value) {
	union { char bytes[8];
		double d;
	} data;
	data.d = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	out << data.bytes[4];
	out << data.bytes[5];
	out << data.bytes[6];
	out << data.bytes[7];
	return out;
}


NAMESPACE_MIDI_END

