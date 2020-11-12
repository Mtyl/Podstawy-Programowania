#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 100
#define DEFAULT_SIZE 3
//COMPRESSION LIMIT 99

short ngets(char data[], short length, FILE *stream){
    short counter = 0;
    char c = getc(stream);
    //printf("FIRST CHAR: %d\n", c);
    while((counter < length) && (c != EOF)){
        data[counter] = c;
        counter++;
        c = getc(stream);
     }
    for(short i = counter; i < length; i++){
        data[i] = 0;
    }
    //fseek(stream,0, SEEK_END);
    //long length1 = ftell(stream);
    //fseek(stream,0, SEEK_SET);
    return counter;
}
short asciiToHex(char c, char result[], short position){
    short b = 0;
    b = c / 16;
    result[position] = ((b < 10) ? (48 + b) : (55 + b));
    position++;
    b = c % 16;
    result[position] = ((b < 10) ? (48 + b) : (55 + b));
    position++;
    return position;
}

short readMany(char ***data){
    short w = 0;

    *data = malloc(DEFAULT_SIZE*sizeof(**data));
    for(short i = 0;i < DEFAULT_SIZE; i++)
        (*data)[i] = malloc(LINE_LENGTH*sizeof(***data));
    while(1) {
        if(ngets((*data)[w], LINE_LENGTH, stdin)){
            w++;
            if (w > 2) {
                *data = realloc(*data, (w + 1) * sizeof(**data));
                (*data)[w] = malloc(LINE_LENGTH * sizeof(***data));
        }}
        else{
            *data = realloc(*data, w * sizeof(**data));
            return w;
        }
    }

}

void compress(char **data){
        char buffer[LINE_LENGTH];
        char c = 0;
        short counter = 0;
        short out = 0;
        char eof = 0;
        for (short in = 0; (in < LINE_LENGTH && !eof); ++in) {
            if(c == (*data)[in]){
                counter++;
            }
            else {
                if (counter > 4 || c == '%' || c == '(' || c == ')') {
                        if(c == '%' || c == '(' || c == ')'){
                            buffer[out] = '%';
                            out++;
                            out = asciiToHex(c, buffer, out);
                        }
                        else {
                            buffer[out] = c;
                            out++;
                        }
                        buffer[out] = '(';
                        out++;
                        if (counter / 10) {
                            buffer[out] = '0' + (counter / 10);
                            out++;
                        }
                        buffer[out] = '0' + (counter % 10);
                        out++;
                        buffer[out] = ')';
                        out++;
                }
                else {
                        for (int j = 0; (j < counter && out < in); ++j) {
                            buffer[out] = (*data)[(in - 1)];
                            out++;
                        }
                }
                c = (*data)[in];
                counter = 1;
                if (((*data)[in]) == 0)
                    eof = 1;
            }
            }

        //printf("OUT: %d \n", out);
        for(short it = out; it < LINE_LENGTH; it++) {
            buffer[it] = 0;
        }
    strcpy((*data), buffer);
}

void decompress(char **data){
    char buffer[LINE_LENGTH];
    char first = 0;
    char second = 0;
    short out = 0;
    short counter = 0;
    for (short i = 0; i < LINE_LENGTH; ++i) {
        first = (*data)[i];
        if(first == '%'){
            if((*data)[i+2] == '5')
                first = '%';
            if((*data)[i+2] == '8')
                first = '(';
            if((*data)[i+2] == '9')
                first = ')';
            i += 4;
            if((*data)[i+1] != ')'){
                counter = (10 * ((*data)[i] - '0')) + ((*data)[i+1] - '0');
                i += 2;
            }
            else{
                counter = ((*data)[i] - '0');
                i++;
            }
        }else if((*data)[i+1] == '('){
            i=i+2;
            if((*data)[i+1] != ')'){
                counter = (10 * ((*data)[i] - '0')) + ((*data)[i+1] - '0');
                i+=2;
            }
            else{
                counter = ((*data)[i] - '0');
                i++;
            }
        }else
            counter = 1;
        for (short j = 0; j < counter; ++j) {
            buffer[out] = first;
            out++;
        }
    }
    strcpy((*data), buffer);
}

int main(int argc, char **argv){
    short mode = -1;
    if(argc == 2){
        if(!strcmp(argv[1], "--compress"))
            mode = 1;
        else if(!strcmp(argv[1], "--decompress"))
            mode = 0;
        else{
            printf("Nieprawidłowy argument! Poprawna składnia:\n./zad3 --compress - kompresja danych wejściowych\n./zad3 --decompress - dekompresja danych wejściowych\n");
            return 1;
    }}
    else{
        printf("Nieprawidłowa liczba argumentów! Poprawna składnia:\n./zad3 --compress - kompresja danych wejściowych\n./zad3 --decompress - dekompresja danych wejściowych\n");
        return 1;
    }
    char **data;
    short it = readMany(&data);
    for (short i = 0; i < it; ++i) {
        if(mode)
        compress(&(data[i]));
        else
        decompress(&(data[i]));
    }
    printf("Output:\n");
    for (int j = 0; j < it; ++j) {
        printf("%s", data[j]);
    }
}