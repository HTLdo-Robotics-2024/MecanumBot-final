#include <kipr/wombat.h>
#include "mycanum.hpp"
#include "config.h"

//general variables





//main functions
void start();
void remove_poms();
void relocate_bottle(int bottle_id);


//helper functions
int lerp(int a, int b, float t);

void set_servo_position_slow(int servo, int pos1, int duration);


int main()
{
    printf("One small stroll for a robot, one big stroll for KuKuk\n");
    enable_servos();
    
    start();
    
    remove_poms();
    
    relocate_bottle(1);
	
    return 0;
}

/*main functions*/
void start() {
    set_servo_position(hand, closed);
    set_servo_position(arm, up);

    int light_value = 0;

    while (1) {
        light_value = analog(light_sensor);
        if (light_value <= 2000) {
            printf("Light Activation B)\n");
            break;
        }
    }


    /*
    * position for the next step
    * this is done here, so if
    * we change the start position -> we change the start function
    * the bot ends up facing the +X axis
    */

    left(1000);
    //turn_angle(-3);
}


void remove_poms() {

    //all in the row
    forward(8666);
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
    backward(4000);
    left(1666);
    forward(833);
    right(1666);
    backward(5000);
    
    /*re-align with wall(s)*/
    backward(1000);
    right(3000);
    
}


void relocate_bottle(int bottle_id) {
    set_servo_position(hand, closed);
    set_servo_position(arm, up);
    
    /* bottles (looking in +Y)
    * 4  5  6
    * 1  2  3
    */
    
    //x_{dis}\left(x\right)=\operatorname{mod}\left(x+2,3\right)+1
    //y_{dis}\left(x\right)=\operatorname{floor}\left(\frac{x}{4}\right)+1
    int x_distance = ((bottle_id + 2) % 3) + 1;
    int y_distance = bottle_id / 4 + 1; //integer division default: floor
    
    int distance_multiplier = 200;
    
    printf("x: %d, y: %d\n", x_distance, y_distance);
    
    
    //go to the general bottle position
    left(2500);
    forward(3500);
    msleep(1000);
    
    //grab bottle)
    forward(x_distance*distance_multiplier);
	turn_angle(90);

    set_servo_position_slow(hand, open, 1000);
    set_servo_position_slow(arm, middle, 2000);
    
    forward(y_distance*distance_multiplier);
    msleep(1000);
    
    set_servo_position_slow(hand, semi_closed, 5000);
    set_servo_position_slow(arm, up, 5000);
    
    
    
	backward(y_distance*distance_multiplier);  
    turn_angle(-90);
    backward(4000);
    right(4000);
    
    set_servo_position(hand, semi_closed);
    set_servo_position(arm, up);
}





/*Helper functions*/
int lerp(int a, int b, float t) {
    return a * (1-t) + b * t;
}


void set_servo_position_slow(int servo, int pos1, int duration) {
    int pos0 = get_servo_position(servo);

    int num_steps = abs(pos1 - pos0);
    int time_step = duration / num_steps;

    if (pos1 >= pos0) {
        printf("%d > %d", pos1, pos0);
        for (int pos = pos0; pos < pos1; pos++) {
            set_servo_position(servo, pos);
            msleep(time_step);
        }
    } else {
        for (int pos = pos0; pos >= pos1; pos--) {
            set_servo_position(servo, pos);
            msleep(time_step);
        }
    }

}








