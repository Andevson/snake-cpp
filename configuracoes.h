#ifndef CONFIGURACOES_CPP
#define CONFIGURACOES_CPP

#include <string>
#include <iostream>
#include <fstream>
#include "matematica.h"

using namespace std;

//Variáveis globais.
char JogoStatus = 'j';
int Pontuacao = 0;
_2D Palco = { 20, 20 };
#define COR_COBRINHA std::cout << "\x1b[32m"//Verde.
#define COR_FRUTA std::cout << "\x1b[31m"//Vermelha.
#define COR_BONUS std::cout << "\x1b[35m"//Magenta.
#define COR_PAREDES std::cout << "\x1b[36m"//Ciano.
#define COR_TEXTO std::cout << "\x1b[37m"//Branco.
#define COR_AVISO std::cout << "\x1b[31m"//Vermelho.
#define COR_PONTUACAO std::cout << "\x1b[33m"//Amarelo.
#define COR_SELECAO std::cout << "\x1b[34m"//Azul.

fstream Pontuacoes;
string Data[10] = {"0","0","0","0","0","0","0","0","0","0",};

//Carrega o histórico de pontuação.
void Carregar(void) {
    string Linha;
    Pontuacoes.open("pontuacao.jogodacobrinha", ios::in);
    int i = 0;
    while (getline(Pontuacoes, Linha) && i <= 9) {
        if (stoi(Linha) >= 0) {
            Data[i] = Linha;
        }
        else {
            Data[i] = "0";
        }
        i++;
    }
    Pontuacoes.close();
}

//Salva o histórico de pontuação.
void Salvar(int Pontos) {
    Carregar();
    for (int i = 9; i >= 0; i--) {
        if (Pontos > stoi(Data[i])) {
            if (i >= 1) {
                for (int j = 0; j <= i - 1; j++) {
                    Data[j] = Data[j + 1];
                }
            }
            Data[i] = to_string(Pontos);
            break;
        }
    }
    Pontuacoes.open("pontuacao.jogodacobrinha", ios::out);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j < Data[i].length(); j++) {
            Pontuacoes.put(Data[i][j]);
        }
        Pontuacoes.put('\n');
    }
    Pontuacoes.close();
}

#endif