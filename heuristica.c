#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "forcaBruta.h"
#include "entradaSaida.h"

/*
void buscarPosMaisPreenchida(int **matriz, int dimensao, int *melhorLinha, int *melhorColuna, int *quadranteLinha, int *quadranteColuna){
    int contagemLinha = 0,contagemColuna = 0;
    int posLinha, posColuna = 0;

    for(int i=0; i<dimensao;i++){
        int auxLinha = 0;
        int auxColuna = 0;
        for(int j=0; j<dimensao;j++){
            if(matriz[i][j] != -1)
                auxLinha++;
            if(matriz[j][i] != -1)
                auxColuna++;
        }
        if(auxLinha >= contagemLinha){
            contagemLinha = auxLinha;
            posLinha = i;
        }
        if(auxColuna >= contagemColuna){
            contagemColuna = auxColuna;
            posColuna = i;
        }
    }

    int dim = sqrt(dimensao); 
    int contagemMatriz = 0;
    int posMatriz[2];

    for (int x0 = 0; x0 < dimensao; x0 += dim) {
        for (int y0 = 0; y0 < dimensao; y0 += dim) {
            int preenchidos = 0;
            for (int k = 0; k <dimensao; k++) {
                int i = k / dim;
                int j = k % dim;
                if (matriz[x0 + i][y0 + j] != -1) {
                    preenchidos++;
                }
            }
            if (preenchidos >= contagemMatriz) {
                contagemMatriz = preenchidos;
                posMatriz[0] = x0;
                posMatriz[1] = y0;

            }
        }
    }
    *melhorLinha = posLinha;
    *melhorColuna = posColuna;
    *quadranteLinha = posMatriz[0];
    *quadranteColuna = posMatriz[1];
}

int numeroValido(int **matriz, int linha, int coluna, int numero, int dimensao){
    int dim = sqrt(dimensao);

    for(int i=0; i<dimensao; i++){
        if(matriz[linha][i] == numero) return 0;
    }
    for(int i=0; i<dimensao; i++){
        if(matriz[i][coluna] == numero) return 0;
    }

    int x0 = (linha/dim) * dim;
    int y0 = (coluna/dim) * dim;

    for(int i = 0; i<dim; i++){
        for(int j = 0; j<dim; j++){
            if(matriz[x0+i][y0+j] == numero){
                return 0;
            }
        }
    }
    return 1;
}

void gerarCandidatos(int **matriz, int linha, int coluna, int candidatos[], int dimensao){
    for(int i=1; i<=dimensao; i++){
        if(numeroValido(matriz, linha, coluna, i, dimensao)){
            candidatos[i-1] = i;
        }else{
            candidatos[i-1] = 0;
        }
    }
}

int buscarMelhorPosicao(int **matriz, int dimensao, int *melhorLinha, int *melhorColuna, int *quadranteLinha, int *quadranteColuna){
    int dim = sqrt(dimensao);
    int atualizou = 0;

    for(int i=0; i<dimensao; i++){
        if(matriz[*melhorLinha][i] == -1){
            int candidatos[dimensao];
            gerarCandidatos(matriz, *melhorLinha, i, candidatos, dimensao);

            int numCandidatos = 0;
            int unicoCandidato = -1;
            for(int k=0; k <dimensao; k++){
                if(candidatos[k] != 0){
                    numCandidatos++;
                    unicoCandidato = candidatos[k];
                }
            }
            if(numCandidatos == 1){
                matriz[*melhorLinha][i] = unicoCandidato;
                atualizou = 1;
            }
        }
    }
    for (int i = 0; i < dimensao; i++) {
        if (matriz[i][*melhorColuna] == -1) {
            int candidatos[dimensao];
            gerarCandidatos(matriz, i, *melhorColuna, candidatos, dimensao);

            int numCandidatos = 0;
            int unicoCandidato = -1;
            for (int k = 0; k < dimensao; k++) {
                if (candidatos[k] != 0) {
                    numCandidatos++;
                    unicoCandidato = candidatos[k];
                }
            }

            if (numCandidatos == 1) {
                matriz[i][*melhorColuna] = unicoCandidato;
                atualizou = 1;
            }
        }
    } 
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int x = *quadranteLinha + i;
            int y = *quadranteColuna + j;

            if (matriz[x][y] == -1) {
                int candidatos[dimensao];
                gerarCandidatos(matriz, x, y, candidatos, dimensao);

                int numCandidatos = 0;
                int unicoCandidato = -1;
                for (int k = 0; k < dimensao; k++) {
                    if (candidatos[k] != 0) {
                        numCandidatos++;
                        unicoCandidato = candidatos[k];
                    }
                }

                if (numCandidatos == 1) {
                    matriz[x][y] = unicoCandidato;
                    atualizou = 1;
                }
            }
        }
    }  
    return atualizou;
}
*/

