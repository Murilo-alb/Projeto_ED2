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
Tpaciente **buscaPaiID(Tpaciente **raiz, int k); //Acha n? anterior pelo Id;
Tpaciente **buscaPaiNome(Tpaciente **raiz, char *nome); //Acha no anterior pelo nome;
Tpaciente **ppMenor(Tpaciente **raiz);//Achar o menor n?;

void insereID(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica); //Arvore por ID
void insereNome(Tpaciente **raiz, int ID, char *nome, int idade, char *condicao_medica); // Arvore por NOME
void imprimeID(Tpaciente *raiz);
void imprimeNome(Tpaciente *raiz);
void removerID(Tpaciente **raiz, int ID); //Remove o usuario pelo ID;
void removerNome(Tpaciente **raiz, char *nome);//Remove o usuario pelo nome;
void salvar(Tpaciente *raiz, FILE *arq); //Salva o arquivo;


int main(){
	
	//Processo de leitura de um arquivo
		FILE *arq=NULL;
		arq=fopen("paciente1.txt","r"); //Abrindo o arquivo para leitura
		
		//Conferindo se o arq ? Vazio;
		if(arq == NULL){
		printf("Erro");	
			return 1;
		}
		
		Tpaciente *raiz_ID = NULL, *raiz_Nome = NULL, *achouID = NULL, *achouNome = NULL; // achou serve para buscar o ID ou Nome;
		int ID, idade, aux = 0;
		char nome[20];
		char condicao_medica[30];
		int op = 1, contador = 0;
		
		//guardando nas variaveis;
		fscanf(arq, "%d", &contador); //Armazena quantidade de Pacientes
		while (fscanf(arq, "%d %s %d %s", &ID, nome, &idade, condicao_medica) == 4){
			 
			 	
			insereID(&raiz_ID, ID, nome, idade, condicao_medica); //Insere para organizar ID;
			insereNome(&raiz_Nome, ID, nome, idade, condicao_medica); //Insere para organizar Nome; 
		}
			fclose(arq); //Fecha o arquivo;
			
			
			printf("Raiz: %d\n", raiz_ID->ID); //Imprime o n? raiz da arvor?
			

			//Op??es para usuario escolher;
			while(op != 8){
				printf("1 - Imprimir por ID\n2 - Imprimeir por Nome\n3 - Cadastrar Paciente \n4 - Buscar por ID \n5 - Buscar por Nome\n6 - Remover ID\n7 - Remover Nome \n8 - Sair\n:");
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
					
					case 3: {
						printf("\nInforme ID, Nome, Idade e Condi??o medica do novo paciente\n: ");
						scanf("%d %s %d %s", &ID, nome, &idade, &condicao_medica);
						
						achouID = buscarID(raiz_ID, ID);
						achouNome = buscarNome(raiz_Nome, nome);
						
						if(achouID || achouNome){
							printf("Ja existe");
						}else{
						insereID(&raiz_ID, ID, nome, idade, condicao_medica);
						insereNome(&raiz_Nome, ID, nome, idade, condicao_medica);
						contador++;
					}
						
					}break;
					
					case 4:{
						printf("Informe o ID: ");
							scanf("%d", &aux);
							
						achouID = buscarID(raiz_ID, aux); //Utiliza??o do achou por ID;
						
						if(achouID){
							printf("\nID encontrado: %d\n", achouID->ID);
						 printf("\nId: %d - %s - Idade: %d - %s\n\n", achouID->ID, achouID->nome, achouID->idade, achouID->condicao_medica);
					
						}else
							printf("\nN?o existe\n");		
					}break;
					
					case 5:{
						char aux_nome[20];
						printf("Informe o Nome Completo: ");
							scanf("%s", aux_nome);
							
						achouNome = buscarNome(raiz_Nome, aux_nome);
						
						if(achouNome){
							printf("\nNome encontrado: %s\n\n", achouNome->nome);
							printf("\nId: %d - %s - Idade: %d - %s\n\n", achouNome->ID, achouNome->nome, achouNome->idade, achouNome->condicao_medica);
						}else
							printf("\nNome nao existe\n");	
					}break;
					
					case 6: {
                		printf("Informe o ID do paciente para remover: ");
                		scanf("%d", &ID);
                		
                		achouID = buscarID(raiz_ID, ID);
                		
                		if(achouID){
                			achouNome = buscarNome(raiz_Nome, achouID->nome);
							if(achouNome){
                			removerID(&raiz_ID, ID);
                			removerNome(&raiz_Nome, achouNome->nome); //Para remover o N? na arvore Nome;
                			contador--;
                			}
                		}else
                			printf("\nNao achou\n");
                		
            		}break;
					
					
					case 7:{
                		printf("Informe o Nome do paciente para remover: ");
                		scanf("%s", nome);
                		
                		achouNome = buscarNome(raiz_Nome, nome);
                		
                		if(achouNome){
                			achouID = buscarID(raiz_ID, achouNome->ID);
                			
                			if(achouID){
                			removerNome(&raiz_Nome, nome);
                			removerID(&raiz_ID, achouID->ID);//Para remover o N? na arvore ID;
							contador--;	
							}
							
                		}else
                			printf("\nNao achou\n");
                			
            		}break;
            		
            		case 8: {
            			printf("\nSaiu..");
            			printf("Total Pacientes: %d", contador); //Pega o contador e imprime;
						arq=fopen("paciente1.txt","w"); //Abrindo o arquivo para escrita
     	
						if(arq == NULL)
            				return 1;
            			fprintf(arq, "%d\n", contador);
						salvar(raiz_ID, arq);
						fclose(arq);
						printf("\n\nFoi salvo");
					}break;
					
					//Caso o usuario coloque uma op??o invalida
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
		else if(strcmp(nome, (*raiz)->nome) < 0)
    		 insereNome(&(*raiz)->esq, ID, nome, idade, condicao_medica);
    	else
           	 insereNome(&(*raiz)->dir, ID, nome, idade, condicao_medica);
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
     
void imprimeID(Tpaciente *raiz)
{
	  if (raiz != NULL) {
        imprimeID(raiz->esq);
        printf("%d - ", raiz->ID);
        imprimeID(raiz->dir);
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
	
	//Tabela ascii
	if(comparar == 0)
		return raiz;
		
	if(comparar < 0)
		return buscarNome(raiz->esq, nome); //Recursividade
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

//Algumas modifica??es de buscarPaiID;
Tpaciente **buscaPaiNome(Tpaciente **raiz, char *nome)
{
    while (*raiz != NULL) {
        int comparar = strcmp(nome, (*raiz)->nome);
        if (comparar == 0) 
		return raiz;
		
		if (comparar < 0) {
   		 raiz = &(*raiz)->esq;
		}else{
    		raiz = &(*raiz)->dir;
		}   
    }
    return NULL;
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

//Mesmo remove utilizado em aula, uma pequena mudan?a para buscar por nome;
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
            	return;
            }
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

//Para salvar o arquivo .txt;
void salvar(Tpaciente *raiz, FILE *arq)
{
	if(raiz != NULL){
		//recursividade
		salvar(raiz->esq, arq);
		fprintf(arq, "%d %s %d %s\n", raiz->ID, raiz->nome, raiz->idade, raiz->condicao_medica); //Salva no arquivo
		salvar(raiz->dir, arq);
	}
}			
