
#include "GameObjects.hpp"
#include "library.hpp"


class GameFactory
{
public:
    GameFactory(Library*);
    ~GameFactory();

    Fish*   createFish(Zone*, Point);
    Bullet* createBullet(Zone*, Point, Vector);

    void InitZone(Zone*);

private:
    Library* library;
};
