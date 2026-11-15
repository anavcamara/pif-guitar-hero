#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "tela.h"
#include "menu.h"
#include "notas.h"

int main() {
    srand(time(NULL));
    static int ch = 0;

    screenInit(1);
    screenHideCursor();
    keyboardInit();
    timerInit(50);

    int opcao = telaInicial();

    Nota *lista = NULL;

    if (opcao == 0) // JOGAR
    {
        desenharCenario();
        screenSetColor(WHITE, BLACK);
        screenUpdate();

        int contador = 0;
        int proximaColuna = 0;

        while (ch != 10) // sai com enter
        {
            // Handle user input
            if (keyhit())
            {
                ch = readch();
                int colunaTecla = -1;

                if(ch == 'd' || ch == 'D'){
                    colunaTecla = 0;
                }else if (ch == 'f' || ch == 'F'){
                    colunaTecla = 1;
                }else if (ch == 'j' || ch == 'J'){
                    colunaTecla = 2;
                }else if (ch == 'k' || ch == 'K'){
                    colunaTecla = 3;
                }
                
                if(colunaTecla != -1){
                    ResultadoAcerto resultado = notasVerificarAcerto(&lista, colunaTecla, LINHA_ACERTO);

                    if(resultado == ACERTO_PERFEITO){
                        screenSetColor(LIGHTGREEN, BLACK);
                        screenGotoxy(10, 5);
                        printf("PERFEITO!");
                    }else if(resultado == ACERTO_BOM){
                        screenSetColor(YELLOW, BLACK);
                        screenGotoxy(10, 5);
                        printf("BOM!");
                    }else{
                        screenSetColor(LIGHTRED, BLACK);
                        screenGotoxy(10, 5);
                        printf("ERRO!");
                    }
                }
            }

            // Update game state (move elements, verify collision, etc)
            if (timerTimeOver() == 1) {
                
                Nota *atual = lista;

                while (atual != NULL) {
                    apagarNota(atual->coluna, atual->y);
                    atual = atual->prox;
                }

                notasMover(&lista);
                contador++;

                if (contador >= 10){
                    int colunaAleatoria = rand() % NUM_COLUNAS;
                    notaCriar(&lista, colunaAleatoria, 3);
                    contador = 0;
                }

                notasRemoverPerdidas(&lista, LINHA_ACERTO +1);
                atual = lista;
                while(atual != NULL) {
                    desenharNota(atual->coluna, atual->y);
                    atual = atual->prox;
                }

                screenSetColor(WHITE, BLACK);
                screenUpdate();
            }
        }
                
    }

    notasLiberar(&lista);

    keyboardDestroy();
    screenShowCursor();
    screenDestroy();
    timerDestroy();

    return 0;
}