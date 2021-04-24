#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

Tags::Tags() {
	
	tags.Add("S",      "simple declarative clause, i.e. one that is not introduced by a (possible empty) subordinating conjunction or a wh-word and that does not exhibit subject-verb inversion.");
	tags.Add("SBAR",   "Clause introduced by a (possibly empty) subordinating conjunction.");
	tags.Add("SBARQ",  "Direct question introduced by a wh-word or a wh-phrase. Indirect questions and relative clauses should be bracketed as SBAR, not SBARQ.");
	tags.Add("SINV",   "Inverted declarative sentence, i.e. one in which the subject follows the tensed verb or modal.");
	tags.Add("SQ",     "Inverted yes/no question, or main clause of a wh-question, following the wh-phrase in SBARQ.");
	
	tags.Add("ADJP",   "Adjective Phrase.");
	tags.Add("AP",     "Adjective Phrase.");
	tags.Add("ADVP",   "Adverb Phrase.");
	tags.Add("CONJP",  "Conjunction Phrase.");
	tags.Add("FRAG",   "Fragment.");
	tags.Add("INTJ",   "Interjection. Corresponds approximately to the part-of-speech tag UH.");
	tags.Add("LST",    "List marker. Includes surrounding punctuation.");
	tags.Add("NAC",    "Not a Constituent; used to show the scope of certain prenominal modifiers within an NP.");
	tags.Add("NP",     "Noun Phrase. ");
	tags.Add("NX",     "Used within certain complex NPs to mark the head of the NP. Corresponds very roughly to N-bar level but used quite differently.");
	tags.Add("PP",     "Prepositional Phrase.");
	tags.Add("PRN",    "Parenthetical. ");
	tags.Add("PRT",    "Particle. Category for words that should be tagged RP. ");
	tags.Add("QP",     "Quantifier Phrase (i.e. complex measure/amount phrase); used within NP.");
	tags.Add("RRC",    "Reduced Relative Clause. ");
	tags.Add("UCP",    "Unlike Coordinated Phrase. ");
	tags.Add("VP",     "Verb Phrase. ");
	tags.Add("WHADJP", "Wh-adjective Phrase. Adjectival phrase containing a wh-adverb, as in how hot.");
	tags.Add("WHADVP",  "Wh-adverb Phrase. Introduces a clause with an NP gap. May be null (containing the 0 complementizer) or lexical, containing a wh-adverb such as how or why.");
	tags.Add("WHNP",   "Wh-noun Phrase. Introduces a clause with an NP gap. May be null (containing the 0 complementizer) or lexical, containing some wh-word, e.g. who, which book, whose daughter, none of which, or how many leopards.");
	tags.Add("WHPP",   "Wh-prepositional Phrase. Prepositional phrase containing a wh-noun phrase (such as of which or by whose authority) that either introduces a PP gap or is contained by a WHNP");
	
	tags.Add("CC",     "Coordinating conjunction");
	tags.Add("CD",     "Cardinal number");
	tags.Add("DT",     "Determiner");
	tags.Add("EX",     "Existential there");
	tags.Add("FW",     "Foreign word");
	tags.Add("IN",     "Preposition or subordinating conjunction");
	tags.Add("JJ",     "Adjective");
	tags.Add("JJR",    "Adjective, comparative");
	tags.Add("JJS",    "Adjective, superlative");
	tags.Add("LS",     "List item marker");
	tags.Add("MD",     "Modal");
	tags.Add("NN",     "Noun, singular or mass");
	tags.Add("NNS",    "Noun, plural");
	tags.Add("NNP",    "Proper noun, singular");
	tags.Add("NNPS",   "Proper noun, plural");
	tags.Add("PDT",    "Predeterminer");
	tags.Add("POS",    "Possessive ending");
	tags.Add("PRP",    "Personal pronoun");
	tags.Add("PRP$",   "Possessive pronoun (prolog version PRP-S)");
	tags.Add("RB",     "Adverb");
	tags.Add("RBR",    "Adverb, comparative");
	tags.Add("RBS",    "Adverb, superlative");
	tags.Add("RP",     "Particle");
	tags.Add("SYM",    "Symbol");
	tags.Add("TO",     "to");
	tags.Add("UH",     "Interjection");
	tags.Add("VB",     "Verb, base form");
	tags.Add("VBD",    "Verb, past tense");
	tags.Add("VBG",    "Verb, gerund or present participle");
	tags.Add("VBN",    "Verb, past participle");
	tags.Add("VBP",    "Verb, non-3rd person singular present");
	tags.Add("VBZ",    "Verb, 3rd person singular present");
	tags.Add("WDT",    "Wh-determiner");
	tags.Add("WP",     "Wh-pronoun");
	tags.Add("WP$",    "Possessive wh-pronoun (prolog version WP-S)");
	tags.Add("WRB",    "Wh-adverb");
	
	tags.Add(".",      "Sentence final puntuation");
	tags.Add(",",      "Comma");
	tags.Add(":",      "Mid sentence punctuation");
	tags.Add("-LRB-",  "Left parenthesis");
	tags.Add("-RRB-",  "Right parenthesis");
	tags.Add("``",     "Start quote");
	tags.Add("''",     "End quote");
	tags.Add("#",      "Pound sign");
	tags.Add("$",      "Dollar sign");
	
	tags.Add("",       "Empty");
	tags.Add("-NONE-", "");
	tags.Add("X",      "Uncertain");
}



WString NormalizeTag(WString tag) {
	int i;
	i = tag.Find("-");
	if (i >= 0) return tag.Left(i);
	i = tag.Find("=");
	if (i >= 0) return tag.Left(i);
	i = tag.Find("|");
	if (i >= 0) return tag.Left(i);
	return tag;
}

WString NormalizeWord(WString word_) {
	word_.Replace("\\/", "/");
	return word_;
}


void ParseNode(const WString& input, int& cursor, Node& node, WString& text) {
	enum {TAG, SEP, WORD};
	
	WString tag, word_;
	int state = TAG;
	
	while (true) {
		if (cursor >= input.GetCount())
			throw Exc("Unexpected end of file");
		
		int chr = input[cursor++];
		text.Cat(chr);
		
		if (state == TAG) {
			if (IsSpace(chr)) {
				state = SEP;
				if (GetTags().tags.Find(tag) < 0) {
					tag = NormalizeTag(tag);
					if (GetTags().tags.Find(tag) < 0) {
						throw Exc("Unrecognized tag: " + tag.ToString());
					}
				}
				node.Add(NODE_NL).SetText(tag);
			}
			else if (chr == '(') {
				// Handle starting ((
				state = SEP;
				node.Add(NODE_SEPARATOR);
				ParseNode(input, cursor, node.Add(NODE_NL), text);
			}
			else
				tag.Cat(chr);
		}
		else if (state == SEP) {
			if (IsSpace(chr))
				;
			else if (chr == '(') {
				ParseNode(input, cursor, node.Add(NODE_NL), text);
			}
			else if (chr == ')')
				break;
			else {
				word_.Clear();
				word_.Cat(chr);
				state = WORD;
			}
		}
		else if (state == WORD) {
			if (chr == ')') {
				node.Add(NODE_NL).SetText(NormalizeWord(word_));
				break;
			}
			else
				word_.Cat(chr);
		}
	}
}

void ParseTreebank(String file_path, Node& tb) {
	WString input = LoadFile(file_path).ToWString();
	int cursor = 0;
	WString text;
	while (true) {
		try {
			if (cursor >= input.GetCount())
				break;
			int chr = input[cursor++];
			if (chr == '(') {
				One<Node> tree;
				tree.Create();
				text.Clear();
				text.Cat(chr);
				ParseNode(input, cursor, *tree, text);
				if (tree->GetCount() && tree->At(0).GetText().IsEmpty())
					tb.Add(tree->Detach(1));
				else
					tb.Add(tree.Detach());
			}
		}
		catch (Exc e) {
			LOG(text);
			LOG(e);
			Exit(1);
		}
	}
}

void NormalizeQuestionbank(String in_path, String out_path) {
	static VectorMap<String, String> REPLACEMENTS;
	if (REPLACEMENTS.IsEmpty()) {
		REPLACEMENTS.Add("(` `)", "(`` ``)");
		REPLACEMENTS.Add("(' <)", "('' '')");
		REPLACEMENTS.Add("<", "'");
		REPLACEMENTS.Add("NPP", "NP");
		REPLACEMENTS.Add("(! !)", "(. !)");
		REPLACEMENTS.Add("(? ?)", "(. ?)");
	}
	
	FileIn fin(in_path);
	FileOut fout(out_path);
	while (!fin.IsEof()) {
		String line = fin.GetLine();
		for(int i = 0; i < REPLACEMENTS.GetCount(); i++)
			line.Replace(REPLACEMENTS.GetKey(i), REPLACEMENTS[i]);
		fout.PutLine(line);
	}
}


NAMESPACE_LANGUAGE_END
