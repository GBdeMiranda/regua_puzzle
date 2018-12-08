#ifndef ESTADO_H_INCLUDED
#define ESTADO_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>    // std::random_shuffle
#include <string>
#include <string.h>
#include <math.h>
#include <sstream>
#include <list>

using namespace std;

class estado{

private:
    string blocos; //regua
    int nBlocos; //numero de blocos do reguapuzzle
    int posicaoVazia; //posicao da regua que tem espaco vazio
    bool ehSolucao; //variavel para saber se o estado ja e final
    estado *pai; //ponteiro para o pai do estado
    bool fechado; //indicando se o estado foi visitado
    int trans;//armazenar no estado qual foi a transicao que resultou nele
    int trans2;
    int custoTotal; //custo do estado raiz ate o estado this
    int valorH1; //valor para heuristica 1
    bool ehFolha; //variavel que diz se no eh folha ou nao
    int custoAvaliacao; //custo da funcao de avaliacao para o estado this
    int profundidade; //profundidade do estado na arvore de busca
    int proxFilho; //qual proximo filho deve ser expandido
                   //EX: se proxFilho = 3 significa que o ultimo filho gerado foi o 2

    bool auxEhPredecessor(estado *e, estado *f);

public:
    estado(int n); //construtor normal
    void defineblocos(char *blocos, int n);
    void imprimeblocos();

    bool transicao(int tipo);

    void copiaEstado(estado *e);

    bool verificaSolucao(); //verifica se configuracao atual de blocos e solucao

    void embaralhaBlocos();

    bool ehPredecessor(estado *f);

    void calculaCustoTotal(); //calcula custo do estado raiz ate o estado this

    void calculaHeuristica1(); //calcula função heuristica no estado this
    void calculaHeuristica2();

    void calculaFuncaoAvaliacao(); //funcao de avaliacao para o a* - f(n) = g(n) + h(n)

    ~estado(){};

    int getNBlocos(){ return this->nBlocos;}
    int getPosicaoVazia(){ return this->posicaoVazia;}
    int getSolucao(){ return this->ehSolucao;}
	string getBlocos();
	bool getFechado(){ return this->fechado;}
	estado *getPais(){ return this->pai;}
	estado *getPai(){ return this->pai;}
	int getTrans(){ return this->trans;}
	int getTrans2(){ return this->trans2;}

	int getCustoTotal(){ return this->custoTotal;}
    int getHeuristica1(){ return this->valorH1; }
    bool getEhFolha(){ return this->ehFolha;}
    int getCustoAvaliacao(){ return this->custoAvaliacao;}
    int getProfundidade(){ return this->profundidade;}
    int getProxFilho(){ return this->proxFilho;}

    void setProxFilho(int i){ this->proxFilho = i;}
	void fechaEstado(){ this->fechado = true;}
    void setPai(estado *pai){ this->pai = pai;}
    void setTrans(int i){ this->trans = i;}
    void setTrans2(int i){ this->trans2 = i;}

    void setProfundidade(int prof){ this->profundidade = prof;}
};

#endif // ESTADO_H_INCLUDED
