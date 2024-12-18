#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int buscarPosMaisPreenchida(int matriz[9][9], int dimensao){
    
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
    
    
    printf("%d %d (%d,%d)", posLinha, posColuna, posMatriz[0], posMatriz[1]);
}

int main(){
    int matriz[9][9] = {
        {5, 3, -1, -1, 7, -1, -1, -1, -1},
        {6, -1, -1, 1, 9, 5, -1, -1, -1},
        {-1, 9, 8, -1, -1, -1, -1, 6, -1},
        {8, -1, -1, -1, 6, -1, -1, -1, 3},
        {4, -1, -1, 8, -1, 3, -1, -1, 1},
        {7, -1, -1, -1, 2, -1, -1, -1, 6},
        {-1, 6, -1, -1, -1, -1, 2, 8, -1},
        {-1, -1, -1, 4, 1, 9, -1, -1, 5},
        {-1, -1, -1, -1, 8, -1, -1, 7, 9}
    };

    buscarPosMaisPreenchida(matriz, 9);

}