
#include "base.hpp"

Zone::Zone()
{}

Zone::Zone(int w, int h)
    : Area(ZEROPOINT, w, h)
{}

Zone::Zone(Shape* s)
    : Area(s)
{}

Zone::~Zone()
{}

int
Zone::ZoneGetColor(int t) const
{
    if(t >= 0 && t < 32)
    {
        return colors[t];
    }
    else
    {
        return 0;
    }
}

void
Zone::ZoneSetColor(int c, int t)
{
    if(t >= 0 && t < 32)
    {
        colors[t] = c;
    }
}

// bool
// Zone::ZoneSetData(void* d, ZoneAreaType t)
// {
//     if(d)
//     {
//         data[t] = d;
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }
