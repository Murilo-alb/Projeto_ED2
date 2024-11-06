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

Tpaciente *alocarNo(int ID, char *nome, int idade, char *condicao_medica);
Tpaciente *buscarID(Tpaciente *raiz, int ID); //Busca codigo pelo ID;
Tpaciente *buscarNome(Tpaciente *raiz, char *nome); //Busca codigo pelo nome;
Tpaciente **buscaPaiID(Tpaciente **raiz, int k); //Acha nó anterior pelo Id;
Tpaciente **buscaPaiNome(Tpaciente **raiz, char *nome); //Acha no anterior pelo nome;
Tpaciente **ppMenor(Tpaciente **raiz);//Achar o menor nó;

void insere(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica); 
void imprimeID(Tpaciente *raiz); 
void imprimeNome(Tpaciente *raiz);
void removerID(Tpaciente **raiz, int ID); //Remove o usuario pelo ID;
void removerNome(Tpaciente **raiz, char *nome);//Remove o usuario pelo nome;
void salvar(Tpaciente *raiz, FILE *arq); //Salva o arquivo;


int main(){
	
	//Processo de leitura de um arquivo
		FILE *arq=NULL;
		arq=fopen("paciente1.txt","r"); //Abrindo o arquivo para leitura
		if(arq == NULL){
		printf("Erro");	
			return 1;
		}
		
		Tpaciente *raiz_ID = NULL, *achou = NULL; // achou serve para buscar o ID ou Nome;
		int ID, idade, aux = 0;
		char nome[20];
		char condicao_medica[30];
		int op = 1, contador = 0;
		
		//guardando nas variaveis;
		while (fscanf(arq, "%d %s %d %s", &ID, nome, &idade, condicao_medica) == 4){
			 insere(&raiz_ID, ID, nome, idade, condicao_medica);
			 contador++;
		}
			fclose(arq);
			
			
			printf("Raiz: %d\n", raiz_ID->ID); //Imprime o nó raiz da arvoré
			
			while(op != 8){
				printf("1 - Imprimir por ID\n2 - Imprimeir por Nome\n3 - Cadastrar Paciente \n4 - Buscar por ID \n5 - Buscar por Nome\n6 - Remover ID\n7 - Remover Nome \n:");
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
						imprimeNome(raiz_ID);
						printf("\n");
							
					}break;
					
					case 3: {
						printf("\nInforme ID, Nome, Idade e Condição medica do novo paciente\n: ");
						scanf("%d %s %d %s", &ID, nome, &idade, &condicao_medica);
						insere(&raiz_ID, ID, nome, idade, condicao_medica);
						
					}break;
					
					case 4:{
						printf("Informe o ID: ");
							scanf("%d", &aux);
						achou = buscarID(raiz_ID, aux); //Utilização do achou por ID;
						if(achou){
							printf("\nID encontrado: %d\n", achou->ID);
						 printf("\nId: %d - %s - Idade: %d - %s\n\n", achou->ID, achou->nome, achou->idade, achou->condicao_medica);
					
						}else
							printf("\nNão existe\n");		
					}break;
					
					case 5:{
						char aux_nome[20];
						printf("Informe o Nome Completo: ");
							scanf("%s", aux_nome);
							
						achou = buscarNome(raiz_ID, aux_nome); //Utilização do achou por Nome;
						
						if(achou){
							printf("\nNome encontrado: %s\n\n", achou->nome);
							printf("\n%s - Id: %d - Idade: %d - %s\n\n", achou->nome, achou->ID, achou->idade, achou->condicao_medica);
					
						}else
							printf("\nNome nao existe\n");	
					}break;
					
					case 6: {
                printf("Informe o ID do paciente para remover: ");
                scanf("%d", &ID);
                removerID(&raiz_ID, ID);
                contador--; //Contador serve para a contagem dos pacientes;
            }break;

            case 7: {
                printf("Informe o Nome do paciente para remover: ");
                scanf("%s", nome);
                removerNome(&raiz_ID, nome);
                contador--;
            }break;
            
            case 8: {
            	printf("\nSaiu..");
            	printf("Total Pacientes: %d", contador);
            		
				arq=fopen("paciente1.txt","w"); //Abrindo o arquivo para escrita
            	if(arq == NULL){
            		return 1;
				}
					salvar(raiz_ID, arq);
					fclose;
				printf("\n\nFoi salvo");
			}break;
					default: 
						printf("Numero invalido");
				}
		}
		return 0;
}

Tpaciente *alocarNo (int ID, char *nome, int idade, char *condicao_medica)
{
    Tpaciente *novo=NULL;
    novo = (Tpaciente *)malloc(sizeof(Tpaciente));
    if(novo)
    {
    	//Atribuindo os valores
       	novo->ID = ID;
       	strcpy(novo->nome, nome); //strcpy para copiar uma string;
       	novo->idade = idade;
       	strcpy(novo->condicao_medica, condicao_medica); 
        novo->dir = NULL;
        novo->esq = NULL;
        
        return novo;
    }
    return novo;
}

void insere(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica)
{
    if(*raiz == NULL)
        *raiz = alocarNo(ID, nome, idade, condicao_medica);
    else{
    	//Confere se ja existe um ID;
		if (buscarID(*raiz, ID) != NULL) {
       		printf("ID já existe!\n");
        	return;
    }	
    	//Confere se ja existe um Nome;
   		 if (buscarNome(*raiz, nome) != NULL) {
       		printf(" Nome ja existe!\n");
       		 return;
    	}
    	//Recursividade;
    	if (ID < (*raiz)->ID)
        	insere(&(*raiz)->esq, ID, nome, idade, condicao_medica);
        else
            insere(&(*raiz)->dir, ID, nome, idade, condicao_medica);
	}
}

void imprimeID(Tpaciente *raiz)
{
	//Imprime in-Order
	  if (raiz != NULL) {
        imprimeID(raiz->esq);
        printf("%d - ", raiz->ID);
        imprimeID(raiz->dir);
	}
}

void imprimeNome(Tpaciente *raiz)
{
	if(raiz != NULL)
	{	//Imprime in-Order pela tabela ascii
		imprimeNome(raiz->esq);
		printf("%s\n", raiz->nome);
		imprimeNome(raiz->dir);
	}

}

Tpaciente *buscarID(Tpaciente *raiz, int ID)
{
    if(raiz == NULL)
        return NULL;
        
    if(ID == raiz->ID)
        return raiz;
    else
    {
        if(ID < raiz->ID)
            return buscarID(raiz->esq, ID);
        else
            return buscarID(raiz->dir, ID);
    }
}

Tpaciente *buscarNome(Tpaciente *raiz, char *nome)
{
	if(raiz == NULL)
		return NULL;
	int comparar = strcmp(nome, raiz->nome); // compara duas strings
	
	if(comparar == 0)
		return raiz;
		
	if(comparar < 0)
		return buscarNome(raiz->esq, nome);
	else
		return buscarNome(raiz->dir, nome);		
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
Tpaciente **buscaPaiNome(Tpaciente **raiz, char *nome)
{
    while (*raiz != NULL) {
        int comparar = strcmp(nome, (*raiz)->nome);
        if (comparar == 0) 
		return raiz;
		
        raiz = (comparar < 0) ? &(*raiz)->esq : &(*raiz)->dir;
    }
    return NULL;
}

Tpaciente **ppMenor(Tpaciente **raiz)
{
    while (*raiz && (*raiz)->esq != NULL)
        raiz = &(*raiz)->esq;

    return raiz;
}


//Mesmo remove utilizado em aula
void removerID(Tpaciente **raiz, int ID){	
    if(*raiz == NULL)
        return;
        
        Tpaciente **pai=NULL;
		pai = buscaPaiID(raiz, ID);
 		
 		if (pai == NULL)
        return; 
    
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {
        free(*pai);
        *pai = NULL;
        
        return;
        
    }else if(((*pai)->esq != NULL) ^ (*pai)->dir !=NULL)
        {
            if((*pai)->esq != NULL)
			{
                Tpaciente *paux=(*pai)->esq; 
                free(*pai);
                *pai = paux;
				return; 
				
            }else if((*pai)->dir != NULL)
			{
                Tpaciente *paux=(*pai)->dir;
                free(*pai);
                *pai = paux;
            }
            return;
        }
      
        else{
            {
                Tpaciente **paux = ppMenor(&(*pai)->dir);
                printf("\n %d", (*paux)->ID);
                printf("\nMenor %d %p", (*paux)->ID, paux);
                (*pai)->ID = (*paux)->ID;
                strcpy((*pai)->nome, (*paux)->nome);
                printf("\ntrocou chave...");
                removerID(paux, (*paux)->ID);
            }
        }
	} 

//Mesmo remove utilizado em aula, uma pequena mudança para buscar por nome;
void removerNome(Tpaciente **raiz, char *nome){
    if((*raiz) == NULL)
        return;
        
    Tpaciente **pai=NULL;
	pai = buscaPaiNome(raiz, nome);
		 
	if (pai == NULL)
       return;
		 
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {	
        free(*pai);
        *pai = NULL;
        return;
    }
    else{
        if(((*pai)->esq != NULL) ^ (*pai)->dir !=NULL)
        {
            if((*pai)->esq != NULL)
            {
                Tpaciente *paux=(*pai)->esq;
                free(*pai);
                *pai = paux;
             
            }
            if((*pai)->dir != NULL)
            {	
                Tpaciente *paux=(*pai)->dir; 
                free(*pai);
                *pai = paux;
            }
            return;
        }
        else{
            {
                Tpaciente **paux = ppMenor(&(*pai)->dir);
                (*pai)->ID = (*paux)->ID;
                strcpy((*pai)->nome, (*paux)->nome);
                removerNome(paux, (*paux)->nome);
            }
        }
    } 
}

void salvar(Tpaciente *raiz, FILE *arq)
{
	if(raiz != NULL){
		//recursividade
		salvar(raiz->esq, arq);
		fprintf(arq, "%d %s %d %s\n", raiz->ID, raiz->nome, raiz->idade, raiz->condicao_medica); //Salva no arquivo
		salvar(raiz->dir, arq);
	}
}
