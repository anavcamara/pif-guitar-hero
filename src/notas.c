#include <stdlib.h>
#include "notas.h"

static void removerNota(Nota **lista, Nota *anterior, Nota *atual) {
    if (anterior == NULL) {
        *lista = atual->prox;
    }else{
        anterior->prox = atual->prox;
    }
    free(atual);
}

int notaCriar(Nota **lista, int coluna, int y){
    if (coluna < 0 || coluna >= NUM_COLUNAS){
        return 0;
    }

    Nota *nova = malloc(sizeof(Nota));
    if(nova == NULL){
        return 0;
    }

    nova->coluna = coluna;
    nova->y = y;

    nova->prox = *lista;
    *lista = nova;

    return 1;
}  

void notasMover(Nota **lista){
    Nota *atual = *lista;
    while(atual != NULL){
        atual->y++;
        atual = atual->prox;
    }
}

int notasRemoverPerdidas(Nota **lista, int limiteY){
    int removidas = 0;
    Nota *anterior = NULL;
    Nota *atual = *lista;

    while(atual != NULL){
        Nota *proxima = atual->prox;

        if (atual->y > limiteY){
            removerNota(lista, anterior, atual);
            removidas++;
        }else{
            anterior = atual;
        }
        atual = proxima;
    }
    return removidas;
}

ResultadoAcerto  notasVerificarAcerto(Nota **lista, int coluna, int linhaAcerto){
    Nota *anterior = NULL;
    Nota *atual = *lista;

    Nota *melhor = NULL;
    Nota *anteriorDaMelhor = NULL;
    int menorDistancia = JANELA_BOM +1;

    while(atual != NULL){
        if(atual->coluna == coluna){
            int distancia = abs(atual->y - linhaAcerto);
            if(distancia < menorDistancia){
                menorDistancia = distancia;
                melhor = atual;
                anteriorDaMelhor = anterior;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }
    if(melhor == NULL){
        return ACERTO_ERRO;
    }
    removerNota(lista, anteriorDaMelhor, melhor);

    if(menorDistancia <= JANELA_PERFEITO){
        return ACERTO_PERFEITO;
    }
    return ACERTO_BOM;
}

int notasContar(Nota *lista){
    int total = 0;
    Nota *atual = lista;
    while (atual != NULL){
        total++;
        atual = atual->prox;
    }
    return total;
}

void notasLiberar(Nota **lista){
    Nota *atual = *lista;
    while(atual != NULL){
        Nota *proxima = atual->prox;
        free(atual);
        atual = proxima;
    }
    *lista = NULL;
}