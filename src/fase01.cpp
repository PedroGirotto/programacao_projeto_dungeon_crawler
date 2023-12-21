#include <vector>

#include "estrutura.hpp"
#include "sistema_operacional.hpp"
#include "funcoes_memoria.hpp"
#include "ias.hpp"
#include "fase01.hpp"


// "renderização" do mapa da segunda fase
void CriarFase1(Fase& fase, Jogador& player){
    const unsigned int terco = 25/3;
    fase.tamanho = 25;
    ZerarFase(fase, player);
    AlocarMemoriaFase(fase);

    // Escrever Paredes
    for(int i = 0; i < 25; i++){
        fase.mapa[i][0] = parede;
        fase.mapa[0][i] = parede;
        fase.mapa[24][i] = parede;
        fase.mapa[i][24] = parede;
    }

    for(int  i = 0; i < terco; i++){
        // Sala Esquerda Superior
        fase.mapa[i][terco] = parede;
        fase.mapa[terco][i] = parede;

        // Sala Direita Superior
        fase.mapa[24-terco][i] = parede;
        fase.mapa[24-i][terco] = parede;

        // Sala Esquerda Inferior
        fase.mapa[i][24-terco] = parede;
        fase.mapa[terco][24-i] = parede;

        // Sala Direita Inferior
        fase.mapa[24-i][24-terco] = parede;
        fase.mapa[24-terco][24-i] = parede;
    }

    // Escrever Buracos
    fase.mapa[24-terco/2][24-terco] = espaco;

    // Escrever Chaves e portas
    AdicionarChaveLista(fase, 24-terco/2, 24-terco/2, terco, terco/2, false);
    AdicionarChaveLista(fase, terco/2, terco/2, terco/2, 24-terco, false);
    AdicionarChaveLista(fase, terco/2, 24-terco/2, 24-terco, terco/2, false);
    AdicionarChaveLista(fase, 24-terco/2, terco/2, 25/2, 24, true);

    // Escrever Monstros
    AdicionarMonstroLista(fase, terco/2-1, terco/2-1, IA01);
    AdicionarMonstroLista(fase, terco/2-1, 24-terco/2-1, IA01);

    // Escrever Jogador
    fase.posicaoInicialJogador.x = 25/2;
    fase.posicaoInicialJogador.y = 25/2;
    fase.mapa[fase.posicaoInicialJogador.y][fase.posicaoInicialJogador.x] = jogador; 
    player.posicao = fase.posicaoInicialJogador;
}