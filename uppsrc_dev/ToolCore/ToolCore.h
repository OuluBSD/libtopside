#ifndef _ToolCore_ToolCore_h_
#define _ToolCore_ToolCore_h_

#include <CtrlLib/CtrlLib.h>
#include <CodeEditor/CodeEditor.h>
#include <Esc/Esc.h>
#include <plugin/jpg/jpg.h>
#define TFILE <TopTool/TopTool.t>
#include <Core/t.h>
#include <BlueBar/BlueBar.h>
#include <RedBar/RedBar.h>
using namespace Upp;


#define IMAGECLASS AppImg
#define IMAGEFILE <ToolCore/App.iml>
#include <Draw/iml_header.h>


#define BEGIN_TEXTLIB_NAMESPACE namespace TextLib {
#define END_TEXTLIB_NAMESPACE }

#define BEGIN_SOCIALLIB_NAMESPACE namespace SocialLib {
#define END_SOCIALLIB_NAMESPACE }


#include "OpenAI.h"

#include "Utils.h"
#include "Optimizer.h"

#include "Common.h"
#include "FileClasses.h"
#include "Tokenizer.h"


#endif
