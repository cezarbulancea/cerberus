#include "main.ih"

namespace
{
    enum
    {
        PASSWORD_LENGTH = 20
    };
}

void cmdAdd(Vault &vault)
{
    string website = IOTools::promptLine("Website: ");
    string userId  = IOTools::promptLine("User identifier: ");

    if (website.empty() || userId.empty())
    {
        cout << "Nothing stored (empty field).\n";
        return;
    }

    vault.add(website, userId, PASSWORD_LENGTH);
    cout << "✓ Stored / updated credential.\n";
}