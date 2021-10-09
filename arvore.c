#include<stdio.h>
#include<stdlib.h>

typedef struct No *Apontador; //Define apontador como tipo ponteiro para estrutura No

typedef struct No{
    int Reg;
    Apontador *pEsq, *pDir;
}No;

int Insere(int x, No **ppRaiz);
int Balanceamento(No** ppRaiz);
int FB (No** pRaiz);
int Altura(No** pRaiz);
int BalancaEsquerda(No **ppRaiz);
int BalancaDireita(No **ppRaiz);
void RSD(No** ppRaiz);
void RSE(No** ppRaiz);

void Inicializa(Apontador *Dicionario){
*Dicionario = NULL;
}

int main(){
    Apontador *Dicio;
    Inicializa(Dicio);
    int n=0, valor=0;
    printf("Quantos nos a arvore tera?\n");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Digite valor para ser inserido\n");
        scanf("%d", &valor);
        Insere(valor,Dicio);
        Balanceamento(Dicio);
    }
    return 0;
}

int Insere(int x, No **ppRaiz){
    if (*ppRaiz == NULL){
        *ppRaiz = (No*)malloc(sizeof(No));
        (*ppRaiz)->Reg = x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }
    else if ((*ppRaiz)->Reg> x){
        if ( Insere(x, &(*ppRaiz)->pEsq) ){
            if (Balanceamento(ppRaiz))
            return 0;
        }
        else{
            return 1;
        }
    }
    else if ( (*ppRaiz)->Reg< x){
        if ( Insere(x, &(*ppRaiz)->pDir) ){
            if (Balanceamento(ppRaiz)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0; /* valor jah presente */
    }
}

void RSD(No** ppRaiz){//ROTAÇÃO SIMPLES DIREITA
    No *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSE(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

//-1<=FB<=1 PARA ESTAR BALANCEADA
/*int Balanceamento(Apontador *p){
    int balanceada=0;

        balanceada=FB(*p);
        printf("O FB eh: %d\n", balanceada);
        if(balanceada<-1){
        //se o lado direito está maior
        }
        if(balanceada>1){
            //se o lado esquerdo está maior
            RSimplesDir(*p);
        }
}*/

int Balanceamento(No** ppRaiz){
int fb = FB(ppRaiz);
if ( fb > 1)
    return BalancaEsquerda(ppRaiz);
else if (fb <-1 )
    return BalancaDireita(ppRaiz);
else
    return 0;
}

int BalancaEsquerda(No** ppRaiz)
{
int fbe = FB ( (*ppRaiz)->pEsq );
if ( fbe > 0 ){
    RSD(ppRaiz);
    return 1;
}
else if (fbe < 0 ){ /* Rotação Dupla Direita */
    RSE( &((*ppRaiz)->pEsq) );
    RSD( ppRaiz ); /* &(*ppRaiz) */
    return 1;
}
return 0;
}

int BalancaDireita(No** ppRaiz){
int fbd = FB((*ppRaiz)->pDir);
if ( fbd < 0 ){
    RSE (ppRaiz);
    return 1;
}
else if (fbd > 0 ){ /* Rotação Dupla Esquerda */
    RSD( &((*ppRaiz)->pDir) );
    RSE( ppRaiz ); /* &(*ppRaiz) */
    return 1;
}
return 0;
}

int FB (No** pRaiz){
    if (*pRaiz == NULL){
       return 0;
    }
    return Altura(&((*pRaiz)->pEsq))-Altura(&((*pRaiz)->pDir));
}

int Altura(No** pRaiz){
int iEsq,iDir;
if (*pRaiz == NULL){
    return 0;
}
iEsq = Altura(&((*pRaiz)->pEsq));
iDir = Altura(&((*pRaiz)->pDir));
    if ( iEsq > iDir ){
        return iEsq + 1;
    }
    else{
        return iDir + 1;
    }
}