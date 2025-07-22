#include "main.ih"

int main()
{
    Vault vault;

    string const welcomeString = 
        "Welcome to Cerberus! What would you like to do?\n"
        "1. GET a password\n"
        "2. ADD a password\n"
        "3. DELETE a password\n"
        "4. LIST all the entries in the database.\n";
    
    cout << welcomeString;

    vault.add("reddit.com", "cezarbulancea", 20);
}