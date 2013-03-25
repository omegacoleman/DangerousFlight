
#include "global.h"

#include "gear.h"
#include <math.h>

#define ROTATE_SPEED_MAX 3

int top_wall, bottom_wall, left_wall, right_wall;

int get_target_angle(GearObject *gear);

void init_gear(GearObject *gear, int x, int y, int weight)
{
    gear->x = x;
    gear->y = y;
    gear->weight = weight;
    gear->x_vector = 0;
    gear->y_vector = 0;
    gear->angle = 0;
}

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
    gear->x_vector = (int) (gear->x_vector * AIR_RESIS);
    gear->y_vector = (int) (gear->y_vector * AIR_RESIS);
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
        int target_angle = get_target_angle(gear);
        if(-ROTATE_SPEED_MAX < (target_angle - gear->angle) < ROTATE_SPEED_MAX)
        {
            gear->angle = target_angle;
        } else {
            if (target_angle > gear->angle){
                gear->angle += ROTATE_SPEED_MAX;
            } else {
                gear->angle -= ROTATE_SPEED_MAX;
            }
        }
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
    double ver, hor, angle;
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
    ver = abs(gear->x_vector);
    hor = abs(gear->y_vector);
    angle = (int)(atan(hor / ver) / 3.14159 * 180);
    if(gear->x_vector < 0){
        angle = 180-(int)angle;
    }
    if(gear->y_vector > 0){
        return -(int)angle;
    } else {
        return (int)angle;
    }
}