typedef struct {
    int linha;
    int coluna;
    int possibilidades;
} Celula;

int *criarLista(int tamanho) {
    int *lista = (int *)malloc(tamanho * sizeof(int));
    if (lista == NULL) return NULL;
    return lista;
}
void liberarLista(int *lista) { free(lista); }

// SOLUCAO CELULAS UNICAS
int buscaIndiceUnico(int **matriz, int dimensao){
    int alterado = 0;

    for(int i = 0; i < dimensao; i++){
        for(int j = 0; j < dimensao; j++){
            if(matriz[i][j] == -1){
                int *valoresValidos = criarLista(dimensao);
                int tamanahoLista = 0;

                for(int w=1; w <= dimensao; w++){
                    if(verificaLinha(matriz, w, i, dimensao) && verificaColuna(matriz, w, j, dimensao) && verificaQuadrante(matriz, w, i, j, dimensao)){
                        valoresValidos[tamanahoLista] = w;
                        tamanahoLista++;
                    }

                }
                if(tamanahoLista == 1){
                    matriz[i][j] = valoresValidos[0];
                    printf("preencheu um valor!\n");
                    alterado = 1;
                }

                liberarLista(valoresValidos);
            }
        }
    }
    return alterado;
}

// ====================================================================================

// solucao com MRV

Celula buscaCelula(int **matriz, int dimensao){
    Celula melhorCelula = {-1, -1, dimensao + 1};

    for(int i = 0; i < dimensao; i++){
        for(int j = 0; j < dimensao; j++){
            if(matriz[i][j] == -1){
                int possibilidades = 0;

                for(int num=1; num <= dimensao; num++){
                    if(verificaLinha(matriz, num, i, dimensao) && verificaColuna(matriz, num, j, dimensao) && verificaQuadrante(matriz, num, i, j, dimensao)){
                        possibilidades++;
                    }

                }

                if(possibilidades < melhorCelula.possibilidades){
                    melhorCelula.linha = i;
                    melhorCelula.coluna = j;
                    melhorCelula.possibilidades = possibilidades;
                }
                

            }
        }
    }

    return melhorCelula;
}

int solucao3(int **matriz, int dimensao) {
    Celula celula = buscaCelula(matriz, dimensao);

    if (celula.linha == -1) return 1;
        
    for (int num = 1; num <= dimensao; num++) {
        if (verificaLinha(matriz, num, celula.linha, dimensao) && verificaColuna(matriz, num, celula.coluna, dimensao) && verificaQuadrante(matriz, num, celula.linha, celula.coluna, dimensao)) {
            matriz[celula.linha][celula.coluna] = num;


            if (solucao3(matriz, dimensao)) {
                return 1;
            }
            //printf("errou!\n");
            matriz[celula.linha][celula.coluna] = -1;
            
        }

    }

    return 0;
}

// ====================================================================================

// SOLUCAO COM LCV

