    /**
	* Algoritmo 2012-2 
    * Busca em Cadeia
    * Flávio Henrique Andrade dos Santos - 201020002040
	* 
	*
	**/
	#include <stdio.h>
	#include <stdlib.h>
    #include <string.h>
	#include <iostream>
	using namespace std;
	
	//Variavéis Globais
	FILE *fpIn, *fpOut;

    void initTab(int* *T, const char *p){
        int i, j = -1;
        (*T)[0] = -1;

        for(i = 1; i < strlen(p); i++){
            while(j >= 0 && p[j+1] != p[i])
                j = (*T)[j];
            if(p[j+1] == p[i])  j++;
            (*T)[i] = j;
        }
    }

    void kmp_busca(const char* text, const char *p, int* result){
        int *T;
        (*result) = 0;

        //Construir Tabela
        T = (int*) malloc((strlen(p)+1)*sizeof(int));

        initTab(&T,p);

        //Busca KMP
        int j = -1;

        for(int i = 0; i < strlen(text); i++) {
            while(j >= 0 && p[j + 1] != text[i]) j = T[j];
            if(p[j + 1] == text[i]) j++;
            if(j == strlen(p) - 1) {
                (*result)++;
                j = T[j];
            }
        }

        free(T);
    }

    class Cadeias{
    private:
        int id;
        string cadeia;

    public:

        Cadeias(int _id,string _c){
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
        int *listaOcorrencias;
        int nO;
        int nC;

        Padroes(string _p){
            nC = 0;
            nO = 0;
            setPadrao(_p);
            setTotal(0);
            listaOcorrencias = (int*) (malloc(sizeof(int)));

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

        void insereOcorrencia(int _v){
            nO++;
            listaOcorrencias = (int*) realloc(listaOcorrencias, nO * sizeof(int));
            listaOcorrencias[nO - 1] = _v;
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

            //deleta ocorrencias
            free(listaOcorrencias);
        }
    };



    void getResult(Cadeias** listaCadeia, Padroes** *listaPadroes, int nc, int nb){

        for(int l = 0; l < nb; l++){
            int _total = 0;
            int _tmp;

            for(int k = 0; k < nc; k++){
                Cadeias* _cadeia = listaCadeia[k];

                kmp_busca(_cadeia->getCadeia().c_str(),(*listaPadroes)[l]->getPadrao().c_str(),&_tmp);

                _total += _tmp;

                if(_tmp > 0){
                    (*listaPadroes)[l]->insereCadeia(_cadeia);
                    (*listaPadroes)[l]->insereOcorrencia(_tmp);
                }
            }

            (*listaPadroes)[l]->setTotal(_total);

        }

    }

    void setFileOut(Padroes** listaPadroes,int nb){
        for(int m = 0; m < nb; m++){
           if(listaPadroes[m]->getTotal() == 0){
               fprintf(fpOut, "[%s] Sem Resultados",listaPadroes[m]->getPadrao().c_str());
               fprintf(fpOut, "\n");
           }
           else if(listaPadroes[m]->getTotal() == 1){
               fprintf(fpOut, "[%s] %i resultado na cadeia %i:%i",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal(),listaPadroes[m]->listaCadeias[0]->getId(),listaPadroes[m]->listaOcorrencias[0]);
               fprintf(fpOut, "\n");
           }
           else{
               if(listaPadroes[m]->nC == 1){
                   fprintf(fpOut, "[%s] %i resultados na cadeia %i:%i",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal(),listaPadroes[m]->listaCadeias[0]->getId(),listaPadroes[m]->listaOcorrencias[0]);
               }else{
                   fprintf(fpOut, "[%s] %i resultados nas cadeias ",listaPadroes[m]->getPadrao().c_str(),listaPadroes[m]->getTotal());
                   for(int n = 0; n < listaPadroes[m]->nC; n++){
                       if(n == 0)
                           fprintf(fpOut, "%i:%i",listaPadroes[m]->listaCadeias[n]->getId(),listaPadroes[m]->listaOcorrencias[n]);
                       else
                           fprintf(fpOut, ", %i:%i",listaPadroes[m]->listaCadeias[n]->getId(),listaPadroes[m]->listaOcorrencias[n]);
                   }
               }
               fprintf(fpOut, "\n");
           }
        }
    }

/**
* Função Principal
* Responsavél pela inserção dos arquivos de entrada e saída, execução do método busca em cadeia do problema.
* Parâmetros
* int argc : conta quantos parametros foram passados para a execução do programa
* char *argv : sequência de strings que serão os argumentos do programa
*/
int main(int argc, char* argv[])
{
    Cadeias** listaCadeia;
    Padroes** listaPadroes;

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
		
    //Pegar do arquivo de entrada
    int nc,nb;
    char cadeia[100];
    char padrao[100];

    fscanf(fpIn, "%i",&nc); // primeiro valor corresponde ao numero total de cadeias

    listaCadeia = (Cadeias**) (malloc(nc *sizeof(Cadeias*)));

    for(int j = 0; j < nc; j++)
    {
        fscanf (fpIn, "%s", cadeia);

        Cadeias* _c = new Cadeias(j,cadeia);

        listaCadeia[j] = _c;

    }

    fscanf(fpIn, "%i",&nb); // valor corresponde ao numero total de padrões de busca

    listaPadroes = (Padroes**) (malloc(nb *sizeof(Padroes*)));

    for(int i = 0; i < nb; i++)
    {
        fscanf (fpIn, "%s", padrao);

        Padroes* _p = new Padroes(padrao);

        listaPadroes[i] = _p;
    }

    //Busca das ocorrências pelo algoritmo KMP
    getResult(listaCadeia,&listaPadroes,nc,nb);

    //imprimir no arquivo de saída
    setFileOut(listaPadroes,nb);

    //deleta cadeia
    int n=0;
    while(n < nc){
       delete(listaCadeia[n]);
       n++;
    }
    free(listaCadeia);

    //deleta padrão
    int o=0;
    while(o < nb){
       delete(listaPadroes[o]);
       o++;
    }
    free(listaPadroes);

    //Fechando os arquivos de entrada e saída
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
