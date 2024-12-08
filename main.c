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

    int **sudoku = leituraConfiguracao(arquivoConfiguracao);
    //separar as partes que calculam a dimensao e fazer uma função só pra isso

    if(sudoku != NULL){
        solucao(sudoku, 9);
        imprimirSaida(sudoku, 9, arquivoSolucao);
    }

    return 0;
}