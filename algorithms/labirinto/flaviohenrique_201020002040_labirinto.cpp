    /**
	* Algoritmo 2012-2 
    * Backtracking
    * Flávio Henrique Andrade dos Santos - 201020002040
	* 
	*
	**/
	#include <stdio.h>
	#include <math.h>
	#include <stdlib.h>
    #include <string.h>
	#include <iostream>
	using namespace std;

	//Variavéis Globais
	FILE *fpIn, *fpOut;

    class NoGrafo
	{
		private:
            string id;
            int altura,largura,sentido;
            bool visitado,inicio,saida;
					  
		public:
			NoGrafo* ptr;
			  
            NoGrafo( string _id, int _altura, int _largura, bool _bool)
			{
				id = _id;
                inicio = _bool;
                setPosicao(_altura,_largura);
				visitado = false;
                saida = false;
				ptr = NULL;
                sentido = 1;
			}
			  
			~NoGrafo()
            {
                limpa();
            }

            void setPosicao( int valorX, int valorY)
			{
                setAltura(valorX);
                setLargura(valorY);
			}

            void setAltura( int _alt )
			{
                altura = _alt;
			}
			
            int getAltura() const
			{
                return altura;
			}

            void setLargura( int _larg )
			{
                largura = _larg;
			}
			
            int getLargura() const
			{
                return largura;
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

            void setInicio( bool _ini )
			{
                inicio = _ini;
			}
			
            bool getInicio() const
			{
                return inicio;
			}

            void setSaida (bool _out){
                saida = _out;
            }

            bool getSaida() const
            {
                return saida;
            }

            void setSentido(int _v){
                sentido = _v;
            }

            int getSentido(){
                return sentido;
            }

            void limpa()
            {
                ptr = NULL;
            }

    };


    class Percurso{
    public:
        int nAdj;
        NoGrafo** listaAdj;

        Percurso(){

            nAdj = 0;
            listaAdj = (NoGrafo**) malloc(sizeof(NoGrafo*));

        }

        ~Percurso(){
            limpa();
        }

        void inserePercurso(NoGrafo* _no){
            nAdj++;

            listaAdj = (NoGrafo**) realloc(listaAdj, nAdj * sizeof(NoGrafo*));
            listaAdj[nAdj - 1] = _no;
        }


        void limpa(){
            //deleta nos
            int i=0;
            while(i < nAdj){
                delete(listaAdj[i]);
                i++;
            }
            free(listaAdj);

        }

    };

    int validPath(int** maze, int row,int col)
    {
        if(maze[row][col])
            return 1;

        return 0;
    }

    void imprimirArquivoOut(Percurso * P){
        //for(int i = P->nAdj - 1; i >= 0; i--)
        for(int i = 0; i < P->nAdj; i++)
            fprintf(fpOut,"[%i, %i] %s\n",P->listaAdj[i]->getAltura(),P->listaAdj[i]->getLargura(),P->listaAdj[i]->getId().c_str());
    }

    void checkAdj(int** maze, int** path, int row, int col, int* prox, int* ind, int *_back){
        int _t = 0;

        if(*_back){
            if(validPath(maze,row,col+1) && path[row][col+1] != 1)
                _t++;

            if(validPath(maze,row-1,col) && path[row-1][col] != 1)
                _t++;

            if(validPath(maze,row,col-1) && path[row][col-1] != 1)
                _t++;

            if(validPath(maze,row+1,col) && path[row+1][col] != 1)
                _t++;

            if(validPath(maze,row,col+1) && path[row][col+1] != 1)
                *prox = 1;
            else if(validPath(maze,row-1,col) && path[row-1][col] != 1)
                *prox = 2;
            else if(validPath(maze,row,col-1) && path[row][col-1] != 1)
                *prox = 3;
            else if(validPath(maze,row+1,col) && path[row+1][col] != 1)
                *prox = 4;

        }else{
            if(validPath(maze,row,col+1) && !path[row][col+1])
                _t++;

            if(validPath(maze,row-1,col) && !path[row-1][col])
                _t++;

            if(validPath(maze,row,col-1) && !path[row][col-1])
                _t++;

            if(validPath(maze,row+1,col) && !path[row+1][col])
                _t++;

            if(validPath(maze,row,col+1) && !path[row][col+1])
                *prox = 1;
            else if(validPath(maze,row-1,col) && !path[row-1][col])
                *prox = 2;
            else if(validPath(maze,row,col-1) && !path[row][col-1])
                *prox = 3;
            else if(validPath(maze,row+1,col) && !path[row+1][col])
                *prox = 4;
            else{
                *_back = 1;
                checkAdj(maze,path,row,col,&*prox,&*ind,&*_back);
            }

        }

        *ind = _t - *prox;

    }

    int checkIni(int** maze, int** path, int row, int col){
         int _t = 0;

         if(validPath(maze,row,col+1) && path[row][col+1] != 1)
             _t++;

         if(validPath(maze,row-1,col) && path[row-1][col] != 1)
             _t++;

         if(validPath(maze,row,col-1) && path[row][col-1] != 1)
             _t++;

         if(validPath(maze,row+1,col) && path[row+1][col] != 1)
             _t++;

         if(_t)
            return 0;

         return 1;
    }


    int searchUtil(int** maze,int** *sol,int row,int col, int _a, int _l, bool _input, Percurso* * _P, int _Rini, int _Cini)
    {
        int prox, ind, _back;


        if((checkIni(maze,(*sol),_Rini,_Cini) && !_input) ||
           (row == _a-1 && !_input) ||
           (row == 0 && !_input) ||
           (col == _l-1 && !_input) ||
           (col == 0 && !_input)){
            if(maze[row][col]){
                (*sol)[row][col] = 1;
                return 1;
            }
        }

        if(row >= _a || col >= _l || row < 0 || col < 0){
            return 0;
        }


        if(validPath(maze,row,col) == 1)
        {

            if((*sol)[row][col] != 1)
            {
                _back = 0;

                checkAdj(maze,(*sol),row,col,&prox,&ind,&_back);

                if(_back){
                    if(ind <= 0)
                        (*sol)[row][col] = 1;
                    else{
                        (*sol)[row][col] = 2;
                    }
                }else{
                    (*sol)[row][col] = 2;
                }

                if(prox == 1){
                    NoGrafo* _no = new NoGrafo("D",row,col,false);
                    (*_P)->inserePercurso(_no);
                    if(searchUtil(maze,&(*sol),row,col+1,_a,_l,false,&(*_P),_Rini,_Cini) == 1)
                        return 1;
                }

                if(prox == 2){
                    NoGrafo* _no = new NoGrafo("F",row,col,false);
                    (*_P)->inserePercurso(_no);
                    if(searchUtil(maze,&(*sol),row-1,col,_a,_l,false,&(*_P),_Rini,_Cini) == 1)
                        return 1;
                }

                if(prox == 3){
                    NoGrafo* _no = new NoGrafo("E",row,col,false);
                    (*_P)->inserePercurso(_no);
                    if(searchUtil(maze,&(*sol),row,col-1,_a,_l,false,&(*_P),_Rini,_Cini) == 1)
                        return 1;
                }

                if(prox == 4){
                    NoGrafo* _no = new NoGrafo("T",row,col,false);
                    (*_P)->inserePercurso(_no);
                    if(searchUtil(maze,&(*sol),row+1,col,_a,_l,false,&(*_P),_Rini,_Cini) == 1)
                        return 1;
                }


                (*sol)[row][col] = 0;
                return 0;
            }
        }

        return 0;
    }

    void iniciarPath(int** *path, int _altura, int _largura){
        int i,j;

		for(i=0;i<_altura;i++){
            (*path)[i] = (int*) malloc(_largura * sizeof(int));

            for(j=0;j<_largura;j++)
                (*path)[i][j] = 0;
        }	
	}

    void searchPath(int** maze,int _row,int _col,int _altura, int _largura)
    {
        int** path;
        Percurso * P = new Percurso();

        path = (int**) malloc(_altura * sizeof(int*));
		
        iniciarPath(&path, _altura, _largura);
	
        if(searchUtil(maze,&path,_row,_col,_altura,_largura,true,&P,_row,_col))
            imprimirArquivoOut(P);

        free(path);

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
		
    int** _maze;
    int _largura,_altura,_row,_col;
    char _indice [10];
    char _comp[] = "X";

    fscanf(fpIn, "%i",&_largura); // primeiro valor corresponde a largura
    fscanf(fpIn, "%i",&_altura); // primeiro valor corresponde a altura

    _maze = (int**) malloc(_altura * sizeof(int*));

    for(int i = 0; i < _altura; i++){

        _maze[i] = (int*) malloc(_largura * sizeof(int));

        for(int j = 0; j < _largura; j++){
            fscanf (fpIn, "%s", _indice);

            if(strcmp(_comp,_indice) != 0){
                _maze[i][j] = atoi(_indice) ? 0 : 1;
            }
            else{
                _maze[i][j] = 1;
                _row = i;
                _col = j;
            }
        }
    }

    searchPath(_maze,_row,_col,_altura,_largura);
	
    free(_maze);
    //Fechando os arquivos de entrada e saída
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
