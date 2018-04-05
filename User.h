//
// Created by Tyhhy on 3/29/2018.
//

#ifndef TEST_USER_H
#define TEST_USER_H
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>


#define MAX_ATTEMPTS 3
#define MAX_NAME_LENGTH 64
#define MAX_PASSWORD_LENGTH 16
#define MIN_PASSWORD_LENGTH 8
#define PHONE_NUMBER_LENGTH 13
#define MAX_EMAIL_LENGTH 128
#define MIN_EMAIL_LENGTH 9



/******************************************************************************************************************
 *                                                USER CLASS                                                      *
 ******************************************************************************************************************
 *  Attributes:                                                                                                   *
 *     __name (std::string) - This is the user's login name. It must be alphanumeric (hyphens are allowed) and a  *
 *                          single word.                                                                          *
 *     __password (std::string) - This is the user's login password. It must be between 8 and 16 alphanumeric     *
 *                              characters. It must be encrypted.                                                 *
 *     __phone (std::string) - Must be of the format (###)###-####, does not need to be a valid phone number, but *
 *                             must be in valid format.                                                           *
 *     __email (std::string) - Must be in the format (an)*.(an)*@a*.(ananan). Where an is alphanumeric. Does not  *
 *                             need to be valid but must be in valid format.                                      *
 *     __UUID (long)         - This is the user's unique ID number. This will be incremented every time a new user*
 *                             is created.                                                                        *
 * ---------------------------------------------------------------------------------------------------------------*
 *  Functions:
 ******************************************************************************************************************/

class User {
private:
    enum States {State0, State1, State2, State3};

    std::string __name;
    std::string __password;
    std::string __phone;
    std::string __email;
    long __UUID;

    const bool new_user(std::string*, std::string*, std::string*, std::string*);

public:
    /* Constructor's for the User Class */
    User();
    User(std::string name, std::string password, std::string phone, std::string email) :
              __name(name), __password(password), __phone(phone), __email(email) {}


    /* Getters and Setters */
    inline const std::string& get_user_name() const { return this->__name; }
    inline const std::string& get_user_phone() const { return this->__phone; }
    inline const std::string& get_user_email() const { return this->__email; }
    inline const long get_user_uuid() const { return this->__UUID; }
private:
    inline const std::string* get_user_password() const { return &(this->__password); }
    void set_user_name(const std::string& nme) { this->__name = nme; }
    void set_user_password(const std::string& pwd) { this->__password = pwd; }
    void set_user_phone(const std::string& phn) { this->__phone = phn; }
    void set_user_email(const std::string& eml) { this->__email = eml; }
    void set_user_uuid(const long uuid) { this->__UUID = uuid; }

public:
    /* Helper Functions */
    const bool authenticate_user() const;
    const bool authenticate_user(const std::string&, const std::string&) const;
    const bool update_user_name();
    const bool check_new_name_valid(const std::string&) const;
    const bool update_user_password();
    const bool check_new_password_valid(const std::string&) const;
    const bool update_user_phone();
    const bool check_new_phone_valid(const std::string&) const;
    const bool update_user_email();
    const bool check_new_email_valid(const std::string&) const;


public:
    bool validate_user_password(const std::string*);

    friend std::ostream &operator<<( std::ostream&, const User&);
};

#endif //TEST_USER_H
