#include <stdio.h>
#define LATIN ('Z' - 'A' + 1)
#define BUFFER_SIZE 100

short cesarCipher(char data[]){
    for (short i = 0; i < BUFFER_SIZE; ++i) {
        data[i] = 0;
    }
    if(!fgets(data, BUFFER_SIZE, stdin))
        return 0;
    for (short i = 0; (data[i] != '\n' && data[i] != 0); ++i) {
        if(data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + ((data[i] - 'A' + 3) % LATIN);
        }
        if(data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + ((data[i] - 'a' + 3) % LATIN);
        }
    }
    return 1;
}

int main(){
    char buffer[BUFFER_SIZE];
    while(cesarCipher(buffer)){
        printf("%s", buffer);
    }

}
