#include <random>

#include "estrutura.hpp"
#include "funcoes_memoria.hpp"
#include "interacao.hpp"


/*
    inteligência artificial do primeiro monstro:
        movimento aleatório para cima, baixo, esquerda ou direta.
        isso vai depender do valor aleatório gerado.
*/
void IA01(Fase& fase, Monstro& monster, Jogador& player)
{
    if(monster.vivo)
    {
        int move = rand()%4;

        if(move == 0)
        {
            Verificar(fase, monster, player, 0, -1);
        }
        else if(move == 1)
        {
            Verificar(fase, monster, player, -1, 0);
        }
        else if(move == 2)
        {
            Verificar(fase, monster, player, 0, 1);
        }
        else if(move == 3)
        {
            Verificar(fase, monster, player, 1, 0);
        }
    }
}


/*
    inteligência artificial do segundo monstro:
        verifica a menor distancia vertical ou horizontal em relação ao jogador
        se movimenta a direção dessa menor distancia
*/
void IA02(Fase& fase, Monstro& monster, Jogador& player)
{
    int distanciaX = monster.posicao.x - player.posicao.x;
    int distanciaY = monster.posicao.y - player.posicao.y;

    // verificar qual a menor distância para o jogador
    // se é a horizontal ou a vertical
    if(abs(distanciaX) > abs(distanciaY))
    {
        // monstro esta em uma região direita do jogador, logo subir
        if(distanciaX > 0)
        {
            Verificar(fase, monster, player, -1, 0);
        }
        // monstro esta em uma região esquerda do jogador, logo descer
        else
        {
            Verificar(fase, monster, player, 1, 0);
        }
    }
    else
    {
        // monstro esta em uma região abaixo do jogador, logo subir
        if(distanciaY > 0)
        {
            Verificar(fase, monster, player, 0, -1);
        }
        // monstro esta em uma região acima do jogador, logo descer
        else
        {
            Verificar(fase, monster, player, 0, 1);
        }
    }
}