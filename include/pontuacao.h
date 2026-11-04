#include "config.h"

typedef struct {
    int pontos;
    int combo;
    int maior_combo;
    int vidas;
    int perfeitos;
    int bons;
    int erros;
} Placar;

typedef struct {
    char nome[RANKING_TAMANHO_NOME + 1];
    int pontos;
} RegistroRanking;

void iniciar_placar(Placar *placar);
void registrar_acerto(Placar *placar, TipoAcerto resultado);
int calcular_multiplicador(int combo);
int jogo_acabou(const Placar *placar);

int carregar_ranking(const char *nome_arquivo,
                     RegistroRanking ranking[RANKING_QUANTIDADE]);
int inserir_ranking(RegistroRanking ranking[RANKING_QUANTIDADE],
                    int *quantidade, const char *nome, int pontos);
int salvar_ranking(const char *nome_arquivo,
                   const RegistroRanking ranking[RANKING_QUANTIDADE],
                   int quantidade);
