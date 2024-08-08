
#include "base.hpp"

Timer::Timer(int max)
{
    time_max = max;
}

void
Timer::Timer_reset()
{
    time = time_max;
}

void
Timer::Timer_update()
{
    if(is_timing)
    {
        if(time > 0)
        {
            time--;
        }
        else
        {
            if(is_loop)
            {
                time = time_max;
            }
            else
            {
                is_timing = false;
            }
        }
    }
}

void
Timer::Timer_setTime(int t)
{
    time_max = t;
    Timer_reset();
}

int
Timer::Timer_getTime()
{
    return time;
}
