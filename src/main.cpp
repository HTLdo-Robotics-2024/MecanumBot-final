#include <kipr/wombat.h>
#include "mycanum.hpp"

//constants
#define pi 3.1415926535897932384626433832795028841971693993751


//port variables
int light_sensor_port = 0;
int hand_servo_port = 0;
int arm_servo_port = 0;


//general variables
int hand_open_value = 0;
int hand_closed_value = 2048;
int arm_up_value = 730;
int arm_down_value = 2048;



//general run function
void start();
void remove_poms();


//helper functions
int lerp(int a, int b, float t);


int main()
{
    printf("One small stroll for a robot, one big stroll for KuKuk\n");
	enable_servos();

    start();
    remove_poms();


    return 0;
}

void start() {
    set_servo_position(hand_servo_port, hand_closed_value);
    set_servo_position(arm_servo_port, arm_up_value);
    
    int light_value = 0;

    /*while (1) {
        light_value = analog(light_sensor_port);
        if (light_value <= 2000) {
            printf("Light Activation B)\n");
            break;
        }
    }*/

    
    /*
    * position for the next step
    * this is done here, so if
    * we change the start position -> we change the start function
    * the bot ends up facing the +X axis
    */
    
    left(1200);
    turn_angle(-5);
}


void remove_poms() {
    
	forward(13000);
    for(int i = 0; i < 15; i++) {
    	forward(1);
        turn_angle(3);
    }
}




int lerp(int a, int b, float t) {
	return a * (1-t) + b * t;
}











