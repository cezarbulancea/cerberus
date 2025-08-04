#include "main.ih"

int main()
try
{
    Vault vault;

    for (;;)
    {
        cout << "\nCommands:  add   get   quit\n> ";
        string cmd;
        if (!(cin >> cmd))
            break;                     // EOF / Ctrl-D
                                       // consume newline left by >> 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cmd == "add")
            cmdAdd(vault);
        else if (cmd == "get")
            cmdGet(vault);
        else if (cmd == "quit" || cmd == "exit")
            break;
        else
            cout << "Unknown command.\n";
    }
}
catch (exception const &ex)
{
    cerr << "Fatal error: " << ex.what() << '\n';
    return 1;
}