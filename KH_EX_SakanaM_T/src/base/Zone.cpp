
#include "base.hpp"

Zone::Zone(uint w, uint h) : Area(ZEROPOINT, w, h) {}
Zone::Zone(Shape *s) : Area(s) {}
Zone::~Zone() {}

void Zone::ZoneClear(ZoneAreaType t)
{
    uint tem = (0x1 << t) | 0xffffffff;
    for (uint i = 0; i < shape_long; i++)
    {
        shape_buffer[i] &= tem;
    }
}

void Zone::ZoneCompute(Area *, ZoneAreaType)
{
}

Vector Zone::ZoneGetRelative(ZoneAreaType t) { return relatives[t - RELATIVE_AREA_START]; }
float Zone::ZoneGetWallCollForce(ZoneAreaType t) { return wall_coll_force[t - WALL_AREA_START]; }
float Zone::ZoneGetCollForce(ZoneAreaType t) { return coll_force[t - COLL_AREA_START]; }
int Zone::ZoneGetDHP(ZoneAreaType t) { return dHP[t - DHP_AREA_START]; }

void Zone::ZoneSetRelative(ZoneAreaType t, Vector v) { relatives[t - RELATIVE_AREA_START] = v; }
void Zone::ZoneSetWallCollForce(ZoneAreaType t, float f) { wall_coll_force[t - WALL_AREA_START] = f; }
void Zone::ZoneSetCollForce(ZoneAreaType t, float f) { coll_force[t - COLL_AREA_START] = f; }
void Zone::ZoneSetDHP(ZoneAreaType t, int i) { dHP[t - DHP_AREA_START] = i; }
