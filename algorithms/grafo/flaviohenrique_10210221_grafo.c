/**
* Algoritmo 2012-2 
* Grafo
* Fl�vio Henrique Andrade dos Santos - 10210221
* 
*
**/
#include <stdio.h>
#include <stdlib.h>

//Variav�is Globais
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
      No<TipoDeLista>* pPrimeiro;                       // ponteiro ao primeiro n� da lista
   public:
//-------------------------------------------------------------
   ListaEncadeada() : pPrimeiro(NULL)      // construtor
      { }                                  // nenhum n� na lista
//-------------------------------------------------------------
   ~ListaEncadeada()                       //destrutor (vamos apagar os objetos)
      {
      No<TipoDeLista>* pAtual = pPrimeiro;              //Iniciar com o 1ro elemento
      while(pAtual != NULL)                //At� o final da lista,
         {
         No<TipoDeLista>* pAntigoAtual = pAtual;        //armazenar o ponteiro atual
         pAtual = pAtual->pSeguinte;       //mover-se ao pr�ximo ponteiro
         delete pAntigoAtual;              //apagar o objeto apontado (pAntigoAtual
         }
      }
      
//-------------------------------------------------------------
   bool estaVazio()                        // verdadeiro se a lista esta vazia
      { 
          return(pPrimeiro == NULL);           
        
      }
//-------------------------------------------------------------
                                           //inserir no in�cio da lista
   void inserePrimeiro(int id, TipoDeLista dd)
      {  
         No<TipoDeLista>* novoNo = new No<TipoDeLista>(id, dd);      //criar novo n� 
         novoNo->pSeguinte = pPrimeiro;    // novoNo-->antigo primeiro
         pPrimeiro = novoNo;               //primeiro-->novoNo
                                           
      }
//-------------------------------------------------------------
   No<TipoDeLista>* buscar(int chave)                               //buscar o n� com a chave desejada
      {                                                             //(assume-se que a lista n�o est� vazia)
         No<TipoDeLista>* buscaNo = pPrimeiro;                      //Inic�a com o 'primeiro' 
                                                                    //enquanto n�o seja igual
         while(buscaNo != NULL && buscaNo->iDado != chave){         //Se est� no final da Lista,
                                                                    //n�o foi encontrado  
           buscaNo = buscaNo->pSeguinte;                            //do contrario n�o esta no final da lista,
                                                                    //ir ao seguinte ponteiro ( do objeto)  
         };                                                             
                                                                      
         return buscaNo;    // retorna NULL se a chave nao for encontrada                                   
      }
//-------------------------------------------------------------
   bool remover(int chave)                //remover um n� atrav�s da chave
      {                                   //( assume-se que a lista n�o est� vazia)
      No<TipoDeLista>* pAtual = pPrimeiro;             //busca desde o 1ro elemento
      No<TipoDeLista>* pPrevio = pPrimeiro;
      while(pAtual->iDado != chave)
         {
         if(pAtual->pSeguinte == NULL)
            return false;                 //n�o foi encontrado
         else
            {
            pPrevio = pAtual;            //ir ao seguinte ponteiro
            pAtual  = pAtual->pSeguinte;
            }
         }                                //Encontrado
      if(pAtual == pPrimeiro)             //Se � o primeiro ponteiro,
         pPrimeiro = pPrimeiro->pSeguinte;//trocar o primeiro
      else                                   //caso contrario,
         pPrevio->pSeguinte = pAtual->pSeguinte; //recolocar ponteiro ao pr�ximo obj
      delete pAtual;                      //apagar n�
      return true;                        //remo��o com sucesso
      }
      
//-------------------------------------------------------------
   No<TipoDeLista>* pegarPrimeiro()                    //retorna o primeiro n�
      { return pPrimeiro; }
//-------------------------------------------------------------
  void removerPrimeiro()                       //apagar primeiro n�
      {                                         
          if(!estaVazio()){                     //( a priori a lista n�o esta vazia)
             No<TipoDeLista>* novoPrimeiro = pPrimeiro;      //guarda o endere�o do primeiro
             pPrimeiro = pPrimeiro->pSeguinte;  //quebra o la�o: primeiro-->antigo seguinte
             delete novoPrimeiro;               //apaga o antigo n� primeiro com 'delete'
          }
      }
//-------------------------------------------------------------
   void mostrarLista()
      {
         No<TipoDeLista>* noAtual = pPrimeiro;         //Iniciar no primeiro n� da lista
         while(noAtual != NULL){          //at� o final da lista,
           noAtual->mostrarNo();          //imprimir dado
           noAtual = noAtual->pSeguinte;  //mover-se ao pr�ximo n�     
         }                               
         cout << "" << endl;
      }
//-------------------------------------------------------------
   };  //fim da classe ListaEncadeada
   
   
////////////////////////////////////////////////////////////////





/**
* Fun��o Principal
* Responsav�l pela inser��o dos arquivos de entrada e sa�da, execu��o do m�todo de ordena��o do problema.
* Par�metros
* int argc : conta quantos parametros foram passados para a execu��o do programa
* char *argv : sequ�ncia de strings que ser�o os argumentos do programa
*/
int main(int argc, char* argv[])
{
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
	


	// preenchendo o vetor com os elementos informados no arquivo de entrada
	int k = 0;
	while (!feof (fpIn)){  
      fscanf (fpIn, "%i", &num);      
      vet[k] = num;
	  k++;
    }
	


	
	//Fechando os arquivos de entrada e sa�da	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}