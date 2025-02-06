#include "ToolCore.h"


BEGIN_TEXTLIB_NAMESPACE


void PutKeyColor(const char* key, int ir, int ig, int ib, double& r, double& g, double& b, double& sr, double& sg, double& sb) {
	int av = (ir + ig + ib) / 3;
	if (strncmp(key, "noun", 4) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "interjection", 12) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "pronoun", 7) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "adjective", 9) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb", 4) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "preposition", 11) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "conjunction", 11) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "adverb", 6) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "determiner", 10) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "numeral", 7) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += ib; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "particle", 8) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "adjective and noun", 18) == 0) {
		r += av; sr += 1 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += av; sg += 1 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += av; sb += 1 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb and noun", 13) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "conjunction and interjection", 28) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 2 * av; sr += 2 * 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 2 * av; sg += 2 * 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 2 * av; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "proper noun", 11) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += ib; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "slang term", 10) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "expression", 10) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "onomatopoeia", 12) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += ib; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "abbreviation", 12) == 0) {
		r += 1.25 * av; sr += 1.25 * 255;
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * av; sg += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.25 * av; sb += 1.25 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "acronym", 7) == 0) {
		r += av; sr += 1 * 255;
		r += 2 * av; sr += 2 * 255;
		g += av; sg += 1 * 255;
		g += 2 * av; sg += 2 * 255;
		b += av; sb += 1 * 255;
		b += 2 * av; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "ordinal number", 14) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "prefix", 6) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "suffix", 6) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "quantifier", 10) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += ib; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "slang for \"out of\"", 20) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "indefinite article", 18) == 0) {
		r += 3 * ir; sr += 3 * 255;
		g += 3 * ig; sg += 3 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "code/abbreviation", 17) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "slang/noun", 10) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 2 * av; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 2 * av; sb += 2 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "jargon", 6) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "past tense verb", 15) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "adverb and conjunction", 22) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "slang term for \"would not\"", 28) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "slang term for \"hundred dollar bills\"", 39) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		r += av; sr += 1 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += av; sg += 1 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += av; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "a leader", 8) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "a very short period of time", 27) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "a slippery substance used to reduce friction", 44) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		r += 50; sr += 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "seep out", 8) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "slang term for leaving", 22) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		r += av; sr += 1 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += av; sg += 1 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += av; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "a shelter made by birds to lay their eggs", 41) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		r += 50; sr += 255;
		g += 2 * ig; sg += 2 * 255;
		g += 50; sg += 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "a long", 6) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "a type of setting in jewelry where small stones are set closely together", 72) == 0) {
		r += 2 * ir; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * ig; sg += 2 * 255;
		g += 50; sg += 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "abbreviation for methamphetamine", 32) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "yeah", 4) == 0) {
		r += 3 * av; sr += 3 * 255;
		g += 3 * av; sg += 3 * 255;
		b += 3 * av; sb += 3 * 255;
		return;
	}
	if (strncmp(key, "past tense of \"to sleep\"", 26) == 0) {
		r += 2.25 * ir; sr += 2.25 * 255;
		g += 2.25 * ig; sg += 2.25 * 255;
		b += 2.25 * ib; sb += 2.25 * 255;
		return;
	}
	if (strncmp(key, "a small", 7) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "other items", 11) == 0) {
		r += 128; sr += 255;
		g += 128; sg += 255;
		b += 128; sb += 255;
		return;
	}
	if (strncmp(key, "plural of \"road\"", 18) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "plural of \"route\"", 19) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "\"comfortable\"", 15) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "a greek god known for his speed and cunning", 43) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "a long upholstered piece of furniture for seating", 49) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "preposition/conjunction", 23) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 50; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 50; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "personal pronoun", 16) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "place name", 10) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 50; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 50; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "plural noun", 11) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "auxiliary verb", 14) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "abbreviation for \"electronic arts\"", 36) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "slang term for \"that\"", 23) == 0) {
		r += 2.5 * ir; sr += 2.5 * 255;
		g += 2.5 * ig; sg += 2.5 * 255;
		b += 2.5 * ib; sb += 2.5 * 255;
		return;
	}
	if (strncmp(key, "abbreviation for \"1950s\"", 26) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "slang term for \"good\"", 23) == 0) {
		r += 2.5 * ir; sr += 2.5 * 255;
		g += 2.5 * ig; sg += 2.5 * 255;
		b += 2.5 * ib; sb += 2.5 * 255;
		return;
	}
	if (strncmp(key, "emoticon", 8) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "determiner/conjunction", 22) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "swear word", 10) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 50; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 50; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "brand", 5) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 50; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 50; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "drug", 4) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "pronoun/adjective", 17) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "unknown", 7) == 0) {
		r += av; sr += 1 * 255;
		r += 2550; sr += 255;
		g += av; sg += 1 * 255;
		g += 2550; sg += 255;
		b += av; sb += 1 * 255;
		b += 2550; sb += 255;
		return;
	}
	if (strncmp(key, "symbol", 6) == 0) {
		r += av; sr += 1 * 255;
		r += 25500; sr += 255;
		g += av; sg += 1 * 255;
		g += 25500; sg += 255;
		b += av; sb += 1 * 255;
		b += 25500; sb += 255;
		return;
	}
	if (strncmp(key, "number", 6) == 0) {
		r += av; sr += 1 * 255;
		r += 12750; sr += 255;
		g += av; sg += 1 * 255;
		g += 12750; sg += 255;
		b += av; sb += 1 * 255;
		b += 12750; sb += 255;
		return;
	}
	if (strncmp(key, "adjective/noun", 14) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb/adverb", 11) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "phrase", 6) == 0) {
		r += av; sr += 1 * 255;
		r += 12750; sr += 255;
		g += av; sg += 1 * 255;
		g += 12750; sg += 255;
		b += av; sb += 1 * 255;
		b += 12750; sb += 255;
		return;
	}
	if (strncmp(key, "sound effect", 12) == 0) {
		r += av; sr += 1 * 255;
		r += 6375; sr += 255;
		g += av; sg += 1 * 255;
		g += 6375; sg += 255;
		b += av; sb += 1 * 255;
		b += 6375; sb += 255;
		return;
	}
	if (strncmp(key, "alphanumeric", 12) == 0) {
		r += av; sr += 1 * 255;
		r += 25500; sr += 255;
		g += av; sg += 1 * 255;
		g += 25500; sg += 255;
		b += av; sb += 1 * 255;
		b += 25500; sb += 255;
		return;
	}
	if (strncmp(key, "adjective/name", 14) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "comparative adjective", 21) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "superlative adjective", 21) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "past participle verb", 20) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "proper noun/person", 18) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "colloquial word for \"stuff\"", 29) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "comparative adjective/name", 26) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "superlative adjective/name", 26) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "noun (slang)", 12) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb (slang)", 12) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "noun (plural)", 13) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "slang/verb", 10) == 0) {
		r += av; sr += 1 * 255;
		r += 19125; sr += 255;
		g += av; sg += 1 * 255;
		g += 19125; sg += 255;
		b += av; sb += 1 * 255;
		b += 19125; sb += 255;
		return;
	}
	if (strncmp(key, "slang/abbreviation", 18) == 0) {
		r += av; sr += 1 * 255;
		r += 60 * av; sr += 60 * 255;
		g += av; sg += 1 * 255;
		g += 60 * av; sg += 60 * 255;
		b += av; sb += 1 * 255;
		b += 60 * av; sb += 60 * 255;
		return;
	}
	if (strncmp(key, "slang/adjective", 15) == 0) {
		r += av; sr += 1 * 255;
		r += 80 * av; sr += 80 * 255;
		g += av; sg += 1 * 255;
		g += 80 * av; sg += 80 * 255;
		b += av; sb += 1 * 255;
		b += 80 * av; sb += 80 * 255;
		return;
	}
	if (strncmp(key, "unfinished verb (french for \"to heat up\")", 43) == 0) {
		r += 255; sr += 255;
		g += 0; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished verb (french for \"let's go\")", 41) == 0) {
		r += 255; sr += 255;
		g += 153; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished interjection (french for \"yes\")", 44) == 0) {
		r += 255; sr += 255;
		g += 204; sg += 255;
		b += 51; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished verb (french for \"succeeded\")", 42) == 0) {
		r += 51; sr += 255;
		g += 153; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished verb (french for \"to begin\")", 41) == 0) {
		r += 204; sr += 255;
		g += 102; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished verb (slang for \"shoot\" in french)", 47) == 0) {
		r += 255; sr += 255;
		g += 51; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "unfinished adjective (french for \"small\")", 43) == 0) {
		r += 255; sr += 255;
		g += 153; sg += 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "adjective/adverb", 16) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "noun/verb", 9) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "noun (brand name)", 17) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "noun (character name)", 21) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "noun (abbreviation)", 19) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "noun (person name)", 18) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "contraction of \"i'm going to\"", 31) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "abbreviation for first person singular", 38) == 0) {
		r += 150; sr += 255;
		g += 150; sg += 255;
		b += 150; sb += 255;
		return;
	}
	if (strncmp(key, "contraction of \"walked\"", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "contraction of \"hiding\"", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "contraction of \"wilding\"", 26) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "mixed", 5) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "interjection/exclamation", 24) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "noun/adverb", 11) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "misspelling", 11) == 0) {
		r += 1.25 * av; sr += 1.25 * 255;
		r += 50; sr += 255;
		g += 1.25 * av; sg += 1.25 * 255;
		g += 50; sg += 255;
		b += 1.25 * av; sb += 1.25 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "contraction of \"might have\"", 29) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "colloquial word for \"here\"", 28) == 0) {
		r += 1.25 * av; sr += 1.25 * 255;
		r += 1.25 * av; sr += 1.25 * 255;
		g += 1.25 * av; sg += 1.25 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 1.25 * av; sg += 1.25 * 255;
		b += 1.25 * av; sb += 1.25 * 255;
		b += 1.25 * av; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "(undefined)", 11) == 0) {
		r += 50; sr += 255;
		g += 50; sg += 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "abbreviation for facebook", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.5 * av; sr += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "noun (colloquial)", 17) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "noun (place name)", 17) == 0) {
		r += 2 * av; sr += 2 * 255;
		g += 2 * av; sg += 2 * 255;
		b += 2 * av; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "noun (name)", 11) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "noun (number)", 13) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "noun (person riding a skateboard)", 33) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		r += 50; sr += 255;
		g += 1.75 * av; sg += 1.75 * 255;
		g += 50; sg += 255;
		b += 1.75 * av; sb += 1.75 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "enthusiasm", 10) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * av; sg += 2 * 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "activities", 10) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * av; sg += 1.5 * 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "improper noun", 13) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "acronym/abbreviation", 20) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "exclamatory word", 16) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 75; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 75; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 75; sb += 255;
		return;
	}
	if (strncmp(key, "decade", 6) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "number (ordinal)", 16) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 50; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "nomenzahl", 9) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "adjecive", 8) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "undefined", 9) == 0) {
		r += av; sr += 1 * 255;
		g += av; sg += 1 * 255;
		b += av; sb += 1 * 255;
		return;
	}
	if (strncmp(key, "n/a", 3) == 0) {
		r += 0; sr += 255;
		g += 0; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "acronym/verb", 12) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 75; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 75; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 75; sb += 255;
		return;
	}
	if (strncmp(key, "combination of letters and numbers", 34) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 75; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 75; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 75; sb += 255;
		return;
	}
	if (strncmp(key, "exclamatory", 11) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "comparable adjective", 20) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "slang expression", 16) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "demonstrative pronoun", 21) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "postposition", 12) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb (french for \"to heat up\")", 32) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 102; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 51; sb += 255;
		return;
	}
	if (strncmp(key, "verb (french for \"let's go\")", 30) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 2 * ir; sr += 2 * 255;
		r += 51; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 153; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "interjection (french for \"yes\")", 33) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "verb (french for \"succeeded\")", 31) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 51; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "verb (french for \"to begin\")", 30) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 102; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 153; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "verb (slang for \"shoot\" in french)", 36) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "adjective (french for \"small\")", 32) == 0) {
		r += 2 * ir; sr += 2 * 255;
		r += 51; sr += 255;
		g += 2 * ig; sg += 2 * 255;
		g += 204; sg += 255;
		b += 2 * ib; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "number (possibly a car model)", 29) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		g += 1.75 * av; sg += 1.75 * 255;
		b += 1.75 * av; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "\"i'm coming for you\"?", 23) == 0) {
		r += av; sr += 1 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += av; sg += 1 * 255;
		g += 0; sg += 255;
		b += av; sb += 1 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "noun (slang for \"paris\" in french)", 36) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 51; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "verb (french for \"to send\")", 29) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 100; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "\"emotions\"", 12) == 0) {
		r += 255; sr += 255;
		g += 0; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "expression (possibly slang for \"wow\"?)", 40) == 0) {
		r += 255; sr += 255;
		g += 0; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "noun (slang for \"small ones\" in french)", 41) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 150; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 150; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 150; sb += 255;
		return;
	}
	if (strncmp(key, "name", 4) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 50; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 50; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "verb (slang for \"i'll send you\" in french)", 44) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 100; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 100; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "a slang term?", 13) == 0) {
		r += 0; sr += 255;
		g += 153; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "\"backing\"", 11) == 0) {
		r += 204; sr += 255;
		g += 204; sg += 255;
		b += 204; sb += 255;
		return;
	}
	if (strncmp(key, "noun (french for \"head\")", 26) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 150; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 150; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 150; sb += 255;
		return;
	}
	if (strncmp(key, "verb (french slang for \"to have sex\")", 39) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 100; sb += 255;
		return;
	}
	if (strncmp(key, "noun (slang for \"arab\" in french)", 35) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 0; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "verb (slang for \"love\" in french)", 35) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "\"okay\" in french)", 19) == 0) {
		r += 0; sr += 255;
		g += 153; sg += 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "\"dude\"", 8) == 0) {
		r += 102; sr += 255;
		g += 0; sg += 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "present participle", 18) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 150; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 150; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 150; sb += 255;
		return;
	}
	if (strncmp(key, "preposition/definite article", 28) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "contraction of \"had not\"", 26) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 100; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 100; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 100; sb += 255;
		return;
	}
	if (strncmp(key, "abbreviation for \"note well\"", 30) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		r += 255; sr += 255;
		g += 1.75 * av; sg += 1.75 * 255;
		g += 0; sg += 255;
		b += 1.75 * av; sb += 1.75 * 255;
		b += 50; sb += 255;
		return;
	}
	if (strncmp(key, "abbreviation for \"beneath\"", 28) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		r += 0; sr += 255;
		g += 1.75 * av; sg += 1.75 * 255;
		g += 50; sg += 255;
		b += 1.75 * av; sb += 1.75 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "japanese word meaning \"unmatched\"", 35) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 150; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 150; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"read\"", 21) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "japanese word meaning \"diamond\"", 33) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 0; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"stretch\"", 24) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"show\"", 21) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"unforgettable\"", 30) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "adjective meaning \"untangled\"", 31) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"swim\"", 21) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "japanese phrase meaning \"isn't it?\"", 37) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"sleep\"", 22) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "adjective meaning \"dazzling\"", 30) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"put in\"", 23) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"got\"", 20) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"slept\"", 22) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "noun meaning \"photograph\"", 27) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 0; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 204; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"flame\"", 22) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 102; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"cabinet\"", 24) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 153; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 153; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"can't throw away\"", 33) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 204; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"outdated\"", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 153; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"teddy bear\"", 27) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 204; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"neighbor\"", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 153; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 153; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"coat\"", 21) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "verb meaning \"can't cross\"", 28) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "noun meaning \"bad\"", 20) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "adjective meaning \"cowardly\"", 30) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"can't fix\"", 26) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 102; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 204; sb += 255;
		return;
	}
	if (strncmp(key, "adjective meaning \"painful\"", 29) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"yell\"", 21) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verb meaning \"close in\"", 25) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "japanese word meaning \"no\"", 28) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "time", 4) == 0) {
		r += 102; sr += 255;
		g += 102; sg += 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "compound noun", 13) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 102; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 102; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "unfamiliar", 10) == 0) {
		r += 153; sr += 255;
		g += 153; sg += 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "ending", 6) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 51; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 51; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "interjection/noun", 17) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 153; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "nonsense", 8) == 0) {
		r += 204; sr += 255;
		g += 204; sg += 255;
		b += 204; sb += 255;
		return;
	}
	if (strncmp(key, "sound/interjection", 18) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "random characters", 17) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "indefinite", 10) == 0) {
		r += 255; sr += 255;
		g += 153; sg += 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "determination", 13) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 204; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 204; sb += 255;
		return;
	}
	if (strncmp(key, "fluidity", 8) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 51; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 51; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "chaos", 5) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 0; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "transformation", 14) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 0; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 255; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "boundlessness", 13) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "solitude", 8) == 0) {
		r += 153; sr += 255;
		g += 204; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "distance", 8) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 153; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 153; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "goodness", 8) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 0; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 255; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "noun/ adjective", 15) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 153; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 204; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "none", 4) == 0) {
		r += 0; sr += 255;
		g += 0; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "interrogative pronoun", 21) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		r += 255; sr += 255;
		g += 1.75 * av; sg += 1.75 * 255;
		g += 0; sg += 255;
		b += 1.75 * av; sb += 1.75 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "interjection/onomatopoeia", 25) == 0) {
		r += 1.5 * av; sr += 1.5 * 255;
		r += 255; sr += 255;
		g += 1.5 * av; sg += 1.5 * 255;
		g += 102; sg += 255;
		b += 1.5 * av; sb += 1.5 * 255;
		b += 51; sb += 255;
		return;
	}
	if (strncmp(key, "palindrome", 10) == 0) {
		r += 1.75 * av; sr += 1.75 * 255;
		r += 102; sr += 255;
		g += 1.75 * av; sg += 1.75 * 255;
		g += 102; sg += 255;
		b += 1.75 * av; sb += 1.75 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "gibberish", 9) == 0) {
		r += 255; sr += 255;
		g += 0; sg += 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "initialism", 10) == 0) {
		r += av; sr += 1 * 255;
		r += av; sr += 1 * 255;
		r += 25; sr += 255;
		g += av; sg += 1 * 255;
		g += av; sg += 1 * 255;
		g += 25; sg += 255;
		b += av; sb += 1 * 255;
		b += av; sb += 1 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "abbreviation for dozen", 22) == 0) {
		r += av; sr += 1 * 255;
		r += 255; sr += 255;
		g += av; sg += 1 * 255;
		g += 128; sg += 255;
		b += av; sb += 1 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "imperative verb", 15) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "slang/expression", 16) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 2 * ir; sr += 2 * 255;
		r += 100; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 100; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 100; sb += 255;
		return;
	}
	if (strncmp(key, "integer", 7) == 0) {
		r += av; sr += 1 * 255;
		r += av; sr += 1 * 255;
		r += 153; sr += 255;
		g += av; sg += 1 * 255;
		g += av; sg += 1 * 255;
		g += 153; sg += 255;
		b += av; sb += 1 * 255;
		b += av; sb += 1 * 255;
		b += 153; sb += 255;
		return;
	}
	if (strncmp(key, "adjective (name)", 16) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "city name", 9) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 2 * ir; sr += 2 * 255;
		g += 3 * av; sg += 3 * 255;
		b += 3 * av; sb += 3 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "given name", 10) == 0) {
		r += 1.5 * ir; sr += 1.5 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "misspelled", 10) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 255; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 0; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "proper name", 11) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 128; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 128; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 128; sb += 255;
		return;
	}
	if (strncmp(key, "nouns", 5) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "unclear", 7) == 0) {
		r += 255; sr += 255;
		g += 255; sg += 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "the essence of nature", 21) == 0) {
		r += 102; sr += 255;
		g += 255; sg += 255;
		b += 102; sb += 255;
		return;
	}
	if (strncmp(key, "proper adjective", 16) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 0; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 128; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "slang", 5) == 0) {
		r += 2 * ir; sr += 2 * 255;
		r += 100; sr += 255;
		g += 2 * ig; sg += 2 * 255;
		g += 100; sg += 255;
		b += 2 * ib; sb += 2 * 255;
		b += 100; sb += 255;
		return;
	}
	if (strncmp(key, "exclamation", 11) == 0) {
		r += av; sr += 1 * 255;
		r += 255; sr += 255;
		g += av; sg += 1 * 255;
		g += 0; sg += 255;
		b += av; sb += 1 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "number and verb", 15) == 0) {
		r += av; sr += 1 * 255;
		r += 1.5 * ir; sr += 1.5 * 255;
		g += av; sg += 1 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += av; sb += 1 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "verbs", 5) == 0) {
		r += 3 * av; sr += 3 * 255;
		r += 255; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 0; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "question word", 13) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "slang noun", 10) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 2 * ir; sr += 2 * 255;
		r += 100; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 100; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		b += 100; sb += 255;
		return;
	}
	if (strncmp(key, "noun and verb", 13) == 0) {
		r += 2 * ir; sr += 2 * 255;
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "adjective and verb", 18) == 0) {
		r += 2 * ir; sr += 2 * 255;
		r += 3 * av; sr += 3 * 255;
		r += 255; sr += 255;
		g += 3 * av; sg += 3 * 255;
		g += 153; sg += 255;
		b += 3 * av; sb += 3 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "negative particle", 17) == 0) {
		r += av; sr += 1 * 255;
		r += 255; sr += 255;
		g += av; sg += 1 * 255;
		g += 255; sg += 255;
		b += av; sb += 1 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "strong and fierce", 17) == 0) {
		r += 2 * av; sr += 2 * 255;
		r += 255; sr += 255;
		g += 2 * av; sg += 2 * 255;
		g += 0; sg += 255;
		b += 2 * av; sb += 2 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "hidden information", 18) == 0) {
		r += av; sr += 1 * 255;
		r += 0; sr += 255;
		g += av; sg += 1 * 255;
		g += 0; sg += 255;
		b += av; sb += 1 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "invisible transmission", 22) == 0) {
		r += av; sr += 1 * 255;
		r += 0; sr += 255;
		g += av; sg += 1 * 255;
		g += 128; sg += 255;
		b += av; sb += 1 * 255;
		b += 128; sb += 255;
		return;
	}
	if (strncmp(key, "mysterious identity", 19) == 0) {
		r += av; sr += 1 * 255;
		r += 255; sr += 255;
		g += av; sg += 1 * 255;
		g += 0; sg += 255;
		b += av; sb += 1 * 255;
		b += 255; sb += 255;
		return;
	}
	if (strncmp(key, "encrypted secrets", 17) == 0) {
		r += av; sr += 1 * 255;
		r += 153; sr += 255;
		g += av; sg += 1 * 255;
		g += 0; sg += 255;
		b += av; sb += 1 * 255;
		b += 0; sb += 255;
		return;
	}
	if (strncmp(key, "curious exploration", 19) == 0) {
		r += 2.5 * ir; sr += 2.5 * 255;
		g += 2.5 * ig; sg += 2.5 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "elusive truth", 13) == 0) {
		r += 2.5 * av; sr += 2.5 * 255;
		r += 127.5; sr += 255;
		g += 2.5 * av; sg += 2.5 * 255;
		g += 127.5; sg += 255;
		b += 2.5 * av; sb += 2.5 * 255;
		b += 127.5; sb += 255;
		return;
	}
	if (strncmp(key, "hidden translation", 18) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.75 * ib; sb += 1.75 * 255;
		return;
	}
	if (strncmp(key, "tangled sentences", 17) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 1.75 * ig; sg += 1.75 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "invisible bond", 14) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "hidden potential", 16) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "invisible love", 14) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
	if (strncmp(key, "unknown/unclear", 15) == 0) {
		r += 2 * ir; sr += 2 * 255;
		g += 2 * ig; sg += 2 * 255;
		b += 2 * ib; sb += 2 * 255;
		return;
	}
	if (strncmp(key, "common noun", 11) == 0) {
		r += 1.25 * ir; sr += 1.25 * 255;
		g += 1.25 * ig; sg += 1.25 * 255;
		b += 1.25 * ib; sb += 1.25 * 255;
		return;
	}
	if (strncmp(key, "modifier", 8) == 0) {
		r += 1.75 * ir; sr += 1.75 * 255;
		g += 1.5 * ig; sg += 1.5 * 255;
		b += 1.5 * ib; sb += 1.5 * 255;
		return;
	}
}

Color GetSentenceColor(const Vector<String>& main_classes, const Vector<Color>& clrs) {
	ASSERT(main_classes.GetCount() == clrs.GetCount());
	double r = 0;
	double g = 0;
	double b = 0;
	double rs = 0;
	double gs = 0;
	double bs = 0;
	for(int i = 0; i < main_classes.GetCount(); i++) {
		const String& main_class = main_classes[i];
		const Color& clr = clrs[i];
		PutKeyColor(main_class.Begin(),
			clr.GetR(), clr.GetG(), clr.GetB(),
			r, g, b,
			rs, gs, bs);
	}
	if (rs > 0) r /= rs;
	if (gs > 0) g /= gs;
	if (bs > 0) b /= bs;
	byte br = (byte)(255 * r);
	byte bg = (byte)(255 * g);
	byte bb = (byte)(255 * b);
	Color res(br, bg, bb);
	return res;
}


END_TEXTLIB_NAMESPACE

