#ifndef REGUAPUZZLE_H_INCLUDED
#define REGUAPUZZLE_H_INCLUDED

#include "estado.h"

using namespace std;

class algoritmo{
private:
    vector<estado*> listaFechados;
    queue<estado*> fila;
    stack<estado*> pilha;
    vector<estado*> listaOrdenada;
    vector<estado*> listaGulosaAux;
    stack<estado*> pilhaGuloso;

    int numExpandidos; //numero de nos expandidos
    int numNosFolha; //numero de nos folha

    void auxBackTracking(estado *e, int *numFechados, int *numFolhas, int * numExpandidos, int impressaoResultado);
    void auxImprimeCaminho(estado *e, int &custo, int &prof, int impressaoResultado);

public:

    algoritmo(){this->numExpandidos = 0; this->numNosFolha = 0;}

    void backtraking(estado *e, int impressaoResultado);

    void largura(estado *e, int impressaoResultado);

    void profundidade(estado *e, int impressaoResultado);

    void ordenada(estado *e, int impressaoResultado);

    void guloso(estado *e, int impressaoResultado);

    void aEstrela(estado *e, int impressaoResultado);

    //void idaEstrela(estado *e, bool poda);

    void idaEstrela(estado *raiz,int impressaoResultado);

    void imprimeCaminho(estado *e, int impressaoResultado);

    void custoProfundidadeSolucao(estado *e);

    vector<estado*> getlistaFechados(){return this->listaFechados;}

    ~algoritmo(){}

    int getNumExpandidos(){ return this->numExpandidos;}
};

#endif // REGUAPUZZLE_H_INCLUDED
