#include <iostream>
#include "User.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    User* user = new User("Alex", "1234", "(303)246-7650", "alex.foreman@yahoo.com");
    //User* user = new User();
    user->authenticate_user();

    std::cout << "TESTING PRINTING OF USER" << *user;

    delete user;
    return 0;
}