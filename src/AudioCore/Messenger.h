#ifndef _AudioCore_MESSAGER_H
#define _AudioCore_MESSAGER_H


NAMESPACE_AUDIO_BEGIN


const int DEFAULT_QUEUE_LIMIT = 200;

class Messenger : public Audio {
public:

	struct MessengerData {
		Script skini;
		Vector<Script::Message> queue;
		int queueLimit;
		int sources;

		MessengerData()
			: queueLimit(0), sources(0) {}
	};

	Messenger();
	~Messenger();
	void PopMessage( Script::Message& message );
	void PushMessage( Script::Message& message );
	void PushMessage( const String& message );
	bool SetScoreFile( const char* filename );

protected:

	MessengerData data_;
	SpinLock lock;
	Script script;
};

NAMESPACE_AUDIO_END

#endif
