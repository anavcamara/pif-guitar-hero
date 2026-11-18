#ifndef MAPA_H
#define MAPA_H

#include "config.h"
#include "notas.h"

typedef struct {
    char nome[ RANKING_TAMANHO_NOME + 1];
    char musica_audio[ RANKING_TAMANHO_NOME + 1];
    int bpm;
    int linhas_por_batida;
    int offset_ms;
    int total_linhas;
    int **linhas;
    int cursor;
} Mapa;

Mapa *carregar_mapa(const char *nome_musica);
int proxima_linha(Mapa *mapa, int linha[MAPA_COLUNAS]);
void criar_notas_da_linha(Mapa *mapa, Nota **lista, int y);
int mapa_acabou(const Mapa *mapa);
int ms_por_linha(const Mapa *mapa);
void liberar_mapa(Mapa *mapa);

#endif