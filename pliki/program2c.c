#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 4
typedef long long int DATA;

short write(DATA element, short length, FILE *stream){
    int buf = 0;
    for (short j = 0; j < length; ++j) {
        fputc(0, stream);
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
    if(argc != 4){
        printf("./program2c matrix1 matrix2 matrix3\n");
        return 1;
    }
    FILE * matrix1 = fopen(argv[1], "r");
    FILE * matrix2 = fopen(argv[2], "r");
    FILE * matrix3 = fopen(argv[3], "w+");
    int w1w3 = read(SIZE, matrix1);
    int w2k1 = read(SIZE, matrix2);
    int k2k3 = read(SIZE, matrix2);
    if(w2k1 != read(SIZE, matrix1)){
        return 1;
        printf("Multiplying impossible\n");
    }
    if(read( 2*SIZE, matrix3) != w1w3){
        return 1;
        printf("Wrong matrix size\n");
    }
    if(read( 2*SIZE, matrix3) != k2k3){
        return 1;
        printf("Wrong matrix size\n");
    }
    write(k2k3, 2*SIZE, matrix3);

    for (int i = 0; i < w1w3; ++i) {
        for (int j = 0; j < k2k3; ++j) {
            DATA sum = 0;
            for (int k = 0; k < w2k1; ++k) {
                sum += read(SIZE, matrix1) * read(SIZE, matrix2);
                if(k != w2k1-1)
                fseek(matrix2, SIZE*(k2k3-1), SEEK_CUR);
            }
            if(sum != read(2*SIZE, matrix3){
                return 1;
                printf("Incorrect element\n");
            }
            fseek(matrix1, -SIZE*(w2k1), SEEK_CUR);
            fseek(matrix2, -SIZE*((w2k1-1)*k2k3), SEEK_CUR);
        }
        fseek(matrix1, SIZE*(w2k1), SEEK_CUR);
        fseek(matrix2, -SIZE*(k2k3), SEEK_CUR);
    }

    printf("Matrix multiplied correctly\n");
    return 0;
}