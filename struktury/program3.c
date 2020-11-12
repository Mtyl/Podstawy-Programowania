#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum days {MON,TUE,WED,THU,FRI,SAT,SUN} Day;
typedef enum actions {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;
short n;
struct limits_struct{
    Day firstDay;
    Day lastDay;
    int firstHour;
    int lastHour;
    int lastDayHour;
} limits = {MON, FRI, 8, 20, 17};

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

typedef struct term_defition_here {
    int hour;
    int minute;
    int duration;
    Day day;
} Term;

void Term__init(Term *term, int hour, int minute, int duration, Day day){
    term->minute = minute;
    term->hour =  hour;
    term->duration = duration;
    term->day = day;
}

Term* Term__create(int hour, int minute, int duration, Day day){
    Term *term =  malloc(sizeof(Term));
    Term__init(term, hour, minute, duration, day);
}

void Term__destroy(Term *term){
    free(term);
}

char* Term__toString(Term *term){
    char *result = malloc((strlen(Day__toString(term->day))+13)*sizeof(*result));
    strcpy(result, Day__toString(term->day));
    char c = strlen(result);
    result[c++] = ' ';
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
    if(term1->day < term2->day)
        return true;
    else if(term1 -> day == term2-> day && term1->hour < term2->hour)
        return true;
    else if(term1 -> day == term2-> day && term1->hour == term2->hour && term1->minute < term2->minute)
        return true;
    return false;
}

bool Term__laterThan(Term *term1, Term *term2){
    if(term1->day > term2->day)
        return true;
    else if(term1 -> day == term2-> day && term1->hour > term2->hour)
        return true;
    else if(term1 -> day == term2-> day && term1->hour == term2->hour && term1->minute > term2->minute)
        return true;
    return false;
}

bool Term__equals(Term *term1, Term *term2){
    if(term1->day == term2-> day && term1->hour == term2->hour && term1->minute == term2->minute)
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

typedef struct lesson_def_here {
    Term *term;
    char *name;
} Lesson;

void Lesson__init(Lesson *lesson, int hour, int minute, int duration, Day day, char* name){
    lesson->name = malloc(strlen(name)*sizeof(char));
    strcpy(lesson->name, name);
    Term__init(lesson->term, hour, minute, duration, day);
}

Lesson* Lesson__create(int hour, int minute, int duration, Day day, char* name){
    Lesson *lesson = malloc(sizeof(lesson));
    lesson->term = Term__create(hour, minute, duration, day);
    lesson->name = malloc(strlen(name)*sizeof(*name));
    strcpy(lesson->name, name);
    return lesson;
}

void Lesson__destroy(Lesson *lesson){
    free(lesson->name);
    Term__destroy(lesson->term);
    free(lesson);
}

bool Lesson__termValidate(Lesson *lesson){
    int endHour = lesson->term->hour + ((lesson->term->duration + lesson->term->minute) / 60);
    int endMinute = (lesson->term->duration + lesson->term->minute) % 60;
    if(lesson->term->day >= MON && lesson->term->day < FRI){
        if((lesson->term->hour > 8 || (lesson->term->hour==8 && lesson->term->minute >= 0)) && (endHour < 20 || (endHour == 20 && endMinute <= 0)))
            return true;
        return false;
    }
    else if(lesson->term->day == FRI){
        if((lesson->term->hour > 8 || (lesson->term->hour==8 && lesson->term->minute >= 0)) && (endHour < 17 || (endHour == 17 && endMinute <= 0)))
            return true;
        return false;
    }
    return false;
}

void Lesson__earlierDay(Lesson *lesson){
    lesson->term->day = Day__prevDay(lesson->term->day);
    printf("Dzień w tył\n");
    if(!Lesson__termValidate(lesson)) {
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
        lesson->term->day = Day__nextDay(lesson->term->day);
    }
}

void Lesson__laterDay(Lesson *lesson){
    lesson->term->day = Day__nextDay(lesson->term->day);
    printf("Dzień w przód\n");
    if(!Lesson__termValidate(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
        lesson->term->day = Day__prevDay(lesson->term->day);
    }
}

void Lesson__earlierTime(Lesson *lesson){
    lesson->term->hour += (lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
    lesson->term->minute = (lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
    printf("Termin w tył\n");
    if(!Lesson__termValidate(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
        lesson->term->hour += (lesson->term->duration + lesson->term->minute) / 60;
        lesson->term->minute = (lesson->term->duration + lesson->term->minute) % 60;
    }
}

void Lesson__laterTime(Lesson *lesson){
    lesson->term->hour += (lesson->term->duration + lesson->term->minute) / 60;
    lesson->term->minute = (lesson->term->duration + lesson->term->minute) % 60;
    printf("Termin w przód\n");
    if(!Lesson__termValidate(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
        lesson->term->hour += (lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
        lesson->term->minute = (lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
    }
}

char* Lesson__toString(Lesson *lesson){
    char *output = malloc(50 * sizeof(*output));
    strcpy(output, lesson->name);
    strcat(output, ", ");
    strcat(output, Term__toString(lesson->term));
    return output;
}

int main(int argc, char **argv) {
    Lesson *lesson = Lesson__create(12, 50, 90, WED, "Podstawy programowania");
    printf("Przed uwzględnieniem przesunięć\n");
    printf("\t\"%s\"\n", Lesson__toString(lesson));
    n = (short) argc - 1;
    argv = argv + 1;
    Action *order = parse(argv);
    for (short i = 0; i < n; ++i) {
        switch (order[i]) {
            case DAY_EARLIER:
                Lesson__earlierDay(lesson);
                break;
            case DAY_LATER:
                Lesson__laterDay(lesson);
                break;
            case TIME_EARLIER:
                Lesson__earlierTime(lesson);
                break;
            case TIME_LATER:
                Lesson__laterTime(lesson);
                break;
        }

    }
    printf("Po uwzględnieniu przesunięć\n");
    printf("\t\"%s\"\n", Lesson__toString(lesson));
}