#include "passwordGenerator.ih"

namespace
{
    bool isSymbol(char character)
    {
        string const symbols = "!@#$%^&*()-_=+[]{};:,.<>?/";
        return symbols.find(character) != string::npos;
    }
}

bool PasswordGenerator::verifyPassword(string const &password)
{
    bool hasLower  = false;
    bool hasUpper  = false;
    bool hasDigit  = false;
    bool hasSymbol = false;           
    
    for (char const character: password)
    {
        if (islower(character))
            hasLower = true;
        else if (isupper(character))
            hasUpper = true;
        else if (isdigit(character))
            hasDigit = true;
        else if (isSymbol(character))
            hasSymbol = true;
    }

    return hasLower && hasUpper && hasDigit && hasSymbol; 
}