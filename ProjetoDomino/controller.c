#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //biblioteca para manipular caracteres na tela
#include <time.h> //biblioteca para gerar os numeros de acordo com o tempo
#include "model.h"
#include "assinatura.h"

//fun��o que estrutura o menu principal do domino
void menuDomino()
{
    int opcao;
    // jogador.qtdeJogadores = 1 (jogar contra o computador)
    // jogador.qtdeJogadores = 2 (2 jogadores)
    do
    {
        viewMenu();// imprime na tela o Menu para iniciar o jogo e para sair
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
        {
            viewMenuQtdeJogadores();
            scanf("%d", &jogador.qtdeJogadores);
            gerarPecas();
            embaralharPecas();
            distribuirPecas();
            iniciarJogo();
        }
        break;
        case 2:
            recuperarJogo();
        break;
        case 3:
            imprimirMsg(10); // mensagem: fim do programa
        break;
        default:
            imprimirMsg(0); // mensagem: opcao invalida
        }
    }
    while(opcao!=3);
}

//fun��o que coloca a maior pe�a na mesa e inicia o jogo
void iniciarJogo()
{
    int i, j, k;

    jogador.pecasCompradas = 0;
    //p=jogador.turno; //p = o jogador que comecou
    jogador.lado[0]=0; // 0 pecas no lado esquerdo da posicao inicial
    jogador.lado[1]=0; // 0 pecas no lado direito da posicao inicial

    for(k=0; k<55; k++)
    {
        jogador.mesa[k].Lado[0]=7;
        jogador.mesa[k].Lado[1]=7;
    }
    i = maiorPeca(); // i = recebe a posicao da maior peca

    jogador.turno = jogador.pecas[i].status; // jogador.turno = qual jogador tem a maior peca (jogador que vai come�ar o jogo)

    jogador.mesa[27]=jogador.pecas[i];
    jogador.pecas[i].status=3; //maior peca na mesa
    trocarTurno();
    menuJogador();
}

void trocarTurno()
{
    if(jogador.turno==2)jogador.turno=1; //troca de turno do jogador 2
    else jogador.turno=2; //troca de turno do jogador 1
}

//funcao que estrutura o menu do jogador
void menuJogador()
{
    int opcao, w=0, y=0, z=0; //u = o contador de quantas pecas foram compradas
    int opcaoFimPartida=0;

    do
    {

        z=jogoTrancado(); // z recebe se o jogo foi trancado ou nao

        if(z==0) // z=0 -> jogo não foi trancado
        {
            w=verificaFim(); // w recebe se algum dos jogadores jogou todas as suas pecas
            if(w==1 || w==2) // se um dos jogadores não tiver mais peça, encerra o jogo
            {
                opcao=9;
            }
            else if(jogador.qtdeJogadores==1 && jogador.turno==2)
            {
                opcao=verificaRobo();// robo ja jogou, portanto troca o turno
            }
            else
            {
                imprimirMesa();
                viewJogador();// imprime pecas do jogador na tela
                scanf("%d", &opcao);
                imprimirMsg(3);// quebra de linha
            }

        }
        else   // z=1 -> jogo trancado
        {
            y=somaPJogador(); // y -> recebe qual jogador tem a menor soma de pecas
            opcao=9;
        }

        switch(opcao)
        {
        case 1: // opcao 1: jogar
        {
            if(jogador.qtdeJogadores==2 || (jogador.turno==1 && jogador.qtdeJogadores==1))
            {
                if (jogarPeca()==1)
                {
                    trocarTurno();
                }
            }
            else trocarTurno();
        }
        break;
        case 2: // opcao 2: comprar
        {
            if(jogador.pecasCompradas<14)
            {
                compraPeca();
                jogador.pecasCompradas++;
            }
            else
            {
                imprimirMsg(4); // mensagem: todas as pecas compradas
            }
        }
        break;
        case 3: // opcao 3: passar
        {
            mostrarMsgJogador(0);
            trocarTurno();
        }
        break;

        case 4:  // opcao 4: abandonar jogo e salvar jogo
        {
            viewMenuFimDaPartida();
            scanf("%d", &opcaoFimPartida);
            if(opcaoFimPartida==1){
                opcao=5;
            } else if(opcaoFimPartida==2){
               salvarJogo();
               opcao=5;
            }
        }
        break;
        case 5:{
            imprimirMsg(5);//mensagem: fim de jogo
        }
        break;
        case 9:
        {
            //imprimirMesa();
            //imprimirMsg(5);//mensagem: fim de jogo

            if(z==1)imprimirMsg(14); //mensagem: jogo trancado

            if(y!=0)y=jogador.turno;
            else w=jogador.turno;

            if(w==1 || y==1)mostrarMsgJogador(1);//mensagem: jogador 1 vencedor
            else if ((w==2 || y==2) && jogador.qtdeJogadores==2)mostrarMsgJogador(1);//mensagem: jogador 2 vencedor
            else if ((w==2 || y==2) && jogador.qtdeJogadores==1)mostrarMsgJogador(1);//mensagem: computador venceu
            // y = o jogador que tem a menor soma de pecas
            // w = o jogador que nao tem mais pecas
            opcao = 5;
        }
        break;

        }

    }
    while(opcao!=5 && opcao!=9);
}

