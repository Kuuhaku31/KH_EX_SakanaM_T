
#include "base.hpp"

class Timer
{
public:
    Timer(int = 0);

    void Timer_start();       // 开始计时
    void Timer_stop();        // 停止计时
    void Timer_reset();       // 重置计时
    void Timer_update();      // 更新计时
    void Timer_setLoop(bool); // 设置循环

    int Timer_getTime(); // 获取时间

private:
    bool is_timing = false; // 是否正在计时
    bool is_loop   = false; // 是否循环
    int  time      = 0;     // 时间
    int  time_max  = 0;     // 最大时间
};

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

int
Timer::Timer_getTime()
{
    return time;
}


class AnimationList
{
    friend class Library;

public:
    AnimationList() = default;
    ~AnimationList();

    Area* AnimationList_getFrame(int); // 获取帧

private:
    Area* frames      = nullptr; // 帧数组
    int   frame_count = 0;       // 帧数

    void free(); // 释放内存
};

AnimationList::~AnimationList()
{
    free();
}

void
AnimationList::free()
{
    if(frame_count)
    {
        frame_count = 0;
        delete[] frames;
        frames = nullptr;
    }
}

Area*
AnimationList::AnimationList_getFrame(int index)
{
    if(index < frame_count && index >= 0)
    {
        return &frames[index];
    }
    else
    {
        return nullptr;
    }
}
