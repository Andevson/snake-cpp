#include <conio.h>
#include "mat.h"

#ifndef INPUT_CPP
#define INPUT_CPP

// convert key into axis
_2D getAxis(void) {
	_2D axis = {0, 0};
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
			axis = { 0, -1 };
			break;
			case 'a':
			axis = { -1, 0 };
			break;
			case 's':
			axis = { 0, 1 };
			break;
			case 'd':
			axis = { 1, 0 };
			break;
		}
	}
	return axis;
}

//get key
char getKey(void) {
	char key;
	if (_kbhit()) {
		key = _getch();
	}
	else {
		key = ' ';
	}
	return key;
}

#endif