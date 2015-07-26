    /**
	* Algoritmo 2012-2 
	* Grafo
	* Fl�vio Henrique Andrade dos Santos - 10210221
	* 
	*
	**/
	#include <stdio.h>
	#include <stdlib.h>
    #include <string.h>
	#include <iostream>
	using namespace std;
	
	//Variav�is Globais
	FILE *fpIn, *fpOut;

    int kmp_search(const char *text, const char *pattern)
    {
        int *T;
        int i, j;
        int result = 0;

        if (pattern[0] == '\0')
            return 0;

        // Construindo Tabela
        T = (int*) malloc((strlen(pattern)+1) * sizeof(int) );
        T[0] = -1;
        for (i=0; pattern[i] != '\0'; i++) {
            T[i+1] = T[i] + 1;
            while (T[i+1] > 0 && pattern[i] != pattern[T[i+1]-1])
                T[i+1] = T[T[i+1]-1] + 1;
        }

        //Busca na cadeia
        for (i=j=0; text[i] != '\0'; ) {
            if (j < 0 || text[i] == pattern[j]) {
                ++i, ++j;
                if (pattern[j] == '\0') {
                    //result = text+i-j;
                    result++;
                    //break;
                }
            }
            else j = T[j];
        }

        free(T);
        return result;
    }


    class Cadeias{
    private:
        int id;
        string cadeia;

    public:

        Cadeias(string _c,int _id){
            setCadeia(_c);
            setId(_id);
        }

        ~Cadeias()
        { }

        void setCadeia(string _c){

            cadeia = _c;
        }

        string getCadeia(){
            return cadeia;
        }

        void setId(int _id){
            id = _id;
        }

        int getId(){
            return id;
        }
    };

    class Padroes{
    private:
        string padrao;
        int total;

    public:
        Cadeias** listaCadeias;
        int nC;

        Padroes(string _p){
            nC = 0;
            setPadrao(_p);
            setTotal(0);

            listaCadeias = (Cadeias**) (malloc(sizeof(Cadeias*)));
        }

        ~Padroes()
        { limpa(); }

        void insereCadeia(Cadeias* _c){
            nC++;
            listaCadeias = (Cadeias**) realloc(listaCadeias, nC * sizeof(Cadeias*));
            listaCadeias[nC - 1] = _c;
        }

        void setPadrao(string _p){
            padrao = _p;
        }

        string getPadrao(){
            return padrao;
        }

        void setTotal(int _v){
            total = _v;
        }

        int getTotal(){
            return total;
        }

        void limpa()
        {
            //deleta cadeias
            int i=0;
            while(i < nC){
                delete(listaCadeias[i]);
                i++;
            }
            free(listaCadeias);
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
    Cadeias** listaCadeia;
    Padroes** listaPadroes;


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
		
    int nc,nb;
    char cadeia[100];
    char padrao[100];

    fscanf(fpIn, "%i",&nc); // primeiro valor corresponde ao numero total de cadeias

    listaCadeia = (Cadeias**) (malloc(nc *sizeof(Cadeias*)));


    for(int j = 0; j < nc; j++)
    {
        fscanf (fpIn, "%s", cadeia);

        Cadeias* _c = new Cadeias(cadeia,j);

        listaCadeia[j] = _c;

    }

    fscanf(fpIn, "%i",&nb); // valor corresponde ao numero total de padr�es de busca

    listaPadroes = (Padroes**) (malloc(nb *sizeof(Padroes*)));

    for(int i = 0; i < nb; i++)
    {
        fscanf (fpIn, "%s", padrao);

        Padroes* _p = new Padroes(padrao);

        listaPadroes[i] = _p;
    }



    //Busca das ocorr�ncias pelo algoritmo KMP
    for(int l = 0; l < nb; l++){
        int _total = 0;
        int _tmp;

        for(int k = 0; k < nc; k++){
            Cadeias* _cadeia = listaCadeia[k];

            _tmp = kmp_search(listaCadeia[k]->getCadeia().c_str(),listaPadroes[l]->getPadrao().c_str());

            _total += _tmp;

            if(_tmp > 0)
                listaPadroes[l]->insereCadeia(_cadeia);
        }

        listaPadroes[l]->setTotal(_total);
    }



   //imprimir no arquivo de sa�da
   for(int m = 0; m < nb; m++){
       if(listaPadroes[m]->getTotal() > 1){
           if(listaPadroes[m]->nC > 1){
               fprintf(fpOut, "[%s] %i resultados nas cadeias ",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal());
               for(int n = 0; n < listaPadroes[m]->nC; n++){
                   if(n > 0)
                       fprintf(fpOut, ",%i",listaPadroes[m]->listaCadeias[n]->getId());
                   else
                       fprintf(fpOut, "%i",listaPadroes[m]->listaCadeias[n]->getId());
               }
           }else{
               fprintf(fpOut, "[%s] %i resultados na cadeia %i",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal(),listaPadroes[m]->listaCadeias[0]->getId());
           }
           fprintf(fpOut, "\n");

       }
       else{
           fprintf(fpOut, "[%s] %i resultado na cadeia %i",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal(),listaPadroes[m]->listaCadeias[0]->getId());
           fprintf(fpOut, "\n");
       }
   }

    //Fechando os arquivos de entrada e sa�da
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
