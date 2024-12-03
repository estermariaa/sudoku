#ifndef LOGICA_H
#define LOGICA_H

char **criarSudoku(int dimensao, char elemento);
void liberarSudoku(char **sudoku, int dimensao);
void imprimirSudoku(char **matriz, int dimensao);


#endif