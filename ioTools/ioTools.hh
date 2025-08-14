#ifndef INCLUDED_IOTOOLS_
#define INCLUDED_IOTOOLS_

#include <string>

/** 
 * \brief Small helper for interactive input. 
 */
class IOTools
{
    public:
        IOTools() = default;

        /** Prints a prompt, reads a full line, and returns a trimmed
         *  (both ends) string. */
        static std::string promptLine(std::string const &prompt);

        /** Prints a prompt and reads input without echoing characters on the 
         *  terminal (supports Windows and POSIX); a newline is still echoed. */
        static std::string hiddenPrompt(std::string const &prompt);
};

#endif