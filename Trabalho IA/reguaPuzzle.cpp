#include "reguaPuzzle.h"
#include <ctime>
#include <time.h>


bool ordenaCustoTotal(estado *e1, estado *e2)
{
    return e1->getCustoTotal() < e2->getCustoTotal();
}

bool ordenaHeuristica(estado *e1, estado *e2)
{
    return e1->getHeuristica1() > e2->getHeuristica1();
}

bool ordenaCustoAvalicao(estado *e1, estado *e2)
{
    return e1->getCustoAvaliacao() < e2->getCustoAvaliacao();
}

bool encontrouSolucao = 0;

void algoritmo::backtraking(estado *e, int impressaoResultado)
{
    int numFechados = 0;
    int numFolhas = 0;
    int numExpandidos = 0;
    cout << "\nEXECUTANDO BUSCA BACKTRACKING..." << endl;
    float inicio;
    float fim;
    inicio = clock();
    auxBackTracking(e,&numFechados,&numFolhas,&numExpandidos, impressaoResultado);
    fim = clock();

    cout << "\nNumero de estados expandidos no backtracking:" << numExpandidos << endl;
    cout << "\nNumero de estados visitados no backtracking:" << numFechados << endl;
    cout << "\nFator de ramificacao no backtracking:" << (numExpandidos)/(float)(numExpandidos-numFolhas+1) << endl;
}

void algoritmo::auxBackTracking(estado *e, int *numFechados, int *numFolhas, int * numExpandidos, int impressaoResultado)
{
    if(e->getFechado() == false)
    {
        e->fechaEstado();
        *numFechados = *numFechados + 1;
    }
    if(e->verificaSolucao() == true)
    {
        *numFolhas = *numFolhas + 1;
        this->imprimeCaminho(e, impressaoResultado);
        return;
    }
    else
    {
        int i;
        estado *filho;
        filho = new estado( (e->getNBlocos()-1)/2 );

        for(i=e->getTrans2()+1; i<=4; i++)
        {
            filho->copiaEstado(e);
            filho->setPai(e);
            filho->setTrans2(0);
            filho->setTrans(i);


            int a = filho->transicao(i);
            int b = !e->ehPredecessor(filho);

            if (a && b)
            {
                //cout << "Aplicando operador " << i << endl;
                *numExpandidos = *numExpandidos + 1;
                e->setTrans2(i);
                break;
            }
        }

        if(i == 5)
        {
            if(e->getTrans2() == 0)
                *numFolhas = *numFolhas + 1;
            delete filho;
            auxBackTracking(e->getPai(),numFechados,numFolhas,numExpandidos, impressaoResultado);
        }
        else
            auxBackTracking(filho,numFechados,numFolhas,numExpandidos, impressaoResultado);
    }
}

void algoritmo::imprimeCaminho(estado *e, int impressaoResultado)
{
    int custo = 0, prof = -1;
    cout << "\nEstado Solucao alcancado:\n" << endl;
    e->imprimeblocos();
    cout << "\n\nCAMINHO SOLUCAO:\n\n";
    auxImprimeCaminho(e, custo, prof,impressaoResultado);
    printf("\n\ncusto da solucao: %d", custo);
    printf("\nprofundidade da solucao: %d\n", prof);
}

void algoritmo::auxImprimeCaminho(estado *e, int &custo, int &prof, int impressaoResultado)
{
    if(e!=NULL)
    {
        if(impressaoResultado == 0)
        {
            auxImprimeCaminho(e->getPai(), custo, prof,impressaoResultado);
            if(e->getTrans()!=0)
            {
                printf("t%d, ",e->getTrans());
            }
            if(e->getTrans()==1 || e->getTrans()==2)
                custo++;
            if(e->getTrans()==3 || e->getTrans()==4)
                custo +=2;

            prof++;
        }
        else
        {
            auxImprimeCaminho(e->getPai(), custo, prof,impressaoResultado);
            if(e->getTrans()!=0)
            {
                printf("t%d, ",e->getTrans());
                printf("\n ||\n|t%d|\n ||\n\n", e->getTrans());
            }
            if(e->getTrans()==1 || e->getTrans()==2)
                custo++;
            if(e->getTrans()==3 || e->getTrans()==4)
                custo +=2;

            prof++;
            e->imprimeblocos();
        }
    }
}


