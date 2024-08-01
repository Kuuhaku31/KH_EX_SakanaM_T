
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

Fish::Fish()
{
    init();
}

Fish::Fish(Position* pos, Point poi)
    : Object(pos, poi)
{
    init();
}

Fish::~Fish()
{}

void
Fish::Update()
{
    // 如果HP为0，立即死亡
    if(fish_HP <= 0) { fish_alive = false; }


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

    Object::Update();
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