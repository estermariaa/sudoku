#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]){
    int opt;
    char *arquivoConfiguracao = NULL;
    char *arquivoSolucao = NULL;

    while((opt = getopt(argc, argv, "i:o:")) != 1){
        switch (opt) {
        case 'i':
            arquivoConfiguracao = optarg;
            break;
        case 'o':
            arquivoSolucao = optarg;
            break;
        default:
            printf("Use: ./<arquivoexecutavel> -k <arquivo configuracao> -c <arquivo solucao>\n");
            return 0;
        }
    }

    if(arquivoConfiguracao == NULL){
        printf("O arquivo de configuracao nao foi especificado.\n");
        return 0;
    }

    if(arquivoSolucao == NULL){
        printf("O arquivo de solucao nao foi especificado.\n");
        return 0;
    }

    return 0;
}