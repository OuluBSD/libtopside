#include "DxUtil.h"


// Description:  Logging functions.


static char						gldLogbuf[1024];
static FILE*					fpGLDLog = NULL;								// Log file pointer
static char						szGLDLogName[_MAX_PATH] = {GLDLOG_FILENAME};	// Filename of the log
static GLDLOG_loggingMethodType	gldLoggingMethod = GLDLOG_NONE;					// Default to No Logging
static GLDLOG_severityType		gldDebugLevel;
static BOOL						bUIWarning = FALSE;								// MessageBox warning ?

// ***********************************************************************

void gldLogOpen(
	GLDLOG_loggingMethodType LoggingMethod,
	GLDLOG_severityType Severity)
{
	if (fpGLDLog != NULL) {
		// Tried to re-open the log
		gldLogMessage(GLDLOG_WARN, "Tried to re-open the log file\n");
		return;
	}

	gldLoggingMethod	= LoggingMethod;
	gldDebugLevel		= Severity;

	if (gldLoggingMethod == GLDLOG_NORMAL) {
		fpGLDLog = fopen(szGLDLogName, "wt");
        if (fpGLDLog == NULL)
            return;
    }

	gldLogMessage(GLDLOG_SYSTEM, "-> Logging Started\n");
}

// ***********************************************************************

void gldLogClose()
{
	// Determine whether the log is already closed
	if (fpGLDLog == NULL && gldLoggingMethod == GLDLOG_NORMAL)
		return; // Nothing to do.

	gldLogMessage(GLDLOG_SYSTEM, "<- Logging Ended\n");

	if (gldLoggingMethod == GLDLOG_NORMAL) {
		fclose(fpGLDLog);
		fpGLDLog = NULL;
	}
}

// ***********************************************************************

void gldLogMessage(
	GLDLOG_severityType severity,
	LPSTR message)
{
	char buf[1024];

	// Bail if logging is disabled
	if (gldLoggingMethod == GLDLOG_NONE)
		return;

	if (gldLoggingMethod == GLDLOG_CRASHPROOF)
		fpGLDLog = fopen(szGLDLogName, "at");

	if (fpGLDLog == NULL)
		return;

	if (severity >= gldDebugLevel) {
		sprintf(buf, "GLD: (%s) %s", gldLogSeverityMessages[severity], message);
		fputs(buf, fpGLDLog); // Write string to file
		OutputDebugString(buf); // Echo to debugger
	}

	if (gldLoggingMethod == GLDLOG_CRASHPROOF) {
		fflush(fpGLDLog); // Write info to disk
		fclose(fpGLDLog);
		fpGLDLog = NULL;
	}

	// Popup message box if critical error
	if (bUIWarning && severity == GLDLOG_CRITICAL) {
		MessageBox(NULL, buf, "GLDirect", MB_OK | MB_ICONWARNING | MB_TASKMODAL);
	}
}

// ***********************************************************************

// Write a string value to the log file
void gldLogError(
	GLDLOG_severityType severity,
	LPSTR message,
	HRESULT hResult)
{
	char dxErrStr[1024];
	_gldDriver.GetDXErrorString(hResult, &dxErrStr[0], sizeof(dxErrStr));
	if (FAILED(hResult)) {
		sprintf(gldLogbuf, "GLD: %s %8x:[ %s ]\n", message, hResult, dxErrStr);
	} else
		sprintf(gldLogbuf, "GLD: %s\n", message);
	gldLogMessage(severity, gldLogbuf);
}

// ***********************************************************************

void gldLogPrintf(
	GLDLOG_severityType severity,
	LPSTR message,
	...)
{
	va_list args;

	va_start(args, message);
	vsprintf(gldLogbuf, message, args);
	va_end(args);

	lstrcat(gldLogbuf, "\n");

	gldLogMessage(severity, gldLogbuf);
}

// ***********************************************************************

void gldLogWarnOption(
	BOOL bWarnOption)
{
	bUIWarning = bWarnOption;
}

// ***********************************************************************

void gldLogPathOption(
	LPSTR szPath)
{
	char szPathName[_MAX_PATH];

	strcpy(szPathName, szPath);
    strcat(szPathName, "\\");
    strcat(szPathName, szGLDLogName);
    strcpy(szGLDLogName, szPathName);
}

// ***********************************************************************
