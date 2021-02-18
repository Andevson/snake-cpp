#include <iostream>

#ifndef RENDER_CPP
#define RENDER_CPP

#include "mat.h"
#include "cfg.h"
#include "object.h"
void drawSnake(void){
	COLOR_SNAKE;
	std::cout << " O";
}
void drawWall(void){
	COLOR_WALL;
	std::cout << " X";
}
void drawFruit(void){
	COLOR_FRUIT;
	std::cout << " F";
	COLOR_WALL;
}
void drawBonus(int life_time){
	COLOR_BONUS;
	std::cout << " " << life_time;
	COLOR_WALL;
}
void drawEmpty(void){
	std::cout << "  ";
}
void drawScore(int score){
	COLOR_TEXT;
	std::cout << "Score : ";
	COLOR_SCORE;
	std::cout << score << std::endl;
	COLOR_WALL;
}
char draw_buffer;
void drawBuffer(char buffer){
	switch(buffer){
		case ' ':
		drawEmpty();
		break;
		case 'w':
		drawWall();
		break;
		case 's':
		drawSnake();
		break;
		case 'f':
		drawFruit();
		break;
		case 'b':
		drawBonus('b');
		break;
		case 'e':
		std::cout << 'E';
		break;
		default:
		drawBonus(buffer);
	}
}
void renderGame(game_config* cfg, objects* objs) {
	if(objs->getSnake() == NULL){
		throwError("Error_rendering_empty_snake");
		return;
	}
	system("cls");
	drawScore(cfg->score);
	_2D scan = { 0, 0 };
	for (scan.y = 0; scan.y <= cfg->stage.y + 1; scan.y += 1) {
		for (scan.x = 0; scan.x <= cfg->stage.x + 1; scan.x ++) {
			draw_buffer = ' ';
			snake* target_snake = objs->getSnake();
			if (scan.x == 0 || scan.x == cfg->stage.x + 1 || scan.y == 0 || scan.y == cfg->stage.y + 1) {
				draw_buffer = 'w';
			}
			while(target_snake != NULL){
				if (equal(scan, target_snake->getPosition())) {
					draw_buffer = 's';
				}
				target_snake = target_snake->getNext();
			}
			for (int i = 1; i <= objs->quantity; i++) {
				if (equal(scan, objs->getFruit(i).getPosition())) {
					if(objs->getFruit(i).getType() == 'f'){
						draw_buffer = 'f';
					}else if(objs->getFruit(i).getType() == 'b'){
						draw_buffer = objs->getFruit(i).getLifeTime();
					}else{
						draw_buffer = 'e';
					}
				}
			}
			drawBuffer(draw_buffer);
		}
		std::cout << endl;
	}
}
void renderMenu(game_config* cfg) {
	system("cls");
	COLOR_TEXT;
	_2D menu_position = { (int)cfg->stage.x/2 - 4, (int)cfg->stage.y/2 - 4};
	_2D scan = { 0, 0 };
	for (scan.y = 0; scan.y <= cfg->stage.y + 1; scan.y += 1) {
		for (scan.x = 0; scan.x <= cfg->stage.x + 1; scan.x += 1) {
			if (scan.y == menu_position.y) {
				if (scan.x == menu_position.x + 1) {
					COLOR_WARNING;
					std::cout << "Game over!";
					COLOR_TEXT;
					scan.x += 4;
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 2) {
				if (scan.x == menu_position.x) {
					std::cout << " Your Score   : ";
					COLOR_SCORE;
					if (cfg->score <= 9) {
						std::cout << " 0";
						scan.x += 1;
					}else if (cfg->score <= 99) {
						std::cout << cfg->score;
						scan.x += 1;
					}else if (cfg->score <= 999) {
						std::cout << " " << cfg->score;
						scan.x += 2;
					}else if (cfg->score <= 9999) {
						std::cout << cfg->score;
						scan.x += 2;
					}
					COLOR_TEXT;
					scan.x += 7;
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 4) {
				if (scan.x == menu_position.x) {
					std::cout << "Select an option  : ";
					scan.x += 9;
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 5) {
				if (scan.x == menu_position.x + 2) {
					if (cfg->game_status == 'c') {
						COLOR_SELECTION;
						std::cout << "-> Continue ";
						COLOR_TEXT;
						scan.x += 5;
					}
					else {
						std::cout << "Continue  ";
						scan.x += 4;
					}
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 6) {
				if (scan.x == menu_position.x + 2) {
					if (cfg->game_status == 'q') {
						COLOR_SELECTION;
						std::cout << "-> Quit.";
						COLOR_TEXT;
						scan.x += 3;
					}
					else {
						std::cout << "Quit..";
						scan.x += 2;
					}
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 8) {
				if (scan.x == menu_position.x) {
					std::cout << "High scores : ";
					scan.x += 6;
				}
				else {
					std::cout << " .";
				}
			}
			else if (scan.y == menu_position.y + 9) {
				if (scan.x == menu_position.x) {
					COLOR_SCORE;
					for (int h = 9; h >= 5; h--) {
						if (stoi(cfg->getData(h)) <= 9) {
							std::cout << " " << cfg->getData(h) << ", ";
							scan.x += 2;
						}
						else if (stoi(cfg->getData(h)) <= 99) {
							std::cout << cfg->getData(h) << ", ";
							scan.x += 2;
						}
						else if (stoi(cfg->getData(h)) <= 999) {
							std::cout << " " << cfg->getData(h) << ", ";
							scan.x += 3;
						}
						else if (stoi(cfg->getData(h)) <= 9999) {
							std::cout << cfg->getData(h) << ", ";
							scan.x += 3;
						}
					}
					COLOR_TEXT;
				}
				std::cout << " .";
			}
			else if (scan.y == menu_position.y + 10) {
			if (scan.x == menu_position.x) {
				COLOR_SCORE;
				for (int h = 4; h >= 0; h--) {
					if (stoi(cfg->getData(h)) <= 9) {
						std::cout << " " << cfg->getData(h) << ", ";
						scan.x += 2;
					}
					else if (stoi(cfg->getData(h)) <= 99) {
						std::cout << cfg->getData(h) << ", ";
						scan.x += 2;
					}
					else if (stoi(cfg->getData(h)) <= 999) {
						std::cout << " " << cfg->getData(h) << ", ";
						scan.x += 3;
					}
					else if (stoi(cfg->getData(h)) <= 9999) {
						std::cout << cfg->getData(h) << ", ";
						scan.x += 3;
					}
				}
				COLOR_TEXT;
			}
			std::cout << " .";
			}
			else {
				std::cout << " .";
			}
		}
		std::cout << std::endl;
	}
}

#endif