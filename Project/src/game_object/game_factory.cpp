#include "game_factory.hpp"

Fish*
GameFactory::createFish()
{
    Fish* fish = new Fish();
    fish->object_areas[0].Shape_copy();
}