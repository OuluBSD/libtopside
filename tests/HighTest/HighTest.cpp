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

void SIC_Input(HiEscape& e)
{
    e = ReadStdIn();
}

void SIC_InputNumber(HiEscape& e)
{
    e = atof(ReadStdIn());
}

CONSOLE_APP_MAIN
{
    ArrayMap<String, HiValue> global;
    HighCall(global, "Print(x)", SIC_Print);
    HighCall(global, "Input()", SIC_Input);
    HighCall(global, "InputNumber()", SIC_InputNumber);
    StdLib(global);
    
    String dir = GetDataFile("");
	Vector<String> files;
	files << "Test0.high";
    
    for (String file : files) {
        String path = AppendFileName(dir, file);
	    LOG("Processing file: " << path);
        try {
	        Scan(global, LoadFile(path));
	        HiValue ret = Execute(global, "main", INT_MAX);
	        DUMP(ret);
	    }
	    catch(CParser::Error e) {
	        PRINT("ERROR: " << e << "\n");
	    }
    }
    
}
