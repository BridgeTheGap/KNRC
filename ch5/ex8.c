static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year % 400 == 0;

    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (day > 31) { 
            return -1;
        }
        break;
    case 2:
        if (leap && day > 29) {
            return -1;
        } else if (!leap && day > 28) {
            return -1;
        }
        break;
    case 4: case 6: case 9: case 11:
        if (day > 30) {
            return -1;
        }
        break;
    default:
        return -1;
    }
    
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if ((leap && yearday > 366) || (!leap && yearday > 365)) {
        *pmonth = -1;
        *pday = -1;
    }

    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}
