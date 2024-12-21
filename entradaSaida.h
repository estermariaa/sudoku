#ifndef ENTRADASAIDA_H
#define ENTRADASAIDA_H

int linhaVazia(char *linha);
int calcularDimensao(FILE *f);
int **leituraConfiguracao(FILE *f, int dimensao);
void imprimirSaida(int **sudoku, int dimensao, FILE *f);


#endif