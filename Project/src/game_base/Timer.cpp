
#include "base.hpp"

Timer::Timer(int max)
{
    time_max = max;
}

void
Timer::Timer_start()
{
    is_timing = true;
}

void
Timer::Timer_stop()
{
    is_timing = false;
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
Timer::Timer_setLoop(bool loop)
{
    is_loop = loop;
}

void
Timer::Timer_setTime(int t)
{
    time = t;
    Timer_reset();
}

int
Timer::Timer_getTime()
{
    return time;
}
