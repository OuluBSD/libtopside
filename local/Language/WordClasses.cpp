#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

bool IsEnding(const char* end, int end_len, const WString& w) {
	int count = w.GetCount();
	if (count < end_len) return false;
	for(int i = 0; i < end_len; i++) {
		if (w[count-end_len+i] != end[i])
			return false;
	}
	return true;
}

bool IsNumberStr(const WString& word_) {
	if (!word_.GetCount())
		return false;
	bool num_fail = false;
	enum {NEG, INT, FRAC, NEGEXP, EXP};
	int s = NEG;
	for(int i = 0; i < word_.GetCount() && !num_fail; i++) {
		int chr = word_[i];
		
		if (s == NEG) {
			if (chr == '-')
				s = INT;
			else if (chr == '.')
				s = FRAC;
			else if (IsDigit(chr))
				s = INT;
			else
				num_fail = true;
		}
		else if (s == INT) {
			if (IsDigit(chr))
				continue;
			else if (chr == '.')
				s = FRAC;
			else if (chr == 'e' || chr == 'E')
				s = NEGEXP;
			else
				num_fail = true;
		}
		else if (s == FRAC) {
			if (IsDigit(chr))
				continue;
			else if (chr == 'e' || chr == 'E')
				s = NEGEXP;
			else
				num_fail = true;
		}
		else if (s == NEGEXP) {
			if (chr == '-')
				s = EXP;
			else if (IsDigit(chr))
				s = EXP;
			else
				num_fail = true;
		}
		else if (s == EXP) {
			if (IsDigit(chr))
				continue;
			else
				num_fail = true;
		}
	}
	return !num_fail;
}


NAMESPACE_LANGUAGE_END
