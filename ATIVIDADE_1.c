
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct paciente
{
	int ID;
	char nome[20];
	int idade;
	char condicao_medica[30];
	struct paciente *esq;
	struct paciente *dir;
	
}Tpaciente;


Tpaciente *alocarNo(int ID, char *nome, int idade, char *condicao_medica);//criar um nó na memoria
Tpaciente *buscar_PacienteID(Tpaciente *raiz, int ID);
Tpaciente *buscar_PacienteNome(Tpaciente *raiz, char *nome);
Tpaciente **buscaPaiID(Tpaciente **raiz, int k);
Tpaciente *buscaPaiNome(Tpaciente *raiz, char *nome);
Tpaciente **ppMenor(Tpaciente **raiz);


void insereID(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica); //Arvore por ID
void insereNome(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica); // Arvore por NOME
void imprimeID(Tpaciente *raiz);
void imprimeNome(Tpaciente *raiz);
void removerID(Tpaciente **raiz, int ID);
void removerNome(Tpaciente **raiz, char *nome);

int main(){
		FILE *arq=NULL;
		arq=fopen("paciente1.txt","r");
		if(arq == NULL)
			return 1;
			
						
		Tpaciente *raiz_ID = NULL, *raiz_Nome = NULL, *achouID = NULL, *achouNome = NULL;
		int ID, idade, aux = 0;
		char nome[20];
		char condicao_medica[30];
		
		int op = 1;
		while(!feof(arq)){
	
			fscanf(arq, "%d %s %d %s", &ID, nome, &idade, condicao_medica);
			
			 insereID(&raiz_ID, ID, nome, idade, condicao_medica);
				insereNome(&raiz_Nome, ID, nome, idade, condicao_medica);
					
		
		}
			fclose(arq);
			printf("Raiz: %d\n", raiz_ID->ID);
			
			while(op != 7){
				printf("1 - Imprimir por ID\n2 - Imprimeir por Nome\n3 - Buscar por ID\n4 - Buscar por Nome\n5 - Remover ID\n:");
					scanf("%d", &op);
				fflush(stdin);
				switch(op){	
				 	case 1:{
				 		printf("\n\n");
						imprimeID(raiz_ID);
							printf("\n\n");
						
					}break;
					
					case 2:{
						printf("\n");
						imprimeNome(raiz_Nome);
						printf("\n");
							
					}break;
					
					case 3:{
						printf("Informe o ID: ");
							scanf("%d", &aux);
						achouID = buscar_PacienteID(raiz_ID, aux);
						
						if(achouID)
							printf("\nID encontrado: %d\n", achouID->ID);
						else
							printf("\nNão existe\n");
							
						
					}break;
					
					case 4:{
						char aux_nome[20];
						printf("Informe o Nome Completo: ");
							scanf("%s", aux_nome);
						achouNome = buscar_PacienteNome(raiz_Nome, aux_nome);
						
						if(achouNome)
							printf("\nNome encontrado: %s\n\n", achouNome->nome);
						else
							printf("\nNome nao existe\n");	
						
					}break;
					
					case 5:{
						printf("\nInforme o valor desejado: ");
							scanf("%d", &aux);
							removerID(&raiz_ID, aux);	
					}break;
				}
		}
}

Tpaciente *alocarNo (int ID, char *nome, int idade, char *condicao_medica)
{
    Tpaciente *novo=NULL;
    novo = (Tpaciente *)malloc(sizeof(Tpaciente));
    if(novo)
    {
       	novo->ID = ID;
       	strcpy(novo->nome, nome);
       	novo->idade = idade;
       strcpy(novo->condicao_medica, condicao_medica);
        novo->dir = NULL;
        novo->esq = NULL;
        
        return novo;
    }
    return novo;
}

void insereID(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica)
{
    if(*raiz == NULL)
        *raiz = alocarNo(ID, nome, idade, condicao_medica);
    else{
	
        if(ID < (*raiz)->ID)
            insereID(&(*raiz)->esq, ID, nome, idade, condicao_medica);
    	else
            insereID(&(*raiz)->dir, ID, nome, idade, condicao_medica);
	}
    
}


void insereNome(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica)
{
	if(*raiz == NULL)
		*raiz = alocarNo(ID, nome, idade, condicao_medica);
		else{
		if(strcmp(nome, (*raiz)->nome) < 0)
    		 insereNome(&(*raiz)->esq, ID, nome, idade, condicao_medica);
    	else
           	 insereNome(&(*raiz)->dir, ID, nome, idade, condicao_medica);
		}
}

void imprimeID(Tpaciente *raiz)
{
	  if (raiz != NULL) {
        imprimeID(raiz->esq);
        printf("%d - ", raiz->ID);
        imprimeID(raiz->dir);
	}
}

