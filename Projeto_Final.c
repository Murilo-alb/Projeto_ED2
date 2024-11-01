#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

typedef struct mapa{
		int i;// linha;
		int j; // coluna;
		int **matriz;
	
}Tmapa;

typedef struct unidade{
	char nome[15];
	int i;
	int j;
	int tipo; // 1-Soldado 2-Explorador; 
	struct unidade *prox;
}Tunidade; 

typedef struct edificio{
	int i;
	int j;
	int tipo; //1 -Edificio de Recurso 2 -Campo de Treinamento 3 -Laboratorio de pesquisa;
	struct edificio *prox;
}Tedificio;

typedef struct alianca{
		char nome[15]; //Nome da faccao aliada;
		struct alianca *prox;
}Talianca;

typedef struct faccao{
 char nome[15];
 int pontos_recurso;
 int pontos_poder;
 struct faccao *prox;
 Tunidade *proxunidade;
 Tedificio *proxedificio;
 Talianca *proxalianca;
}Tfaccao;




//funções para mapa;
Tmapa *aloca(int i, int j);
void cria_mapa(Tmapa *mapa);
void imprime_mapa(Tmapa *mapa);

//Função para unidade;
Tunidade *alocar_unidade(const char *nome, int i, int j, int tipo);
			
				
//Função para alocar edificio;
Tedificio *alocar_edificio(int i, int j, int tipo);


//função para criar facção;
Tfaccao *aloca_faccao(char *nome, int pontos_recurso, int pontos_poder);
void adicionar_faccao(Tfaccao **lista, Tfaccao *faccao);

//Funções para adicionar dentro da facção;
void adicionar_unidade(Tfaccao *faccao, Tunidade *unidade);
void adicio_edificio(Tfaccao *faccao, Tedificio *edificio);

//Função para formar aliança;
void formar_alianca(Tfaccao *lista, char *s1, char *s2);

//Desalocar
void desaloca_mapa(Tmapa **mapa);
void desaloca_uni(Tunidade *uni);
void desaloca_edif(Tedificio *edif);
void desaloca_fac(Tfaccao *lista);
    


//Função para atualizar mapa;
void mapa_atualizado(Tmapa *mapa, Tfaccao *lista);
void imprime_atualizado(Tmapa *mapa);

//Funções para dar condição ao switch;
void combate(Tfaccao *lista, char *nome1, char *nome2);
void constroi(Tfaccao *lista, int tipo);
void ataca(Tfaccao *lista1, Tfaccao *lista2);


