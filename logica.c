#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "entradaSaida.h"

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

int *criarLista(int tamanho) {
    int *lista = (int *)calloc(tamanho, sizeof(int));
    if (lista == NULL) return NULL;
    return lista;
}
void liberarLista(int *lista) { free(lista); }

int verificaLinha(int **sudoku, int candidato, int linha, int dimensao){
    for(int i=0; i<dimensao; i++){
        if(sudoku[linha][i] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaColuna(int **sudoku, int candidato, int coluna,int dimensao){
    for(int i=0; i<dimensao; i++){
        if(sudoku[i][coluna] == candidato){
            return 0;
        }
    }
    return 1;
}

int verificaQuadrante(int **sudoku, int candidato, int linha, int coluna, int dimensao){
    int dim = sqrt(dimensao);
    int x0 = (linha/dim) * dim;
    int y0 = (coluna/dim) * dim;

    for(int i = 0; i<dim; i++){
        for(int j = 0; j<dim; j++){
            if(sudoku[x0+i][y0+j] == candidato){
                return 0;
            }
        }
    }
    return 1;
}

int solucaoBacktracking(int **sudoku, int dimensao){
    int vazioEncontrado = 0;
    int linha, coluna;

    for(linha = 0; linha < dimensao; linha++){
        for(coluna = 0; coluna < dimensao; coluna++){
            if(sudoku[linha][coluna] == -1){
                vazioEncontrado = 1;
                break;
            }
        }
        if (vazioEncontrado) break;
    }

    if(!vazioEncontrado){
        return 1;
    }

    for(int i = 1;i <= dimensao; i++){
        if(verificaLinha(sudoku, i, linha, dimensao) && verificaColuna(sudoku, i, coluna, dimensao) && verificaQuadrante(sudoku, i, linha, coluna, dimensao)){
            sudoku[linha][coluna] = i;

            if(solucaoBacktracking(sudoku, dimensao)){
                return 1;
            }

            sudoku[linha][coluna] = -1;
        }
    }

    return 0;
}

int heuristicaBuscaIndiceUnico(int **sudoku, int dimensao){
    int alterado = 0;

    for(int i = 0; i < dimensao; i++){
        for(int j = 0; j < dimensao; j++){
            if(sudoku[i][j] == -1){
                int *valoresValidos = criarLista(dimensao);
                int tamanahoLista = 0;

                for(int w=1; w <= dimensao; w++){
                    if(verificaLinha(sudoku, w, i, dimensao) && verificaColuna(sudoku, w, j, dimensao) && verificaQuadrante(sudoku, w, i, j, dimensao)){
                        valoresValidos[tamanahoLista] = w;
                        tamanahoLista++;
                    }

                }
                if(tamanahoLista == 1){
                    sudoku[i][j] = valoresValidos[0];
                    alterado = 1;
                }

                liberarLista(valoresValidos);
            }
        }
    }
    return alterado;
}

int sudokuSolucionado(int **sudoku, int dimensao){
    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            if(sudoku[i][j] == -1){
                return 0;
            }
        }
    }
    return 1;
}

int solucaoHeuristica(int **sudoku, int dimensao){
    int alterado = 0;
    do {
        alterado = heuristicaBuscaIndiceUnico(sudoku, dimensao);
    } while (alterado);

    if(sudokuSolucionado(sudoku, dimensao)) return 1;
    return 0;
}