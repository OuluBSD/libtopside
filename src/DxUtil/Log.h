#ifndef __GLD_LOG_H
#define __GLD_LOG_H


// Description:  Logging functions.


#include <stdio.h>

/*---------------------- Macros and type definitions ----------------------*/

#define GLDLOG_FILENAME	"gldirect.log"

typedef enum {
	GLDLOG_NONE					= 0,			// No log output
	GLDLOG_NORMAL				= 1,			// Log is kept open
	GLDLOG_CRASHPROOF			= 2,			// Log is closed and flushed
	GLDLOG_METHOD_FORCE_DWORD	= 0x7fffffff,
} GLDLOG_loggingMethodType;

// Denotes type of message sent to the logging functions
typedef enum {
	GLDLOG_INFO					= 0,			// Information only
	GLDLOG_WARN					= 1,			// Warning only
	GLDLOG_ERROR				= 2,			// Notify user of an error
	GLDLOG_CRITICAL				= 3,			// Exceptionally severe error
	GLDLOG_SYSTEM				= 4,			// System message. Not an error
												// but must always be printed.
	GLDLOG_SEVERITY_FORCE_DWORD	= 0x7fffffff,	// Make enum dword
} GLDLOG_severityType;

// The message that will be output to the log
static const char *gldLogSeverityMessages[] = {
	"INF",	// Info
	"WRN",	// Warn
	"ERR",	// Error
	"CRI",	// Critical
	"SYS",	// System
};

/*------------------------- Function Prototypes ---------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

void gldLogOpen(GLDLOG_loggingMethodType LoggingMethod, GLDLOG_severityType Severity);
void gldLogClose();
void gldLogMessage(GLDLOG_severityType severity, LPSTR message);
void gldLogError(GLDLOG_severityType severity, LPSTR message, HRESULT hResult);
void gldLogPrintf(GLDLOG_severityType severity, LPSTR message, ...);
void gldLogWarnOption(BOOL bWarnOption);
void gldLogPathOption(LPSTR szPath);

#ifdef  __cplusplus
}
#endif

#endif