#ifndef TELA_H
#define TELA_H

#include "pontuacao.h"

#define LINHA_ACERTO 19
#define PISTA_X 13
#define LARGURA_PISTA 12   // 1 divisoria + 11 colunas internas

void desenharMenu(int selecionada);
void desenharOpcoes(int selecionada);
void desenharComoJogar();

void desenharPads();
void desenharCenario();

void desenharNota(int pista, int y);
void apagarNota(int pista, int y);

void desenharPainel(const Placar *placar);

void desenharFimDeJogo(const Placar *placar);
void desenharPedirNome(char nome[]);
void desenharRanking(RegistroRanking ranking[], int quantidade, int destaque);

void limparPista(int pista);

#endif