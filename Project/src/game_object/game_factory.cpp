
#include "game_factory.hpp"


// 碰撞检测
// 用于检测角色是否与墙体或其他角色发生碰撞
// 有12个检测点，分别在角色的四个角和四个边的中点
// 当角色的检测点与墙体或其他角色的检测点重合时，认为发生碰撞
/*

(-hw,-hh)---(0,-hh)----(hw,-hh)
   |           |           |
   |           |           |
(-hw,0)------(0,0)-------(hw,0)
   |           |           |
   |           |           |
(-hw,hh)-----(0,hh)----(hw,hh)

*/

// 快速设置检测点
void
setTestPoints(Position* master, Position* ps, int count, int w, int h)
{
    if(count % 4)
    {
        for(int i = 0; i < count; i++)
        {
            ps[i] = ZEROPOINT;
        }
    }
    else
    {
        int side     = count / 4;      // 每个边上的点数
        int spaced_w = w / (side + 1); // 每个边上的点的间隔
        int spaced_h = h / (side + 1); // 每个边上的点的间隔

        for(int i = 1; i <= side; i++)
        {
            ps[i]            = Point{ spaced_w * i, 0 };
            ps[i + side]     = Point{ w, spaced_h * i };
            ps[i + 2 * side] = Point{ w - spaced_w * i, h };
            ps[i + 3 * side] = Point{ 0, h - spaced_h * i };
        }
        for(int i = 0; i < count; i++) ps[i] += Point{ -w / 2, -h / 2 };
    }

    for(int i = 0; i < count; i++) ps[i].parent_pos = master;
}

GameFactory::GameFactory(Library* lib)
    : library(lib)
{
}

GameFactory::~GameFactory()
{
}

Fish*
GameFactory::createFish(Zone* zone, Point p)
{
    Fish* fish       = new Fish(zone);
    fish->parent_pos = zone;
    fish->Position_xy_to(p);

    // 动画
    fish->animation_list = library->LibAnimation(ani_sakana_swim);
    fish->animation_timer.Timer_setTime(fish->animation_list->AnimationList_getFrameCount());

    // 质量
    fish->area_matter.Shape_copy(library->LibMat(shape_hitbox_sakana));
    fish->area_matter.Shape_clear(20, 0);
    fish->area_matter.Area_align();

    // 设置测试点
    fish->test_point_count  = FISH_TEST_POINTS_COUNT;
    fish->test_points       = new Position[FISH_TEST_POINTS_COUNT];
    fish->test_points_value = new int[FISH_TEST_POINTS_COUNT];
    setTestPoints(fish, fish->test_points, FISH_TEST_POINTS_COUNT, 20, 20);

    return fish;
}

Bullet*
GameFactory::createBullet(Zone* zone, Point p, Vector v)
{
    Bullet* bullet     = new Bullet(zone);
    bullet->parent_pos = zone;
    bullet->Position_xy_to(p);
    bullet->movement_velocity = v;

    // 动画
    bullet->animation_list = library->LibAnimation(ani_bullet_fly);
    bullet->animation_timer.Timer_setTime(bullet->animation_list->AnimationList_getFrameCount());

    // 质量
    bullet->area_matter.Shape_copy(library->LibMat(shape_hitbox16));
    bullet->area_matter.Shape_clear(20, 0);
    bullet->area_matter.Area_align();

    // 爆炸范围
    bullet->explode_timer_del.Timer_setTime(100);
    bullet->explode_area.Shape_copy(library->LibMat(shape_img_skin_ikacyan));

    return bullet;
}

void
GameFactory::InitZone(Zone* z)
{
}
