
#include "GameObjects.hpp"

GameObject::GameObject(MessageSystem *mss, Zone *z, Point poi, float m, Vector v) : Object(z, poi, m, v), message_system(mss) {}

GameObject::~GameObject() {}

// void GameObject::GameObjectUpdate(Zone zone)
// {
//     if (zone.move_area->Area_in(this))
//     {
//         MovementUpdate(zone.relative);
//     }
// }
