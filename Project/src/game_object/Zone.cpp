
#include "GameObjects.hpp"


Zone::Zone()
{
    zone_data.parent_pos   = this;
    zone_matter.parent_pos = this;
    zone_damage.parent_pos = this;
}

Zone::~Zone()
{
}
