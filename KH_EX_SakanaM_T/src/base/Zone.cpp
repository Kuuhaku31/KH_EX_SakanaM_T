
#include "base.hpp"

Zone::Zone(uint w, uint h) : Area(ZEROPOINT, w, h) {}
Zone::Zone(Shape *s) : Area(s) {}
Zone::~Zone() {}

Vector Zone::ZoneGetRelative(ZoneAreaType t) { return relatives[t - RELATIVE_AREA_START]; }
float Zone::ZoneGetWallCollForce(ZoneAreaType t) { return wall_coll_force[t - WALL_AREA_START]; }
float Zone::ZoneGetCollForce(ZoneAreaType t) { return coll_force[t - COLL_AREA_START]; }
int Zone::ZoneGetDHP(ZoneAreaType t) { return dHP[t - DHP_AREA_START]; }

void Zone::ZoneSetRelative(ZoneAreaType t, Vector v) { relatives[t - RELATIVE_AREA_START] = v; }
void Zone::ZoneSetWallCollForce(ZoneAreaType t, float f) { wall_coll_force[t - WALL_AREA_START] = f; }
void Zone::ZoneSetCollForce(ZoneAreaType t, float f) { coll_force[t - COLL_AREA_START] = f; }
void Zone::ZoneSetDHP(ZoneAreaType t, int i) { dHP[t - DHP_AREA_START] = i; }
