#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#define STRL 13

typedef struct term_defition_here {
    int hour;
    int minute;
    int duration;
} Term;

Term **terms;

void Term__init(Term *term, int hour, int minute, int duration){
    term->minute = minute;
    term->hour =  hour;
    term->duration = duration;
}

Term* Term__create(int hour, int minute, int duration){
    Term *term =  malloc(sizeof(Term));
    Term__init(term, hour, minute, duration);
}

void Term__destroy(Term *term){
    free(term);
}

char* Term__toString(Term *term){
    char *result = malloc(STRL*sizeof(*result));
    char c = 0;
    if(term->hour/10)
        result[c++] = '0' + (term->hour / 10);
    result[c++] = '0' + term->hour % 10;
    result[c++] = ':';
    result[c++] = '0' + term->minute / 10;
    result[c++] = '0' + term->minute % 10;
    result[c++] = ' ';
    result[c++] = '[';
    if(term->duration/100)
        result[c++] = '0' + term->duration/100;
    if((term->duration/10) % 10 )
        result[c++] = '0' + (term->duration/10) % 10;
    result[c++] = '0' + term->duration % 10;
    result[c++] = ']';
    result[c] = 0;
    return result;
}

bool Term__earlierThan(Term *term1, Term *term2){
    if(term1->hour < term2->hour)
        return true;
    else if(term1->hour == term2->hour && term1->minute < term2->minute)
        return true;
    return false;
}

bool Term__laterThan(Term *term1, Term *term2){
    if(term1->hour > term2->hour)
        return true;
    else if(term1->hour == term2->hour && term1->minute > term2->minute)
        return true;
    return false;
}

bool Term__equals(Term *term1, Term *term2){
    if(term1->hour == term2->hour && term1->minute == term2->minute)
        return true;
    return false;
}

Term* Term__endTerm(Term *term1, Term *term2){
    Term *term = malloc(sizeof(Term));
    term->hour = term1->hour;
    term->minute = term1->minute;
    int duration = (term2->hour - term1->hour)*60;
    duration += term2->minute - term1->minute;
    term->duration = duration > 0 ? duration : 0;
    return term;
}

void testCreate(){
    terms = malloc(3 * sizeof(*terms));
    terms[0] = Term__create(9, 30, 90);
    terms[1] = Term__create(10, 15, 120);
    terms[2] = Term__create(12, 45, 30);
    CU_ASSERT_EQUAL(terms[0]->hour, 9);
    CU_ASSERT_EQUAL(terms[1]->hour, 10);
    CU_ASSERT_EQUAL(terms[2]->hour, 12);
}

void testInit(){
    Term termstable[3];
    Term__init(&termstable[0], 9, 12, 15);
    Term__init(&termstable[1], 10, 13, 16);
    Term__init(&termstable[2], 17, 21, 39);
    CU_ASSERT_EQUAL(termstable[0].hour, 9);
    CU_ASSERT_EQUAL(termstable[1].minute, 13);
    CU_ASSERT_EQUAL(termstable[2].duration, 39);
}

void testString(){
    CU_ASSERT_STRING_EQUAL(Term__toString(terms[0]), "9:30 [90]");
    CU_ASSERT_STRING_EQUAL(Term__toString(terms[1]), "10:15 [120]");
    CU_ASSERT_STRING_EQUAL(Term__toString(terms[2]), "12:45 [30]");
}

void testEarlier(){
    CU_ASSERT_TRUE(Term__earlierThan(terms[0], terms[1]));
    CU_ASSERT_TRUE(Term__earlierThan(terms[1], terms[2]));
    CU_ASSERT_FALSE(Term__earlierThan(terms[2], terms[0]));
}

void testLater(){
    CU_ASSERT_TRUE(Term__laterThan(terms[1], terms[0]));
    CU_ASSERT_TRUE(Term__laterThan(terms[2], terms[0]));
    CU_ASSERT_FALSE(Term__laterThan(terms[1], terms[2]));
}

void testEqual(){
    CU_ASSERT_TRUE(Term__equals(terms[0], terms[0]));
    CU_ASSERT_TRUE(Term__equals(terms[1], terms[1]));
    CU_ASSERT_FALSE(Term__equals(terms[2], terms[0]));
}

void testEnd(){
    Term *tester = Term__endTerm(terms[1], terms[2]);
    CU_ASSERT_EQUAL(tester->duration, 150);
    CU_ASSERT_EQUAL(tester->hour, 10);
    CU_ASSERT_EQUAL(tester->minute, 15);
    free(tester);
    tester = Term__endTerm(terms[1], terms[2]);
    CU_ASSERT_EQUAL(tester->duration, 45);
    CU_ASSERT_EQUAL(tester->hour, 9);
    CU_ASSERT_EQUAL(tester->minute, 30);
}

int main()
{

    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Terms", 0,0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__init()", testInit)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__create()", testCreate)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__toString()", testString)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__earlierThan()", testEarlier)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__laterThan()", testLater)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of Term__equals()", testEqual)))
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
