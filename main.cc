#include "main.ih"

int main()
{
    Vault vault;

    vault.add("reddit.com", "cezarbulancea", 20);

    string secret = vault.get("reddit.com", "cezarbulancea");
    cout << secret << '\n';
}