//fun��o que determina qual ser� a primeira pe�a a ser jogada
int maiorPeca()
{
    int i, maior=0, j, maiorI; //j = jogador, maiorI = maior peca

    for (i=0; i<14; i++)// pecas do jogadores
    {
        if(jogador.pecas[i].Lado[0]==jogador.pecas[i].Lado[1]) // se os dois lados da peca forem iguais
        {
            if (jogador.pecas[i].Lado[0]>maior)
            {
                maior=jogador.pecas[i].Lado[0];
                maiorI=i;// indice da maior peca
                j=jogador.pecas[i].status; // status do jogador com a maior peca
            }
        }
    }
    jogador.turno = j;
    imprimirMsg(11);
    mostrarMsgJogador(2); // mensagem: o jogador que começa e o j
    return(maiorI); // retorna o indice da maior peca
}

//fun��o que permite o jogador a comprar as pe�as disponiveis
void compraPeca()
{
    int i; //i = indice da peca selecionada

    i = 14 + jogador.pecasCompradas;

    if(jogador.pecas[i].status==4)  //permitir apenas a compra das pecas com status 4(compra)
    {
        jogador.pecas[i].status = jogador.turno;
    }

    if(jogador.qtdeJogadores==1 && jogador.turno==2) // computador
    {
        mostrarMsgPeca(1, i); // mensagem: computador comprou uma peca

    }
    else
    {
        mostrarMsgPeca(0, i); // mensagem: voce comprou uma peca
    }
}


int jogarPeca()
{
    // p -> numero do jogador
    int i, npeca, cont=0, ipeca, ladomesa, aux, verificado=0;
    // npeca -> o numero da peca escolhida,
    // count -> o contador,
    // ipeca -> o numero da peca escolhida no vetor


    imprimirMsg(6); // mensagem: numero da peca que o jogador quer jogar
    scanf("%d", &npeca);
    if(npeca!=0)
    {
        imprimirMsg(7); // mensagem: lado que o jogador quer jogar
        imprimirMsg(9); // mensagem: opcao
        scanf("%d", &ladomesa);

        for(i=0; i<28; i++)
        {
            if(jogador.pecas[i].status==jogador.turno)
            {
                cont++;
                if(cont==npeca)ipeca=i;
            }
        }
        if(ladomesa==1) // lado escolhido pelo jogador: esquerda
        {
            verificado=verificaJogada(ipeca, ladomesa);
            if (verificado==1) // jogada valida
            {
                aux=26-jogador.lado[0]; //aux � variavel auxiliar que representa o espa�o na mesa que a pe�a sera colocada
                jogador.mesa[aux]=jogador.pecas[ipeca];
                jogador.pecas[ipeca].status=3; // peca jogada na mesa
                jogador.lado[0]++; // soma +1 peca ao lado esquerdo da mesa
            }
            else imprimirMsg(8);  // mensagem: jogada invalida

        }
        if(ladomesa==2) // lado escolhido pelo jogador: direita
        {

            verificado=verificaJogada(ipeca, ladomesa);
            if (verificado==1) // jogada valida
            {
                aux=28+jogador.lado[1]; //aux � variavel auxiliar que representa o espa�o na mesa que a pe�a sera colocada
                jogador.mesa[aux]=jogador.pecas[ipeca];
                jogador.pecas[ipeca].status=3; // peca jogada na mesa
                jogador.lado[1]++; // soma +1 peca ao lado direito da mesa
            }
            else imprimirMsg(8);  // mensagem: jogada invalida

        }
    }

    return(verificado); // verificado = 1 -> jogada valida /// verificado = 0 -> jogada invalida
}
int verificaJogada(int ipeca, int ladomesa)
{
    // lado[2] = qtde de pecas no lado esquerdo e direito da mesa,
    // ipeca = o indice da peca jogada,
    // ladomesa = o lado que o jogador quer jogar

    int aux, valido=0; //

    if(ladomesa==1) // se o lado que o jogador quer jogar e o esquerdo
    {
        aux=27-jogador.lado[0]; // adiciona peca no lado esquerdo

        if (jogador.pecas[ipeca].Lado[0]==jogador.mesa[aux].Lado[0])mudaLado(ipeca);// inverte o lado p/ jogar a peca na mesa

        if (jogador.pecas[ipeca].Lado[1]==jogador.mesa[aux].Lado[0])valido=1; // jogada valida

    }

    if(ladomesa==2) // se o lado que o jogador quer jogar e o direito
    {
        aux=27+jogador.lado[1]; // adiciona peca do lado direito

        if (jogador.pecas[ipeca].Lado[1]==jogador.mesa[aux].Lado[1])mudaLado(ipeca);// inverte o lado p/ jogar a peca na mesa

        if (jogador.pecas[ipeca].Lado[0]==jogador.mesa[aux].Lado[1])valido=1; // jogada valida
    }

    return (valido); // retorna 0 para jogada invalida e 1 para jogada valida
}

