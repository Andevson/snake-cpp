#ifndef OBJETO_CPP
#define OBJETO_CPP

#include <stdlib.h>
#include "matematica.h"
#include "configuracoes.h"

class Cobrinha {
public:
	//Variáveis globais.
	bool Vida = true;
	_2D Pos = { 0, 0 }, Acel = { 1, 0 }, Corpo[600];
	int Tamanho = 0;
	//Método construtor com valores predefinidos.
	Cobrinha(void) {
		Resetar();
	}
	//Método construtor o tamanho da cobrinha passado por parâmetro.
	Cobrinha(int NovoTamanho) {
		Resetar();
		Tamanho = NovoTamanho;
	}
	//Atualiza as propriedades da cobrinha.
	void Atualizar(void) {
		if (Tamanho > 0) {
			int i = Tamanho;
			while (i > 0) {
				Corpo[i] = { Corpo[i - 1].x, Corpo[i - 1].y };
				i--;
			}
			Corpo[0] = { Pos.x, Pos.y };
		}
		Pos.x += Acel.x;
		Pos.y += Acel.y;
		DetectarColisao();
	}
	//Redefine as propriedades da cobrinha para os valores iniciais.
	void Resetar(void) {
		Vida = true;
		Acel = { 1, 0 };
		Tamanho = 0;
		Pos = { (int)Palco.x / 2 , (int)Palco.y / 2 };
	}
	//Aumenta o tamanho da cobrinha em 1 unidade.
	void Crescer(void) {
		Tamanho += 1;
		Corpo[Tamanho - 1] = Pos;
	}
	//Aumenta o tamanho da cobrinha em um valor passado por parâmetro.
	void Crescer(int Quanto) {
		for (int i = 0; i < Quanto; i++) {
			Tamanho += 1;
			Corpo[Tamanho - 1] = Pos;
		}
	}
	//Detecta colisões.
	void DetectarColisao(void) {
		if (Tamanho > 0) {
			for (int i = Tamanho; i > 0; i--) {
				if (Pos.x == Corpo[i].x && Pos.y == Corpo[i].y) {
					Vida = false;
				}
			}
		}
		else {
			Crescer();
		}
		if (Pos.x > Palco.x) {
			Pos.x = Palco.x;
			Vida = false;
		}
		else if (Pos.x < 1) {
			Pos.x = 1;
			Vida = false;
		}
		if (Pos.y > Palco.y) {
			Pos.y = Palco.y;
			Vida = false;
		}
		else if (Pos.y < 1) {
			Pos.y = 1;
			Vida = false;
		}
	}
};

#endif //