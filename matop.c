#include "mat.h"
#include "msgassert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3
#define OPCRIAR 4

static int opescolhida;
char outnome[100];
int optx, opty;

void uso() {
    fprintf(stderr, "matop\n");
    fprintf(stderr, "\t-s \t(somar matrizes) \n");
    fprintf(stderr, "\t-m \t(multiplicar matrizes) \n");
    fprintf(stderr, "\t-t \t(transpor matriz)\n");
    fprintf(stderr, "\t-c <arq> \t(cria matriz e salva em arq)\n");
    fprintf(stderr, "\t-x <int>\t(primeira dimensao)\n");
    fprintf(stderr, "\t-y <int>\t(segunda dimensao)\n");
}

void parse_args(int argc, char **argv) {
    extern char *optarg;
    extern int optind;
    int c;

    opescolhida = -1;
    optx = -1;
    opty = -1;
    outnome[0] = 0;

    while ((c = getopt(argc, argv, "smtc:x:y:h")) != EOF) {
        switch (c) {
            case 'm':
                avisoAssert(opescolhida == -1, "Mais de uma operação escolhida");
                opescolhida = OPMULTIPLICAR;
                break;
            case 's':
                avisoAssert(opescolhida == -1, "Mais de uma operação escolhida");
                opescolhida = OPSOMAR;
                break;
            case 't':
                avisoAssert(opescolhida == -1, "Mais de uma operação escolhida");
                opescolhida = OPTRANSPOR;
                break;
            case 'c':
                avisoAssert(opescolhida == -1, "Mais de uma operação escolhida");
                opescolhida = OPCRIAR;
                strcpy(outnome, optarg);
                break;
            case 'x':
                optx = atoi(optarg);
                break;
            case 'y':
                opty = atoi(optarg);
                break;
            case 'h':
            default:
                uso();
                exit(1);
        }
    }

    erroAssert(opescolhida > 0, "matop - necessário escolher operação");
    erroAssert(optx > 0, "matop - dimensão X da matriz tem que ser positiva");
    erroAssert(opty > 0, "matop - dimensão Y da matriz tem que ser positiva");
    if (opescolhida == OPCRIAR) {
        erroAssert(strlen(outnome) > 0, "matop - nome de arquivo de saída tem que ser definido");
    }
}

int main(int argc, char **argv) {

    mat_tipo a, b, c;
    FILE *outfile;

    parse_args(argc, argv);

    switch (opescolhida) {
        case OPSOMAR:
            criaMatriz(&a, optx, opty, 0);
            inicializaMatrizAleatoria(&a);
            criaMatriz(&b, optx, opty, 1);
            inicializaMatrizAleatoria(&b);
            criaMatriz(&c, optx, opty, 2);
            inicializaMatrizNula(&c);
            somaMatrizes(&a, &b, &c);
            imprimeMatriz(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
            break;
        case OPMULTIPLICAR:
            criaMatriz(&a, optx, opty, 0);
            inicializaMatrizAleatoria(&a);
            criaMatriz(&b, opty, optx, 1);
            inicializaMatrizAleatoria(&b);
            criaMatriz(&c, optx, optx, 2);
            inicializaMatrizNula(&c);
            multiplicaMatrizes(&a, &b, &c);
            imprimeMatriz(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
            break;
        case OPTRANSPOR:
            criaMatriz(&a, optx, opty, 0);
            inicializaMatrizAleatoria(&a);
            transpoeMatriz(&a);
            imprimeMatriz(&a);
            destroiMatriz(&a);
            break;
        case OPCRIAR:
            outfile = fopen(outnome, "wt");
            erroAssert(outfile != NULL, "Erro na criação do arquivo de saída");
            criaMatriz(&a, optx, opty, 0);
            inicializaMatrizAleatoria(&a);
            salvaMatriz(&a, outfile);
            destroiMatriz(&a);
            fclose(outfile);
            break;
        default:
            uso();
            exit(1);
    }

    return 0;
}





