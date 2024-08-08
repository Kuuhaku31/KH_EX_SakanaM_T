
#include "base.hpp"


// 天才！！！！
// 一个Area的点有32位
// 每一位表示不同的Area
// 一个Zone类可以存储32个Area信息
// main_area 为主要区域，用于判断是否在区域内
class Zone : public Position
{
public:
    Zone();
    ~Zone();

    Area zone_data;
    Area zone_matter;
    Area zone_damage;

    int zone_data_colors[32] = { 0 };

    void ZoneSetArea(Area*, int); // 设置某个area的区域
};


// bar类
struct Bar : public Area
{
    int bar_border_thickness = 1;
    int bar_background_color = 0x88cccccc;
    int bar_border_color     = 0x88000000;
    int bar_fill_color       = 0x8800ff00;

    void Bar_draw(int, int);
};
