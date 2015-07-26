//Implementação 01
//Data da entrega: Segunda Feira 28 de Março - em Laboratorio - em horario de aula.
//                 Deve executar no computador
//Objetivo: Implementar a "Estrutura de Dados Lista Encadeada"
//          a partir da especificação definida (Classes, dados-membro, funções-membro).
//Observações:
//           - fazer o teste da sua implementação
//           - Não mudar nenhuma definição de parámetros de E/S nem nome
//             de funções-membro ou dado-membro
//           - foram deixadas duas funções-membro já implementadas:
//             "~ListaEncadeada()" e "bool remover(int chave)" 
//             estudar o funcionamento destas duas funções-embro.
// BOM TRABALHO DE IMPLEMENTAÇÂO !

//ListaEncadeada.cpp
//Demostração de uma lista encadeada


/* Alterações :
    - 14/03/2012 - Template
*/
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////
template<class TipodDado>
class No
   {
   public:
      int iDado;                  //identificador do dado
      TipodDado dDado;               //Dado
      No<TipodDado>* pSeguinte;              //ponteiro ao seguinte nó na lista
//-------------------------------------------------------------                                  
   No(int id, TipodDado dd) : iDado(id), dDado(dd), pSeguinte(NULL) //construtor
      {  }                           
//-------------------------------------------------------------
   void mostrarNo()               //mostra na tela o nó {11, 7.66}
      {
        cout << "{ " << iDado << ",  " << dDado << " }     " << endl;
      }
//-------------------------------------------------------------
   };  //fim da classe No
////////////////////////////////////////////////////////////////


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





int main()
   {
   ListaEncadeada<int>* Lista1 = new ListaEncadeada<int>();                   //instanciar um objeto
   ListaEncadeada<double>* Lista2 = new ListaEncadeada<double>();             //instanciar um objeto
   ListaEncadeada<string>* Lista3 = new ListaEncadeada<string>();             //instanciar um objeto
   
   Lista1->inserePrimeiro(22, 2);         //inserir 4 registros
   Lista1->inserePrimeiro(44, 4);
   Lista1->inserePrimeiro(66, 6);
   Lista1->inserePrimeiro(88, 8);        

   Lista2->inserePrimeiro(22, 2.99);         //inserir 4 registros
   Lista2->inserePrimeiro(44, 4.99);
   Lista2->inserePrimeiro(66, 6.99);
   Lista2->inserePrimeiro(88, 8.99);       
   
   Lista3->inserePrimeiro(22, "Texto 1");         //inserir 4 registros
   Lista3->inserePrimeiro(44, "Texto 2");
   Lista3->inserePrimeiro(66, "Texto 3");
   Lista3->inserePrimeiro(88, "Texto 4");                   

   // faz os testes
   cout << "\nLISTA 1\n" << endl;
   Lista1->mostrarLista();   
   cout << "\nLISTA 2\n" << endl;
   Lista2->mostrarLista();
   cout << "\nLISTA 3\n" << endl;
   Lista3->mostrarLista();
   
   cin.get();
   return 0;
   }  //fim main()
