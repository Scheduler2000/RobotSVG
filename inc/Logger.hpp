#if !defined(__LOGGER__)
#define __LOGGER__

#include <string>

enum class LoggerPriority : short
{
    Fatal_Error,
    Error,
    Warn,
    Info,
    Debug
};

class Logger
{

public:
    Logger();
    ~Logger();
    void Log(std::string const &message, LoggerPriority priority) const;
};

#endif // __LOGGER__
