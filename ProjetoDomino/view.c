#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //biblioteca para manipular caracteres na tela
#include <time.h> //biblioteca para gerar os numeros de acordo com o tempo
#include "model.h"
#include "assinatura.h"

//fun��o que imprime o menu principal
void viewMenu()
{
    printf("\n-----=-=-=-=-=-= DOMINO =-=-=-=-=-=-----\n");
    printf("      Escolha uma das opcoes abaixo:\n");
    printf("\t[1] - Iniciar Jogo\n");
    printf("\t[2] - Recuperar Jogo\n");
    printf("\t[3] - Sair");
    printf("\n\n\tOpcao: ");
}


//funcao que imprime o menu do jogador
void viewJogador()
{
    int i, j=1;//i = indice das pecas, j = identificador das pecas

    printf("\n-----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-----\n");
    printf("\n\t    Turno do Jogador %d\n\n", jogador.turno);
    printf("Suas pecas sao: \n\t");
    for (i=0; i<28; i++)
    {
        if(jogador.pecas[i].status==jogador.turno)
        {
            printf("%d.[%d|%d] ", j, jogador.pecas[i].Lado[0], jogador.pecas[i].Lado[1]);
            j++;
        }
    }
    printf("\n\n[1] Jogar");
    printf("\n[2] Comprar");
    printf("\n[3] Passar");
    printf("\n[4] Abandonar partida");
    printf("\n\n\tOpcao: ");

}
//funcao que imprime a mesa
void imprimirMesa()
{
    int i;

    printf("\n==================MESA==================\n");
    for(i=0; i<55; i++)
    {
        if(jogador.mesa[i].Lado[0]!=7 && jogador.mesa[i].Lado[1]!=7)
            printf("[%d|%d]", jogador.mesa[i].Lado[0], jogador.mesa[i].Lado[1]);

    }
    printf("\n========================================\n");
}
void viewMenuQtdeJogadores(){
    printf("\n-----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-----\n\n");
    printf("      Escolha uma das opcoes abaixo:\n");
    printf("\t[1] - Jogar com o computador\n");
    printf("\t[2] - Jogar com dois jogadores");
    printf("\n\n\tOpcao: ");
}

//imprimir Mensagens simples na tela
void imprimirMsg(int idMsg){
    msg mensagens[] = {
            {"\tOpcao Invalida!!\n"},// idMsg = 0
            {"\n-----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-----\n\n"},// idMsg = 1
            {"\tIniciar com 1 ou 2 jogadores:"},// idMsg = 2
            {" \n "},// idMsg = 3
            {"Todas as pecas ja foram compradas!!"},// idMsg = 4
            {"\n\tJogo Encerrado!\n\n"},// idMsg = 5
            {"\nInsira o numero da peca (0 se desejar voltar) : "},// idMsg = 6
            {"\nVoce quer jogar na:\n\t[1] Esquerda\n\t[2] Direita"},// idMsg = 7
            {"\nJogada Invalida!\n"},// idMsg = 8
            {"\n\n\tOpcao: "},// idMsg = 9
            {"\t\n-----=-=-=-= FIM DO PROGRAMA =-=-=-=-----\n"},// idMsg = 10
            {"\t\n------=-=-=-= INICIO DO JOGO =-=-=-=------\n"},// idMsg = 11
            {"\t\n--=-=-=-= RECUPERACAO DO PROGRAMA =-=-=-=--\n"},// idMsg = 12
            {"\n Sucesso na recuperacao dos dados do arquivo domino.txt\n"},// idMsg = 13
            {"   JOGO TRANCADO - "},// idMsg = 14
            {"\n Erro na recuperacao dos dados do arquivo domino.txt\n"},// idMsg = 15
            {" Sucesso na gravacao dos dados do arquivo domino.txt\n"},// idMsg = 16
            {" Erro na gravacao dos dados do arquivo domino.txt\n"},// idMsg = 17

    };

    printf("%s", mensagens[idMsg].txt);
}
void viewMenuFimDaPartida(){
    printf("-----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-----\n\n");
    printf("      Escolha uma das opcoes abaixo:\n");
    printf("\t[1] - Finalizar partida sem salvar\n");
    printf("\t[2] - Salvar jogo e finalizar\n");
    printf("\t[3] - Voltar ao jogo\n");
    printf("\n\n\tOpcao: ");
}
void mostrarMsgJogador(int idMsg){
    msg msgJ1[] ={
        {"\n + O jogador 1 passou a vez +\n"},// idMsg = 0
        {"JOGADOR 1 VITORIOSO!\n"},// idMsg = 1
        {"\n + O jogador 1 comeca +\n"},// / idMsg = 2
    };
    msg msgJ2[] ={
        {"\n + O jogador 2 passou a vez +\n"},// idMsg = 0
        {"JOGADOR 2 VITORIOSO!\n"},// / idMsg = 1
        {"\n + O jogador 2 comeca +\n"}, // idMsg = 2
    };
    msg msgBot[] ={
        {"\n + O computador passou a vez +\n"},// idMsg = 0
        {"COMPUTADOR VITORIOSO!\n"},// / idMsg = 1
        {"\n + O computador comeca +\n"}, // idMsg = 2
    };
    if(jogador.turno==1)printf("%s", msgJ1[idMsg]);
    if(jogador.qtdeJogadores==2 && jogador.turno==2)printf("%s", msgJ2[idMsg]);
    if(jogador.qtdeJogadores==1 && jogador.turno==2)printf("%s", msgBot[idMsg]);

}
void mostrarMsgPeca(int idMsg, int indicePeca){
    msg msgPeca[] ={
        {"Voce comprou a peca"}, // idMsg = 0
        {"O computador comprou a peca"}, // idMsg = 1
        {"O computador jogou a peca"} // idMsg = 2
    };

    printf("\n + %s [%d|%d] +\n", msgPeca[idMsg], jogador.pecas[indicePeca].Lado[0], jogador.pecas[indicePeca].Lado[1]);
}
