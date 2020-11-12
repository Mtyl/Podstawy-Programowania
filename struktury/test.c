
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum days {MON,TUE,WED,THU,FRI,SAT,SUN} Day;
typedef enum actions {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;
short n;

char* Day__toString(Day day){
    static const char days[7][15] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    return (char *)days[day];
}

Day Day__nextDay(Day day){
    if(day == SUN)
        return MON;
    else
        return day + 1;
}

Day Day__prevDay(Day day){
    if(day == MON)
        return SUN;
    else
        return day - 1;
}

Day Day__fromString(char *str){
    if(!strcmp(str,"Mon"))
        return MON;
    else if(!strcmp(str,"Tue"))
        return TUE;
    else if(!strcmp(str,"Wed"))
        return WED;
    else if(!strcmp(str,"Thu"))
        return THU;
    else if(!strcmp(str,"Fri"))
        return FRI;
    else if(!strcmp(str,"Sat"))
        return SAT;
    else
        return SUN;
}

Action* parse(char *tablica[]){
    Action *out = malloc(n * sizeof(*out));
    short c = 0;
    for (short i = 0; i < n; ++i) {
        if(!strcmp(tablica[i], "d+"))
            out[c] = DAY_LATER;
        else if(!strcmp(tablica[i], "d-"))
            out[c] = DAY_EARLIER;
        else if(!strcmp(tablica[i], "t-"))
            out[c] = TIME_EARLIER;
        else if(!strcmp(tablica[i], "t+"))
            out[c] = TIME_LATER;
        else
            c--;
        c++;
    }
    n = c;
    if(c>0)
        out = realloc(out, c * sizeof(*out));
    else
        return 0;
    return out;
}

Day day__pushMany(Action *actions, Day day) {
    for (short i = 0; i < n; ++i) {
        switch (actions[i]) {
            case DAY_EARLIER:
                day = Day__prevDay(day);
                break;
            case DAY_LATER:
                day = Day__nextDay(day);
                break;
            case TIME_EARLIER:
                break;
            case TIME_LATER:
                break;
        }
    }
    return day;
}
void testParse(){
    n = 3;
    char *argss[] = {"d+", "d+", "t+"};
    CU_ASSERT_EQUAL(day__pushMany(parse(argss), Day__fromString("Mon")), WED);
    argss[0] = "d+";
    argss[1] = "asdfg";
    argss[2] = "d-";
    CU_ASSERT_EQUAL(day__pushMany(parse(argss), Day__fromString("Wed")), WED);
    argss[0] = "d+";
    argss[1] = "asdfg";
    argss[2] = "d+";
    n = 3;
    CU_ASSERT_EQUAL(day__pushMany(parse(argss), Day__fromString("Sat")), MON);

}

void testString(){
    CU_ASSERT_STRING_EQUAL(Day__toString(MON), "Poniedziałek");
    CU_ASSERT_STRING_EQUAL(Day__toString(TUE), "Wtorek");
    CU_ASSERT_STRING_EQUAL(Day__toString(WED), "Środa");
}

void testDayNext(){
    CU_ASSERT_EQUAL(WED, Day__nextDay(TUE));
    CU_ASSERT_EQUAL(MON, Day__nextDay(SUN));
}

void testDayPrev(){
    CU_ASSERT_EQUAL(WED, Day__prevDay(THU));
    CU_ASSERT_EQUAL(SUN, Day__prevDay(MON));
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

    if ((NULL == CU_add_test(pSuite, "test of day__nextDay", testDayNext)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "test of day__prevDay", testDayPrev)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "test of day__toString", testString)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of parse()", testParse)))
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
