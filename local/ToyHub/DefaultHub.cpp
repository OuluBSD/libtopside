#include "ToyHub.h"

NAMESPACE_TOYHUB_BEGIN

void LoadDefaultHub(String db_name, String lang) {
	User root;
	root.Create("root", "123", "root@email.com");
	root.Load(1);
	root.Authenticate();
	root.IncEdits();
	DUMPC(User::GetRange(0, User::GetCount()));
	
	
	Hub en_hub;
	if (!en_hub.Load(db_name, lang) && !en_hub.Create(root, db_name, lang))
		return;
	
	String model = "toy";
	String format = "html";
	FindFile ff;
	if (ff.Search(ShareDirFile("toyhub" DIR_SEPS "*"))) {
		do {
			if (ff.IsFile())
				SetPage(en_hub, root, ff.GetName(), UPP::LoadFile(ff.GetPath()), lang, model, format);
		}
		while (ff.Next());
	}
	
}


NAMESPACE_TOYHUB_END
