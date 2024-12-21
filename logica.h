#ifndef LOGICA_H
#define LOGICA_H

int **criarSudoku(int dimensao, int elemento);
void liberarSudoku(int **sudoku, int dimensao);
void imprimirSudoku(int **sudoku, int dimensao);
int *criarLista(int tamanho);
void liberarLista(int *lista);
int verificaLinha(int **sudoku, int candidato, int linha, int dimensao);
int verificaColuna(int **sudoku, int candidato, int coluna,int dimensao);
int verificaQuadrante(int **sudoku, int candidato, int linha, int coluna, int dimensao);
int solucaoBacktracking(int **sudoku, int dimensao);
int heuristicaBuscaIndiceUnico(int **sudoku, int dimensao);
int solucaoHeuristica(int **sudoku, int dimensao);
int sudokuSolucionado(int **sudoku, int dimensao);

#endif