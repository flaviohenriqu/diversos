/**
* Algoritmo 2012-2 
* HeapSort
* Flávio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>

//Variavéis Globais
FILE *fpIn, *fpOut;
int TAMANHO;



/**
* ImprimirArquivoSaida - Imprimir no arquivo de saída 
*
* Parâmetros
* int v: vetor com os elemetos de entrada
* int n: número de elementos
*
*/
void imprimirArquivoSaida(int v[], int n){
	int k;
	for(k=0;k<n;k++)
		fprintf(fpOut, "%i ", v[k]);
	fprintf(fpOut, "\n");
}

/**
* Função Pai
*
*/
int Pai(int i){
	return (i-1)/2;
}

/**
* Filho Direito do nó
*
*/
int Direito(int i){
	return 2*i + 2;
}

/**
* Filho Esquerdo do nó
*
*/
int Esquerdo(int i){
	return 2*i + 1;
}

/**
* SWAP - Trocar
*
* Parâmetros
* int *v1 : valor que irá para a posição da variável *v2
* int *v2 
*
*/
void swap(int *v1, int *v2) {
	int tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
	return ;
}

/**
* Heapfy 
* Responsável pela construção da HEAP
*
*/
void heapify(int V[], int i, int n) {
	unsigned int P = i;
	unsigned int E = Esquerdo(i);
	unsigned int D = Direito(i);
	if(E < n && V[E] < V[P]) P = E;
	if(D < n && V[D] < V[P]) P = D;
	if(P != i) {
		swap(&V[P], &V[i]);
		heapify(V, P, n);
	}
}

/**
* Construir HEAP utiliza a função do Heapfy na construção da HEAP
*
*/
void construir_heap(int v[], int n)
{
	int p = Pai(n-1);

	while(p >= 0){
		heapify(v,p,n);
		p--;
	}
}



/**
* HeapSort
* 
* Parâmetros
* int *v : vetor contendo os elementos a serem ordenados
* int n : número de elementos
*/
void heapsort(int V[], int n) {
	construir_heap(V, n);
	int i;	
	imprimirArquivoSaida(V,n);
	
	for(i = n - 1; i > 0; i--){
		swap(&V[0], &V[i]);
		heapify(V, 0, i);
		imprimirArquivoSaida(V,n);	
	}
}

/**
* Função Principal
* Responsavél pela inserção dos arquivos de entrada e saída, execução do método de ordenação do problema.
* Parâmetros
* int argc : conta quantos parametros foram passados para a execução do programa
* char *argv : sequência de strings que serão os argumentos do programa
*/
int main(int argc, char* argv[])
{
	//vetor de elementos
	int *vet;

	// Checando se os arquivos de entrada e saída foram passados correntamente 
	if(argc!=3){
		printf("Voce deve informa os arquivos de entrada e saida!\n");
		printf("na linha de comando. Tente novamente\n");
		return 1;
	}
	
	//abrindo o arquivo de entrada no modo de leitura
	if((fpIn=fopen(argv[1],"r"))==NULL){
		printf("O arquivo de ENTRADA nao pode ser aberto.\n");
		return 1;
	}

	//abrindo o arquivo de saída no modo de escrita
	if((fpOut=fopen(argv[2],"w"))==NULL){
		printf("O arquivo de SAIDA nao pode ser aberto.\n");
		return 1;
	}
		
	int num,num_elements;
	fscanf(fpIn, "%i",&num_elements); // primeiro valor corresponde ao numero total de elementos do vetor
	//int vet[num_elements];
	vet = (int*) malloc(num_elements * sizeof(int));
	TAMANHO = num_elements;
	
	// preenchendo o vetor com os elementos informados no arquivo de entrada
	int k = 0;
	while (!feof (fpIn)){  
      fscanf (fpIn, "%i", &num);      
      vet[k] = num;
	  k++;
    }
	
/*	int iter;	
	for(iter = 0;iter < num_elements;iter++){
		printf("%d ",vet[iter]);
    }		*/
	//Método de ordenação - HeapSort(Vetor, Número de Elementos);
	heapsort(vet,num_elements);
	
	//desalocar vetor
	free(vet);
	//Fechando os arquivos de entrada e saída	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}