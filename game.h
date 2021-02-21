#include "object.h"
#include "cfg.h"
#include "input.h"

#ifndef GAME_CPP
#define GAME_CPP

using namespace std;

class game {

    private:
    string status;
    int score;
    int game_time;
    game_config* game_cfg;
	objects* game_objects;
    int getGameTime(void){
        return game_time;
    }
    void setStatus(string new_status){
        status = new_status;
    }
    void setScore(int new_score){
        score = new_score;
    }
    void setGameTime(int new_game_time){
        game_time = new_game_time;
    }
    void resetGame(void){
        setScore(0);
        setGameTime(0);
        game_objects->reset(game_cfg->getMiddleStage());
    };
    void gamePlay(void){
        if(game_objects->getSnake() == NULL){
            game_cfg->save(getScore());
            setStatus("menu_play");
        }else{
            game_objects->update();
            if(game_objects->getLength() == 0){
                if((getGameTime() % 10) == 0 && getGameTime() != 0){
                    game_objects->newBonus(game_cfg->getStage());
                }
                game_objects->newFruit(game_cfg->getStage());
                setGameTime(getGameTime() + 1);
            }
            game_objects->getSnake()->move(getAxis());
            for (int i = 1; i <= game_objects->getLength(); i++) {
                game_objects->getFruit(i).update();
                if (game_objects->getSnake()->hitPoint(game_objects->getFruit(i).getPosition())) {
                    if(game_objects->getFruit(i).getType() == 'f'){
                        setScore(getScore() + 10);
                    }else if(game_objects->getFruit(i).getType() == 'b'){
                        setScore(getScore() + 50);
                    }
                    game_objects->getSnake()->grow();
                    game_objects->removeObj(i);
                }
            }
            if(game_objects->getSnake()->hitArea(game_cfg->getStage()) || game_objects->getSnake()->hitSelf()){
                game_objects->removeFruits();
                game_objects->removeSnake();
                std::cout << "\nGAME OVER";
                Sleep(1000);
            }
        }
    }
    void menuPlay(void){
        char Key = getKey();
        if (getStatus() == "menu_play") {
            if (Key == 's') {
                setStatus("menu_quit");
            }
            else if (Key == '\r') {
                resetGame();
                setStatus("game_playing");
            }
        }else if (getStatus() == "menu_quit") {
            if (Key == 'w') {
                setStatus("menu_play");
            }else if (Key == '\r') {
                setStatus("quit");
            }
        }else{
            setStatus("menu_play");
        }
    }

    public:
    game(game_config* new_game_cfg, objects* new_game_objects){
        status = "menu_play";
        score = 0;
        game_cfg = new_game_cfg;
        game_objects = new_game_objects;
    }
	string getStatus(void){
        return status;
    }
    int getScore(void){
        return score;
    }
    void play(void){
        if(getStatus() == "game_playing"){
            gamePlay();
        }else{
            menuPlay();
        }
    }
};

#endif