// Funcao que verifica se algum jogador ganhou a partida jogando todas as pecas da mao
int verificaFim()
{
    int i, j1=0, j2=0, w=0;
    // j1 = jogador 1
    // j2 = jogador 2
    // w = variavel auxiliar para saber quem ganhou

    for (i=0; i<28; i++)
    {
        if (jogador.pecas[i].status==1)j1++;
        if (jogador.pecas[i].status==2)j2++;
    }
    if (j1==0) //jogador 1 vence se nao possuir pecas
    {
        w=1;
    }
    if (j2==0) //jogador 2 vence se nao possuir pecas
    {
        w=2;
    }

    return (w); // retorna o jogador que ganhou ou retorna 0, caso ambos ainda tenham pecas na mao

}

// Funcao que verifica se o jogo esta trancado
int jogoTrancado()
{
    int i, aux1, aux2, trancado = 1;
    // trancado -> variavel de controle para saber se o jogo deve ser trancado ou nao

    aux1=POSICAO_INICIAL-jogador.lado[0]; // variavel auxiliar para saber onde esta a extremidade esquerda da mesa
    aux2=POSICAO_INICIAL+jogador.lado[1]; // variavel auxiliar para saber onde esta a extremidade direita da mesa

    for(i=0; i<28; i++)
    {
        if(jogador.pecas[i].status==1)
        {
            if (jogador.pecas[i].Lado[0]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[1]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[0]==jogador.mesa[aux2].Lado[1] || jogador.pecas[i].Lado[1]==jogador.mesa[aux2].Lado[1])
                trancado=0; // jogo não foi trancado
            i = 29; // sentinela para sair do for, pois o jogo nao sera trancado
        }
        if(jogador.pecas[i].status==2)
        {
            if (jogador.pecas[i].Lado[0]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[1]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[0]==jogador.mesa[aux2].Lado[1] || jogador.pecas[i].Lado[1]==jogador.mesa[aux2].Lado[1])
                trancado=0; // jogo não foi trancado
            i = 29; // sentinela para sair do for, pois o jogo nao sera trancado
        }
    }

    if (trancado==1) // trancado = 1 -> jogo trancado
    {
        for(i=0; i<28; i++)
        {
            if(jogador.pecas[i].status==4)
            {
                if (jogador.pecas[i].Lado[0]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[1]==jogador.mesa[aux1].Lado[0] || jogador.pecas[i].Lado[0]==jogador.mesa[aux2].Lado[1] || jogador.pecas[i].Lado[1]==jogador.mesa[aux2].Lado[1])
                    trancado=0; // se o jogo estiver trancado e tiver alguma peca p/comprar que possa ser jogada, o jogo não sera trancado
            }
        }
    }
    return(trancado);
}

