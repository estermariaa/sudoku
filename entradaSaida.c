#include <stdio.h>
#include <string.h>
#include "entradaSaida.h"
#include "logica.h"

int leituraConfiguracao(char *arquivo){
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

    char **matriz = criarSudoku(dimensao, 'v');
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
                matriz[linhaAtual][colunaAtual] = linha[i];
                colunaAtual++;
            }
        }
        linhaAtual++;
    }

    imprimirSudoku(matriz, dimensao);
    liberarSudoku(matriz, dimensao);

    fclose(f);

    return 1;
}
