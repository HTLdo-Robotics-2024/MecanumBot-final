#include <kipr/wombat.h>
#include "config.h"

#define FULL_TURN_TIME 5530

void forward(int time) {
	mav(0, 1500);
    mav(1, 1500);
    mav(2, 1500);
    mav(3, 1500);
    msleep(time);
    ao();
}

void backward(int time) {
    mav(0, -1500);
    mav(1, -1500);
    mav(2, -1500);
    mav(3, -1500);
    msleep(time);
    ao();
}

void left(int time) {
    mav(0, 1500);
    mav(1, -1500);
    mav(2, 1500);
    mav(3, -1500);
    msleep(time);
    ao();
}

void right(int time) {
    mav(0, -1500);
    mav(1, 1500);
    mav(2, -1500);
    mav(3, 1500);
    msleep(time);
    ao();
}


void turn_angle(int angle) {
    int current_servo_pos = get_servo_position(arm);
    
    int direction = 1;
    if (angle < 0) {
        direction = -1;
        angle = -angle;
    }
    else {
        direction = 1;
    }
    
    float time = (float)FULL_TURN_TIME;
    printf("%f -> ", time);
    time = time / 360.0; // Ensure floating-point division
    printf("%f -> ", time);
    time = time * (float)angle;
    printf("%f -> ", time);

    
    mav(0, 1500 * direction);
    mav(1, 1500 * direction);
    mav(2, -1500 * direction);
    mav(3, -1500 * direction);
    msleep(time);
    ao();
}
