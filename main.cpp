#include <iostream>
#include <cstdlib>
#include <vector>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <random>
using namespace std;

// Todo:
    // // todo: Refatorar as funções para trabalhar com menos parâmestros de entrada
    // // todo: Criar o monstro
    // // todo: Criar as inteligências dos monstros
        // // * Inteligencia 01: andar aleatóriamente
        // // * Inteligencia 02: seguir o jogador 
    // todo: criar o sistema de geração de fase fazendo o colapso de onda
        // ! por que diabos eu vou fazer isso eu não sei mas bora

// Leitura imediata do input do usuário
static struct termios old, current;

// Simbolos do jogos ###########################################################
const char espaco = ' ';
const char parede = '*';
const char espinho = '#';
const char chave = '@';
const char portaFecada = 'D';
const char portaAberta = '=';
const char jogador = '&';
const char teletrans = '>';
const char botao = '0';
const char monstro = 'X';

// Estruturas ###################################################################
struct Botao;
struct Monstro;

struct Coordenada
{
    int x;
    int y;
};

struct ChavePorta
{
    Coordenada chave;
    Coordenada porta;
    bool ehFinal;
    bool foiAtivada;
};

struct Teletransporte
{
    Coordenada posicaoInicial;
    Coordenada posicaoFinal;
};

struct Jogador
{
    int vidas;
    bool portaFinalAberta;
    Coordenada portaFinalPosicao;
    char simboloPosicaoAntiga;
    Coordenada posicao;
};

struct Fase
{
    bool vitoria;
    char mapa[75][75];
    Coordenada posicaoInicialJogador;
    vector<ChavePorta> chaves;
    vector<Teletransporte> teletransportes;
    vector<Botao> botoes;
    vector<Monstro> monstros;
};

struct Monstro
{
    bool vivo;
    Coordenada posicao;
    char simboloPosicaoAntiga;
    void (*ia)(Fase&, Monstro&, Jogador&);
};

struct Botao
{
    Coordenada posicao;
    bool foiAtivado;
    void (*acao)(Fase&, Jogador&);
};


// Protótipos funções ################################################################################
// Menu Principal
void Jogar(Fase& fase, Jogador& player);
void Tutorial();

// Extras
void EscreverMapa(Fase fase, int level);
void ZerarFase(Fase& fase, Jogador& player);
void AdicionarChaveLista(Fase& fase, int cX, int cY, int pX, int pY, bool final);
void AdicionarTeletransporteLista(Fase& fase, int iX, int iY, int fX, int fY);
void AdicionarBotaoLista(Fase& fase, int x, int y, void (*funcao)(Fase&, Jogador&));
void AdicionarMonstroLista(Fase& fase, int x, int y, void (*ia)(Fase&, Monstro&, Jogador&));
void Dano(Fase& fase, Jogador& player);
void TrocarPosicao(Fase& fase, Monstro& monster, int x, int y);
double Radianos(float grau);
void Circulo(Fase& fase, int centroX, int centroY, int raio, char simboloDesenho);
void MudarTamanhoFonte(int tamanho);

// Movimentação
void Verificar(Fase& fase, Jogador& player, int x, int y);
void Verificar(Fase& fase, Jogador& monster, Jogador& player, int x, int y);
void Interagir(Fase& fase, Jogador& player);
void Mover(Fase& fase, Jogador& player);

// Inteligencias Artificiais Monstros
void IA01(Fase& fase, Monstro& monster, Jogador& player);
void IA02(Fase& fase, Monstro& monster, Jogador& player);

// Criar Fases e Ações
// Fase 1
void CriarFase1(Fase& fase, Jogador& player);
// Fase 2
void CriarFase2(Fase& fase, Jogador& player);
void AcaoF02B01(Fase& fase, Jogador& player);
void AcaoF02B02(Fase& fase, Jogador& player);
// Fase 3
void CriarFase3(Fase& fase, Jogador& player);
void AcaoF03B01(Fase& fase, Jogador& player);
void AcaoF03B02(Fase& fase, Jogador& player);
void AcaoF03B03(Fase& fase, Jogador& player);
void AcaoF03B04(Fase& fase, Jogador& player);

// Termios
void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch(void);
char getche(void);

// Sobrecarga Operadores
bool operator==(Coordenada a, Coordenada b);


