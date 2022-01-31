#include "Adventure.h"

GUI_APP_MAIN {
	using namespace Adventure;
	
	reset_ui();
	
	
	
	clear_curr_cmd()
	// talking_curr = nil  // currently displayed speech {x,y,col,lines ... }
	// dialog_curr = nil   // currently displayed dialog options to pick
	// cutscene_curr = nil // currently active cutscene
	// talking_actor = nil // currently talking actor
	
	global_scripts = {}	// table of scripts that are at game-level (background)
	local_scripts = {}	// table of scripts that are actively running
	cutscenes = {}			// table of scripts for (the active cutscene(s)
	draw_zplanes = {}		// table of tables for (each of the (8) zplanes for (drawing depth
	
	fade_iris, fade_iris = 0, 0
	
	cutscene_cooloff = 0
	
	
	
	// game loop
	
	function _init()
	
	// use mouse input
	poke(0x5f2d, 1)
	
	// init all the rooms/objects/actors
	game_init()
	
	// run any startup script(s)
	start_script(startup_script, true)
	
}
