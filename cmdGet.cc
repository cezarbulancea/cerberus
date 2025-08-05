#include "main.ih"

void cmdGet(Vault &vault)
{
    string const website = IOTools::promptLine("Website: ");
    string const userId  = IOTools::promptLine("User identifier: ");

    if (website.empty() || userId.empty())
    {
        cout << "Lookup aborted (empty field).\n";
        return;
    }

    try
    {
        string password = vault.get(website, userId);
        cout << "Password: " << password << '\n';
                                       // Wipe after it has been displayed or 
                                       // copied elsewhere
        sodium_memzero(password.data(), password.size());
    }
    catch (exception const &ex)
    {
        cout << ex.what() << '\n';
    }
}