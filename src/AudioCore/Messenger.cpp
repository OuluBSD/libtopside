#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN



typedef int MessengerSourceType;
MessengerSourceType AUDIO_FILE   = 0x1;
MessengerSourceType AUDIO_MIDI   = 0x2;
MessengerSourceType AUDIO_STDIN   = 0x4;
MessengerSourceType AUDIO_SOCKET = 0x8;

Messenger::Messenger() {
	data_.sources = 0;
	data_.queueLimit = DEFAULT_QUEUE_LIMIT;
}

Messenger::~Messenger() {
	data_.sources = 0;
}

bool Messenger::SetScoreFile( const char* filename ) {
	if ( data_.sources ) {
		if ( data_.sources == AUDIO_FILE ) {
			LOG("Messenger::SetScoreFile: already reading a scorefile!");
			HandleError( AudioError::WARNING );
		}
		else {
			LOG("Messenger::SetScoreFile: already reading realtime Control input ... cannot do scorefile input too!");
			HandleError( AudioError::WARNING );
		}

		return false;
	}

	if ( !data_.skini.SetFile( filename ) ) return false;

	data_.sources = AUDIO_FILE;
	return true;
}

void Messenger::PopMessage( Script::Message& message ) {
	if ( data_.sources == AUDIO_FILE ) {
		if ( !data_.skini.NextMessage( message ) )
			message.type = __SK_Exit_;

		return;
	}

	if ( data_.queue.GetCount() == 0 ) {
		message.type = 0;
		return;
	}
	
	lock.Enter();
	message = data_.queue[0];
	data_.queue.Remove(0);
	lock.Leave();
}

void Messenger::PushMessage( Script::Message& message ) {
	lock.Enter();
	data_.queue.Add( message );
	lock.Leave();
}

void Messenger::PushMessage( const String& message ) {
	Script::Message msg;
	script.ParseString(message, msg);
	if (msg.type)
		PushMessage(msg);
}

NAMESPACE_AUDIO_END

