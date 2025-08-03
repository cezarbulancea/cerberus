#include "vault.ih"

#if defined(_WIN32)                    // ───── Windows branch ─────
#   include <windows.h>
#   include <conio.h>
string Vault::hiddenPrompt(string const &prompt)
{
    cout << prompt << flush;

    string password;
    for (;;)
    {
        int ch = _getch();             // char, but no echo
        if (ch == '\r' || ch == '\n')
            break;

        if (ch == '\b')                // backspace support
        {                              
            if (!password.empty()) 
                password.pop_back();
            continue;
        }

        password.push_back(static_cast<char>(ch));
    }

    cout << '\n';
    return password;
}

#else                                  // ───── POSIX / UNIX branch ─────
#   include <termios.h>
#   include <unistd.h>
#   include <stdexcept>
string Vault::hiddenPrompt(string const &prompt)
{
    cout << prompt << flush;

    termios oldAttr, newAttr;
    if (tcgetattr(STDIN_FILENO, &oldAttr) == -1)
        throw runtime_error("tcgetattr failed");

    newAttr = oldAttr;
    newAttr.c_lflag &= ~ECHO;          // clear echo bit
    newAttr.c_lflag |= ECHONL;         // but still echo newline

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newAttr) == -1)
        throw runtime_error("tcsetattr failed");

    string password;
    getline(cin, password);
                                       // restore terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldAttr);
    return password;
}
#endif