// ##################################################################################################
// Main #############################################################################################
int main()
{
    system("clear || cls");

    // Declaração das variáveis;
    Fase fase;
    Jogador player;
    char escolha;

    cout << "\e[8;5;10t";

    do
    {
        system("clear || cls");
        cout << "#################################################\n\n";
        cout << "\t\tGiras Labirinto\n";
        cout << "\t\t\t1- Jogar\n";
        cout << "\t\t\t2- Tutorial\n";
        cout << "\t\t\t3- Sair\n";
        cout << "\n#################################################\n";
        escolha = getch();

        if(escolha == '1')
            Jogar(fase, player);
        else if(escolha == '2')
            Tutorial();
    }
    while(escolha != '3');
    
    cout << "O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-\n\n";
    cout << "Fechando Software!\n";
    cout << "\nO-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-\n";

    return 0;
}
// ##################################################################################################
// ##################################################################################################


// Corpo Funções ##########################################################################################
// Menu Principal
void Jogar(Fase& fase, Jogador& player)
{
    // Configurações iniciais
    int8_t levelAtual = 1;
    player.vidas = 1;

    // Função que roda a lógica de quando selecionar jogo
    while(player.vidas > 0 && levelAtual != 4)
    {
        // Selecionar a fase
        if(levelAtual == 1)
        {
            CriarFase1(fase, player);
        }
        else if(levelAtual == 2)
        {
            CriarFase2(fase, player);
        }
        else
        {
            CriarFase3(fase, player);
        }
        
        // Rodar a fase atual
        while(!fase.vitoria && player.vidas)
        {
            EscreverMapa(fase, levelAtual);
            Mover(fase, player);
            for(int i = 0; i < fase.monstros.size(); i++)
            {
                fase.monstros[i].ia(fase, fase.monstros[i], player);
            }
        }

        // Verificar se ganhou a fase
        if(fase.vitoria && levelAtual < 4)
        {
            levelAtual++;
        }
        
        if(fase.vitoria && levelAtual == 4)
        {
            system("clear || cls");
            cout << "#################################################\n\n";
            cout << "\t\t Você terminou o labirinto!\n \t\t Parabéns!\n\n";
            cout << "#################################################\n";

            char espera;
            espera = getch();
        }
        
        if(player.vidas == 0)
        {
            system("clear || cls");
            cout << "#################################################\n\n";
            cout << "\t\t Você perdeu todas as vidas!\n \t\t Fim de Jogo!\n\n";
            cout << "#################################################\n";

            char espera;
            espera = getch();
        }
    }
}

void Tutorial()
{
    cout << "O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-\n\n";
    cout << "\tO jogo é do estilo aventura/puzzle onde o objetivo é o jogador conseguir passar de três fases.\n";
    cout << "\tEm cada fase o jogador deve se movimentar para pegar uma chave para abrir a porta fechada.\n\n";

    cout << "\tO jogador possui os seguintes comando:\n";
    cout << "\t\tW: O jogador movimenta uma unidade para cima;\n";
    cout << "\t\tA: O jogador movimenta uma unidade para esquerda;\n";
    cout << "\t\tS: O jogador movimenta uma unidade para baixo;\n";
    cout << "\t\tD: O jogador movimenta uma unidade para direita;\n";
    cout << "\t\tI: O jogador interage com o objeto que ele estar em cima.\n\n";

    cout << "\tO jogo possui os seguintes elementos nas fases:\n";
    cout << "\t\t&: Simbolo que representa o jogador;\n";
    cout << "\t\t*: Simbolo que representa uma parede, o jogador ao se movimentar não pode passar pela parede;\n";
    cout << "\t\t@: Simbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave;\n";
    cout << "\t\tD: Simbolo que representa a porta fechada;\n";
    cout << "\t\t=: Simbolo que representa a porta aberta quando o jogador interagiu com a chave;\n";
    cout << "\t\tO: Simbolo que representa um botão que o usuário pode interagir, o botão fica no chão e o jogador deve ficar em cima dele para poder interagir;\n";
    cout << "\t\t#: Simbolo que representa um espinho. A fase é reiniciada quando o jogador toca no espinho, caso a fase seja reiniciada três vezes, o jogo volta para o menu principal;\n";
    cout << "\t\t>: Simbolo que representa um teletransporte. O teletransporte sempre deve vir em par, quando o jogador toca em um ele é transportado para o outro e vice-versa.\n";
    cout << "\nO-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-\n\n";

    char espera;
    espera = getch();
}

// Funções Extras ##########################################################################################
void EscreverMapa(Fase fase, int level)
{
    system("clear || cls");

    int i, j;

    // Dependendo do valor para level, a variável tamanho recebe 25, 50 ou 75
    // if(level == 1) tamanho = 25;  if(level == 2) tamanho = 50;  if(level == 3) tamanho = 75;   
    int tamanho = 25*(level == 1) + 50*(level == 2) + 75*(level == 3);

    // Loop para escrever a matriz
    for(i = 0; i < tamanho; i++)
    {
        for(j = 0; j < tamanho; j++)
        {
            cout << fase.mapa[i][j] << espaco;
        }
        cout << "\n";
    }
}

