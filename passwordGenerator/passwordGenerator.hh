#ifndef INCLUDED_PASSWORDGENERATOR_
#define INCLUDED_PASSWORDGENERATOR_

#include <sodium.h>
#include <string>

class PasswordGenerator
{
    public:
        PasswordGenerator() = default;
        std::string generatePassword(size_t length) const;

    private:                          
        template <size_t N>
        static char pickOne(char const (&set)[N]);
};

#include "pickOne.i"

#endif