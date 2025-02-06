#include "ToolCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


Tasks::Tasks() {
	Add(hsplit.SizePos());
	#if 0
	Add(hsplit.HSizePos().VSizePos(0,30));
	Add(lbl.LeftPos(5, 200-5).BottomPos(0,30));
	Add(prog.HSizePos(200,0).BottomPos(0,30));
	prog.Set(0,1);
	lbl.SetLabel(t_("Idle"));
	#endif
	
	hsplit.Horz() << list << vsplit;
	vsplit.Vert() << input << output;
	
	list.AddColumn(t_("#"));
	list.AddColumn(t_("Description"));
	list.AddColumn(t_("Status"));
	list.ColumnWidths("1 4 4");
	list <<= THISBACK(DataTask);
	
	output <<= THISBACK(ValueChange);
	
	list.WhenBar	<< THISBACK(OutputMenu);
	
}

void Tasks::Data() {
	TaskMgr& m = TaskMgr::Single();
	
	for(int i = 0; i < m.tasks.GetCount(); i++) {
		AiTask& t = m.tasks[i];
		list.Set(i, 0, i);
		list.Set(i, 1, t.GetDescription());
		String s;
		if (t.failed)
			s = t_("Error") + String(": ") + t.error;
		else if (t.processing)
			s = t_("Processing");
		else if (t.ready)
			s = t_("Ready");
		if (t.tries > 0)
			s << " (" << t_("tries") << " " << t.tries << ")";
		list.Set(i, 2, s);
	}
	list.SetCount(m.tasks.GetCount());
	
	int cursor = 0;
	if (!list.IsCursor() && cursor >= 0 && cursor < list.GetCount())
		list.SetCursor(cursor);
	
	#if 0
	prog.Set(m.actual, max(1,m.total));
	lbl.SetLabel(m.status.IsEmpty() ? String(t_("Idle")) : m.status);
	#endif
	
	DataTask();
}

void Tasks::DataTask() {
	TaskMgr& m = TaskMgr::Single();
	
	if (!list.IsCursor())
		return;
	
	int cursor = list.GetCursor();
	AiTask& t = m.tasks[cursor];
	m.active_task = &t;
	
	if (cursor != data_cursor || (output.GetLength() == 0 && t.output.GetCount())) {
		if (t.raw_input.GetCount())
			input.SetData(t.raw_input);
		else
			input.SetData(t.input.AsString().ToWString());
		output.SetData(t.output.ToWString());
		data_cursor = cursor;
	}
}

void Tasks::ValueChange() {
	TaskMgr& m = TaskMgr::Single();
	
	if (!m.active_task)
		return;
	
	AiTask& t = *m.active_task;
	t.output = TrimBoth(output.GetData());
	t.changed = true;
	t.output.Replace("\r", "");
	
	t.Store();
}

void Tasks::ProcessItem() {
	TaskMgr& m = TaskMgr::Single();
	
	if (!list.IsCursor())
		return;
	int cursor = list.GetCursor();
	AiTask& t = m.tasks[cursor];
	t.failed = false;
	m.StartSingle(cursor);
}

void Tasks::RetryItem(bool skip_prompt, bool skip_cache) {
	TaskMgr& m = TaskMgr::Single();
	
	if (!list.IsCursor())
		return;
	int cursor = list.GetCursor();
	AiTask& t = m.tasks[cursor];
	t.Retry(skip_prompt, skip_cache);
	m.StartSingle(cursor);
	this->output.Clear();
}

void Tasks::ReturnFail() {
	TaskMgr& m = TaskMgr::Single();
	
	if (!list.IsCursor())
		return;
	int cursor = list.GetCursor();
	AiTask& t = m.tasks[cursor];
	t.ReturnFail();
	this->output.SetData("fail");
}


void Tasks::OutputMenu(Bar& bar) {
	bar.Add(t_("Process output"), THISBACK(ProcessItem));
	bar.Add(t_("Retry"), THISBACK2(RetryItem, false, false));
	bar.Add(t_("Retry cached prompt"), THISBACK2(RetryItem, true, false));
	bar.Add(t_("Retry and skip cache"), THISBACK2(RetryItem, false, true));
	bar.Add(t_("Return fail"), THISBACK(ReturnFail));
	
}


END_TEXTLIB_NAMESPACE
