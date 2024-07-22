
#include "GameObjects.hpp"

inline void ceck(int line, int &v)
{
    if (v < 0)
    {
        v = 0;
    }
    if (v > line)
    {
        v = line;
    }
}

Fish::Fish(MessageSystem *mss, Zone *z) : GameObject(mss, z) {}
Fish::~Fish() {}

bool Fish::FishUpdate()
{
    //...
    return true;
}

int Fish::FishGetHP() { return fish_HP; }
int Fish::FishGetPower() { return fish_power; }

void Fish::FishSetHP(int hp)
{
    fish_HP = hp;
    ceck(fish_HP_MAX, fish_HP);
}

void Fish::FishSetPower(int p)
{
    fish_power = p;
    ceck(fish_power_MAX, fish_power);
}

void Fish::FishSetHP_d(int hp)
{
    fish_HP += hp;
    ceck(fish_HP_MAX, fish_HP);
}

void Fish::FishSetPower_d(int p)
{
    fish_power += p;
    ceck(fish_power_MAX, fish_power);
}