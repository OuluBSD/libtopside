#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


void DatabaseBrowser::RealizeUniqueAttrs() {
	if (!uniq_attr.IsEmpty())
		return;
	
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	uniq_attr_values.Clear();
	for(int i = 0; i < da.phrase_parts.GetCount(); i++) {
		const PhrasePart& pp = da.phrase_parts[i];
		if (pp.attr < 0)
			continue;
		const auto& ah = da.attrs.GetKey(pp.attr);
		uniq_attr.GetAdd(ah.group).GetAdd(ah.value, 0)++;
		uniq_attr_values.GetAdd(ah.value,0)++;
	}
	SortByValue(uniq_attr, VMapSumSorter());
	for (auto& v : uniq_attr.GetValues())
		SortByValue(v, StdGreater<int>());
}

void DatabaseBrowser::RealizeUniqueActions() {
	if (!uniq_acts.IsEmpty())
		return;
	
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	uniq_act_args.Clear();
	for(int i = 0; i < da.phrase_parts.GetCount(); i++) {
		const PhrasePart& pp = da.phrase_parts[i];
		for (int act_i : pp.actions) {
			const auto& ah = da.actions.GetKey(act_i);
			uniq_acts.GetAdd(ah.action).GetAdd(ah.arg, 0)++;
			uniq_act_args.GetAdd(ah.arg,0)++;
		}
	}
	SortByValue(uniq_acts, VMapSumSorter());
	for (auto& v : uniq_acts.GetValues())
		SortByValue(v, StdGreater<int>());
}

void DatabaseBrowser::SetInitialData() {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	phrase_parts.SetCount(da.phrase_parts.GetCount());
	int i = 0;
	for (int& pp_i : phrase_parts)
		pp_i = i++;
}

void DatabaseBrowser::FilterNextFrom(ColumnType t) {
	int cursor = GetColumnOrder(t);
	for(int i = cursor; i < (int)TYPE_COUNT; i++) {
		FilterData(order[i]);
	}
}

void DatabaseBrowser::FilterAll() {
	for(int i = 0; i < (int)TYPE_COUNT; i++)
		FilterData(order[i]);
}

void DatabaseBrowser::SetColumnCursor(ColumnType t, int i) {
	int c = GetColumnOrder(t);
	if (i >= 0 && i < items[c].GetCount()) {
		cursor[c] = i;
		history.GetAdd(GetHash(c)) = i;
	}
}

void DatabaseBrowser::FillItems(ColumnType t) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	int c = GetColumnOrder(t);
	if (c > 0)
		RemoveExcessData(c);
	
	auto& type_items = items[c];
	type_items.SetCount(1);
	
	Item& it = type_items[0];
	it.str = "All";
	it.count = phrase_parts.GetCount();
	it.idx = -1;
	
	switch (t) {
		case ELEMENT: {
			VectorMap<int,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				if (pp.el_i >= 0)
					vmap.GetAdd(pp.el_i,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				int el_id = vmap.GetKey(i);
				Item& it = type_items[1+i];
				it.str = da.element_keys[el_id];
				it.count = vmap[i];
				it.idx = el_id;
			}
			break;
		}
		case ATTR_GROUP: {
			VectorMap<String,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				if (pp.attr < 0)
					continue;
				const AttrHeader& ah = da.attrs.GetKey(pp.attr);
				vmap.GetAdd(ah.group,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				it.str = vmap.GetKey(i);
				it.count = vmap[i];
				it.idx = -1;
			}
			break;
		}
		case ATTR_VALUE: {
			VectorMap<String,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				if (pp.attr < 0)
					continue;
				const AttrHeader& ah = da.attrs.GetKey(pp.attr);
				vmap.GetAdd(ah.value,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				it.str = vmap.GetKey(i);
				it.count = vmap[i];
				it.idx = -1;
			}
			break;
		}
		case COLOR: {
			VectorMap<int,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				int clr_i = GetColorGroup(pp.clr);
				vmap.GetAdd(clr_i,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				int clr_i = vmap.GetKey(i);
				it.str = "#" + IntStr(clr_i);
				it.count = vmap[i];
				it.idx = clr_i;
			}
			break;
		}
		case ACTION: {
			VectorMap<String,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				for (int act_i : pp.actions) {
					const ActionHeader& ah = da.actions.GetKey(act_i);
					vmap.GetAdd(ah.action,0)++;
				}
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				it.str = vmap.GetKey(i);
				it.count = vmap[i];
				it.idx = -1;
			}
			break;
		}
		case ACTION_ARG: {
			VectorMap<String,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				for (int act_i : pp.actions) {
					const ActionHeader& ah = da.actions.GetKey(act_i);
					vmap.GetAdd(ah.arg,0)++;
				}
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				it.str = vmap.GetKey(i);
				it.count = vmap[i];
				it.idx = -1;
			}
			break;
		}
		case TYPECLASS: {
			VectorMap<int,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				for (int tc : pp.typecasts)
					vmap.GetAdd(tc,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				int tc = vmap.GetKey(i);
				TODO //it.str = GetTypeclasses()[tc];
				it.count = vmap[i];
				it.idx = tc;
			}
			break;
		}
		case CONTENT: {
			VectorMap<int,int> vmap;
			for (int pp_i : phrase_parts) {
				const PhrasePart& pp = da.phrase_parts[pp_i];
				for (int con : pp.contrasts)
					vmap.GetAdd(con,0)++;
			}
			SortByValue(vmap, StdGreater<int>());
			type_items.SetCount(1+vmap.GetCount());
			TODO/*const auto& cons = GetContents();
			for(int i = 0; i < vmap.GetCount(); i++) {
				Item& it = type_items[1+i];
				int tc = vmap.GetKey(i);
				int tc_i = tc / 3;
				int mod_i = tc % 3;
				if (tc_i < cons.GetCount()) {
					const auto& con = cons[tc_i];
					it.str = con.key + ": " + con.parts[mod_i];
				}
				else it.str = "<Error>";
				it.count = vmap[i];
				it.idx = tc;
			}*/
			break;
		}
		default: TODO break;
	}
	
}

