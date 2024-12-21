#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
//#include <sys/time.h>
//#include <sys/resource.h>
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
    
    /*struct timeval inicioUsuario, fimUsuario;
    gettimeofday(&inicioUsuario, NULL);
    struct rusage inicioCPU, fimCPU;
    getrusage(RUSAGE_SELF, &inicioCPU);*/

    double tempoEntrada = 0.0;
    double tempoSaida = 0.0;
    int numeroSudokus = 0;

    FILE *f = fopen(arquivoConfiguracao, "r");
    FILE *fSaida = fopen(arquivoSolucao, "w");
    int dimensao = calcularDimensao(f);

    //ver ultima linha vazia
    while(!feof(f)){     

        //struct timeval inicioEntrada, fimEntrada;
        //gettimeofday(&inicioEntrada, NULL);

        int **sudoku = leituraConfiguracao(f,dimensao);
        numeroSudokus++;
        fprintf(fSaida, "\nSUDOKU %d:\n", numeroSudokus);

        //gettimeofday(&fimEntrada, NULL);
        //tempoEntrada += (fimEntrada.tv_sec - inicioEntrada.tv_sec) + (fimEntrada.tv_usec - inicioEntrada.tv_usec) / 1000000.0;

        if(sudoku != NULL){
            if(!solucaoHeuristica(sudoku, dimensao)){
                fprintf(fSaida, "Solução parcial: Heuristica\n");
                imprimirSaida(sudoku, dimensao, fSaida);
                if(solucaoBacktracking(sudoku, dimensao)){
                    if(sudokuSolucionado(sudoku, dimensao)){
                        //struct timeval inicioSaida, fimSaida;
                        //gettimeofday(&inicioSaida, NULL);

                        fprintf(fSaida, "Sudoku solucionado: Backtracking:\n");
                        imprimirSaida(sudoku, dimensao, fSaida);
                        liberarSudoku(sudoku, dimensao);

                        //gettimeofday(&fimSaida, NULL);
                        //tempoSaida += (fimSaida.tv_sec - inicioSaida.tv_sec) + (fimSaida.tv_usec - inicioSaida.tv_usec) / 1000000.0;

                        continue;
                    }
                }else{
                    //struct timeval inicioSaida, fimSaida;
                    //gettimeofday(&inicioSaida, NULL);

                    fprintf(fSaida, "Sudoku nao solucionado (nem heuristica nem backtracking):\n");
                    imprimirSaida(sudoku, dimensao, fSaida);
                    liberarSudoku(sudoku, dimensao);

                    //gettimeofday(&fimSaida, NULL);
                    //tempoSaida += (fimSaida.tv_sec - inicioSaida.tv_sec) + (fimSaida.tv_usec - inicioSaida.tv_usec) / 1000000.0;

                }
            }else{
                //struct timeval inicioSaida, fimSaida;
                //gettimeofday(&inicioSaida, NULL);

                fprintf(fSaida, "Sudoku solucionado: Heuristica\n");
                imprimirSaida(sudoku, dimensao, fSaida);
                liberarSudoku(sudoku, dimensao);

                //gettimeofday(&fimSaida, NULL);
                //tempoSaida += (fimSaida.tv_sec - inicioSaida.tv_sec) + (fimSaida.tv_usec - inicioSaida.tv_usec) / 1000000.0;
            }
        }

    }

    fclose(f);
    fclose(fSaida);

    //gettimeofday(&fimUsuario, NULL);
    //getrusage(RUSAGE_SELF, &fimCPU);

    //double tempoTotal = (fimUsuario.tv_sec - inicioUsuario.tv_sec) + (fimUsuario.tv_usec - inicioUsuario.tv_usec) / 1000000.0;
    //double tempoCPU = (fimCPU.ru_utime.tv_sec - inicioCPU.ru_utime.tv_sec) + (fimCPU.ru_utime.tv_usec - inicioCPU.ru_utime.tv_usec) / 1000000.0 + (fimCPU.ru_stime.tv_sec - inicioCPU.ru_stime.tv_sec) + (fimCPU.ru_stime.tv_usec - inicioCPU.ru_stime.tv_usec) / 1000000.0;
    
    //printf("\nDimensão testada: %dx%d\n", dimensao, dimensao);
    //printf("Tempo de Entrada e Saida: %.6f segundos\n", tempoEntrada + tempoSaida);
    //printf("Tempo de Relogio: %.6f segundos\n", tempoTotal);
    //printf("Tempo de CPU: %.6f segundos\n\n", tempoCPU);
    
    return 0;
}