#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN





void PathIdentifier::Clear() {
	memset(this, 0, sizeof(PathIdentifier));
}

String PathIdentifier::ToString() const {
	if (!begin || begin == end)
		return String();
	String s;
	const Token* iter = begin;
	const bool* is_meta = &this->is_meta[0];
	while (iter != end) {
		if (iter->type == TK_ID) {
			if (*is_meta)
				s.Cat('$');
			is_meta++;
			s.Cat(iter->GetTextValue());
		}
		else if (iter->type == '$')
			; // pass
		else
			s.Cat(iter->GetTextValue());
		iter++;
	}
	return s;
}

bool PathIdentifier::IsEmpty() const {
	return part_count == 0;
}

bool PathIdentifier::HasMeta() const {
	for(int i = 0; i < part_count; i++)
		if (is_meta[i])
			return true;
	return false;
}

bool PathIdentifier::HasPartialMeta() const {
	for(int i = 0; i < part_count; i++)
		if (is_meta[i])
			return i > 0; // if first is meta, then it's full, not partial
	return false;
}

NAMESPACE_TOPSIDE_END
