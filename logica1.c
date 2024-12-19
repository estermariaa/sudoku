#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"

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

int *criarLista(int tamanho) {
    int *lista = (int *)malloc(tamanho * sizeof(int));
    if (lista == NULL) return NULL;
    return lista;
}

void liberarLista(int *lista) { free(lista); }

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

int main(){
    int dimensao = 9;

    int **matriz = criarSudoku(dimensao, -1);

    int valores[9][9] = {
        {4, -1, -1, 8, -1, -1, 3, -1, -1},
        {-1, -1, 3, -1, -1, 1, -1, 8, -1},
        {-1, -1, -1, -1, 2, -1, -1, -1, 9},
        {7, -1, -1, -1, 6, -1, -1, -1, -1},
        {-1, 1, -1, -1, 9, -1, -1, 2, -1},
        {-1, -1, -1, -1, 1, -1, -1, -1, 7},
        {9, -1, -1, -1, 5, -1, -1, -1, -1},
        {-1, 4, -1, 2, -1, -1, 8, -1, -1},
        {-1, -1, 8, -1, -1, 4, -1, -1, 5}
    };


    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            matriz[i][j] = valores[i][j];
        }
    }

    int melhorLinha, melhorColuna, quadranteLinha, quadranteColuna;
    int atualizou;
    
    imprimirSudoku(matriz, dimensao);

    //do{
    //    buscarPosMaisPreenchida(matriz, dimensao, &melhorLinha, &melhorColuna, &quadranteLinha, &quadranteColuna);
    //    atualizou = buscarMelhorPosicao(matriz, dimensao, &melhorLinha, &melhorColuna, &quadranteLinha, &quadranteColuna);
    //} while(atualizou);
    
    //printf("\n");
    //imprimirSudoku(matriz, dimensao);
    //liberarSudoku(matriz, dimensao);

    int alterado;
    do {
        alterado = buscaIndiceUnico(matriz, dimensao);
        printf("oi\n");
    } while (alterado);

    imprimirSudoku(matriz, dimensao);

    return 0;
}