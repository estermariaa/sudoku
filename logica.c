#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logica.h"

char **criarSudoku(int dimensao, char elemento){
    char **matriz = (char**)malloc(dimensao*sizeof(char*));
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

void liberarSudoku(char **sudoku, int dimensao){
    for(int i=0; i<dimensao; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

void imprimirSudoku(char **matriz, int dimensao){
    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

int verificaLinha(char **matriz, int candidato, int linha,int dimensao){
    for(int i=0; i<dimensao; i++){
        // mudar para comparar com char
        if(matriz[linha][i] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaColuna(char **matriz, int candidato, int coluna,int dimensao){
    for(int i=0; i<dimensao; i++){
        // mudar para comparar com char
        if(matriz[i][coluna] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaQuadrante(char **matriz, int candidato, int linha, int coluna, int dimensao){
    int elemento = matriz[linha][coluna];
    int dim = sqrt(dimensao);
    int x0 = (linha/dim) * dim;
    int y0 = (coluna/dim) * dim;
    for(int i = 0; i<dim; i++){
        for(int j = 0; j<dim; j++){
            if(matriz[x0+i][y0+j] == candidato){
                return 0;
            }
        }
    }
    return 1;
}

void solucao(char **matriz, int dimensao){
    for(int x=0; x <dimensao; x++){
        for(int y=0; y < dimensao; y++){
            if(matriz[x][y] == 0){
                for(int w=1; w < 10; w++){
                    if(verificaLinha(matriz, w, x, dimensao) && verificaColuna(matriz, w, y, dimensao) && verificaQuadrante(matriz, w, x, y, dimensao)){
                        // tem que mudar a logica para char
                        matriz[x][y] = w;
                        solucao(matriz, dimensao);
                        matriz[x][y] = 0;
                        return;
                    }
                }
            }
        }
    }
}
