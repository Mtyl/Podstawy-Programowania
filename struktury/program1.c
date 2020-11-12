#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum days {MON,TUE,WED,THU,FRI,SAT,SUN} Day;
typedef enum actions {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;
short n;

char* Day__toString(Day day){
    static const char days[7][13] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
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

int main(int argc, char **argv){
    n = (short)argc - 2;
    if(argc < 2){
        printf("Podaj dzień tygodnia i argumenty\n");
        return 0;}
    Day day = Day__fromString(argv[1]);
    argv = argv + 2;
    Action *order = parse(argv);
    for (short i = 0; i < n; ++i) {
        switch(order[i]){
            case DAY_EARLIER:
                printf("Dzień w tył\n");
                day = Day__prevDay(day);
                break;
            case DAY_LATER:
                printf("Dzień w przód\n");
                day = Day__nextDay(day);
                break;
            case TIME_EARLIER:
                printf("Termin w tył\n");
                break;
            case TIME_LATER:
                printf("Termin w przód\n");
                break;
        }

    }
    printf("Wynik przesunięcia: \"%s\"\n", Day__toString(day));
    return 0;
}
