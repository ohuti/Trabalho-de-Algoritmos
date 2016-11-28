#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaracao do TAD TPonto
typedef struct{
    int x, y;
}TPonto;

// declaracao do TAD TListaPonto
typedef struct{
    TPonto*elementos; // vetor de pontos
    int maximo; // quantidade maxima de pontos no vetor de pontos
    int qtdAtual; // quantidade atual de pontos no vetor de pontos
}TListaPonto;

// declação do TAD TCalcDist
typedef struct{
    TPonto*resposta; // vetor resposta
    int qtdAtual; // quantidade maxima de pontos no vetor resposta
    int maximo; // quantidade atual de pontos no vetor resposta
}TCalcDist;

// declaracao de funcoes
TListaPonto *Init( int N );
TCalcDist *CInit(int K);
void Desaloca( TListaPonto*lista, TCalcDist*listaR);
void insereFinal( TListaPonto*lista, TPonto p);
void inserePonto(TListaPonto*lista, TPonto p, int x);
void removePonto(TListaPonto*lista, int x);
void imprimeListaPontos( TListaPonto *lista );
void distPonto(TListaPonto*lista, TCalcDist*listaR, TPonto p, int K);


int main(){
    // declarando Lista de Pontos;
    TListaPonto *lista;
    TCalcDist *listaR;
    char opc;

    lista = Init( 1000 ); //cria um vetor de pontos com 1000 posicoes


    // faz o menu de opcoes
    do{
        printf("1 - adicionar no final\n"
               "2 - adicionar em uma dada posicao\n"
               "3 - remover ponto em uma dada posicao\n"
               "4 - mostrar quantidade de pontos armazenados\n"
               "5 - calcular k pontos mais proximos ao ponto dado\n"
               "6 - sair\n");
        scanf("%s", &opc);

        if( opc == '1'){ //adicionar no final
            TPonto p;
            printf("digite os valores de x,y (separados por virgula):");
            scanf("%d,%d",&p.x,&p.y);
            printf("\nlista de pontos:");
            insereFinal(lista,p);
        }
        if(opc == '2'){
        	TPonto p;
        	int x;
        	printf("digite os valores de x,y (separados por virgula):");
        	scanf("%d,%d",&p.x,&p.y);
        	printf("digite a posicao que esse ponto deve ser guardado:");
        	scanf("%d",&x);
        	inserePonto(lista, p, x);
        }
        if(opc == '3'){
        	TPonto p;
        	int x;
        	printf("digite a posicao que deseja remover o ponto:");
        	scanf("%d", &x);
        	removePonto(lista, x);
        }
        if(opc == '4'){
        	printf("\nPontos armazenados no vetor: %d\n", lista->qtdAtual);
        }
        if(opc == '5'){
            TPonto p;
            int K;
            printf("digite o ponto referencia para o calculo:");
            scanf("%d,%d",&p.x, &p.y);
            printf("digite quantidade de pontos que serao comparados com o ponto referencia:");
            scanf("%d", &K);
            listaR = CInit( K ); //cria o vetor para armazenar respostas
            distPonto(lista, listaR, p, K);
        }
        imprimeListaPontos( lista );
    }while (opc != '6');

    printf("\nfim do programa\n");
    // libera a lista de pontos

    Desaloca(lista, listaR);

}
// Função cria e devolve uma nova estrutura TListaPontos, inicializa os atributos da estrutura.
TListaPonto *Init( int N ){

    TListaPonto *lista;

    lista = (TListaPonto*) calloc(1,sizeof(TListaPonto));
    lista->qtdAtual = 0;
    lista->maximo   = N;

    // aloca um vetor de pontos
    lista->elementos = (TPonto*) calloc(N,sizeof(TPonto));

    return lista;
}

// Função cria lista para vetor resposta do calculo de distância.
TCalcDist *CInit(int K){

    TCalcDist*listaR;

    listaR = (TCalcDist*) calloc(1,sizeof(TCalcDist));
    listaR->qtdAtual = 0;
    listaR->maximo = K;

    // aloca um vetor para armazenar pontos mais próximos do ponto referência
    listaR->resposta = (TPonto*) calloc(K,sizeof(TPonto));

    return listaR;
}

// Função desaloca a memoria utilizada por *listaPontos
void Desaloca( TListaPonto *lista, TCalcDist*listaR){
    // libera o vetor
    free(lista->elementos);
    // libera o vetor resposta
    free(listaR->resposta);
    // libera a estrutura
    free(lista);
    //libera estrutura resposta
    free(listaR);
}

// insere um ponto no final da lista de pontos
void insereFinal( TListaPonto *lista, TPonto p){

    if( lista->qtdAtual < lista->maximo){
        lista->elementos[lista->qtdAtual] = p;
        (lista->qtdAtual)++;
    }
    else{
        printf("\nlista lotada\n");

    }

}

// insere ponto no local escolhido pelo usuário REVISAR!!!
void inserePonto(TListaPonto*lista, TPonto p, int x){
	if(lista->qtdAtual < lista->maximo){
		if(x > 1000){
			printf("Impossível inserir ponto na posicao %d\n", x);
		} else if(lista->qtdAtual == 0){
			lista->elementos[x] = p;
			(lista->qtdAtual)++;
		} else if(lista->qtdAtual > 0){
            for(int i = lista->qtdAtual; i >= x; i--){
				lista->elementos[i+1] = lista->elementos[i];			 
            }
            lista->elementos[x] = p;
            (lista->qtdAtual)++;
		}
	}
}

// remove ponto da posição solicitada
void removePonto(TListaPonto*lista, int x){
	if(x == lista->qtdAtual){
		(lista->qtdAtual)--;
	} else {
		for(int i = x+1; i < lista->qtdAtual; i++){
			lista->elementos[i-1] = lista->elementos[i];
		}
		(lista->qtdAtual)--;
	}
}

// imprime a lista de pontos
void imprimeListaPontos( TListaPonto *lista ){
    int i;
    for(i=0;i<lista->qtdAtual;i++)
        printf("(%d,%d) ", lista->elementos[i].x,lista->elementos[i].y);
    printf("\n\n");
}

// calcula distância
void distPonto(TListaPonto*lista, TCalcDist*listaR, TPonto p, int K){
    float distancia = sqrt(pow(p.x-lista->elementos[0].x,2)+pow(p.y-lista->elementos[0].y,2));
    printf("\nponto(s) mai(s) proximo(s): %.2lf", distancia);
}