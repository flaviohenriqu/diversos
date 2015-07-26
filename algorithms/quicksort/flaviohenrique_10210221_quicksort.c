/**
* Algoritmo 2012-2 
* QuickSort
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
* mediana3 - m�todo utilizado para o calculo da Mediana de 3
*
* Par�metros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posi��o inicial da ordena��o
* int fim : posi��o final da ordena��o
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
* Par�metros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posi��o inicial da ordena��o
* int fim : posi��o final da ordena��o
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
* Par�metros
* int *v : vetor contendo os elementos a serem ordenados
* int inicio : posi��o inicial da ordena��o
* int fim : posi��o final da ordena��o
*/
void quicksort(int v[],int inicio,int fim) {
	int q;
	if (inicio < fim) {
		q = particionar(v,inicio,fim);
		
		imprimirArquivoSaida(v); //Fun��o utilizada para impress�o dos dados de sa�da no arquivo de sa�da
		
		quicksort(v,inicio,q-1);
		quicksort(v,q+1,fim);
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
	
	//M�todo de ordena��o - QuickSort(Vetor, Posi��o Inicial, Posi��o Final);
	quicksort(vet,0,num_elements-1);

/*	int iter;	
	for(iter = 0;iter < num_elements;iter++){
		printf("%d ",vet[iter]);
    }		*/
	
	//desalocar vetor
	free(vet);	
	//Fechando os arquivos de entrada e sa�da	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
