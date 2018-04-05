#include <iostream>
#include "User.h"
#include "Appointment.h"

using namespace std;

bool test_authenticate(User*);
bool test_new_name(User*);
bool test_new_password(User*);
bool test_new_phone(User*);
bool test_new_email(User*);
void print(User*);

int main() {
    //User* user = new User("Alex", "1234", "(303)246-7650", "alex.foreman@yahoo.com");
    //User* user = new User();

    Appointment* appointment = new Appointment();

    //if (test_authenticate(user)){ std::cout << "Passed!\n"; }
    //if (test_new_name(user)) { std::cout << "Passed!\n"; }
    //if (test_new_password(user)) { std::cout << "Passed!\n"; }
    //if (test_new_phone(user)) { std::cout<< "Passed!\n"; }
    //if (test_new_email(user)) { std::cout << "Passed!\n"; }
/*
    time_t now = time(0);

    cout << "Number of sec since January 1,1970:" << now << endl;

    tm *ltm = localtime(&now);

    // print various components of tm structure.
    cout << "Year" << 1900 + ltm->tm_year<<endl;
    cout << "Month: "<< 1 + ltm->tm_mon<< endl;
    cout << "Day: "<<  ltm->tm_mday << endl;
    cout << "Time: "<< 1 + ltm->tm_hour << ":";
    cout << 1 + ltm->tm_min << ":";
    cout << 1 + ltm->tm_sec << endl;
*/

    //delete user;
    delete appointment;
    return 0;
}

bool test_authenticate(User* u){
    return u->authenticate_user();
}

bool test_new_name(User* u){
    return u->update_user_name();
}

bool test_new_password(User* u){
    return u->update_user_password();
}

bool test_new_phone(User* u){
    return u->update_user_phone();
}

bool test_new_email(User* u){
    return u->update_user_email();
}
void print(User* u){
    std::cout << *u << std::endl;
}