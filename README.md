# 🎸 Guitar Hero CLI

Jogo de ritmo inspirado em Guitar Hero, feito em C e executado no terminal. Projeto da disciplina Programação Imperativa e Funcional (2026.2) da CESAR School.

## Equipe
 
| Nome | E-mail |
|------|--------|
| Ana Luiza Vieira Câmara | alvc@cesar.school |
| Arthur Morais Barbosa de Almeida | Amba3@cesar.school |
| Pedro Henrique Ramos da Silva | phrs@cesar.school |

## Sobre o jogo
 
Notas descem pela tela em 4 colunas, cada uma associada a uma tecla. O jogador precisa apertar a tecla correta no momento em que a nota chega na linha de acerto. Quanto mais precisa a jogada, mais pontos; acertos seguidos formam combos, e errar custa vidas.

### Funcionalidades

- 4 colunas de notas, controladas pelas teclas **D, F, J, K**
- Notas caindo com animação e velocidade controlada por timer
- Detecção de acerto na zona de pontuação (perfeito / bom / erro)
- Pontuação, combo e multiplicador
- Sistema de vidas e tela de fim de jogo
- Três dificuldades (fácil, médio e difícil), cada uma com seu mapa
- Ranking de melhores pontuações salvo em arquivo, com uma coluna por dificuldade
- Menu inicial e tela de como jogar

## Como jogar

| Tecla | Ação |
|-------|------|
| **D F J K** | acertam as notas das colunas 1 a 4 |
| **↑ ↓** (ou **W S**) | navegam pelos menus |
| **ENTER** | confirma uma opção ou abandona a partida |

Ao escolher **Jogar**, o jogador seleciona a dificuldade e a partida começa. Ela termina quando as vidas acabam ou quando o mapa chega ao fim. Se a pontuação for maior que zero, o jogador digita o nome e entra no ranking da dificuldade jogada. A tela de ranking mostra as três dificuldades lado a lado.

## Dificuldades

Cada dificuldade carrega um mapa próprio, em `dados/mapas/`:

| Dificuldade | Mapa | BPM | Características |
|-------------|------|-----|-----------------|
| Fácil | `facil.map` | 90 | uma nota por vez, só nas batidas |
| Médio | `medio.map` | 120 | notas fora da batida e algumas notas duplas |
| Difícil | `dificil.map` | 150 | muitas notas e notas duplas frequentes |

### Formato de um mapa

A primeira linha tem `nome arquivo_de_audio bpm linhas_por_batida total_linhas offset_ms`. Cada linha seguinte tem 4 valores (`0` ou `1`), um por coluna, indicando se há nota naquele instante.

```
medio medio.mp3 120 2 100 0
1 0 1 0
0 0 0 0
...
```

## Como compilar e executar

É preciso ter `gcc` e `make` em um terminal Linux (ou WSL).

```bash
make        # compila e gera o executável guitar-hero
make run    # compila e executa
make clean  # remove o executável
```

Os rankings são gravados em `dados/ranking_facil.txt`, `dados/ranking_medio.txt` e `dados/ranking_dificil.txt`, criados na primeira pontuação.

## Estrutura do projeto

```
src/        código do jogo (main, menu, tela, notas, mapa, pontuação, ranking, dificuldade)
include/    headers do jogo
cli-lib/    biblioteca de terminal (tela, teclado e timer)
dados/      mapas das músicas e arquivos de ranking
```

## Vídeo de demonstração

[Assista no YouTube](https://youtu.be/yo5Yr7wIshM)
