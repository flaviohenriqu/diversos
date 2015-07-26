    /**
	* Algoritmo 2012-2 
	* Grafo
	* Flávio Henrique Andrade dos Santos - 10210221
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
    const double CABOS = 100;
    const int CABOS_CUSTO = 3000;
    const int DIARIA = 1;
    const int DIARIA_CUSTO = 500;
	
	//Variavéis Globais
	FILE *fpIn, *fpOut;

	
	class NoGrafo
	{
		private:
            string id;
            int latitude,longitude,posicao,chave;
			bool visitado;
					  
		public:
			NoGrafo* ptr;
			  
            NoGrafo( string _id, int _lat, int _long, int _pos)
			{
				id = _id;
				posicao = _pos;
                setLocalizacao(_lat,_long);
				visitado = false;
                chave = 0;
				ptr = NULL;
			}
			  
			~NoGrafo()
            {
                limpa();
            }

            void setLocalizacao( int valorX, int valorY)
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

            void setChave( int _chv )
			{
                chave = _chv;
			}
			
            int getChave() const
			{
                return chave;
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
                ptr = NULL;
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

        if(E < n && ((*F)[E])->getChave() < ((*F)[P])->getChave())
            P = E;

        if(D < n && ((*F)[D])->getChave() < ((*F)[P])->getChave())
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

    void setValorMatriz(NoGrafo *no, NoGrafo *adj, int ** *M)
    {

        int _dist = calcular_distancia(no, adj);

        if(_dist < adj->getChave()) {

            adj->setChave(_dist);

            if(adj->ptr != NULL){
                (*M)[adj->ptr->getPosicao()][adj->getPosicao()] = 0;
                (*M)[adj->getPosicao()][adj->ptr->getPosicao()] = 0;
            }

            adj->ptr = no;

            (*M)[no->getPosicao()][adj->getPosicao()] = 1;
            (*M)[adj->getPosicao()][no->getPosicao()] = 1;

        }

    }

    int custoTotal(int _total,int _prazo)
    {
        int result = ((_total * CABOS_CUSTO) + (_prazo * DIARIA_CUSTO));
        return result;
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
            int nV;
            Grafo()
			{ 
                nV = 0;
                listaNos = (NoGrafo**) (malloc(sizeof(NoGrafo*)));
			}

			~Grafo()
			{
				limpa(); 
			}
			
            void insereNo(NoGrafo * no)
			{
                if(no == NULL)
                    return;

                nV++;
                listaNos = (NoGrafo**) realloc(listaNos, nV * sizeof(NoGrafo*));
                listaNos[nV - 1] = no;

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

                int i=0;

                while(i < nV){
                    no = listaNos[i];
                    if((no->getLatitude() == 0) && (no->getLongitude() == 0))
                        return no;

                    i++;
                }

                return NULL;

            }

			void limpa()
			{
                //deleta nos
                int i=0;
                while(i < nV){
                    delete(listaNos[i]);
                    i++;
                }
                free(listaNos);
			}


            void Fila(NoGrafo** *F){

                *F = (NoGrafo**) malloc(nV * sizeof(NoGrafo*));

                int i = 0;

                while(i < nV){
                    (*F)[i] = listaNos[i];
                    i++;
                }

                criar_heap(F, nV);
            }

            void inicializar() {
                NoGrafo* s = origem();
                int i = 0;
                while(i < nV){
                    listaNos[i]->setChave(INFINITO);
                    listaNos[i]->ptr = NULL;
                    i++;
                }
                s->setChave(0);
            }

            void prim(int** *M) {

                inicializar();

                NoGrafo** F;

                Fila(&F);

                int i = nV - 1;

                while( i>=0 ){
                    NoGrafo* x = F[0];

                    swap(&F, 0, i);

                    NoGrafo* NoAdj = listaNos[0];

                    for(int j=1; NoAdj != NULL; j++) {

                        if(NoAdj != x && !NoAdj->getVisitado())
                            setValorMatriz(x, NoAdj, M);

                        NoAdj = j < nV ? listaNos[j] : NULL;
                    }

                    F[i] = NULL;
                    delete(F[i]);

                    criar_heap(&F, i);

                    x->setVisitado(true);

                    i--;
                }

                free(F);
            }

            void imprimirArquivoOut(int ** *M)
            {
                int total = 0;

                int i = 0;
                int virg;

                while(i < nV)
                {
                    virg = 0;

                    if(listaNos[i] != NULL){

                        string bairro = listaNos[i]->getId();
                        str_replace("_"," ",&bairro);
                        fprintf(fpOut, "[%s]",bairro.c_str());

                        int j = 0;
                        while(j < nV)
                        {
                            if((*M)[i][j] != 0){
                                if(listaNos[j] != NULL){
                                    string adj = listaNos[j]->getId();
                                    str_replace("_"," ",&adj);
                                    if(virg > 0)
                                        fprintf(fpOut, ",");

                                    fprintf(fpOut, " %s", adj.c_str());
                                    virg++;
                                }
                            }
                            j++;
                        }
                    }
                    fprintf(fpOut, "\n");
                    i++;
                }

                int k = 0;

                while(k < nV){
                    if(listaNos[k] != NULL)
                        total += listaNos[k]->getChave();

                    k++;
                }

                double _totalCabos = (total * 1000) / CABOS;

                int totalCabos = arredondar(_totalCabos);

                int _prazo = totalCabos * DIARIA;

                int _custo = custoTotal(totalCabos,_prazo);

                fprintf(fpOut, "Prazo: %i dias\nCusto: R$%i\n", _prazo, _custo);

            }

			
    };

    void initMatriz(int** *M, int _row, int _col, int _valor){

        int i = 0;

        (*M) = (int**) malloc(_row * sizeof(int*));

        while(i < _row){

            (*M)[i] = (int*) malloc(_col * sizeof(int));

            int j = 0;
            while(j < _col){
                (*M)[i][j] = _valor;
                j++;
            }

            i++;
        }
    }


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
		
    int lt,lg,num_vertices;
    char indice [100];

	fscanf(fpIn, "%i",&num_vertices); // primeiro valor corresponde ao numero total de vertices	
	
    Grafo* G = new Grafo();

    for(int j = 0; j < num_vertices; j++)
    {
        fscanf (fpIn, "%s", indice);
        fscanf (fpIn, "%i", &lt);
        fscanf (fpIn, "%i", &lg);

        NoGrafo *newNo = new NoGrafo( indice, lt, lg, j);

        G->insereNo(newNo);
    }

    int** Mat;

    initMatriz(&Mat,num_vertices,num_vertices,0);
	
    //Árvores mínimas
    G->prim(&Mat);

    //arquivo de saída
    G->imprimirArquivoOut(&Mat);

    /*for(int i = 0; i < G->nV; i++)
    {
        cout << "Bairro: " << G->listaNos[i]->getId().c_str() << " Lat: " << G->listaNos[i]->getLatitude() << " Long: " << G->listaNos[i]->getLongitude() << " chave: " << G->listaNos[i]->getChave() << endl;
    }*/

    //Fechando os arquivos de entrada e saída
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
