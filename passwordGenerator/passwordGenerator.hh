#ifndef INCLUDED_PASSWORDGENERATOR_
#define INCLUDED_PASSWORDGENERATOR_

#include <string>

class PasswordGenerator
{
    public:
        PasswordGenerator() = default;
        std::string generatePassword(size_t length);

    private:                          
        bool verifyPassword(std::string const &password);
};

#endif 