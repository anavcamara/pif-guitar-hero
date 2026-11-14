#include "screen.h"
#include "keyboard.h"
#include "tela.h"
#include "menu.h"

void mostrarComoJogar() {
    int ch = 0;

    desenharComoJogar();
    screenUpdate();

    while (ch != 10) {
        if (keyhit()) ch = readch();
    }
}

int telaInicial() {
    int selecionada = 0;
    int ch = 0;

    desenharMenu(selecionada);
    screenUpdate();

    while (1)
    {
        if (keyhit())
        {
            ch = readch();

            // seta: chegam 3 codigos seguidos (27, 91 e uma letra)
            if (ch == 27) {
                readch(); // le o 91 e ignora
                ch = readch();
                if (ch == 65) selecionada--; // seta pra cima
                if (ch == 66) selecionada++; // seta pra baixo
            }

            // alternativa com as teclas W e S
            if (ch == 'w' || ch == 'W') selecionada--;
            if (ch == 's' || ch == 'S') selecionada++;

            // da a volta no menu
            if (selecionada < 0) selecionada = 3;
            if (selecionada > 3) selecionada = 0;

            if (ch == 10) {
                if (selecionada != 2) return selecionada;

                mostrarComoJogar();
                desenharMenu(selecionada);
            } else {
                desenharOpcoes(selecionada);
            }

            screenUpdate();
        }
    }
}