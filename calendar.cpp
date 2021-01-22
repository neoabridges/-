#include<iostream>
#include<conio.h>
#include<malloc.h>
using namespace std;
const int leap_years[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int normal_years[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
bool is_leap_year(int);
int what_day(int, int, int);
void create_calendar(int, int, int(*days)[7]);
void print_calendar(int(*days)[7], int year, int month);
void continuous_calendar(int year, int month);
int main()
{
    int days[7][7] = { 0 };
    int iyear, imonth;
    cout << "please input the year and the month you want to know: " << endl;
    cin >> iyear >> imonth;
    //cout << what_day(iyear, imonth, 0);
    create_calendar(iyear, imonth, days);   
    continuous_calendar(iyear, imonth);
    return 0;
}
void continuous_calendar(int year, int month)
{
    char curr = _getche();
    for (curr = _getche(); curr >= 72 && curr <= 80; curr = _getche()) {
        int(*days)[7] = (int(*)[7]) malloc(sizeof(int) * 49);
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                days[i][j] = { 0 };
            }
        }
        system("cls");
        if (curr == 72) {
            if (--month <= 0) 
                month += 12;
            create_calendar(year, month, days);
        }
        else if (curr == 80) {
            if (++month > 12)
                month -= 12;
            create_calendar(year, month, days);
        }
        else if (curr == 75) {
            create_calendar(--year, month, days);
        }
        else if (curr == 77) {
            create_calendar(++year, month, days);
        }
        curr = _getche();
    }
}
void create_calendar(int year, int month, int(*days)[7])
{
    int weekday = what_day(year, month, 0);
    int max_day;
    if (is_leap_year(year)) {
        max_day = leap_years[month - 1];
    }
    else {
        max_day = normal_years[month - 1];
    }
    int day = 1;
    for (int i = 0; i < 7 && day <= max_day; i++) {
        for (; weekday < 7 && day <= max_day; weekday++) {
            days[i][weekday] = day;
            day++;
        }
        weekday = 0;
    }
    print_calendar(days, year, month);
}
void print_calendar(int(*days)[7], int year, int month)
{
    printf("\tYEAR: %d\t\tMONTH: %d\n\n\n", year, month);
    printf("SUN\tMON\tTUE\tWEN\tTHU\tFRI\tSAT\n\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (days[i][j]) {
                cout << days[i][j] << '\t';
            }
            else {
                cout << '\t';
            }
        }
        cout << endl;
    }
}
int what_day(int year, int month, int day)
{
    int weekday;
    int c = year / 100, y = year % 100;
    if (month == 1) {
        year -= 1;
        month = 13;
    }
    else if (month == 2) {
        year -= 1;
        month = 14;
    }
    weekday = ((c / 4) - 2 * c + y + (y / 4) + (26 * (month + 1) / 10) + day - 1) % 7;
    if (weekday < 0) {
        weekday += 7;
    }
    return weekday;
}
bool is_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0) {
        return true;
    }
    else if (year % 400 == 0) {
        return true;
    }
    return false;
}