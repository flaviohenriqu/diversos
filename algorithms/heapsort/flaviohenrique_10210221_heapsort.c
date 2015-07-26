/**
* Algoritmo 2012-2 
* HeapSort
* Fl�vio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>

//Variav�is Globais
FILE *fpIn, *fpOut;
int TAMANHO;



/**
* ImprimirArquivoSaida - Imprimir no arquivo de sa�da 
*
* Par�metros
* int v: vetor com os elemetos de entrada
* int n: n�mero de elementos
*
*/
void imprimirArquivoSaida(int v[], int n){
	int k;
	for(k=0;k<n;k++)
		fprintf(fpOut, "%i ", v[k]);
	fprintf(fpOut, "\n");
}

/**
* Fun��o Pai
*
*/
int Pai(int i){
	return (i-1)/2;
}

/**
* Filho Direito do n�
*
*/
int Direito(int i){
	return 2*i + 2;
}

/**
* Filho Esquerdo do n�
*
*/
int Esquerdo(int i){
	return 2*i + 1;
}

/**
* SWAP - Trocar
*
* Par�metros
* int *v1 : valor que ir� para a posi��o da vari�vel *v2
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
* Respons�vel pela constru��o da HEAP
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
* Construir HEAP utiliza a fun��o do Heapfy na constru��o da HEAP
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
* Par�metros
* int *v : vetor contendo os elementos a serem ordenados
* int n : n�mero de elementos
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
* Fun��o Principal
* Responsav�l pela inser��o dos arquivos de entrada e sa�da, execu��o do m�todo de ordena��o do problema.
* Par�metros
* int argc : conta quantos parametros foram passados para a execu��o do programa
* char *argv : sequ�ncia de strings que ser�o os argumentos do programa
*/
int main(int argc, char* argv[])
{
	//vetor de elementos
	int *vet;

	// Checando se os arquivos de entrada e sa�da foram passados correntamente 
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

	//abrindo o arquivo de sa�da no modo de escrita
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
	//M�todo de ordena��o - HeapSort(Vetor, N�mero de Elementos);
	heapsort(vet,num_elements);
	
	//desalocar vetor
	free(vet);
	//Fechando os arquivos de entrada e sa�da	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}