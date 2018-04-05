//
// Created by Tyhhy on 3/29/2018.
//

#include "User.h"


User::User(){
    bool success = false;
    do {
        success = User::new_user(&(this->__name), &(this->__password), &(this->__phone), &(this->__email));
    } while (!success);
}

const bool User::new_user(std::string* nme, std::string* pwd, std::string* phn, std::string* eml){
    bool success = true;
    success = success && update_user_name();
    success = success && update_user_password();
    success = success && update_user_phone();
    success = success && update_user_email();
    return success;
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
    bool valid;
    std::string newName;
    // ASK FOR NEW USER NAME
    do {
        std::cout << "New name: ";
        getline(std::cin, newName);
        // TEST IT IS VALID
        valid = check_new_name_valid(newName);
        if(!valid){
            std::cout << "Sorry invalid input" << std::endl;
        }
    } while(!valid);

    this->__name = newName;
    std::cout << "User Name Updated" << std::endl;
    return true;
}

const bool User::check_new_name_valid(const std::string& newName) const {

    User::States state = State0;
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
        //isalnum returns NON-0(int) if true else returns 0 if false
        int intCastedChar = static_cast<int>(*it);
        int notAlNum = isalnum(intCastedChar);
        if(notAlNum == 0 && *it != '-') {
            return false;
        }
        else if (notAlNum != 0) {
            if(state == State0) state = State1;
            else if (state == State2) state = State3;
        }
        else if (*it == '-'){
            if (state == State1) state = State2;
            else return false; }
    }
    return state == State1 || state == State3;
}

const bool User::update_user_password(){
    bool valid;
    std::string newPassword;

    do {
        std::cout << "New password: ";
        getline(std::cin, newPassword);
        // TEST IT IS VALID
        valid = check_new_password_valid(newPassword);
        if(!valid){
            std::cout << "Sorry invalid input" << std::endl;
        }
    } while(!valid);

    this->__password = newPassword;
    std::cout << "User Password Updated to " << this->__password << std::endl;
    return true;
}

const bool User::check_new_password_valid(const std::string &newPassword) const {
    if(newPassword.length() > MAX_PASSWORD_LENGTH || newPassword.length() < MIN_PASSWORD_LENGTH) return false;
    std::string copy = newPassword;
    for (std::string::iterator it = copy.begin(); it != copy.end(); ++it){
        if(isalnum(static_cast<int>(*it)) == 0) return false;
    }
    return true;
}

const bool User::update_user_phone(){
    bool valid;
    std::string newPhone;

    do {
        std::cout << "New phone: ";
        getline(std::cin, newPhone);
        // TEST IT IS VALID
        valid = check_new_phone_valid(newPhone);
        if(!valid){
            std::cout << "Sorry invalid input" << std::endl;
        }
    } while(!valid);
    this->__phone = newPhone;
    std::cout << "User Phone Updated" << std::endl;
    return true;
}

const bool User::check_new_phone_valid(const std::string &newPhone) const {
    if(newPhone.length() != PHONE_NUMBER_LENGTH) return false;

    std::string copy = newPhone;

    if(copy[0] != '(' || copy[4] != ')' || copy[8] != '-') return false;

    copy.erase (copy.begin());
    copy.erase (copy.begin()+3);
    copy.erase(copy.begin()+6);

    for(std::string::iterator it = copy.begin(); it != copy.end(); ++it){
        if(isdigit(static_cast<int>(*it)) == 0) return false;
    }
    return true;
}

const bool User::update_user_email() {
    bool valid;
    std::string newEmail;
    // ASK FOR NEW USER NAME
    do {
        std::cout << "New email: ";
        getline(std::cin, newEmail);
        // TEST IT IS VALID
        valid = check_new_email_valid(newEmail);
        if(!valid){
            std::cout << "Sorry invalid input" << std::endl;
        }
    } while(!valid);

    this->__email = newEmail;
    std::cout << "User Email Updated" << std::endl;
    return true;
    }

const bool User::check_new_email_valid(const std::string &newEmail) const {
    bool nullstr = true;
    bool processingDomain = false;
    int substrLen = 0;
    User::States state = State0;

    if(newEmail.length() > MAX_EMAIL_LENGTH || newEmail.length() < MIN_EMAIL_LENGTH) {
        std::cout << "New email too short or too long! Try a different email." << std::endl;
        return false;
    }

    std::string copy = newEmail;
    for(std::string::iterator it = copy.begin(); it != copy.end(); ++it){
        int intCastedChar = static_cast<int>(*it);
        int notAlNum = isalnum(intCastedChar);
        if (state == State0){
            if (nullstr) {
                if (notAlNum == 0) {
                    return false;
                } else {
                    nullstr = false;
                }
            } else {
                if (notAlNum != 0){
                    // Continue
                } else if (*it == '.') {
                    state = State1;
                    nullstr = true;
                } else if (*it == '@') {
                    state = State2;
                    nullstr = true;
                } else {
                    return false;
                }
            }
        } else if (state == State1) {
            if (nullstr) {
                if (notAlNum == 0) {
                    return false;
                } else {
                    nullstr = false;
                }
            } else {
                if (notAlNum != 0) {
                    //Continue
                } else if (*it == '@') {
                    state = State2;
                    processingDomain = true;
                    nullstr = true;
                } else {
                    return false;
                }
            }
        } else if (state == State2) {
            if (nullstr) {
                if (notAlNum == 0){
                    return false;
                } else {
                    nullstr = false;
                }
            } else {
                if (notAlNum != 0){
                    //Continue
                } else if (*it == '.') {
                    state = processingDomain ? State3 : State2;
                    nullstr = true;
                } else {
                    return false;
                }
            }
        } else {
            if (nullstr){
                if (notAlNum == 0) {
                    return false;
                } else {
                    nullstr = false;
                    ++substrLen;
                }
            } else {
                if (notAlNum == 0) {
                    return false;
                } else {
                    ++substrLen;
                }
            }
        }
    }
    return substrLen == 3;
}

std::ostream& operator<<( std::ostream& output, const User& user) {

    output << "\nUser: " << user.get_user_name()
           << "\nPhone: " << user.get_user_phone()
           << "\nEmail: " << user.get_user_email()
           << std::endl;

    return output;
}
