//
// Created by Tyhhy on 4/4/2018.
//

#include "Appointment.h"



Appointment::Appointment() {
    bool success = false;
    __title = APPOINTMENT_TITLE_DEFAULT;
    __location = APPOINTMENT_LOCATION_DEFAULT;
    __contents = APPOINTMENT_CONTENTS_DEFAULT;
    __start.first.__hour = APPOINTMENT_TIME_HOUR_DEFAULT;
    __start.first.__minute = APPOINTMENT_TIME_MINUTE_DEFAULT;
    __start.second.__day = APPOINTMENT_DATE_DAY_DEFAULT;
    __start.second.__month = APPOINTMENT_DATE_MONTH_DEFAULT;
    __start.second.__year = APPOINTMENT_DATE_YEAR_DEFAULT;
    __end.first.__hour = APPOINTMENT_TIME_HOUR_DEFAULT;
    __end.first.__minute = APPOINTMENT_TIME_MINUTE_DEFAULT;
    __end.second.__day = APPOINTMENT_DATE_DAY_DEFAULT;
    __end.second.__month = APPOINTMENT_DATE_MONTH_DEFAULT;
    __end.second.__year = APPOINTMENT_DATE_YEAR_DEFAULT;
    do {
        success = Appointment::new_appointment(&(this->__title), this->__start, this->__end, &(this->__location), &(this->__contents));
    } while(!success);
}

const bool Appointment::new_appointment(std::string* title, datetime& start, datetime& end, std::string* location, std::string* contents){
    bool success = true;
    success = success && update_appointment_title(title);
    success = success && update_appointment_date('S', start.second);
    success = success && update_appointment_time('S', start.first);
    success = success && update_appointment_date('E', end.second);
    success = success && update_appointment_time('E', end.first);
    success = success && update_appointment_location(location);
    success = success && update_appointment_contents(contents);
    return success;
}

const bool Appointment::update_appointment_date(const char mode, apmtDate& date) {
    if (mode != 'S' && mode != 'E') return false;
    bool valid = false;
    std::string day;
    std::string month;
    std::string year;
    std::pair<std::string, std::string> monyr;
    do {
        std::cout << "Month: ";
        getline(std::cin, month);
        valid = check_date_valid(&month, 'M');
        if(!valid) continue;
        monyr.first = month;

        std::cout << "Year: ";
        getline(std::cin, year);
        valid = check_date_valid(&year, 'Y');
        if(!valid) continue;
        monyr.second = year;

        std::cout << "Day: ";
        getline(std::cin, day);
        valid = check_date_valid(&day, 'D', &monyr);
    } while (!valid);
    size_t numericDay = (std::size_t)atoi(day.c_str());
    size_t numericMonth = (std::size_t)atoi(month.c_str());
    size_t numericYear = (std::size_t)atoi(year.c_str());
    date.__day = numericDay;
    date.__month = numericMonth;
    date.__year = numericYear;
    return true;
}

const bool Appointment::update_appointment_time(const char mode, apmtTime& time) {
    if (mode != 'S' && mode != 'E') return false;
    bool valid = false;
    std::string hour;
    std::string minute;
    // ASK FOR HOUR
    do {
        std::cout << "HOUR: ";
        getline(std::cin, hour);
        valid = check_time_valid(hour,'H');
    } while (!valid);
    valid = false;
    do {
        std::cout << "MINUTE: ";
        getline(std::cin, minute);
        valid = check_time_valid(minute,'M');
    } while (!valid);
    apmtTime temp = {(std::size_t)atoi(hour.c_str()),(std::size_t)atoi(minute.c_str())};
    time = temp;
    return valid;
}

const bool Appointment::update_appointment_title(std::string* title) {
    bool valid = false;
    std::string temp;
    do{
        std::cout << "Title: ";
        getline(std::cin, temp);
        valid = check_title_valid(&temp);
    } while (!valid);
    *title = temp;
    return valid;
}

const bool Appointment::update_appointment_location(std::string* location) {
    std::string temp;
    std::cout << "Location: ";
    getline(std::cin, temp);
    if(temp.length() == 0) *location = APPOINTMENT_LOCATION_DEFAULT;
    else *location = temp;
    return true;
}

const bool Appointment::update_appointment_contents(std::string* contents) {
    std::string temp;
    std::cout << "Contents: ";
    getline(std::cin, temp);
    if(temp.length() == 0) *contents = APPOINTMENT_CONTENTS_DEFAULT;
    else *contents = temp;
    return true;
}

const bool Appointment::check_title_valid(const std::string* title) const {
    if (title == NULL) return false;
    return title->length() >= APPOINTMENT_TITLE_MIN_LENGTH && title->length() <= APPOINTMENT_TITLE_MAX_LENGTH;
}

const bool Appointment::check_date_valid(const std::string* value, const char mode) const {
    if (mode != 'D' && mode != 'M' && mode != 'Y') return false;
    if (!is_numeric(value->c_str())) return false;
    if (mode == 'Y') {
        return value->length() == 4 && is_numeric(value->c_str());
    } else if (mode == 'M') {
        std::size_t month = (std::size_t)atoi(value->c_str());
        return month > 0 && month <= 12;
    } else {
        return false;
    }
}

const bool Appointment::check_date_valid(const std::string* value, const char mode, std::pair<std::string, std::string>* mmyyyy) const{
    if (!is_numeric(value->c_str())) return false;
    std::size_t day = (std::size_t)atoi(value->c_str());
    bool isLeap = is_leap_year(&mmyyyy->second);
    std::size_t month = (std::size_t)atoi((mmyyyy->first).c_str());

    if(month % 2 == 1){
        return day == 31;
    } else if(month == 2) {
        if(isLeap) return day == 29;
        else return day == 28;
    } else {
        return day == 30;
    }
}

const bool Appointment::check_time_valid(const std::string& testString, const char mode) const {
    // TIME HAS TO BE 2 characters and 0-23:0-59
    const char* temp = testString.c_str();

    if(!is_numeric(temp)) return false;

    const int val = atoi(temp);
    if(mode == 'H') {
        return val < 24 && val >= 0;
    } else if (mode == 'M' ) {
        return val < 60 && val >= 0;
    } else {
        return false;
    }
}

const bool Appointment::is_numeric(const char *string) const {
    std::size_t sizeOfString = strlen(string);
    int iteration = 0;
    bool isNumeric = true;

    while (iteration < sizeOfString) {
        if (!isdigit(string[iteration])) {
            isNumeric = false;
            break;
        }
        iteration++;
    }
    return isNumeric;
}

const bool Appointment::is_leap_year(const std::string* year) const {
    std::size_t numericYear = (std::size_t)atoi(year->c_str());
    if(numericYear % 4 == 0) {
        if(numericYear % 100 == 0){
            if(numericYear % 400 == 0){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}