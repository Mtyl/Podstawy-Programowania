#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
        if(write(rand(), length, stream))
        return -1;
    }
    return 0;
}

void sort(short length, short elements, FILE *stream){
    for(short i = 0; i < elements; i++){
        fseek(stream, i*length, SEEK_SET);
        DATA minimum = read(length, stream);
        DATA cur;
        short position = i;
        for(short j = i+1; j < elements; j++){
            cur = read(length, stream);
            if(cur < minimum){
                position = j;
                minimum = cur;
            }
        }
        fseek(stream, i*length, SEEK_SET);
        cur = read(length, stream);
        fseek(stream, -length, SEEK_CUR);
        write(minimum, length, stream);
        fseek(stream, position*length, SEEK_SET);
        write(cur, length, stream);
    }
    fseek(stream, 0, SEEK_SET);
}

void list(short length, short elements, FILE *stream){
    for (short i = 0; i < elements; ++i) {
        printf("%lli\n", read(length, stream));
    }
    return;
}
int main(int argc, char **argv){
    srand(time(NULL));
    FILE * data;
    if(argc != 5){
        printf("Syntax: ./program1 namefile length_of_element number_of_elements action\n Actions:\n -g\t generate list of elements \n -s\t sort elements \n -l\t print elements\n");
        return 1;
    }
    short length = atoi(argv[2]) > 8 ? 8 : atoi(argv[2]);
    short elements = atoi(argv[3]);
    if(!strcmp(argv[4], "-g")){
        data = fopen(argv[1], "w+");
        generate(length, elements, data);
    }
    else if(!strcmp(argv[4], "-s")){
        data = fopen(argv[1], "r+");
        sort(length, elements, data);
    }
    else if(!strcmp(argv[4], "-l")){
        data = fopen(argv[1], "r+");
        list(length, elements, data);
    }
    return 0;
}

