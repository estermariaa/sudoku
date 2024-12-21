#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "entradaSaida.h"
#include "logica.h"
#include <errno.h> 

int linhaVazia(char *linha) {
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n' && linha[i] != '\r') {
            return 0; // Não é vazia
        }
    }
    return 1; // É vazia
}

int calcularDimensao(FILE *f){
    int dimensao = 0;
    char linha[1000];
    long posicaoInicial = ftell(f);

    while(fgets(linha, sizeof(linha), f)!= NULL){
        if(strspn(linha, " \t\n") == strlen(linha)){
            break;
        }
        dimensao++;
    }
    dimensao = dimensao*dimensao;

    fseek(f,posicaoInicial,SEEK_SET);
    return dimensao;
}

int **leituraConfiguracao(FILE *f, int dimensao) {
    char linha[1000];
    int **matriz = criarSudoku(dimensao, -1);

    if (matriz == NULL) {
        fclose(f);
        return NULL;
    }

    int linhaAtual = 0;
    while (linhaAtual < dimensao && fgets(linha, sizeof(linha), f) != NULL) {
        if (linhaVazia(linha)) continue;

        int colunaAtual = 0;
        char *token = strtok(linha, " \t\n\r"); 
        while (token != NULL && colunaAtual < dimensao) {
            if (strcmp(token, "v") == 0 || strcmp(token, "V") == 0) {
                matriz[linhaAtual][colunaAtual++] = -1;
            } else {
                char *endptr;
                long int num = strtol(token, &endptr, 10); 

                if (*endptr != '\0' || errno == ERANGE) { 
                    printf("Erro de conversao na linha %d, coluna %d: '%s'\n", linhaAtual+1, colunaAtual+1, token);
                    return NULL;
                }

                if (num < 1 || num > dimensao) {
                    printf("Numero fora do intervalo na linha %d, coluna %d: %ld\n", linhaAtual+1, colunaAtual+1, num);
                    return NULL;
                }
                matriz[linhaAtual][colunaAtual++] = (int)num;
            }
            token = strtok(NULL, " \t\n\r"); 
        }


        if (colunaAtual != dimensao) {
            printf("Numero de colunas invalido na linha %d.\n", linhaAtual+1);
            return NULL;
        }
        linhaAtual++;
    }

    if (linhaAtual != dimensao) {
        printf("Numero de linhas invalido no arquivo.\n");
        return NULL;
    }

    return matriz;
}

void imprimirSaida(int **sudoku, int dimensao, FILE *f){
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
}
