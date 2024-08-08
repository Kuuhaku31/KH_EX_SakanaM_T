
#include "game_widgets.hpp"


void
Bar::Bar_draw(int value, int value_max)
{
    int wide = shape_wide - bar_border_thickness * 2;
    int high = shape_high - bar_border_thickness * 2;

    int fill_w = (value / 1.0 / value_max) * wide;

    // draw border
    Shape_clear(bar_border_color);

    // draw fill
    Shape_draw_rectangle(bar_border_thickness,
                         bar_border_thickness,
                         fill_w,
                         high,
                         bar_fill_color);

    // draw background
    Shape_draw_rectangle(bar_border_thickness + fill_w,
                         bar_border_thickness,
                         wide - fill_w,
                         high,
                         bar_background_color);
}
