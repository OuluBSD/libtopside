#ifndef _ToyHub_Server_h_
#define _ToyHub_Server_h_


NAMESPACE_TOYHUB_BEGIN


void OpenSQL();
const XmlNode& TryOpenLocation(String pos, const XmlNode& root, int& errorcode);
String XmlTreeString(const XmlNode& node, int indent=0, String prev_addr="");
String GetHubPath(String file);
void LoadDefaultHub(String db_name="toyhub", String lang="en");

class ToyServer : public SkylarkApp {
	
public:
	virtual void WorkThread();

	typedef ToyServer CLASSNAME;
	ToyServer();
	
};

inline ToyServer& GetToyServer() {return Single<ToyServer>();}

void ServerInit();
void RunToyHub();
void StopToyHub();
bool HasHomePageConnection();

Value GetLastError();
void SetLastError(Value v);
bool SetPage(const Hub& hub, const User& user, String title, String text, String lang, String model, String format);


NAMESPACE_TOYHUB_END


#endif
