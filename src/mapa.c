#include "mapa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void liberar_linhas(int **linhas, int quantidade)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        free(linhas[i]);
    }
    free(linhas);
}

Mapa *carregar_mapa(const char *nome_musica)
{
    FILE *musica;
    Mapa *mapa;
    char nome[RANKING_TAMANHO_NOME + 1];
    char musica_audio[RANKING_TAMANHO_NOME + 1];
    int valor;
    int i;
    int j;

    musica = fopen(nome_musica, "r");
    if (musica == NULL) {
        return NULL;
    }

    mapa = malloc(sizeof(Mapa));
    if (mapa == NULL) {
        fclose(musica);
        return NULL;
    }

    if (fscanf(musica, "%30s %30s %d %d %d %d",
               nome, musica_audio, &mapa->bpm,
               &mapa->linhas_por_batida, &mapa->total_linhas,
               &mapa->offset_ms) != 6) {
        free(mapa);
        fclose(musica);
        return NULL;
    }

    if (mapa->bpm <= 0 || mapa->linhas_por_batida <= 0 ||
        mapa->total_linhas < 0) {
        free(mapa);
        fclose(musica);
        return NULL;
    }

    strcpy(mapa->nome, nome);
    strcpy(mapa->musica_audio, musica_audio);
    mapa->cursor = 0;
    mapa->linhas = malloc(mapa->total_linhas * sizeof(int *));
    if (mapa->linhas == NULL && mapa->total_linhas > 0) {
        free(mapa);
        fclose(musica);
        return NULL;
    }

    for (i = 0; i < mapa->total_linhas; i++) {
        mapa->linhas[i] = malloc(MAPA_COLUNAS * sizeof(int));
        if (mapa->linhas[i] == NULL) {
            liberar_linhas(mapa->linhas, i);
            free(mapa);
            fclose(musica);
            return NULL;
        }

        for (j = 0; j < MAPA_COLUNAS; j++) {
            if (fscanf(musica, "%d", &valor) != 1 ||
                (valor != 0 && valor != 1)) {
                liberar_linhas(mapa->linhas, i + 1);
                free(mapa);
                fclose(musica);
                return NULL;
            }
            mapa->linhas[i][j] = valor;
        }
    }

    fclose(musica);
    return mapa;
}

int proxima_linha(Mapa *mapa, int linha[MAPA_COLUNAS])
{
    int coluna;

    if (mapa_acabou(mapa)) {
        return 0;
    }

    for (coluna = 0; coluna < MAPA_COLUNAS; coluna++) {
        linha[coluna] = mapa->linhas[mapa->cursor][coluna];
    }
    mapa->cursor++;

    return 1;
}

int mapa_acabou(const Mapa *mapa)
{
    return mapa->cursor >= mapa->total_linhas;
}

int ms_por_linha(const Mapa *mapa)
{
    return 60000 / mapa->bpm / mapa->linhas_por_batida;
}

void liberar_mapa(Mapa *mapa)
{
    if (mapa == NULL) {
        return;
    }

    liberar_linhas(mapa->linhas, mapa->total_linhas);
    free(mapa);
}
