#ifndef FRUTA_H
#define FRUTA_H

#include "matematica.h"
#include "configuracoes.h"

//Define uma nova fruta.
class Fruta {
public:
	//Vari�veis globais.
	_2D Pos = { 0, 0 };
	char Tipo;
	float Tempo;
	//Redefine as propriedades da fruta com os valores para o tipo fruta.
	void FormatarF(void) {
		Tipo = 'f';
		NovaPosicao();
	}
	//Redefine as propriedades da fruta com os valores para o tipo b�nus.
	void FormatarB(void) {
		Tempo = 6;
		Tipo = 'b';
		NovaPosicao();
	}
	//M�todo construtor com propriedades iniciais do tipo fruta.
	Fruta(void) {
		FormatarF();
	}
	//M�todo construtor com propriedades iniciais do tipo passado por par�metro.
	Fruta(char NovoTipo) {
		if (NovoTipo == 'f' || NovoTipo == 'F') {
			FormatarF();
		}else if (NovoTipo == 'b' || NovoTipo == 'B') {
			FormatarB();
		}
	}
	//M�todo construtor com posi��o e propriedades iniciais do tipo passados por par�metros.
	Fruta(_2D NovaPosicao, char NovoTipo) {
		if (NovoTipo == 'f' || NovoTipo == 'F') {
			FormatarF();
		}
		else if (NovoTipo == 'b' || NovoTipo == 'B') {
			FormatarB();
		}
		Pos = NovaPosicao;
	}
	//Define uma nova posi��o para a fruta.
	void NovaPosicao(void) {
		Pos = {(int)rand() % Palco.x + 1, (int)rand() % Palco.x + 1 };
	}
	//Atualiza as propriedades da fruta.
	boolean Atualizar(void) {
		if (Tipo == 'b') {
			if (Tempo > 0) {
				Tempo -= 0.1;
			}
			else {
				return true;
			}
		}
		return false;
	}
};

//Define uma nova cole��o de frutas.
struct Frutas {
private:
	//Vari�veis locais.
	Fruta frutas[32];
public:
	//Vari�veis globais.
	int Tamanho = 0;
	//Adiciona uma nova fruta do tipo padr�o a cole��o de frutas.
	void NovaFruta(void) {
		if (Tamanho < 30) {
			Fruta *NFruta = new Fruta();
			frutas[Tamanho] = *NFruta;
			Tamanho += 1;
		}
	}
	//Adiciona uma nova fruta do tipo b�nus a cole��o de frutas.
	void NovoBonus(void) {
		if (Tamanho < 30) {
			Fruta* NFruta = new Fruta('b');
			frutas[Tamanho] = *NFruta;
			Tamanho += 1;
		}
	}
	//Adiciona uma nova quantidade de frutas, passada por par�metro, do tipo b�nus, a cole��o de frutas.
	void NovoBonus(int Quantidade) {
		while (Quantidade > 0 && Tamanho < 30) {
			NovoBonus();
			Quantidade -= 1;
		}
	}
	//Obt�m uma fruta ou b�nus da cole��o de frutas.
	Fruta ObterFruta(int Posicao) {
		return frutas[Posicao];
	}
	void RemoverFruta(int Posicao) {
		if (Tamanho >= 2) {
			for (int i = Posicao; i < Tamanho - 1; i++) {
				frutas[Posicao] = frutas[Posicao + 1];
			}
		}
		Tamanho -= 1;
	}
	//Redefine as propriedades de uma fruta da cole��o de frutas.
	void Formatar(int Posicao) {
		if (frutas[Posicao].Tipo == 'f') {
			frutas[Posicao].FormatarF();
		}
		else if (frutas[Posicao].Tipo == 'b') {
			frutas[Posicao].FormatarB();
		}
	}
	//Atualiza uma fruta passada por par�metro da cole��o.
	void Atualizar(int Posicao) {
		if (frutas[Posicao].Atualizar()) {
			RemoverFruta(Posicao);
		}
	}
};
#endif // !FRUTA_H
