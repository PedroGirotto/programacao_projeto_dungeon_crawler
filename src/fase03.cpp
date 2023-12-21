#include <vector>

#include "estrutura.hpp"
#include "sistema_operacional.hpp"
#include "funcoes_memoria.hpp"
#include "ias.hpp"
#include "fase03.hpp"


// "renderização" do mapa da segunda fase
void CriarFase3(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;

    ZerarFase(fase, player);
    fase.tamanho = 75;
    AlocarMemoriaFase(fase);

    Circulo(fase, quarto, quarto, quarto, parede);
    Circulo(fase, quarto*3, quarto, quarto, parede);
    Circulo(fase, quarto, quarto*3, quarto, parede);
    Circulo(fase, quarto*3, quarto*3, quarto, parede);

    AdicionarTeletransporteLista(fase, oitavo*3, quarto, oitavo*3, quarto*3);
    AdicionarTeletransporteLista(fase, oitavo-1, quarto, oitavo*5-1, quarto);
    AdicionarTeletransporteLista(fase, oitavo-1, quarto*3, oitavo*5-1, quarto*3);
    AdicionarTeletransporteLista(fase, oitavo*7, quarto, oitavo*7, quarto*3);

    AdicionarBotaoLista(fase, quarto, quarto, AcaoF03B01);
    AdicionarBotaoLista(fase, quarto*3, quarto, AcaoF03B02);
    AdicionarBotaoLista(fase, quarto, quarto*3, AcaoF03B03);
    AdicionarBotaoLista(fase, quarto*3, quarto*3, AcaoF03B04);

    AdicionarMonstroLista(fase, quarto-1, quarto-1, IA02);
    AdicionarMonstroLista(fase, quarto*3-1, quarto-1, IA02);
    AdicionarMonstroLista(fase, quarto-1, quarto*3-1, IA02);
    AdicionarMonstroLista(fase, quarto*3-1, quarto*3-1, IA02);

    fase.posicaoInicialJogador.x = quarto;
    fase.posicaoInicialJogador.y = oitavo;
    fase.mapa[fase.posicaoInicialJogador.y][fase.posicaoInicialJogador.x] = jogador; 

    player.posicao = fase.posicaoInicialJogador;
}


// ação ao acionar o primeiro botão da fase 3
void AcaoF03B01(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto, quarto, quarto, espinho);
    Circulo(fase, quarto, quarto, oitavo, espinho);
    fase.mapa[oitavo][quarto] = fase.mapa[oitavo*3-1][quarto] = espaco;
}


// ação ao acionar o segundo botão da fase 3
void AcaoF03B02(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto*3, quarto, quarto, espinho);
    Circulo(fase, quarto*3, quarto, oitavo, espinho);
    fase.mapa[oitavo][quarto*3] = fase.mapa[oitavo*3-1][quarto*3] = espaco;
}


// ação ao acionar o terceiro botão da fase 3
void AcaoF03B03(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto, quarto*3, quarto, espinho);
    Circulo(fase, quarto, quarto*3, oitavo, espinho);
    fase.mapa[oitavo*5][quarto] = fase.mapa[oitavo*7-1][quarto] = espaco;
}


// ação ao acionar o quarto botão da fase 3
void AcaoF03B04(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int meio = 75/2;
    int oitavo = 75/8;
    Circulo(fase, quarto*3, quarto*3, quarto, espinho);
    Circulo(fase, quarto*3, quarto*3, oitavo, espinho);
    fase.mapa[oitavo*5][quarto*3] = fase.mapa[oitavo*7-1][quarto*3] = espaco;
    fase.teletransportes.pop_back();
    fase.teletransportes.pop_back();

    AdicionarTeletransporteLista(fase, oitavo*7, quarto, meio+1, meio-1);
    AdicionarChaveLista(fase, meio-1, meio-1, quarto*3, 71, true);
}