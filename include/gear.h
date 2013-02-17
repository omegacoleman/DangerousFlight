
#ifndef _GEAR_H_
#define _GEAR_H_

#define AIR_RESIS 0.97

typedef struct
{
    unsigned int weight;
    int x_vector;
    int y_vector;
    int x;
    int y;
    int angle;
}GearObject;


void give_push(GearObject *gear, int x_push, int y_push);
void step_gear(GearObject *gear);
void set_walls(int top, int bottom, int left, int right);

#endif


