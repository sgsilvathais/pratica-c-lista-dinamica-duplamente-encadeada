#include <stdio.h>
#include <stdlib.h>

typedef struct numero
{
    int num;
    struct numero *prox;
    struct numero *ante;
} TipoNumero;

typedef struct listaDDE
{
    TipoNumero *primeiro;
    TipoNumero *ultimo;
    int tamanho;
} TipoListaDDE;

//----------Inicializa a lista----------
void inicializaListaDDE(TipoListaDDE *listaAux)
{
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanho = 0;
}

void criaListaInicial(TipoListaDDE *listaAux)
{
    int i;
    TipoNumero *novo = malloc(sizeof(TipoNumero));

    scanf("%d", &novo->num);

        if(listaAux->tamanho == 0)
        {
            listaAux->primeiro = novo;
            listaAux->ultimo = novo;
            novo->ante = NULL;
            novo->prox = NULL;
        }
        else
        {
            novo->ante = listaAux->ultimo;
            novo->prox = NULL;
            listaAux->ultimo->prox = novo;
            listaAux->ultimo = novo;            
        }
        listaAux->tamanho++;

}

void imprimeListaDDE(TipoListaDDE *listaAux)
{
    TipoNumero *aux = listaAux->primeiro;
    if(listaAux->tamanho != 0){
        while(aux != NULL)
        {
            printf("%d ", aux->num);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void insereJogada(TipoListaDDE *listaAux)
{
    TipoNumero *novo = malloc(sizeof(TipoNumero)), *aux = listaAux->primeiro;
    int pos, i;

    scanf("%d %d", &novo->num, &pos);
    
    if(novo->num > 0 && novo->num <= 9)
    {
        if(pos == 0)
        {
            novo->ante = NULL;
            novo->prox = listaAux->primeiro;
            listaAux->primeiro->ante = novo;
            listaAux->primeiro = novo;
        }
        else if(pos == (listaAux->tamanho - 1))
        {
            novo->prox = NULL;
            novo->ante = listaAux->ultimo;
            listaAux->ultimo->prox = novo;
            listaAux->ultimo = novo;
        }
        else
        {
            for (i = 0; i < pos; i++)
            {
                aux = aux->prox;
            }
            novo->ante = aux->ante;
            novo->prox = aux;
            aux->ante->prox = novo;
            aux->ante = novo;
        }
        listaAux->tamanho++;
    } else exit(1);
    
}

int procuraTriplas(TipoListaDDE *listaAux)
{
    int soma, cont = 0;
    TipoNumero *aux = listaAux->primeiro;
    if (listaAux->tamanho >= 3){
    while(cont < listaAux->tamanho)
    {   
        if(cont == 0)
            soma = listaAux->ultimo->num + aux->num + aux->prox->num;
        else if(cont == (listaAux->tamanho-1))
            soma = listaAux->primeiro->num + aux->ante->num + aux->num;
        else
            soma = aux->ante->num + aux->num + aux->prox->num;     
        if (soma == 10)
            return cont;
        else
        {
            aux = aux->prox;
            cont++;
        }
    }
    }

    return -1;
}

void removeTriplas(TipoListaDDE *listaAux, int pos)
{
    int i = 0;
    TipoNumero *aux = listaAux->primeiro;

    while(i != pos)
    {
        aux = aux->prox;
        i++;
    }

    if(pos == 0)
    {
        if(listaAux->tamanho ==3)
        {
            free(aux->prox->prox);
            free(aux->prox);
            free(aux);
            listaAux->ultimo = NULL;
            listaAux->primeiro = NULL;
        }
        else
        {
            listaAux->ultimo = listaAux->ultimo->ante;
            free(listaAux->ultimo->prox);
            listaAux->ultimo->prox = NULL;
            listaAux->primeiro = aux->prox->prox;
            listaAux->primeiro->ante = NULL;
            free(aux->prox);
            free(aux);
        }        
    }
    else if(pos == (listaAux->tamanho-1))
    {
        listaAux->ultimo = aux->ante->ante;
        listaAux->ultimo->prox = NULL;
        listaAux->primeiro = listaAux->primeiro->prox;
        free(listaAux->primeiro->ante);
        listaAux->primeiro->ante = NULL;
        free(aux->ante);
        free(aux);
    }
    else{
        if(pos == 1)
        {
            listaAux->primeiro = aux->prox->prox;
            listaAux->primeiro->ante = NULL;
        }
        else if(pos == (listaAux->tamanho-2))
        {
            listaAux->ultimo = aux->ante->ante;
            listaAux->ultimo->prox = NULL;
        }
        else 
        {
            aux->ante->ante->prox = aux->prox->prox;
            aux->prox->prox->ante = aux->ante->ante;
        }

        free(aux->ante);
        free(aux->prox);
        free(aux);
    }
    listaAux->tamanho -= 3;
    
}

void verificaResultado(TipoListaDDE *listaAux)
{
    if(listaAux->tamanho == 0)
        printf("ganhou\n");
    else printf("perdeu\n");
}

int main (void)
{
    TipoListaDDE start;
    int i, posicao;
    
    inicializaListaDDE(&start);

    for (i = 0; i < 10; i++)
    {
        criaListaInicial(&start);
    }

    imprimeListaDDE(&start);

    for (i = 0; i < 5; i++)
    {
        insereJogada(&start);

            while((posicao = procuraTriplas(&start)) != -1)
                {                  
                    removeTriplas(&start, posicao);
                }
        imprimeListaDDE(&start);
    }

    verificaResultado(&start);

    return 0;
}
