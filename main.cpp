#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "cfg.h"
#include "object.h"
#include "input.h"
#include "render.h"


using namespace std;

void resetGame(game_config* config, objects* objs) {
	config->score = 0;
	objs->reset();
}
/*
	game_status :
		'j' == playing;
		'm' == enter menu
		'c' == menu selection - continue
		'q' == menu selection - quit
*/
int main() {
	setlocale(LC_ALL, "english");
	game_config* game_cfg = new game_config();
	objects* game_objects = new objects();
	game_cfg->load();
	while (game_cfg->game_status != 'f') {
		if (game_cfg->game_status == 'j') {
			if (game_objects->getSnake() == NULL) {
				game_cfg->save(game_cfg->score);
				game_cfg->game_status = 'm';
			}else{
				game_objects->update();
				game_objects->getSnake()->move(getAxis());
				for (int i = 1; i <= game_objects->quantity; i++) {
					game_objects->getFruit(i).update();
					if (game_objects->getSnake()->hitPoint(game_objects->getFruit(i).getPosition())) {
						game_cfg->score += 1;
						game_objects->getSnake()->grow();
						game_objects->removeObj(i);
					}
				}
				if(game_objects->getSnake()->hitArea(game_cfg->stage) || game_objects->getSnake()->hitSelf()){
					game_objects->removeFruits();
					game_objects->removeSnake();
					std::cout << "\nGAME OVER";
					Sleep(1000);
				}
				renderGame(game_cfg, game_objects);
				Sleep(20);
			}
		}else {
			char Key = getKey();
			if (game_cfg->game_status == 'c') {
				if (Key == 's') {
					game_cfg->game_status = 'q';
				}
				else if (Key == '\r') {
					resetGame(game_cfg, game_objects);
					game_cfg->game_status = 'j';
				}
			}else if (game_cfg->game_status == 'q') {
				if (Key == 'w') {
					game_cfg->game_status = 'c';
				}else if (Key == '\r') {
					game_cfg->game_status = 'f';
				}
			}
			if(Key != ' ' || game_cfg->game_status == 'm'){
				renderMenu(game_cfg);
				Sleep(20);
				if(game_cfg->game_status == 'm'){
					game_cfg->game_status = 'c';
				}
			}
		}
	}
	std::cout << std::endl << "Game closed." << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}