#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logica.h"

int **criarSudoku(int dimensao, int elemento){
    int **matriz = (int**)malloc(dimensao*sizeof(int*));
    if(matriz == NULL){
        printf("Erro ao alocar memoria para as linhas da matriz\n");
        return NULL;
    }

    for(int i=0; i<dimensao; i++){
        matriz[i] = (int*)malloc(dimensao*sizeof(int));
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

void liberarSudoku(int **sudoku, int dimensao){
    for(int i=0; i<dimensao; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

void imprimirSudoku(int **sudoku, int dimensao){
    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            if(sudoku[i][j] == -1){
                printf("v ");
            }else{
                printf("%d ", sudoku[i][j]);
            }
        }
        printf("\n");
    }
}

int verificaLinha(int **matriz, int candidato, int linha, int dimensao){
    for(int i=0; i<dimensao; i++){
        if(matriz[linha][i] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaColuna(int **matriz, int candidato, int coluna,int dimensao){
    for(int i=0; i<dimensao; i++){
        if(matriz[i][coluna] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaQuadrante(int **matriz, int candidato, int linha, int coluna, int dimensao){
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

int resolvido = 0;

void solucao(int **matriz, int dimensao){
    if(resolvido) return;

    int vazio = 1;
    for(int x=0; x <dimensao; x++){
        for(int y=0; y < dimensao; y++){
            if(matriz[x][y] == -1){
                vazio = 0;
                for(int w=1; w <= dimensao; w++){
                    if(verificaLinha(matriz, w, x, dimensao) && verificaColuna(matriz, w, y, dimensao) && verificaQuadrante(matriz, w, x, y, dimensao)){
                        matriz[x][y] = w;
                        solucao(matriz, dimensao);
                        if(resolvido) return;
                        matriz[x][y] = -1;
                    }
                }

                return;
            }
        }
    }
    if (vazio) {
        imprimirSudoku(matriz, dimensao);
        resolvido = 1;
    }
}
