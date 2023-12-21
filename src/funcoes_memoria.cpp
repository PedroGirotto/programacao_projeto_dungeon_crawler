#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>

#include "estrutura.hpp"
#include "sistema_operacional.hpp"
#include "funcoes_memoria.hpp"


// funções para alocação de memoria ou apoio para criação de fases
void AlocarMemoriaFase(Fase& fase){
    int i, j;
    
    //fase.mapa = (char**) malloc(fase.tamanho*sizeof(char*));
    fase.mapa = new char*[fase.tamanho];

    for(i = 0; i < fase.tamanho; i++){
        //fase.mapa[i] = (char*) malloc(fase.tamanho*sizeof(char));
        fase.mapa[i] = new char[fase.tamanho];
        for(j = 0; j < fase.tamanho; j++){
            fase.mapa[i][j] = espaco;
        }
    }
}


void EscreverMapa(Fase fase, Jogador player){
    system(LIMPAR);

    int i, j;

    // Loop para escrever a matriz
    for(i = player.posicao.y-12; i < player.posicao.y+13; i++){
        for(j = player.posicao.x-12; j < player.posicao.x+13; j++){
            if(i >= 0 && i < fase.tamanho && j >= 0 && j < fase.tamanho){
                std::cout << fase.mapa[i][j] << espaco;
            }
            else{
                std::cout << espaco;
            }
        }
        std::cout << "\n";
    }
}


void ZerarFase(Fase& fase, Jogador& player){
    // Desalocar memória da matriz
    int i, j;
    
    if(fase.mapa != nullptr){
        for(i = 0; i < fase.tamanho; i++)
            delete[] fase.mapa[i];
        delete[] fase.mapa;
    }
    fase.mapa = nullptr;

    // Resetar jogador
    player.portaFinalAberta = false;
    player.portaFinalPosicao = {0, 0};
    player.posicao = {0, 0};
    player.simboloPosicaoAntiga = espaco;
    fase.vitoria = false;
    player.vidas = 3;

    // Resetar Chaves e Portas;
    while(fase.chaves.size() > 0){
        fase.chaves.pop_back();
    }

    // Resetar Teletransportes
    while(fase.teletransportes.size() > 0){
        fase.teletransportes.pop_back();
    }

    // Resetar Botões
    while(fase.botoes.size() > 0){
        fase.botoes.pop_back();
    }

    while(fase.monstros.size() > 0){
        fase.monstros.pop_back();
    }
}


void AdicionarChaveLista(Fase& fase, int cX, int cY, int pX, int pY, bool final){
    // Adicionar uma nova chave na lista
    fase.chaves.push_back(ChavePorta());
    int tamanho = fase.chaves.size();

    // Configurar a chave adicionada de acordo com os argumentos passados
    fase.chaves[tamanho-1].ehFinal = final;
    fase.chaves[tamanho-1].foiAtivada = false;
    
    fase.chaves[tamanho-1].chave.x = cX;
    fase.chaves[tamanho-1].chave.y = cY;
    fase.mapa[cY][cX] = chave;

    fase.chaves[tamanho-1].porta.x = pX;
    fase.chaves[tamanho-1].porta.y = pY;
    fase.mapa[pY][pX] = portaFecada;
}


void AdicionarTeletransporteLista(Fase& fase, int iX, int iY, int fX, int fY){
    int tamanho;

    // Adicionando novo teletransporte na lista
    fase.teletransportes.push_back(Teletransporte());
    tamanho = fase.teletransportes.size();

    // Adicionando o teletransporte
    fase.teletransportes[tamanho-1].posicaoInicial.x = iX;
    fase.teletransportes[tamanho-1].posicaoInicial.y = iY;
    fase.teletransportes[tamanho-1].posicaoFinal.x = fX;
    fase.teletransportes[tamanho-1].posicaoFinal.y = fY;
    fase.mapa[iY][iX] = teletrans;

    // Adicionando o seu par
    fase.teletransportes.push_back(Teletransporte());
    tamanho = fase.teletransportes.size();
    fase.teletransportes[tamanho-1].posicaoInicial = fase.teletransportes[tamanho-2].posicaoFinal;
    fase.teletransportes[tamanho-1].posicaoFinal = fase.teletransportes[tamanho-2].posicaoInicial;
    fase.mapa[fY][fX] = teletrans;
}


void AdicionarBotaoLista(Fase& fase, int x, int y, void (*funcao)(Fase&, Jogador&)){
    // Adicionando novo botão na lista
    fase.botoes.push_back(Botao());
    int tamanho = fase.botoes.size();

    // Configurando botão de acordo com os argumentos passados
    fase.botoes[tamanho-1].foiAtivado = false;

    fase.botoes[tamanho-1].posicao.x = x;
    fase.botoes[tamanho-1].posicao.y = y;
    fase.mapa[y][x] = botao;

    fase.botoes[tamanho-1].acao = funcao;
}


void AdicionarMonstroLista(Fase& fase, int x, int y, void (*ia)(Fase&, Monstro&, Jogador&)){
    // Adicionando novo monstro na lista
    fase.monstros.push_back(Monstro());
    int tamanho = fase.monstros.size();

    // Configurando botão de acordo com os argumentos passados
    fase.monstros[tamanho-1].vivo = true;
    fase.monstros[tamanho-1].simboloPosicaoAntiga = espaco;

    fase.monstros[tamanho-1].posicao.x = x;
    fase.monstros[tamanho-1].posicao.y = y;
    fase.mapa[y][x] = monstro;

    fase.monstros[tamanho-1].ia = ia;
}


void Dano(Fase& fase, Jogador& player){
    // Apagar o jogador e colocar o simbolo antigo no lugar
    fase.mapa[player.posicao.y][player.posicao.x] = player.simboloPosicaoAntiga;

    // Resetar o antigo simbolo que o jogador viu
    player.simboloPosicaoAntiga = espaco;

    // Resetar a posição do jogador
    player.posicao.x = fase.posicaoInicialJogador.x;
    player.posicao.y = fase.posicaoInicialJogador.y;

    // Desenhar o jogador no mapa
    fase.mapa[player.posicao.y][player.posicao.x] = jogador;
    
    // Diminuir uma vida
    player.vidas -= 1;
}


void TrocarPosicao(Fase& fase, Monstro& monster, int x, int y){
    // Apagar posição atual do monstro pelo simbolo original do lugar
    fase.mapa[monster.posicao.y][monster.posicao.x] = monster.simboloPosicaoAntiga;

    // Atualizar a posição do monstro
    monster.posicao.x += x;
    monster.posicao.y += y;

    // Salvar o simbolo original da nova posição
    monster.simboloPosicaoAntiga = fase.mapa[monster.posicao.y][monster.posicao.x];

    // Mover o monstro
    fase.mapa[monster.posicao.y][monster.posicao.x] = monstro;      
}


double Radianos(float grau){
    return grau*std::numbers::pi/180.0;
}


void Circulo(Fase& fase, int centroX, int centroY, int raio, char simboloDesenho){
    for(int i = 1; i < 360; i++){
        fase.mapa[int(sin(Radianos(i))*raio + centroY)][int(cos(Radianos(i))*raio + centroX)] = simboloDesenho;
    }
}


// sobrecarga do operador == para aceitar coordenadas
bool operator==(Coordenada a, Coordenada b){
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}