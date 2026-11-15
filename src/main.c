#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "tela.h"
#include "menu.h"
#include "notas.h"
#include "pontuacao.h"
#include "mapa.h"
#include "ranking.h"

int main() {
    static int ch = 0;

    screenInit(1);
    screenHideCursor();
    keyboardInit();
    timerInit(50);

    int opcao = telaInicial();

    Nota *lista = NULL;

    while (opcao == 0) // JOGAR
    {
        Mapa *mapa = carregar_mapa(DADOS_PASTA "musicas/exemplo.map");
        if (mapa == NULL) break;

        Placar placar;
        iniciar_placar(&placar);
        ch = 0;

        desenharCenario();
        screenSetColor(WHITE, BLACK);
        screenUpdate();

        int contador = 0;
        int proximaColuna = 0;

        // sai com enter, sem vidas ou quando a musica acaba
        while (ch != 10 && !jogo_acabou(&placar) && !(mapa_acabou(mapa) && lista == NULL))
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
                    registrar_acerto(&placar, resultado);

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

                if (contador >= ms_por_linha(mapa) / 50){
                    criar_notas_da_linha(mapa, &lista, 3);
                    contador = 0;
                }

                registrar_perdidas(&placar, notasRemoverPerdidas(&lista, LINHA_ACERTO +1));
                desenharPainel(&placar);
                atual = lista;
                while(atual != NULL) {
                    desenharNota(atual->coluna, atual->y);
                    atual = atual->prox;
                }

                screenSetColor(WHITE, BLACK);
                screenUpdate();
            }
        }

        if (ch != 10) mostrarResultado(&placar);

        notasLiberar(&lista);
        liberar_mapa(mapa);

        opcao = telaInicial();
    }

    keyboardDestroy();
    screenShowCursor();
    screenDestroy();
    timerDestroy();

    return 0;
}