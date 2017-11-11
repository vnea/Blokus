#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

typedef struct coord
{
    int x;
    int y;
} t_coord;

void translation_x_coord(t_coord *coord, int delta_x);
void translation_y_coord(t_coord *coord, int delta_y);
void translation_xy_coord(t_coord *coord, int delta_x, int delta_y);

#endif // COORD_H_INCLUDED
