
#include "GameObjects.hpp"

GameObject::GameObject(MessageSystem *mss, Position *pos, Point poi, float m, Vector v) : Object(pos, poi, m, v), message_system(mss) {}

GameObject::~GameObject() {}
