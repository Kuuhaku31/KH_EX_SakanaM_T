
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
Zone::Zone_color(int i) const
{
    Limit(i, 0, 31);
    return colors[i];
}

void*
Zone::Zone_data(int i) const
{
    Limit(i, 0, 31);
    return data[i];
}

void
Zone::Zone_color(int i, int c)
{
    Limit(i, 0, 31);
    colors[i] = c;
}

void
Zone::Zone_data(int i, void* d)
{
    Limit(i, 0, 31);
    data[i] = d;
}
