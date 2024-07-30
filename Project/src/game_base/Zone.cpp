
#include "base.hpp"

Zone::Zone()
{}

Zone::~Zone()
{
}

int
Zone::ZoneGetColor(ZoneAreaType t) const
{
    return colors[t];
}

// bool
// Zone::ZoneGetData(void* d, ZoneAreaType t) const
// {
//     d = data[t];
//     return d ? true : false;
// }

void
Zone::ZoneSetColor(int c, ZoneAreaType t)
{
    colors[t] = c;
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
