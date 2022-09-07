#include "Music1.h"



GUI_APP_MAIN {
	SetCoutLog();
	
	LomseTutorial1().Run();
	
}



LomseTutorial1::LomseTutorial1() {
	Title("LomseTutorial1");
	MinimizeBox().MaximizeBox().Sizeable();
	
	Add(notation.SizePos());
	
	notation.OpenDocumentLenmus(
		"(lenmusdoc (vers 0.0)"
            "(content "
                "(para (txt \"Hello world!\"))"
                "(score (vers 1.6) "
                    "(instrument (musicData (clef G)(key C)(time 2 4)(n c4 q) )))"
            ")"
        ")");
	
}
