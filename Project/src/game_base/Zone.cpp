
#include "base.hpp"

Zone::Zone()
{}

Zone::~Zone()
{}

int
Zone::Zone_color(int i) const
{
    Limit<0, 31>(i);
    return colors[i];
}

void*
Zone::Zone_data(int i) const
{
    Limit<0, 31>(i);
    return data[i];
}

void
Zone::Zone_color(int i, int c)
{
    Limit<0, 31>(i);
    colors[i] = c;
}

void
Zone::Zone_data(int i, void* d)
{
    Limit<0, 31>(i);
    data[i] = d;
}
