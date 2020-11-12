
#include <CUnit/Basic.h>
#define LATIN ('Z' - 'A' + 1)
#define BUFFER_SIZE 100

short ffgets(char *s, int size){
    static short i = 0;
    switch(i){
        case 0:
            sprintf(s, "to be or not to be");
            break;
        case 1:
            sprintf(s, "ala ma kota");
            break;
        case 2:
            sprintf(s, "abcdefghijklmnopqrstuvwxyz");
            break;
        case 3:
            sprintf(s, " a b c d e f g h i j k l m n o p q r s t u v w x y z");
            break;
    }
    i++;
    return 1;
}

short cesarCipher(char data[]){
    for (short i = 0; i < BUFFER_SIZE; ++i) {
        data[i] = 0;
    }
    if(!ffgets(data, BUFFER_SIZE))
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

void testCesar(){
    char result[BUFFER_SIZE];

    cesarCipher(result);
    CU_ASSERT_STRING_EQUAL(result, "vq dg qt pqv vq dg");

    cesarCipher(result);
    CU_ASSERT_STRING_EQUAL(result, "dod pd nrwd");

    cesarCipher(result);
    CU_ASSERT_STRING_EQUAL(result, "abcdefghijklmnopqrstuvwxyz");

    cesarCipher(result);
    CU_ASSERT_STRING_EQUAL(result, " b c d e f g h i j k l m n o p q r s t u v w x y z a");
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
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of cesarCipher()", testCesar)))
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
