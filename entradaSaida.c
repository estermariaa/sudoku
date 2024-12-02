#include <stdio.h>
#include <string.h>
#include "entradaSaida.h"

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
    printf("%d\n", dimensao);

    return 1;
}
