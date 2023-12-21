#ifndef FUNCOES_MEMORIA_HPP
    #define FUNCOES_MEMORIA_HPP
    
        // funções para alocação de memoria ou apoio para criação de fases
        void AlocarMemoriaFase(Fase& fase);
        void EscreverMapa(Fase fase, Jogador player);
        void ZerarFase(Fase& fase, Jogador& player);
        void AdicionarChaveLista(Fase& fase, int cX, int cY, int pX, int pY, bool final);
        void AdicionarTeletransporteLista(Fase& fase, int iX, int iY, int fX, int fY);
        void AdicionarBotaoLista(Fase& fase, int x, int y, void (*funcao)(Fase&, Jogador&));
        void AdicionarMonstroLista(Fase& fase, int x, int y, void (*ia)(Fase&, Monstro&, Jogador&));
        void Dano(Fase& fase, Jogador& player);
        void TrocarPosicao(Fase& fase, Monstro& monster, int x, int y);
        double Radianos(float grau);
        void Circulo(Fase& fase, int centroX, int centroY, int raio, char simboloDesenho);


        // sobrecarga do operador == para aceitar coordenadas
        bool operator==(Coordenada a, Coordenada b);
#endif