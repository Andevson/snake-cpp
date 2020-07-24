#ifndef ENTRADA_CPP
#define ENTRADA_CPP

#include <conio.h>
#include "cobrinha.h"

//Converte as entradas do teclado em valores base para movimentação da cobrinha.
void MovimentarObjeto(Cobrinha& obj) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (obj.Acel.y == 0) {
				obj.Acel = { 0, -1 };
			}
			break;
		case 'a':
			if (obj.Acel.x == 0) {
				obj.Acel = { -1, 0 };
			}
			break;
		case 's':
			if (obj.Acel.y == 0) {
					obj.Acel = { 0, 1 };
			}
			break;
		case 'd':
			if (obj.Acel.x == 0) {
				obj.Acel = { 1, 0 };
			}
			break;
		}
	}
}

//Converte as entradas do teclado em valores base para navegação em menu.
char SelecionarOpcao(void) {
	char Resultado;
	if (_kbhit()) {
		Resultado = _getch();
	}
	else {
		Resultado = ' ';
	}
	return Resultado;
}

#endif