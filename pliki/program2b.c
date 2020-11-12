#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 4
#define RAND_SIZE 52600
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

short generate(short length, short elements, FILE *stream){
    for (short i = 0; i < elements; ++i) {
        if(write(rand()%RAND_SIZE, length, stream))
            return -1;
    }
    return 0;
}

int nwd(int a, int b){
    int c = -1;
    if(b > a){
        c = b;
        b = a;
        a = c;
    }
    do{
        int div = a / b;
        c = a - (div * b);
        a = b;
        b = c;
    }while(c != 0);
    return a;
}

int main(int argc, char **argv){
    srand(time(NULL));
    if(argc != 3){
        return 1;
    }
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    /* GENERATING SIZE OF MATRIX */
    int w1 = min + rand() % (max-min+1);
    int k2 = min + rand() % (max-min+1);
    int k1w2 = nwd(w1, k2);
    w1 /= k1w2;
    k2 /= k1w2;

    FILE * matrix1 = fopen("matrix1", "w+");
    FILE * matrix2 = fopen("matrix2", "w+");

    write(w1, SIZE, matrix1);
    write(k1w2, SIZE, matrix1);

    write(k1w2, SIZE, matrix2);
    write(k2, SIZE, matrix2);

    generate(SIZE, w1*k1w2, matrix1);
    generate(SIZE, k2*k1w2, matrix2);

}