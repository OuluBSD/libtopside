#include "EonBaseGen.h"


NAMESPACE_EONGEN_BEGIN




void GenerateEonBase() {
	/*
	
	Bases
		- test that all can be connected
		- find all loop combinations (generalize, split)
		- dump generalized combinations as naming template
		- add names to loops
	
	Headers
		- test that all can be connected
		- find combinations, dump them, name them
		- find constraints to separate connections
	
	Loops (optional)
		- test that loops can connect
		- find constraints that are required for the loop to connect
	Chains
		- test that side connections works
		- find constraints?
	TopChains
		- test that side connections works
		- find constraints?
	MultiChains
		- test that side connections works
		- find constraints?
	Machines
		- test that side connections works
		- find constraints?
	Systems
		- test that side connections works
			- connection might need separate classes
		- find constraints?
	Impl
		- find constraints?
		- generate template frames
	
	
	
	Abstraction?
		
		Unit
			- can stack
			- test connections
			- find combinations
			- dump link naming template
			- name links
		
		Node
			- test connections
			- find special constraints for connections
	
	What follows?
		
		- generate c++ projects?
			- can't be the primary solution, because it breaks shader player
			- might be easier to debug
		- generate ecs conf files?
		- generate u++ project files for ecs comp impl?
		
		- generate scripts?
		
		
	How to do?
		- parse and resolve json files to a networked structure
		- keep track of pathways, and what unique constraints they have
		- use structure as ROM, which is searched with A*
			- convert .eon file to searching scenario
	*/
	
	Index<String> json_files;
	json_files.Add("Bases.json");
	json_files.Add("Headers.json");
	json_files.Add("Loops.json");
	json_files.Add("Links.json");
	json_files.Add("Chains.json");
	json_files.Add("TopChains.json");
	json_files.Add("Machines.json");
	json_files.Add("Systems.json");
	//json_files.Add("Impl.json");
	
	
	World world;
	
	String dir = GetDataFile("");
	for (String file : json_files) {
		LOG("Loading " << file);
		String path = AppendFileName(dir, file);
		String content = LoadFile(path);
		if (content.IsEmpty()) {
			LOG("Empty file: " + path);
			return;
		}
		if (!world.LoadJSON(content)) {
			LOG("Loading json failed: " + path);
			return;
		}
		
	}
	
	LOG("Json load success!");
	
	
	
	/*
	
	Traverse (& dump)
	- base connections (check integrity and that all are connected)
	- loops
	- valid links
	- chains
	- top chains
	- machines
	- systems
	
	*/
	
	if (!world.TraverseUnits(Unit::BASE))
		return;
	if (!world.TraverseUnits(Unit::HEADER))
		return;
	if (!world.TraverseLoops())
		return;
	
	
	LOG("success!");
}

NAMESPACE_EONGEN_END

CONSOLE_APP_MAIN {
	TS::ECS::Eon::Gen::GenerateEonBase();
}
