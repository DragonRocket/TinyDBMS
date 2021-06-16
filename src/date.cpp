#include "cdate"

Date::Date() : day(1), month(1), year(1) {}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
    this->year = 1 > year ? 1 : year; //max(1, year);

    this->month = 1 > month ? 1 : month;               //max(1, month);
    this->month = this->month < 12 ? this->month : 12; //min(month, 12);

    static unsigned int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (__isleap(this->year))
        length[2] = 29;

    this->day = 1 > day ? 1 : day;                                                 //max(1, day);
    this->day = this->day < length[this->month] ? this->day : length[this->month]; //min(day, length[month]);
}

void Date::setDate(unsigned int day, unsigned int month, unsigned int year)
{
    this->year = 1 > year ? 1 : year; //max(1, year);

    this->month = 1 > month ? 1 : month;               //max(1, month);
    this->month = this->month < 12 ? this->month : 12; //min(month, 12);

    static unsigned int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (__isleap(year))
        length[2] = 29;

    this->day = 1 > day ? 1 : day;                                                 //max(1, day);
    this->day = this->day < length[this->month] ? this->day : length[this->month]; //min(day, length[month]);
}

void Date::setDay(unsigned int day)
{
    static unsigned int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    this->day = 1 > day ? 1 : day;                                     //max(1, day);
    this->day = this->day < length[month] ? this->day : length[month]; //min(day, length[month]);
}

void Date::setMonth(unsigned int month)
{
    this->month = 1 > month ? 1 : month;               //max(1, month);
    this->month = this->month < 12 ? this->month : 12; //min(month, 12);
}

void Date::setYear(unsigned int year)
{
    this->year = 1 > year ? 1 : year; //max(1, year);
}

unsigned int Date::getDay()
{
    return day;
}

unsigned int Date::getMonth()
{
    return month;
}

unsigned int Date::getYear()
{
    return year;
}

void Date::showDate()
{
    cout << day << "/" << month << "/" << year;
}
