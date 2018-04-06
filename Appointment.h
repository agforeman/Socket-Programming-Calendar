//
// Created by Tyhhy on 4/4/2018.
//

#ifndef TEST_APPOINTMENTS_H
#define TEST_APPOINTMENTS_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

#define APPOINTMENT_TITLE_MAX_LENGTH 32
#define APPOINTMENT_TITLE_MIN_LENGTH 8
#define APPOINTMENT_LOCATION_DEFAULT "NO LOCATION"
#define APPOINTMENT_CONTENTS_DEFAULT "NO CONTENTS"
#define APPOINTMENT_TITLE_DEFAULT "NO TITLE"
#define APPOINTMENT_TIME_HOUR_DEFAULT 0
#define APPOINTMENT_TIME_MINUTE_DEFAULT 0
#define APPOINTMENT_DATE_DAY_DEFAULT 1
#define APPOINTMENT_DATE_MONTH_DEFAULT 1
#define APPOINTMENT_DATE_YEAR_DEFAULT 1990

typedef struct {
    std::size_t __hour;
    std::size_t __minute;
} apmtTime;

typedef struct {
    std::size_t __day;
    std::size_t __month;
    std::size_t __year;
} apmtDate;

typedef std::pair<apmtTime, apmtDate> datetime;

class Appointment {
private:
    std::string __title;
    datetime __start;
    datetime __end;
    std::string __location;
    std::string __contents;

    const bool new_appointment(std::string*, datetime&, datetime&, std::string*, std::string*);
public:
    Appointment();

    const bool update_appointment_date(char, apmtDate&);
    const bool update_appointment_time(char, apmtTime&);
    const bool update_appointment_title(std::string*);
    const bool update_appointment_location(std::string*);
    const bool update_appointment_contents(std::string*);
    const bool check_title_valid(const std::string*) const;
    const bool check_date_valid(const std::string*, char) const;
    const bool check_date_valid(const std::string*, char, std::pair<std::string, std::string>*) const;
    const bool check_time_valid(const std::string&, char) const;
    const bool is_leap_year(const std::string*) const;

    const bool is_numeric(const char*) const;

};


#endif //TEST_APPOINTMENTS_H
