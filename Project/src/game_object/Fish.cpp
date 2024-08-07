
#include "GameObjects.hpp"


#define barcolor 0x8800ff00
#define barbkcolor 0x88aaaaaa
#define barboundcolor 0x88dddddd

inline void
initbar(Area* barimg)
{
    barimg->Shape_reset(20, 5);
    barimg->Shape_draw_rectangle(0, 0, 20, 5, barboundcolor);
    barimg->Shape_draw_rectangle(1, 1, 18, 3, barbkcolor);
    barimg->Area_align();
    barimg->py -= 10;
}

inline void
setbar(Shape* barimg, int value, int max)
{
    int longer = 18 * value / max;

    barimg->Shape_draw_rectangle(1, 1, longer, 3, barcolor);
    barimg->Shape_draw_rectangle(longer + 1, 1, 18 - longer, 3, barbkcolor);
}

#undef barcolor
#undef barbkcolor
#undef barboundcolor

void
Fish::init()
{
    ObjectResetAreas(FISH_AREA_COUNT);
    ObjectResetColls(FISH_TEST_POINTS_COUNT);

    initbar(&object_areas[fish_HP_bar]);
    initbar(&object_areas[fish_power_bar]);
}

Fish::Fish(Position* pos, Point poi, Area* ca, Area* da)
    : GameObject(pos, poi)
    , coll_area(ca)
    , dHP_area(da)
{
    init();
}

Fish::~Fish()
{
}

void
Fish::Update()
{
    if(!fish_alive) return;

    // 如果HP为0，立即死亡
    if(fish_HP <= 0)
    {
        fish_alive = false;
        return;
    }

    FishSetHP_d(dHP_area->Area_in(this));
    ObjectCollTest(coll_area);

    // 根据碰撞情况更新Movement
#define side 3
#define back 1

    Vector force_vector = ZEROVECTOR;

    int force = 0;

    // 检测上方碰撞
    for(int i = fish_test_point_top_start; i < fish_test_point_top_end; i++)
    {
        force += object_test_points_value[i];
    }
    if(force)
    {
        if(force > WALL_LIM)
        {
            movement_velocity.vy = 0; // 如果受到的力过大，则视为碰到墙壁，立即停止
            py += back;
        }
        else
        {
            force_vector.vy += force / side;
        }
        force = 0;
    }

    // 检测右方碰撞
    for(int i = fish_test_point_right_start; i < fish_test_point_right_end; i++)
    {
        force += object_test_points_value[i];
    }
    if(force)
    {
        if(force > WALL_LIM)
        {
            movement_velocity.vx = 0;
            px -= back;
        }
        else
        {
            force_vector.vx -= force / side;
        }
        force = 0;

        FishSetHP_d(-10);
    }

    // 检测下方碰撞
    for(int i = fish_test_point_down_start; i < fish_test_point_down_end; i++)
    {
        force += object_test_points_value[i];
    }
    if(force)
    {
        if(force > WALL_LIM)
        {
            movement_velocity.vy = 0;
            py -= back;
        }
        else
        {
            force_vector.vy -= force / side;
        }
        force = 0;
    }

    // 检测左方碰撞
    for(int i = fish_test_point_left_start; i < fish_test_point_left_end; i++)
    {
        force += object_test_points_value[i];
    }
    if(force)
    {
        if(force > WALL_LIM)
        {
            movement_velocity.vx = 0;
            px += back;
        }
        else
        {
            force_vector.vx += force / side;
        }
        force = 0;

        FishSetHP_d(-10);
    }

    ObjectAddForce(force_vector);

#undef side
#undef back

    // 更新

    setbar(&object_areas[fish_HP_bar], fish_HP, fish_HP_MAX);
    setbar(&object_areas[fish_power_bar], fish_power, fish_power_MAX);

    GameObject::Update();
}

bool
Fish::FishIsAlive()
{
    return fish_alive;
}

void
Fish::FishKill()
{
    fish_alive = false;
}

Bullet*
Fish::FishShoot(Position* p, Vector v)
{
    fish_power -= bullet_power;
    Bullet* bullet = new Bullet(p, *this, v * 50, dHP_area);
    bullet->ObjectGetArea(bullet_skin)->Shape_copy(&object_areas[fish_bullet_skin]);
    bullet->ObjectGetArea(bullet_skin)->Area_align();
    bullet->ObjectGetArea(bullet_explode_range)->Shape_copy(&object_areas[fish_bullet_hitbox]);
    bullet->ObjectGetArea(bullet_explode_range)->Area_align();

    bullet->px += v.vx * 10;
    bullet->py += v.vy * 10;

    return bullet;
}

Marble*
Fish::FishThrow(Position* p, Vector v)
{
    fish_power -= bullet_power;
    Marble* marble = new Marble(p, *this, v * 50);
    marble->ObjectGetArea(marble_skin)->Shape_copy(&object_areas[fish_bullet_skin]);
    marble->ObjectGetArea(marble_skin)->Area_align();

    marble->px += v.vx * 20;
    marble->py += v.vy * 20;

    return marble;
}

int
Fish::FishGetHP()
{
    return fish_HP;
}
int
Fish::FishGetPower()
{
    return fish_power;
}

void
Fish::FishSetHP(int hp)
{
    fish_HP = hp;
    Limit(fish_HP, 0, fish_HP_MAX);
}

void
Fish::FishSetPower(int p)
{
    fish_power = p;
    Limit(fish_power, 0, fish_power_MAX);
}

void
Fish::FishSetHP_d(int hp)
{
    fish_HP += hp;
    Limit(fish_HP, 0, fish_HP_MAX);
}

void
Fish::FishSetPower_d(int p)
{
    fish_power += p;
    Limit(fish_power, 0, fish_power_MAX);
}

void
Fish::FishAddHitbox(Area* matter)
{
    hitbox_point = object_areas[fish_main_hitbox].Position_root_xy();
    AREA_COMPUTE(matter, (&object_areas[fish_main_hitbox]), (a += b));
}

void
Fish::FishDelHitbox(Area* matter)
{
    M0M2(
        matter,
        (&object_areas[fish_main_hitbox]),
        (hitbox_point.px - matter->Position_root_x()),
        (hitbox_point.py - matter->Position_root_y()),
        {
            (a -= b);
        });
}
