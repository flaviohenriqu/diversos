/**
* Algoritmo 2012-2 
* Grafo
* Flávio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//Variavéis Globais
FILE *fpIn, *fpOut;

	/**
	* 
	* 
	* 
	* 
	* 
	* 
	*/
	template<class TNo>
	class No{
	public:
		int iDado;
		TNo dDado;
		No<TNo>* pSeguinte;

		No(int id, TNo dd) : iDado(id), dDado(dd), pSeguinte(NULL){  }                  

		void mostrarNo(){
			cout << "{ " << iDado << ",  " << dDado << " }     " << endl;
		}
	};  

   
	/**
	* 
	* 
	* 
	* 
	* 
	* 
	*/
	template<class TLista>
	class ListaEncadeada{
	private:
		No<TLista>* pPrimeiro;
		No<TLista>* pUltimo;
	public:

		ListaEncadeada() : pPrimeiro(NULL), pUltimo(NULL){ }                                  

		~ListaEncadeada(){
			No<TLista>* pAtual = pPrimeiro;   
			while(pAtual != NULL){
				No<TLista>* pAntigoAtual = pAtual;
				pAtual = pAtual->pSeguinte;       
				delete pAntigoAtual;              
			}
		}

		bool estaVazio(){ return(pPrimeiro == NULL);  }

		void inserePrimeiro(int id, TLista dd){  
			No<TLista>* novoNo = new No<TLista>(id, dd);      
			novoNo->pSeguinte = pPrimeiro;   
			pPrimeiro = novoNo;              
		}
	  
		void insereUltimo(int id, TLista dd){
			No<TLista>* novoNo = new No<TLista>(id, dd);
			if((pUltimo == NULL)&&(pPrimeiro == NULL)){
				pUltimo = novoNo;
				pPrimeiro = novoNo;
			}else{
				pUltimo->pSeguinte = novoNo;
				pUltimo = novoNo;
			}
		}

		No<TLista>* buscar(int chave){                                   
			No<TLista>* buscaNo = pPrimeiro;
			while(buscaNo != NULL && buscaNo->iDado != chave){
				buscaNo = buscaNo->pSeguinte;                   
			}                                                             
			return buscaNo;    
		}

		bool remover(int chave){                     
			No<TLista>* pAtual = pPrimeiro;
			No<TLista>* pPrevio = pPrimeiro;
			while(pAtual->iDado != chave){
				if(pAtual->pSeguinte == NULL)
					return false;               
				else{
					pPrevio = pAtual;           
					pAtual  = pAtual->pSeguinte;
				}
			}                              
			if(pAtual == pPrimeiro)           
				pPrimeiro = pPrimeiro->pSeguinte;
			else                                
				pPrevio->pSeguinte = pAtual->pSeguinte;
			delete pAtual;
			return true;                        
		}
      
		No<TLista>* pegarPrimeiro(){ return pPrimeiro; }

		void removerPrimeiro(){                                         
			if(!estaVazio()){
				No<TLista>* novoPrimeiro = pPrimeiro;
				pPrimeiro = pPrimeiro->pSeguinte;
				delete novoPrimeiro;
			}
		}

		void mostrarLista(){
			No<TLista>* noAtual = pPrimeiro;
			while(noAtual != NULL){
				noAtual->mostrarNo();
				noAtual = noAtual->pSeguinte;
			}                               
			cout << "" << endl;
		}
	};
   
   	/**
	* 
	* 
	* 
	* 
	* 
	* 
	*/
   template<class TFila>
   class Fila{
        private:
            ListaEncadeada<TFila>* pLista;     
        public:

		Fila(){ pLista = new ListaEncadeada<TFila>(); }

		~Fila(){ delete pLista; }

		void push(int id, TFila dd){ 
			pLista->insereUltimo(id, dd);             
		}

		No<TFila>* pop(){
			return pLista->removerPrimeiro();                         
		}

		bool estaVazio(){
			return pLista->estaVazio();     
		}

		bool mostrarFila(){
			pLista->mostrarLista();     
		}        
	};   

	/**
	* 
	* 
	* 
	* 
	* 
	* 
	*/	
	template<class TGrafo>
	class Grafo{

	};
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
	ListaEncadeada<int> *vet;

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
		
	int indice,peso,num,num_vertices,num_arestas;
	fscanf(fpIn, "%i",&num_vertices); // primeiro valor corresponde ao numero total de vertices
	
	vet = new ListaEncadeada<int> [num_vertices];
	
	fscanf(fpIn, "%i",&num_arestas); // segundo valor corresponde ao numero total de arestas

	//primeiro indice
	fscanf (fpIn, "%i", &indice);

	// preenchendo o vetor com os elementos informados no arquivo de entrada
	while (!feof (fpIn)){
      fscanf (fpIn, "%i", &peso);
	  if(!peso){
		fscanf (fpIn, "%i", &indice);
	  }else{
		fscanf (fpIn, "%i", &num);
		vet[indice].insereUltimo(num,peso);		
	  }
    }
	
	int j;
	for(j = 0 ; j < num_vertices; j++)
	   vet[j].mostrarLista();
	   
	
	delete [] vet; // free an array
	//Fechando os arquivos de entrada e saída	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
