#ifndef TIME_HPP
#define TIME_HPP

namespace Time
{

    unsigned long startTimeOffset = 0;

    void Init()
    {
        unsigned long timeFromSterver = 0;
        startTimeOffset = timeFromSterver - millis();
    }

    unsigned long GetTime()
    {
        return startTimeOffset + millis();
    }
};

using Time::GetTime();

#endif