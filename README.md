# Programacao2-Projeto01

## INTRODUÇÃO:
Um jogo de aventura é um gênero de videogame no qual o jogador assume o papel de protagonista em uma história interativa impulsionada pela exploração e/ou resolução de quebra-cabeças (Rollings & Adams 2003, p. 43). O foco do gênero na história permite que ele se baseie fortemente em outras mídias, literatura e filmes. Muitos jogos de aventura (texto e gráfico) são projetados para um único jogador, já que essa ênfase na história e no personagem dificulta o design multijogador (Hitchens 2002, p. 258). Colossal Cave Adventure é identificado ("The Colossal Cave Adventure page". rickadams.org. Retrieved 31 July 2020.) como o primeiro jogo de aventura, lançado pela primeira vez em 1976, enquanto outras séries de jogos de aventura notáveis incluem Zork, King's Quest, The Secret of Monkey Island e Myst.

## OBJETIVO:
Desenvolver a habilidade do aluno de resolução de problema, raciocínio lógico algorítmico e competência interpessoal, além de treinar todos o conhecimento adquirido na programação estruturada em C++.

## ATIVIDADE:
O projeto pode ser desenvolvido em equipe de até três alunos e gera três artefatos para serem entregues:
  * O arquivo principal do código desenvolvido em C++;
  * Um repositório no Github, contendo o arquivo do código e um arquivo README explicando o que é o projeto e o nome dos integrantes da equipe;
  * Um seminário da apresentação e defesa do código.
O projeto envolve o desenvolvimento de um jogo em C++. O jogo deve utilizar o console para o desenvolvimento gráfico e interação com o usuário. O objetivo do jogo é desafiar o jogador a passar de três fases, onde cada um deles terão seu próprio mapa.

## JOGO:
O jogo é do estilo aventura/puzzle onde o objetivo é o jogador conseguir passar de três fases. Em cada fase o jogador deve se movimentar para pegar uma chave para abrir a porta fechada.
O jogador possui os seguintes comando:
  * W: O jogador movimenta uma unidade para cima;
  * A: O jogador movimenta uma unidade para esquerda;
  * S: O jogador movimenta uma unidade para baixo;
  * D: O jogador movimenta uma unidade para direita;
  * I: O jogador interage com o objeto que ele estar em cima.
  
  * O jogo possui os seguintes elementos nas fases:
  * &: Simbolo que representa o jogador.
  * *: Simbolo que representa uma parede, o jogador ao se movimentar não pode passar pela parede.
  * @: Simbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave.
  * D: Simbolo que representa a porta fechada.
  * =: Simbolo que representa a porta aberta quando o jogador interagiu com a chave.
  * O: Simbolo que representa um botão que o usuário pode interagir, o botão fica no chão e o jogador deve ficar em cima dele para poder interagir.
  * #: Simbolo que representa um espinho. A fase é reiniciada quando o jogador toca no espinho, caso a fase seja reiniciada três vezes, o jogo volta para
  o menu principal.
  * \>: Simbolo que representa um teletransporte. O teletransporte sempre deve vir em par, quando o jogador toca em um ele é transportado para o outro e vice-versa.
  
O jogo possui um total de 8 telas:
  * Menu Principal: Menu com com três escolhas para o usuário (Jogar, Tutorial, Sair);
  * Tutorial: Texto ensinando o jogador a jogar o jogo;
  * Sair: Texto de despedida e encerramento do programa;
  * Fase 1: A Fase 1 é inicializada quando o jogador seleciona a opção Jogar no Menu Principal;
  * Fase 2: A Fase 2 é inicializada quando o jogador termina a Fase 1;
  * Fase 3: A Fase 3 é inicializada quando o jogador termina a Fase 2;
  * Vitória: Texto elogiando o jogador por ter conseguido terminar o jogo, depois dessa tela o jogador volta para o Menu Principal. Essa tela só pode ser acessada se o jogador finalizar a Fase 3;
  * Derrota: Texto caçoando o jogador, depois dessa tela o jogador volta para o Menu Principal. Essa tela só pode ser acessada quando o jogador perde em uma fase.
     
Cada fase deve possuir as seguintes características:
  * Fase 1: Essa fase possui uma dimensão de 25x25 e possui os seguintes elementos: jogador, parede, chave e porta;
  * Fase 2: Essa fase possui uma dimensão de 50x50 e possui os seguintes elementos: todos da Fase 1, botão e espinhos;
  * Fase 3: Essa fase possui uma dimensão de 75x75 e possui os seguintes elementos: todos da Fase 2 e teletransporte.

## AVALIAÇÃO
O projeto terá a seguinte distribuições de pontos:
  * Entrega do código (1,5 pontos): O código deve seguir as características descritas na seção JOGO.
  * Apresentação e defesa do código (0,7 ponto): A equipe deve apresentar o jogo funcionando, as principais ideias e dificuldades durante o desenvolvimento.
  * Repositório no GitHub (0,3 ponto): Repositório no Github contendo o código principal e um README explicando o que é o projeto e seu jogo, assim como o nome dos integrantes da equipe.
  * Acompanhamento do projeto (0,5 ponto): Terá dois dias específicos para o acompanhamento dos projeto, para esses dias os alunos devem mostrar que houve processo no desenvolvimento, será avaliado o quanto foi desenvolvido entre as semanas. Os dias do acompanhamento são 13/09 e 20/09.
