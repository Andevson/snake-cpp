#include <stdlib.h>

#ifndef MAT_CPP
#define MAT_CPP

using namespace std;

struct _2D {
	int x;
	int y;
};
_2D sum(_2D value1, _2D value2){
	return {value1.x + value2.x, value1.y + value2.y};
};
bool equal(_2D value1, _2D value2){
	if(value1.x == value2.x && value1.y == value2.y){
		return true;
	}else{
		return false;
	};
};
_2D minus(_2D value1, _2D value2){
	return {value1.x - value2.x, value1.y - value2.y};
};
_2D negative(_2D value){
	return {-value.x , -value.y};
};
int random(int value){
	return { rand() % value };
}
_2D random(_2D value){
	return {random(value.x) + 1, random(value.y) + 1};
};

#endif