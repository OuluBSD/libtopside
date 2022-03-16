#include "HighTest.h"

#include <High/High.h>

using namespace UPP;

#define PRINT(x) {Cout() << x; VppLog() << x;}

void SIC_Print(HiEscape& e)
{
    if(e[0].IsArray())
		PRINT((String) e[0])
    else
    if(e[0].IsNumber())
		PRINT(e[0].GetNumber())
    else
    if(!e[0].IsVoid())
		e.ThrowError("invalid argument to 'Print'");
}

void SIC_PrintLine(HiEscape& e)
{
    if(e[0].IsArray())
		PRINT((String) e[0] << "\n")
    else
    if(e[0].IsNumber())
		PRINT(e[0].GetNumber() << "\n")
    else
    if(!e[0].IsVoid())
		e.ThrowError("invalid argument to 'Print'");
}

void SIC_Input(HiEscape& e)
{
    e = ReadStdIn();
}

void SIC_InputNumber(HiEscape& e)
{
	float f = atof(ReadStdIn());
    e = f;
}

CONSOLE_APP_MAIN
{
    ArrayMap<String, HiValue> global;
    HighCall(global, "Print(x)", SIC_Print);
    HighCall(global, "Printl(x)", SIC_PrintLine);
    HighCall(global, "Input()", SIC_Input);
    HighCall(global, "InputNumber()", SIC_InputNumber);
    StdLib(global);
    
    String dir = GetDataFile("");
	Vector<String> files;
	files << "Test0.high";
	//files << "Test1.high";
	//files << "Test99.high";
    
    for (String file : files) {
        String path = AppendFileName(dir, file);
	    LOG("Processing file: " << path);
        try {
	        Scan(global, LoadFile(path), path);
	        HiValue ret = Execute(global, "main", INT_MAX);
	        DUMP(ret);
	    }
	    catch(Exc e) {
	        PRINT("ERROR: " << e << "\n");
	        break;
	    }
    }
    
}
