/**
* Algoritmo 2012-2 
* MergeSort
* Fl�vio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>

//Variav�is Globais
FILE *fpIn, *fpOut;

/**
* MergeSort
* 
* Par�metros
* int *vec : vetor contendo os elementos a serem ordenados
* int vecSize : tamanho do vetor
* 
*/
void merge(int vec[], int vecSize) {
  int mid;
  int i, j, k;
  int* tmp;
 
  tmp = (int*) malloc(vecSize * sizeof(int));
  if (tmp == NULL) {
    exit(1);
  }
 
  mid = vecSize / 2;
 
  i = 0;
  j = mid;
  k = 0;
  while (i < mid && j < vecSize) {
    if (vec[i] > vec[j]) {
      tmp[k] = vec[i];
      ++i;
    }
    else {
      tmp[k] = vec[j];
      ++j;
    }
    ++k;
  }
 
  if (i == mid) {
    while (j < vecSize) {
      tmp[k] = vec[j];
      ++j;
      ++k;
    }
  }
  else {
    while (i < mid) {
      tmp[k] = vec[i];
      ++i;
      ++k;
    }
  }
 // copia vetor intercalado para o vetor original
	for (i = 0; i < vecSize; ++i) {
		vec[i] = tmp[i];
		fprintf(fpOut, "%i ", vec[i]);
	}
	fprintf(fpOut, "\n");
 
  free(tmp);
}
 
void mergeSort(int vec[], int vecSize) {
  int mid;
 
  if (vecSize > 1) {
    // ordenacao recursiva das duas metades              
    mid = vecSize / 2;
    mergeSort(vec, mid);
    mergeSort(vec + mid, vecSize - mid);
    merge(vec, vecSize);
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
	
	// preenchendo o vetor com os elementos informados no arquivo de entrada
	int k = 0;
	while (!feof (fpIn)){  
      fscanf (fpIn, "%i", &num);      
      vet[k] = num;
	  k++;
    }
	
	//M�todo de ordena��o - MergeSort(Vetor, Tamanho do Vetor a ser ordenado);
	mergeSort(vet,num_elements);
		
	//desalocar vetor
	free(vet);
	//Fechando os arquivos de entrada e sa�da	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
