#include <stdio.h>
#include <getopt.h>
#include "logica.h"
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
    int **sudoku = leituraConfiguracao(f, dimensao);

    if(sudoku != NULL){
        if(solucao2(sudoku, dimensao)){
            imprimirSudoku(sudoku, dimensao);
            imprimirSaida(sudoku, dimensao, arquivoSolucao);
            liberarSudoku(sudoku, dimensao);
        }
    }

    fclose(f);
    
//vou arrumar ainda
/*
    FILE *f = fopen(leituraConfiguracao, "r");

    while(!feof(f)){
        int dimensao = calcularDimensao(f);
        int **sudoku = leiturcaConfiguraco(f, dimensao);

        if(sudoku != NULL){
            if(solucao2(sudoku, dimensao)){
                imprimirSudoku(sudoku, dimensao);
                imprimirSaida(sudoku, dimensao, arquivoSolucao);
                liberarSudoku(sudoku, dimensao);
            }
        }
    }
    fclose(f);
*/

    return 0;
}