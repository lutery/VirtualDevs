#include "MyLog.h"


QString MyLog::addLogs(std::initializer_list<QString> logs)
{
    if (mLogs.size() >= mMaxLogCount)
    {
        mLogs.removeFirst();
    }

    QString curLog;
    for (auto log : logs)
    {
        curLog += log;
    }

    mLogs.append(curLog);

    return curLog;
}
