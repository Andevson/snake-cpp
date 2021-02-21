#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "game.h"
#include "render.h"
#include "object.h"
#include "cfg.h"

using namespace std;

int main(void){
	setlocale(LC_ALL, "english");
	game_config* game_cfg = new game_config();
	objects* game_objects = new objects();
	game* g = new game(game_cfg, game_objects);
	game_cfg->load();
	while(g->getStatus() != "quit"){
		g->play();
		render(g, game_cfg, game_objects);
	}
	system("pause");
	return EXIT_SUCCESS;
}