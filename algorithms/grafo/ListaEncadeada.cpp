/* Deivid Goes Farias Marinho
   11110547 */

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
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////
class No
   {
   public:
      int iDado;                  //identificador do dado
      double dDado;               //Dado
      No* pSeguinte;              //ponteiro ao seguinte n� na lista
      No* pAnterior;              //ponteiro ao anterior n� na lista
//-------------------------------------------------------------                                  
   No(int id, double dd) : iDado(id), dDado(dd), pSeguinte(NULL), pAnterior(NULL) //construtor
      {  }                           
//-------------------------------------------------------------
   void mostrarNo()               //mostra na tela o n� {11, 7.66}
      {
        cout << iDado << ",  " << dDado << "     " << endl;
      }
//-------------------------------------------------------------
   };  //fim da classe No
////////////////////////////////////////////////////////////////
class ListaEncadeada 
   {
   private:
      No* pPrimeiro;                       // ponteiro ao primeiro n� da lista
      No* pUltimo;                          // ponteiro ao �ltimo n� da lista
   public:
//-------------------------------------------------------------
   ListaEncadeada() : pPrimeiro(NULL), pUltimo(NULL)      // construtor
      { }                                  // nenhum n� na lista
//-------------------------------------------------------------
   ~ListaEncadeada()                       //destrutor (vamos apagar os objetos)
      {
      No* pAtual = pPrimeiro;              //Iniciar com o 1ro elemento
      while(pAtual != NULL)                //At� o final da lista,
         {
         No* pAntigoAtual = pAtual;        //armazenar o ponteiro atual
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
   void inserePrimeiro(int id, double dd)
      {  
         No* novoNo = new No(id, dd);              // criar novo n� 
         novoNo->pSeguinte = pPrimeiro;            // novoNo-->antigo primeiro
         
         if(pUltimo == NULL)
           pUltimo = novoNo;                 
          
         if(pPrimeiro != NULL)
           pPrimeiro->pAnterior = novoNo;          // anterior do antigo primeiro passa a ser o novo no
                               
         pPrimeiro = novoNo;                       // primeiro-->novoNo
                                           
      }
//-------------------------------------------------------------
   No* buscar(int chave)                                            //buscar o n� com a chave desejada
      {                                                             //(assume-se que a lista n�o est� vazia)
         No* buscaNo = pPrimeiro;                                   //Inic�a com o 'primeiro' 
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
  /*    No* pAtual = pPrimeiro;             //busca desde o 1ro elemento
      No* pPrevio = pPrimeiro;
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
      if(pAtual == pPrimeiro){             //Se � o primeiro ponteiro,
         pPrimeiro = pPrimeiro->pSeguinte;//trocar o primeiro
         pPrimeiro->pAnterior = pUltimo;
      }else{                                   //caso contrario,
         pPrevio->pSeguinte = pAtual->pSeguinte; //recolocar ponteiro ao pr�ximo obj
      }
      delete pAtual;                      //apagar n�
      return true;                        //remo��o com sucesso */
      
      No* noBuscado = buscar(chave);
      if(noBuscado == NULL)
        return false;
        
      if(noBuscado == pPrimeiro){
        removerPrimeiro();
        return true;
      }
      
      if(noBuscado == pUltimo){
        removerUltimo();
        return true;
      }
      
      removerDoMeio(noBuscado);
      return true;      
      }
      
//-------------------------------------------------------------
   No* pegarPrimeiro()                    //retorna o primeiro n�
      { return pPrimeiro; }
//-------------------------------------------------------------
    No* pegarUltimo()                    //retorna o primeiro n�
      { return pUltimo; }
//-------------------------------------------------------------
   
   void removerPrimeiro()                       //apagar primeiro n�
      {                                         
          if(!estaVazio()){                     //( a priori a lista n�o esta vazia)
             No* novoPrimeiro = pPrimeiro;      //guarda o endere�o do primeiro
             pPrimeiro = pPrimeiro->pSeguinte;  //quebra o la�o: primeiro-->antigo seguinte
             pPrimeiro->pAnterior = NULL;
             delete novoPrimeiro;               //apaga o antigo n� primeiro com 'delete'
          }
      }
      
//-------------------------------------------------------------
   
   void removerUltimo()                       //apagar primeiro n�
      {                                         
          if(!estaVazio()){                     //( a priori a lista n�o esta vazia)
             if(pUltimo == pPrimeiro)
               removerPrimeiro();
             else{  
               No* pAux = pUltimo;
               pUltimo = pUltimo->pAnterior;
               pUltimo->pSeguinte = NULL;
               delete pAux;               //apaga o antigo n� ultimo com 'delete'
             }
          }
      }      
//-------------------------------------------------------------
   void mostrarLista()
      {
         No* noAtual = pPrimeiro;         //Iniciar no primeiro n� da lista
         if(noAtual != NULL){
             do{          //at� o final da lista,
               noAtual->mostrarNo();          //imprimir dado
               noAtual = noAtual->pSeguinte;  //mover-se ao pr�ximo n�     
             }while(noAtual != pUltimo); 
             
             if(pPrimeiro != pUltimo)
               noAtual->mostrarNo(); 
                                           
             cout << "" << endl;
         }
      }
//-------------------------------------------------------------

// complementar

   void removerDoMeio(No* noTemp){ // remove um elemento do meio da lista
      No* noAux1 = noTemp;
      No* noAux2 = noTemp->pAnterior;
      noTemp = noTemp->pSeguinte;
      noTemp->pAnterior = noAux2;
      noAux2->pSeguinte = noTemp;
      delete noAux1;     
   }
//-------------------------------------------------------------   
   };  //fim da classe ListaEncadeada
   
   
   
   
   
   
   
   
   
   
   
   
   // fun��es complementares
   void menu(){
       cout << "      MENU      " << endl;
       cout << " 1 - Insere Primeiro " << endl;  
       cout << " 2 - Buscar " << endl;
       cout << " 3 - Remover " << endl;
       cout << " 4 - Mostrar Lista " << endl;
       cout << "  " << endl;
       cout << " 0 - Encerrar " << endl;
       cout << "  " << endl;
       cout << " Entre com a opcao: " << endl;
   }
   
   void menuInserePrimeiro(ListaEncadeada* Lista){
       int id;
       double dd; 
       cout << " Entre com o id :";  
       cin >> id; 
       cout << endl;
       cout << " Entre com o dd : ";
       cin >> dd;
       cout << endl;
       
       if(Lista->buscar(id) != NULL)
         cout << "ID ja existe na lista!" << endl;
       else{  
         Lista->inserePrimeiro(id, dd);
         cout << "Inserido com sucesso" << endl;
       }
   }     
   
   void menuBuscar(ListaEncadeada* Lista){
       int id;
       cout << " Entre com o id a ser buscado " << endl;  
       cin >> id;
       
       if(Lista->buscar(id) != NULL)
         cout << "ID existe na lista" << endl;
       else
         cout << "ID nao consta na lista" << endl;
   }  
   
    void menuRemover(ListaEncadeada* Lista){
       int id;
       cout << " Entre com o id a ser removido " << endl;  
       cin >> id;
       
       if(Lista->remover(id))
         cout << "Removido com sucesso!" << endl;
       else
         cout << "ID nao consta na lista" << endl;
   }  
   
   
   
////////////////////////////////////////////////////////////////
int main()
   {
   ListaEncadeada Lista1;                   //instanciar um objeto
   char opcao = '1';
   
   while(opcao != '0'){
     menu();
     cin >> opcao;
     
     system("CLS");
     
     switch(opcao){
       case '1' : menuInserePrimeiro(&Lista1); 
                  break;
       case '2' : menuBuscar(&Lista1);
                  break;
       case '3' : menuRemover(&Lista1);
                  break;
       case '4' : Lista1.mostrarLista();
                  if(!Lista1.estaVazio()){
                      cout << "Primeiro : " << Lista1.pegarPrimeiro()->iDado << "     " << Lista1.pegarPrimeiro()->dDado << endl;
                      cout << "Ultimo : " << Lista1.pegarUltimo()->iDado << "     " << Lista1.pegarUltimo()->dDado << endl;
                  }
                  break;
       case '0' : cout << "O Programa sera finalizado!" << endl;
                  break;
       default : cout << "Opcao invalida!" << endl; 
                 break;                  
     }
     
     cin.get();
     cin.get();

     system("CLS");
            
   }
   
   return 0;
   }  //fim main()
   
   
   
   
   
   
   
