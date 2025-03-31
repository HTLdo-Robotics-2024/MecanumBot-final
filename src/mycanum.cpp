#include <kipr/wombat.h>

#define FULL_TURN_TIME 67.5/8
//8 spins took 67.5s

void forward(int time) {
	mav(0, 1000);
    mav(1, 1000);
    mav(2, 1000);
    mav(3, 1000);
    msleep(time);
    ao();
}

void backward(int time) {
    mav(0, -1000);
    mav(1, -1000);
    mav(2, -1000);
    mav(3, -1000);
    msleep(time);
    ao();
}

void left(int time) {
    mav(0, 1000);
    mav(1, -1000);
    mav(2, 1000);
    mav(3, -1000);
    msleep(time);
    ao();
}

void right(int time) {
    mav(0, -1000);
    mav(1, 1000);
    mav(2, -1000);
    mav(3, 1000);
    msleep(time);
    ao();
}


void turn_angle(int angle) {
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
    time = time * 1000.0; // Ensure correct scaling
    printf("%f\n", time);

    
    mav(0, 1000 * direction);
    mav(1, 1000 * direction);
    mav(2, -1000 * direction);
    mav(3, -1000 * direction);
    msleep(time);
    ao();
}