#include "passwordGenerator.ih"

string PasswordGenerator::generatePassword(size_t length)
{
    string const possibleCharacters =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:,.<>?/";

    random_device randomDevice;
    mt19937 generator{ randomDevice() };
    uniform_int_distribution<> distribution(0, possibleCharacters.size() - 1);

    string password;              
                                       // Should have at least a lower, 
    while (!verifyPassword(password))  // an upper, a digit and a symbol
    {
        password = "";
        for (size_t idx = 0; idx != length; ++idx)
            password += possibleCharacters[distribution(generator)];
    }

    return password;
}