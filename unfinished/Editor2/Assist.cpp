#include "Editor.h"



Assist::Assist(IDE* ide) : ide(ide) {
	ide = 0;
	
	SetRect(0,0,640,0);
	
	Add(tabs.VSizePos().HSizePos());
	tabs.Add(nice_split, "Nice");
	tabs.Add(nice_split);
	tabs.Add(split, "Detailed");
	tabs.Add(split);
	
	
	nice_split.Vert();
	nice_split << nice_completions;
	
	nice_completions.AddColumn("");
	nice_completions.AddColumn("");
	
	
	
	split.Vert();
	split << completions << diagnostics << misc;
	
	completions.AddColumn("Key");
	completions.AddColumn("Value");
	
	diagnostics.AddColumn("Key");
	diagnostics.AddColumn("Value");
	
	misc.AddColumn("Key");
	misc.AddColumn("Value");
	
	
}

void Assist::RefreshNiceData() {
	nice_completions.Clear();
	nice_diagnostics.Clear();
	nice_misc.Clear();
	
	Translation::Unit& unit = ide->GetProject().GetTranslator().GetUnit(path);
	CodeEdit& code = ide->GetEditor().GetOpenEditor();
	
	int off;
	String variable = code.GetVariable(line, column, &off);
	String content = code.GetData();
	
	ArrayMap<uint32, Translation::Cursor> cc = unit.GetCodeCompletion(path, line, column - off, content);
	
	
	nice_completions.Add(off);
	nice_completions.Add(variable);

	int c1 = cc.GetCount();
	for(int i = 0; i < c1; i++) {
		Translation::Cursor cursor = cc[i];
		Translation::Type t = cursor.GetType();
		if (cursor.GetDisplayName().Left(variable.GetCount()) != variable)
			continue;
		
		String s = IntStr(i);
		nice_completions.Add(s + "-type-kind", t.GetKind());
		nice_completions.Add(s + "-type-name", t.GetName());
		nice_completions.Add(s + "-name", cursor.GetName());
		nice_completions.Add(s + "-display-name", cursor.GetDisplayName());
		nice_completions.Add(s + "-comment", cursor.GetComment());
		
		int c2 = cursor.GetArgumentCount();
		misc.Add(s + "-arg-count", c2);
		for(int j = 0; j < c2; j++) {
			
			Translation::Cursor arg = cursor.GetArgument(j);
			String c = s + "-arg-" + IntStr(j);
			misc.Add(c + "-kind", arg.GetKind());
			misc.Add(c + "-text", arg.GetName());
			misc.Add(c + "-comment", arg.GetComment());
		}
	}
	
}