int main(){
	
	FILE *arq=NULL;
    char s1[3], s2[9], letra;
    int v1, v2, v3, v4, t1, t2,fac;
    arq=fopen("entrada11_v2.txt","r");
    fscanf(arq,"%d %d", &t1, &t2);//lendo tamanho do tabuleiro
    fscanf(arq,"%d", &fac);//quantidade de fac??es
    printf("\n%d %d %d", t1, t2, fac);
    
     
    //Mapa;
    Tmapa *mapa = aloca(t1, t2);
    cria_mapa(mapa);
    printf("\n\nMatriz do mapa: \n");
    imprime_mapa(mapa);
    printf("\n"); 
    
    
    //Facção;
    Tfaccao *lista = NULL;
    int i = 0,linha, coluna;
	
	
	while(!feof(arq)){	
	fscanf(arq,"%s %s", &s1, &s2);
	
    for(i = i; i < fac; i++){
    	fscanf(arq, "%d %d", &linha, &coluna);
    	printf("Faccao %s\n posicao: %d %d", s1, linha, coluna);
    	Tfaccao *lista_nova = aloca_faccao(s1, 0, 0);
    	adicionar_faccao(&lista, lista_nova);
    	fscanf(arq, "%s %s", &s1, &s2);
    	printf("\n------------------------------\n");
	}
	
	//unidade;
	Tfaccao *lista_atual = lista;
	int tipo, linha, coluna, recebe, quantidade;
	int tipo2;
	char s3[3] = "\0";	
		
	switch (s2[0]){
		case 'p':{
		
			fscanf(arq, "%d %d %d", &tipo, &linha, &coluna);
			Tunidade *lista_unidade = alocar_unidade(s1, linha, coluna, tipo);
			while(lista_atual){	
				if(lista_atual->nome[1] == s1[0]){
					adicionar_unidade(lista_atual, lista_unidade);
					lista_atual->pontos_poder +=2;
					printf("\nFaccao: %s Pontos de poder: %d", lista_atual->nome, lista_atual->pontos_poder);
					Tunidade *unidade_atual = lista_atual->proxunidade;
					while(unidade_atual){
				
						printf("\nUnidade: %s Tipo: %d Posicao: %d %d", unidade_atual->nome, unidade_atual->tipo,
						unidade_atual->i, unidade_atual->j);
					unidade_atual = unidade_atual->prox;
				}
						break;
											
				}
					lista_atual = lista_atual->prox;	
			}
				
		}break;
		
		case 'm':{
		fscanf(arq, "%d %d %d", &tipo, &linha, &coluna);
				while(lista_atual){
						Tunidade *unidade_atual = lista_atual->proxunidade;
						while(unidade_atual){
			if(strcmp(unidade_atual->nome, s1) == 0){ 
				unidade_atual->i = linha;
				unidade_atual->j = coluna; 
				unidade_atual->tipo = tipo;
				printf("\nUnidade: %s Tipo: %d Move: %d %d", unidade_atual->nome, unidade_atual->tipo, 
				unidade_atual->i, unidade_atual->j);  
			}
				unidade_atual = unidade_atual->prox;	
		}
			lista_atual = lista_atual->prox;
	}			
	}break;				
		case 'c':{
			if(strcmp(s2, "coleta") == 0){
			fscanf(arq, "%d %d ", &tipo, &recebe);
				
				while(lista_atual){
						
						if(lista_atual->nome[1] == s1[0]){
							
							switch(mapa->matriz[linha][coluna]){
								
								case 1:{
									lista_atual->pontos_recurso += recebe;
								}break;
								
								case 2:{
									lista_atual->pontos_recurso = lista_atual->pontos_recurso;
								}break;
								
								case 3:{
									lista_atual->pontos_recurso += (recebe * 2);
								}break;
								
								default:{
									lista_atual->pontos_recurso = lista_atual->pontos_recurso;
								}break;
								
							}		
							
						}
						lista_atual = lista_atual->prox;
					}
					lista_atual = lista;
					while(lista_atual){
							if(lista_atual->nome[1] == s1[0]){
								printf("\nFaccao: %s Tem: %d pontos de recurso",lista_atual->nome, lista_atual->pontos_recurso);
							}
								lista_atual = lista_atual->prox;
					}
			
		}else if(strcmp(s2, "combate") == 0){
				fscanf(arq, "%d %s %d ", &tipo, &s3, &tipo2);	
				
				while(lista_atual){
						Tunidade *unidade_atual = lista_atual->proxunidade;
					
					while(unidade_atual){
						if(strcmp(s1, unidade_atual->nome) == 0){
								printf("\nUnidade: %s Tipo: %d Combate unidade: %s Tipo: %d", unidade_atual->nome
								, unidade_atual->tipo, s3, tipo2);	
									combate(lista_atual, s1, s3);	
					
						}
						
						unidade_atual= unidade_atual->prox;
							
					}
						
				
						lista_atual = lista_atual->prox;
				
					}
					
			}
	//edificio;
		else if(strcmp(s2, "constroi") == 0){
			
			fscanf(arq, "%d %d %d %d ", &quantidade, &tipo, &linha, &coluna);
			
			Tedificio *lista_edificio = alocar_edificio(linha, coluna, tipo);
			
			while(lista_atual){
			if(strcmp(s1, lista_atual->nome) == 0){
				adicio_edificio(lista_atual, lista_edificio);
			while(lista_atual->proxedificio){
				lista_atual->proxedificio->i = linha;
				lista_atual->proxedificio->j = coluna;
				lista_atual->proxedificio->tipo = tipo;
				printf("\nFaccao: %s  Constroi: %d Edificios Tipo: %d Posicao: %d %d", lista_atual->nome, quantidade,
				lista_atual->proxedificio->tipo, lista_atual->proxedificio->i, lista_atual->proxedificio->j);
				constroi(lista_atual, tipo);
				lista_atual->proxedificio = lista_atual->proxedificio->prox;
				}
			}
			lista_atual = lista_atual->prox;
		}	
	  }		
	}break;
			
	//facção 2;
		case 'g':{
				fscanf(arq, "%d", &recebe);
				while(lista_atual){
					if(strcmp(s1, lista_atual->nome) == 0){
						lista_atual->pontos_poder += recebe;
						printf("\nFaccao: %s Recebe: %d pontos de poder", lista_atual->nome, recebe);									
					}
					
						lista_atual = lista_atual->prox;
				}
				
				lista_atual = lista;
				while(lista_atual){
					if(strcmp(s1, lista_atual->nome) == 0){
					printf("\nFaccao: %s pontos de poder: %d", lista_atual->nome, lista_atual->pontos_poder);
				}
					lista_atual = lista_atual->prox;			
			}	
						
		}break;
		
		case 'a':{
			if(strcmp(s2, "alianca")== 0){
				fscanf(arq, "%s", &s3);
				printf("\nFaccao %s\n Alinca com: %s", s1, s3);
				formar_alianca(lista, s1, s3);
			}
			else if(strcmp(s2, "ataca")== 0){
				fscanf(arq, "%s %d %d", s3, &linha, &coluna);
				Tfaccao *lista_aux = lista;			
					while(lista_atual){
						if(strcmp(s1, lista_atual->nome) == 0){
								printf("\nFaccao: %s Ataca: %s na posicao %d %d", lista_atual->nome, s3, linha,coluna);
								
								while(lista_aux){
								
								if(strcmp(lista_aux->nome, s3)== 0){
								ataca(lista_atual, lista_aux);
								}
								
								lista_aux = lista_aux->prox;
							}
						
						}
							lista_atual = lista_atual->prox;
					}
						
				}
				
		}break;
		
		case 'd':{
				fscanf(arq, "%d %d", &linha, &coluna);
				while(lista_atual){
						if(strcmp(s1, lista_atual->nome) == 0){	
								printf("\nFaccao: %s Defende: %d %d", lista_atual->nome, linha, coluna);	
					}
					
					lista_atual = lista_atual->prox;
					
				}
					
			
		}break;

	}		
		
			/*mapa_atualizado(mapa, lista);
			printf("\nMapa Atualizado:\n");
			imprime_atualizado(mapa);
			printf("\n");
			*/
			printf("\n-------------------------------------------------\n");
			
}

			//Declarar vencedora;
			int coleta;
		
		if(lista){
			Tfaccao *aux = lista;
			coleta = lista->pontos_poder;
			
			while(aux){
				if(coleta < aux->pontos_poder){
				coleta = aux->pontos_poder;
					}
				aux = aux->prox;
			}
			
			Tfaccao *vencedor = lista;
			while(vencedor){
			if(coleta == vencedor->pontos_poder){
			printf("\nFaccao: %s Venceu", vencedor->nome);
			}
			vencedor = vencedor->prox;
			}
		}
			
			Tunidade *aux_uni;
			while(lista->proxunidade){
				aux_uni = lista->proxunidade->prox;
				free(lista->proxunidade);
				lista->proxunidade = aux_uni;
			}
			
				Tedificio *aux_edi;
			while(lista->proxedificio){
				aux_edi = lista->proxedificio->prox;
				free(lista->proxedificio);
				lista->proxedificio = aux_edi;
			}
			
					
	 desaloca_mapa(&mapa); 
	 
	 	Tfaccao *aux_fac;
			while(lista){
			aux_fac = lista->prox;
			free(lista->prox);
			lista = aux_fac;
		}
	

	if(mapa == NULL && lista == NULL)
			printf("\nDesalocou");
		fclose(arq);
			return 0;
}
//Alocar mapa;
Tmapa *aloca(int i, int j){
   	Tmapa *novo = (Tmapa *)malloc(sizeof(Tmapa));
	if(novo == NULL){
		printf("\nNao alocou");
		return NULL;
	}
	novo->i = i;
	novo->j = j;
	
	novo->matriz = (int **)malloc(i *sizeof(int *));
	if(novo->matriz == NULL){
		printf("\nNao alocou");
			return NULL;
	}
	int linha, coluna;	
	for(linha = 0; linha < i; linha++){
		novo->matriz[linha] = (int *)malloc(j * sizeof(int));
	}	
			return novo;
}

