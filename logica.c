#include <stdio.h>
#include <stdlib.h>
#include "logica.h"

char **criarSudoku(int dimensao, char elemento){
    char **matriz = (char*)malloc(dimensao*sizeof(char));
    if(matriz == NULL){
        printf("Erro ao alocar memoria para as linhas da matriz\n");
        return NULL;
    }

    for(int i=0; i<dimensao; i++){
        matriz[i] = (char*)malloc(dimensao*sizeof(char));
        if(matriz[i] == NULL){
            printf("Erro ao alocar memoria para as colunas da matriz\n");
            return NULL;
        }
        for(int j=0; j<dimensao; j++){
            matriz[i][j] = elemento;
        }
    }
    
    return matriz;
}

void liberarSudoku(int dimensao, char **sudoku){
    for(int i=0; i<dimensao; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}