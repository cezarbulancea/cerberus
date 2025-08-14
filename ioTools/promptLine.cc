#include "ioTools.ih"
                                       // static
string IOTools::promptLine(string const &prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
                                       // trim leading whitespace
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";                     // all blanks
                                       // trim trailing whitespace
    size_t end = line.find_last_not_of(" \t\r\n");
    return line.substr(start, end - start + 1);
}
