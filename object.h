#include <stdlib.h>

#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "mat.h"

using namespace std;

class snake {
	private:
	snake* next = NULL;
	_2D position = { 1, 1 };
	_2D aceleration = { 0, 0 };
	int weight = 1;

	public:
	snake(){
		//
	}
	snake(_2D new_position){
		position = new_position;
	}
	_2D getPosition(void){
		return position;
	}
	int getWeight(void){
		return weight;
	}
	snake* getNext(void){
		return next;
	}
	void setPosition(_2D new_position){
		position = new_position;
	}
	void move(_2D new_aceleration){
		if(new_aceleration.x != 0 || new_aceleration.y != 0){
			aceleration = new_aceleration;
		}
		if(next != NULL){
			if(!equal(next->getPosition(), getPosition())){
				next->move( {getPosition().x - next->getPosition().x, getPosition().y - next->getPosition().y} );
			}
		}
		setPosition(sum(position, aceleration));
	}
	void grow(){
		weight += 1;
		if(next != NULL){
			next->grow();
		}else{
			next = new snake(position);
		}
	}
	bool hitPoint(_2D hit_point) {
		if(equal(getPosition(), hit_point)){
			return true;
		}else{
			return false;
		}
	}
	bool hitArea(_2D hit_point) {
		_2D new_position = getPosition();
		if(new_position.x == 0
		|| new_position.x == hit_point.x + 1
		|| new_position.y == 0
		|| new_position.y == hit_point.y + 1){
			return true;
		}else{
			return false;
		}
	}
	bool hitSelf(void){
		snake* n = next;
		while(n != NULL){
			if(equal(n->getPosition(), getPosition()) && !equal(n->aceleration, {0, 0})){
				return true;
			}
			n = n->getNext();
		}
		return false;
	}
	void reset(void) {
		aceleration = { 1, 0 };
		setPosition({ 1 , 1 });
		if(next != NULL){
			next->die();
		}
	}
	void reset(_2D new_position) {
		reset();
		setPosition(new_position);
	}
	void die(){
		if(next != NULL){
			next->die();
			delete next;
		}
	}
};

class fruit {
	
	private:
	_2D position;
	float life_time;
	char type;

	public:
	fruit(void) {
		position = {1, 1};
		life_time = 1;
		type = 'e';
	}
	fruit(_2D new_position, char new_type){
		position = new_position;
		type = new_type;
		switch(new_type){
			case 'f':
			life_time = 9999;
			break;
			case 'b':
			life_time = 10;
			break;
			default :
			life_time = 9999;
			type = 'f';
			break;
		}
	}
	_2D getPosition(void){
		return position;
	}
	char getType(void){
		return type;
	}
	int getLifeTime(void){
		return life_time;
	}
	void setPosition(_2D new_position){
		position = new_position;
	}
	void setType(char new_type){
		type = new_type;
	}
	void update(void) {
		life_time -= 1;
	}
};

class objects {

	private:
	fruit fruit_array[32] = {};
	snake* game_snake = NULL;
	
	public:
	object(void){
		//
	}
	int quantity = 0;
	void newSnake(_2D new_position){
		game_snake = new snake(new_position);
	}
	void newFruit(_2D stage_size) {
		fruit* new_fruit = new fruit(random(stage_size), 'f');
		if (quantity < 30) {
			quantity += 1;
			fruit_array[quantity] = *new_fruit;
		}
		delete new_fruit;
	}
	void newBonus(_2D stage_size) {
		fruit* new_fruit = new fruit(random(stage_size), 'b');
		if (quantity < 30) {
			quantity += 1;
			fruit_array[quantity] = *new_fruit;
		}
	}
	fruit getFruit(int new_index) {
		return fruit_array[new_index];
	}
	snake* getSnake(void){
		if(game_snake != NULL){
			return game_snake;
		}else{
			return 0;
		}
	}
	void removeObj(int new_index) {
		int index_scan = new_index;
		while(index_scan < quantity){
			fruit_array[index_scan] = fruit_array[index_scan + 1];
			index_scan++;
		}
		quantity -= 1;
	}
	void removeSnake(void){
		delete game_snake;
		game_snake = NULL;
	}
	void removeFruits(void){
		quantity = 0;
	}
	void update(void) {
		for(int i = 1; i <= quantity; i++){
			fruit_array[i].update();
			if(fruit_array[i].getLifeTime() < 0){
				if(fruit_array[i].getType() == 'b'){
					removeObj(i);
				}
			}
		}
		if(quantity == 0){
			newFruit(STAGE);
		}
	}
	void reset(void){
		removeSnake();
		removeFruits();
		newSnake(MIDDLE_STAGE);
	}
	
};

#endif