void algoritmo::largura(estado *e, int impressaoResultado)
{
    cout << "\nBUSCA EM LARGURA INICIADA\n\n"<<endl;
    this->fila.push(e);
    int numFechados = 0;

    int numFilhos = 0;

    estado *filho;
    while(this->fila.empty()==false)
    {

        e = this->fila.front();
        if(e->verificaSolucao()==false)
        {
            e->fechaEstado();
            numFechados++;

            numFilhos = 0;
            for(int i=1; i<=4; i++)
            {
                filho = new estado( (e->getNBlocos()-1)/2 );
                filho->copiaEstado(e);

                //se a transicao puder ser feita e filho gerado nao repetir
                if (filho->transicao(i) && !e->ehPredecessor(filho))
                {
                    filho->setPai(e);
                    filho->setTrans(i);
                    filho->setProfundidade(e->getProfundidade() + 1);

                    this->fila.push(filho);
                    this->numExpandidos++;
                    numFilhos++;
                }
            }
            if(numFilhos==0)
                this->numNosFolha++;
            this->fila.pop();
        }
        else
        {
            e->fechaEstado();
//                this->listaFechados.push_back(e);
            numFechados++;
            this->numNosFolha = this->numNosFolha + (int) this->fila.size();
            break;
        }
    }
    cout << "\nNumero de estados visitados no largura:" << numFechados << endl;
    cout << "\nNumero de estados folhas no largura:" << this->numNosFolha << endl;
    cout << "\nNumero de estados expandidos no largura:" << this->numExpandidos << endl;
    cout << "\nFator de ramificacao no largura:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
    this->imprimeCaminho(e, impressaoResultado);
    printf("\nBUSCA LARGURA FINILIZADA!\n");
}

void algoritmo::profundidade(estado *e, int impressaoResultado)
{

    cout << "\nBUSCA EM PROFUNDIDADE INICIADA\n\n" << endl;
    this->pilha.push(e);
    int numFechados = 0;
    int stop = 0;
    list<estado*> caminho;

    int numFilhos = 0;

    estado *filho;
    while(stop == 0)
    {

        e = this->pilha.top();
        if(e->verificaSolucao()==false)
        {
            if(e->getFechado() == false)
            {
                e->fechaEstado();
                numFechados = numFechados + 1;
                caminho.push_back(e);
            }

            this->pilha.pop();

            numFilhos = 0;
            for(int i=4; i>=1; i--)
            {
                filho = new estado( (e->getNBlocos()-1)/2 );
                filho->copiaEstado(e);

                //se a transicao puder ser feita e filho gerado nao repetir
                if (filho->transicao(i) && !e->ehPredecessor(filho))
                {
                    filho->setPai(e);
                    filho->setTrans(i);

                    this->pilha.push(filho);
                    this->numExpandidos++;
                    numFilhos++;
                }
                else
                {
                    delete filho;
                }
            }
            if(numFilhos==0)
                this->numNosFolha++;
        }
        else
        {
            e->fechaEstado();
            numFechados++;
            caminho.push_back(e);
            stop = 1;
            this->numNosFolha = this->numNosFolha + (int) this->pilha.size();
        }
    }
    cout << "\nNumero de estados visitados no profundidade:" << (numFechados +1)<< endl;
    cout << "\nNumero de estados folhas no profundidade:" << this->numNosFolha << endl;
    cout << "\nNumero de estados expandidos no profundidade:" << this->numExpandidos << endl;
    cout << "\nFator de ramificacao no profundidade:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
    this->imprimeCaminho(e, impressaoResultado);
    printf("\nBUSCA PROFUNDIDADE FINILIZADA!\n");
}

