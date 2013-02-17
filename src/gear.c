
#include <gear.h>
#include <math.h>

int top_wall, bottom_wall, left_wall, right_wall;

void give_push(GearObject *gear, int x_push, int y_push)
{
    gear->x_vector += x_push;
    gear->y_vector += y_push;
}

void step_gear(GearObject *gear)
{
    gear->y_vector += gear->weight;
    gear->x += gear->x_vector;
    gear->y += gear->y_vector;
    gear->x_vector *= AIR_RESIS;
    gear->y_vector *= AIR_RESIS;
    if(gear->x < left_wall)
    {
        gear->x = left_wall;
        gear->x_vector = abs(gear->x_vector);
    }
    if(gear->x > right_wall)
    {
        gear->x = right_wall;
        gear->x_vector = -abs(gear->x_vector);
    }
    if(gear->y < top_wall)
    {
        gear->y = top_wall;
        gear->y_vector = abs(gear->y_vector);
    }
    if(gear->y > bottom_wall)
    {
        gear->y = bottom_wall;
        gear->y_vector = -abs(gear->y_vector);
    } else {
        gear->angle += (get_target_angle(gear) - gear->angle) / 2;
    }
}

void set_walls(int top, int bottom, int left, int right)
{
    top_wall = top;
    bottom_wall = bottom;
    left_wall = left;
    right_wall = right;
}

int get_target_angle(GearObject *gear)
{
    if(gear->y_vector == 0){
        return 0;
    }
    if(gear->x_vector == 0){
        if(gear->y_vector > 0){
            return -90;
        } else {
            return 90;
        }
    }
    double ver = abs(gear->x_vector);
    double hor = abs(gear->y_vector);
    int angle = (int)(atan(hor / ver) / M_PI * 180);
    if(gear->x_vector < 0){
        angle = -angle;
    }
    if(gear->y_vector > 0){
        return -angle;
    } else {
        return angle;
    }
}

