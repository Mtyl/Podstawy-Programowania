#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#define LINE_LENGTH 100
#define DEFAULT_SIZE 3
//COMPRESSION LIMIT 99
char standard_input[LINE_LENGTH];
short inputPosition = 0;

short ngets(char data[], short length, FILE *stream){
    short counter = 0;
    char c = standard_input[inputPosition];//getc(stream);
    inputPosition++;
    while((counter < length) && (c != -1/*EOF*/)){
        data[counter] = c;
        counter++;
        c = standard_input[inputPosition];//getc(stream);
        inputPosition++;
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

void testAscii(){
    char result[3];
    result[2] = 0;
    asciiToHex('%', result, 0);
    CU_ASSERT_STRING_EQUAL(result, "25");
    asciiToHex('(', result, 0);
    CU_ASSERT_STRING_EQUAL(result, "28");
    asciiToHex(')', result, 0);
    CU_ASSERT_STRING_EQUAL(result, "29");
}

void testRead(){
    char **data;
    strcpy(standard_input, "aaaaa00bbbbb00%%%%%");
    standard_input[5] = 0;
    standard_input[6] =  -1;
    standard_input[12] = 0;
    standard_input[13] =  -1;
    standard_input[19] = 0;
    standard_input[20] =  -1;
    standard_input[21] =  -1;
    short a = readMany(&data);
    CU_ASSERT_STRING_EQUAL(data[0], "aaaaa");
    CU_ASSERT_STRING_EQUAL(data[1], "bbbbb");
    CU_ASSERT_STRING_EQUAL(data[2], "%%%%%");
}

void testCompress(){
    char *data;
    data = malloc(LINE_LENGTH*sizeof(*data));
    strcpy(data, "(%)(%)(%)(%)(%)");
    compress(&data);
    CU_ASSERT_STRING_EQUAL(data, "%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)");
    strcpy(data, "aaaabbbbbbbbbb");
    compress(&data);
    CU_ASSERT_STRING_EQUAL(data, "aaaab(10)");
    strcpy(data, "10000000000");
    compress(&data);
    CU_ASSERT_STRING_EQUAL(data, "10(10)");
}

void testDecompress(){
    char *data;
    data = malloc(LINE_LENGTH*sizeof(*data));
    strcpy(data, "%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)%28(1)%25(1)%29(1)");
    decompress(&data);
    CU_ASSERT_STRING_EQUAL(data, "(%)(%)(%)(%)(%)");
    strcpy(data, "aaaab(10)");
    decompress(&data);
    CU_ASSERT_STRING_EQUAL(data, "aaaabbbbbbbbbb");
    strcpy(data, "10(10)");
    decompress(&data);
    CU_ASSERT_STRING_EQUAL(data, "10000000000");
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", 0,0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of asciiToHex()", testAscii)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of readMany()", testRead)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of compress()", testCompress)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of decompress()", testDecompress)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}