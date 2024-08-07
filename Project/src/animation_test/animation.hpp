
#include "base.hpp"


class Animation
{
    friend class GameFactory;

public:
    void Animation_play();        // 播放
    void Animation_stop();        // 停止
    void Animation_resetIndex();  // 重置帧索引
    void Animation_setLoop(bool); // 设置循环
    void Animation_update();      // 更新

    Area* Animation_current_frame(); // 获取当前帧

private:
    bool is_playing = false;
    bool is_loop    = false;

    Area** frames      = nullptr; // 帧数组
    int    frame_count = 0;       // 帧数
    int    frame_index = 0;       // 当前帧
};


void
Animation::Animation_play()
{
    is_playing = true;
}

void
Animation::Animation_stop()
{
    is_playing = false;
}

void
Animation::Animation_resetIndex()
{
    frame_index = 0;
}

void
Animation::Animation_setLoop(bool loop)
{
    is_loop = loop;
}

void
Animation::Animation_update()
{
    if(is_playing)
    {
        if(frame_index < frame_count - 1)
        {
            frame_index++;
        }
        else
        {
            if(is_loop)
            {
                frame_index = 0;
            }
            else
            {
                is_playing = false;
            }
        }
    }
}

Area*
Animation::Animation_current_frame()
{
    return frames[frame_index];
}