// Funcao que verifica qual jogador tem a menor soma das pecas caso o jogo fique trancado
int somaPJogador()
{
    int i, somaj1 = 0, somaj2 = 0, vencedor, menor = 7;
    // somaj1 = soma dos lados das pecas do jogador 1,
    // somaj2 = soma dos lados das pe�as do jogador 2,
    // menor = 7 pois o maior numero que a peca podera ter e 6

    for(i=0; i<28; i++)
    {
        if(jogador.pecas[i].status==1)
        {
            somaj1 = somaj1+jogador.pecas[i].Lado[0]+jogador.pecas[i].Lado[1];

            if (jogador.pecas[i].Lado[1]<menor)
                menor=i;

            if (jogador.pecas[i].Lado[0]<menor)
                menor=i;
        }
        if(jogador.pecas[i].status==2)
        {
            somaj2 = somaj2+jogador.pecas[i].Lado[0]+jogador.pecas[i].Lado[1];

            if (jogador.pecas[i].Lado[1]<menor)
                menor=i;

            if (jogador.pecas[i].Lado[0]<menor)
                menor=i;
        }
    }
    if (somaj1<somaj2)// jogador 1 vence, pois sua soma e menor que a soma do jogador 2
    {
        vencedor=1;
    }
    else if (somaj1>somaj2)// jogador 2 vence, pois sua soma e menor que a soma do jogador 1
    {
        vencedor=2;
    }
    else if (somaj1==somaj2) // caso a soma das pecas seja igual, o jogador com a menor peca vencera
    {
        vencedor=jogador.pecas[menor].status;
    }
    return (vencedor);// VENCEDOR = jogador que tem a menor soma das pecas
}

int verificaRobo()
{
    int i, aux1, aux2, jogada=0, j, ipeca; //jogada = 0 -> o robo ainda nao jogou

    aux1=POSICAO_INICIAL-jogador.lado[0]; // variavel auxiliar para saber onde esta a extremidade esquerda da mesa
    aux2=POSICAO_INICIAL+jogador.lado[1]; // variavel auxiliar para saber onde esta a extremidade direita da mesa

    for(j=0; j<28; j++)
    {
        if(jogador.pecas[j].status==2) //pecas do computador
        {
            if((jogador.pecas[j].Lado[0]==jogador.mesa[aux2].Lado[1] || jogador.pecas[j].Lado[1]==jogador.mesa[aux2].Lado[1]) && jogador.pecas[j].status==2) //verifica se tem alguma pe�a que de para jogar no lado direito da mesa
            {
                if (jogador.pecas[j].Lado[1]==jogador.mesa[aux2].Lado[1])mudaLado(j);// inverte o lado p/ jogar a peca na mesa
                jogador.mesa[aux2+1]=jogador.pecas[j]; // joga peca na mesa (aux2+1) = a extremidade direita da mesa + 1 posi��o
                jogador.lado[1]++; // a peca sera jogada no lado direito
                jogada=1;// opcao 1 no switch -> jogar
                jogador.pecas[j].status=3; // define que a peca esta na mesa
                i=j;// i -> indice da peca que sera jogada pelo computador
                j=29; // interrompe o for (sentinela)
                mostrarMsgPeca(2, i); //mensagem: o computador jogou a peca
            }
            else if((jogador.pecas[j].Lado[1]==jogador.mesa[aux1].Lado[0] || jogador.pecas[j].Lado[1]==jogador.mesa[aux1].Lado[0]) && jogador.pecas[j].status==2)   //verifica se tem alguma pe�a que de para jogar no lado esquerdo da mesa
            {
                if (jogador.pecas[j].Lado[0]==jogador.mesa[aux1].Lado[0])mudaLado(j);// inverte o lado p/ jogar a peca na mesa
                jogador.mesa[aux1-1]=jogador.pecas[j]; // joga peca na mesa (aux1-1) = a extremidade esquerda da mesa - 1 posicao
                jogador.lado[0]++; // a peca sera jogada no lado esquerdo
                jogada=1; // opcao 1 no switch -> jogar
                jogador.pecas[j].status=3; // define que a peca esta na mesa
                i=j; // i -> indice da peca que sera jogada pelo computador
                j=29; // interrompe o for (sentinela)
                mostrarMsgPeca(2, i); //mensagem: o computador jogou a peca
            }
        }
    }


    if(jogada==0 && jogador.pecasCompradas==14) // se o computador nao jogou nenhuma peca e todas as pecas ja foram compradas, o computador passa a vez
    {
        jogada=3; // opcao 3 no switch -> passar
        mostrarMsgJogador(0); // mensagem: o computador passou
    }
    if(jogada==0 && jogador.pecasCompradas<14) // se o computador nao jogou nenhuma peca e tem disponiveis para comprar, ele compra
    {
        jogada=2; // opcao 2 no switch -> comprar
    }

    return(jogada); //retorna a opcao do switch
}