void algoritmo::ordenada(estado *e, int impressaoResultado)
{
    cout << "\nBUSCA ORDENADA INICIADA\n\n" << endl;

    this->listaOrdenada.push_back(e);

    int numFechados = 0;
    int numFilhos = 0;

    estado *filho;

    while(this->listaOrdenada.empty()==false)
    {

        e = this->listaOrdenada.at(0);
        if(e->verificaSolucao()==false)
        {
            e->fechaEstado();
            numFechados++;

            numFilhos = 0;
            for(int i=1; i<=4; i++)
            {
                filho = new estado( (e->getNBlocos()-1)/2 );
                filho->copiaEstado(e);

                //se a transicao puder ser feita e filho gerado nao repetir
                if (filho->transicao(i) && !e->ehPredecessor(filho))
                {
                    filho->setPai(e);
                    filho->setTrans(i);
                    filho->setProfundidade(e->getProfundidade() + 1);
                    filho->calculaCustoTotal();

                    this->listaOrdenada.push_back(filho);
                    this->numExpandidos++;
                    numFilhos++;
                }
            }
            if(numFilhos==0)
                this->numNosFolha++;
            this->listaOrdenada.erase(listaOrdenada.begin());
            stable_sort(this->listaOrdenada.begin(), this->listaOrdenada.end(), ordenaCustoTotal);
        }
        else
        {
            e->fechaEstado();
            numFechados++;
            this->numNosFolha = this->numNosFolha + (int) this->listaOrdenada.size();
            break;
        }
    }

    cout << "\nNumero de estados visitados no ordenada:" << numFechados << endl;
    cout << "\nNumero de estados folhas no ordenada:" << this->numNosFolha << endl;
    cout << "\nNumero de estados expandidos no ordenada:" << this->numExpandidos << endl;
    cout << "\nFator de ramificacao no ordenada:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
    this->imprimeCaminho(e, impressaoResultado);
    printf("\nBUSCA ORDENADA FINILIZADA!\n");

}

void algoritmo::guloso(estado *e, int impressaoResultado)
{
    cout << "\nBUSCA GULOSA INICIADA\n\n" << endl;

    this->pilhaGuloso.push(e);

    int numFechados = 0;
    int numFilhos = 0;

    estado *filho;

    while(this->pilhaGuloso.empty()==false)
    {

        e = this->pilhaGuloso.top();
        if(e->verificaSolucao()==false)
        {
            e->fechaEstado();
            this->pilhaGuloso.pop();
            numFechados++;

            numFilhos = 0;
            for(int i=4; i>=1; i--)
            {
                filho = new estado( (e->getNBlocos()-1)/2 );
                filho->copiaEstado(e);

                //se a transicao puder ser feita e filho gerado nao repetir
                if (filho->transicao(i) && !e->ehPredecessor(filho))
                {
                    filho->setPai(e);
                    filho->setTrans(i);
                    filho->setProfundidade(e->getProfundidade() + 1);

                    filho->calculaHeuristica1();
                    this->numExpandidos++;
                    numFilhos++;

                    this->listaGulosaAux.push_back(filho);
                }
            }
            if(numFilhos==0)
                this->numNosFolha++;
            stable_sort(this->listaGulosaAux.begin(), this->listaGulosaAux.end(), ordenaHeuristica);
            for(unsigned int i = 0; i < listaGulosaAux.size() ; i++)
            {
                this->pilhaGuloso.push(listaGulosaAux.at(i));
            }
            this->listaGulosaAux.clear();
        }
        else
        {
            e->fechaEstado();
            numFechados++;
            this->numNosFolha = this->numNosFolha + (int) this->pilhaGuloso.size();
            break;
        }
    }


    cout << "\nNumero de estados visitados no guloso:" << numFechados << endl;
    cout << "\nNumero de estados folhas no guloso:" << this->numNosFolha << endl;
    cout << "\nNumero de estados expandidos no guloso:" << this->numExpandidos << endl;
    cout << "\nFator de ramificacao no guloso:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
    this->imprimeCaminho(e, impressaoResultado);
    printf("\nBUSCA GULOSO FINILIZADA!\n");

}

