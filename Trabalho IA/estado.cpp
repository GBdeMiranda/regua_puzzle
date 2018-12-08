#include "estado.h"

using namespace std;

estado::estado(int n)
{
    this->nBlocos = 2*n + 1;
    this->blocos = new char[2*n + 1];
    this->ehSolucao = false;
    this->pai = NULL;
    this->fechado = false;
    this->trans = 0;
    this->trans2 = 0;
    this->custoTotal = 0;
    this->ehFolha = true;
    this->profundidade = 0;
    this->proxFilho = 1;
}

void estado::copiaEstado(estado *e)
{
    this->nBlocos = e->getNBlocos();
    this->posicaoVazia = e->getPosicaoVazia();
    this->ehSolucao = e->getSolucao();
    this->pai = e->pai;
    this->fechado = false;
    this->trans = e->trans;

    for(int i=0; i<this->nBlocos; i++)
    {
        this->blocos[i] = e->getBlocos()[i];
    }
}

void estado::defineblocos(char *blocos, int tam)
{
    if(tam == this->nBlocos)
    {
        for(int i=0; i<tam; i++)
        {
            this->blocos[i] = blocos[i];
            if(blocos[i]=='-')
                this->posicaoVazia = i;
        }
    }
    else
    {
        printf("numero de blocos maior que blocos!\n");
    }
}

void estado::imprimeblocos()
{
    printf("\n<<|");
    for(int i=0; i<this->nBlocos; i++)
        printf(" %c |", this->blocos[i]);
    printf(">>");
}

//faz todas as 4 possiveis transicoes
bool estado::transicao(int tipo)
{

    //mover peca para esquerda
    if(tipo==1)
    {
        if(this->posicaoVazia==this->nBlocos-1)
        {
            return 0;
        }
        else
        {
            this->blocos[posicaoVazia] = this->blocos[posicaoVazia+1];
            this->blocos[posicaoVazia+1] = '-';
            this->posicaoVazia++;
            return 1;
        }
    }

    //mover peca para direita
    if(tipo==2)
    {
        if(this->posicaoVazia==0)
        {
            return 0;
        }
        else
        {
            this->blocos[posicaoVazia] = this->blocos[posicaoVazia-1];
            this->blocos[posicaoVazia-1] = '-';
            this->posicaoVazia--;
            return 1;
        }
    }

    //saltar peca para esquerda
    if(tipo==3)
    {
        if(this->posicaoVazia>=nBlocos-2 || blocos[this->posicaoVazia+1] == blocos[this->posicaoVazia+2] )
        {
            return 0;
        }
        else
        {
            this->blocos[posicaoVazia] = this->blocos[posicaoVazia+2];
            this->blocos[posicaoVazia+2] = '-';
            this->posicaoVazia +=2;
            return 1;
        }
    }

    //saltar peca para direita
    if(tipo==4)
    {
        if(this->posicaoVazia<=1  || blocos[this->posicaoVazia-1] == blocos[this->posicaoVazia-2])
        {
            return 0;
        }
        else
        {
            this->blocos[posicaoVazia] = this->blocos[posicaoVazia-2];
            this->blocos[posicaoVazia-2] = '-';
            this->posicaoVazia -=2;
            return 1;
        }
    }
    return 0;
}

//gera um estado aleatorio, coloca as pecas na regua de forma aleatoria
void estado::embaralhaBlocos()
{
    vector<char> blocks;

    for(int i=0; i<(int)this->nBlocos/2; i++)
        blocks.push_back('1');

    for(int i=(int)this->nBlocos/2; i<nBlocos-1; i++)
        blocks.push_back('0');

    blocks.push_back('-');

    random_shuffle(blocks.begin(), blocks.end());

    for(int i=0; i<nBlocos; i++)
    {
        this->blocos[i] = blocks.at(i);
        if(this->blocos[i]=='-')
            this->posicaoVazia = i;
    }
}

bool estado::verificaSolucao()
{
    if(this->blocos[this->nBlocos/2] =='0')
    {
        for(int i = 0; i < this->nBlocos/2; i++)
        {
            if(this->blocos[i] == '1')
            {
                this->ehSolucao = false;
                return false;
            }
        }
        this->ehSolucao = true;
        return true;
    }

    if(this->blocos[this->nBlocos/2] =='1')
    {
        for(int i = this->nBlocos/2 +1; i < this->nBlocos; i++)
        {
            if(this->blocos[i] == '0')
            {
                this->ehSolucao = false;
                return false;
            }
        }
        this->ehSolucao = true;
        return true;
    }

    if(this->blocos[this->nBlocos/2] =='-')
    {
        for(int i = 0; i < this->nBlocos/2; i++)
        {
            if(this->blocos[i] == '1')
            {
                this->ehSolucao = false;
                return false;
            }
        }
        this->ehSolucao = true;
        return true;
    }
}

bool estado::ehPredecessor(estado *f)
{
    return auxEhPredecessor(this, f);
}

bool estado::auxEhPredecessor(estado *e, estado *f)
{
    if( e->getBlocos() == f->getBlocos() )
    {
        return true;
    }
    else if(e->getPai()==NULL)
    {
        return false;
    }
    else
    {
        return auxEhPredecessor(e->getPai(), f);
    }
}

void estado::calculaCustoTotal()
{
    if(this->pai==NULL)
        this->custoTotal = 0;
    else
    {
        if(this->trans == 1 || this->trans == 2)
            this->custoTotal = pai->getCustoTotal() + 1;
        if(this->trans == 3 || this->trans == 4)
            this->custoTotal = pai->getCustoTotal() + 2;
    }
}

///Verifica distancia entre peca preta mais a esquerda e peca branca mais a direita (HEURISTICA 1)
void estado::calculaHeuristica2()
{
    int esquerda, direita;

    // Considerando que deseja-se pretas na direita
    for(int i=0; i<this->nBlocos; i++)
    {
        if(this->blocos[i]=='1')
        {
            esquerda = i;
            break;
        }
    }
    for(int i=nBlocos-1; i>0; i--)
    {
        if(this->blocos[i]=='0')
        {
            direita = i;
            break;
        }
    }
    int distancia = direita - esquerda;

    if(distancia < 0)   distancia = 0;
    this->valorH1 = distancia;
}


///Heuristica 2
void estado::calculaHeuristica1(){
    int meio = (int)this->nBlocos/2, i = 0, h2 = 0;
    for(; i < meio; i++){
        if(this->blocos[i] == '1')
            h2 ++;
    }
    i += 1;
    for(; i < this->nBlocos; i++){
        if(this->blocos[i] == '0')
            h2 ++;
    }
    this->valorH1 = h2;
}

void estado::calculaFuncaoAvaliacao()
{
    this->calculaCustoTotal();
    this->calculaHeuristica1();
    this->custoAvaliacao = this->getCustoTotal() + this->getHeuristica1();
}

string estado::getBlocos()
{
    ostringstream oss;
    for(int i=0; i<this->nBlocos; i++)
        oss << this->blocos[i];
    return oss.str();
}
