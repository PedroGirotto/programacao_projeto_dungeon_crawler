#include <vector>

#include "estrutura.hpp"
#include "sistema_operacional.hpp"
#include "funcoes_memoria.hpp"
#include "ias.hpp"
#include "fase02.hpp"

// "renderização" do mapa da segunda fase
void CriarFase2(Fase& fase, Jogador& player){
    ZerarFase(fase, player);
    fase.tamanho = 50;
    AlocarMemoriaFase(fase);

    const unsigned int meio = 50/2;
    const unsigned int terco = 50/3;
    const unsigned int quarto = 50/4;

    Circulo(fase, meio, meio, meio, parede);
    Circulo(fase, meio, meio, terco, parede);
    Circulo(fase, meio, meio, quarto, parede);

    // Chaves
    AdicionarChaveLista(fase, meio, meio, 49, meio, true);

    // Botões
    AdicionarBotaoLista(fase, 50-5, meio, AcaoF02B01);
    AdicionarBotaoLista(fase,  meio-terco+1, meio, AcaoF02B02);

    // Monstros
    AdicionarMonstroLista(fase, meio-terco-2, meio, IA01);

    // Escrever Jogador
    fase.posicaoInicialJogador.x = 48;
    fase.posicaoInicialJogador.y = meio;
    fase.mapa[fase.posicaoInicialJogador.y][fase.posicaoInicialJogador.x] = jogador; 

    player.posicao = fase.posicaoInicialJogador;
}


// ação ao acionar o primeiro botão da fase 2
void AcaoF02B01(Fase& fase, Jogador& player){
    const unsigned int meio = 50/2;
    const unsigned int terco = 50/3;
    const unsigned int quarto = 50/4;

    Circulo(fase, meio, meio, quarto+1, espinho);
    fase.mapa[meio][meio+terco-1] = espaco;
}


// ação ao acionar o segundo botão da fase 2
void AcaoF02B02(Fase& fase, Jogador& player){
    const unsigned int meio = 50/2;
    const unsigned int quarto = 50/4;
    const unsigned int sexto = 50/6;

    Circulo(fase, meio, meio, sexto, espinho);

    fase.mapa[meio][quarto] = espaco;
    fase.mapa[meio][quarto+1] = espaco;
    fase.mapa[meio][sexto+meio-1] = espaco;
}