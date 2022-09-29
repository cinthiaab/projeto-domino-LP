#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //biblioteca para manipular caracteres na tela
#include <time.h> //biblioteca para gerar os numeros de acordo com o tempo
#include "model.h"
#include "assinatura.h"

void embaralharPecas()
{
    int k;

    srand(time(NULL));

    for(k=0; k<28 ; k++)
    {
        int r = rand() % 28; //comando para gerar numero entre 0 e 28 de forma aleatoria

        struct domino temp = jogador.pecas[k]; //temp e a peca que será substituida

        jogador.pecas[k] = jogador.pecas[r]; //substituição da peça K pela R
        jogador.pecas[r] = temp; //substituição da peça R pela K
    }

}

void gerarPecas()
{
    int i, j, k=0;
    for(i=0; i<7; i++)  // gera as peças
    {
        for(j=i; j<7; j++) // criação das peças na matriz
        {
            jogador.pecas[k].Lado[0] = i;
            jogador.pecas[k].Lado[1] = j;
            k++;
        }
    }
}

// Funcao que inverte o lado da peca dependendo do lado que a peca deve ser jogada
void mudaLado(int ipeca)
{
    int gira;
    gira=jogador.pecas[ipeca].Lado[0];
    jogador.pecas[ipeca].Lado[0]=jogador.pecas[ipeca].Lado[1];
    jogador.pecas[ipeca].Lado[1]=gira;
}
//fun��o que distribui as pe�as
void distribuirPecas()
{
    int i;

    for(i=0; i<14; i++) // separa as 14 primeiras pecas para entrega-las aos jogadores (7 para cada respectivamente)
    {
        if(i<7)
        {
            jogador.pecas[i].status=1; //separa as pecas para o jogador 1
        }
        else
        {
            jogador.pecas[i].status=2;   // separa as pecas para o jogador 2
        }

    }
    for(i=14; i<28; i++)   //pecas que ficaram na pilha de compra
        jogador.pecas[i].status=4; // resto das pecas que nao foram separadas para os jogadores
}
//funcao para salvar o jogo
void salvarJogo()
{
    fp = fopen("domino.txt", "wb");

    int mesaSalva = fwrite(jogador.mesa, sizeof(struct domino), 55, fp);
    int pecasSalva = fwrite(jogador.pecas, sizeof(struct domino), 28, fp);
    int turnoSalvo = fwrite(&jogador.turno, sizeof(int), 1,fp);
    int pecasCompradasSalva = fwrite(&jogador.pecasCompradas, sizeof(int), 1,fp);
    int qtdeJogadoresSalva = fwrite(&jogador.qtdeJogadores, sizeof(int), 1,fp);


    if(mesaSalva!=55 || pecasSalva!=28 || turnoSalvo!=1 || pecasCompradasSalva!=1 || qtdeJogadoresSalva!=1)
    {
        imprimirMsg(17);
    }
    else
    {
        imprimirMsg(16);
    }

    fclose(fp);

}

//funcao que recupera os arquivos, lendo os arquivos salvos
void recuperarJogo()
{
    fp = fopen("domino.txt","rb");

    int mesaSalva = fread(jogador.mesa, sizeof(struct domino), 55, fp);
    int pecasSalva = fread(jogador.pecas, sizeof(struct domino), 28, fp);
    int turnoSalvo = fread(&jogador.turno, sizeof(int), 1,fp);
    int pecasCompradasSalva = fread(&jogador.pecasCompradas, sizeof(int), 1,fp);
    int qtdeJogadoresSalva = fread(&jogador.qtdeJogadores, sizeof(int), 1,fp);


    if(mesaSalva!=55 || pecasSalva!=28 || turnoSalvo!=1 || pecasCompradasSalva!=1 || qtdeJogadoresSalva!=1)
    {
        imprimirMsg(15);
    }
    else
    {
        imprimirMsg(13);
    }

    fclose(fp);
    imprimirMsg(12);
    menuJogador();
}
