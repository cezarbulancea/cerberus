#ifndef INCLUDED_IOTOOLS_
#define INCLUDED_IOTOOLS_

#include <string>

class IOTools
{
    public:
        IOTools() = default;

        static std::string promptLine(std::string const &message);
        static std::string hiddenPrompt(std::string const &prompt);
};

#endif