/**
* Algoritmo 2012-2 
* Grafo
* Flávio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>

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
template<class TipodDado>
class No
   {
   public:
      int iDado;            
      TipodDado dDado;
      No<TipodDado>* pSeguinte;

   No(int id, TipodDado dd) : iDado(id), dDado(dd), pSeguinte(NULL)
      {  }                           

   void mostrarNo()
      {
        cout << "{ " << iDado << ",  " << dDado << " }     " << endl;
      }
   };  

template<class TipoDeLista>
class ListaEncadeada 
   {
   private:
      No<TipoDeLista>* pPrimeiro;                       // ponteiro ao primeiro nó da lista
   public:
//-------------------------------------------------------------
   ListaEncadeada() : pPrimeiro(NULL)      // construtor
      { }                                  // nenhum nó na lista
//-------------------------------------------------------------
   ~ListaEncadeada()                       //destrutor (vamos apagar os objetos)
      {
      No<TipoDeLista>* pAtual = pPrimeiro;              //Iniciar com o 1ro elemento
      while(pAtual != NULL)                //Até o final da lista,
         {
         No<TipoDeLista>* pAntigoAtual = pAtual;        //armazenar o ponteiro atual
         pAtual = pAtual->pSeguinte;       //mover-se ao próximo ponteiro
         delete pAntigoAtual;              //apagar o objeto apontado (pAntigoAtual
         }
      }
      
//-------------------------------------------------------------
   bool estaVazio()                        // verdadeiro se a lista esta vazia
      { 
          return(pPrimeiro == NULL);           
        
      }
//-------------------------------------------------------------
                                           //inserir no início da lista
   void inserePrimeiro(int id, TipoDeLista dd)
      {  
         No<TipoDeLista>* novoNo = new No<TipoDeLista>(id, dd);      //criar novo nó 
         novoNo->pSeguinte = pPrimeiro;    // novoNo-->antigo primeiro
         pPrimeiro = novoNo;               //primeiro-->novoNo
                                           
      }
//-------------------------------------------------------------
   No<TipoDeLista>* buscar(int chave)                               //buscar o nó com a chave desejada
      {                                                             //(assume-se que a lista não está vazia)
         No<TipoDeLista>* buscaNo = pPrimeiro;                      //Inicía com o 'primeiro' 
                                                                    //enquanto não seja igual
         while(buscaNo != NULL && buscaNo->iDado != chave){         //Se está no final da Lista,
                                                                    //não foi encontrado  
           buscaNo = buscaNo->pSeguinte;                            //do contrario não esta no final da lista,
                                                                    //ir ao seguinte ponteiro ( do objeto)  
         };                                                             
                                                                      
         return buscaNo;    // retorna NULL se a chave nao for encontrada                                   
      }
//-------------------------------------------------------------
   bool remover(int chave)                //remover um nó através da chave
      {                                   //( assume-se que a lista não está vazia)
      No<TipoDeLista>* pAtual = pPrimeiro;             //busca desde o 1ro elemento
      No<TipoDeLista>* pPrevio = pPrimeiro;
      while(pAtual->iDado != chave)
         {
         if(pAtual->pSeguinte == NULL)
            return false;                 //não foi encontrado
         else
            {
            pPrevio = pAtual;            //ir ao seguinte ponteiro
            pAtual  = pAtual->pSeguinte;
            }
         }                                //Encontrado
      if(pAtual == pPrimeiro)             //Se é o primeiro ponteiro,
         pPrimeiro = pPrimeiro->pSeguinte;//trocar o primeiro
      else                                   //caso contrario,
         pPrevio->pSeguinte = pAtual->pSeguinte; //recolocar ponteiro ao próximo obj
      delete pAtual;                      //apagar nó
      return true;                        //remoção com sucesso
      }
      
//-------------------------------------------------------------
   No<TipoDeLista>* pegarPrimeiro()                    //retorna o primeiro nó
      { return pPrimeiro; }
//-------------------------------------------------------------
  void removerPrimeiro()                       //apagar primeiro nó
      {                                         
          if(!estaVazio()){                     //( a priori a lista não esta vazia)
             No<TipoDeLista>* novoPrimeiro = pPrimeiro;      //guarda o endereço do primeiro
             pPrimeiro = pPrimeiro->pSeguinte;  //quebra o laço: primeiro-->antigo seguinte
             delete novoPrimeiro;               //apaga o antigo nó primeiro com 'delete'
          }
      }
//-------------------------------------------------------------
   void mostrarLista()
      {
         No<TipoDeLista>* noAtual = pPrimeiro;         //Iniciar no primeiro nó da lista
         while(noAtual != NULL){          //até o final da lista,
           noAtual->mostrarNo();          //imprimir dado
           noAtual = noAtual->pSeguinte;  //mover-se ao próximo nó     
         }                               
         cout << "" << endl;
      }
//-------------------------------------------------------------
   };  //fim da classe ListaEncadeada
   
   
////////////////////////////////////////////////////////////////





/**
* Função Principal
* Responsavél pela inserção dos arquivos de entrada e saída, execução do método de ordenação do problema.
* Parâmetros
* int argc : conta quantos parametros foram passados para a execução do programa
* char *argv : sequência de strings que serão os argumentos do programa
*/
int main(int argc, char* argv[])
{
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
	


	// preenchendo o vetor com os elementos informados no arquivo de entrada
	int k = 0;
	while (!feof (fpIn)){  
      fscanf (fpIn, "%i", &num);      
      vet[k] = num;
	  k++;
    }
	


	
	//Fechando os arquivos de entrada e saída	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}