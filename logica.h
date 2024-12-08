#ifndef LOGICA_H
#define LOGICA_H

int **criarSudoku(int dimensao, int elemento);
void liberarSudoku(int **sudoku, int dimensao);
void imprimirSudoku(int **matriz, int dimensao);
int verificaLinha(int **matriz, int candidato, int linha, int dimensao);
int verificaColuna(int **matriz, int candidato, int coluna,int dimensao);
int verificaQuadrante(int **matriz, int candidato, int linha, int coluna, int dimensao);
void solucao(int **matriz, int dimensao);


#endif