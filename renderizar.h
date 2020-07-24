#ifndef RENDERIZAR_CPP
#define RENDERIZAR_CPP

#include <iostream>
#include "matematica.h"
#include "configuracoes.h"
#include "cobrinha.h"
#include "fruta.h"

//Renderiza o palco.
void RenderizarJogo(Cobrinha Obj, Frutas frutas) {
	system("cls");//system("clear") para linux.
	COR_TEXTO;
	std::cout << "Pontuacao : ";
	COR_PONTUACAO;
	cout << Pontuacao << std::endl;
	COR_PAREDES;
	_2D Varr = { 0, 0 };
	for (Varr.y = 0; Varr.y <= Palco.y + 1; Varr.y += 1) {
		for (Varr.x = 0; Varr.x <= Palco.x + 1; Varr.x += 1) {
			boolean Check = false;
			for (int i = 0; i <= Obj.Tamanho; i++) {
				if (Varr.x == Obj.Pos.x && Varr.y == Obj.Pos.y) {
					COR_COBRINHA;
					std::cout << " O";
					COR_PAREDES;
					Check = true;
					i = Obj.Tamanho;
				}
				if(Varr.x == Obj.Corpo[i].x && Varr.y == Obj.Corpo[i].y && Obj.Tamanho >= 1) {
					COR_COBRINHA;
					std::cout << " o";
					COR_PAREDES;
					Check = true;
					i = Obj.Tamanho;
				}
				
				if (Varr.x == 0 || Varr.x == Palco.x + 1 || Varr.y == 0 || Varr.y == Palco.y + 1) {
					std::cout << " X";
					Check = true;
					i = Obj.Tamanho;
				}
			}
			for (int i = 0; i < frutas.Tamanho; i++) {
				if (Varr.x == frutas.ObterFruta(i).Pos.x && Varr.y == frutas.ObterFruta(i).Pos.y && !Check) {
					if (frutas.ObterFruta(i).Tipo == 'f') {
						COR_FRUTA;
						std::cout << " F";
						COR_PAREDES;
					}else if(frutas.ObterFruta(i).Tipo == 'b') {
						COR_BONUS;
						std::cout << " " << (int)frutas.ObterFruta(i).Tempo;
						COR_PAREDES;
					}
					Check = true;
				}
			}
			if (!Check) {
				std::cout << "  ";
			}

		}
		std::cout << std::endl;
	}
}

//Renderiza os menus.
void RenderizarMenu(char Estado) {
	system("cls");//system("clear") para linux.
	std::cout << "\x1b[37m";
	_2D MPos = { (int)Palco.x/2 - 4, (int)Palco.y/2 - 4};//Posição do menu.
	//Inicia a varredura em duas dimensões.
	_2D Varr = { 0, 0 };
	for (Varr.y = 0; Varr.y <= Palco.y + 1; Varr.y += 1) {
		for (Varr.x = 0; Varr.x <= Palco.x + 1; Varr.x += 1) {
			if (Varr.y == MPos.y) {
				if (Varr.x == MPos.x + 1) {
					COR_AVISO;
					std::cout << "Fim de jogo!";
					COR_TEXTO;
					Varr.x += 5;
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 2) {
				if (Varr.x == MPos.x) {
					std::cout << "Sua Pontuação : ";
					COR_PONTUACAO;
					if (Pontuacao <= 9) {
						std::cout << " 0";
						Varr.x += 1;
					}else if (Pontuacao <= 99) {
						std::cout << Pontuacao;
						Varr.x += 1;
					}else if (Pontuacao <= 999) {
						std::cout << " " << Pontuacao;
						Varr.x += 2;
					}else if (Pontuacao <= 9999) {
						std::cout << Pontuacao;
						Varr.x += 2;
					}
					COR_TEXTO;
					Varr.x += 7;
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 4) {
				if (Varr.x == MPos.x) {
					std::cout << "Escolha uma opção : ";
					Varr.x += 9;
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 5) {
				if (Varr.x == MPos.x + 2) {
					if (Estado == 'c') {
						COR_SELECAO;
						std::cout << "-> Continuar";
						COR_TEXTO;
						Varr.x += 5;
					}
					else {
						std::cout << "Continuar ";
						Varr.x += 4;
					}
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 6) {
				if (Varr.x == MPos.x + 2) {
					if (Estado == 's') {
						COR_SELECAO;
						std::cout << "-> Sair.";
						COR_TEXTO;
						Varr.x += 3;
					}
					else {
						std::cout << "Sair";
						Varr.x += 1;
					}
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 8) {
				if (Varr.x == MPos.x) {
					std::cout << "Melhores pontuações : ";
					Varr.x += 10;
				}
				else {
					std::cout << " .";
				}
			}
			else if (Varr.y == MPos.y + 9) {
				if (Varr.x == MPos.x) {
					COR_PONTUACAO;
					for (int h = 0; h < 5; h++) {
						if (stoi(Data[h]) <= 9) {
							std::cout << " " << Data[h] << ", ";
							Varr.x += 2;
						}
						else if (stoi(Data[h]) <= 99) {
							std::cout << Data[h] << ", ";
							Varr.x += 2;
						}
						else if (stoi(Data[h]) <= 999) {
							std::cout << " " << Data[h] << ", ";
							Varr.x += 3;
						}
						else if (stoi(Data[h]) <= 9999) {
							std::cout << Data[h] << ", ";
							Varr.x += 3;
						}
					}
					COR_TEXTO;
				}
				std::cout << " .";
			}
			else if (Varr.y == MPos.y + 10) {
			if (Varr.x == MPos.x) {
				COR_PONTUACAO;
				for (int h = 5; h < 10; h++) {
					if (stoi(Data[h]) <= 9) {
						std::cout << " " << Data[h] << ", ";
						Varr.x += 2;
					}
					else if (stoi(Data[h]) <= 99) {
						std::cout << Data[h] << ", ";
						Varr.x += 2;
					}
					else if (stoi(Data[h]) <= 999) {
						std::cout << " " << Data[h] << ", ";
						Varr.x += 3;
					}
					else if (stoi(Data[h]) <= 9999) {
						std::cout << Data[h] << ", ";
						Varr.x += 3;
					}
				}
				COR_TEXTO;
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