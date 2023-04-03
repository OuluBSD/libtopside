#ifndef _BINASC_H_INCLUDED
#define _BINASC_H_INCLUDED


NAMESPACE_MIDI_BEGIN
using namespace UPP;


// Interface to convert bytes between binary and ASCII forms.

class Binasc {

public:
	Binasc();
	~Binasc();
	
	// functions for setting options:
	int      SetLineLength(int length);
	int      GetLineLength();
	int      SetLineBytes(int length);
	int      GetLineBytes();
	void     SetComments(int state);
	void     SetCommentsOn();
	void     SetCommentsOff();
	int      GetComments();
	void     SetBytes(int state);
	void     SetBytesOn();
	void     SetBytesOff();
	int      GetBytes();
	void     Set(int state);
	void     SetOn();
	void     SetOff();
	int      Get();
	
	// functions for converting into a binary file:
	int      WriteToBinary(String outfile, String infile);
	int      WriteToBinary(String outfile, Stream& input);
	int      WriteToBinary(Stream& out, String infile);
	int      WriteToBinary(Stream& out, Stream& input);
	
	// functions for converting into an ASCII file with hex bytes:
	int      ReadFromBinary(String outfile, String infile);
	int      ReadFromBinary(String outfile, Stream& input);
	int      ReadFromBinary(Stream& out, String infile);
	int      ReadFromBinary(Stream& out, Stream& input);
	
	// static functions for writing ordered bytes:
	static Stream& WriteLittleEndianUShort(Stream& out, uint16 value);
	static Stream& WriteBigEndianUShort(Stream& out, uint16 value);
	static Stream& WriteLittleEndianShort(Stream& out, short  value);
	static Stream& WriteBigEndianShort(Stream& out, short  value);
	static Stream& WriteLittleEndianULong(Stream& out, uint32  value);
	static Stream& WriteBigEndianULong(Stream& out, uint32  value);
	static Stream& WriteLittleEndianLong(Stream& out, long   value);
	static Stream& WriteBigEndianLong(Stream& out, long   value);
	static Stream& WriteLittleEndianFloat(Stream& out, float  value);
	static Stream& WriteBigEndianFloat(Stream& out, float  value);
	static Stream& WriteLittleEndianDouble(Stream& out, float value);
	static Stream& WriteBigEndianDouble(Stream& out, float value);
	
	static String   KeyToPitchName(int key);
	
protected:
	// helper functions for reading ASCII content to conver to binary:
	int      ProcessLine(Stream& out, String input, int line_num);
	int      ProcessAsciiWord(Stream& out, String input, int line_num);
	int      ProcessStringWord(Stream& out, String input, int line_num);
	int      ProcessBinaryWord(Stream& out, String input, int line_num);
	int      ProcessDecimalWord(Stream& out, String input, int line_num);
	int      ProcessHexWord(Stream& out, String input, int line_num);
	int      ProcessVlvWord(Stream& out, String input, int line_num);
	int      ProcessPitchBendWord(Stream& out, String input, int line_num);
	int      ProcessTempoWord(Stream& out, String input, int line_num);
	        
	// helper functions for reading binary content to convert to ASCII:
	int      OutputStyleAscii(Stream& out, Stream& input);
	int      OutputStyleBinary(Stream& out, Stream& input);
	int      OutputStyleBoth(Stream& out, Stream& input);
	int      OutputStyle(Stream& out, Stream& input);
	
	// MIDI parsing helper functions:
	int      ReadEvent(Stream& out, Stream& infile, int& trackbytes, int& command);
	int      GetVLV(Stream& infile, int& trackbytes);
	int      GetWord(String& word, String input, String terminators, int index);
	                 
	                 
private:
	int bytes_q;         // option for printing hex bytes in ASCII output.
	int comments_q;      // option for printing comments in ASCII output.
	int midi_q;          // output ASCII data as parsed MIDI file.
	int max_line_length; // number of character in ASCII output on a line.
	int max_line_bytes;  // number of hex bytes in ASCII output on a line.
};


NAMESPACE_MIDI_END


#endif
