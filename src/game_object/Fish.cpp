
#include "GameObjects.hpp"


#define barcolor 0x8800ff00
#define barbkcolor 0x88aaaaaa
#define barboundcolor 0x88dddddd


#undef barcolor
#undef barbkcolor
#undef barboundcolor

Fish::Fish(Zone* z)
    : GameObject(z)
{
    fish_HP_bar.parent_pos = this;
    fish_HP_bar.Shape_reset(20, 5);
    fish_HP_bar.Area_align();
    fish_HP_bar.py -= 15;
}

Fish::~Fish()
{
    FishMatterDel();
}

void
Fish::Update()
{
    if(!is_alive) return;

    // 如果HP为0，立即死亡
    if(fish_HP <= 0)
    {
        is_alive = false;
        return;
    }

    FishSetHP_d(zone->zone_damage.Area_in(this));

    updateTestValue();

    // 根据碰撞情况更新Movement
#define side 3
#define back 1

    Vector force_vector = ZEROVECTOR;

    int force = 0;

    // 检测上方碰撞
    for(int i = fish_test_point_top_start; i < fish_test_point_top_end; i++)
    {
        force += test_points_value[i];
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
        force += test_points_value[i];
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
        force += test_points_value[i];
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
        force += test_points_value[i];
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

    Force(force_vector);

#undef side
#undef back

    updateMovement();
    updateTimer();

    // 更新bar
    fish_HP_bar.Bar_draw(fish_HP, fish_HP_MAX);
    fish_power_bar.Bar_draw(fish_power, fish_power_MAX);
}

// Bullet*
// Fish::FishShoot(Position* p, Vector v)
// {
//     fish_power -= bullet_power;
//     Bullet* bullet = new Bullet(p, *this, v * 50, dHP_area);
//     bullet->ObjectGetArea(bullet_skin)->Shape_copy(&object_areas[fish_bullet_skin]);
//     bullet->ObjectGetArea(bullet_skin)->Area_align();
//     bullet->ObjectGetArea(bullet_explode_range)->Shape_copy(&object_areas[fish_bullet_hitbox]);
//     bullet->ObjectGetArea(bullet_explode_range)->Area_align();

//     bullet->px += v.vx * 10;
//     bullet->py += v.vy * 10;

//     return bullet;
// }

// Marble*
// Fish::FishThrow(Position* p, Vector v)
// {
//     fish_power -= bullet_power;
//     Marble* marble = new Marble(p, *this, v * 50);
//     marble->ObjectGetArea(marble_skin)->Shape_copy(&object_areas[fish_bullet_skin]);
//     marble->ObjectGetArea(marble_skin)->Area_align();

//     marble->px += v.vx * 20;
//     marble->py += v.vy * 20;

//     return marble;
// }

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
Fish::FishMatterAdd()
{
    if(is_add_matter)
    {
        return;
    }
    else
    {
        is_add_matter = true;
        hitbox_point  = area_matter.Position_root_xy();
        zone->zone_matter += area_matter;
    }
}

void
Fish::FishMatterDel()
{
    if(is_add_matter)
    {
        is_add_matter = false;
        zone->zone_matter.Shape_merge(&area_matter, hitbox_point, default_action_sub);
    }
    else
    {
        return;
    }
}
