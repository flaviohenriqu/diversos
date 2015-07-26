//Implementa��o 01
//Data da entrega: Segunda Feira 28 de Mar�o - em Laboratorio - em horario de aula.
//                 Deve executar no computador
//Objetivo: Implementar a "Estrutura de Dados Lista Encadeada"
//          a partir da especifica��o definida (Classes, dados-membro, fun��es-membro).
//Observa��es:
//           - fazer o teste da sua implementa��o
//           - N�o mudar nenhuma defini��o de par�metros de E/S nem nome
//             de fun��es-membro ou dado-membro
//           - foram deixadas duas fun��es-membro j� implementadas:
//             "~ListaEncadeada()" e "bool remover(int chave)" 
//             estudar o funcionamento destas duas fun��es-embro.
// BOM TRABALHO DE IMPLEMENTA��O !

//ListaEncadeada.cpp
//Demostra��o de uma lista encadeada


/* Altera��es :
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
      No<TipodDado>* pSeguinte;              //ponteiro ao seguinte n� na lista
//-------------------------------------------------------------                                  
   No(int id, TipodDado dd) : iDado(id), dDado(dd), pSeguinte(NULL) //construtor
      {  }                           
//-------------------------------------------------------------
   void mostrarNo()               //mostra na tela o n� {11, 7.66}
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
