#include <stdio.h>
#include <string.h>
#include "entradaSaida.h"
#include "logica.h"

int **leituraConfiguracao(char *arquivo){
    FILE *f = fopen(arquivo, "r");
    if(f == NULL){
        printf("Erro ao abrir o arquivo de configuracao\n");
        return 0;
    }

    int dimensao = 0;
    char linha[1000];
    while(fgets(linha, sizeof(linha), f)!= NULL){
        if(strspn(linha, " \t\n") == strlen(linha)){
            break;
        }
        dimensao++;
    }
    dimensao = dimensao*dimensao;

    rewind(f);

    int **matriz = criarSudoku(dimensao, -1);
    if(matriz == NULL){
        fclose(f);
        return 0;
    }

    int linhaAtual = 0;
    while(fgets(linha, sizeof(linha), f) != NULL){
        if(strspn(linha, " \t\n") == strlen(linha)){
            continue; //ignora as linhas vazias
        }

        int colunaAtual = 0;
        for(int i=0; i<strlen(linha); i++){
            if(linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n'){
                if(linha[i] == 'v'){
                    matriz[linhaAtual][colunaAtual] = -1;
                }else{
                    matriz[linhaAtual][colunaAtual] = linha[i] - '0';
                }
                colunaAtual++;
            }
        }
        linhaAtual++;
    }

    fclose(f);

    return matriz;
}

void imprimirSaida(int **sudoku, int dimensao, char *arquivo){
    FILE *f = fopen(arquivo, "w");
    if(f == NULL){
        printf("Erro ao abrir o arquivo de saida\n");
        return;
    }

    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            if(sudoku[i][j] == -1){
                fprintf(f, "v ");
            }else{
                fprintf(f, "%d ", sudoku[i][j]);
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
