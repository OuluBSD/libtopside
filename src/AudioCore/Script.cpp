#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN



Script::Script() {
}

Script::~Script() {
}

bool Script::SetFile( String file_name ) {
	if ( file_.IsOpen() ) {
		LOG("Script::SetFile: already reaading a file!");
		HandleError( AudioError::WARNING );
		return false;
	}

	file_.Open( file_name.Begin() );

	if ( !file_ ) {
		LOG("Script::SetFile: unable to open file (" << file_name << ")");
		HandleError( AudioError::WARNING );
		return false;
	}

	return true;
}

long Script::NextMessage( Message& message ) {
	if ( !file_.IsOpen() ) return 0;

	String line;
	bool done = false;

	while ( !done ) {
		line = file_.GetLine();

		if ( line.GetCount() == 0 && file_.IsEof() ) {
			LOG("// End of Score.  Thanks for using SCRIPT!!");
			HandleError( AudioError::STATUS );
			file_.Close();
			message.type = 0;
			done = true;
		}
		else if ( ParseString( line, message ) > 0 ) done = true;
	}

	return message.type;
}

void Script::Tokenize( const String&        str,
						 Vector<String>& tokens,
						 const String&        delimiters ) {
	int lastPos = FindFirstNotOf(str, delimiters, 0);
	int pos     = FindFirstOf(str, delimiters, lastPos);

	while (-1 != pos || -1 != lastPos) {
		tokens.Add(str.Mid(lastPos, pos - lastPos));
		lastPos = FindFirstNotOf(str, delimiters, pos);
		pos = FindFirstOf(str, delimiters, lastPos);
		if (pos == -1) {
			tokens.Add(str.Mid(lastPos));
			break;
		}
	}
}

long Script::ParseString(const String& line, Message& message ) {
	message.type = 0;

	if ( line.IsEmpty() ) return message.type;

	int lastPos = FindFirstNotOf(line, " ,\t", 0);
	int pos     = FindFirstOf(line, "/", lastPos);

	if ( -1 != pos ) {
		LOG("// Comment Line: " << line);
		HandleError( AudioError::STATUS );
		return message.type;
	}

	Vector<String> tokens;
	this->Tokenize( line, tokens, " ,\t");

	if ( tokens.GetCount() < 3 ) return message.type;

	int iScript = 0;

	while ( iScript < __SK_MaxMsgTypes_ ) {
		if ( tokens[0] == skini_msgs[iScript].messageString ) break;

		iScript++;
	}

	if ( iScript >= __SK_MaxMsgTypes_ )  {
		LOG("Script::ParseString: couldn't parse this line:\n   " << line);
		HandleError( AudioError::WARNING );
		return message.type;
	}

	message.type = skini_msgs[iScript].type;

	if ( tokens[1][0] == '=' ) {
		tokens[1].Remove( 0 );

		if ( tokens[1].IsEmpty() ) {
			LOG("Script::ParseString: couldn't parse time field in line:\n   " << line);
			HandleError( AudioError::WARNING );
			return message.type = 0;
		}

		message.time = (float) - atof( tokens[1].Begin() );
	}
	else
		message.time = (float) atof( tokens[1].Begin() );

	message.channel = atoi( tokens[2].Begin() );
	int iValue = 0;
	long dataType = skini_msgs[iScript].data2;

	while ( dataType != NOPE ) {
		if ( tokens.GetCount() <= (int) (iValue + 3) ) {
			LOG( "WARNING: Script::ParseString: inconsistency between type table and parsed line:\n   " << line);
			HandleError( AudioError::WARNING );
			return message.type = 0;
		}

		switch ( dataType ) {
		case SK_INT:
			message.int_values[iValue] = atoi( tokens[iValue + 3].Begin() );
			message.float_values[iValue] = (float) message.int_values[iValue];
			break;

		case SK_DBL:
			message.float_values[iValue] = atof( tokens[iValue + 3].Begin() );
			message.int_values[iValue] = (long) message.float_values[iValue];
			break;

		case SK_STR:
			message.remainder = tokens[iValue + 3];
			return message.type;

		default:
			message.int_values[iValue] = dataType;
			message.float_values[iValue] = (float) message.int_values[iValue];
			iValue--;
		}

		if ( ++iValue == 1 )
			dataType = skini_msgs[iScript].data3;
		else
			dataType = NOPE;
	}

	return message.type;
}

String Script::whatsThisType(long type) {
	String typeString;

	for ( int i = 0; i < __SK_MaxMsgTypes_; i++ ) {
		if ( type == skini_msgs[i].type ) {
			typeString = skini_msgs[i].messageString;
			break;
		}
	}

	return typeString;
}

String Script::whatsThisController( long number ) {
	String Controller;

	for ( int i = 0; i < __SK_MaxMsgTypes_; i++) {
		if ( skini_msgs[i].type == __SK_ControlChange_ &&
			 number == skini_msgs[i].data2) {
			Controller = skini_msgs[i].messageString;
			break;
		}
	}

	return Controller;
}

NAMESPACE_AUDIO_END