void DatabaseBrowser::SetAttrGroup(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	RealizeUniqueAttrs();
	
	auto& attr_groups = Get(ATTR_GROUP);
	if (IsFirstInOrder(ATTR_GROUP)) {
		SetInitialData();
	}
	else {
		FillItems(ATTR_GROUP);
	}
	SetColumnCursor(ATTR_GROUP, i);
}

void DatabaseBrowser::SetAttrValue(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	RealizeUniqueAttrs();
	
	auto& attr_values = Get(ATTR_VALUE);
	if (IsFirstInOrder(ATTR_VALUE)) {
		SetInitialData();
	}
	else {
		FillItems(ATTR_VALUE);
	}
	SetColumnCursor(ATTR_VALUE, i);
}

void DatabaseBrowser::SetColor(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& colors = Get(COLOR);
	
	if (IsFirstInOrder(COLOR)) {
		/*colors.SetCount(1 + GetColorGroupCount());
		Item& a = colors[0];
		a.str = "All";
		a.idx = -1;
		a.count = da.phrase_parts.GetCount();
		for(int i = 0; i < GetColorGroupCount(); i++) {
			Item& a = colors[1+i];
			a.str = "#" + IntStr(i);
			a.idx = i;
			a.count = color_counts[i];
		}*/
		SetInitialData();
	}
	else {
		FillItems(COLOR);
	}
	SetColumnCursor(COLOR, i);
}

void DatabaseBrowser::SetAction(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& actions = Get(ACTION);
	int cur = GetColumnCursor(ACTION);
	
	RealizeUniqueActions();
	
	if (IsFirstInOrder(ACTION)) {
		SetInitialData();
	}
	else {
		FillItems(ACTION);
	}
	SetColumnCursor(ACTION, i);
}

void DatabaseBrowser::SetActionArg(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& args = Get(ACTION_ARG);
	int cur = GetColumnCursor(ACTION_ARG);
	
	RealizeUniqueActions();
	
	if (IsFirstInOrder(ACTION_ARG)) {
		SetInitialData();
	}
	else {
		FillItems(ACTION_ARG);
	}
	SetColumnCursor(ACTION_ARG, i);
}

void DatabaseBrowser::SetElement(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& elements = Get(ELEMENT);
	int cur = GetColumnCursor(ELEMENT);
	
	RealizeUniqueActions();
	
	if (IsFirstInOrder(ELEMENT)) {
		SetInitialData();
	}
	else {
		FillItems(ELEMENT);
	}
	SetColumnCursor(ELEMENT, i);
}

void DatabaseBrowser::SetTypeclass(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& tcs = Get(TYPECLASS);
	int cur = GetColumnCursor(TYPECLASS);
	
	RealizeUniqueActions();
	
	if (IsFirstInOrder(TYPECLASS)) {
		SetInitialData();
	}
	else {
		FillItems(TYPECLASS);
	}
	SetColumnCursor(TYPECLASS, i);
}

void DatabaseBrowser::SetContrast(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	auto& cons = Get(CONTENT);
	int cur = GetColumnCursor(CONTENT);
	
	RealizeUniqueActions();
	
	if (IsFirstInOrder(CONTENT)) {
		SetInitialData();
	}
	else {
		FillItems(CONTENT);
	}
	SetColumnCursor(CONTENT, i);
}

