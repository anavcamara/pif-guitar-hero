#ifndef __NOTAS_H_
#define __NOTAS_H_

#define NUM_COLUNAS 4
#define JANELA_PERFEITO 0
#define JANELA_BOM 1

typedef enum {
    ACERTO_ERRO, 
    ACERTO_BOM, 
    ACERTO_PERFEITO

} ResultadoAcerto;

typedef struct Nota {
    int coluna;
    int y;
    struct Nota *prox;

} Nota;

int notaCriar(Nota **lista, int coluna, int y);

void notasMover(Nota **lista);

int notasRemoverPerdidas(Nota **lista, int limiteY);

ResultadoAcerto notasVerificarAcerto(Nota **lista, int coluna, int linhaAcerto);

int notasContar(Nota *lista);

void notasLiberar(Nota **lista);

#endif 