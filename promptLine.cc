#include "main.ih"

string promptLine(string const &message)
{
    cout << message;
    string line;
    getline(cin, line);
                                       // trim left
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";                     // all blanks
                                       // trim right
    size_t end = line.find_last_not_of(" \t\r\n");
    return line.substr(start, end - start + 1);
}
