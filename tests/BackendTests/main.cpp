#include "BackendTests.h"


CONSOLE_APP_MAIN {
	using namespace TS;
	CompilationUnit	cu;
	Namespace&		ns = cu.GetAddNamespace("TS");
	Class&			atom_base = ns.GetAddClass("AtomBase");
	Class&			eg_atom = ns.GetAddTemplateClass("AtomExample");
	bool r = true;
	
	atom_base.Hint("prj", "SerialCore");
	atom_base.Hint("file", "Atom");
	
	r = eg_atom.Inherit(atom_base);
	ASSERT(r);
	
	String dir_out = ConfigFile("export");
	RealizeDirectory(dir_out);
	
	
	cu.SetPackage("BackendTest");
	cu.SetFile("BackendTest");
	
	AssemblyExporter ae(cu);
	r = ae.Export(dir_out);
	ASSERT(r);
	
	
}