int contarRestricoes(int** matriz, int linha, int coluna, int numero, int dimensao) {
    int restricoes = 0;

    for (int coluna = 0; coluna < dimensao; coluna++) {
        if (matriz[linha][coluna] == -1) {
            if(verificaLinha(matriz, numero, linha, dimensao) && verificaColuna(matriz, numero, coluna, dimensao) && verificaQuadrante(matriz, numero, linha, coluna, dimensao)){
                restricoes++;
            }
        }
    }

    for (int linha = 0; linha < dimensao; linha++) {
        if (matriz[linha][coluna] == -1) {
            if(verificaLinha(matriz, numero, linha, dimensao) && verificaColuna(matriz, numero, coluna, dimensao) && verificaQuadrante(matriz, numero, linha, coluna, dimensao)){
                restricoes++;
            }
        }
    }

    int dim = sqrt(dimensao);
    int x0 = (linha / dim) * dim;
    int y0 = (coluna / dim) * dim;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matriz[x0 + i][y0 + j] == -1) {
                if(verificaLinha(matriz, numero, x0 + i, dimensao) && verificaColuna(matriz, numero, y0 + j, dimensao) && verificaQuadrante(matriz, numero, x0 + i, y0 + j, dimensao)){
                    restricoes++;
                }
            }
        }
    }

    return restricoes;
}

int escolherValorLCV(int** matriz, int linha, int coluna, int dimensao) {
    int melhorValor = -1;
    int minRestricoes = dimensao + 1; // Um valor maior que o possível número de restrições

    for (int numero = 1; numero <= dimensao; numero++) {
        if (verificaLinha(matriz, numero, linha, dimensao) && verificaColuna(matriz, numero, coluna, dimensao) && verificaQuadrante(matriz, numero, linha, coluna, dimensao)) {
            int restricoes = contarRestricoes(matriz, linha, coluna, numero, dimensao);
            if (restricoes < minRestricoes) {
                minRestricoes = restricoes;
                melhorValor = numero;
            }
        }
    }
    return melhorValor;
}

int solucaoComLCV(int** matriz, int dimensao) {
    Celula celula = buscaCelula(matriz, dimensao); // Sua função buscaCelula (MRV)
    if (celula.linha == -1) return 1; // Sudoku resolvido

    int valor = escolherValorLCV(matriz, celula.linha, celula.coluna, dimensao);

    if (valor != -1) {
        matriz[celula.linha][celula.coluna] = valor;
        if (solucaoComLCV(matriz, dimensao)) return 1;
        matriz[celula.linha][celula.coluna] = -1; // Backtracking
    }
    return 0;
}

// ====================================================================================

int main(){
    int dimensao = 9;

    int **matriz = criarSudoku(dimensao, -1);

    int valores[9][9] = {
        {5, -1, -1, -1, 7, -1, -1, -1, -1},
        {-1, 3, -1, 9, -1, -1, -1, 1, 5},
        {7, -1, -1, -1, 5, 6, -1, -1, -1},
        {6, -1, 8, 7, -1, -1, -1, -1, 3},
        {-1, 9, -1, -1, 8, 4, -1, -1, 7},
        {3, -1, -1, -1, -1, 9, 4, -1, 6},
        {-1, -1, 7, 6, 3, -1, -1, -1, 9},
        {-1, 8, -1, -1, -1, -1, 9, 6, -1},
        {9, -1, -1, 3, -1, -1, -1, 4, 8}
    };


    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            matriz[i][j] = valores[i][j];
        }
    }

    int melhorLinha, melhorColuna, quadranteLinha, quadranteColuna;
    int atualizou;
    
    //imprimirSudoku(matriz, dimensao);

    //do{
    //    buscarPosMaisPreenchida(matriz, dimensao, &melhorLinha, &melhorColuna, &quadranteLinha, &quadranteColuna);
    //    atualizou = buscarMelhorPosicao(matriz, dimensao, &melhorLinha, &melhorColuna, &quadranteLinha, &quadranteColuna);
    //} while(atualizou);
    
    //printf("\n");
    //imprimirSudoku(matriz, dimensao);
    //liberarSudoku(matriz, dimensao);

    
    int contador = 0;
    int alterado;
    do {
        alterado = buscaIndiceUnico(matriz, dimensao);
        contador++;
    } while (alterado);
    
    //solucao3(matriz, dimensao);
    //solucaoComLCV(matriz,dimensao);

    
      
    //printf("%d\n", contador);

    imprimirSudoku(matriz, dimensao);

    return 0;
}