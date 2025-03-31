#include <kipr/wombat.h>
#include "mycanum.hpp"

//constants
#define pi 3.1415926535897932384626433832795028841971693993751


//port variables
int light_sensor_port = 0;
int hand_servo_port = 1;
int arm_servo_port = 0;


//general variables
int hand_open_value = 1000;
int hand_closed_value = 0;
int arm_up_value = 730;
int arm_down_value = 2048;



//main functions
void start();
void remove_poms();
void relocate_bottle(int bottle_id);


//helper functions
int lerp(int a, int b, float t);


int main()
{
    printf("One small stroll for a robot, one big stroll for KuKuk\n");
    enable_servos();
    start();
    //remove_poms();
    
    relocate_bottle(1);

    return 0;
}

/*main functions*/
void start() {
    set_servo_position(hand_servo_port, hand_closed_value);
    set_servo_position(arm_servo_port, arm_up_value);

    /*int light_value = 0;

    while (1) {
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

    left(1500);
    turn_angle(-3);
}


void remove_poms() {

    //all in the row
    forward(13000);
    ao();
    //pushing them aside
    mav(0, 1000);
    mav(1, 1000);
    msleep(4000);
    ao();
    //backing up
    mav(0, -1000);
    mav(1, -1000);
    msleep(4000);
    ao();
    //the other two
    backward(6000);
    left(2500);
    forward(1250);
    right(2500);
    backward(7500);
    
    /*re-align with wall(s)*/
    backward(1000);
    right(3000);
    
}


void relocate_bottle(int bottle_id) {
	/* bottles (looking in +Y)
    * 4  5  6
    * 1  2  3
    */
    
    //x_{dis}\left(x\right)=\operatorname{mod}\left(x+2,3\right)+1
    //y_{dis}\left(x\right)=\operatorname{floor}\left(\frac{x}{4}\right)+1
    int x_distance = ((bottle_id + 2) % 3) + 1;
    int y_distance = bottle_id / 4 + 1; //integer division default: floor
    
    int distance_multiplier = 2000;
    
    printf("x: %d, y: %d\n", x_distance, y_distance);
    
    
    forward(5500);
    msleep(2000);
    
    forward(x_distance*distance_multiplier);
    msleep(1000);
    turn_angle(90);
    msleep(1000);
    forward(y_distance*distance_multiplier);

}





/*Helper functions*/
int lerp(int a, int b, float t) {
    return a * (1-t) + b * t;
}











