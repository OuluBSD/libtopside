#ifndef _CommandBridge_Console_h_
#define _CommandBridge_Console_h_

#include "CommandPrompt.h"
#include "Word.h"

class CommandBridge;

class Console : public ParentCtrl {
	
protected:
	CommandPrompt cmd;
	Word wordapp;
	
	#ifdef flagHAVE_FTP
	One<FTPServer> ftpd;
	#endif
	
	CommandBridge* bridge = NULL;
	int id = -1;
	
	ArrayMap<String, Callback1<String> > commands;
	String out, err;
	String cwd;
	int view = VIEW_CMD;
	
	enum {VIEW_CMD, VIEW_WORD};
	void SetView(int i);
	void SetTitle(String s);
	
public:
	typedef Console CLASSNAME;
	Console();
	
	void AddProgram(String cmd, Callback1<String> cb);
	String Command(const String& cmd);
	
	void ListFiles(String arg);
	void ChangeDirectory(String arg);
	void CreateDirectory(String arg);
	void RemoveFile(String arg);
	void ShowFile(String arg);
	void EditFile(String arg);
	void DownloadFile(String arg);
	
	#ifdef flagHAVE_FTP
	void StartFtpServer(String arg);
	#endif
	
	void Menu(Bar& bar);
	String GetMenuTitle();
	String GetTitle();
	
	inline void Put(const String& s)		{out << s;}
	inline void PutLine(const String& s)	{out << s << "\n";}
	const String& GetOutput() const			{return out;}
	const String& GetError() const			{return err;}
	
	void SetBridge(CommandBridge* bridge, int id) {this->bridge = bridge; this->id = id;}
	
	Callback WhenTitle;
	Callback WhenViewChange;
	
};

#endif
