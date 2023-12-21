#ifndef INTERACAO_HPP
    #define INTERACAO_HPP

    // funções de interação do usuário e funções de apoio para essa ação
    void Verificar(Fase& fase, Jogador& player, int x, int y);
    void Verificar(Fase& fase, Monstro& monster, Jogador& player, int x, int y);
    void Interagir(Fase& fase, Jogador& player);
    void Mover(Fase& fase, Jogador& player);

#endif