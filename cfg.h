#include <string>
#include <iostream>
#include <fstream>

#ifndef CONFIG_CPP
#define CONFIG_CPP

#include "mat.h"

using namespace std;

//Global vars.
#define STAGE {20, 20}
#define MIDDLE_STAGE {10, 10}
#define COLOR_SNAKE std::cout << "\x1b[32m"//green.
#define COLOR_FRUIT std::cout << "\x1b[31m"//Red.
#define COLOR_BONUS std::cout << "\x1b[35m"//Magenta.
#define COLOR_WALL std::cout << "\x1b[36m"//Cyan.
#define COLOR_TEXT std::cout << "\x1b[37m"//White.
#define COLOR_WARNING std::cout << "\x1b[31m"//Red.
#define COLOR_SCORE std::cout << "\x1b[33m"//Yellow.
#define COLOR_SELECTION std::cout << "\x1b[34m"//Blue.

class game_config {

    private:
    //Data storage
    fstream data_scores;
    string scores[10] = {"0","0","0","0","0","0","0","0","0","0",};
    
    public:
    char game_status = 'j';
    int score = 0;
    _2D stage = { 20, 20 };
    string getData(int index){
        return scores[index];
    }
    //Load history of scores
    void load(void) {
        string line;
        data_scores.open("scores.snakecpp", ios::in);
        int i = 0;
        while (getline(data_scores, line) && i <= 9) {
            if (stoi(line) >= 0) {
                scores[i] = line;
            }
            else {
                scores[i] = "0";
            }
            i++;
        }
        data_scores.close();
    }
    //Save new scores in history of scores
    void save(int new_scores) {
        load();
        for (int i = 9; i >= 0; i--) {
            if (new_scores > stoi(scores[i])) {
                if (i >= 1) {
                    for (int j = 0; j <= i - 1; j++) {
                        scores[j] = scores[j + 1];
                    }
                }
                scores[i] = to_string(new_scores);
                break;
            }
        }
        data_scores.open("scores.snakecpp", ios::out);
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j < scores[i].length(); j++) {
                data_scores.put(scores[i][j]);
            }
            data_scores.put('\n');
        }
        data_scores.close();
    }
};

#endif