//Preencher o mapa com numero;
void cria_mapa(Tmapa *mapa){
	
		srand(time(NULL));
		int linha, coluna, op;
		
		for(linha = 0; linha < mapa->i; linha++)
			for(coluna = 0; coluna < mapa->j; coluna++){
				op = rand() % 3 + 1;
				mapa->matriz[linha][coluna] = op;
			}
}


//Converter os numeros em letras e imprimir;
void imprime_mapa(Tmapa *mapa){
		int linha, coluna;
		for(linha = 0; linha < mapa->i; linha++){
			for(coluna = 0; coluna < mapa->j; coluna++){
				
				switch(mapa->matriz[linha][coluna]){
					case 1:
						printf("P ");
						break;
					case 2:
						printf("M ");
						break;
					case 3:
						printf("F ");
						break;			
				}
			}
			printf("\n");
		}
}


//Alocar unidade;
Tunidade *alocar_unidade(const char *nome, int i, int j, int tipo){
	Tunidade *novo = malloc(sizeof(Tunidade));	
		if(novo){
			snprintf(novo->nome, sizeof(novo->nome), "%s", nome);
			novo->i = i;
			novo->j = j;
			novo->tipo = tipo;
			novo->prox = NULL;
		}else{
			printf("\nNao alocou");
		}
	
	return novo;		
}

