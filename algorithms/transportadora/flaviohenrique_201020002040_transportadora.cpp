    /**
	* Algoritmo 2012-2 
	* Grafo
	* Fl�vio Henrique Andrade dos Santos - 10210221
	* 
	*
	**/
	#include <stdio.h>
	#include <math.h>
	#include <stdlib.h>
    #include <string.h>
	#include <iostream>
	#define INFINITO 9999999	
	using namespace std;

	//Constantes
	const int TERRESTRE_CUSTO = 5;
    const double TERRESTRE_VELOCIDADE = 60;
	const int AEREO_CUSTO = 2000;
    const double AEREO_VELOCIDADE = 500;
	
	//Variav�is Globais
	FILE *fpIn, *fpOut;

	
	class NoGrafo
	{
		private:
            string id;
			int latitude,longitude,posicao,nAdj;
			bool visitado;
					  
		public:
            NoGrafo ** listaAdj;
			int distancia;
			NoGrafo* ptr;
			  
            NoGrafo( string _id, int _lat, int _long, int _pos)
			{
				id = _id;
				posicao = _pos;
				setCoordenadas(_lat,_long);
				visitado = false;
                listaAdj = (NoGrafo**) (malloc(sizeof(NoGrafo*)));
				nAdj = 0;
				distancia = 0;
				ptr = NULL;
			}
			  
			~NoGrafo()
            {
                limpa();
            }

            NoGrafo* getListaAdjPos(int _pos)
            {
                if(_pos < 0 || _pos >= nAdj)
                    return NULL;
                return listaAdj[_pos];
            }
			  
			void insereListaAdj(NoGrafo* no)
			{
                if(no == NULL)
                    return;

                nAdj++;
                listaAdj = (NoGrafo**) realloc(listaAdj, nAdj * sizeof(NoGrafo*));
                listaAdj[nAdj - 1] = no;
			}
			
            int getNAdj()
            {
                return nAdj;
            }

			void setCoordenadas( int valorX, int valorY)
			{
				setLatitude(valorX);
				setLongitude(valorY);
			}

			void setLatitude( int lat )
			{
				latitude = lat;
			}
			
			int getLatitude() const
			{
				return latitude;
			}

			void setLongitude( int _long )
			{
				longitude = _long;
			}
			
			int getLongitude() const
			{
				return longitude;
			}

			bool getVisitado() const
			{
				return visitado;
			}
			
			void setVisitado( bool valor )
			{
				visitado = valor;
			}
			
			string getId() const
			{
				return id;
			}

			void setDistancia( int _dis )
			{
				distancia = _dis;
			}
			
			int getDistancia() const
			{
				return distancia;
			}
			
			void setPosicao(int valor)
			{
				posicao = valor;
			}
			
			int getPosicao() const
			{
				return posicao;
			}

            void limpa()
            {
                //deleta nos adj
                for(int i=0; i < nAdj; i++)
                    delete(listaAdj[i]);
                free(listaAdj);
            }

	};

    class Percurso
    {
        private:
            int tipo;
            string destino;

        public:

            Percurso(int _tipo, string _destino)
            {
                setTipo(_tipo);
                setDestino(_destino);
            }

            ~Percurso()
            {}

            void setTipo(int valor)
            {
                tipo = valor;
            }

            int getTipo()
            {
                return tipo;
            }

            void setDestino(string valor)
            {
                destino = valor;
            }

            string getDestino()
            {
                return destino;
            }
    };
   

    void swap(NoGrafo** *F, int i, int j){

        NoGrafo* aux = (*F)[i];

        (*F)[i] = (*F)[j];

        (*F)[j] = aux;
    }

    void heapify(NoGrafo** *F, int i, int n) {
        unsigned int P = i;
        unsigned int E = 2*i + 1;
        unsigned int D = 2*i + 2;

        if(E < n && ((*F)[E])->getDistancia() < ((*F)[P])->getDistancia())
            P = E;

        if(D < n && ((*F)[D])->getDistancia() < ((*F)[P])->getDistancia())
            P = D;

        if(P != i) {
            swap(F, P, i);
            heapify(F, P, n);
        }
    }

    void criar_heap(NoGrafo** *F, int n){

        if(n <= 0)
            return;

        int p = (int) (n-2)/2;

        if(p < 0)
            p *= -1;

        for(int i = p; i >= 0; i--)
            heapify(F, i, n);

    }

    int arredondar(double d){
        return (d >= 0) ? (int)(d + 0.5) : (int)(d - 0.5);
    }

    int calcular_distancia(NoGrafo* x, NoGrafo* y){
        int a = (x->getLatitude() - y->getLatitude());
        int b = (x->getLongitude() - y->getLongitude());

        double result = pow(a,2) + pow(b,2);

        double d = sqrt(result);

        return arredondar(d);
    }

    void relaxar(NoGrafo* x, NoGrafo* y) {
        int d = calcular_distancia(x, y);
        if(y->getDistancia() > x->getDistancia() + d) {
            y->setDistancia(x->getDistancia() + d);
            y->ptr = x;
        }
    }

    void str_replace(const string& search, const string& replace, string *str)
    {
        size_t pos = 0;
        while((pos = str->find(search, pos)) != string::npos)
        {
            str->replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return;
    }

    int prazo(int _dist, int _tipo)
    {
        double result;
        if(_tipo == 1)
        {
            result = (_dist / TERRESTRE_VELOCIDADE);
            return arredondar(result);
        }
        else
        {
            result = (_dist / AEREO_VELOCIDADE);
            return arredondar(result);
        }
    }

    int custo(int _prazo, int _tipo)
    {
        if(_tipo == 1)
            return (int)(_prazo * TERRESTRE_CUSTO);
        else
            return (int)(_prazo * AEREO_CUSTO);
    }



	/**
	* 
	* 
	* 
	* 
	* 
	* 
	*/	
	class Grafo{
        public:
            NoGrafo ** listaNos;
            Percurso ** listaPercursos;
            int nV,nP;
            Grafo()
			{ 
                nV = 0;
                nP = 0;
                listaNos = (NoGrafo**) (malloc(sizeof(NoGrafo*)));
                listaPercursos = (Percurso**) (malloc(sizeof(Percurso*)));
			}

			~Grafo()
			{
				limpa(); 
			}
			
            void insereNo(NoGrafo * no)
			{
                nV++;
                listaNos = (NoGrafo**) realloc(listaNos, nV * sizeof(NoGrafo*));
                listaNos[nV - 1] = no;

			}

            void inserePercurso(Percurso * _p)
            {
                nP++;
                listaPercursos = (Percurso**) (realloc(listaPercursos, nP * sizeof(Percurso*)));
                listaPercursos[nP - 1] = _p;
            }

            NoGrafo* getLastListaNo()
            {
                return listaNos[nV - 1];
            }
			
			NoGrafo* procuraPonteiroNaPosicao( int valor )
			{
			   NoGrafo* retorno  = NULL;

               for(int i=0; i < nV; i++)
               {
                   if(listaNos[i]->getPosicao() == valor)
                   {
                       retorno = listaNos[i];
                       break;
                   }
               }

			   return retorno;
			}			
			
            NoGrafo* procuraPonteiroNoId( char id[100] )
			{
			   NoGrafo* retorno  = NULL;

               for(int i=0; i < nV; i++)
               {
                  if ( strcmp(id,listaNos[i]->getId().c_str()) == 0)
				  {
                      retorno = listaNos[i];
                      break;
				  }
			   }

			   return retorno;
            }

            NoGrafo* procuraPonteiroNoValor( string id )
            {
               NoGrafo* retorno  = NULL;

               for(int i=0; i < nV; i++)
               {
                   if ( strcmp(id.c_str(),listaNos[i]->getId().c_str()) == 0)
                  {
                      retorno = listaNos[i];
                      break;
                  }
               }

               return retorno;
            }

            NoGrafo* origem(){

                NoGrafo* no = NULL;

                for(int i=0; i < nV; i++){
                    no = listaNos[i];
                    if(no->getLatitude() == 0 && no->getLongitude() == 0)
                        return no;
                }

                return NULL;

            }

            void mostraListaAdj(NoGrafo *no)
			{
                int nAdj = no->getNAdj();
                //cout << " " << nAdj;
                for(int i = 0; i < nAdj; i++)
                    cout << " "  << no->listaAdj[i]->getId() << " lat: " << no->listaAdj[i]->getLatitude() << " long: " << no->listaAdj[i]->getLongitude() << endl;
            }

            void mostraListaPercursos()
            {
                for(int i = 0; i < nP; i++)
                {
                    cout << endl;
                    cout << " Tipo: " << listaPercursos[i]->getTipo() << " Destino: " << listaPercursos[i]->getDestino() << endl;
                }
            }
			
			void limpa()
			{
                //deleta nos
                for(int i=0; i < nV; i++)
                    delete(listaNos[i]);
                free(listaNos);

                //deleta percurso
                for(int j=0; j < nP; j++)
                    delete(listaPercursos[j]);
                free(listaPercursos);
			}

            void Fila(NoGrafo** *F)
            {

                *F = (NoGrafo**) malloc(nV * sizeof(NoGrafo*));

                int i = 0;

                while(i < nV){
                    (*F)[i] = listaNos[i];
                    i++;
                }

                criar_heap(F, nV);
            }


            void inicializar()
            {
                int i = 0;
                NoGrafo * s = origem();
                while(i < nV){
                    listaNos[i]->setDistancia(INFINITO);
                    listaNos[i]->ptr = NULL;
                    i++;
                }
                s->setDistancia(0);
            }


            void dijkstra()
            {
                inicializar();

                NoGrafo** F;

                Fila(&F);
                int i = nV - 1;

                while(i >= 0){
                    NoGrafo* x = F[0];

                    swap(&F, 0, i);

                    NoGrafo* NoAdj = x->getListaAdjPos(0);

                    for(int j=1; NoAdj != NULL; j++) {

                        if(!NoAdj->getVisitado())
                            relaxar(x, NoAdj);

                        NoAdj = x->getListaAdjPos(j);
                    }

                    F[i] = NULL;
                    delete(F[i]);

                    criar_heap(&F, i);

                    x->setVisitado(true);
                    i--;
                }

                free(F);
            }


            void imprimirArquivoOut()
            {
                for(int i = 0; i < nP; i++)
                {
                    NoGrafo *atualNo = procuraPonteiroNoValor(listaPercursos[i]->getDestino());
                    int _prazo,_custo;

                    if(atualNo != NULL)
                    {
                        string cidade = atualNo->getId();

                        str_replace("_"," ",&cidade);

                        if(listaPercursos[i]->getTipo() == 1)
                        {
                            _prazo = prazo(atualNo->getDistancia(),1);
                            _custo = custo(_prazo,1);

                            fprintf(fpOut, "Transporte economico para %s \nDistancia: %ikm \nCusto: R$%i \nPrazo: %ih\n", cidade.c_str(),atualNo->getDistancia(),_custo,_prazo);
                        }
                        else
                        {
                            _prazo = prazo(atualNo->getDistancia(),2);
                            _custo = custo(_prazo,2);

                            fprintf(fpOut, "Transporte expresso para %s \nDistancia: %ikm \nCusto: R$%i \nPrazo: %ih\n", cidade.c_str(),atualNo->getDistancia(),_custo,_prazo);
                        }
                    }
                    fprintf(fpOut, "\n");
                }
            }
			
    };



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
		
    int lt,lg,num_vertices,num_arestas,num_percursos;
    char indice [100];
    char adj [100];
    char tipo [100];
    char destino [100];
	char stop[] = "0";
    char cmptipo[] = "ECO";
	int ctrol = 0;


	fscanf(fpIn, "%i",&num_vertices); // primeiro valor corresponde ao numero total de vertices
	
	fscanf(fpIn, "%i",&num_arestas); // segundo valor corresponde ao numero total de arestas
	
    Grafo* G = new Grafo();

	//primeiro indice
    fscanf (fpIn, "%s", indice);
    fscanf (fpIn, "%i", &lt);
	fscanf (fpIn, "%i", &lg);

    NoGrafo *newNo = new NoGrafo( indice, lt, lg, ctrol);

    G->insereNo(newNo);

    NoGrafo * atualNo = newNo;
	
	
	// preenchendo o vetor com os elementos informados no arquivo de entrada
	while (!feof (fpIn) && (ctrol < num_vertices)){
      fscanf (fpIn, "%s", adj);
      if(strcmp(stop,adj) == 0)
	  {
		ctrol++;
		
        if(ctrol < num_vertices){
            fscanf (fpIn, "%s", indice);

			NoGrafo *no = G->procuraPonteiroNoId(indice);
			
			if(no != NULL)
			{
				fscanf (fpIn, "%i", &lt);
				fscanf (fpIn, "%i", &lg);
				no->setCoordenadas(lt,lg);
				no->setPosicao(ctrol);

                atualNo = no;
			}
			else
			{
				fscanf (fpIn, "%i", &lt);
				fscanf (fpIn, "%i", &lg);

                NoGrafo *newNoP = new NoGrafo( indice, lt, lg, ctrol);

                G->insereNo(newNoP);

                atualNo = newNoP;
			}
		}
	  }
	  else 
	  {		
		NoGrafo *proxNo = G->procuraPonteiroNoId(adj);
        if(proxNo == NULL){
            NoGrafo * newNoAdj = new NoGrafo(adj,0,0,-1);

            G->insereNo(newNoAdj);

            atualNo->insereListaAdj(newNoAdj);
        }
        else
        {
            atualNo->insereListaAdj(proxNo);
        }
	  }
    }
	
    //Ler as sa�das
    fscanf (fpIn, "%i", &num_percursos);

    for(int j = 0; j < num_percursos; j++)
    {
        fscanf (fpIn, "%s", tipo);
        fscanf (fpIn, "%s", destino);
        if(strcmp(cmptipo,tipo) == 0){
            Percurso * newPerc = new Percurso(1,destino);
            G->inserePercurso(newPerc);
        }
        else
        {
            Percurso * newPerc = new Percurso(2,destino);
            G->inserePercurso(newPerc);
        }
    }

    //Caminhos m�nimos
    G->dijkstra();

    //arquivo de sa�da
    G->imprimirArquivoOut();


    for(int i = 0; i < G->nV; i++)
    {
        cout << endl;
        cout << " Cidade: " << G->listaNos[i]->getId() << " distancia: " << G->listaNos[i]->getDistancia() << endl;
    }
	
	//Fechando os arquivos de entrada e sa�da	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
