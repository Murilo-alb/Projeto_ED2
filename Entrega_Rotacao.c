#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    int altDireita;
    int altEsquerda;
    struct no *dir;
    struct no *esq;
} Tno;


Tno *criarNo(int chave);
Tno *balecear(Tno *no);
Tno *rotacaoEsquerda(Tno *no);
Tno *rotacaoDireita(Tno *no);
void exibirArvore(Tno *no);

int main() {
    Tno *raiz_ID = NULL;
    int chave, op = 0;

    while (op != 2) {
        printf("1 - Cadastrar Paciente\n2 - Exibir\n3- Sair\n");
        scanf("%d", &op);

        switch(op) {
            case 1: {
                printf("\nInforme Chave: \n");
                scanf("%d", &chave);

                if (raiz_ID == NULL) {
                    raiz_ID = criarNo(chave);
                } else {
                    if (chave < raiz_ID->chave) {
                        raiz_ID->esq = criarNo(chave);
                        raiz_ID->altEsquerda = 1;
                    } else if (chave > raiz_ID->chave) {
                        raiz_ID->dir = criarNo(chave);
                        raiz_ID->altDireita = 1;
                    }
                    raiz_ID = balecear(raiz_ID);    
                }
            } break;

            case 2: {
                printf("Exibindo!\n");
                exibirArvore(raiz_ID);
            } break;
			
			case 3: {
				printf("Saindo!");
			}break;
            default:
                printf("Numero invalido\n");
        }
    }

    return 0;
}

Tno *criarNo(int chave) {
    Tno *aux = (Tno *)malloc(sizeof(Tno));
    aux->chave = chave;
    aux->altDireita = 0;
    aux->altEsquerda = 0;    
    aux->dir = NULL;
    aux->esq = NULL;
    return aux;
}

Tno *balecear(Tno *no) {
    if (!no)
        return NULL;
    
    int MaiorMenor = no->altDireita - no->altEsquerda;

    if (MaiorMenor == 2) {
        int diferenca = no->dir->altDireita - no->esq->altEsquerda;

    
        if (diferenca >= 0) {
            no = rotacaoEsquerda(no);
        } else {
            no->dir = rotacaoDireita(no->dir);
            no = rotacaoEsquerda(no);
        }
    }
 
    else if (MaiorMenor == -2) {
        int diferenca = no->esq->altDireita - no->dir->altEsquerda;

        if (diferenca <= 0) {
            no = rotacaoDireita(no);
        } else {
            no->esq = rotacaoEsquerda(no->esq);
            no = rotacaoDireita(no);
        }
    }

    return no;
}

Tno *rotacaoEsquerda(Tno *no) {
    Tno *aux1 = no->dir;
    Tno *aux2 = no->esq;
    no->dir = aux2;
    aux1->esq = no;

    if (no->dir == NULL) {
        no->altDireita = 0;
    } else if (no->dir->altEsquerda > no->dir->altDireita) {
        no->altDireita = no->dir->altEsquerda + 1;
    } else {
        no->altDireita = no->dir->altDireita + 1;
    }

    if (aux1->esq->altEsquerda > aux1->esq->altDireita) {
        aux1->altEsquerda = aux1->esq->altEsquerda + 1;
    } else {
        aux1->altEsquerda = aux1->esq->altDireita + 1;
    }

    return aux1;
}

Tno *rotacaoDireita(Tno *no) {
    Tno *aux1 = no->esq;
    Tno *aux2 = no->dir;
    no->esq = aux2;
    aux1->dir = no;

    if (no->esq == NULL) {
        no->altEsquerda = 0;
    } else if (no->esq->altEsquerda > no->esq->altDireita) {
        no->altEsquerda = no->esq->altEsquerda + 1;
    } else {
        no->altEsquerda = no->esq->altDireita + 1;
    }

    if (aux1->dir->altEsquerda > aux1->dir->altDireita) {
        aux1->altDireita = aux1->dir->altEsquerda + 1;
    } else {
        aux1->altDireita = aux1->dir->altDireita + 1;
    }

    return aux1;
}

void exibirArvore(Tno *no) {
    if (no != NULL) {
        printf("Chave: %d, Altura Esquerda: %d, Altura Direita: %d\n", no->chave, no->altEsquerda, no->altDireita);
        exibirArvore(no->esq);
        exibirArvore(no->dir);
    }
}

