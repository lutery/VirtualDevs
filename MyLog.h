#ifndef MYLOG_H
#define MYLOG_H

#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

class MyLog
{
private:
    MyLog(){};

public:
    static log4cplus::Logger MemoryCheck()
    {
        static std::string outTarget = LOG4CPLUS_TEXT("MemoryCheck");
        static log4cplus::Logger outInstance = log4cplus::Logger::getInstance(outTarget);

        return outInstance;
    }

public:
    static void I(std::string logTxt)
    {
        LOG4CPLUS_INFO(MyLog::MemoryCheck(), LOG4CPLUS_TEXT(logTxt));
    }

    template<class T, class... Args>
    static void I(std::string logTxt, T arg, Args... args)
    {
//        std::string log = logTxt + " " + arg;
        MyLog::I(logTxt + " " + arg, args...);
    }

    static void W(std::string logTxt)
    {
        LOG4CPLUS_WARN(MyLog::MemoryCheck(), LOG4CPLUS_TEXT(logTxt));
    }

    static void E(std::string logTxt)
    {
        LOG4CPLUS_ERROR(MyLog::MemoryCheck(), LOG4CPLUS_TEXT(logTxt));
    }
};

#define LOGI(logTxt) \
    LOG4CPLUS_INFO(MyLog::MemoryCheck(), LOG4CPLUS_TEXT(logTxt));

#define LOGIM(logTxt, ...) \
    MyLog::I(logTxt, __VA_ARGS__);

#endif // MYLOG_H