void ZerarFase(Fase& fase, Jogador& player)
{
    // Resetar matriz
    int i, j;
    for(i = 0; i < 75; i++)
        for(j = 0; j < 75; j++)
            fase.mapa[i][j] = espaco;
    
    // Resetar jogador
    player.portaFinalAberta = false;
    player.portaFinalPosicao = {0, 0};
    player.posicao = {0, 0};
    player.simboloPosicaoAntiga = espaco;
    fase.vitoria = false;
    player.vidas = 3;

    // Resetar Chaves e Portas;
    while(fase.chaves.size() > 0)
    {
        fase.chaves.pop_back();
    }

    // Resetar Teletransportes
    while(fase.teletransportes.size() > 0)
    {
        fase.teletransportes.pop_back();
    }

    // Resetar Botões
    while(fase.botoes.size() > 0)
    {
        fase.botoes.pop_back();
    }

    while(fase.monstros.size() > 0)
    {
        fase.monstros.pop_back();
    }
}

void AdicionarChaveLista(Fase& fase, int cX, int cY, int pX, int pY, bool final)
{
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

void AdicionarTeletransporteLista(Fase& fase, int iX, int iY, int fX, int fY)
{
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

void AdicionarBotaoLista(Fase& fase, int x, int y, void (*funcao)(Fase&, Jogador&))
{
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

void AdicionarMonstroLista(Fase& fase, int x, int y, void (*ia)(Fase&, Monstro&, Jogador&))
{
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

void Dano(Fase& fase, Jogador& player)
{
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

void TrocarPosicao(Fase& fase, Monstro& monster, int x, int y)
{
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

double Radianos(float grau)
{
    return grau*M_PIf/180.0;
}

void Circulo(Fase& fase, int centroX, int centroY, int raio, char simboloDesenho)
{
    for(size_t i = 1; i < 360; i++)
    {
        fase.mapa[int(sin(Radianos(i))*raio + centroY)][int(cos(Radianos(i))*raio + centroX)] = simboloDesenho;
    }
}

void MudarTamanhoFonte(int tamanho)
{
    
}

// Movimentação ########################################################################################################
void Verificar(Fase& fase, Jogador& player, int x, int y)
{
    if(fase.mapa[player.posicao.y + y][player.posicao.x + x] == espaco || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == chave  || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == portaAberta || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == teletrans || \
       fase.mapa[player.posicao.y + y][player.posicao.x + x] == botao)
    {
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
        if(player.portaFinalAberta && player.posicao == player.portaFinalPosicao)
        {
            fase.vitoria = true;
        }
        
    }
    else if (fase.mapa[player.posicao.y + y][player.posicao.x + x] == espinho)
    {
        Dano(fase, player);
    }
}

void Verificar(Fase& fase, Monstro& monster, Jogador& player, int x, int y)
{
    if(fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == espaco || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == chave  || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == portaAberta || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == teletrans || \
       fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == botao)
    {
        TrocarPosicao(fase, monster, x, y);  
    }
    else if (fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == espinho)
    {
        // Apagar o monstro e colocar o simbolo antigo no lugar
        fase.mapa[monster.posicao.y][monster.posicao.x] = monster.simboloPosicaoAntiga;
        
        // Desativa o monstro
        monster.vivo = false;

        for(size_t i = 0; i < fase.monstros.size(); i++)
        {
            // Verificar qual monstro morreu
            if(!fase.monstros[i].vivo)
            {
                //Tirar o monstro da lista
                fase.monstros.erase(fase.monstros.begin()+i);
                break;
            }
        }
    }
    else if(fase.mapa[monster.posicao.y + y][monster.posicao.x + x] == jogador)
    {
        Dano(fase, player);
        TrocarPosicao(fase, monster, x, y);
    }
}

void Interagir(Fase& fase, Jogador& player) 
{
    if(player.simboloPosicaoAntiga == chave)
    {  
        // Interagindo com uma chave, fazer a varredura para descobrir qual
        for(size_t i = 0; i < fase.chaves.size(); i++)
        {
            // Verificar qual chave não foi ativada e se possui a mesma coordenada do jogador
            if(!fase.chaves[i].foiAtivada && player.posicao == fase.chaves[i].chave)
            {
                // Colocar que a chave foi ativada para ignorar na busca
                fase.chaves[i].foiAtivada = true;

                // Apagar a chave do mapa
                player.simboloPosicaoAntiga = espaco;

                // Mudar o simbolo da porta fechada para uma porta aberta
                fase.mapa[fase.chaves[i].porta.y][fase.chaves[i].porta.x] = portaAberta;

                // Ativar a flag da porta final e salvar sua coordenada
                if(fase.chaves[i].ehFinal)
                {
                    player.portaFinalAberta = true;
                    player.portaFinalPosicao = fase.chaves[i].porta;
                }
                fase.chaves.erase(fase.chaves.begin()+i);
                break;
            }
        }
    }
    else if(player.simboloPosicaoAntiga == teletrans)
    {
        // Interagindo com um teletransporte, fazer a varredura para descobrir qual
        for(size_t i = 0; i < fase.teletransportes.size(); i++)
        {
            // Verificar qual possui a mesma coordenada do jogador
            if(player.posicao == fase.teletransportes[i].posicaoInicial)
            {
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
    else if(player.simboloPosicaoAntiga == botao)
    {
        // Interagindo com um botão, fazer a varredura para descobrir qual
        for(size_t i = 0; i < fase.botoes.size(); i++)
        {
            // Verificar se o botão ainda não foi precionado e se possui a mesma posição do jogador
            if(!fase.botoes[i].foiAtivado && player.posicao == fase.botoes[i].posicao)
            {
                // Mudar o estado para precionado
                fase.botoes[i].foiAtivado = true;
                // Chamar a função registrada na função
                fase.botoes[i].acao(fase, player);
                break;
            }
        }
    }
}

void Mover(Fase& fase, Jogador& player)
{
    char move;
    move = getch();

    if(move == 'w')
    {
        Verificar(fase, player, 0, -1);
    }
    else if(move == 'a')
    {
        Verificar(fase, player, -1, 0);
    }
    else if(move == 's')
    {
        Verificar(fase, player, 0, 1);
    }
    else if(move == 'd')
    {
        Verificar(fase, player, 1, 0);
    }
    else if(move == 'i')
    {
        Interagir(fase, player);
    }
    else if(move == 'k')
    {
        fase.vitoria = true;
    }
}


// Funções Inteligencias Artificiais Monstros ###############################################################################################
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

// Funções Criar Fases ###############################################################################################
// Fase 1
void CriarFase1(Fase& fase, Jogador& player)
{
    const unsigned int terco = 25/3;
    ZerarFase(fase, player);
    
    // Escrever Paredes
    for(size_t i = 0; i < 25; i++)
    {
        fase.mapa[i][0] = parede;
        fase.mapa[0][i] = parede;
        fase.mapa[24][i] = parede;
        fase.mapa[i][24] = parede;
    }

    for(size_t  i = 0; i < terco; i++)
    {
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

// Fase 2
void CriarFase2(Fase& fase, Jogador& player)
{
    ZerarFase(fase, player);

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

void AcaoF02B01(Fase& fase, Jogador& player)
{
    const unsigned int meio = 50/2;
    const unsigned int terco = 50/3;
    const unsigned int quarto = 50/4;

    Circulo(fase, meio, meio, quarto+1, espinho);
    fase.mapa[meio][meio+terco-1] = espaco;
}

void AcaoF02B02(Fase& fase, Jogador& player)
{
    const unsigned int meio = 50/2;
    const unsigned int quarto = 50/4;
    const unsigned int sexto = 50/6;

    Circulo(fase, meio, meio, sexto, espinho);

    fase.mapa[meio][quarto] = espaco;
    fase.mapa[meio][quarto+1] = espaco;
    fase.mapa[meio][sexto+meio-1] = espaco;
}

// Fase 3
void CriarFase3(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;

    ZerarFase(fase, player);

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

void AcaoF03B01(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto, quarto, quarto, espinho);
    Circulo(fase, quarto, quarto, oitavo, espinho);
    fase.mapa[oitavo][quarto] = fase.mapa[oitavo*3-1][quarto] = espaco;
}

void AcaoF03B02(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto*3, quarto, quarto, espinho);
    Circulo(fase, quarto*3, quarto, oitavo, espinho);
    fase.mapa[oitavo][quarto*3] = fase.mapa[oitavo*3-1][quarto*3] = espaco;
}

void AcaoF03B03(Fase& fase, Jogador& player)
{
    int quarto = 75/4;
    int oitavo = 75/8;
    Circulo(fase, quarto, quarto*3, quarto, espinho);
    Circulo(fase, quarto, quarto*3, oitavo, espinho);
    fase.mapa[oitavo*5][quarto] = fase.mapa[oitavo*7-1][quarto] = espaco;
}

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


// Funções Termios ##############################################################################################
/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        current.c_lflag |= ECHO; /* set echo mode */
    }
    else {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)   
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* 
Read 1 character without echo 
getch() function definition.
*/
char getch(void)
{
    return getch_(0);
}

/* 
Read 1 character with echo 
getche() function definition.
*/
char getche(void)
{
    return getch_(1);
}


// Sobrecarga Operadores ######################################################################################
bool operator==(Coordenada a, Coordenada b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
