#include <stdio.h>
#include <getopt.h>
#include "forcaBruta.h"
#include "entradaSaida.h"

int main(int argc, char *argv[]){
    int opt;
    char *arquivoConfiguracao = NULL;
    char *arquivoSolucao = NULL;

    while((opt = getopt(argc, argv, "i:o:")) != -1){
        switch (opt) {
        case 'i':
            arquivoConfiguracao = optarg;
            break;
        case 'o':
            arquivoSolucao = optarg;
            break;
        default:
            printf("Use: ./<arquivoexecutavel> -i <arquivo configuracao> -o <arquivo solucao>\n");
            return 0;
        }
    }

    if(arquivoConfiguracao == NULL){
        printf("O arquivo de configuracao nao foi especificado.\n");
        return 0;
    }

    if(arquivoSolucao == NULL){
        printf("O arquivo de solucao nao foi especificado.\n");
        return 0;
    }
    
    FILE *f = fopen(arquivoConfiguracao, "r");
    int dimensao = calcularDimensao(f);


    //ver ultima linha vazia
    while(!feof(f)){        
        int **sudoku = leituraConfiguracao(f,dimensao);
        printf("\n");
        imprimirSudoku(sudoku, dimensao);
        printf("\n");

        if(sudoku != NULL){
            if(solucao2(sudoku, dimensao)){
                imprimirSudoku(sudoku, dimensao);
                imprimirSaida(sudoku, dimensao, arquivoSolucao);
                liberarSudoku(sudoku, dimensao);
            }
        }

    }

    fclose(f);
    return 0;
}