void DatabaseBrowser::DataCursorTail(int cursor) {
	for(int i = cursor; i < TYPE_COUNT; i++) {
		if (order[i] == INVALID)
			break;
		DataCursor(i);
	}
}

void DatabaseBrowser::SetCursor(int c, ColumnType type) {
	switch (type) {
		case INVALID:		break;
		case ELEMENT:		SetElement(c); break;
		case ATTR_GROUP:	SetAttrGroup(c); break;
		case ATTR_VALUE:	SetAttrValue(c); break;
		case COLOR:			SetColor(c); break;
		case ACTION:		SetAction(c); break;
		case ACTION_ARG:	SetActionArg(c); break;
		case TYPECLASS:		SetTypeclass(c); break;
		case CONTENT:		SetContrast(c); break;
		default:			TODO break;
	}
}

void DatabaseBrowser::ResetCursor(int c, ColumnType type) {
	SetInitialData();
	for(int i = 0; i < TYPE_COUNT; i++) {
		ColumnType t = order[i];
		if (t == INVALID)
			break;
		
		int& tgt = history.GetAdd(GetHash(i), 0);
		
		if (type != INVALID && t == type) {
			const auto& items = this->items[i];
			if (c >= 0 && c < items.GetCount()) {
				tgt = c;
				SetCursor(c, type);
			}
			else break;
		}
		else {
			FillItems(t);
			int& c = cursor[i];
			if (c < 0 || c >= items[i].GetCount()) {
				c = 0;
				tgt = 0;
			}
		}
		
		FilterData(t);
	}
}

void DatabaseBrowser::DataCursor(int i) {
	int c = history.GetAdd(GetHash(i), 0);
	ColumnType type = order[i];
	SetCursor(c, type);
}

void DatabaseBrowser::FilterData(ColumnType t) {
	int order_i = GetColumnOrder(t);
	auto& items = Get(t);
	
	int cur = GetColumnCursor(t);
	if (!cur) {
		if (order_i > 0)
			RemoveExcessData(order_i);
		return;
	}
	
	Item& filter = items[cur];
	int filter_idx = filter.idx;
	String filter_str = filter.str;
	
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	rm_list.SetCount(0);
	
	int* iter = phrase_parts.Begin();
	for(int i = 0; i < phrase_parts.GetCount(); i++) {
		int pp_i = phrase_parts[i];
		const PhrasePart& pp = da.phrase_parts[pp_i];
		bool rem = false;
		
		switch (t) {
			case ELEMENT:
				rem = pp.el_i < 0 || pp.el_i != filter_idx;
				break;
			case ATTR_GROUP:
				rem = pp.attr < 0 || da.attrs.GetKey(pp.attr).group != filter_str;
				break;
			case ATTR_VALUE:
				rem = pp.attr < 0 || da.attrs.GetKey(pp.attr).value != filter_str;
				break;
			case COLOR: {
				int clr_i = GetColorGroup(pp.clr);
				rem = clr_i != filter_idx;
				break;}
			case ACTION: {
				rem = true;
				for (int act_i : pp.actions) {
					if (da.actions.GetKey(act_i).action == filter_str) {
						rem = false;
						break;
					}
				}
				break;}
			case ACTION_ARG: {
				rem = true;
				for (int act_i : pp.actions) {
					if (da.actions.GetKey(act_i).arg == filter_str) {
						rem = false;
						break;
					}
				}
				break;}
			case TYPECLASS:{
				rem = true;
				for (int tt : pp.typecasts) {
					if (tt == filter_idx) {
						rem = false;
						break;
					}
				}
				break;}
			case CONTENT:{
				rem = true;
				for (int tt : pp.contrasts) {
					if (tt == filter_idx) {
						rem = false;
						break;
					}
				}
				break;}
			default:
				TODO
				break;
		}
		
		if (rem)
			rm_list << i;
	}
	phrase_parts.Remove(rm_list);
	
	if (order_i > 0)
		RemoveExcessData(order_i);
}

void DatabaseBrowser::RemoveExcessData(int order_i) {
	// Don't remove with the first category
	if (order_i <= 0)
		return;
	
	// Don't remove, if already category-limited
	int prev_cur = cursor[order_i-1];
	if (prev_cur != 0)
		return;
	
	// Remove excess data
	if (secondary_category_limit > 0 && phrase_parts.GetCount() > secondary_category_limit)
		phrase_parts.SetCount(secondary_category_limit);
	
}


END_TEXTLIB_NAMESPACE

