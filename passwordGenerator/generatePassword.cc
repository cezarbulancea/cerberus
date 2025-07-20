#include "passwordGenerator.ih"

string PasswordGenerator::generatePassword(size_t length)
{
    std::string const possibleCharacters =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:,.<>?/";

    std::random_device randomDevice;
    std::mt19937 generator{ randomDevice() };
    std::uniform_int_distribution<> distribution(0, possibleCharacters.size() - 1);

    std::string password;              
                                       // Should have at least a lower, 
    while (!verifyPassword(password))  // an upper, a digit and a symbol
    {
        password = "";
        for (size_t idx = 0; idx != length; ++idx)
            password += possibleCharacters[distribution(generator)];
    }

    return password;
}