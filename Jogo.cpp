#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "cobrinha.h"
#include "fruta.h"
#include "entrada.h"
#include "renderizar.h"


using namespace std;

void ResetarJogo(Cobrinha &obj) {
	obj.Resetar();
	Pontuacao = 0;
}

int main() {
	//Vari�vies globais.
	char EntradaDeMenu[64];
	Cobrinha *cobrinha = new Cobrinha();
	Frutas Frutinhas;
	//Carrega o hist�rico de pontua��es
	Carregar();
	//Declara o esquema de caracteres para o portugu�s.
	setlocale(LC_ALL, "portuguese");
	//Personaliza a cor do terminal.
	//Inicia o jogo com uma fruta.
	Frutinhas.NovaFruta();
	//Define um loop para o jogo.
	while (JogoStatus != 'f') {
		//Aguarda um tempo espec�fico para o loop continuar
		//Isso faz com que a velocidade do loop esteja em fun��o do tempo e n�o da velocidade do computador.
		Sleep(20);
		if (JogoStatus == 'j') {
			MovimentarObjeto(*cobrinha);
			cobrinha->Atualizar();
			if (cobrinha->Vida == false) {
				Salvar(Pontuacao);
				JogoStatus = 'c';
			}
			for (int i = 0; i < Frutinhas.Tamanho; i++) {
				Frutinhas.Atualizar(i);
				if (cobrinha->Pos.x == Frutinhas.ObterFruta(i).Pos.x && cobrinha->Pos.y == Frutinhas.ObterFruta(i).Pos.y) {
					if (Frutinhas.ObterFruta(i).Tipo == 'f') {
						switch (Pontuacao) {
						case 2:
							Frutinhas.NovoBonus();
							break;
						case 9:
							Frutinhas.NovoBonus(2);
							break;
						case 24:
							Frutinhas.NovoBonus(3);
							break;
						case 49:
							Frutinhas.NovoBonus(4);
							break;
							break;
						case 74:
							Frutinhas.NovoBonus(5);
							break;
						case 99:
							Frutinhas.NovoBonus(6);
							break;
						}
						Pontuacao += 1;
						cobrinha->Crescer();
						Frutinhas.Formatar(i);
					}else if (Frutinhas.ObterFruta(i).Tipo == 'b') {
						Pontuacao += 5;
						cobrinha->Crescer(5);
						Frutinhas.RemoverFruta(i);
					}
				}
			}
			RenderizarJogo(*cobrinha, Frutinhas);
		}
		else {
			if (JogoStatus == 'c') {
				char Valor = SelecionarOpcao();
				if (Valor == 's') {
					JogoStatus = 's';
				}
				else if (Valor == '\r') {
					ResetarJogo(*cobrinha);
					JogoStatus = 'j';
				}
				RenderizarMenu(JogoStatus);
			}else if (JogoStatus == 's') {
				char Valor = SelecionarOpcao();
				if (Valor == 'w') {
					JogoStatus = 'c';
				}else if (Valor == '\r') {
					JogoStatus = 'f';
				}
				RenderizarMenu(JogoStatus);
			}
			else {
				cout << JogoStatus;
			}
		}
	}
	//Declara o fim da aplica��o.
	cout << endl << "Fim" << endl;
	system("pause");
	return EXIT_SUCCESS;
}