#ifndef ESTRUTURA_HPP
    #define ESTRUTURA_HPP
    
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

        struct Coordenada{
            int x;
            int y;
        };

        struct ChavePorta{
            Coordenada chave;
            Coordenada porta;
            bool ehFinal;
            bool foiAtivada;
        };

        struct Teletransporte{
            Coordenada posicaoInicial;
            Coordenada posicaoFinal;
        };

        struct Jogador{
            int vidas;
            bool portaFinalAberta;
            Coordenada portaFinalPosicao;
            char simboloPosicaoAntiga;
            Coordenada posicao;
        };

        struct Fase{
            bool vitoria;
            char** mapa;
            int tamanho;
            Coordenada posicaoInicialJogador;
            std::vector<ChavePorta> chaves;
            std::vector<Teletransporte> teletransportes;
            std::vector<Botao> botoes;
            std::vector<Monstro> monstros;
        };

        struct Monstro{
            bool vivo;
            Coordenada posicao;
            char simboloPosicaoAntiga;
            void (*ia)(Fase&, Monstro&, Jogador&);
        };

        struct Botao{
            Coordenada posicao;
            bool foiAtivado;
            void (*acao)(Fase&, Jogador&);
        };
#endif