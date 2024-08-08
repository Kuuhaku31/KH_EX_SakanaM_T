
#include "base.hpp"

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

Shape*
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

int
AnimationList::AnimationList_getFrameCount()
{
    return frame_count;
}
