/* Deivid Goes Farias Marinho
   11110547 */

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
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////
class No
   {
   public:
      int iDado;                  //identificador do dado
      double dDado;               //Dado
      No* pSeguinte;              //ponteiro ao seguinte nó na lista
      No* pAnterior;              //ponteiro ao anterior nó na lista
//-------------------------------------------------------------                                  
   No(int id, double dd) : iDado(id), dDado(dd), pSeguinte(NULL), pAnterior(NULL) //construtor
      {  }                           
//-------------------------------------------------------------
   void mostrarNo()               //mostra na tela o nó {11, 7.66}
      {
        cout << iDado << ",  " << dDado << "     " << endl;
      }
//-------------------------------------------------------------
   };  //fim da classe No
////////////////////////////////////////////////////////////////
class ListaEncadeada 
   {
   private:
      No* pPrimeiro;                       // ponteiro ao primeiro nó da lista
      No* pUltimo;                          // ponteiro ao último nó da lista
   public:
//-------------------------------------------------------------
   ListaEncadeada() : pPrimeiro(NULL), pUltimo(NULL)      // construtor
      { }                                  // nenhum nó na lista
//-------------------------------------------------------------
   ~ListaEncadeada()                       //destrutor (vamos apagar os objetos)
      {
      No* pAtual = pPrimeiro;              //Iniciar com o 1ro elemento
      while(pAtual != NULL)                //Até o final da lista,
         {
         No* pAntigoAtual = pAtual;        //armazenar o ponteiro atual
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
   void inserePrimeiro(int id, double dd)
      {  
         No* novoNo = new No(id, dd);              // criar novo nó 
         novoNo->pSeguinte = pPrimeiro;            // novoNo-->antigo primeiro
         
         if(pUltimo == NULL)
           pUltimo = novoNo;                 
          
         if(pPrimeiro != NULL)
           pPrimeiro->pAnterior = novoNo;          // anterior do antigo primeiro passa a ser o novo no
                               
         pPrimeiro = novoNo;                       // primeiro-->novoNo
                                           
      }
//-------------------------------------------------------------
   No* buscar(int chave)                                            //buscar o nó com a chave desejada
      {                                                             //(assume-se que a lista não está vazia)
         No* buscaNo = pPrimeiro;                                   //Inicía com o 'primeiro' 
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
  /*    No* pAtual = pPrimeiro;             //busca desde o 1ro elemento
      No* pPrevio = pPrimeiro;
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
      if(pAtual == pPrimeiro){             //Se é o primeiro ponteiro,
         pPrimeiro = pPrimeiro->pSeguinte;//trocar o primeiro
         pPrimeiro->pAnterior = pUltimo;
      }else{                                   //caso contrario,
         pPrevio->pSeguinte = pAtual->pSeguinte; //recolocar ponteiro ao próximo obj
      }
      delete pAtual;                      //apagar nó
      return true;                        //remoção com sucesso */
      
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
   No* pegarPrimeiro()                    //retorna o primeiro nó
      { return pPrimeiro; }
//-------------------------------------------------------------
    No* pegarUltimo()                    //retorna o primeiro nó
      { return pUltimo; }
//-------------------------------------------------------------
   
   void removerPrimeiro()                       //apagar primeiro nó
      {                                         
          if(!estaVazio()){                     //( a priori a lista não esta vazia)
             No* novoPrimeiro = pPrimeiro;      //guarda o endereço do primeiro
             pPrimeiro = pPrimeiro->pSeguinte;  //quebra o laço: primeiro-->antigo seguinte
             pPrimeiro->pAnterior = NULL;
             delete novoPrimeiro;               //apaga o antigo nó primeiro com 'delete'
          }
      }
      
//-------------------------------------------------------------
   
   void removerUltimo()                       //apagar primeiro nó
      {                                         
          if(!estaVazio()){                     //( a priori a lista não esta vazia)
             if(pUltimo == pPrimeiro)
               removerPrimeiro();
             else{  
               No* pAux = pUltimo;
               pUltimo = pUltimo->pAnterior;
               pUltimo->pSeguinte = NULL;
               delete pAux;               //apaga o antigo nó ultimo com 'delete'
             }
          }
      }      
//-------------------------------------------------------------
   void mostrarLista()
      {
         No* noAtual = pPrimeiro;         //Iniciar no primeiro nó da lista
         if(noAtual != NULL){
             do{          //até o final da lista,
               noAtual->mostrarNo();          //imprimir dado
               noAtual = noAtual->pSeguinte;  //mover-se ao próximo nó     
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
   
   
   
   
   
   
   
   
   
   
   
   
   // funções complementares
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
   
   
   
   
   
   
   
