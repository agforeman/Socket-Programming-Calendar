//
// Created by Tyhhy on 3/29/2018.
//

#include "User.h"


User::User(){
    User::new_user(&(this->__name), &(this->__password), &(this->__phone), &(this->__email));
}

void User::new_user(std::string* nme, std::string* pwd, std::string* phn, std::string* eml){
    std::cout << "Name: ";
    getline(std::cin, *nme);
    std::cout << "\nPassword: ";
    getline(std::cin, *pwd);
    std::cout << "\nPhone: ";
    getline(std::cin, *phn);
    std::cout << "\nEmail: ";
    getline(std::cin, *eml);
}

// GIVES 3 CHANCES, ASKS FOR USER NAME AND PASS IF THEY ARE GOOD THEN RETURN TRUE;
const bool User::authenticate_user() const {
    bool returnValue = false;
    int attemptNumber = 0;
    std::string nme;
    std::string pwd;

    do {
        ++attemptNumber;
        std::cout << "\nUsername: ";
        getline(std::cin, nme);
        std::cout << "\nPassword: ";
        getline(std::cin, pwd);
        returnValue = this->authenticate_user(nme,pwd);
        if(returnValue == false){
            std::cout << "Failed Attempt Number " << attemptNumber << std::endl;
            std::cout << MAX_ATTEMPTS - attemptNumber << " tries left!\n" << std::endl;
        }
    } while (attemptNumber < MAX_ATTEMPTS && returnValue == false);
    return returnValue;
}

const bool User::authenticate_user(const std::string& nme, const std::string& pwd) const {
    if (nme == this->__name && pwd == this->__password) {
        std::cout << "User authenticated sucessfully!" << std::endl;
        return true;
    } else {
        std::cout << "\nInvalid Username or Password\n";
        return false;
    }
}

const bool User::update_user_name() {
    // ASK FOR NEW USER NAME
    // TEST IT IS VALID
    // UPDATE USER NAME
    // RETURN TRUE
}

const bool User::check_new_name_valid(const std::string& newName) const {
    enum States {State1, State2, State3};
    States state = State1;
    // WE will enforce a 64 length
    // Check if alphanumeric possible hyphen alphanumeric
    // check that only 1 word
    if(newName.length() > MAX_NAME_LENGTH){
        std::cout << "Max name length exceeded! Reminder the max name length is " << MAX_NAME_LENGTH << std::endl;
        return false;
    }
    std::string copy = newName;
    // TEST IF STRING IS ALPHANUM AND '-" if so accept
    // While Alphanumeric accept if '-' state 2
    for (std::string::iterator it = copy.begin(); it!=copy.end(); ++it){
        isalnum(atoi((const char*)*it);
    }
        isalnum(atoi((char*)*it));
    std::cout << '\n';
    // reject unless next symbol is alphanumeric state 3
    // Accept if remainder of string is alphanumeric


}

std::ostream& operator<<( std::ostream& output, const User& user) {

    output << "\nUser: " << user.get_user_name()
           << "\nPhone: " << user.get_user_phone()
           << "\nEmail: " << user.get_user_email()
           << std::endl;

    return output;
}

