#include "../header/main.h"

void getMonth(int type) {
    switch(type) {
        case 1:
            printf("Jan ");
            break;
        case 2:
            printf("Feb ");
            break;
        case 3:
            printf("Mar ");
            break;
        case 4:
            printf("Apr ");
            break;
        case 5:
            printf("May ");
            break;
        case 6:
            printf("Jun ");
            break;
        case 7:
            printf("Jul ");
            break;
        case 8:
            printf("Aug ");
            break;
        case 9:
            printf("Sep ");
            break;
        case 10:
            printf("Oct ");
            break;
        case 11:
            printf("Nov ");
            break;
        case 12:
            printf("Dec ");
            break;
        default:
            break;
    }
}

void getWeekday(int type) {
    switch(type) {
        case 0:
            printf("Sun ");
            break;
        case 1:
            printf("Mon ");
            break;
        case 2:
            printf("Tue ");
            break;
        case 3:
            printf("Wed ");
            break;
        case 4:
            printf("Thu ");
            break;
        case 5:
            printf("Fri ");
            break;
        case 6:
            printf("Sat ");
            break;
        default:
            break;
    }
}

void getToday(Date *date) {
    time(&ltime);
    today = localtime(&ltime);

    date->weekday = today->tm_wday;
    date->month = today->tm_mon + 1;
    date->day = today->tm_mday;
    date->hour = today->tm_hour;
    date->minute = today->tm_min;
    date->second = today->tm_sec;
    date->year = today->tm_year + 1900;
}