//Alocar edificio;
Tedificio *alocar_edificio(int i, int j, int tipo){
	Tedificio *novo = malloc(sizeof(Tedificio));
		if(novo){
			novo->i = i;
			novo->j = j;
			novo->tipo = tipo;
			novo->prox = NULL;
		}else{
			printf("\nNao alocou");
		}
		return novo;		
}


//Alocar facção;
Tfaccao *aloca_faccao(char *nome, int pontos_recurso, int pontos_poder){
	Tfaccao *novo = malloc(sizeof(Tfaccao));
			if(novo){
				strcpy(novo->nome, nome);
				novo->pontos_poder = pontos_poder;
				novo->pontos_recurso = pontos_recurso;
				novo->prox = NULL;
				novo->proxunidade = NULL;
				novo->proxedificio = NULL;
				novo->proxalianca = NULL;
			}else
				printf("\nNao alocou");
				
			return novo;
}

//Adicionar faccao no fim;
void adicionar_faccao(Tfaccao **lista, Tfaccao *faccao){
		if (faccao == NULL)
        printf("\nNao alocou");
        
    if (*lista == NULL) 
        *lista = faccao;
    	 else {
        Tfaccao *paux = *lista;
        while (paux->prox != NULL) 
            paux = paux->prox;
        
        paux->prox = faccao;
    }
}

//Adicionar dentro da facção no fim;	
void adicionar_unidade(Tfaccao *faccao, Tunidade *unidade){
			if(!faccao){
			printf("\nNao alocou");
				return;	
			}
			
			if(!faccao->proxunidade)
				faccao->proxunidade = unidade;
				else{
					Tunidade *paux = faccao->proxunidade;
					while(paux->prox)
					paux = paux->prox;
					
					paux->prox = unidade;
				
		}			
	}
void adicio_edificio(Tfaccao *faccao, Tedificio *edificio){
		if(!faccao || !edificio){
		printf("\nNao alocou");
			return;	
	}
	
			if(!faccao->proxedificio)
	 		faccao->proxedificio = edificio;
	 		else{
	 		Tedificio *paux = faccao->proxedificio;
	 		while(paux->prox)
	 			paux =paux->prox;
	 			
	 			
	 		paux->prox = edificio;	
	 }
}