void Assist::RefreshData() {
	if (tabs.Get() == 0) {
		RefreshNiceData();
		return;
	}
	
	completions.Clear();
	diagnostics.Clear();
	misc.Clear();
	
	
	Translation::Unit& unit = ide->GetProject().GetTranslator().GetUnit(path);
	String content = ide->GetEditor().GetOpenEditor().GetData(); // TODO: fix after U++... not efficient now
	ArrayMap<uint32, Translation::Cursor> cc = unit.GetCodeCompletion(path, line, column, content);
	
	
	int c1 = cc.GetCount();
	
	for(int i = 0; i < c1; i++) {
		Translation::Cursor cursor = cc[i];
		Translation::Type t = cursor.GetType();
		String s = IntStr(i);
		completions.Add(s + "-type-kind", t.GetKind());
		completions.Add(s + "-type-name", t.GetName());
		completions.Add(s + "-name", cursor.GetName());
		completions.Add(s + "-display-name", cursor.GetDisplayName());
		completions.Add(s + "-comment", cursor.GetComment());
		
		int c2 = cursor.GetArgumentCount();
		completions.Add(s + "-arg-count", c2);
		for(int j = 0; j < c2; j++) {
			
			Translation::Cursor arg = cursor.GetArgument(j);
			String c = s + "-arg-" + IntStr(j);
			completions.Add(c + "-kind", arg.GetKind());
			completions.Add(c + "-text", arg.GetName());
			completions.Add(c + "-comment", arg.GetComment());
		}
	}
	
	Translation::File path_file = unit.GetFile(path);
	Array<Translation::Range> includes = unit.GetIncludes(path_file);
	diagnostics.Add("include-count", includes.GetCount());
	for(int i = 0; i < includes.GetCount(); i++) {
		Translation::Range& r = includes[i];
		Translation::Location loc = r.Begin();
		Translation::Cursor cur = loc.GetCursor(unit);
		String s = "include-" + IntStr(i);
		//diagnostics.Add(s + "-name", cur.GetName());
		diagnostics.Add(s + "-display-name", cur.GetDisplayName());
	}
	
	
	
	
	Translation::DiagnosticSet diagset = unit.GetDiagnostics();
	c1 = diagset.GetCount();
	for(int i = 0; i < c1; i++) {
		Translation::Diagnostic diag = diagset[i];
		String s = "diagnostic-" + IntStr(i);
		diagnostics.Add(s + "-severity", diag.GetSeverity());
		diagnostics.Add(s + "-spelling", diag.GetSpelling());
		diagnostics.Add(s + "-category-text", diag.GetCategoryText());
		diagnostics.Add(s + "-category-num", diag.GetCategoryNum());
		diagnostics.Add(s + "-options", diag.GetOptions());
		diagnostics.Add(s + "-trigger-option", diag.GetTriggerOption());
		
	}
	
	Translation::Type t = cursor.GetType();
	Translation::Type srctype = t.GetSourceType();
	Translation::Type pointee = t.GetPointeeType();
	Translation::Type ptrtype = t.GetTypeFromPointer();
	Translation::Type restype = t.GetResultType();
	
	Translation::Cursor src = cursor.GetSourceTemplate();
	Translation::Type srctempltype = src.GetType();
	
	Translation::Cursor def = cursor.GetDefinition();
	Translation::Type deftype = def.GetType();
	
	Translation::Cursor ref = cursor.GetReferenced();
	Translation::Type reftype = ref.GetType();
	
	Translation::Cursor sem = cursor.GetSemanticParent();
	Translation::Type semtype = ref.GetType();
	
	Translation::Cursor lex = cursor.GetLexicalParent();
	Translation::Type lextype = ref.GetType();
	
	
	Array<Translation::Range> refs = unit.GetReferences(path_file, path_file, line, column);
	misc.Add("reference-count", refs.GetCount());
	for(int i = 0; i < refs.GetCount(); i++) {
		Translation::Range& r = refs[i];
		Translation::Location loc = r.Begin();
		Translation::Cursor cur = loc.GetCursor(unit);
		String s = "reference-" + IntStr(i);
		misc.Add(s + "-name", cur.GetName());
		misc.Add(s + "-display-name", cur.GetDisplayName());
	}
	
	misc.Add("type-kind", t.GetKind());
	misc.Add("type-name", t.GetName());
	misc.Add("name", cursor.GetName());
	misc.Add("display-name", cursor.GetDisplayName());
	misc.Add("comment", cursor.GetComment());
	misc.Add("pointee-type-kind", pointee.GetKind());
	misc.Add("pointee-type-name", pointee.GetName());
	misc.Add("pointer-type-kind", ptrtype.GetKind());
	misc.Add("pointer-type-name", ptrtype.GetName());
	misc.Add("source-type-kind", srctype.GetKind());
	misc.Add("source-type-name", srctype.GetName());
	misc.Add("result-type-kind", srctype.GetKind());
	misc.Add("result-type-name", srctype.GetName());
	misc.Add("source-template-type-kind", srctempltype.GetKind());
	misc.Add("source-template-type-name", srctempltype.GetName());
	misc.Add("source-template-name", src.GetName());
	misc.Add("source-template-display-name", src.GetDisplayName());
	misc.Add("definition-type-kind", deftype.GetKind());
	misc.Add("definition-type-name", deftype.GetName());
	misc.Add("definition-name", def.GetName());
	misc.Add("definition-display-name", def.GetDisplayName());
	misc.Add("reference-type-kind", reftype.GetKind());
	misc.Add("reference-type-name", reftype.GetName());
	misc.Add("reference-name", ref.GetName());
	misc.Add("reference-display-name", ref.GetDisplayName());
	misc.Add("semantic-parent-type-kind", semtype.GetKind());
	misc.Add("semantic-parent-type-name", semtype.GetName());
	misc.Add("semantic-parent-name", sem.GetName());
	misc.Add("semantic-parent-display-name", sem.GetDisplayName());
	misc.Add("lexical-parent-type-kind", lextype.GetKind());
	misc.Add("lexical-parent-type-name", lextype.GetName());
	misc.Add("lexical-parent-name", lex.GetName());
	misc.Add("lexical-parent-display-name", lex.GetDisplayName());
	
	
	misc.Add("---Code", "Completion---");
	
	c1 = cursor.GetArgumentCount();
	misc.Add("argument-count", c1);
	for(int i = 0; i < c1; i++) {
		Translation::Cursor a = cursor.GetArgument(i);
		Translation::Type at = a.GetType();
		String arg = "argument-" + IntStr(i);
		misc.Add(arg + "-type-kind", at.GetKind());
		misc.Add(arg + "-type-name", at.GetName());
		misc.Add(arg + "-name", a.GetName());
		misc.Add(arg + "-display-name", a.GetDisplayName());
	}
	Translation::Completion comp = cursor.GetCompletion();
	
	c1 = comp.GetAnnotationCount();
	misc.Add("annotation-count", c1);
	for(int i = 0; i < c1; i++) {
		String a = "annotation-" + IntStr(i);
		misc.Add(a, comp.GetAnnotation(i));
	}
	
	c1 = comp.GetChunkCount();
	misc.Add("chunk-count", c1);
	for(int i = 0; i < c1; i++) {
		Translation::Completion chunk = comp.GetChunkCompletion(i);
		String c = "chunk-" + IntStr(i);
		misc.Add(c + "-kind", comp.GetChunkText(i));
		misc.Add(c + "-text", comp.GetChunkKind(i));
		misc.Add(c + "-comment", chunk.GetBriefComment());
		misc.Add(c + "-chunk-count", chunk.GetChunkCount());
		
		
		int c2 = chunk.GetAnnotationCount();
		misc.Add(c + "-annotation-count", c2);
		for(int i = 0; i < c2; i++) {
			String a = c + "-annotation-" + IntStr(i);
			misc.Add(a, chunk.GetAnnotation(i));
		}
	}
}

void Assist::SetCursor(const String& path, int line, int column, Translation::Cursor cursor) {
	this->cursor = cursor;
	this->path = path;
	this->line = line;
	this->column = column;
	RefreshData();
}

bool Assist::Key(dword key, int count)
{
	//LOG(Format("Key(%x, %d) ", (int)key, count));
	//if (key == K_ESCAPE || key == 120020 || key == K_ENTER)
	//	Close();
	
	return false;
}

