/**
* Algoritmo 2012-2 
* QuickSort
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
*
*/
void imprimirArquivoSaida(int v[]){
	int k;
	for(k=0;k<TAMANHO;k++)
		fprintf(fpOut, "%i ", v[k]);
	fprintf(fpOut, "\n");
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
* mediana3 - método utilizado para o calculo da Mediana de 3
*
* Parâmetros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posição inicial da ordenação
* int fim : posição final da ordenação
*/
void mediana3(int v[],  int inicio, int fim){
	
	int num = fim - inicio + 1;
	
	int x = v[(num/4)+inicio];
	int y = v[(num/2)+inicio];
	int z = v[((3*num)/4)+inicio];
	
	if((y <= x && y >= z) || (y >= x && y <= z))
		swap(&v[(num/2)+inicio], &v[fim]); 
	else if((x <= y && x >= z) || (x >= y && x <= z))
		swap(&v[(num/4)+inicio], &v[fim]);			
	else
		swap(&v[((3*num)/4)+inicio], &v[fim]);	
}

/**
* Particionar
*
* Parâmetros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posição inicial da ordenação
* int fim : posição final da ordenação
*/
int particionar(int V[], int inicio, int fim) {	
	mediana3(V,inicio,fim);
	
	int pivo = V[fim];
	int i = inicio - 1, j;
	for(j = inicio; j < fim; j++) {
		if(V[j] >= pivo) {
			i++;
			swap(&V[i], &V[j]);
		}
	}
	swap(&V[i + 1], &V[fim]);
	return i + 1;
}

/**
* QuickSort
* 
* Parâmetros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posição inicial da ordenação
* int fim : posição final da ordenação
*/
void quicksort(int v[],int inicio,int fim) {
	int q;
	if (inicio < fim) {
		q = particionar(v,inicio,fim);
		
		imprimirArquivoSaida(v); //Função utilizada para impressão dos dados de saída no arquivo de saída
		
		quicksort(v,inicio,q-1);
		quicksort(v,q+1,fim);
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
	
	//Método de ordenação - QuickSort(Vetor, Posição Inicial, Posição Final);
	quicksort(vet,0,num_elements-1);

/*	int iter;	
	for(iter = 0;iter < num_elements;iter++){
		printf("%d ",vet[iter]);
    }		*/
	
	//desalocar vetor
	free(vet);	
	//Fechando os arquivos de entrada e saída	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