//Formar aliança
void formar_alianca(Tfaccao *lista, char *s1, char *s2){
   
    Tfaccao *novo = lista;
    while(novo){
    if(strcmp(novo->nome, s1) == 0){
		Talianca *novo_ali = (Talianca *)malloc(sizeof(Talianca));
		if(!novo_ali){
			printf("\nNao alocou");
			}
			strcpy(novo_ali->nome, s2);
			novo_ali->prox = NULL;	
				
		if(!novo->proxalianca){
			novo->proxalianca = novo_ali;
		}
		
		printf("\nFaccaoo %s agora esta aliada com: %s\n", novo->nome, novo_ali->nome);
		return;
		}
	novo = novo->prox;
	}
}
		

//Desalocar
void desaloca_mapa(Tmapa **mapa) {
    if (*mapa == NULL)
        return;
        
    int linha;
    for (linha = 0; linha < (*mapa)->i; linha++) {
        free((*mapa)->matriz[linha]);
    }
    free((*mapa)->matriz);
    free(*mapa);
    *mapa = NULL; 
}
//Funções para dar condição ao switch;
void combate(Tfaccao *lista, char *nome1, char *nome2)
{
		if(lista){
			if(lista->nome[1] == nome1[0]){				
			lista->pontos_poder += 2;
			printf("\nFaccao: %s Pontos de poder: %d",lista->nome, lista->pontos_poder);		
			}

			lista = lista->prox;
		}
		
}

void constroi(Tfaccao *lista, int tipo){
		
		if(lista){
			switch(tipo){
				case 1:{
					if(lista->pontos_recurso >= 3){
						lista->pontos_recurso -= 3;
					
					}else{
						printf("\nPontos de recurso insuficiente");
					}break;
				
				case 2:{
					if(lista->pontos_recurso >= 4){
						lista->pontos_recurso -=4;
					}else{
						printf("\nPontos de recurso insuficiente");
					}	
				}break;
				
				case 3:{
					if(lista->pontos_recurso >= 5){
						lista->pontos_recurso -= 5;
					}else{
						printf("\nPontos de recurso insuficiente");
					}	
				}break;		
				
			}
			
			lista = lista->prox;
		}
	}
}

void ataca(Tfaccao *lista1, Tfaccao *lista2){
			
			if(lista1->pontos_poder > lista2->pontos_poder){
					lista1->pontos_poder += 5;
					printf("\n%s Ganhou 5", lista1->nome);
					printf("\nFaccao: %s Tem %d pontos de poder", lista1->nome, lista1->pontos_poder);
					
			}else{
					lista2->pontos_poder +=5;
					printf("\n%s Ganhou 5", lista1->nome);
					printf("\nFaccao: %s Tem %d pontos de poder", lista2->nome, lista2->pontos_poder);
			}	
}
/*
//Função para atualizar o mapa;
void mapa_atualizado(Tmapa *mapa, Tfaccao *lista){
		cria_mapa(mapa);
		
		Tfaccao *faccao = lista;
		while(faccao){
			Tunidade *unidade_atual = faccao->proxunidade;
		while(unidade_atual){
				mapa->matriz[unidade_atual->i][unidade_atual->j] = unidade_atual->nome[1]; 
				unidade_atual = unidade_atual->prox;
		}	
		
			Tedificio *edificio_atual = faccao->proxedificio;
			while(edificio_atual){
					mapa->matriz[edificio_atual->i][edificio_atual->j] = edificio_atual->tipo;
					edificio_atual = edificio_atual->prox;
			}
		
				faccao = faccao->prox;	
		}
	
}	
	
void imprime_atualizado(Tmapa *mapa){
	int linha, coluna;
	for(linha = 0; linha < mapa->i; linha++){
			for(coluna = 0; coluna < mapa->j; coluna++){
					if(mapa->matriz[linha][coluna] >= 'A' && mapa->matriz[linha][coluna] <= 'Z'){
						printf("%s", mapa->matriz[linha][coluna]);
					}else{
							switch(mapa->matriz[linha][coluna]){
								
							case 1:{
									
									printf("P ");
								}break;
								
								
								case 2:{
									printf("M ");
									
								}break;
								
								case 3:{
									
									printf("F ");
								}break;

								
								default:{
								printf("U ");
								}break;									
							}
					}
			}
		printf("\n");
	}
	
}	
*/