void algoritmo::aEstrela(estado *e, int impressaoResultado)
{
    cout << "\nBUSCA A* INICIADA\n\n" << endl;

    this->listaOrdenada.push_back(e);
    e->calculaCustoTotal();

    int numFechados = 0;
    int numFilhos = 0;

    estado *filho;

    while(this->listaOrdenada.empty()==false)
    {

        e = this->listaOrdenada.at(0);
        if(e->verificaSolucao()==false)
        {
            e->fechaEstado();
            numFechados++;

            numFilhos = 0;
            for(int i=1; i<=4; i++)
            {
                filho = new estado( (e->getNBlocos()-1)/2 );
                filho->copiaEstado(e);

                //se a transicao puder ser feita e filho gerado nao repetir
                if (filho->transicao(i) && !e->ehPredecessor(filho))
                {
                    filho->setPai(e);
                    filho->setTrans(i);
                    filho->setProfundidade(e->getProfundidade() + 1);

                    filho->calculaFuncaoAvaliacao();

                    this->listaOrdenada.push_back(filho);
                    this->numExpandidos++;
                    numFilhos++;
                }
            }
            if(numFilhos==0)
                this->numNosFolha++;

            this->listaOrdenada.erase(listaOrdenada.begin());

            stable_sort(this->listaOrdenada.begin(), this->listaOrdenada.end(), ordenaCustoAvalicao);
        }
        else
        {
            e->fechaEstado();
            numFechados++;
            this->numNosFolha = this->numNosFolha + (int) this->listaOrdenada.size();
            break;
        }
    }

    printf("\nBUSCA A* FINILIZADA!\n");
    cout << "\nNumero de estados visitados no a*:" << numFechados << endl;
    cout << "\nNumero de estados folhas no a*:" << this->numNosFolha << endl;
    cout << "\nNumero de estados expandidos no a*:" << this->numExpandidos << endl;
    cout << "\nFator de ramificacao no a*:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
    this->imprimeCaminho(e, impressaoResultado);
}



void algoritmo::idaEstrela(estado *raiz,int impressaoResultado){
    cout << "\nBUSCA IDA* INICIADA\n\n" << endl;

    this->numExpandidos = 0;
    int numFechados = 0;
    this->numNosFolha = 0;

    this->listaOrdenada.push_back(raiz);

    vector<estado*> estadosF;
    estado *e;
    e = new estado( (e->getNBlocos()-1)/2 );
    e->copiaEstado(raiz);
    estado *filho;

    int patamar;
    int patamar_old = -1;

    e->calculaFuncaoAvaliacao();
    patamar = e->getCustoAvaliacao();

    bool sucesso  = false;
    bool fracasso = false;
    e->calculaFuncaoAvaliacao();

    while (! (fracasso || sucesso)){
        numFechados++;
        if(patamar_old == patamar){
            fracasso = true;

        }else{
            if(e->verificaSolucao() && e->getCustoAvaliacao() <= patamar){
                sucesso = true;
                this->numExpandidos = numFechados;
                printf("\nBUSCA IDA* FINILIZADA!\n");
                cout << "\nNumero de estados visitados no ida*:" << numFechados << endl;
                cout << "\nNumero de estados expandidos no ida*:" << this->numExpandidos << endl;
                cout << "\nFator de ramificacao da arvore de busca no ida*:" << (this->numExpandidos)/(float)(this->numExpandidos-this->numNosFolha+1) << endl;
                this->imprimeCaminho(e, impressaoResultado);
            }else{
                if (e->getCustoAvaliacao() > patamar)
                {
                    estadosF.push_back(e);
                    e = e->getPai();
                }
                if(e->getProxFilho() <= 4){


                    filho = new estado( (e->getNBlocos()-1)/2 );
                    filho->copiaEstado(e);

                    int aux = e->getProxFilho();

                    //!(filho->transicao(aux++) && !e->ehPredecessor(filho))

                    while(aux < 5 && (!filho->transicao(aux) || e->ehPredecessor(filho))){
                        aux++;
                        filho->copiaEstado(e);
                    }

                    e->setProxFilho(aux+1);

                    if(aux < 5){
                        filho->setPai(e);
                        filho->setTrans(aux);
                        filho->setProfundidade(e->getProfundidade() + 1);

                        filho->calculaFuncaoAvaliacao();

                        this->listaOrdenada.push_back(filho);


                        e = filho; //proximo filho n visitado do e
                    }

                }else{
                    e->setProxFilho(1);
                    if(e->getBlocos() == raiz->getBlocos()){
                        //atualiza patamar
                        patamar_old = patamar;

                        stable_sort(estadosF.begin(), estadosF.end(), ordenaCustoAvalicao);
                        if(estadosF.size()>0){
                            patamar     = estadosF.at(0)->getCustoAvaliacao();
                        }
                        estadosF.clear();
                        this->listaOrdenada.clear();
                        numFechados = 0;

                        e->setProxFilho(1);
                    }else{
                        e = e->getPai();
                    }
                }
            }
        }
    }
}
