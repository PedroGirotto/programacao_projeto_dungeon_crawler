#include <cstdlib>
#include <iostream>
#include <vector>

#include "estrutura.hpp"
#include "funcoes_memoria.hpp"
#include "sistema_operacional.hpp"
#include "interacao.hpp"


void Verificar(Fase& fase, Jogador& player, int x, int y){
    if(fase.mapa[player.posicao.y + y][player.posicao.x + x] == espaco || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == chave  || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == portaAberta || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == teletrans || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == botao){
        // Apagar posição atual do jogador pelo simbolo original do lugar
        fase.mapa[player.posicao.y][player.posicao.x] = player.simboloPosicaoAntiga;

        // Atualizar a posição do jogador
        player.posicao.x += x;
        player.posicao.y += y;

        // Salvar o simbolo original da nova posição
        player.simboloPosicaoAntiga = fase.mapa[player.posicao.y][player.posicao.x];
        // Mover o jogador
        fase.mapa[player.posicao.y][player.posicao.x] = jogador;

        // Ativação de eventos específicos
        if(player.portaFinalAberta && player.posicao == player.portaFinalPosicao){
            fase.vitoria = true;
        }
        
    }
    else if (fase.mapa[player.posicao.y + y][player.posicao.x + x] == espinho){
        Dano(fase, player);
    }
}


void Verificar(Fase& fase, Monstro& monster, Jogador& player, int x, int y){
    if(fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == espaco || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == chave  || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == portaAberta || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == teletrans || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == botao)
    {
        TrocarPosicao(fase, monster, x, y);  
    }
    else if (fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == espinho){
        // Apagar o monstro e colocar o simbolo antigo no lugar
        fase.mapa[monster.posicao.y][monster.posicao.x] = monster.simboloPosicaoAntiga;
        
        // Desativa o monstro
        monster.vivo = false;

        for(int i = 0; i < fase.monstros.size(); i++){
            // Verificar qual monstro morreu
            if(!fase.monstros[i].vivo){
                //Tirar o monstro da lista
                fase.monstros.erase(fase.monstros.begin()+i);
                break;
            }
        }
    }
    else if(fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == jogador){
        Dano(fase, player);
        TrocarPosicao(fase, monster, x, y);
    }
}


void Interagir(Fase& fase, Jogador& player) {
    if(player.simboloPosicaoAntiga == chave){  
        // Interagindo com uma chave, fazer a varredura para descobrir qual
        for(int i = 0; i < fase.chaves.size(); i++){
            // Verificar qual chave não foi ativada e se possui a mesma coordenada do jogador
            if(!fase.chaves[i].foiAtivada && player.posicao == fase.chaves[i].chave){
                // Colocar que a chave foi ativada para ignorar na busca
                fase.chaves[i].foiAtivada = true;

                // Apagar a chave do mapa
                player.simboloPosicaoAntiga = espaco;

                // Mudar o simbolo da porta fechada para uma porta aberta
                fase.mapa[fase.chaves[i].porta.y][fase.chaves[i].porta.x] = portaAberta;

                // Ativar a flag da porta final e salvar sua coordenada
                if(fase.chaves[i].ehFinal){
                    player.portaFinalAberta = true;
                    player.portaFinalPosicao = fase.chaves[i].porta;
                }
                fase.chaves.erase(fase.chaves.begin()+i);
                break;
            }
        }
    }
    else if(player.simboloPosicaoAntiga == teletrans){
        // Interagindo com um teletransporte, fazer a varredura para descobrir qual
        for(int i = 0; i < fase.teletransportes.size(); i++){
            // Verificar qual possui a mesma coordenada do jogador
            if(player.posicao == fase.teletransportes[i].posicaoInicial){
                // Colocar o simbolo do teletransporte de volta no lugar
                fase.mapa[player.posicao.y][player.posicao.x] = teletrans;
                
                // Atualizar a posição do jogador para o outro lado do teletransporte
                player.posicao = fase.teletransportes[i].posicaoFinal;

                // Colocar o símbolo do jogador na nova posição
                fase.mapa[player.posicao.y][player.posicao.x] = jogador;
                break;
            }
        }
    }
    else if(player.simboloPosicaoAntiga == botao){
        // Interagindo com um botão, fazer a varredura para descobrir qual
        for(int i = 0; i < fase.botoes.size(); i++){
            // Verificar se o botão ainda não foi precionado e se possui a mesma posição do jogador
            if(!fase.botoes[i].foiAtivado && player.posicao == fase.botoes[i].posicao){
                // Mudar o estado para precionado
                fase.botoes[i].foiAtivado = true;
                // Chamar a função registrada na função
                fase.botoes[i].acao(fase, player);
                break;
            }
        }
    }
}


void Mover(Fase& fase, Jogador& player){
    char move;
    move = getch();
    
    if(move == 'w'){
        Verificar(fase, player, 0, -1);
    }
    else if(move == 'a'){
        Verificar(fase, player, -1, 0);
    }
    else if(move == 's'){
        Verificar(fase, player, 0, 1);
    }
    else if(move == 'd'){
        Verificar(fase, player, 1, 0);
    }
    else if(move == 'i'){
        Interagir(fase, player);
    }
    else if(move == 'k'){
        fase.vitoria = true;
    }
}