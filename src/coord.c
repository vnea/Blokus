#include "../include/coord.h"

void translation_x_coord(t_coord *coord, int delta_x)
{
    coord->x += delta_x;
}

void translation_y_coord(t_coord *coord, int delta_y)
{
    coord->y += delta_y;

}

void translation_xy_coord(t_coord *coord, int delta_x, int delta_y)
{
    translation_x_coord(coord, delta_x);
    translation_y_coord(coord, delta_y);
}
