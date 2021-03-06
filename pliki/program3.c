#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 4
typedef long long int DATA;

short write(DATA element, short length, FILE *stream){
    int buf = 0;
    for (short j = 0; j < length; ++j) {
        if(fputc(0, stream) == EOF)
            return EOF;
    }
    fseek(stream, -1, SEEK_CUR);
    for(short i = 0; i < length; ++i){
        buf = element % 256;
        element = element >> 8;
        if(fputc(buf, stream) == EOF)
            return EOF;
        if(i != length-1)
            fseek(stream, -2, SEEK_CUR);
    }
    fseek(stream, length-1, SEEK_CUR);
    return 0;
}

DATA read(short length, FILE *stream){
    DATA result = 0;
    for (short i = 0; i < length; ++i) {
        result = result << 8;
        result += fgetc(stream);
    }
    return result;
}

int main(int argc, char **argv){
    int kmin, kmax;

    if(argc != 3){
        printf("./program2 list number[1 or 2]\n");
        return 1;
    }

    FILE * list = fopen(argv[1], "r");
    char names[3][100];
    fscanf(list, "%s\n%s\n%s", names[0], names[1], names[2]);
    FILE * matrix1 = fopen(names[0], "r");
    FILE * matrix2 = fopen(names[1], "r");
    FILE * matrix3 = fopen(names[2], "r+");
    int w1w3 = read(SIZE, matrix1);
    int w2k1 = read(SIZE, matrix2);
    int k2k3 = read(SIZE, matrix2);
    if(w2k1 != read(SIZE, matrix1))
        return 1;
    write(w1w3, 2*SIZE, matrix3);
    write(k2k3, 2*SIZE, matrix3);

    kmin = atoi(argv[2]);
    if(kmin == 1){
        kmin = 0;
        kmax = k2k3 / 2;
        for (int i = 0; i < k2k3*w1w3; ++i) {
            //write(0, 2*SIZE, matrix3);
        }
        fseek(matrix3, 4*SIZE, SEEK_SET);
    }else if(kmin == 2){
        kmin = k2k3 / 2;
        kmax = k2k3;
        fseek(matrix2, SIZE*kmin, SEEK_CUR);
        fseek(matrix3, 2*SIZE*kmin, SEEK_CUR);
    }else{
        printf("./program2 list number[1 or 2]\n");
        return 1;
    }

    for (int i = 0; i < w1w3; ++i) {
        for (int j = kmin; j < kmax; ++j) {
            DATA sum = 0;
            for (int k = 0; k < w2k1; ++k) {
                sum += read(SIZE, matrix1) * read(SIZE, matrix2);
                if (k != w2k1 - 1)
                    fseek(matrix2, SIZE * (k2k3 - 1), SEEK_CUR);
            }
            write(sum, 2 * SIZE, matrix3);
            fseek(matrix1, -SIZE * (w2k1), SEEK_CUR);
            fseek(matrix2, -SIZE * ((w2k1 - 1) * k2k3), SEEK_CUR);
        }
        fseek(matrix3, 2*SIZE*(k2k3-(kmax-kmin)), SEEK_CUR);
        fseek(matrix1, SIZE*(w2k1), SEEK_CUR);
        fseek(matrix2, -SIZE*(kmax-kmin), SEEK_CUR);
    }
    return 0;
}