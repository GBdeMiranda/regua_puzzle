#include <stdio.h>
#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h>

#include "reguaPuzzle.h"

using namespace std;

int main()
{

    int nPecas;
    estado *e;
    algoritmo *alg = new algoritmo();

    printf("Bem vindo ao jogo da Regua Puzzle!\n");
    printf("Digite um valor n que será o número de peças brancas e peças pretas:\n");
    cin >> nPecas;

    e = new estado(nPecas);
    int configuracao;
    printf("Digite 0 caso queira uma configuracao aleatória ou 1 caso queira inserir uma configuracao:\n");

    cin>> configuracao;
    while(configuracao!=0 && configuracao !=1)
    {
        printf("Digite um valor valido entre os ditos acima (0 ou 1):\n");
        cin>>configuracao;
    }

    if(configuracao == 0)
    {
        e->embaralhaBlocos();
    }
    else
    {
        string entradaInicial;

        printf("Para a configuração inicial voce deve inserir os valores todos seguidos um do outro \n e respeitando o numero de peças brancas e pretas que voce digitou\n");
        printf("0 para pecas brancas, 1 para pecas pretas, e '-' para espaco vazio");
        printf("Digite a configuracao inicial:\n");

        cin >> entradaInicial;
        char *blocos = new char[2*nPecas+1];

        for(int i=0; i<2*nPecas+1; i++)
        {
            blocos[i] = entradaInicial[i];
        }
        e->defineblocos(blocos, 2*nPecas+1);
    }

    printf("Dado a seguinte configuracao inicial escolhida:\n");
    e->imprimeblocos();

    int busca;
    double tempoInicio;
    double tempoFim;
    int impressaoResultado;

    printf("Escolha uma das busca abaixo para executar sobre a configuracao inicial:\n");
    printf("1 - BackTracking\n");
    printf("2 - Profundidade\n");
    printf("3 - Largura\n");
    printf("4 - Ordenada\n");
    printf("5 - Guloso\n");
    printf("6 - A*\n");
    printf("7 - IDA*\n");

    cin >> busca;
    printf("Deseja ver o caminho completo encontrado no final da busca?\n");
    printf("Digite 0 para nao e 1 para sim:\n");
    cin >> impressaoResultado;
    if(busca == 1)
    {
        tempoInicio = clock();
        alg->backtraking(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else if(busca == 2)
    {
        tempoInicio = clock();
        alg->profundidade(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else if(busca == 3)
    {
        tempoInicio = clock();
        alg->largura(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else if(busca == 4)
    {
        tempoInicio = clock();
        alg->ordenada(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else if(busca == 5)
    {
        tempoInicio = clock();
        alg->guloso(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else if(busca == 6)
    {
        tempoInicio = clock();
        alg->aEstrela(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }
    else
    {
        tempoInicio = clock();
        alg->idaEstrela(e,impressaoResultado);
        tempoFim = clock();
        cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
    }


    while(busca != 0)
    {
        printf("\n\nEscolha uma das busca abaixo para executar sobre a configuracao inicial:\n");
        printf("1 - BackTracking\n");
        printf("2 - Profundidade\n");
        printf("3 - Largura\n");
        printf("4 - Ordenada\n");
        printf("5 - Guloso\n");
        printf("6 - A*\n");
        printf("7 - IDA*\n");
        printf("0- para Sair\n");
        cin >> busca;
        if(busca==0){break;}
        printf("\nDeseja ver o caminho completo encontrado no final da busca?\n");
        printf("Digite 0 para nao e 1 para sim:\n");
        cin >> impressaoResultado;
        if(busca == 1)
        {
            tempoInicio = clock();
            alg->backtraking(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 2)
        {
            tempoInicio = clock();
            alg->profundidade(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 3)
        {
            tempoInicio = clock();
            alg->largura(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 4)
        {
            tempoInicio = clock();
            alg->ordenada(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 5)
        {
            tempoInicio = clock();
            alg->guloso(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 6)
        {
            tempoInicio = clock();
            alg->aEstrela(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
        else if(busca == 7)
        {
            tempoInicio = clock();
            alg->idaEstrela(e,impressaoResultado);
            tempoFim = clock();
            cout << "\nTempo de execucao em ms : " << 1000*(tempoFim - tempoInicio)/CLOCKS_PER_SEC;
        }
    }
    return 0;
}
