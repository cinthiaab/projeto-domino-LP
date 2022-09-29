typedef struct domino //criacao do tipo domino
{
    int Lado[2]; // determina os lados da pecas
    int status; //1 - jogador 1, 2 - jogador 2, 3 - mesa, 4 - compra
} domino;

typedef struct _msg {
    char txt[100];
} msg;

typedef struct _jogo{
    int qtdeJogadores; // quantidade de jogadores
    // qtdeJogadores = 1 -> 1 jogador = jogando com o computador
    // qtdeJogadores = 2 -> 2 jogadores
    int turno; // turno referente ao jogador
    // turno = 1 -> jogador 1
    // turno = 2 -> jogador 2
    int pecasCompradas; // quantidade de pecas comprada
    domino pecas[28];
    domino mesa[55];
    int lado[2];
} jogo;

#define POSICAO_INICIAL 27
FILE *fp;
jogo jogador;
