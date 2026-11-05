#include "config.h"

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
int mapa_acabou(const Mapa *mapa);
int ms_por_linha(const Mapa *mapa);
void liberar_mapa(Mapa *mapa);