void imprimeNome(Tpaciente *raiz)
{

	if(raiz != NULL)
	{
		imprimeNome(raiz->esq);
		printf("%s", raiz->nome);
		printf("\n");
		imprimeNome(raiz->dir);
		
	}

}

Tpaciente *buscar_PacienteID(Tpaciente *raiz, int ID)
{
    if(raiz == NULL)
        return NULL;
        
    if(ID == raiz->ID)
        return raiz;
    else
    {
        if(ID < raiz->ID)
            return buscar_PacienteID(raiz->esq, ID);
        else
            return buscar_PacienteID(raiz->dir, ID);
    }
}

Tpaciente *buscar_PacienteNome(Tpaciente *raiz, char *nome)
{
	if(raiz == NULL)
		return NULL;
	int comparar = strcmp(nome, raiz->nome);
	
	if(comparar == 0)
		return raiz;
		
	if(comparar < 0)
		return buscar_PacienteNome(raiz->esq, nome);
	else
		return buscar_PacienteNome(raiz->dir, nome);		
}

Tpaciente **buscaPaiID(Tpaciente **raiz, int ID)
{
	if (*raiz == NULL)
    return NULL;
  while(*raiz!=NULL)
  {
      if((*raiz)->ID == ID)
        return raiz;
      if((*raiz)->ID < ID)
        raiz = &((*raiz)->dir);
      else
        raiz = &((*raiz)->esq);
        
  }
  
}
Tpaciente *buscaPaiNome(Tpaciente *raiz, char *nome)
{
	int comparar = strcmp(nome, raiz->nome);
	if (raiz == NULL)
    	return NULL;
    	
  while(raiz!=NULL)
  {
      if(comparar == 0)
        return raiz;
        
      if(comparar < 0)
        return buscaPaiNome(raiz->esq, nome);
      else
        return buscaPaiNome(raiz->dir, nome);
        
	}	
}

void removerID(Tpaciente **raiz, int ID)
{
	 Tpaciente **pai= NULL;
    if((*raiz) == NULL)
        return;
        
    pai = buscaPaiID(raiz, ID);
    Tpaciente *remover_Nome = *pai;
    
    //1o caso --> remover no folha
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
	{

    	removerNome(&raiz, remover_Nome->nome);
        free(remover_Nome);
        *pai = NULL;
    }
    //2o caso --> remover pai com 1 filho apenas
    else{
        if(((*pai)->esq != NULL) ^ (*pai)->dir !=NULL)
        {
            if((*pai)->esq != NULL)
            {
                Tpaciente *paux=(*pai)->esq; //guardando end. filho
                free((*pai));
                *pai = paux;
            }
            if((*pai)->dir != NULL)
            {
                Tpaciente *paux=(*pai)->dir; //guardando end. filho
                free((*pai));
                *pai = paux;
            }
        }
        //    3o caso --> remover pai com 2 filhos
        else{
           // if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                Tpaciente **paux = ppMenor(&(*pai)->dir);
                //substituiDados
                (*pai)->ID = (*paux)->ID;
				strcpy((*pai)->nome, (*paux)->nome);
				strcpy((*pai)->condicao_medica, (*paux)->condicao_medica);
                removerNome();
            }
        }
    }
}

void removerNome(Tpaciente **raiz, char *nome)
{		 Tpaciente **pai=NULL;

    if((*raiz) == NULL)
        return;
        
    pai = buscaPaiNome(*raiz, nome);
    Tpaciente *remover_ID = *pai;
    
    //1o caso --> remover no folha
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {
        free(remover_ID);
        *pai = NULL;
    
    }
    //2o caso --> remover pai com 1 filho apenas
    else{
        if(((*pai)->esq != NULL) ^ (*pai)->dir !=NULL)
        {
            if((*pai)->esq != NULL)
            {
                Tpaciente *paux=(*pai)->esq; //guardando end. filho
                free(remover_ID);
                *pai = paux;
                /*
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(*paux);
                */
            }
            if((*pai)->dir != NULL)
            {
                Tpaciente *paux=(*pai)->dir; //guardando end. filho
                free(remover_ID);
                *pai = paux;
            }
        }
        //    3o caso --> remover pai com 2 filhos
        else{
           // if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                Tpaciente **paux = ppMenor(&remover_ID->dir);
                strcpy(remover_ID->nome, (*paux)->nome);
                //substituiDados
                remover_ID->ID = (*paux)->ID;
                printf("\ntrocou chave...");
                strcpy(remover_ID->condicao_medica, (*paux)->condicao_medica);
                removerNome(&(*pai)->dir, (*paux)->nome);
            }
        }
    }
			
	
	
	
}

Tpaciente **ppMenor(Tpaciente **raiz)//a entrada ? o lado direito da ?rvore
{
    Tpaciente **pmenor=raiz;
    while((*pmenor)->esq)
    {
        printf("\n%d", (*pmenor)->ID);
        pmenor = &(*pmenor)->esq;
    }
    return pmenor;
}
