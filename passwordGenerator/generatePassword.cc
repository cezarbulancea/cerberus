#include "passwordGenerator.ih"

namespace
{
    enum
    {
        CHARACTER_TYPES = 4
    };

    char constexpr LOWER[]  = "abcdefghijklmnopqrstuvwxyz";
    char constexpr UPPER[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char constexpr DIGIT[]  = "0123456789";
    char constexpr SYMBOL[] = "!@#$%^&*()-_=+[]{};:,.<>?/";
    char constexpr ALL[]    =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:,.<>?/";
}

string PasswordGenerator::generatePassword(size_t length) const
{
    if (length < CHARACTER_TYPES)
        throw invalid_argument("Password length must be at least 4");

    string password;
    password.reserve(length);
                                       // each type should be represented
    password.push_back(pickOne(LOWER));
    password.push_back(pickOne(UPPER));
    password.push_back(pickOne(DIGIT));
    password.push_back(pickOne(SYMBOL));

    while (password.size() < length)   // fill the rest
        password.push_back(pickOne(ALL));

                                       // shuffle with Fisher–Yates using CSPRNG
    for (size_t idx = password.size(); idx != 1; --idx) 
    {
        uint32_t position = randombytes_uniform(static_cast<uint32_t>(idx));
        swap(password[idx - 1], password[position]);
    }

    return password;
}